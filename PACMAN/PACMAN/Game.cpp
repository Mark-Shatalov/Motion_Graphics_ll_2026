//Mark Shatalov
//Animation with pacman

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Game.h"
#include "ScreenSize.h"

void setCirclesPos(const int t_numCircles, sf::CircleShape t_circles[], int t_circleStartPos)
{

	//circles[0].setPosition(sf::Vector2f(circleStartPos, 300));

	int randomBuff = rand() % t_numCircles;

	for (int index = 0; index < t_numCircles; index++)
	{
		t_circles[index].setFillColor(sf::Color::White);
		t_circles[index].setRadius(10);
		t_circles[index].setOrigin(sf::Vector2f(10, 10));

		//if(circles[index])	
		float x = static_cast<float>(t_circleStartPos) * (index + 1);
		t_circles[index].setPosition(sf::Vector2f(x, 300));


		if (randomBuff == index)
		{
			t_circles[randomBuff].setFillColor(sf::Color::Yellow);
			t_circles[randomBuff].setRadius(15);
			t_circles[randomBuff].setOrigin(sf::Vector2f(15, 15));
		}
	}
}

//recreate the game ..
//
//https://abagames.github.io/crisp-game-lib-11-games/?pakupaku
// see blackboard for sample sprites.
// 
int main()
{

	sf::RenderWindow window(sf::VideoMode({ ScreenSize::s_width, ScreenSize::s_height }, 32), "Sprites", sf::Style::Default);

	srand(time(NULL));

	window.setFramerateLimit(60);
	sf::RectangleShape simpleRectangle;
	float width = 30;
	float height = 30;

	sf::Texture pacman3tex;
	sf::Texture backgroundTex;
	sf::Texture enemyTex;
	if (!pacman3tex.loadFromFile("ASSETS//IMAGES//pacman3.png"))
	{
		// error...
		std::cout << "error witg loading pacman3\n";
	}
	if(!backgroundTex.loadFromFile("ASSETS//IMAGES//pacmanBackground.png"))
	{
		// error...
		std::cout << "error witg loading pacmanBackground\n";
	}
	if (!enemyTex.loadFromFile("ASSETS//IMAGES//enemy.png"))
	{
		// error...
		std::cout << "error witg loading pacmanBackground\n";
	}
	sf::Sprite backgroundSprite(backgroundTex);
	sf::Sprite pacmanSprite(pacman3tex);
	sf::Sprite enemySprite(enemyTex);

	pacmanSprite.setTextureRect(sf::IntRect({ 0,0 }, { 32, 32 }));
	pacmanSprite.setOrigin(sf::Vector2f(0.5, 0.5));

	backgroundSprite.setTextureRect(sf::IntRect({ 314,131 }, { 52,18 }));
	backgroundSprite.setPosition(sf::Vector2f(0, 255));
	backgroundSprite.setScale({16,5});

	simpleRectangle.setSize(sf::Vector2f(width, height));

	simpleRectangle.setFillColor(sf::Color::Red);

	simpleRectangle.setPosition(sf::Vector2f(100, 200));

	sf::Vector2f enemyRow = { 0,64 };
	enemySprite.setTextureRect(sf::IntRect({ 0,64 }, { 15,15 })); //457
	enemySprite.setScale(sf::Vector2f(3, 3));


	const int numCircles = 15;
	sf::CircleShape circles[numCircles];
	int circleStartPos = 50;
	setCirclesPos(numCircles, circles, circleStartPos);

	

	float xPosition = 300;
	float yPosition = 700;
	float speed = 1;
	bool spacePressed = false;
	int pacmanframesPerSecond = 10;
	int pacmanNumFramesinAnim = 3;
	int pacmanFrame = 0;
	int pacmanFrameCounter = 0;
	int pacmanWidth = 32;
	int pacmanHeight = 32;
	int eatenCount = 0;

	float enemyXPosition = 500;
	float enemyYPosition = 700;

	float enemySpeed = 1.2f;
	int enemyFramesPerSecond = 5;
	int enemyNumFramesinAnim = 2;
	int enemyFrame = 0;
	int enemyFrameCounter = 0;
	int enemyWidth = 15;
	int enemyHeight = 15;


	while (window.isOpen())
	{
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
			else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
			{
				if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
					window.close();
			}
		}





		if (pacmanFrameCounter >= 60 / pacmanframesPerSecond)
		{
			if (pacmanFrame < pacmanNumFramesinAnim - 1)
			{
				pacmanFrame++;
			}
			else {
				pacmanFrame = 0;
			}
			pacmanFrameCounter = 0;
		}
		else {
			pacmanFrameCounter++;
		}

		if (enemyFrameCounter >= 60 / enemyFramesPerSecond)
		{
			if (enemyFrame < enemyNumFramesinAnim - 1)
			{
				enemyFrame++;
			}
			else
			{
				enemyFrame = 0;
			}
			enemyFrameCounter = 0;
		}
		else
		{
			enemyFrameCounter++;
		}

		// Calculate the texture rectangle for the current frame
		int left = pacmanFrame * pacmanWidth;
		int top = 0; // Assuming all frames are in a single row
		pacmanSprite.setTextureRect(sf::IntRect({ left,top }, { pacmanWidth, pacmanHeight }));
		pacmanSprite.setOrigin(sf::Vector2f(16, 16));
		if (speed < 0)
		{
			pacmanSprite.setScale(sf::Vector2f(-1, -1));
		}
		else {
			pacmanSprite.setScale(sf::Vector2f(1, 1));
		}
		if (speed < 0)
		{

		}

		/*if (enemySpeed < 0)
		{
			enemySprite.setScale(sf::Vector2f(3, 3));
		}
		else
		{
			enemySprite.setScale(sf::Vector2f(-3, 3));
		}*/

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space))
		{
			if (spacePressed == false)
			{
				speed *= -1;
				spacePressed = true;
			}
		}
		else {
			spacePressed = false;
		}


	

		int enemyLeft = enemyRow.x + (enemyFrame * enemyWidth);
		int enemyTop = enemyRow.y;
		enemySprite.setTextureRect(sf::IntRect({ enemyLeft,enemyTop }, { enemyWidth, enemyHeight }));
		enemySprite.setOrigin(sf::Vector2f(7.5, 7.5));



		xPosition += speed;
		
		pacmanSprite.setPosition(sf::Vector2f(xPosition, yPosition - 400));
		enemySprite.setPosition(sf::Vector2f(enemyXPosition, enemyYPosition - 400));

		float dirX = xPosition - enemyXPosition;
		float dirY = yPosition - enemyYPosition;
		float distance = std::sqrt((dirX * dirX) + (dirY * dirY));

		if (distance > 0)
		{
			dirX /= distance;
			dirY /= distance;

			if (enemySpeed < 1.2f)
			{
				enemyXPosition += dirX * -enemySpeed;
				if (xPosition > enemyXPosition) enemySprite.setScale({ -3.0f,3.0f }); 
				else enemySprite.setScale({ 3.0f,3.0f });
			}
			else
			{
				enemyXPosition += dirX * enemySpeed;
				if (xPosition > enemyXPosition) enemySprite.setScale({ 3.0f,3.0f }); 
				else enemySprite.setScale({ -3.0f,3.0f });

			}
			enemyYPosition += dirY * enemySpeed;
		}


		for (int index = 0; index < numCircles; index++)
		{
			if (pacmanSprite.getGlobalBounds().findIntersection(circles[index].getGlobalBounds()))
			{
				circles[index].setPosition(sf::Vector2f(1000, 1000));
				eatenCount++;
			}

		}

		if (eatenCount >= numCircles)
		{
			setCirclesPos(numCircles, circles, circleStartPos);
			eatenCount = 0;
		}

		sf::Vector2u windowSize = window.getSize();

		unsigned int windowSizeX = windowSize.x;

		float sizeX = static_cast<float>(windowSizeX);

		if (pacmanSprite.getPosition().x >= sizeX + pacmanWidth)
		{
			xPosition = 0;
			pacmanSprite.setPosition(sf::Vector2f(xPosition, yPosition));
		}
		if (pacmanSprite.getPosition().x <= 0 - pacmanWidth)
		{
			xPosition = sizeX;
			pacmanSprite.setPosition(sf::Vector2f(xPosition, yPosition));
		}



		window.clear();

		window.draw(backgroundSprite);

		for (int index = 0; index < numCircles; index++)
		{

			window.draw(circles[index]);

		}


		//window.draw(simpleRectangle);


		
		window.draw(pacmanSprite);
		window.draw(enemySprite);

		window.display();



	}

	return 0;
}


