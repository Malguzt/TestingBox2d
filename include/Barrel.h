#ifndef BARREL_H
#define BARREL_H
#include "includes.h"


class Barrel
{
    public:
        Barrel(b2World* theWorld, RenderWindow *window, float x, float y);
        virtual ~Barrel();
        void draw();
        void updatePosition(Vector2i mousePosition);
        float32 getAngle();
        b2Body* body;
    protected:
    private:
        void createBody();
        b2World *world;
        RenderWindow *wnd;
        Texture *texture;
        Sprite *sprite;
        void defineSize();
};

#endif // BARREL_H
