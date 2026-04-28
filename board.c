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
            if (!board_cell_status(board, row, j))
            {
                return NOT_FULL;
            }
        }
        return FULL;
}

void board_clear_row(BOARD board, int row)
{
    for (int i = 0; i < BOARD_COLUMNS; i++)
    {
        board[row][i] = CELL_EMPTY;
    }
}

int board_clear_full_rows(BOARD board)
{
    int cleared = 0;
    int row = BOARD_ROWS - 1;

    while (row >= 0)
    {
        if (board_is_row_full(board, row) == FULL)
        {
            board_clear_row(board, row);
            for (int i = row; i > 0; i--)
            {
                for (int j = 0; j < BOARD_COLUMNS; j++)
                {
                    board[i][j] = board[i-1][j];
                }
            }
            cleared++;
        }
        else
        {
            row--;
        }
    }
    return cleared;
}

void board_print(BOARD board)  //pentru debugging
{
    // bordura de sus
    printf("+");
    for (int i = 0; i < BOARD_COLUMNS; i++)
        printf("-");
    printf("+\n");

    // randurile
    for (int i = 0; i < BOARD_ROWS; i++)
    {
        printf("|");
        for (int j = 0; j < BOARD_COLUMNS; j++)
        {
            if (board[i][j] == CELL_EMPTY)
                printf(" ");
            else
                printf("#");
        }
        printf("|\n");
    }

    // bordul de jos
    printf("+");
    for (int i = 0; i < BOARD_COLUMNS; i++)
        printf("-");
    printf("+\n");
    printf("\n");
}


