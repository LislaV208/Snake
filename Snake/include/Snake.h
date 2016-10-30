#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;
using namespace sf;

class Snake : public Drawable
{
    public:
        Snake();
        ~Snake();

        friend class Engine;

        enum Direction{
            UP,
            LEFT,
            DOWN,
            RIGHT
        };

        void create();
        void move(Direction);
        void setDirection(Direction);
        Direction getDirection() const;
        void setPreviousDirection();
        Direction getPrevious() const;
        int getSpeed() const;
        int getLength() const;
        Vector2f getHeadPosition() const;
        Vector2f getBodyPosition(int) const;
        void makeLonger(int);
        void increaseSpeed();
        void decreaseSpeed();

    protected:
    private:
        Texture tHead, tBody, tTail;
        RectangleShape head;
        RectangleShape bodyShape;
        vector <RectangleShape> body;
        int length;
        float speed;
        int size;
        Direction direction;
        Vector2f positionHead;
        Direction previous;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(head);
            for (int i = 0; i < length; i++)
                target.draw(body[i]);
        }

};

#endif // SNAKE_H
