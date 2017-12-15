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

void GO_Manager::moveForward()
{
    if(!player->isMoving())
    {
        float x = player->getPos().x + player->getDir().x*40;
        float y = player->getPos().y + player->getDir().y*40;
        Vector2f v(x,y);

        GObject * coll = findGOWithPos(v);
        float distance = dist(coll->getPos(),v);

        if(distance >= 30)
        {
            player->moveForward();
        }
        else
        {
            if(coll->isMovable())
            {

                coll->setDir(player->getDir().x, player->getDir().y);
                float x1 = coll->getPos().x + coll->getDir().x*40;
                float y1 = coll->getPos().y + coll->getDir().y*40;
                Vector2f v1(x1,y1);
                GObject * colcol = findGOWithPos(v1);
                float distan = dist(colcol->getPos(),v1);
                if(distan >= 30)
                {
                    coll->setPos(v1.x, v1.y);
                    player->moveForward(); 
                }
            }
        }
    }
    else
    {
        player->moveForward();
    }

}


GObject * GO_Manager::findGOWithPos(Vector2f v)
{
    float distance = std::numeric_limits<float>::max();
    GObject * nearest;
    for(int i = 0; i<objects_scene.size();i++)
    {
        if(objects_scene[i].isCollider())
        {
            if(dist(objects_scene[i].getPos(),v) < distance)
            {
                distance = dist(objects_scene[i].getPos(),v);
                nearest = &objects_scene[i];
            }
        }
    }
    return nearest;
}

float GO_Manager::dist(Vector2f a, Vector2f b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}