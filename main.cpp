#include <time.h>
#include "src/player.h"
#include "src/go_manager.h"

using namespace sf;

int main()
{
	srand(time(0));

	RenderWindow window(VideoMode(480, 480), "Best Sokoban Ever !");
	window.setFramerateLimit(60);

	//Player
    Texture player_text;
	player_text.loadFromFile("images/player.png");

	std::vector<Sprite> player_anim;
	for(int i = 0;i<6;i++){
		player_anim.push_back(Sprite(player_text,IntRect(i*40,0,40,40)));
	}
	Player player(player_anim,0,0,40, true);
	player.setPos(player.getSprite().getTextureRect().width/2,player.getSprite().getTextureRect().height/2);

	//Manager
	GO_Manager manager(&player);

	//Floor
	Texture floor_text;
	floor_text.loadFromFile("images/floor.png");
	Sprite floor_sprite(floor_text);

	//Square wall
	Texture wall_text;
	wall_text.loadFromFile("images/tile.png");
	Sprite wall_sprite(wall_text);
	for(int i=0; i<6;i++)
	{
		std::vector<Sprite> sprites;
		sprites.push_back(wall_sprite);
		GObject g(sprites, 120.0f+i*40.0f, 120.0f, 0.0f, true);
		manager.addGameObject(g);
	}

	//Clock
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
		if(manager.getPlayer()->isMoving() && timer>(animTime/manager.getPlayer()->numberOfSprites())){
			manager.getPlayer()->moveForward();
			timer = 0;
		}
		while (window.pollEvent(e))
		{
			if(!manager.getPlayer()->isMoving()){
				manager.getPlayer()->event(&e);
			}
			if (e.type == Event::Closed)
				window.close();
		}

		//Drawing part
		window.clear();
		window.draw(floor_sprite);
		manager.drawAll(&window);

		window.display();
	}

    return 0;
}
