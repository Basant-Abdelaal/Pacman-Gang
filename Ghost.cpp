#include "Ghost.h"

Ghost::Ghost():Object() {
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
	initialRow = 0;
	initialColumn = 0;
	memset(cost, -1, sizeof cost);
}

Ghost::Ghost(string n, int initialR, int initialC, string imagename):Object(n, initialR, initialC, imagename)
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
}

Ghost& Ghost::operator=(Ghost& g) {
	canMove = g.canMove;
	name = g.name;
	curRow = g.curRow;
	curColumn = g.curColumn;
	updatePosition();
	shape = g.shape;
	texture = g.texture;
	return *this;
}

void Ghost::setGhost(string n, int initialR, int initialC, string imagename1, string imagename2, string imagename3, bool can) {
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

	snapshot.resize(4);
	snapshot[0].loadFromFile(imagename1);
	snapshot[1].loadFromFile(imagename2);
	snapshot[2].loadFromFile(imagename3);
	snapshot[3].loadFromFile(imagename2);

	snapshotIndex = 0;
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


void Ghost::frightMode()
{
	shape.setFillColor(Color::Blue);
}

void Ghost::updateAnimation() {
	if (animationTimer.getElapsedTime().asMilliseconds() > 250) {
		snapshotIndex = (snapshotIndex + 1) % 4;
		texture = snapshot[snapshotIndex];
		animationTimer.restart();
	}
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

void Ghost::okMove(bool n)
{
	canMove = n;
}

