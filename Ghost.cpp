#include "Ghost.h"

Ghost::Ghost() :Object() {
	int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
	startLeft = 0;
	srand(time(0));
	canMove = 0;
	ifstream g;
	g.open("gpath.txt");
	if (g.is_open())
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (!g.eof())
					g >> gpath[i][j];
	}
	g.close();
	//setting the adjacency list 
	int r, c, node;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (gpath[i][j] == -1) //if a wall
				continue;
			node = gpath[i][j];
			for (int k = 0; k < 4; k++)
			{
				r = i + dx[k]; c = j + dy[k];
				if (r >= 0 && r < row && c >= 0 && c < col) //Not out of boundaries
				{
					graph[node].push_back(gpath[r][c]);
				}
			}
		}
	//To connect the left gate with the right gate
	graph[71].push_back(85); 
	graph[85].push_back(71);
	initialRow = 0;
	initialColumn = 0;
	memset(cost, -1, sizeof cost);
	wait = 0;
}

Ghost::Ghost(string n, int initialR, int initialC, string imagename, bool sl) :Object(n, initialR, initialC, imagename)
{
	int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
	srand(time(0));
	canMove = 0;
	ifstream g;
	g.open("gpath.txt");
	if (g.is_open())
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (!g.eof())
					g >> gpath[i][j];
	}
	g.close();
	int r, c, node;
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			if (gpath[i][j] == -1)
				continue;
			node = gpath[i][j];
			for (int k = 0; k < 4; k++)
			{
				r = i + dx[k]; c = j + dy[k];
				if (r >= 0 && r < row && c >= 0 && c < col)
				{
					graph[node].push_back(gpath[r][c]);
				}
			}
		}
	memset(cost, -1, sizeof cost);
	startLeft = sl;
	if (sl)
	{
		if (gpath[initialRow][initialColumn] == 78)
			wait = 3;
		else if (gpath[initialRow][initialColumn] == 61)
			wait = 1;
	}
	else
		wait = 0;
}


void Ghost::setGhost(string n, int initialR, int initialC, string imagename1, string imagename2, string imagename3, bool can, bool sl) {
	startLeft = sl;
	canMove = can;
	name = n;
	initialRow = initialR;
	initialColumn = initialC;
	curRow = initialR;
	curColumn = initialC;
	updatePosition();
	texture.loadFromFile(imagename1);
	shape.setTexture(&texture);
	shape.setSize(Vector2f(32, 32));

	this->snapshot.resize(4);
	snapshot[0].loadFromFile(imagename1);
	snapshot[1].loadFromFile(imagename2);
	snapshot[2].loadFromFile(imagename3);
	snapshot[3].loadFromFile(imagename2);

	if (sl)
	{
		if (gpath[initialRow][initialColumn] == 78)
			wait = 3;
		else if (gpath[initialRow][initialColumn] == 61)
			wait = 1;
	}
	else
		wait = 0;
}

//moving the ghost to a specific node (returned by getDirection)

void Ghost::move(int node)
{
	if (canMove) //if the ghost can move
	{
		if (!wait) //if this is not from the initial obligatory left moves
		{
			bool f = 1;
			for (int i = 0; i < row && f; i++)
				for (int j = 0; j < col && f; j++)
					if (gpath[i][j] == node)
					{
						curRow = i;
						curColumn = j;
						f = 0;
					}
			updatePosition();
		}
		//if this is from the initial obligatory left moves, then go left
		//According to the initial position of the ghost, he will be obliged to number of moves to go left (which is the variable wait)
		else 
		{
			switch (wait)
			{
			case 3:				
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						if (gpath[i][j] == 68)
						{
							curRow = i;
							curColumn = j;
						}
				updatePosition();
				wait--;
				break;
			case 2:
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						if (gpath[i][j] == 61)
						{
							curRow = i;
							curColumn = j;
						}
				updatePosition();
				wait--;
				break;
			case 1:
				for (int i = 0; i < row; i++)
					for (int j = 0; j < col; j++)
						if (gpath[i][j] == 60)
						{
							curRow = i;
							curColumn = j;
						}
				updatePosition();
				wait--;
				break;
			}
		}
	}
}


void Ghost::freightMode() //To go into freight mode
{
	shape.setFillColor(Color::Blue);
}

void Ghost::unFreight() //To go out of freight mode
{
	shape.setFillColor(Color::White);
}


//Get the node that the ghost should go next
//BFS from pacman to the ghost , the adjascent node to the ghost that has less cost by 1 is the next node

int Ghost::getDirection(int  x, int y, vector<int> occupied)
{
	queue<pair<int, int> >q;  //bfs queue<position node, level>
	q.push(make_pair(gpath[curRow][curColumn], 0)); //starting from the node of the ghost
	pair<int, int> cur;
	memset(cost, -1, sizeof cost);
	while (q.size())
	{
		cur = q.front();
		q.pop();
		if (cost[cur.first] != -1) continue;  //node is visited already
		cost[cur.first] = cur.second;
		if (cur.first == gpath[x][y])  //if pacman is found
			break;
		for (int i = 0; i < graph[cur.first].size(); i++) //loop on the adjacent nodes
		{
			if (cost[graph[cur.first][i]] == -1) //if not visited, then push in the queue
				q.push(make_pair(graph[cur.first][i], cur.second + 1));
		}
	}
	while (q.size())
		q.pop();
	q.push(cur); //push pacman to the queue
	while (q.size())
	{
		cur = q.front();
		q.pop();
		if (cur.second == 1)
			break;
		for (int i = 0; i < graph[cur.first].size(); i++)  //loop on the adjacent node
			if (cost[graph[cur.first][i]] == cur.second - 1) //if it is less than the level by 1, push it to the queue
				q.push(make_pair(graph[cur.first][i], cur.second - 1));
	}
	for (int i = 0; i < occupied.size(); i++)
		if (occupied[i] == cur.first)
			cur.first = gpath[curRow][curColumn];
	return cur.first; 
}

//Get the node that the ghost should go next in fright mode
//BFS from the ghost to the initial position, return back till you reach the node with cost 1, this is the next node

int Ghost::getFreightDirection(vector<int> occupied)
{
	//if (gpath[curRow][curColumn] == gpath[initialRow][initialColumn])
		//return gpath[curRow][curColumn];
	queue<pair<int, int> >q;
	q.push(make_pair(gpath[curRow][curColumn], 0));
	pair<int, int> cur;
	memset(cost, -1, sizeof cost);
	while (q.size())
	{
		cur = q.front();
		q.pop();
		if (cost[cur.first] != -1) continue;
		cost[cur.first] = cur.second;
		if (cur.first == gpath[initialRow][initialColumn])
			break;
		for (int i = 0; i < graph[cur.first].size(); i++)
		{
			if (cost[graph[cur.first][i]] == -1)
				q.push(make_pair(graph[cur.first][i], cur.second + 1));
		}
	}
	while (q.size())
		q.pop();
	q.push(cur);
	while (q.size())
	{
		cur = q.front();
		q.pop();
		if (cur.second == 1)
			break;
		for (int i = 0; i < graph[cur.first].size(); i++)
			if (cost[graph[cur.first][i]] == cur.second - 1)
				q.push(make_pair(graph[cur.first][i], cur.second - 1));
	}
	for (int i = 0; i < occupied.size(); i++)
		if (occupied[i] == cur.first)
			cur.first = gpath[curRow][curColumn];
	return cur.first;
}


void Ghost::okMove(bool n)
{
	canMove = n;
}

