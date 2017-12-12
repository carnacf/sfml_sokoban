#include "go_manager.h"


void GO_Manager::addGameObject(GObject g)
{
    objects_scene.push_back(g);
}

void GO_Manager::removeGameObject(int i)
{
    objects_scene.erase (objects_scene.begin()+i);
}

bool GO_Manager::testCollide(GObject g, GObject o)
{
    return g.getSprite().getGlobalBounds().intersects(o.getSprite().getGlobalBounds());
}

std::vector<GObject> GO_Manager::checkCollide(GObject g)
{
    std::vector<GObject> colliders;
    for(GObject o : objects_scene)
    {
        if(o.isCollider() && &g != &o)
        {
            if(testCollide(g,o))
            {
                colliders.push_back(o);
            }
        }
    }
    return colliders;

}

void GO_Manager::drawAll(RenderWindow * window)
{
    for(GObject o : objects_scene)
    {
        window->draw(o.getSprite());
    }
    window->draw(player->getSprite());
}
