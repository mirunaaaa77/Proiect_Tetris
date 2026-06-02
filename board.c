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
    /* BUG FIX: > inlocuit cu >= pentru a nu accesa out-of-bounds */            
    if ((row < 0) || (row >= BOARD_ROWS))                                       
        return 0;                                                               
    if ((col < 0) || (col >= BOARD_COLUMNS))                                    
        return 0;                                                               
                                                                                
    if (board[row][col] == CELL_EMPTY)                                          
        return CELL_EMPTY;                                                      
    else                                                                        
        return CELL_FILLED;                                                     
}        

void board_lock_piece(BOARD board, int cell[][2], int count, int color)         
{                                                                               
    int i;                                                                      
    for (i = 0; i < count; i++)                                                 
    {                                                                           
        int row = cell[i][0];                                                   
        int col = cell[i][1];                                                   
                                                                                
        /* BUG FIX: > inlocuit cu >= */                                         
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
            return NOT_FULL;                                                    
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

// Explodeaza blocurile instabile dintr-un rand si vecinii lor 3x3 */             
int board_explode(BOARD board, int row)                                           
{                                                                                 
    int blocks_destroyed = 0;                                                     
                                                                                  
    for (int col = 0; col < BOARD_COLUMNS; col++)                                 
    {                                                                             
        if (board[row][col] == CELL_UNSTABLE)                                     
        {                                                                         
            /* unda de soc 3x3 */                                                 
            for (int i = -1; i <= 1; i++)                                         
            {                                                                     
                for (int j = -1; j <= 1; j++)                                     
                {                                                                 
                    int r = row + i;                                              
                    int c = col + j;                                              
                    if (r >= 0 && r < BOARD_ROWS &&                               
                        c >= 0 && c < BOARD_COLUMNS &&                            
                        board[r][c] != CELL_EMPTY)                                
                    {                                                             
                        board[r][c] = CELL_EMPTY;                                 
                        blocks_destroyed++;                                       
                    }                                                             
                }                                                                 
            }                                                                     
        }                                                                         
    }                                                                             
    return blocks_destroyed;                                                      
}            
int board_clear_full_rows(BOARD board, int *exploded_blocks)                      
{                                                                                 
    int cleared = 0;                                                              
    int row = BOARD_ROWS - 1;                                                     
    *exploded_blocks = 0;                                                         
                                                                                  
    while (row >= 0)                                                              
    {                                                                             
        if (board_is_row_full(board, row) == FULL)                                
        {                                                                         
            /* verifica daca randul contine blocuri instabile */                  
            int exploded = board_explode(board, row);                             
            *exploded_blocks += exploded;                                         
                                                                                  
            /* sterge randul si coboara tot ce e deasupra */                      
            board_clear_row(board, row);                                          
            for (int i = row; i > 0; i--)                                         
                for (int j = 0; j < BOARD_COLUMNS; j++)                           
                    board[i][j] = board[i - 1][j];                                
                                                                                  
            /* goleste randul 0 */                                                
            for (int j = 0; j < BOARD_COLUMNS; j++)                               
                board[0][j] = CELL_EMPTY;                                         
                                                                                  
            cleared++;                                                            
            /* nu decrementam row - verificam acelasi index din nou */            
        }                                                                         
        else                                                                      
        {                                                                         
            row--;                                                                
        }                                                                         
    }                                                                             
    return cleared;                                                               
}        

/*void board_print(BOARD board)  //pentru debugging
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

    // bodura de jos
    printf("+");
    for (int i = 0; i < BOARD_COLUMNS; i++)
        printf("-");
    printf("+\n");
    printf("\n");
}*/


