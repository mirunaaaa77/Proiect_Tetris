#include "game.h"

int main()
{
    Game game;

    game_init(&game);
    game_run(&game);
    game_over(&game);

    return 0;
}
