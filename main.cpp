#include <iostream>
#include <thread>
#include <time.h>
#include "src/generator/util.h"
#include "src/generator/sokoban.h"
#include "src/generator/cxxopts.h"
#include "src/player.h"
#include "src/go_manager.h"

using namespace sf;

void printLevel(const Table<char>& level) {
  for (int y : level.getBounds().getYRange()) {
    for (int x : level.getBounds().getXRange())
      cout << level[Vec2(x, y)];
    cout << '\n';
  }
}

Table<char> trySokoban(RandomGen& randomGen, Vec2 levelSize, int numTries,
                int numBoulders, int numMoves, int rooms, int doors) {
  int maxDepth = -1;
  for (int i = 0; i < numTries; ++i) {
    SokobanMaker sokoban(randomGen, levelSize, numBoulders, numMoves);
    sokoban.setNumRooms(rooms);
    sokoban.setNumDoors(doors);
    if (sokoban.make() && sokoban.getMaxDepth() > maxDepth) {
      maxDepth = sokoban.getMaxDepth();
      cout << "Depth reached: " << maxDepth << endl;
      return sokoban.getResult();
    }
  }
  if (maxDepth == -1)
    cout << "Unable to generate a level with these parameters" << endl;
}

int main()
{
	//Generate level
	int tries = 1000;
    Vec2 levelSize(20,20);
    int boulders = 4;
    int moves = 20;
    int rooms = 3;
    int doors = 1;
    RandomGen randomGen;
    randomGen.init(time(0));
    Table<char> level = trySokoban(randomGen, levelSize, tries, boulders, moves, rooms, doors);
	srand(time(0));

	RenderWindow window(VideoMode(20*40, 20*40), "Best Sokoban Ever !");
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

	//Caisse
	Texture caisse,done_caisse;
	caisse.loadFromFile("images/todo.png");
	done_caisse.loadFromFile("images/done.png");

	//Goal
	Texture goal;
	goal.loadFromFile("images/goal.png");

	for (int y : level.getBounds().getYRange()) {
	  for (int x : level.getBounds().getXRange()){
		  std::vector<Sprite> v;
		  switch (level[Vec2(x,y)]) {
		  	case '#'/*Wall*/:
				v.push_back(Sprite(wall_text));
				manager.addGameObject(GObject(v,x*40+20,y*40+20,0,true));
				break;
			case '@'/*Player*/:
				player.setPos(x*40+20,y*40+20);
				break;
			case '0'/*Caisse*/:
				{
					v.push_back(Sprite(caisse));
					v.push_back(Sprite(done_caisse));
					GObject ca(v,x*40+20,y*40+20,0,true);
					ca.setMovable(true);
					manager.addGameObject(ca);
					break;
				}
			case '^'/*Goal*/:
				v.push_back(Sprite(goal));
				manager.addGameObject(GObject(v,x*40+20,y*40+20,0,false));
				break;
			default:
				break;

		  }
	  }
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
			
			manager.moveForward();
			timer = 0;
		}
		while (window.pollEvent(e))
		{
			if(!manager.getPlayer()->isMoving()){
				manager.getPlayer()->event(&e);
				if(!(manager.getPlayer()->getDir().x == 0 && manager.getPlayer()->getDir().y == 0))
				{
					manager.moveForward();
				}
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
