#include <SFML/Audio.hpp>
#include"Screen.h"

bool runLevelOne(Screen&, Player&, RenderWindow&, Event&, char&, Clock&);
Text FinalText;
Player pacman("pacman", 15, 8, "pacman.png");
Ghost ghosts[4];

int main()
{
	//Music backgroundMusic;
	//backgroundMusic.openFromFile("Music.mp3");

	RenderWindow window;
	Font font;
	font.loadFromFile("aerial.ttf");
	Text Ready; Ready.setString("Ready!"); Ready.setPosition(Vector2f(55 + 7 * 32, 62 + 11 * 32)); Ready.setCharacterSize(28); Ready.setFillColor(Color::White); Ready.setFont(font);
	FinalText.setCharacterSize(60); FinalText.setPosition(Vector2f(70, 70 + 10 * 32)); FinalText.setFillColor(Color::White); FinalText.setFont(font);
	window.create(VideoMode(800, 800), "Maze");

	ghosts[0].setGhost("blinky", 7, 8, "blinky.png", true);//setting Blinky above the ghost house and prepared to move at the beginning of the game
	ghosts[1].setGhost("pinky", 9, 8, "pinky.png", true);//setting Pinky int the middle of the ghost house and prepared to move at the beginning of the game
	ghosts[2].setGhost("inky", 9, 7, "inky.png", false);//setting Inky in the left of the ghost house and wouldn't start moving at the beginning of the game
	ghosts[3].setGhost("clyde", 9, 9, "clyde.png", false);//setting Clyde in the left of the ghost house and wouldn't start moving at the beginning of the game

	Screen myScreen(pacman, ghosts);

	Event e;

	Clock timer;
	char movement = ' ';

	window.clear();
	myScreen.drawAll(window);
	window.draw(Ready);
	window.display();

	bool gameOn = false;//If the game is working

	

	while (window.isOpen())
	{
		while (!gameOn)
			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();
				else if (e.type == Event::KeyPressed)
					if (e.key.code == Keyboard::Space)
						gameOn = true;

		while (gameOn) {
			gameOn = runLevelOne(myScreen, pacman, window, e, movement, timer);
			window.clear();
			myScreen.drawAll(window);
			if (!gameOn)
				window.draw(FinalText);
			window.display();
		}
	}

	return 0;
}

bool runLevelOne(Screen& myScreen, Player& pacman, RenderWindow& window, Event& e, char& movement, Clock& timer) {
	while (window.pollEvent(e))
	{
		if (e.type == Event::Closed)
			window.close();
		else if (e.type == Event::KeyPressed)
		{

			switch (e.key.code)
			{
			case Keyboard::Up:
				movement = 'U';
				break;
			case Keyboard::Down:
				movement = 'D';
				break;
			case Keyboard::Right:
				movement = 'R';
				break;
			case Keyboard::Left:
				movement = 'L';
				break;
			}
		}
	}
	if (timer.getElapsedTime().asMilliseconds() > 200) {
		if (!myScreen.updatePac(movement))
		{
			FinalText.setString("Congratulations");
			return false;
		}
		if (myScreen.ghostCollision())
		{
			if (!pacman.loseLive())
			{
				FinalText.setString("GameOver!!");
				return false;
			}
			movement = ' ';
		}

		myScreen.updateGhosts();
		if (myScreen.ghostCollision())
		{
			
			if (!pacman.loseLive())
			{
				FinalText.setString("GameOver!!");
				return false;
			}
			for (int i = 0; i < 4; i++)
				ghosts[i].restart();
			movement = ' ';
		}
		timer.restart();
	}
	return true;
}