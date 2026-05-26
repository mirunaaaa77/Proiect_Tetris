#include "input.h"

Action input_get_action()
{
    int key = getch(); //citeste tasta 
    switch (key)
    {
        case KEY_LEFT:  return ACTION_MOVE_LEFT;
        case KEY_RIGHT: return ACTION_MOVE_RIGHT;
        case KEY_DOWN:  return ACTION_MOVE_DOWN;
        case KEY_UP:    return ACTION_ROTATE;
        case 'a':
        case 'A':       return ACTION_MOVE_LEFT;
        case 's':
        case 'S':       return ACTION_MOVE_DOWN;
        case 'd':
        case 'D':       return ACTION_MOVE_RIGHT;
        case 'w':
        case 'W':       return ACTION_ROTATE;
        case ' ':       return ACTION_DROP;
        case 'p':
        case 'P':       return ACTION_PAUSE;
        case 'q':
        case 'Q':
        case 27:        return ACTION_QUIT; /* 27 = ESC */
        default:        return ACTION_NONE;

    }
}
