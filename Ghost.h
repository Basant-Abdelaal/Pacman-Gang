#ifndef GHOST
#define GHOST
#include "Object.h"
#include <cstdlib>   
#include <ctime>
#include<fstream>
#include<queue>
#define row 21
#define col 17

enum orientation {Up=0, Right, Down, Left};


class Ghost:public Object
{
private:
	orientation direction; //current direction of ghost
	bool canMove;
	int gpath[row][col];
	vector<int> graph[200];
	int cost[200];
public:
	Ghost();
	Ghost(string n, int initialR, int initialC, string imagename);
	Ghost& operator=(Ghost&);
	void setGhost(string n, int initialR, int initialC, string imagename, bool can);
	void move(int node);
	void restart();
	void frightMode();
	orientation changeDirection();
	int getDirection(int  x, int y);
	void okMove();
};

#endif