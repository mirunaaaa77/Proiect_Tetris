#include <stdio.h>

#include "board.h"
#include "tetromino.h"

int main()
{
    BOARD board;
    Tetro_piece piece;

    board_init(board);
    printf("S-a facut initializarea tablei cu 0\n");
    board_print(board);

    if(board_cell_status(board, 5,3)==CELL_EMPTY)
    {
        printf("corect: este goala\n");
    }
    
    int cell[4][2]= { {19, 0}, {19, 1}, {19, 2}, {19, 3}};
    
    board_lock_piece(board, cell, 4, 1);
    printf("Piesa lipita pe linia 19: tetronimo linie ****\n");
    board_print(board);

    if(board_is_row_full(board, 19)==NOT_FULL)
    {
        printf("corect! nu s a umplut randul\n");
    }

    int Cells[6][2]= { {19, 4}, {19, 5}, {19, 6}, {19, 7}, {19, 8}, {19, 9}};

    board_lock_piece(board, Cells, 6, 1);
    board_print(board);

    if(board_is_row_full(board, 19)==NOT_FULL)
    {
        printf("incorect! s a umplut randul\n");
    }
    else
    {
        printf("corect!! nu este plin\n");
    }
    board_print(board);

     tetromino_init(&piece, PIECE_I);
    printf("Piesa I creata la row=%d col=%d rot=%d\n",
           piece.row, piece.col, piece.rotation);

    /* 3. Testeaza can_place */
    if (tetromino_can_place(&piece, board))
        printf("Piesa POATE fi plasata - CORECT!\n");

    /* 4. Testeaza move_right */
    tetromino_move_right(&piece, board);
    printf("Dupa move_right: col=%d\n", piece.col);

    /* 5. Testeaza move_left */
    tetromino_move_left(&piece, board);
    printf("Dupa move_left: col=%d\n", piece.col);

    /* 6. Testeaza rotate */
    tetromino_rotate(&piece, board);
    printf("Dupa rotate: rotation=%d\n", piece.rotation);

    return 0;
}