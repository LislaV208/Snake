#ifndef APPLE_H
#define APPLE_H
#include <SFML/Graphics.hpp>
#include "Snake.h"

using namespace sf;

class Apple : public Drawable
{
    public:
        Apple();
        ~Apple();
        friend class Engine;

        void create();
        Vector2f getPosition() const;
        int getSize() const;

    protected:
    private:
        RectangleShape apple;
        int size;
        Vector2f position;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            target.draw(apple);
        }
};

#endif // APPLE_H
