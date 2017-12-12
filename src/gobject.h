#ifndef GOBJECT
#define GOBJECT

#include <SFML/Graphics.hpp>

using namespace sf;

class GObject
{
private:
    int animIndex;
    float speed;
    bool moving;

    Vector2f pos;
    Vector2f dir;
    std::vector<Sprite> anim;
    Sprite current;
    bool collider;

public:
    GObject(float x, float y,float speed, bool collider);
    GObject(std::vector<Sprite> anim, float x, float y,float speed, bool collider);
    GObject(std::vector<Sprite> anim, float x, float y,float dirX,float dirY,float speed, bool collider);

    ~GObject(){}

    Sprite getSprite(){return current;}
    bool isMoving(){return moving;}
    void setPos(float x, float y);
    void setDir(float x, float y);
    int numberOfSprites(){return anim.size();}
    bool isCollider(){return collider;}

    void moveForward();
    void setSpriteNext();
    virtual void event(Event * e) {}

};
#endif
