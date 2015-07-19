#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World* world, RenderWindow *window)
{
    b2DistanceJointDef* jointDeff = new b2DistanceJointDef();
    jointDeff->length = 10.0f;
    for(int it = 0; it < numberOfParts; ++it)
    {
        parts[it] = new Ball(world, window, 10.0f + 10.0f * it, 10.0f);
        if(it > 0)
        {
            jointDeff->bodyA = parts[it]->body;
            jointDeff->bodyB = parts[it - 1]->body;
            joints[it] = world->CreateJoint(jointDeff);
        }
    }

    jointDeff->bodyA = parts[numberOfParts - 1]->body;
    jointDeff->bodyB = parts[0]->body;
    joints[numberOfParts - 1] = world->CreateJoint(jointDeff);
}

Ragdoll::~Ragdoll()
{
    for(int it = 0; it < numberOfParts; ++it)
    {
        delete parts[it];
    }
}

void Ragdoll::draw()
{
    for(int it = 0; it < numberOfParts; ++it)
    {
        parts[it]->draw();
    }
}

void Ragdoll::updatePosition()
{
    for(int it = 0; it < numberOfParts; ++it)
    {
        parts[it]->updatePosition();
    }
}

void Ragdoll::applyForce(float x, float y)
{
    parts[0]->applyForce(x, y);
}
