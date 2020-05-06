#include"Screen.h"

bool runLevel(Screen&, Player&, RenderWindow&, Event&, char&);
Text FinalText;
Player pacman("pacman", 15, 8, "pacman.png");
Ghost ghosts[4];
Clock timerP, timerG, fruitTimer;
vector<RectangleShape> lives;
Texture liveTexture;
string gender;
//SoundBuffer buffer;
//Sound sound;
int main()
{
	RenderWindow window;
	/*buffer.loadFromFile("pacman_beginning.wav");
	sound.setBuffer(buffer);
	sound.play();*/
	Font font;
	font.loadFromFile("aerial.ttf");
	Text Ready; Ready.setString("Ready!");
	Ready.setPosition(Vector2f(55 + 7 * 32, 62 + 11 * 32));
	Ready.setCharacterSize(28);
	Ready.setFillColor(Color::White);
	Ready.setFont(font);
	FinalText.setCharacterSize(60);
	FinalText.setPosition(Vector2f(70, 70 + 10 * 32));
	FinalText.setFillColor(Color::White); FinalText.setFont(font);
	Text choosePlayer; 
	choosePlayer.setString("1) Pacman OR 2) Ms Pacman ?");
	choosePlayer.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32)); 
	choosePlayer.setCharacterSize(23);
	choosePlayer.setFillColor(Color::White); 
	choosePlayer.setFont(font);
	Text chooseLevel;  
	chooseLevel.setString("1)Easy  2)Medium  3)Hard");
	chooseLevel.setPosition(Vector2f(55 + 2 * 32, 62 + 11 * 32));
	chooseLevel.setCharacterSize(23);
	chooseLevel.setFillColor(Color::White);
	chooseLevel.setFont(font);
	window.create(VideoMode(800, 800), "Maze");


	ghosts[0].setGhost("blinky", 7, 8, "blinky.png", "blinky2.png", "blinky3.png", true);//setting Blinky above the ghost house and prepared to move at the beginning of the game
	ghosts[1].setGhost("pinky", 9, 8, "pinky.png", "pinky2.png", "pinky3.png", true);//setting Pinky int the middle of the ghost house and prepared to move at the beginning of the game
	ghosts[2].setGhost("inky", 9, 7, "inky.png", "inky2.png", "inky3.png", false);//setting Inky in the left of the ghost house and wouldn't start moving at the beginning of the game
	ghosts[3].setGhost("clyde", 9, 9, "clyde.png", "clyde2.png", "clyde3.png", false);//setting Clyde in the left of the ghost house and wouldn't start moving at the beginning of the game

	pacman.addSnapshots("pacman.png", "pacman2.png", "pacman3.png");

	liveTexture.loadFromFile("pacman.png");
	lives.resize(3);
	for (int i = 0; i < 3; i++)
	{
		lives[i].setPosition(64 + 32 * i, 64 + 32 * 21);
		lives[i].setSize(Vector2f(32, 32));
		lives[i].setTexture(&liveTexture);
	}


	Screen myScreen(pacman, ghosts);

	Event e;

	char movement = ' ';

	bool gameOn = false;//If the game is working
	bool playerChosen = false;//If the player has chosen which avatar to play with
	bool isLevelChosen = false;

	while (window.isOpen())
	{
		while (!gameOn) {
			while (window.pollEvent(e))
				if (e.type == Event::Closed)
					window.close();
				else if (e.type == Event::KeyPressed)
					if (!playerChosen) {
						if (e.key.code == Keyboard::Numpad1 || e.key.code == Keyboard::Num1)
						{
							gender ="man";
							pacman.setImage("pacman.png");
							pacman.addSnapshots("pacman.png", "pacman2.png", "pacman3.png");
							playerChosen = true;}
						else if (e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2)
						{
							gender = "girl";
							pacman.setImage("mspacman.png");
							pacman.addSnapshots("mspacman.png", "mspacman2.png", "mspacman3.png");
							playerChosen = true;
						}
					}
					else if (!isLevelChosen) {
						if (e.key.code == Keyboard::Num1 || e.key.code == Keyboard::Numpad1) {
							myScreen.setLevel(1);
							isLevelChosen = true;
						}
						else if (e.key.code == Keyboard::Num2 || e.key.code == Keyboard::Numpad2) {
							myScreen.setLevel(2);
							isLevelChosen = true;
						}
						else if (e.key.code == Keyboard::Num3 || e.key.code == Keyboard::Numpad3) {
							myScreen.setLevel(3);
							isLevelChosen = true;
						}
					}
					else if (e.key.code == Keyboard::Space)
						gameOn = true;
			for (int i = 0; i < 4; i++)
				ghosts[i].updateAnimation();
			pacman.updateAnimation();

			window.clear();
			myScreen.drawAll(window);

			if (!playerChosen)
				window.draw(choosePlayer);
			else if (!isLevelChosen)
				window.draw(chooseLevel);
			else
				window.draw(Ready);
			window.display();
		}

		while (gameOn) {
			gameOn = runLevel(myScreen, pacman, window, e, movement);
			pacman.updateAnimation();
			window.clear();
			myScreen.drawAll(window);


			if (!gameOn) {
				window.draw(FinalText);
				playerChosen = false;
				isLevelChosen = false;
				pacman.restart();
				for (int i = 0; i < 4; i++)
					ghosts[i].restart();
			}
			for (int i = 0; i < lives.size(); i++)
				window.draw(lives[i]);
			window.display();
		}
	}

	return 0;
}

bool runLevel(Screen& myScreen, Player& pacman, RenderWindow& window, Event& e, char& movement) {
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
				if (gender == "man") {
					pacman.addSnapshots("pacman-up.png", "pacman2-up.png", "pacman3-up.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman-up.png", "mspacman2-up.png", "mspacman3-up.png");
					pacman.updateAnimation();
				}
				break;
			case Keyboard::Down:
				movement = 'D';
				if (gender == "man") {
					pacman.addSnapshots("pacman-down.png", "pacman2-down.png", "pacman3-down.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman-down.png", "mspacman2-down.png", "mspacman3-down.png");
					pacman.updateAnimation();
				}
				break;
			case Keyboard::Right:
				movement = 'R';
				if (gender == "man") {
					pacman.addSnapshots("pacman.png", "pacman2.png", "pacman3.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman.png", "mspacman2.png", "mspacman3.png");
					pacman.updateAnimation();
				}
				break;
			case Keyboard::Left:
				movement = 'L';
				if (gender == "man") {
					pacman.addSnapshots("pacman-left.png", "pacman2-left.png", "pacman3-left.png");
					pacman.updateAnimation();
				}
				else {
					pacman.addSnapshots("mspacman-left.png", "mspacman2-left.png", "mspacman3-left.png");
					pacman.updateAnimation();
				}
				break;
			}
		}
	}
	if (timerP.getElapsedTime().asMilliseconds() > 200) {
		if (!myScreen.updatePac(movement))
		{
			/*buffer.loadFromFile("cong.wav");
			sound.setBuffer(buffer);
			sound.play();*/
			FinalText.setString("Congratulations");
			return false;
		}
		if (myScreen.ghostCollision())
		{
			if (!pacman.loseLive())
			{
				///*buffer.loadFromFile("pacman_death.wav");
				//sound.setBuffer(buffer);*/
				//sound.play();
				FinalText.setString("GameOver!!");
				return false;
			}
			movement = ' ';
		}

		timerP.restart();
	}
	if (timerG.getElapsedTime().asMilliseconds() > 400 - 80 * myScreen.getLevel()) {

		myScreen.updateGhosts();
		if (myScreen.ghostCollision())
		{

			if (!pacman.loseLive())
			{
				/*buffer.loadFromFile("pacman_death.wav");
				sound.setBuffer(buffer);
				sound.play();*/
				FinalText.setString("GameOver!!");
				return false;
			}
			for (int i = 0; i < 4; i++)
				ghosts[i].restart();
			movement = ' ';
		}
		timerG.restart();
	}

	if (lives.size() != pacman.getLives())
	{
		lives.resize(pacman.getLives());
		for (int i = 0; i < lives.size(); i++)
		{
			lives[i].setPosition(64 + 32 * i, 64 + 32 * 22);
			lives[i].setSize(Vector2f(32, 32));
			lives[i].setTexture(&liveTexture);
		}
	}
	if (myScreen.isFruitAdded())
		fruitTimer.restart();
	else {
		if (fruitTimer.getElapsedTime().asSeconds() > 10 * myScreen.getLevel()) {
			myScreen.addFruit();
		}
	}


	return true;
}