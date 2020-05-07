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
	vector<Texture> snapshot;
	Clock animationTimer;
	int snapshotIndex;// Index to point to the next snapshot
public:
	Object();
	Object(string n, int initialR, int initialC, string imagename);
	int getRow();
	int getColumn();
	int getHorizontal(); //To get actual horizontal position on screen
	int getVertical(); //To get actual vertical position on screen
	RectangleShape& getShape() { return shape; }
	void updatePosition(); //updates the horizontal and vertical positions according to the row and column
	void drawOnWindow(RenderWindow& win);
	void move() {};
	void addSnapshots(string, string, string); //adds snapshots of the object's animation
	void updateAnimation(); //updates object's animation
	void restart(); //object returns to initial state
};

#endif

