#ifndef POWERUP_H
#define POWERUP_H

#include <SFML/Graphics.hpp>
using namespace sf;

class PowerUp : public Drawable
{
    public:
        PowerUp();
        ~PowerUp();

        void create();
        void setNewPosition(Vector2f);
        Vector2f getPosition() const;
    protected:
    private:
        Texture tPowerUp;
        Sprite powerUp;

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
        {
            //rysowanie obiektow, które sk³adaj¹ siê na narysowanie naszej postaci
            target.draw(powerUp);
        }
};

#endif // POWERUP_H
