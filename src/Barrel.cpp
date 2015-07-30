#include "Barrel.h"
#include <math.h>
using namespace std;

Barrel::Barrel(b2World* theWorld, RenderWindow *window, float x, float y)
{
    wnd = window;
    texture = new Texture();
    texture->loadFromFile("img/barrel.png");
    sprite = new Sprite(*texture);
    world = theWorld;
    createBody();
    defineSize();
}

Barrel::~Barrel()
{
    delete texture;
}

void Barrel::createBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(40.0f, 920.0f);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape* box= new b2PolygonShape();

    box->SetAsBox(30.0f, 60.0f,b2Vec2(0.0f,0.0f),0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = box;

    body->CreateFixture(&fixtureDef);

//	body->SetTransform(b2Vec2(500.0f,0.0f),0.0f);
}

void Barrel::defineSize()
{
	b2AABB aabb;
	aabb.lowerBound = b2Vec2(FLT_MAX, FLT_MAX);
	aabb.upperBound = b2Vec2(-FLT_MAX, -FLT_MAX);

	for (b2Fixture* f = body->GetFixtureList(); f; f = f->GetNext())
	{
		aabb.Combine(f->GetAABB(0));
	}

	float sizeX = aabb.GetExtents().x*2.0f / sprite->getTexture()->getSize().x;
	float sizeY = aabb.GetExtents().y*2.0f / sprite->getTexture()->getSize().y;
	float originX = sprite->getTexture()->getSize().x / 2.0f;
	float originY = sprite->getTexture()->getSize().y / 2.0f;

	sprite->setScale(sf::Vector2f(sizeX, sizeY));
	sprite->setOrigin(Vector2f(originX, originY));
	sprite->setPosition(body->GetPosition().x, body->GetPosition().y);
}

void Barrel::draw()
{
    wnd->draw(*sprite);
}

void Barrel::updatePosition(Vector2i mousePosition)
{
    sprite->setPosition(body->GetPosition().x, body->GetPosition().y);
    Vector2f direction = sprite->getPosition() - (Vector2f) mousePosition;
    float32 angle = atan2(direction.y,  direction.x) - M_PI/2;

    body->SetTransform(body->GetWorldCenter(), angle);
    sprite->setRotation(angle * 180 / M_PI);
}

float32 Barrel::getAngle()
{
    return body->GetAngle();
}
