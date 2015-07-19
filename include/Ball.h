#ifndef BALL_H
#define BALL_H
#include "includes.h"

class Ball
{
    public:
        Ball(b2World* world, RenderWindow *window, float x, float y);
        virtual ~Ball();
        void updatePosition();
        void draw();
        void applyForce(float x, float y);
        b2Body *body;
    protected:
    private:
        Sprite *sprite;
        Texture *texture;
        RenderWindow *wnd;
        b2Vec2 auxPosition;
        void defineSize();
        void defineBody(b2World* world, float x, float y);
};

#endif // BALL_H
