#include "gobject.h"
#include "go_manager.h"

GObject::GObject():anim()
{

}

GObject::GObject(float x, float y,float speed, bool collider,bool movable,bool goal):
animIndex(0),
speed(speed),
moving(false),
pos(x,y),
dir(0,0),
anim(),
current(),
collider(collider),
movable(movable),
victory(goal)
{

}

GObject::GObject(std::vector<Sprite> anim, float x, float y,float speed, bool collider,bool movable, bool goal):
animIndex(0),
speed(speed),
moving(false),
pos(x,y),
dir(0,0),
anim(anim),
collider(collider),
movable(movable),
victory(goal)
{
    current = anim[animIndex];
    current.setPosition(x,y);
    current.setOrigin( current.getTextureRect().width / 2, current.getTextureRect().height / 2 );
}

GObject::GObject(std::vector<Sprite> anim, float x, float y, float xDir, float yDir,float speed, bool collider,bool movable, bool goal):
animIndex(0),
speed(speed),
moving(false),
pos(x,y),
dir(xDir,yDir),
anim(anim),
collider(collider),
movable(movable),
victory(goal)
{
    current = anim[animIndex];
    current.setPosition(x,y);
    current.setOrigin( current.getTextureRect().width / 2, current.getTextureRect().height / 2 );
}

void GObject::setPos(float x, float y)
{
    pos.x = x;
    pos.y = y;
    current.setPosition(x,y);
}

void GObject::setDir(float x, float y)
{
    dir.x = x;
    dir.y = y;
    if(!(x==0&&y==0))
    {
        current.setOrigin( current.getTextureRect().width / 2, current.getTextureRect().height / 2 );
        float angle = dir.x*90;
        if(dir.y == 1){
            angle+=180;
        }
        current.setRotation(angle);
    }
}

void GObject::moveForward()
{
   
    if(animIndex == 0){
        moving = true;
    }else if(animIndex == (int)anim.size()-1){
        moving = false;
    }

    pos = pos + (dir*((float)current.getTextureRect().width)/(float)anim.size());
    setSpriteNext();
    //Rotate
    float angle = dir.x*90;
    if(dir.y == 1){
        angle+=180;
    }
    current.setRotation(angle);

}

void GObject::setSpriteNext()
{
    animIndex = (animIndex+1)%anim.size();
    current = anim[animIndex];
    current.setPosition(pos.x,pos.y);
    current.setOrigin( current.getTextureRect().width / 2, current.getTextureRect().height / 2 );
}
