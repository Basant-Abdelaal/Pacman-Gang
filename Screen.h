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
	Player* pacman;
	Ghost* ghosts;
	Font font;
	Text scoreHeader, highScoreHeader, levelHeader, score, levelText, highScore;
	int pelletsNum;
	Texture bricks, small_p, big_p, space, fruit1, fruit2, fruit3, fruit4, fruit5, fruit6;
	vector <RectangleShape> fruit;
	int fruitOrder; //Index to which fruit from the vector would be drawn next
	bool fruitAdded; //whether to draw a fruit or not
	Clock clydeTimer;
	/*bool directionOk(Ghost&);*/
	/*SoundBuffer eat;
	Sound s;*/
public:
	Screen(Player& pac, Ghost[4]);
	pair<bool,bool> updatePac(char&);
	void updateGhosts(bool freight);
	bool ghostCollision();
	void drawAll(RenderWindow&);
	void setLevel(int);
	int getLevel() { return level; }
	void addFruit();
	bool isFruitAdded() { return fruitAdded; }
	//void setPlayerData(string n, string s);
	void setHighScore(int n);
};



#endif

