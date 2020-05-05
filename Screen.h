#ifndef SCREEN
#define SCREEN
#include "Ghost.h"
#include "Player.h"
#include<vector>
#include<fstream>
#include <SFML/Audio.hpp>
#define row 21
#define col 17
class Screen
{
private:
	int level;
	int pellets[row][col];
	RectangleShape board[row][col];
	Player *pacman;
	Ghost* ghosts;
	Font font;
	Text scoreHeader, highScoreHeader, levelHeader, score, levelText;
	//vector<RectangleShape> lives;
	Texture live;
	int pelletsNum;
	Texture bricks, small_p, big_p, space;
	bool directionOk(Ghost&);
	SoundBuffer eat;
	Sound s;
public:
	Screen(Player& pac, Ghost[4]);
	bool updatePac(char&);
	void updateGhosts();
	bool ghostCollision();
	void drawAll(RenderWindow&);
	void levelUp();
	int getLevel() { return level; }
};



#endif

