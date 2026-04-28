#include <string.h>

#include "board.h"
#include "tetromino.h"

const int shapes[TETRO_COUNT][4][4][2] = {

    // PIECE_I
    {
        {{1,0},{1,1},{1,2},{1,3}},  // rot 0 - orizontal
        {{0,2},{1,2},{2,2},{3,2}},  // rot 1 - vertical
        {{2,0},{2,1},{2,2},{2,3}},  // rot 2 - orizontal
        {{0,1},{1,1},{2,1},{3,1}},  // rot 3 - vertical
    },

    // PIECE_O
    {
        {{0,1},{0,2},{1,1},{1,2}},  // rot 0
        {{0,1},{0,2},{1,1},{1,2}},  // rot 1 (identic)
        {{0,1},{0,2},{1,1},{1,2}},  // rot 2 (identic)
        {{0,1},{0,2},{1,1},{1,2}},  // rot 3 (identic)
    },

    // PIECE_T
    {
        {{0,1},{1,0},{1,1},{1,2}},  // rot 0
        {{0,1},{1,1},{1,2},{2,1}},  // rot 1
        {{1,0},{1,1},{1,2},{2,1}},  // rot 2
        {{0,1},{1,0},{1,1},{2,1}},  // rot 3
    },

    // PIECE_L
    {
        {{0,0},{1,0},{1,1},{1,2}},  // rot 0
        {{0,0},{0,1},{1,0},{2,0}},  // rot 1
        {{1,0},{1,1},{1,2},{2,2}},  // rot 2
        {{0,1},{1,1},{2,0},{2,1}},  // rot 3
    },

    // PIECE_J
    {
        {{0,2},{1,0},{1,1},{1,2}},  // rot 0
        {{0,0},{1,0},{2,0},{2,1}},  // rot 1
        {{1,0},{1,1},{1,2},{2,0}},  // rot 2
        {{0,0},{0,1},{1,1},{2,1}},  // rot 3
    },

    // PIECE_S
    {
        {{0,1},{0,2},{1,0},{1,1}},  // rot 0
        {{0,0},{1,0},{1,1},{2,1}},  // rot 1
        {{0,1},{0,2},{1,0},{1,1}},  // rot 2 (identic cu 0)
        {{0,0},{1,0},{1,1},{2,1}},  // rot 3 (identic cu 1)
    },

    // PIECE_Z
    {
        {{0,0},{0,1},{1,1},{1,2}},  // rot 0
        {{0,1},{1,0},{1,1},{2,0}},  // rot 1
        {{0,0},{0,1},{1,1},{1,2}},  // rot 2 (identic cu 0)
        {{0,1},{1,0},{1,1},{2,0}},  // rot 3 (identic cu 1)
    },
};

void tetromino_init(Tetro_piece *piece, Tetro_type type)
{
    piece->type=type;
    piece->row=0;
    piece->col=3;
    piece->rotation=0;
}

int tetromino_can_place(Tetro_piece *piece, const BOARD board)
{
    for (int i = 0; i < 4; i++)
    {
        int row = piece->row + shapes[piece->type][piece->rotation][i][0];
        int col = piece->col + shapes[piece->type][piece->rotation][i][1];

        if (board_cell_status(board, row, col)==CELL_FILLED)
            return 0;
    }
    return 1;
}

void tetromino_rotate(Tetro_piece *piece, const BOARD board)
{
    // salveaza rotatia veche
    int old_rotation = piece->rotation;

    // incearca noua rotatie
    piece->rotation = (piece->rotation + 1) % 4;

    // verifica daca nu poate sta acolo
    if (!tetromino_can_place(piece, board))
    {
        piece->rotation = old_rotation;
    }
}

void tetromino_move_left(Tetro_piece *piece, const BOARD board)
{
    int old_col = piece->col;
    piece->col = piece->col - 1;
    if(!tetromino_can_place(piece,board))
    {
        piece->col = old_col;
    }
}


void tetromino_move_right(Tetro_piece *piece, const BOARD board)
{
    int old_col = piece->col;
    piece->col = piece->col + 1;
    if(!tetromino_can_place(piece,board))
    {
        piece->col = old_col;
    }
}