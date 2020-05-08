#include "Screen.h"

Screen::Screen(Player& pac, Ghost G[4])
{
	pacman = &pac;
	ghosts = G;

	ifstream p;
	p.open("pellets.txt");
	if (p.is_open())
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (!p.eof())
					p >> pellets[i][j];
	}
	p.close();

	bricks.loadFromFile("brick.png");
	small_p.loadFromFile("small_p.png");
	big_p.loadFromFile("big_p.png");
	space.loadFromFile("space.png");

	pelletsNum = 0;

	//Setting board
	//Increasing number of pellets every time a pellet is drawn 
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			board[i][j].setPosition(64 + 32 * j, 64 + 32 * i);
			board[i][j].setSize(Vector2f(32, 32));
			if (pellets[i][j] == -1)   //Bricks
			{
				board[i][j].setTexture(&bricks);
			}
			else if (pellets[i][j] == 1)   //Pellets small
			{
				board[i][j].setTexture(&small_p);
				pelletsNum++;
			}
			else if (pellets[i][j] == 2)   //Pellets big
			{
				board[i][j].setTexture(&big_p);
				pelletsNum++;
			}
			else  //space
			{
				board[i][j].setTexture(&space);
			}
		}

	level = 1; //Initiallizing level

	font.loadFromFile("aerial.ttf");
	//Setting texts
	scoreHeader.setString("Score:"); scoreHeader.setPosition(Vector2f(0, 0)); scoreHeader.setCharacterSize(27); scoreHeader.setFillColor(Color::White); scoreHeader.setFont(font);
	score.setString("0"); score.setPosition(Vector2f(0, 32)); score.setCharacterSize(27); score.setFillColor(Color::White); score.setFont(font);
	levelHeader.setString("Level:"); levelHeader.setPosition(Vector2f(32 * 15, 0)); levelHeader.setCharacterSize(27); levelHeader.setFillColor(Color::White); levelHeader.setFont(font);
	levelText.setString("Easy"); levelText.setPosition(Vector2f(32 * 15, 32)); levelText.setCharacterSize(27); levelText.setFillColor(Color::White); levelText.setFont(font);
	highScoreHeader.setString("HighScore:"); highScoreHeader.setPosition(Vector2f(32 * 6, 0)); highScoreHeader.setCharacterSize(27); highScoreHeader.setFillColor(Color::White); highScoreHeader.setFont(font);

	//setting fruits' textures
	fruit1.loadFromFile("fruit1.png");
	fruit2.loadFromFile("fruit2.png");
	fruit3.loadFromFile("fruit3.png");
	fruit4.loadFromFile("fruit4.png");
	fruit5.loadFromFile("fruit5.png");
	fruit6.loadFromFile("fruit6.png");

	//setting all fruits' shapes
	fruit.resize(6);
	for (int i = 0; i < 6; i++)
		fruit[i].setSize(Vector2f(32, 32));
	fruit[0].setPosition(64 + 32 * 5, 64 + 32 * 7);
	fruit[0].setTexture(&fruit1);
	fruit[1].setPosition(64 + 32 * 7, 64 + 32 * 11);
	fruit[1].setTexture(&fruit2);
	fruit[2].setPosition(64 + 32, 64 + 32 * 9);
	fruit[2].setTexture(&fruit3);
	fruit[3].setPosition(64 + 32 * 15, 64 + 32 * 9);
	fruit[3].setTexture(&fruit4);
	fruit[4].setPosition(64 + 32 * 5, 64 + 32 * 7);
	fruit[4].setTexture(&fruit5);
	fruit[5].setPosition(64 + 32 * 7, 64 + 32 * 11);
	fruit[5].setTexture(&fruit6);

	fruitOrder = 0; //starting with the first fruit in the vector

}

void Screen::setHighScore(int n)
{
	string str = to_string(n);
	highScore.setString(str); highScore.setPosition(Vector2f(32 * 6, 32)); highScore.setCharacterSize(27); highScore.setFillColor(Color::White); highScore.setFont(font);

}

void Screen::updateGhosts(bool freight) 
{
	vector<int> n;
	n.clear();
	int node;
	if (!freight)
		for (int i = 0; i < 4; i++)
		{
			node = ghosts[i].getDirection(pacman->getRow(), pacman->getColumn(),n);
			ghosts[i].move(node);
			n.push_back(node);
		}

	else
		for (int i = 0; i < 4; i++)
		{
			node = ghosts[i].getFreightDirection(n);
			ghosts[i].move(node);
			n.push_back(node);
		}
}


pair<bool,bool> Screen::updatePac(char& m)
{
	pair<bool, bool> ans;
	ans.second = 0;
	int newRow = pacman->getRow(), newColumn = pacman->getColumn(); //for pac
	switch (m)
	{
	case 'U':
		newRow--;
		break;
	case 'D':
		newRow++;
		break;
	case 'R':
		newColumn++;
		break;
	case 'L':
		newColumn--;
		break;
	}
	if (newColumn == -1 && newRow == 9)
	{
		newColumn = 16;
		pacman->move(newRow, 16);
	}
	else if (newColumn == 17 && newRow == 9)
	{
		newColumn = 0;
		pacman->move(newRow, 0);
	}
	else if (pellets[newRow][newColumn] != -1)
	{
		pacman->move(newRow, newColumn);
		if (pellets[newRow][newColumn] == 1)
		{
			eat.loadFromFile("pacman_chomp.wav");
			s.setBuffer(eat);
			s.play();
			pacman->increaseScore(10);
			score.setString(pacman->getScore());
			pelletsNum--;
		}
		else if (pellets[newRow][newColumn] == 2)
		{
			pacman->increaseScore(50);
			score.setString(pacman->getScore());
			ans.second = 1;  //freight mode
			pelletsNum--;
		}
		pellets[newRow][newColumn] = 0;
		board[newRow][newColumn].setTexture(&space);
	}

	if (fruitAdded) {
		if (pacman->getShape().getGlobalBounds().intersects(fruit[fruitOrder].getGlobalBounds())) {
			fruitAdded = false;
			pacman->increaseScore(250 * (fruitOrder + 1));
			score.setString(pacman->getScore());

			fruitOrder = (fruitOrder + 1) % fruit.size();
		}
	}

	if (pelletsNum == 60) {
		ghosts[2].okMove(true);
		clydeTimer.restart();
	}
	else if (pelletsNum < 60) {
		if (clydeTimer.getElapsedTime().asSeconds() > 10)
			ghosts[3].okMove(true);
	}

	if (pelletsNum == 0)
	{
		ans.first = 1;
	}
	else
		ans.first = 0;

	return ans;
}

bool Screen::ghostCollision()
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
		if (ghosts[i].getShape().getGlobalBounds().intersects(pacman->getShape().getGlobalBounds()))
		{
			flag = true;
			ghosts[i].restart();
		}
	return flag;
}


void Screen::drawAll(RenderWindow& win)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			win.draw(board[i][j]);

	if (fruitAdded) {
		win.draw(fruit[fruitOrder]);
	}

	pacman->drawOnWindow(win);

	for (int i = 0; i < 4; i++)
		ghosts[i].drawOnWindow(win);

	win.draw(scoreHeader);
	win.draw(score);
	win.draw(levelText);
	win.draw(levelHeader);
	win.draw(highScoreHeader);
	win.draw(highScore);
}

void Screen::setLevel(int n) {
	level = n;

	ifstream p;
	p.open("pellets.txt");
	if (p.is_open())
	{
		for (int i = 0; i < row; i++)
			for (int j = 0; j < col; j++)
				if (!p.eof())
					p >> pellets[i][j];
	}
	p.close();

	pelletsNum = 0;

	switch (level) { //sets the level's theme
	case 1:
		bricks.loadFromFile("brick.png");
		levelText.setString("Easy");
		break;
	case 2:
		bricks.loadFromFile("flowers.png");
		levelText.setString("Medium");
		break;
	case 3:
		bricks.loadFromFile("bricks3.png");
		levelText.setString("Hard");
		break;
	}

	for (int i = 0; i < row; i++) //redraws the board
		for (int j = 0; j < col; j++)
		{
			board[i][j].setPosition(64 + 32 * j, 64 + 32 * i);
			board[i][j].setSize(Vector2f(32, 32));
			if (pellets[i][j] == -1)   //Bricks
			{
				board[i][j].setTexture(&bricks);
			}
			else if (pellets[i][j] == 1)   //Pellets small
			{
				board[i][j].setTexture(&small_p);
				pelletsNum++;
			}
			else if (pellets[i][j] == 2)   //Pellets big
			{
				board[i][j].setTexture(&big_p);
				pelletsNum++;
			}
			else  //space
			{
				board[i][j].setTexture(&space);
			}
		}

	//initiallizes the players and ghosts
	pacman->restart();
	for (int i = 0; i < 4; i++)
		(ghosts + i)->restart();

	fruitOrder = 0; //starts the fruits vector from beginning

	//stops clyde and inky from moving until conditions are set
	ghosts[2].okMove(false);
	ghosts[3].okMove(false);
}

void Screen::addFruit() {
	fruitAdded = true;
}

