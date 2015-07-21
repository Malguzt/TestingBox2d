#include "Arm.h"

Arm::Arm(b2World* world, RenderWindow *window, float x, float y): PartOfBody(world, window, x, y)
{
    texture->loadFromFile("img/arm.png");
    sprite = new Sprite(*texture);
    defineBody(x, y);
    defineSize();
}

Arm::~Arm()
{
    //dtor
}

void Arm::defineBody(float x, float y)
{
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(2.0f, 5.0f);

    createBody(dynamicBox, x, y);
}
