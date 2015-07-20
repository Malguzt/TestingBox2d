#include "Ragdoll.h"
#include "Head.h"
#include "Body.h"
#include "includes.h"

Ragdoll::Ragdoll(b2World* theWorld, RenderWindow *theWindow)
{
    world = theWorld;
    window = theWindow;

    createHead();
}

void Ragdoll::createHead()
{
    parts[HEAD] = new Head(world, window, 20.0f, 10.0f);
    parts[BODY] = new Body(world, window, 10.0f, 20.0f);
    joinParts(parts[HEAD]->body, parts[BODY]->body);
}

void Ragdoll::joinParts(b2Body *bodyA, b2Body *bodyB)
{
    float width = 1.0f;
    b2DistanceJointDef* jointDeff = new b2DistanceJointDef();
    jointDeff->length = 0.0f;
    jointDeff->frequencyHz = 30.0f;
    jointDeff->dampingRatio = 1.0f;
    jointDeff->bodyA = bodyA;
    jointDeff->bodyB = bodyB;

    jointDeff->localAnchorA = b2Vec2(width, 5.0f);
    jointDeff->localAnchorB = b2Vec2(width, -8.0f);
    world->CreateJoint(jointDeff);

    jointDeff->localAnchorA = b2Vec2(-width, 5.0f);
    jointDeff->localAnchorB = b2Vec2(-width, -8.0f);
    world->CreateJoint(jointDeff);
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
    parts[HEAD]->applyForce(x, y);
}
