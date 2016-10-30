#include "Apple.h"
#include "Engine.h"

using namespace std;
using namespace sf;


void Apple::create()
{
    size = 28;
    apple.setSize(Vector2f(size, size));
    apple.setFillColor(Color::Red);
}

Vector2f Apple::getPosition() const
{
    return position;
}

int Apple::getSize() const
{
    return size;
}
