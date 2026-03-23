#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "board.h"

void board_init(BOARD board)
{
    memset(board, 0, sizeof(BOARD));
}

int board_cell_status(const BOARD board, int row, int col)
{
    if ((row < 0) || (row >= BOARD_ROWS))
    {
        return 0;
    }
    if ((col < 0) || (col >= BOARD_COLUMNS))
    {
        return 0;
    }
    if (board[row][col] == CELL_EMPTY)
        return CELL_EMPTY;
    else
    {
        return CELL_FILLED;
    }
}

void board_lock_piece(BOARD board, int cell[][2], int count, int color) /* marcheaza pe tabla locul piesei*/
{
    int i;
    for (i = 0; i < count; i++)
    {
        int row = cell[i][0];
        int col = cell[i][1];

        if (row < 0 || row >= BOARD_ROWS)
            continue;    
        if (col < 0 || col >= BOARD_COLUMNS)
            continue;

        board[row][col] = color;
    }
}

int board_is_row_full(BOARD board, int row)
{
        int j;
        for (j = 0; j < BOARD_COLUMNS; j++)
        {
            if (board_cell_status(board, row, j))
            {
                return NOT_FULL;
            }
        }
        return FULL;
}