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
        Clock pClock;
        Time time;
        Time pTime;
        Text score;
        ostringstream ssScore;
        Text title;
        int iScore;
        int iTime;
        RectangleShape playingField;
        RectangleShape infoField;
        Snake snake;
        Apple apple;

        bool checkCollisions();
        void setApplePosition();
        bool snakeAteApple();
        void setTitle();
        void setPlayingField();
        void setInfoField();
        void setScore();
        void updateScore();
        bool showContinue(RenderWindow &window);
        bool showGameOver(RenderWindow &window);
};

#endif // ENGINE_H
