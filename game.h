#ifndef GAME_H
#define GAME_H

#include "board.h"
#include "tetromino.h"

/* Starile posibile ale jocului */
typedef enum
{
    GAME_RUNNING = 0,
    GAME_PAUSED,
    GAME_OVER
} GameState;

/* Structura principala a jocului */
typedef struct
{
    BOARD       board;        /* tabla de joc          */
    Tetro_piece piece;        /* piesa care cade acum  */
    GameState   state;        /* starea jocului        */
    int         score;        /* scorul curent         */
    int         level;        /* nivelul curent        */
    int         lines;        /* linii sterse total    */
    int         drop_timer;   /* timer pentru cadere   */
    int         drop_speed;   /* viteza de cadere (ms) */
} Game;

void game_init(Game *game);
void game_run(Game *game);
void game_over(Game *game);

#endif
