#include "Apple.h"
#include "Engine.h"

using namespace std;
using namespace sf;

Apple::Apple()
{
    //ctor
}

Apple::~Apple()
{
    //dtor
}

void Apple::create()
{
    size = 30;

    if (!texture.loadFromFile("data/images/apple2.png"))
    {
        MessageBox(NULL,"Texture not found!","ERROR",NULL);
		return;
    }
    apple.setTexture(texture);
}

Vector2f Apple::getPosition() const
{
    return position;
}

int Apple::getSize() const
{
    return size;
}
