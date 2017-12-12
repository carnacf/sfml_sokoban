#include <time.h>
#include "src/player.h"

using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(320, 480), "Best Sokoban Ever !");
	window.setFramerateLimit(60);

    Texture player_text;
	player_text.loadFromFile("images/player.png");

	std::vector<Sprite> player_anim;
	for(int i = 0;i<6;i++){
		player_anim.push_back(Sprite(player_text,IntRect(i*40,0,40,40)));
	}

	Player player(player_anim,50,50,40);

	Clock clock;
	float timer = 0;
	float animTime = 0.5;

    while (window.isOpen())
    {
		//Time
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;

		Event e;
		if(player.isMoving() && timer>(animTime/player.numberOfSprites())){
			player.moveForward();
			timer = 0;
		}
		while (window.pollEvent(e))
		{
			if(!player.isMoving()){
				player.event(&e);
			}
			if (e.type == Event::Closed)
				window.close();
		}

		//Drawing part
		window.clear();
		window.draw(player.getSprite());

		window.display();
	}

    return 0;
}
