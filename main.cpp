#include <iostream>
#include <thread>
#include <time.h>
#include "src/generator/util.h"
#include "src/generator/sokoban.h"
#include "src/generator/cxxopts.h"
#include "src/player.h"
#include "src/go_manager.h"

using namespace sf;

Table<char> trySokoban(RandomGen& randomGen, Vec2 levelSize, int numTries,
                int numBoulders, int numMoves, int rooms, int doors) {
	srand(time(0));
	numBoulders = rand() % 4 + 3;
	numMoves = 40;
	rooms = rand() % 4 + 3;
	doors = 1;
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
  return Table<char>(0,0);
}

void loadLevel(Table<char> & level, GO_Manager & manager, Texture & floor_text,
				Texture & wall_text, Texture & caisse, Texture & done_caisse, Texture & goal)
{


	for (int y : level.getBounds().getYRange()) {
	  for (int x : level.getBounds().getXRange()){
		  std::vector<Sprite> v;
		  switch (level[Vec2(x,y)]) {
		  	case '#'/*Wall*/:
				v.push_back(Sprite(wall_text));
				manager.addGameObject(GObject(v,x*40+20,y*40+20,0,true));
				break;
			case '@'/*Player*/:
				manager.getPlayer()->setPos(x*40+20,y*40+20);
				break;
			case '0'/*Caisse*/:
				{
					v.push_back(Sprite(caisse));
					v.push_back(Sprite(done_caisse));
					manager.addGameObject(GObject(v,x*40+20,y*40+20,0,true,true));
					break;
				}
			case '^'/*Goal*/:
				{
					v.push_back(Sprite(goal));
					manager.addGameObject(GObject(v,x*40+20,y*40+20,0,false,false,true));
				}
				break;
			default:
				break;

		  }
	  }
	}

}

int main()
{
	//Generate level
	int tries = 1000;
    Vec2 levelSize(25,25);
    srand(time(0));
    int boulders = rand() % 4 + 3;
    int moves = 40;
    int rooms = rand() % 4 + 3;
    int doors = 1;
    int cpt = 0;
    RandomGen randomGen;
    randomGen.init(time(0));
    Table<char> level = trySokoban(randomGen, levelSize, tries, boulders, moves, rooms, doors);
	srand(time(0));

	RenderWindow window(VideoMode(levelSize.x*40, levelSize.y*40), "Best Sokoban Ever !");
	if(window.getSize().x > VideoMode::getDesktopMode().width || window.getSize().y > VideoMode::getDesktopMode().width)
		window.setSize(Vector2u(window.getSize().x/2, window.getSize().y/2));

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

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
	Font MyFont;

	// Chargement à partir d'un fichier sur le disque
	if (!MyFont.loadFromFile("images/azertyperegular.ttf"))
	{
	    printf("font not loaded\n");
	}

	Text _text, _time_txt, _cpt_txt;
	_text.setFont(MyFont);_time_txt.setFont(MyFont);_cpt_txt.setFont(MyFont);
	_text.setCharacterSize(34);_time_txt.setCharacterSize(34);_cpt_txt.setCharacterSize(34);
	_text.setColor(Color::Black);_time_txt.setColor(Color::Black);_cpt_txt.setColor(Color::Black);


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


	loadLevel(level, manager, floor_text, wall_text, caisse, done_caisse, goal);

	//Clock
	Clock clock;
	float timer = 0;
	int seconds;
	int minuts;
	float globalTimer = 0;
	float animTime = 0.25;

    while (window.isOpen())
    {
		//Time
		float time = clock.getElapsedTime().asSeconds();
		clock.restart();
		timer+=time;
		globalTimer+=time;
		if(!manager.victoryGlobal())
		{
			seconds = (int)globalTimer%60;
			minuts = floor(globalTimer / 60);
		}
		Event e;
		if(manager.getPlayer()->isMoving() && timer>(animTime/manager.getPlayer()->numberOfSprites())){
			
			manager.moveForward();
			timer = 0;
		}
		else{

		}
		while (window.pollEvent(e))
		{
			if(e.type == sf::Event::KeyPressed)
			{
				switch(e.key.code)
				{
					case Keyboard::R:
						manager.clearAll();
						loadLevel(level, manager, floor_text, wall_text, caisse, done_caisse, goal);
						cpt = 0;
						globalTimer = 0;
						break;
					case Keyboard::N:
					{
						manager.clearAll();
		    			level = trySokoban(randomGen, levelSize, tries, boulders, moves, rooms, doors);
		    			loadLevel(level, manager, floor_text, wall_text, caisse, done_caisse, goal);
						cpt = 0;
						globalTimer = 0;
		    			break;
					}
					case Keyboard::Z:
						manager.depiler();
						if(cpt!=0)
							cpt--;
						break;
					default:
						break;
				}
				if(!manager.getPlayer()->isMoving()){
					manager.getPlayer()->event(&e);
					if(!(manager.getPlayer()->getDir().x == 0 && manager.getPlayer()->getDir().y == 0))
					{
						manager.empiler();
						if(manager.moveForward())
						{
							cpt++;
						}
					}
				}
			}
			
			if (e.type == Event::Closed)
				window.close();
		}

		//Drawing part
		window.clear();
    	manager.victoryUpdate();
		window.draw(floor_sprite);
		manager.drawAll(&window);
		_time_txt.setString(" Time : " + std::to_string(minuts) +" : "+ std::to_string(seconds));
		window.draw(_time_txt);
		_cpt_txt.setString(" Moves : " + std::to_string(cpt) + "  ");
		FloatRect rect_cpt = _cpt_txt.getLocalBounds();
		_cpt_txt.setPosition(Vector2f(window.getSize().x - rect_cpt.width, 0));
		window.draw(_cpt_txt);
    	if(manager.victoryGlobal())
    	{
			_text.setString("Victory !\nPress R to restart\nPress N to generate a new level");
			FloatRect rect = _text.getLocalBounds();
			_text.setOrigin(rect.left + rect.width/2.0f, rect.top + rect.height/2.0f);
			_text.setPosition(Vector2f(window.getSize().x/2.0f, window.getSize().y/2.0f));
			window.draw(_text);
    	}
		window.display();
	}

    return 0;
}
