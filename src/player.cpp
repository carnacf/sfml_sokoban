#include "player.h"

void Player::event(Event * e)
{
    switch(e->type){
        case sf::Event::KeyPressed:
            keyPressed(e);
            break;
        case sf::Event::KeyReleased:
            keyReleased(e);
            break;
        default:
            break;
    }
}

void Player::keyPressed(Event * e)
{

    switch (e->key.code) {
        case sf::Keyboard::Left:
            setDir(-1,0);
            break;
        case sf::Keyboard::Right:
            setDir(1,0);
            break;
        case sf::Keyboard::Up:
            setDir(0,-1);
            break;
        case sf::Keyboard::Down:
            setDir(0,1);
            break;
        default:
            setDir(0,0);
            break;
    }
}
void Player::keyReleased(Event * e)
{

}
