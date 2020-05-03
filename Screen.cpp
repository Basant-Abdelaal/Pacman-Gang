#include "Screen.h"

Screen::Screen(Player& pac, Ghost G[4])
{
	pacman = & pac;
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

	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
		{
			board[i][j].setPosition(64 + 32 * j, 64 + 32 * i);
			board[i][j].setSize(Vector2f(32, 32));
			if (pellets[i][j] == -1)   //Bricks
			{
				board[i][j].setTexture(&bricks);
			}
			else if(pellets[i][j]==1)   //Pellets small
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
	level = 1;
	font.loadFromFile("aerial.ttf");

	scoreHeader.setString("Score:"); scoreHeader.setPosition(Vector2f(0, 0)); scoreHeader.setCharacterSize(27); scoreHeader.setFillColor(Color::White); scoreHeader.setFont(font);
	score.setString("0"); score.setPosition(Vector2f(0, 32)); score.setCharacterSize(27); score.setFillColor(Color::White); score.setFont(font);
	levelHeader.setString("Level:"); levelHeader.setPosition(Vector2f(32 * 15, 0)); levelHeader.setCharacterSize(27); levelHeader.setFillColor(Color::White); levelHeader.setFont(font);
	levelText.setString(to_string(level)); levelText.setPosition(Vector2f(32*15, 32)); levelText.setCharacterSize(27); levelText.setFillColor(Color::White); levelText.setFont(font);
	highScoreHeader.setString("HighScore:"); highScoreHeader.setPosition(Vector2f(32 * 6, 0)); highScoreHeader.setCharacterSize(27); highScoreHeader.setFillColor(Color::White); highScoreHeader.setFont(font);

	/*live.loadFromFile("live.png");
	for (int i = 0; i < 3; i++)
	{
		lives[i].setPosition(64 + 32 * i, 64 + 32 * 22);
		lives[i].setScale(Vector2f(32, 32));
		lives[i].setTexture(&live);
	}*/

}

void Screen::updateGhosts()
{
	for (int i = 0; i < 4; i++) {
		ghosts[i].move(ghosts[i].getDirection(pacman->getRow(),pacman->getColumn()));
	}
}


bool Screen::updatePac(char& m)
{
	int newRow=pacman->getRow(), newColumn=pacman->getColumn(); //for pac
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
	if (newColumn < 0 )
	{
		newColumn = 17;
	}
	else if (newColumn > 17)
	{
		newColumn = 0;
	}
	else if (pellets[newRow][newColumn] != -1)
	{
		pacman->move(newRow, newColumn);
		if (pellets[newRow][newColumn] == 1)
		{
			pacman->increaseScore(500);
			score.setString(pacman->getScore());
			pelletsNum--;
		}
		else if (pellets[newRow][newColumn] == 2)
		{
			//freight mode
			pelletsNum--;
		}
		pellets[newRow][newColumn] = 0;
		board[newRow][newColumn].setTexture(&space);
	}
	/*if (lives.size() != pacman->getLives())
	{
		lives.resize(pacman->getLives());
		for (int i = 0; i < pacman->getLives(); i++)
		{
			lives[i].setPosition(64 + 32 * i, 64 + 32 * 22);
			lives[i].setScale(Vector2f(32, 32));
			lives[i].setTexture(&live);
		}
	}*/
	if (pelletsNum == 0)
	{
		return 0;
	}
	return 1;
}

bool Screen::ghostCollision()
{
	bool flag = false;
	for (int i = 0; i < 4; i++)
		if (ghosts[i].getShape().getGlobalBounds().intersects(pacman->getShape().getGlobalBounds()))
			flag = true;
	return flag;
}


void Screen::drawAll(RenderWindow& win)
{
	for (int i = 0; i < row; i++)
		for (int j = 0; j < col; j++)
			win.draw(board[i][j]);
	pacman->drawOnWindow(win);
	for (int i = 0; i < 4; i++)
		ghosts[i].drawOnWindow(win);
	win.draw(scoreHeader);
	win.draw(score);
	win.draw(levelText);
	win.draw(levelHeader);
	win.draw(highScoreHeader);
	/*for (int i=0;i<lives.size();i++)
	{
		win.draw(lives[i]);
	}*/
}

void Screen::levelUp() {
	level++;
	levelText.setString(to_string(level));

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

	switch (level) {
	case 2:
		bricks.loadFromFile("bricks2.png");
		break;
	case3:
		bricks.loadFromFile("bricks3.png");
		break;
	case 4:

		break;
	default:

		break;
	}
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

	pacman->restart();
	for (int i = 0; i < 4; i++)
		(ghosts+i)->restart();

	
}