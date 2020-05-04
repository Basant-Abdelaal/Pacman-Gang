#include <SFML/Audio.hpp>
#include"Screen.h"

bool runLevelOne(Screen&, Player&, RenderWindow&, Event&, char&);
Text FinalText;
Player pacman("pacman", 15, 8, "pacman.png");
Ghost ghosts[4];
Clock timerP, timerG;

int main()
{

	RenderWindow window;
	SoundBuffer buffer;
	buffer.loadFromFile("pacman_beginning.wav");
	Sound sound;
	sound.setBuffer(buffer);
	sound.play();
	Font font;
	font.loadFromFile("aerial.ttf");
	Text Ready; Ready.setString("Ready!"); Ready.setPosition(Vector2f(55 + 7 * 32, 62 + 11 * 32)); Ready.setCharacterSize(28); Ready.setFillColor(Color::White); Ready.setFont(font);
	FinalText.setCharacterSize(60); FinalText.setPosition(Vector2f(70, 70 + 10 * 32)); FinalText.setFillColor(Color::White); FinalText.setFont(font);
	Text choosePlayer;  choosePlayer.setString("1) Pacman OR 2) Ms Pacman ?"); choosePlayer.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32)); choosePlayer.setCharacterSize(23); choosePlayer.setFillColor(Color::White); choosePlayer.setFont(font);
	window.create(VideoMode(800, 800), "Maze");

	ghosts[0].setGhost("blinky", 7, 8, "blinky.png", true);//setting Blinky above the ghost house and prepared to move at the beginning of the game
	ghosts[1].setGhost("pinky", 9, 8, "pinky.png", true);//setting Pinky int the middle of the ghost house and prepared to move at the beginning of the game
	ghosts[2].setGhost("inky", 9, 7, "inky.png", false);//setting Inky in the left of the ghost house and wouldn't start moving at the beginning of the game
	ghosts[3].setGhost("clyde", 9, 9, "clyde.png", false);//setting Clyde in the left of the ghost house and wouldn't start moving at the beginning of the game

	Screen myScreen(pacman, ghosts);

	Event e;

	char movement = ' ';

	bool gameOn = false;//If the game is working
	bool playerChosen = false;//If the player has chosen which avatar to play with
	
	while (window.isOpen())
	{
		while (!gameOn) {
			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();
				else if (e.type == Event::KeyPressed)
					if (!playerChosen) {
						if (e.key.code == Keyboard::Num1)
						{
							pacman.setImage("pacman.png");
							playerChosen = true;
						}
						else if (e.key.code == Keyboard::Num2)
						{
							pacman.setImage("mspacman.png");
							playerChosen = true;
						}
					}
					else if (e.key.code == Keyboard::Space)
						gameOn = true;
			window.clear();
			myScreen.drawAll(window);
			if (!playerChosen)
				window.draw(choosePlayer);
			else
				window.draw(Ready);
			window.display();
		}

		while (gameOn) {
			gameOn = runLevelOne(myScreen, pacman, window, e, movement);
			window.clear();
			myScreen.drawAll(window);
			if (!gameOn) {
				window.draw(FinalText);
				playerChosen = false;
			}
			window.display();
		}
	}

	return 0;
}

bool runLevelOne(Screen& myScreen, Player& pacman, RenderWindow& window, Event& e, char& movement) {
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
	if (timerP.getElapsedTime().asMilliseconds() > 200) {
		if (!myScreen.updatePac(movement))
		{
			FinalText.setString("Congratulations");
			myScreen.levelUp();
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

		timerP.restart();
	}
	if (timerG.getElapsedTime().asMilliseconds() > 300-50*myScreen.getLevel()) {

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
		timerG.restart();
	}

	return true;
}