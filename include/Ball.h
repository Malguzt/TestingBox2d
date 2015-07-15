#ifndef BALL_H
#define BALL_H
#include "includes.h"

class Ball
{
    public:
        Ball(b2World* world, RenderWindow *window);
        virtual ~Ball();
        void updatePosition();
        void draw();
    protected:
    private:
        Sprite *sprite;
        Texture *texture;
        RenderWindow *wnd;
        b2Body *body;
        b2Vec2 auxPosition;
        void defineSize();
        void defineBody(b2World* world);
};

#endif // BALL_H
