#include <stdio.h>

#include "board.h"

int main()
{
    BOARD board;

    board_init(board);
    printf("S-a facut initializarea tablei cu 0\n");

    if(board_cell_status(board, 5,3)==CELL_EMPTY)
    {
        printf("corect: este goala\n");
    }
    
    int cell[4][2]= { {19, 0}, {19, 1}, {19, 2}, {19, 3}};
    
    board_lock_piece(board, cell, 4, 1);
    printf("Piesa lipita pe linia 19: tetronimo linie ****\n");

    if(board_is_row_full(board, 19)==NOT_FULL)
    {
        printf("corect! nu s a umplut randul\n");
    }

    int Cells[6][2]= { {19, 4}, {19, 5}, {19, 6}, {19, 7}, {19, 8}, {19, 9}};

    board_lock_piece(board, Cells, 6, 1);

    if(board_is_row_full(board, 19)==NOT_FULL)
    {
        printf("incorect! s a umplut randul\n");
    }
    else
    {
        printf("corect!! este plin\n");
    }
    return 0;
}