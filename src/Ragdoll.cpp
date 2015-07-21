#include "Ragdoll.h"
#include "Head.h"
#include "Arm.h"
#include "Forearm.h"
#include "Body.h"
#include "includes.h"
#include <math.h>

Ragdoll::Ragdoll(b2World* theWorld, RenderWindow *theWindow)
{
    world = theWorld;
    window = theWindow;

    initJointDeff();
    createHeadAndBody();
    createArms();
}

void Ragdoll::createHeadAndBody()
{
    parts[HEAD] = new Head(world, window, 20.0f, 10.0f);
    parts[BODY] = new Body(world, window, 10.0f, 20.0f);

    createJoint(HEAD, BODY, b2Vec2(1.0f, 5.0f), b2Vec2(1.0f, -8.0f));
    createJoint(HEAD, BODY, b2Vec2(-1.0f, 5.0f), b2Vec2(-1.0f, -8.0f));
}

void Ragdoll::createArms()
{
    parts[LEFT_ARM] = new Arm(world, window, 10.0f, 23.0f);
    parts[LEFT_FOREARM] = new Forearm(world, window, 10.0f, 28.0f);
    createJoint(BODY, LEFT_ARM, b2Vec2(-8.0f, -7.0f), b2Vec2(0.0f, -4.0f));
    createJoint(LEFT_ARM, LEFT_FOREARM, b2Vec2(0.0f, 4.0f), b2Vec2(0.0f, -4.0f));

    parts[RIGHT_ARM] = new Arm(world, window, 20.0f, 23.0f);
    parts[RIGHT_FOREARM] = new Forearm(world, window, 20.0f, 28.0f);
    createJoint(BODY, RIGHT_ARM, b2Vec2(8.0f, -7.0f), b2Vec2(0.0f, -4.0f));
    createJoint(RIGHT_ARM, RIGHT_FOREARM, b2Vec2(0.0f, 4.0f), b2Vec2(0.0f, -4.0f));
}

void Ragdoll::createJoint(int partA, int partB, b2Vec2 anchorA, b2Vec2 anchorB)
{
    jointDeff->bodyA = parts[partA]->body;
    jointDeff->bodyB = parts[partB]->body;
    jointDeff->localAnchorA = anchorA;
    jointDeff->localAnchorB = anchorB;

    world->CreateJoint(jointDeff);
}

void Ragdoll::initJointDeff()
{
    jointDeff = new b2DistanceJointDef();
    jointDeff->length = 0.0f;
    jointDeff->frequencyHz = 30.0f;
    jointDeff->dampingRatio = 1.0f;
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
    for(int it = 0; it < numberOfParts ; ++it)
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
