#ifndef RAGDOLL_H
#define RAGDOLL_H

#define NUM_OF_PARTS 4
#define HEAD 0
#define BODY 1
#define LEFT_ARM 2
#define RIGHT_ARM 3

#include "PartOfBody.h"

class Ragdoll
{
    public:
        Ragdoll(b2World* world, RenderWindow *window);
        virtual ~Ragdoll();
        void draw();
        void updatePosition();
        void applyForce(float x, float y);
    protected:
    private:
        b2World *world;
        RenderWindow *window;
        int numberOfParts = NUM_OF_PARTS;
        PartOfBody* parts[NUM_OF_PARTS];
        void createHead();
        void joinParts(b2Body *bodyA, b2Body *bodyB);
};

#endif // RAGDOLL_H
