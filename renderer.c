#include <locale.h>
#include "renderer.h"
#include "board.h"
#include "tetromino.h"

/* ── renderer_init ──────────────────────── */                         
void renderer_init()                                                    
{                                                                       
    setlocale(LC_ALL, "");                                              
    initscr();                                                          
    noecho();                                                           
    cbreak();                                                           
    keypad(stdscr, TRUE);                                               
    curs_set(0);                                                        
    nodelay(stdscr, TRUE);                                              
                                                                        
    start_color();                                                      
    init_pair(1, COLOR_CYAN,    COLOR_BLACK); /* I */                   
    init_pair(2, COLOR_YELLOW,  COLOR_BLACK); /* O */                   
    init_pair(3, COLOR_MAGENTA, COLOR_BLACK); /* T */                   
    init_pair(4, COLOR_WHITE,   COLOR_BLACK); /* L */                   
    init_pair(5, COLOR_BLUE,    COLOR_BLACK); /* J */                   
    init_pair(6, COLOR_GREEN,   COLOR_BLACK); /* S */                   
    init_pair(7, COLOR_RED,     COLOR_BLACK); /* Z */                   
    init_pair(8, COLOR_WHITE,   COLOR_WHITE); /* INSTABILA - alb */     
}                                        

// renderer_cleanup ───────────────────── 
void renderer_cleanup()
{
    endwin(); // opreste ncurses
}

// renderer_clear ───────────────────────
void renderer_clear()
{
    clear();
}

/* ── renderer_draw_board ────────────────── */                         
void renderer_draw_board(const BOARD board)                             
{                                                                       
    /* borduri laterale */                                              
    for (int i = 0; i < BOARD_ROWS; i++)                                
    {                                                                   
        mvaddch(i, 0, '|');                                             
        mvaddch(i, BOARD_COLUMNS * 2 + 1, '|');                         
    }                                                                   
                                                                        
    /* linie de jos */                                                  
    for (int j = 0; j <= BOARD_COLUMNS * 2 + 1; j++)                    
        mvaddch(BOARD_ROWS, j, '-');                                    
                                                                        
    /* celulele tablei */                                               
    for (int i = 0; i < BOARD_ROWS; i++)                                
    {                                                                   
        for (int j = 0; j < BOARD_COLUMNS; j++)                         
        {                                                               
            if (board[i][j] != CELL_EMPTY)                              
            {                                                           
                /* CELL_UNSTABLE (8) foloseste color pair 8 */          
                int color = (board[i][j] == CELL_UNSTABLE) ? 8 : board[\
i][j];                                                                  
                attron(COLOR_PAIR(color));                              
                mvaddch(i, j * 2 + 1, ACS_BLOCK);                       
                mvaddch(i, j * 2 + 2, ACS_BLOCK);                       
                attroff(COLOR_PAIR(color));                             
            }                                                           
            else                                                        
            {                                                           
                mvaddstr(i, j * 2 + 1, "  ");                           
            }                                                           
        }                                                               
    }                                                                   
}    

/* ── renderer_draw_piece ────────────────── */                         
void renderer_draw_piece(const Tetro_piece *piece, int is_unstable)     
{                                                                       
    /* piesa instabila = alb (color 8), altfel culoarea tipului */      
    int color = is_unstable ? 8 : piece->type + 1;                      
                                                                        
    attron(COLOR_PAIR(color));                                          
    for (int i = 0; i < 4; i++)                                         
    {                                                                   
        int row = piece->row + shapes[piece->type][piece->rotation][i][\
0];                                                                     
        int col = piece->col + shapes[piece->type][piece->rotation][i][\
1];                                                                     
                                                                        
        if (row >= 0 && row < BOARD_ROWS &&                             
            col >= 0 && col < BOARD_COLUMNS)                            
        {                                                               
            mvaddch(row, col * 2 + 1, ACS_BLOCK);                       
            mvaddch(row, col * 2 + 2, ACS_BLOCK);                       
        }                                                               
    }                                                                   
    attroff(COLOR_PAIR(color));                                         
}   

/* ── renderer_draw_score ────────────────── */                         
void renderer_draw_score(int score, int level, int lines)               
{                                                                       
    int x = BOARD_COLUMNS * 2 + 5;                                      
                                                                        
    mvprintw(2,  x, "TETRIS");                                          
    mvprintw(4,  x, "SCOR:   %d", score);                               
    mvprintw(6,  x, "NIVEL:  %d", level);                               
    mvprintw(8,  x, "LINII:  %d", lines);                               
    mvprintw(12, x, "CONTROALE:");                                      
    mvprintw(13, x, "<-/A  Stanga");                                    
    mvprintw(14, x, "->/D  Dreapta");                                   
    mvprintw(15, x, "Sus/W Roteste");                                   
    mvprintw(16, x, "Jos/S Coboara");                                   
    mvprintw(17, x, "SPC   Drop");                                      
    mvprintw(18, x, " P    Pauza");                                     
    mvprintw(19, x, "ESC   Iesire");                                    
}        