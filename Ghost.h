#ifndef GHOST
#define GHOST
#include "Object.h"
#include <cstdlib>   
#include <ctime>
#include<fstream>
#include<queue>
#define row 21
#define col 17



class Ghost:public Object
{
private:
	bool canMove;
	int gpath[row][col];
	vector<int> graph[200];
	vector<Texture> snapshot;
	Clock animationTimer;
	int snapshotIndex;// Index to point to the next snapshot
	int cost[200];
public:
	Ghost();
	Ghost(string n, int initialR, int initialC, string imagename);
	Ghost& operator=(Ghost&);
	void setGhost(string n, int initialR, int initialC, string imagename1, string imagename2, string imagename3, bool can);
	void move(int node);
	void updateAnimation();
	void frightMode();
	int getDirection(int  x, int y);
	void okMove(bool n);
};

#endif