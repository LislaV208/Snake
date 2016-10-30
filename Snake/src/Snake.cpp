#include "Snake.h"
#include <SFML/Graphics.hpp>

using namespace sf;


void Snake::create()
{
    length = 2;
    speed = 7;
    size = 28;
    direction = RIGHT;

    positionHead.x = 10;
    positionHead.y = rand() % 17 * size + 113;
    head.setSize(Vector2f(size, size));
    head.setPosition(positionHead);
    head.setFillColor(Color(40,114,51));

    for (int i = 0; i < length; i++)
    {
        body.push_back(bodyShape);
        body[i].setSize(Vector2f(size, size));
        body[i].setPosition(head.getPosition().x - head.getGlobalBounds().height * (i+1), head.getPosition().y);
        body[i].setFillColor(Color::Green);
    }
}

void Snake::move(Direction direction)
{
    Vector2f lastHeadPosition(head.getPosition());
    Vector2f lastBodyPosition[length];
    for (int i = 0; i < length; i++)
    {
        lastBodyPosition[i].x = body[i].getPosition().x;
        lastBodyPosition[i].y = body[i].getPosition().y;
    }

    switch(direction)
    {
        case UP:
            head.setPosition(head.getPosition().x, head.getPosition().y - size);
            break;
        case DOWN:
            head.setPosition(head.getPosition().x, head.getPosition().y + size);
            break;
        case LEFT:
            head.setPosition(head.getPosition().x - size, head.getPosition().y);
            break;
        case RIGHT:
            head.setPosition(head.getPosition().x + size, head.getPosition().y);
            break;
    }

    for (int i = 0; i < length; i++)
    {
        if (i == 0)
            body[i].setPosition(lastHeadPosition);
        else
            body[i].setPosition(lastBodyPosition[i-1]);
    }
}

Snake::Direction Snake::getDirection() const
{
    return direction;
}

void Snake::setDirection(Direction dir)
{
    switch (dir)
    {
        case Direction::UP: direction = UP; break;
        case Direction::LEFT: direction = LEFT; break;
        case Direction::DOWN: direction = DOWN; break;
        case Direction::RIGHT: direction = RIGHT; break;
        default: break;
    }
}

int Snake::getSpeed() const
{
    return speed;
}

int Snake::getLength() const
{
    return length;
}

Vector2f Snake::getHeadPosition() const
{
    return head.getPosition();
}

Vector2f Snake::getBodyPosition(int pos) const
{
    for (int i = 0; i < length; i++)
    {
        if (i == pos)
            return body[i].getPosition();
    }
}

void Snake::setPreviousDirection()
{
    previous = getDirection();
}

Snake::Direction Snake::getPrevious() const
{
    return previous;
}

void Snake::makeLonger(int how)
{
    for (int i = 0; i < how; i++)
    {
        length++;
        body.push_back(bodyShape);
        body[length-1].setSize(Vector2f(size, size));
        body[length-1].setFillColor(Color::Green);
        body[length-1].setPosition(body[length-2].getPosition());
    }

}

void Snake::increaseSpeed()
{
    speed += 0.05;
}

void Snake::decreaseSpeed()
{
    speed -= 0.05;
}
