#include "Game.h"
#include "Engine.h"

using namespace sf;


RenderWindow window(VideoMode(Game::WIDTH, Game::HEIGHT), "Snake");

Game::Game()
{
    state = END;
    if (!font.loadFromFile("data/Mecha.ttf"))
    {
        MessageBox(NULL,"Font not found!","ERROR",NULL);
		return;
    }
    state = MENU;
}

Game::~Game()
{
    //dtor
}

void Game::run()
{
    while (state != END)
    {
        switch (state)
        {
        case GameState::MENU:
            menu();
            break;
        case GameState::GAME:
            play();
            break;
        case GameState::GAMEOVER:
            break;
        }
    }
}

void Game::menu()
{
    VideoMode desktop = VideoMode::getDesktopMode();
    Vector2u windowSize = window.getSize();
    window.setPosition(Vector2i(desktop.width/2 - windowSize.x/2, 10));

    Text title;
    title.setFont(font);
    title.setString("SNAKE");
    title.setCharacterSize(200);
    title.setPosition(WIDTH/2 - title.getGlobalBounds().width/2, 20);
    title.setColor(Color::Green);
    title.setStyle(Text::Bold);

    const int optionsAmount = 2;
    Text options[optionsAmount];
    string str[optionsAmount] = {"Play", "Exit"};

    int currentOption = 0;

    for (int i = 0; i < optionsAmount; i++)
    {
        options[i].setFont(font);
        options[i].setString(str[i]);
        options[i].setCharacterSize(72);
        options[i].setPosition(WIDTH/2 - options[i].getGlobalBounds().width/2, 350 + i*100);
    }

    while (state == MENU)
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == Event::Closed)
                state = END;
            if (event.type == Event::KeyPressed)
            {
                if (event.key.code == Keyboard::Escape)
                    state = END;
                if (event.key.code == Keyboard::Up)
                {
                    if (currentOption > 0){
                        currentOption--;
                    }
                }
                if (event.key.code == Keyboard::Down)
                {
                    if (currentOption < optionsAmount - 1){
                        currentOption++;
                    }
                }
                if (event.key.code == Keyboard::Return)
                {
                    switch (currentOption)
                    {
                        case 0: state = GAME; break;
                        case 1: state = END; break;
                    }
                }
            }
        }



        window.clear();

        window.draw(title);
        for (int i = 0; i < optionsAmount; i++)
        {
            if (i == currentOption){
                options[i].setColor(Color::Cyan);
            }
            else {
                options[i].setColor(Color::White);
            }
            window.draw(options[i]);
        }
        window.display();
    }
}

void Game::play()
{
    Engine engine;
    engine.run(window);

    state = MENU;
}
