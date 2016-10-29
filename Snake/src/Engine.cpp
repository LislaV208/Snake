#include "Engine.h"
#include "Snake.h"
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>

using namespace sf;
using namespace std;

Engine::Engine()
{
    if (!font.loadFromFile("data/Mecha.ttf"))
    {
        MessageBox(NULL,"Font not found!","ERROR",NULL);
		return;
    }
}

Engine::~Engine()
{
    //dtor
}

void Engine::run(RenderWindow &window)
{
    bool menu = false;
    bool directionSet = false;
    iTime = (rand() % 15) + 10;

    setTitle();
    setPlayingField();
    setInfoField();
    setScore();

    snake.create();
    apple.create();
    setApplePosition();

    while (!menu)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        time = clock.getElapsedTime();
        pTime = pClock.getElapsedTime();
        updateScore();
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                if (!showContinue(window)) menu = true;
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                    if (!showContinue(window)) menu = true;
                if (!directionSet){
                    if (event.key.code == Keyboard::Up){
                        if (snake.getDirection() != Snake::Direction::DOWN) snake.setDirection(0);
                    }
                    if (event.key.code == Keyboard::Left){
                        if (snake.getDirection() != Snake::Direction::RIGHT) snake.setDirection(1);
                    }
                    if (event.key.code == Keyboard::Down){
                        if (snake.getDirection() != Snake::Direction::UP) snake.setDirection(2);
                    }
                    if (event.key.code == Keyboard::Right){
                        if (snake.getDirection() != Snake::Direction::LEFT) snake.setDirection(3);
                    }
                    directionSet = true;
                }
            }
        }

        if (time.asSeconds() >= 1.1 / snake.getSpeed()){
            snake.move(snake.getDirection()); directionSet = false;
            time = clock.restart();
        }

        if (!checkCollisions())
        {
            if(!showGameOver(window)) menu = true;
            else run(window); return;
        }
        if (snakeAteApple());


        window.clear();
        window.draw(title);
        window.draw(playingField);
        window.draw(infoField);
        window.draw(score);
        window.draw(snake);
        window.draw(apple);
        window.display();
    }
}

void Engine::setTitle()
{
    title.setFont(font);
    title.setString("SNAKE");
    title.setCharacterSize(75);
    title.setPosition(Game::WIDTH/2 - title.getGlobalBounds().width/2, 10);
    title.setColor(Color::Green);
    title.setStyle(Text::Bold);
}

void Engine::setPlayingField()
{
    playingField.setSize(Vector2f(560, 476));
    playingField.setFillColor(Color::White);
    playingField.setPosition(10, title.getGlobalBounds().height + 46 + 15);
}
void Engine::setInfoField()
{
    infoField.setSize(Vector2f(210, playingField.getGlobalBounds().height));
    infoField.setFillColor(Color::White);
    infoField.setPosition(playingField.getPosition().x + playingField.getGlobalBounds().width + 10, title.getGlobalBounds().height + 46 + 15);
}

void Engine::setScore()
{
    score.setFont(font);
    score.setColor(Color::Black);
    score.setCharacterSize(40);
//    score.setPosition(Vector2f(infoField.getPosition().x + infoField.getGlobalBounds().width/4, 100));
    iScore = 0;
}

void Engine::updateScore()
{
    ssScore.str("");
    ssScore << iScore;
    score.setString("Score: " + ssScore.str());
    score.setPosition(Vector2f(infoField.getPosition().x + infoField.getGlobalBounds().width/2 -
                               score.getGlobalBounds().width/2, 115));
}

bool Engine::checkCollisions()
{
    //check collisions beetwen snake's body
    for (int i = 0; i < snake.getLength(); i++)
    {
        if (snake.getHeadPosition() == snake.getBodyPosition(i))
            return false;
    }

    //check collisions beetwen snake and walls
    if (snake.getHeadPosition().x < 10 ||
        snake.getHeadPosition().x > 560 ||
        snake.getHeadPosition().y < 110 ||
        snake.getHeadPosition().y > 572){
        return false;
    }

    return true;

}

bool Engine::snakeAteApple()
{
    if (snake.getHeadPosition() == apple.getPosition())
    {
        snake.makeLonger(1);
        setApplePosition();
        iScore++;
        snake.increaseSpeed();
        return true;
    }
    return false;
}

bool Engine::showContinue(RenderWindow &window)
{
    bool pause = true;
    int currentOption = 0;

    RectangleShape pauseField(Vector2f(500, 200));
    pauseField.setPosition(Vector2f(Game::WIDTH/2 - pauseField.getGlobalBounds().width/2, Game::HEIGHT/2 - pauseField.getGlobalBounds().height/2));
    pauseField.setFillColor(Color::Black);

    Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("Continue?");
    pauseText.setCharacterSize(100);
    pauseText.setPosition(Vector2f(Game::WIDTH/2 - pauseText.getGlobalBounds().width/2, pauseField.getPosition().y - 10));
    pauseText.setColor(Color::Yellow);

    Text yes("Yes", font, 50);
    yes.setColor(Color::Yellow);

    Text no("No", font, 50);
    no.setColor(Color::Yellow);

    yes.setPosition(Game::WIDTH/2 - yes.getGlobalBounds().width/2 - 60,
                    pauseText.getPosition().y + pauseText.getGlobalBounds().height + 50);
    no.setPosition(Game::WIDTH/2 + no.getGlobalBounds().width/2 + 20,
                   yes.getPosition().y);

    while(pause)
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape){
                    pause = false;
                }
                if (event.key.code == Keyboard::Left)
                {
                    if (currentOption > 0){
                        currentOption--;
                    }
                }
                if (event.key.code == Keyboard::Right)
                {
                    if (currentOption < 1){
                        currentOption++;
                    }
                }
                if (event.key.code == Keyboard::Return)
                {
                    switch (currentOption)
                    {
                        case 0: pause = false; break;
                        case 1: return false; break;
                    }
                }
            }
        }

        if (currentOption == 0)
        {
            yes.setStyle(Text::Underlined); no.setStyle(Text::Regular);
        } else {
            no.setStyle(Text::Underlined); yes.setStyle(Text::Regular);
        }

        window.draw(pauseField);
        window.draw(pauseText);
        window.draw(yes);
        window.draw(no);
        window.display();
    }

    return true;
}

bool Engine::showGameOver(RenderWindow &window)
{
    bool pause = true;
    int currentOption = 0;

    RectangleShape pauseField(Vector2f(500, 250));
    pauseField.setPosition(Vector2f(Game::WIDTH/2 - pauseField.getGlobalBounds().width/2, Game::HEIGHT/2 - pauseField.getGlobalBounds().height/2));
    pauseField.setFillColor(Color::Black);

    Text pauseText;
    pauseText.setFont(font);
    pauseText.setString("GAME OVER");
    pauseText.setCharacterSize(100);
    pauseText.setPosition(Vector2f(Game::WIDTH/2 - pauseText.getGlobalBounds().width/2, pauseField.getPosition().y - 10));
    pauseText.setColor(Color::Red);
    pauseText.setStyle(Text::Bold);

    Text replay("Replay?", font, 60);
    replay.setColor(Color::Yellow);
    replay.setPosition(Game::WIDTH/2 - replay.getGlobalBounds().width/2, pauseText.getPosition().y + 120);

    Text yes("Yes", font, 50);
    yes.setColor(Color::Yellow);

    Text no("No", font, 50);
    no.setColor(Color::Yellow);

    yes.setPosition(Game::WIDTH/2 - yes.getGlobalBounds().width/2 - 60,
                    replay.getPosition().y + yes.getGlobalBounds().height + 35);
    no.setPosition(Game::WIDTH/2 + no.getGlobalBounds().width/2 + 20,
                   yes.getPosition().y);

    while(pause)
    {
        while (window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape){
                    pause = false;
                }
                if (event.key.code == Keyboard::Left)
                {
                    if (currentOption > 0){
                        currentOption--;
                    }
                }
                if (event.key.code == Keyboard::Right)
                {
                    if (currentOption < 1){
                        currentOption++;
                    }
                }
                if (event.key.code == Keyboard::Return)
                {
                    switch (currentOption)
                    {
                        case 0: pause = false; break;
                        case 1: return false; break;
                    }
                }
            }
        }

        if (currentOption == 0)
        {
            yes.setStyle(Text::Underlined); no.setStyle(Text::Regular);
        } else {
            no.setStyle(Text::Underlined); yes.setStyle(Text::Regular);
        }

        window.draw(pauseField);
        window.draw(pauseText);
        window.draw(replay);
        window.draw(yes);
        window.draw(no);
        window.display();
    }

    return true;
}

void Engine::setApplePosition()
{
    bool repeat;

    do
    {
        repeat = false;
        int x = rand() % 20;
        int y = rand() % 17;
        apple.position.x = 10 + x*apple.getSize();
        apple.position.y = 113 + y*apple.getSize();

        if (snake.getHeadPosition() == apple.position)
            repeat = true;
        else
        {
            for (int i = 0; i < snake.getLength(); i++)
            {
                if (snake.getBodyPosition(i) == apple.position)
                    repeat = true;
            }
        }

    } while(repeat);

    apple.apple.setPosition(apple.position);
}
