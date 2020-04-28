#include "Player.h"

Player::Player(string n, int initialR, int initialC, string imagename):Object(n,initialR, initialC, imagename)
{
	score = 0;
	lifeIncrements = 0;
	lives = 3;
}

string Player::getScore() 
{
	string str = to_string(score);
	return str;
	
}

int Player::getLives() 
{
	return lives;
}

void Player::increaseLives() 
{
	++lives;
}

bool Player::loseLive()
{
	--lives;
	if (lives == 0)
		return false;
	else {
		curColumn = initialColumn;
		curRow = initialRow;
		updatePosition();
		return true;
	}
}

void Player::move(int horizontal, int vertical) 
{
	curColumn = vertical;
	curRow = horizontal;
	updatePosition();
}

void Player::increaseScore(int n)
{
	score += n;
	if (checkLiveBonus())
		lives++;
}

bool Player::checkLiveBonus()
{
	if (score - (lifeIncrements + 1) * 100000 > 0) {
		++lifeIncrements;
		return true;
	}
	return false;
}