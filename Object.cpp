#include "Object.h"

Object::Object() {
	name = "";
	curRow = 0;
	curColumn = 0;
	initialColumn = 0;
	initialRow = 0;
}

Object::Object(string n, int initialR, int initialC, string imagename)
{
	name = n;
	curRow = initialR;
	curColumn = initialC;
	initialColumn = initialC;
	initialRow = initialR;
	updatePosition();
	texture.loadFromFile(imagename);
	shape.setTexture(&texture);
	shape.setSize(Vector2f(32, 32));
}

int Object::getRow()
{

	return curRow;
}

int Object::getColumn()
{
	return curColumn;
}

void Object::drawOnWindow(RenderWindow& win)
{
	shape.setPosition(Vector2f(curHorizontal, curVertical));
	win.draw(shape);
}

int Object::getHorizontal() //To get actual horizontal position on screen
{
	return curHorizontal;
}

int Object::getVertical() //To get actual vertical position on screen
{
	return curVertical;
}

void Object::updatePosition()
{
	curHorizontal = 64 + curColumn * 32;
	curVertical = 64 + curRow * 32;
	shape.setPosition(Vector2f(curHorizontal, curVertical));
}

void Object::restart() {
	curColumn = initialColumn;
	curRow = initialRow;
	updatePosition();
}




void Object::updateAnimation(int n) {
	if (animationTimer.getElapsedTime().asMilliseconds() > 250) { //So that the total time of the animation is 1 second
		snapshotIndex = (snapshotIndex + 1) % 4;
		texture = snapshot[snapshotIndex+n];
		animationTimer.restart();
	}
}