#include "Ball.h"

Ball::Ball(b2World* world, RenderWindow *window)
{
    wnd = window;
    texture = new Texture();
    texture->loadFromFile("img/ball.png");

    defineBody(world);
    defineSize();
}

Ball::~Ball()
{
    //dtor
}

void Ball::defineBody(b2World* world)
{
    sprite = new Sprite(*texture);

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(10.0f, 10.0f);
    body = world->CreateBody(&bodyDef);

    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(10.0f, 10.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 0.3f;
    fixtureDef.restitution = 1.0f;
    body->CreateFixture(&fixtureDef);
}

void Ball::defineSize()
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

void Ball::updatePosition()
{
    b2Vec2 pos = body->GetPosition();
    sprite->setPosition(pos.x, pos.y);
}

void Ball::draw()
{
    wnd->draw(*sprite);
}
