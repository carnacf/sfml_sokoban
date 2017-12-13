#ifndef GO_MANAGER
#define GO_MANAGER

#include <SFML/Graphics.hpp>
#include "player.h"

using namespace sf;

class GO_Manager
{
private:

    std::vector<GObject> objects_scene;
    Player * player;

public:
    GO_Manager(Player * p){player = p;}

    void addGameObject(GObject g);

    void removeGameObject(int i);

    void setPlayer(Player * p){player = p;}

    Player * getPlayer(){return player;}

    std::vector<GObject> getObjects(){ return objects_scene;}

    bool testCollide(GObject g, GObject o);

    std::vector<GObject> checkCollide(GObject g);

    void drawAll(RenderWindow * window);

};

#endif