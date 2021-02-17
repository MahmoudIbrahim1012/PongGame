#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

using namespace sf;


struct _pad
{
	int yVelocity;
	Texture padTex;
	sf::RectangleShape shape;
};

struct _ball
{
	int yVelocity = -4, xVelocity = -4;
	Texture padTex;
	sf::CircleShape shape;
};


//Initialize pads
void padinit(_pad& pad, Texture& tex_pad)
{
	pad.yVelocity = 0;
	pad.shape.setSize(Vector2f(60, 100));
	pad.shape.setTexture(&tex_pad);

}
void ballinit(_ball& ball, Texture& tex_ball)
{
	ball.xVelocity = -4, ball.yVelocity = -4;
	ball.shape.setRadius(20);
	ball.shape.setPosition(400, 200);
	ball.shape.setTexture(&tex_ball);
}

void collision(_ball& ball, _pad& pad1, _pad& pad2, Sound& hit)
{

	//Collision
	if (ball.shape.getGlobalBounds().intersects(pad2.shape.getGlobalBounds()) and ball.shape.getPosition().x > 700)
	{
		ball.xVelocity = -ball.xVelocity;
		ball.yVelocity = -ball.yVelocity;
		hit.play();
	}
	if (ball.shape.getGlobalBounds().intersects(pad1.shape.getGlobalBounds()))
	{
		ball.xVelocity = -ball.xVelocity;
		hit.play();
	}
	if (ball.shape.getGlobalBounds().intersects(pad2.shape.getGlobalBounds()))
	{
		ball.xVelocity = -ball.xVelocity;
		hit.play();
	}

}

/*Returns zero if ball not out of bound
One if p1 scores
Two if p2 scores*/
int outBounds(_ball& ball)
{

	if (ball.shape.getPosition().y < 0 or ball.shape.getPosition().y>550)
	{
		ball.yVelocity = -ball.yVelocity;
	}
	if (ball.shape.getPosition().x > 800)
	{
		ball.shape.setPosition(300, 200);
		return 1;
	}
	else if (ball.shape.getPosition().x < -50)
	{
		ball.shape.setPosition(300, 200);
		return 2;
	}
	else
		return 0;
}

void pad1Controls(_pad& pad1, _ball& ball, bool w, bool s)
{

	//Logic handling
		// Pad 1 player
					//Pad1
	if (w)
	{
		pad1.yVelocity = -5;
	}
	if (s)
	{
		pad1.yVelocity = 5;
	}
	if (w && s or !w and !s)
	{
		pad1.yVelocity = 0;
	}

	pad1.shape.move(0, pad1.yVelocity);

	//Out of bounds
	if (pad1.shape.getPosition().y < 0 or pad1.shape.getPosition().y > 500)
	{
		pad1.shape.move(0, -pad1.yVelocity);
	}
	


	//Ball
	ball.shape.move(ball.xVelocity, ball.yVelocity);
}
void pad2Controls(_pad& pad2, _ball& ball, bool up, bool down)
{
	//Pad2
	if (up)
	{
		pad2.yVelocity = -5;
	}
	if (down)
	{
		pad2.yVelocity = 5;
	}
	if (up && down or !up and !down)
	{
		pad2.yVelocity = 0;
	}

	pad2.shape.move(0, pad2.yVelocity);

	//Out of bounds
	if (pad2.shape.getPosition().y < 0 or pad2.shape.getPosition().y > 500)
	{
		pad2.shape.move(0, -pad2.yVelocity);
	}

}
void pad2AI(_pad& pad2, _ball ball)
{

if (ball.shape.getPosition().y < pad2.shape.getPosition().y)
{
	pad2.yVelocity = -2;
}
if (ball.shape.getPosition().y > pad2.shape.getPosition().y)
{
	pad2.yVelocity = 2;
}

pad2.shape.move(0, pad2.yVelocity);
}
void backgroundPlay(_pad& pad1, _pad& pad2, _ball& ball)
{
	//Ball
	ball.shape.move(ball.xVelocity, ball.yVelocity);
	if (ball.shape.getPosition().y < pad1.shape.getPosition().y)
	{
		pad1.yVelocity = -2;
	}
	if (ball.shape.getPosition().y > pad1.shape.getPosition().y)
	{
		pad1.yVelocity = 2;
	}

	pad1.shape.move(0, pad1.yVelocity);

	if (ball.shape.getPosition().y < pad2.shape.getPosition().y)
	{
		pad2.yVelocity = -2;
	}
	if (ball.shape.getPosition().y > pad2.shape.getPosition().y)
	{
		pad2.yVelocity = 2;
	}


	pad2.shape.move(0, pad2.yVelocity);
}

/*
		//Score
		std::stringstream text;
		text << pad1Score << " : " << pad2Score;
		score.setString(text.str());
		window.draw(score);

		if (pad1Score == 5)
		{
			window.draw(p1win);
			ball.xVelocity = 0;
			ball.yVelocity = 0;
		}
		if (pad2Score == 5)
		{
			window.draw(p2win);
			ball.xVelocity = 0;
			ball.yVelocity = 0;
		}

		window.display();
	}

	if (pad1Score == 5)
	{
		window.draw(p1win);
		ball.xVelocity = 0;
		ball.yVelocity = 0;
		history << "Player one wins, player two's score is: " << pad2Score << endl;
	}
	if (pad2Score == 5)
	{
		window.draw(p2win);
		ball.xVelocity = 0;
		ball.yVelocity = 0;
		history << "Player two wins, player one's score is: " << pad1Score << endl;
	}
		*/