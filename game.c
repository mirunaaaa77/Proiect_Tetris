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

        /* la fiecare 10 piese → piesa instabila */
    game->piece_count++;
    if (game->piece_count % 10 == 0)
        game->is_unstable = 1;
    else
        game->is_unstable = 0;

    //daca nu poate fi plasata -> game over
    if (!tetromino_can_place(&game->piece, game->board))
        return 0;

    return 1;
}

//Actualizeaza scorul dupa stergere
static void update_score(Game *game, int cleared,int exploded_blocks)
{
    if (cleared > 0)
        game->score += SCORE_TABLE[cleared] * game->level;

    /* 50 puncte per bloc distrus de explozie */
    if (exploded_blocks > 0)
        game->score += exploded_blocks * 50;

    game->lines += cleared;

    /* creste nivelul la fiecare 10 linii */
    game->level = (game->lines / 10) + 1;
    game->drop_speed = get_drop_speed(game->level);
}


/* Lipeste piesa pe tabla si spawneaza urmatoarea */
static void lock_and_spawn(Game *game)
{
    int cells[4][2];
    for (int i = 0; i < 4; i++)
    {
        cells[i][0] = game->piece.row +
            shapes[game->piece.type][game->piece.rotation][i][0];
        cells[i][1] = game->piece.col +
            shapes[game->piece.type][game->piece.rotation][i][1];
    }

    /* culoarea depinde de tipul piesei — instabila primeste CELL_UNSTABLE */
    int color = game->is_unstable ? CELL_UNSTABLE : game->piece.type + 1;
    board_lock_piece(game->board, cells, 4, color);

    /* sterge randurile pline si obtine blocurile explodiate */
    int exploded_blocks = 0;
    int cleared = board_clear_full_rows(game->board, &exploded_blocks);
    update_score(game, cleared, exploded_blocks);

    /* spawneaza piesa urmatoare */
    if (!spawn_piece(game))
        game->state = GAME_OVER;
}

static void hard_drop(Game *game)
{
    while (tetromino_can_place(&game->piece, game->board))
        game->piece.row++;

    /* a mers prea jos cu 1 — da inapoi */
    game->piece.row--;
    
    /* Blochează piesa imediat */
    lock_and_spawn(game);
}

void game_init(Game *game)
{
    srand(time(NULL));

    board_init(game->board);

    game->state       = GAME_RUNNING;
    game->score       = 0;
    game->level       = 1;
    game->lines       = 0;
    game->drop_timer  = 0;
    game->drop_speed  = get_drop_speed(1);
    game->piece_count = 0;
    game->is_unstable = 0;

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
                   {} tetromino_move_down(&game->piece, game->board);
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
                    /* piesa s-a oprit — da inapoi */
                    game->piece.row--;

                    /* Deleagă TOATĂ logica către funcția care o face deja corect */
                    lock_and_spawn(game);
                }
            }
        }

        /* ── Randare ────────────────────── */
        renderer_clear();
        renderer_draw_board(game->board);

        if (game->state == GAME_RUNNING)
            renderer_draw_piece(&game->piece, game->is_unstable);

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