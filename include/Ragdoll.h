#ifndef RAGDOLL_H
#define RAGDOLL_H
#include "Ball.h"
#define NUM_OF_PARTS 5


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
        int numberOfParts = NUM_OF_PARTS;
        Ball* parts[NUM_OF_PARTS];
        b2Joint* joints[NUM_OF_PARTS];
};

#endif // RAGDOLL_H
