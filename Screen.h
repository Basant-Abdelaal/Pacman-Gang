#ifndef SCREEN
#define SCREEN
#include "Ghost.h"
#include "Player.h"
#include<vector>
#include<fstream>
#define row 21
#define col 17
class Screen
{
private:
	int gpath[row][col];
	int pellets[row][col];
	RectangleShape board[row][col];
	Player *pacman;
	Ghost* ghosts;
	Font font;
	Text header, readyText, score, level;
	//vector<RectangleShape> lives;
	Texture live;
	int pelletsNum;
	Texture bricks, small_p, big_p, space;
	bool directionOk(Ghost&);
public:
	Screen(Player& pac, Ghost[4]);
	bool updatePac(char&);
	void updateGhosts();
	bool ghostCollision();
	void drawAll(RenderWindow&);
};



#endif

