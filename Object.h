#ifndef OBJECT
#define OBJECT
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
using namespace std;
using namespace sf;

class Object
{
protected:
	string name;
	int curHorizontal;
	int curVertical;
	int curRow;
	int curColumn;
	int initialRow; //To return to initial position after death
	int initialColumn;
	RectangleShape shape;
	Texture texture;
public:
	Object();
	Object(string n, int initialR, int initialC, string imagename);
	int getRow();
	int getColumn();
	int getHorizontal();
	int getVertical();
	RectangleShape& getShape() { return shape; }
	void updatePosition();
	void drawOnWindow(RenderWindow& win);
	void move() {};
};

#endif

