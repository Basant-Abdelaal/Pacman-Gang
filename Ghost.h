#ifndef GHOST
#define GHOST
#include "Object.h"
#include <cstdlib>   
#include <ctime>       

class Ghost:public Object
{
private:
	int direction;
	bool canMove;
public:
	Ghost();
	Ghost(string n, int initialR, int initialC, string imagename);
	Ghost& operator=(Ghost&);
	void move();
	void restart();
	void frightMode();
	int changeDirection();
	int getDirection();
	void okMove();
};

#endif