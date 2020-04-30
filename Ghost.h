#ifndef GHOST
#define GHOST
#include "Object.h"
#include <cstdlib>   
#include <ctime>

enum orientation {Up=0, Right, Down, Left};

class Ghost:public Object
{
private:
	orientation direction; //current direction of ghost
	bool canMove;
public:
	Ghost();
	Ghost(string n, int initialR, int initialC, string imagename);
	Ghost& operator=(Ghost&);
	void setGhost(string n, int initialR, int initialC, string imagename, bool can);
	void move();
	void restart();
	void frightMode();
	orientation changeDirection();
	orientation getDirection();
	void okMove();
};

#endif