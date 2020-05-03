#include "Ghost.h"

Ghost::Ghost():Object() {
	int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
	direction = Up;
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
	for(int i=0;i<row;i++)
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
}

Ghost::Ghost(string n, int initialR, int initialC, string imagename):Object(n, initialR, initialC, imagename)
{
	int dx[4] = { 1,-1,0,0 }, dy[4] = { 0,0,1,-1 };
	direction = Up;
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
}

Ghost& Ghost::operator=(Ghost& g) {
	direction = g.direction;
	canMove = g.canMove;
	name = g.name;
	curRow = g.curRow;
	curColumn = g.curColumn;
	updatePosition();
	shape = g.shape;
	texture = g.texture;
	return *this;
}

void Ghost::setGhost(string n, int initialR, int initialC, string imagename, bool can) {
	canMove = can;
	name = n;
	curRow = initialR;
	curColumn = initialC;
	updatePosition();
	texture.loadFromFile(imagename);
	shape.setTexture(&texture);
	shape.setSize(Vector2f(32, 32));
}

void Ghost::move(int node)
{
	if (canMove)
	{
		bool f = 1;
		for(int i=0;i<row && f;i++)
			for(int j=0;j<col && f;j++)
				if (gpath[i][j] == node)
				{
					curRow = i;
					curColumn = j;
					f = 0;
				}
		updatePosition();
	}
}

void Ghost::restart() {
	curColumn = initialColumn;
	curRow = initialRow;
	updatePosition();
}

void Ghost::frightMode()
{
	shape.setFillColor(Color::Blue);
}


orientation Ghost::changeDirection()
{
	int n = rand() % 4 + 1;
	switch (n) {
	case 0:
		direction = Up;
		break;
	case 1:
		direction = Right;
		break;
	case 2:
		direction = Down;
		break;
	case 3:
		direction = Left;
		break;
	}
	return direction;
}


int Ghost::getDirection(int  x, int y)
{
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
		if (cur.first == gpath[x][y])
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
	return cur.first;
}

void Ghost::okMove()
{
	canMove = 1;
}