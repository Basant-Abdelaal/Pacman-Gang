#ifndef GHOST
#define GHOST
#include "Object.h"
#include <cstdlib>   
#include <ctime>
#include<fstream>
#include<queue>
#define row 21
#define col 17



class Ghost :public Object
{
private:
	bool canMove; //whether the ghost can move or not
	int gpath[row][col]; 
	vector<int> graph[200]; //adjacency list
	int cost[200];
	int parent[200];
	bool startLeft;
	int wait;
public:
	Ghost();
	Ghost(string n, int initialR, int initialC, string imagename, bool sl);
	void setGhost(string n, int initialR, int initialC, string imagename1, string imagename2, string imagename3, bool can, bool sl);
	void move(int node);
	void freightMode(); //To go into freight mode
	void unFreight(); //To go out of freight mode
	int getDirection(int  x, int y, vector<int> occupied);
	int getFreightDirection(vector<int> occupied);
	void okMove(bool n); //setting whether ghost can move or not
};

#endif