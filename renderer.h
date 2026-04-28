#ifndef RENDERER_H
#define RENDERER_H

#include <ncurses.h>
#include "board.h"
#include "tetromino.h"

void renderer_init();
void renderer_cleanup();
void renderer_draw_board(const BOARD board);
void renderer_draw_piece(const Tetro_piece *piece);
void renderer_draw_score(int score, int level, int lines);
void renderer_clear();

#endif