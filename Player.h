#ifndef PLAYER
#define PLAYER
#include "Object.h"

class Player:public Object
{
private:
	int score;
	int lives;
	int lifeIncrements;
public:
	Player(string n, int initialR, int initialC, string imagename);
	string getScore();
	int getLives();
	void increaseLives();
	bool loseLive();
	void move(int, int);
	void increaseScore(int);
	bool checkLiveBonus();
};

#endif