#ifndef INPUT_H
#define INPUT_H

#include <ncurses.h>

/* Actiunile posibile ale jucatorului */
typedef enum
{
    ACTION_NONE = 0,
    ACTION_MOVE_LEFT,
    ACTION_MOVE_RIGHT,
    ACTION_MOVE_DOWN,
    ACTION_ROTATE,
    ACTION_DROP,      //coboara instant
    ACTION_PAUSE,
    ACTION_QUIT
} Action;

//Citeste o tasta si returneaza actiunea corespunzatoare 
Action input_get_action();

#endif
