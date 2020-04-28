#include <SFML/Audio.hpp>
#include"Screen.h"

int main()
{
	//Music backgroundMusic;
	//backgroundMusic.openFromFile("Music.mp3");
	Player pacman("pacman", 11, 8, "pacman.png");
	Ghost pinky("pinky", 9, 8, "pinky.png"), blinky("blinky", 7, 8, "blinky.png"), inky("inky", 9, 7, "inky.png"), clyde("clyde", 9, 9, "clyde.png");
	Ghost ghosts[4];
	RenderWindow window;
	Text FinalText; FinalText.setScale(Vector2f(600, 100)); FinalText.setPosition(Vector2f(64, 64 + 8 * 32));
	window.create(VideoMode(800, 800), "Maze");

	ghosts[0] = blinky;
	ghosts[1] = pinky;
	ghosts[2] = inky;
	ghosts[3] = clyde;
	Screen myScreen(pacman, ghosts);

	Event e;
	for (int i = 0; i < 4; i++)
		ghosts[i].okMove();

	Clock timer;
	char movement = ' ';

	while (window.isOpen())
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
				break;
			}
			myScreen.updateGhosts();
			timer.restart();
		}
		if (myScreen.ghostCollision())
		{
			if (!pacman.loseLive())
			{
				window.clear();
				myScreen.drawAll(window);
				FinalText.setString("GameOver!!");
				window.draw(FinalText);
				break;
			}
			movement = ' ';
		}
		window.clear();
		myScreen.drawAll(window);
		window.display();
	}

	return 0;
}