#include "Game.h"
#include <cstdlib>
#include <ctime>


int main()
{
    srand(time(NULL));
    Game game;
    game.run();

    return EXIT_SUCCESS;
}
