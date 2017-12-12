#include "src/player.h"
#include <iostream>

using namespace sf;


int main()
{

	RenderWindow window(VideoMode(320, 480), "The Game!");
	window.setFramerateLimit(60);
    Texture player_text;

	player_text.loadFromFile("images/player.png");
	std::vector<Sprite> player_anim;
	for(int i = 0;i<6;i++){
		player_anim.push_back(Sprite(player_text,IntRect(i*40,0,40,40)));
	}

	Player player(player_anim,50,50,40);

    while (window.isOpen())
    {
		window.clear();
		Event e;
		if(player.isMoving()){
			player.moveForward();
		}
		while (window.pollEvent(e))
		{
			if(!player.isMoving()){
				player.event(&e);
			}
			if (e.type == Event::Closed)
				window.close();
		}
		window.draw(player.getSprite());

		window.display();
	}

    return 0;
}
