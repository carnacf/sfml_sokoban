#include "go_manager.h"


void GO_Manager::addGameObject(GObject g)
{
    if(g.isMovable())
    {
        movable.push_back(g);
    }
    else if(g.isVictory())
    {
        goals.push_back(g);
    }
    else
    {
        objects_scene.push_back(g);
    }

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


std::vector<GObject> GO_Manager::checkCollideVictory(GObject g)
{
    std::vector<GObject> colliders;
    for(GObject o : goals)
    {
        if(testCollide(g,o))
        {
            colliders.push_back(o);
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
    for(GObject o : goals)
    {
        window->draw(o.getSprite());
    }
    for(GObject o : movable)
    {
        window->draw(o.getSprite());
    }
    window->draw(player->getSprite());
}

bool GO_Manager::moveForward()
{
    bool t = false;
    if(!player->isMoving())
    {
        float x = player->getPos().x + player->getDir().x*player->getSprite().getTextureRect().width;
        float y = player->getPos().y + player->getDir().y*player->getSprite().getTextureRect().width;
        Vector2f v(x,y);

        GObject * coll = findGOWithPos(v);
        float distance = dist(coll->getPos(),v);

        if(distance >= player->getSprite().getTextureRect().width-10)
        {
            player->moveForward();
            t = true;
        }
        else
        {
            if(coll->isMovable())
            {

                coll->setDir(player->getDir().x, player->getDir().y);
                float x1 = coll->getPos().x + coll->getDir().x*player->getSprite().getTextureRect().width;
                float y1 = coll->getPos().y + coll->getDir().y*player->getSprite().getTextureRect().width;
                Vector2f v1(x1,y1);
                GObject * colcol = findGOWithPos(v1);
                float distan = dist(colcol->getPos(),v1);
                if(distan >= player->getSprite().getTextureRect().width-10)
                {
                    coll->setPos(v1.x, v1.y);
                    player->moveForward();
                    t = true;
                }
            }
        }
    }
    else
    {
        player->moveForward();
        t = true;
    }
    return t;

}


GObject * GO_Manager::findGOWithPos(Vector2f v)
{
    float distance = std::numeric_limits<float>::max();
    GObject * nearest = nullptr;
    for(size_t i = 0; i<objects_scene.size();i++)
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
    for(size_t i = 0; i<movable.size();i++)
    {
        if(movable[i].isCollider())
        {
            if(dist(movable[i].getPos(),v) < distance)
            {
                distance = dist(movable[i].getPos(),v);
                nearest = &movable[i];
            }
        }
    }
    return nearest;
}

float GO_Manager::dist(Vector2f a, Vector2f b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

void GO_Manager::clearAll()
{
    objects_scene.clear();
    movable.clear();
    goals.clear();
    while(!histo_movable.empty())
        histo_movable.pop();
    while(!histo_player.empty())
        histo_player.pop();
    
}


void GO_Manager::victoryUpdate()
{
    for(size_t i = 0; i<movable.size();i++)
    {
        std::vector<GObject> v = checkCollideVictory(movable[i]);
        if(!v.empty() && movable[i].getIndex() != 1)
        {
            movable[i].setSpriteNext();
        }else if(v.empty() && movable[i].getIndex() == 1)
        {
            movable[i].setSpriteNext();
        }
    }
}

bool GO_Manager::victoryGlobal()
{
    bool victoire = true;
    for(size_t i = 0; i<movable.size();i++)
    { 
        if(movable[i].getIndex() == 0)
        {
            victoire = false;
            break;
        }
    } 
    return victoire;
}

void GO_Manager::empiler()
{
    histo_player.push(player->getPos());
    histo_movable.push(movable);
}

void GO_Manager::depiler()
{

    if(!histo_player.empty())
    {
        player->setPos(histo_player.top().x, histo_player.top().y);
        histo_player.pop();
    }
    if(!histo_movable.empty())
    {
        movable = histo_movable.top();
        histo_movable.pop();
    }

}
