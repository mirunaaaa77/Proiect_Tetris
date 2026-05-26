#define _POSIX_C_SOURCE 199309L
#include <time.h>
#include <stdlib.h>
#include "game.h"
#include "input.h"
#include "renderer.h"

//Punctaj pentru linii sterse
static const int SCORE_TABLE[5] = {0, 100, 300, 500, 800};

//Viteza in functie de nivel (ms)
static int get_drop_speed(int level)
{
    if (level >= 10) return 100;
    return 800 - (level - 1) * 70;
}

//Genereaza un tip de piesa random
static Tetro_type random_piece()
{
    return (Tetro_type)(rand() % TETRO_COUNT);
}

//Spawneaza o piesa noua
static int spawn_piece(Game *game)
{
    tetromino_init(&game->piece, random_piece());

    //daca nu poate fi plasata -> game over
    if (!tetromino_can_place(&game->piece, game->board))
        return 0;

    return 1;
}

//Actualizeaza scorul dupa stergere
static void update_score(Game *game, int cleared)
{
    if (cleared <= 0) return;

    game->score += SCORE_TABLE[cleared] * game->level;
    game->lines += cleared;

    //creste nivelul la fiecare 10 linii
    game->level = (game->lines / 10) + 1;
    game->drop_speed = get_drop_speed(game->level);
}

//Hard drop (coboara instant)
static void hard_drop(Game *game)
{
    while (tetromino_can_place(&game->piece, game->board))
        game->piece.row++;

    //a mers prea jos cu 1 — da inapoi
    game->piece.row--;
}

//── game_init ────────────────────────────
void game_init(Game *game)
{
    srand(time(NULL));

    board_init(game->board);

    game->state      = GAME_RUNNING;
    game->score      = 0;
    game->level      = 1;
    game->lines      = 0;
    game->drop_timer = 0;
    game->drop_speed = get_drop_speed(1);

    spawn_piece(game);

    renderer_init();
}

/* ── game_over ──────────────────────────── */
void game_over(Game *game)
{
    renderer_cleanup();
}

// ── game_run ─────────────────────────────
void game_run(Game *game)
{
    struct timespec ts_start, ts_end;
    int elapsed_ms;

    while (game->state != GAME_OVER)
    {
        clock_gettime(CLOCK_MONOTONIC, &ts_start);

        // ── Input ────────────────────────
        Action action = input_get_action();

        if (game->state == GAME_RUNNING)
        {
            switch (action)
            {
                case ACTION_MOVE_LEFT:
                    tetromino_move_left(&game->piece, game->board);
                    break;
                case ACTION_MOVE_RIGHT:
                    tetromino_move_right(&game->piece, game->board);
                    break;
                case ACTION_MOVE_DOWN:
                   {
                case ACTION_MOVE_DOWN:
                if (!tetromino_move_down(&game->piece, game->board)) 
                {
                    // AICI trebuie să apelezi funcția ta care cimentează piesa!
                    // Numele diferă în funcție de cum l-ai scris tu, de ex:
                    board_lock_piece(game);
                    board_clear_row(game);
                    spawn_piece(game);
                    
                    // Opțional: resetează timpul (ts_start) pentru a nu avea o dublă-cădere imediată
                    clock_gettime(CLOCK_MONOTONIC, &ts_start);
                }
                    break;
                case ACTION_ROTATE:
                    tetromino_rotate(&game->piece, game->board);
                    break;
                case ACTION_DROP:
                    hard_drop(game);
                    break;
                case ACTION_PAUSE:
                    game->state = GAME_PAUSED;
                    break;
                case ACTION_QUIT:
                    game->state = GAME_OVER;
                    return;
                default:
                    break;
            }
        }
        else if (game->state == GAME_PAUSED)
        {
            if (action == ACTION_PAUSE)
                game->state = GAME_RUNNING;
            if (action == ACTION_QUIT)
                return;
        }

        /* ── Cadere automata ────────────── */
        if (game->state == GAME_RUNNING)
        {
            game->drop_timer += 16; /* ~16ms per frame (60fps) */

            if (game->drop_timer >= game->drop_speed)
            {
                game->drop_timer = 0;

                /* incearca sa coboare */
                game->piece.row++;

                if (!tetromino_can_place(&game->piece, game->board))
                {
                    /* piesa s-a oprit — da inapoi si lipeste */
                    game->piece.row--;

                    /* obtine celulele piesei */
                    int cells[4][2];
                    for (int i = 0; i < 4; i++)
                    {
                        extern const int shapes[7][4][4][2];
                        cells[i][0] = game->piece.row +
                            shapes[game->piece.type][game->piece.rotation][i][0];
                        cells[i][1] = game->piece.col +
                            shapes[game->piece.type][game->piece.rotation][i][1];
                    }

                    board_lock_piece(game->board, cells, 4,
                                     game->piece.type + 1);

                    //sterge randurile pline
                    int cleared = board_clear_full_rows(game->board);
                    update_score(game, cleared);

                    /* spawneaza piesa urmatoare */
                    if (!spawn_piece(game))
                    {
                        game->state = GAME_OVER;
                    }
                }
            }
        }

        /* ── Randare ────────────────────── */
        renderer_clear();
        renderer_draw_board(game->board);

        if (game->state == GAME_RUNNING)
            renderer_draw_piece(&game->piece);

        renderer_draw_score(game->score, game->level, game->lines);

        if (game->state == GAME_PAUSED)
        {
            mvprintw(10, BOARD_COLUMNS + 2, "*** PAUZA ***");
            mvprintw(11, BOARD_COLUMNS + 2, "Apasa P pentru a continua");
        }

        if (game->state == GAME_OVER)
        {
            mvprintw(10, BOARD_COLUMNS + 2, "*** GAME OVER ***");
            mvprintw(11, BOARD_COLUMNS + 2, "Scor final: %d", game->score);
            mvprintw(12, BOARD_COLUMNS + 2, "Apasa Q pentru a iesi");
            refresh();
            /* asteapta Q */
            while (input_get_action() != ACTION_QUIT);
            return;
        }

        refresh();

        /* ── ~60 FPS ─────────────────────── */
        clock_gettime(CLOCK_MONOTONIC, &ts_end);
        elapsed_ms = (ts_end.tv_nsec - ts_start.tv_nsec) / 1000000;
        if (elapsed_ms < 16)
        {
            struct timespec sleep_ts = {0, (16 - elapsed_ms) * 1000000};
            nanosleep(&sleep_ts, NULL);
        }
    }
}