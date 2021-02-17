#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include "Misc.h"
#include "Menu.h"

using namespace sf;
using namespace std;



int main()
{
	RenderWindow window(VideoMode(800, 600), "Pong");

	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);
	std::cout << "Pong has started" << std::endl;

	//Menu
	Menu menu(window.getSize().x, window.getSize().y);
	
	//Date and time
	time_t now = time(0);
	tm* ltm = localtime(&now);


	//Text file
	ofstream history;
	history.open("history.txt", ios::app);
	history << "--------------------------- \n";
	history << ltm->tm_mday << "/" << 1 + ltm->tm_mon << "/" << 1900 + ltm->tm_year << endl;

	//Font file
	Font font;
	font.loadFromFile("Data/arial.ttf");

	//Text
	Text score;
	score.setFont(font);
	score.setCharacterSize(30);
	score.setFillColor(Color::Red);
	score.setPosition(320, 10);
	score.setString(" 0 : 0 ");

	Text p1win;
	p1win.setFont(font);
	p1win.setCharacterSize(75);
	p1win.setFillColor(Color(255, 0, 0));
	p1win.setPosition(200, 250);
	p1win.setString("Player 1 wins!");

	Text p2win;
	p2win.setFont(font);
	p2win.setCharacterSize(75);
	p2win.setFillColor(Color(0, 0, 255));
	p2win.setPosition(200, 250);
	p2win.setString("Player 2 wins!");


	//Images
	Texture tex_pad, tex_pad1, tex_ball, tex_background;
	tex_pad.loadFromFile("Data/pad.png"); tex_pad1.loadFromFile("Data/pad1.png"); tex_ball.loadFromFile("Data/ball.png"); tex_background.loadFromFile("Data/bg.jpg");


	//Sound
	SoundBuffer buff_hit;
	buff_hit.loadFromFile("Data/hit.wav");
	Sound hit;
	hit.setBuffer(buff_hit);

	//States
	bool up = false, down = false, w = false, s = false;

	//Variables
	bool p1 = false, p2 = false;
	bool onePlayer = false, twoPlayer = false, onMenu = true;
	//Shapes

	//Background
	RectangleShape background;
	background.setSize(Vector2f(800, 600));
	background.setPosition(0, 0);
	background.setTexture(&tex_background);

	//Pads
	_pad pad1, pad2;
	padinit(pad1, tex_pad);
	padinit(pad2, tex_pad1);
	pad1.shape.setPosition(50, 200);
	pad2.shape.setPosition(700, 200);
	//Ball
	_ball ball;
	ballinit(ball, tex_ball);

	//Main game loop
	while (window.isOpen())
	{
		// Event part on the main game loop
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Processing events
			switch (event.type)
			{
				//Case to close the window
			case Event::Closed:
				window.close();
				break;

				//Case for when a key is pressed
			case Event::KeyPressed:
				switch (event.key.code)
				{
					//Sets the boolean variables to true when key is pressed.
				case Keyboard::Up:
					up = true;
					continue;
				case Keyboard::Down:
					down = true;
					continue;
				case Keyboard::W:
					w = true;
					continue;
				case Keyboard::S:
					s = true;
					continue;
				}
				//Case for when the key is released.
			case Event::KeyReleased:
				switch (event.key.code)
				{
				case Keyboard::Up:
					up = false;
					menu.MoveUp();
					continue;
				case Keyboard::Down:
					down = false;
					menu.MoveDown();
					continue;
				case Keyboard::W:
					w = false;
					continue;
				case Keyboard::R:
					onePlayer = false;
					twoPlayer = false;
					onMenu = true;
					continue;
				case Keyboard::S:
					s = false;
					continue;
					if (onMenu)
					{
						
						case Keyboard::Return:
						switch (menu.GetPressed())
						{
						case 0:
							cout << "One Player button has been pressed \n";
							onePlayer = true;
							ball.shape.setPosition(400, 200);
							onMenu = false;
							break;
						case 1:
							cout << "Two Players button has been pressed \n";
							twoPlayer = true;
							ball.shape.setPosition(400, 200);
							onMenu = false;
							break;
						case 2:
							cout << "Exit button has been pressed";
							window.close();
							break;
						}

					}
				}
			}

		}

		//Function to determine which keys aree pressed and act accordingly
		if (onMenu)
			backgroundPlay(pad1, pad2, ball);
		else if (onePlayer)
		{
		pad1Controls(pad1, ball, w, s);
		pad2AI(pad2, ball);
		}
		else if (twoPlayer)
		{
			pad2Controls(pad2, ball, up, down);
			pad1Controls(pad1, ball, w, s);
		}
		//Out of bounds check
		outBounds(ball);

		//Collision
		collision(ball, pad1, pad2, hit);


		//Rendering part of the main game loop
		window.clear();
		
		window.draw(background);
		window.draw(pad1.shape);
		window.draw(pad2.shape);
		window.draw(ball.shape);
		if (onMenu)
			menu.draw(window);
		window.display();
		
	}
		history << "---------------------------";
		history.close();

	}
