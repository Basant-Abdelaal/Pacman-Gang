#include "Ghost.h"

Ghost::Ghost():Object() {
	direction = Up;
	srand(time(0));
	canMove = 0;
}

Ghost::Ghost(string n, int initialR, int initialC, string imagename):Object(n, initialR, initialC, imagename)
{
	direction = Up;
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


orientation Ghost::getDirection()
{
	return direction;
}

void Ghost::okMove()
{
	canMove = 1;
}