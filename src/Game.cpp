#include "Game.h"

Game::Game()
{
    pWnd = new RenderWindow(VideoMode(1200, 768), "Testin box2d", Style::Fullscreen);
	pWnd->setVisible(true);
	fps = 60;
	pWnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;

    setZoom();
	initPhysics();

    theBall = new Ball(phyWorld, pWnd);
}

Game::~Game()
{
    delete theBall;
    delete phyWorld;
    delete pWnd;
}

void Game::Go()
{
    Event evt;

    while(pWnd->isOpen())
    {

        while (pWnd->pollEvent(evt))
        {
            processEvent(evt);
        }

        pWnd->clear();
        updateGame();
        drawGame();
        pWnd->display();
    }
}

void Game::processEvent(Event &evt)
{
    switch (evt.type)
    {
        case Event::Closed:
            pWnd->close();
            break;
        case Event::KeyPressed:
            processKey(evt.key.code);
            break;
        case Event::MouseButtonPressed:
            //board.checkClick(Vector2i(evt.mouseButton.x, evt.mouseButton.y), *pWnd);
            break;
    }
}

void Game::processKey(int keyCode)
{
//    if(Keyboard::isKeyPressed(Keyboard::Right)) theRock.changeRadius(2);
//    if(Keyboard::isKeyPressed(Keyboard::Left)) theRock.changeRadius(-2);
//    if(Keyboard::isKeyPressed(Keyboard::Up)) theRock.changeSpeed(2);
//    if(Keyboard::isKeyPressed(Keyboard::Down)) theRock.changeSpeed(-2);

    switch(keyCode)
    {
        case Keyboard::Escape:
            pWnd->close();
            break;
    }
}

void Game::updateGame()
{
	phyWorld->Step(frameTime,8,8);
	phyWorld->ClearForces();
	theBall->updatePosition();
}

void Game::drawGame()
{
    theBall->draw();
}

void Game::initPhysics(){
	//Set the gravity
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));

	//Create floor and walls

	b2Body* groundBody = Game::CreateRectangularStaticBody(phyWorld,100,10);
	groundBody->SetTransform(b2Vec2(50.0f,100.0f),0.0f);

	b2Body* leftWallBody = Game::CreateRectangularStaticBody(phyWorld,10,100);
	leftWallBody->SetTransform(b2Vec2(0.0f,50.0f),0.0f);

	b2Body* rightWallBody = Game::CreateRectangularStaticBody(phyWorld,10,100);
	rightWallBody->SetTransform(b2Vec2(100.0f,50.0f),0.0f);

	//Create the ceiling
	b2Body* topWallBody = Game::CreateRectangularStaticBody(phyWorld,100,10);
	topWallBody->SetTransform(b2Vec2(50.0f,0.0f),0.0f);
}

b2Body* Game::CreateRectangularStaticBody(b2World *phyWorld, float sizeX, float sizeY){
    b2Body* body = CreateStaticBody(phyWorld);
    b2FixtureDef box = CreateRectangularFixtureDef(sizeX,sizeY,0.0f,0.0f,0.0f);
    body->CreateFixture(&box);

    return body;
}

b2Body* Game::CreateStaticBody(b2World *phyWorld){
    b2Body * body;

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(0.0f, 0.0f);
    body = phyWorld->CreateBody(&bodyDef);
    return body;
}

b2FixtureDef Game::CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction,float restitution){

    b2PolygonShape* box= new b2PolygonShape();

    box->SetAsBox(sizeX/2.0f, sizeY/2.0f,b2Vec2(0.0f,0.0f),0.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = box;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution=restitution;

    return fixtureDef;
}

void Game::setZoom(){
	View camara;

	camara.setSize(100.0f, 100.0f);
	camara.setCenter(50.0f, 50.0f);
	pWnd->setView(camara);
}