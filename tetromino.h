#ifndef TETROMINO_H
#define TETROMINO_H

#include "board.h"

#define TETRO_SIZE 4
#define TETRO_COUNT 7

typedef enum
{
    PIECE_I = 0,
    PIECE_O,
    PIECE_T,
    PIECE_L,
    PIECE_J,
    PIECE_S,
    PIECE_Z,
}Tetro_type;

typedef struct
{
    Tetro_type type;
    int row, col;
    int rotation;

}Tetro_piece;

void tetromino_init(Tetro_piece *piece, Tetro_type type);

int tetromino_can_place(Tetro_piece *piece, const BOARD board);

void tetromino_rotate(Tetro_piece *piece, const BOARD board);

void tetromino_move_left(Tetro_piece *piece, const BOARD board);

void tetromino_move_right(Tetro_piece *piece, const BOARD board);

#endif