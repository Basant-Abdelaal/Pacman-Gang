#include "Ghost.h"

Ghost::Ghost():Object() {
	direction = 0;
	srand(time(0));
	canMove = 0;
}

Ghost::Ghost(string n, int initialR, int initialC, string imagename):Object(n, initialR, initialC, imagename)
{
	direction = 0;
	srand(time(0));
	canMove = 0;
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

void Ghost::move()
{
	if (canMove)
	{
		switch (direction)
		{
		case 0:
			curRow--;
			break;
		case 1:
			curColumn++;
			break;
		case 2:
			curRow++;
			break;
		case 3:
			curColumn--;
			break;
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


int Ghost::changeDirection()
{
	direction= rand() % 4;
	return direction;
}


int Ghost::getDirection()
{
	return direction;
}

void Ghost::okMove()
{
	canMove = 1;
}