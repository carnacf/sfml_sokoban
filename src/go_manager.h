#ifndef GO_MANAGER
#define GO_MANAGER

#include <SFML/Graphics.hpp>
#include "player.h"

using namespace sf;

class GO_Manager
{
private:

    std::vector<GObject> objects_scene;
    std::vector<GObject> movable;
    std::vector<GObject> goals;

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

    std::vector<GObject> checkCollideVictory(GObject g);

    void drawAll(RenderWindow * window);

    void moveForward();

    GObject * findGOWithPos(Vector2f v);

    float dist(Vector2f a, Vector2f b);

    void clearAll();

    void victoryUpdate();

    bool victoryGlobal();

};

#endif
