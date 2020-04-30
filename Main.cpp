#include <SFML/Audio.hpp>
#include"Screen.h"

int main()
{
	//Music backgroundMusic;
	//backgroundMusic.openFromFile("Music.mp3");
	Player pacman("pacman", 11, 8, "pacman.png");
	Ghost ghosts[4];
	RenderWindow window;
	Text FinalText; FinalText.setScale(Vector2f(600, 100)); FinalText.setPosition(Vector2f(64, 64 + 8 * 32));
	window.create(VideoMode(800, 800), "Maze");

	ghosts[0].setGhost("blinky", 7, 8, "blinky.png", true);//setting Blinky above the ghost house and prepared to move at the beginning of the game
	ghosts[1].setGhost("pinky", 9, 8, "pinky.png", true);//setting Pinky int the middle of the ghost house and prepared to move at the beginning of the game
	ghosts[2].setGhost("inky", 9, 7, "inky.png", false);//setting Inky in the left of the ghost house and wouldn't start moving at the beginning of the game
	ghosts[3].setGhost("clyde", 9, 9, "clyde.png", false);//setting Clyde in the left of the ghost house and wouldn't start moving at the beginning of the game

	Screen myScreen(pacman, ghosts);

	Event e;
	for (int i = 0; i < 4; i++)
		ghosts[i].okMove();

	Clock timer;
	char movement = ' ';
	bool gameOn = true;//If the player didn't win or lose yet

	while (window.isOpen() && gameOn)
	{
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
				gameOn = false;
			}
			if (myScreen.ghostCollision())
			{
				if (!pacman.loseLive())
				{
					FinalText.setString("GameOver!!");
					gameOn = false;
				}
				movement = ' ';
			}

			myScreen.updateGhosts();
			if (myScreen.ghostCollision())
			{
				if (!pacman.loseLive())
				{
					FinalText.setString("GameOver!!");
					gameOn = false;
				}
				movement = ' ';
			}
			timer.restart();
		}
		
		window.clear();
		myScreen.drawAll(window);
		if (!gameOn)
			window.draw(FinalText);
		window.display();
	}

	return 0;
}