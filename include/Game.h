#ifndef GAME_H
#define GAME_H

#include "includes.h"
#include "Ragdoll.h"
#include "Barrel.h"
#include "../libs/SFMLRenderer.h"
#include <vector>

using namespace sf;
using namespace std;

class Game
{
    public:
        Game();
        virtual ~Game();
        void Go();
    private:
        float impulseValue = 1000000.0f;
        RenderWindow *pWnd;
        std::vector<Ragdoll*> ragdolls;
        Barrel *theBarrel;
        b2World *phyWorld;
        SFMLRenderer *debugRender;
        float frameTime;
        int fps;
        void setZoom();
        void initPhysics();
        void processEvent(Event &evt);
        void drawGame();
        void updateGame();
        void updatePhysics();
        void processKey(int keyCode);
        static b2Body* CreateRectangularStaticBody(b2World *phyWorld, float sizeX, float sizeY);
        static b2Body* CreateStaticBody(b2World *phyWorld);
        static b2FixtureDef CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction,float restitution);
};

#endif // GAME_H
