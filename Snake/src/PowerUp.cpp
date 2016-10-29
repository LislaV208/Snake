#include "PowerUp.h"

PowerUp::PowerUp()
{
    //ctor
}

PowerUp::~PowerUp()
{
    //dtor
}

void PowerUp::create()
{
    tPowerUp.loadFromFile("data/images/powerup.png");
    powerUp.setTexture(tPowerUp);
    powerUp.setPosition(-30, 0);
}

void PowerUp::setNewPosition(Vector2f p)
{
    powerUp.setPosition(p);
}

Vector2f PowerUp::getPosition() const
{
    return powerUp.getPosition();
}
