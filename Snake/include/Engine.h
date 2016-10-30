#ifndef ENGINE_H
#define ENGINE_H

#include <SFML/Graphics.hpp>
#include <windows.h>
#include <game.h>
#include <sstream>
#include <ctime>

#include "Snake.h"
#include "Apple.h"

using namespace sf;


class Engine
{
    public:
        Engine();
        ~Engine();
        void run(RenderWindow &window);

    protected:
    private:
        Event event;
        Font font;
        Clock clock;
        Time time;
        Text score;
        ostringstream ssScore;
        Text title;
        int iScore;
        RectangleShape playingField;
        RectangleShape infoField;
        Snake snake;
        Apple apple;

        void handleKeyboardInput(RenderWindow&, Event, bool&, bool&);
        bool checkCollisions();
        bool win();
        void setApplePosition();
        bool snakeAteApple();
        void setTitle();
        void setPlayingField();
        void setInfoField();
        void setScore();
        void updateScore();
        bool showContinue(RenderWindow &window);
        bool showGameOver(RenderWindow &window);
        bool showWin(RenderWindow&);
};

#endif // ENGINE_H
