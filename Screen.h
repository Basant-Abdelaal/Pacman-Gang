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
	//vector <Text>high;
	int pelletsNum; //The number of pellets in the game
	Texture bricks, small_p, big_p, space, fruit1, fruit2, fruit3, fruit4, fruit5, fruit6;
	vector <RectangleShape> fruit; //all the fruits that could be added
	int fruitOrder; //Index to which fruit from the vector would be drawn next
	bool fruitAdded; //whether to draw a fruit or not
	Clock clydeTimer; //Timer to know when should clyde move
	SoundBuffer eat;
	Sound eatSound;
public:
	Screen(Player& pac, Ghost[4]);
	pair<bool,bool> updatePac(char&);
	void updateGhosts(bool freight);
	bool ghostCollision(); //if player collides with any ghost
	void drawAll(RenderWindow&); //To draw all objects in class Screen
	void setLevel(int);
	int getLevel() { return level; }
	void addFruit();
	bool isFruitAdded() { return fruitAdded; }
	void setHighScore(int n);
};



#endif

