#include "gobject.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class Player: public GObject
{
public:
    using GObject::GObject;
    ~Player(){}

    void event(Event * e) override;

private:
    void keyPressed(Event * e);
    void keyReleased(Event * e);

};
