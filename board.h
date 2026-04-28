#ifndef BOARD_H
#define BOARD_H

/*dimensiunea tablei*/
#define BOARD_COLUMNS 10
#define BOARD_ROWS 20

/*valorile casutelor*/
#define CELL_EMPTY 0
#define CELL_FILLED 1

#define NOT_FULL 0
#define FULL 1

typedef int BOARD[BOARD_ROWS][BOARD_COLUMNS];

void board_init(BOARD board);

int board_cell_status(const BOARD board, int row, int col);

void board_lock_piece(BOARD board, int cell[][2], int count, int color);

int board_is_row_full(BOARD board, int row);

void board_clear_row(BOARD board, int row);

int board_clear_full_rows(BOARD board);

void board_print(BOARD board); 

#endif