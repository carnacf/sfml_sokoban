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
    bool movable;

public:
    GObject();
    GObject(float x, float y,float speed, bool collider);
    GObject(std::vector<Sprite> anim, float x, float y,float speed, bool collider);
    GObject(std::vector<Sprite> anim, float x, float y,float dirX,float dirY,float speed, bool collider);

    ~GObject(){}

    Sprite getSprite(){return current;}
    void setSprite(Sprite s){current = s;}
    bool isMoving(){return moving;}
    void setMoving(bool t){moving = t;}
    void setPos(float x, float y);
    void setDir(float x, float y);
    Vector2f getPos(){return pos;}
    Vector2f getDir(){return dir;}
    int getIndex(){return animIndex;}
    std::vector<Sprite> getAnim(){return anim;}

    bool isMovable(){return movable;}
    void setMovable(bool t){movable = t;}

    void moveForward();

    int numberOfSprites(){return anim.size();}
    bool isCollider(){return collider;}

    void setSpriteNext();
    virtual void event(Event * e) {}

    operator bool() const
    {
        return anim.empty();
    }


};
#endif
