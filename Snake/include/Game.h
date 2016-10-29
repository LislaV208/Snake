#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <string>

using namespace sf;
using namespace std;

class Game
{
    public:
        Game();
        ~Game();

        friend class Engine;

        const static int WIDTH = 1024;
        const static int HEIGHT = 768;

        void run();
    protected:
    private:
        Font font;

        enum GameState {
            MENU,
            GAME,
            GAMEOVER,
            END
        };
        GameState state;

        void menu();
        void play();

};

#endif // GAME_H
