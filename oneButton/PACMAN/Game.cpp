// platform game.....
// Author :Mark Shatalov

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

#include <SFML/Graphics.hpp> // main SFML graphics header
#include <iostream>          // for console output
#include <time.h>            // time functions
#include "Game.h"           // include the Game class definition
#include <SFML/Audio.hpp>


    Game::Game()
        :jumpSound(jumpBuffer), deathSound(deathBuffer)
    {
		randomNum = 0.0f;
        if (!jumpBuffer.loadFromFile("ASSETS/AUDIO/jumpSound.wav"))
        {
            std::cout << "Error loading jump sound!" << std::endl;
        }

        if (!deathBuffer.loadFromFile("ASSETS/AUDIO/deathSound.wav"))
        {
            std::cout << "Error loading deathh sound!" << std::endl;
        }
        window.create(sf::VideoMode({ 800, 600 }), "Endless Runner Game");
    }

    void Game::init()
    {
        scrollSpeed = 3.7f; // reset scroll speed to default on level reset
        view = window.getDefaultView(); // reset view to default
        playerShape.setSize(sf::Vector2f(20, 20)); 
        playerShape.setPosition(sf::Vector2f(160, 500)); 
        //particles.clear(); // clear particles on reset
        initLava();
       
        for (int row = 0; row < numRows; row++) // iterate grid rows
        {
            for (int col = 0; col < numCols; col++) // iterate grid columns
            {
                // set up rectangle for each cell depending on levelData value
                if (levelData[row][col] == 1) // red blocks
                {
                    level[row][col].setSize(sf::Vector2f(70, 30)); 
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color::Red);
                }
                if (levelData[row][col] == 0) // empty cells
                {
                    level[row][col].setSize(sf::Vector2f(70, 30)); 
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30)); 
                    level[row][col].setFillColor(sf::Color::Black);
                }
                if (levelData[row][col] == 2) // blue hazard blocks
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color::Blue);
                }
				if (levelData[row][col] == 3) // green speed boost blocks
                {
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
					level[row][col].setFillColor(sf::Color::Green);
					level[row][col].setOutlineColor(sf::Color::Yellow);
					level[row][col].setOutlineThickness(-2);
                }
				if (levelData[row][col] == 4) // white jump boost blocks
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color::White);
                }
                if (levelData[row][col] == 6) // win cell
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color::Yellow);
                }
            }
            std::cout << std::endl;
        }
    }
    void Game::run()
    {
        sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
        sf::Time timeSinceLastUpdate = sf::Time::Zero;
        sf::Clock clock;
        clock.restart();
        while (window.isOpen())
        {
            // check if the close window button pressed
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
            timeSinceLastUpdate += clock.restart();

            if (timeSinceLastUpdate > timePerFrame)
            {
                // reset
                timeSinceLastUpdate = sf::Time::Zero;

                // if player has won, freeze game and show win screen only
                if (gameWon) 
                {
                    // clear screen to black
                    window.clear(sf::Color::Black);

                    sf::RectangleShape winOverlay(sf::Vector2f(800, 600));
                    winOverlay.setFillColor(sf::Color(0, 180, 0, 200));
                    // draw win overlay
                    window.draw(winOverlay);

                    sf::Font font;
                    font.openFromFile("C:/motion/Motion_Graphics_ll_2026/oneButton/PACMAN/ASSETS/FONTS/Jersey20-Regular.ttf");
                    sf::Text winText(font);
					winText.setString("You Win!");
					winText.setCharacterSize(48);
					winText.setPosition(sf::Vector2f(300, 250));
					winText.setFillColor(sf::Color::White);
					window.draw(winText);
                   
                    // win screen
                    window.display();
                    continue;
                }

                // move every level rectangle leftwards to simulate scrolling
                for (int row = 0; row < numRows; row++) 
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        level[row][col].move(sf::Vector2f(-scrollSpeed, 0));
                    }
                }

                updateLava();

                // jump input if space is pressed and we are not already moving vertically
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && velocityY == 0)
                {
                    // if player is standing on a white jump pad block
                    if (onJumpPad) 
                    {
                        velocityY = -18.0f;
                        onJumpPad = false;  
                    }
                    else
                    {
                        velocityY = -11.8f;
                    }
                    // play jump sound effect
					jumpSound.play(); 
                }

                // store previos pos
                prevVelocityY = velocityY;
                // apply gravity to vertical velocity
                velocityY = velocityY + gravity;
                playerShape.move(sf::Vector2f(0, velocityY));
                gravity = 0.6;
                // reset scroll speed to base every frame before checking boosts
                scrollSpeed = 3.7f;

                // collision detection between player and level cells
                for (int row = 0; row < numRows; row++)
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        // if player is falling or stationary vertically
                        if (velocityY >= 0) 
                        {
                            // only collide with solid platforms
                            if (levelData[row][col] == 1)
                            {
                                // check if bounding boxes intersect
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                                {
                                    // if player is above the platform
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y) 
                                    {
                                        gravity = 0;
                                        velocityY = 0;
                                        // align player top to platform top
                                        playerShape.setPosition(sf::Vector2f(playerShape.getPosition().x, level[row][col].getPosition().y));
                                        // move player up by its height
                                        playerShape.move(sf::Vector2f(0, -playerShape.getGlobalBounds().size.y));

                                        // spawn only when we are falling and collides with platforms
                                        if (prevVelocityY > 0)
                                        {
                                            spawnParticles();
                                        }
                                        break;
                                    }
                                    // collided from side/bottom
                                    else {
                                        deathSound.play();
                                        spawnDeathParticles();
                                        init(); 
                                    }
                                }
                            }
                            // landing on white jump pad block
                            if (levelData[row][col] == 4) 
                            {
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                                {
                                    // player is above the pad
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y)
                                    {
                                        gravity = 0;
                                        velocityY = 0;
                                        // snap to pad top
                                        playerShape.setPosition(sf::Vector2f(playerShape.getPosition().x, level[row][col].getPosition().y)); 
                                        // move player up by its height
                                        playerShape.move(sf::Vector2f(0, -playerShape.getGlobalBounds().size.y));

                                        onJumpPad = true; 

                                        // spawn only when we are falling and collides with platforms
                                        if (prevVelocityY > 0)
                                        {
                                            spawnParticles();
                                        }
                                        break;
                                    }
                                }
                            }
                            // landing on green speed boost block
                            if (levelData[row][col] == 3)
                            {
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                                {
                                    // player is above the block
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y)
                                    {
                                        gravity = 0;   
                                        velocityY = 0;
                                        // snap to block top
                                        playerShape.setPosition(sf::Vector2f(playerShape.getPosition().x, level[row][col].getPosition().y));
                                        // move player up by its height
                                        playerShape.move(sf::Vector2f(0, -playerShape.getGlobalBounds().size.y));
                                        // increase scroll speed while standing on green block
                                        scrollSpeed = scrollSpeed * speedBuff;

                                        // spawn only when we are falling and collides with platforms
                                        if (prevVelocityY > 0)

                                        {
                                            spawnParticles();
                                        }
                                        break;
                                    }
									// reset if we hit the block from the side or bottom
                                    else
                                    {
                                        deathSound.play();
                                        spawnDeathParticles();
                                        init(); 
                                    }
                                }
                            }
                        }
                        // if player is jump
                        if (velocityY < 0) 
                        {
                            // check against solids
                            if (levelData[row][col] == 1) 
                            {
                                // head hit platform
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds())) 
                                {
                                    deathSound.play();
                                    spawnDeathParticles();
                                    // reset level
                                    init(); 
                                }
                            }
                        }
                        // hazard cells
                        if (levelData[row][col] == 2) 
                        {
                            if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                            {
                                deathSound.play();
                                spawnDeathParticles();
                                // reset 
                                init(); 
                            }
                        }
                        // yellow win cell
                        if (levelData[row][col] == 6) 
                        {
                            if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                            {
                                gameWon = true;
                            }
                        }
                    }
                }
                // fell off bottom of screen
                if (playerShape.getPosition().y > 600) 
                {
                    deathSound.play();
                    spawnDeathParticles();
                    // reset level
                    init(); 
                }

                // update particles
                for (auto& p : particles)
                {
                    // to do a gravity for particles 
                    p.vx *= 0.9f;
                    p.vy += 0.3f;
                    p.lifetime -= 1.0f / 60.0f;

                    if (p.isCircle)
                    {
                        p.circleShape.move(sf::Vector2f(p.vx, p.vy));
                    }
                    else
                    {
                        p.shape.move(sf::Vector2f(p.vx, p.vy));
                    }
                }

				// remove particles if time is finished
                for (int i = particles.size() - 1; i >= 0; i--)
                {
                    if (particles[i].lifetime <= 0)
                    {
                        particles.erase(particles.begin() + i);
                    }
                }

                window.clear();
                // draw every cell
                for (int row = 0; row < numRows; row++) 
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        window.draw(level[row][col]);
                    }
                }

                // draw particles below player
                for (auto& p : particles)
                {
                    if (p.isCircle)
                    {
                        window.draw(p.circleShape);
                    }
                    else
                    {
                        window.draw(p.shape);
                    }
                }
                for (int i = 0; i < LAVA_COUNT; i++)
                {
                    window.draw(lavaShape[i]);
                }

                window.draw(playerShape); 
                window.display();
            }
        }
    }

    void Game::spawnParticles()
    {
        // spawn landing particles
        for (int i = 0; i < 8; i++)
        {
            Particle p;
            p.shape.setSize(sf::Vector2f(4, 4));
            p.shape.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));
            p.shape.setPosition(sf::Vector2f(playerShape.getPosition().x + 10, playerShape.getPosition().y + 20));
            p.vx = (rand() % 7 - 3) * 1.0f;
            p.vy = -(rand() % 4 + 1) * 1.0f;
            p.lifetime = 1.0f;
            particles.push_back(p);
        }
    }

    void Game::spawnDeathParticles()
    {
        sf::Color redColors[3] = {
            sf::Color(255, 0, 0),      // red
            sf::Color(139, 0, 0),      // dark red
            sf::Color(255, 99, 99)     // light red
        };

        // spawn landing circle particles
        for (int i = 0; i < 20; i++)
        {
            Particle p;
            p.isCircle = true;
            p.circleShape.setRadius(5.0f);
            p.circleShape.setFillColor(redColors[rand() % 3]); 
            p.circleShape.setPosition(sf::Vector2f(playerShape.getPosition().x + 10, playerShape.getPosition().y + 10));
            p.vx = (rand() % 11 - 5) * 1.2f;
            p.vy = (rand() % 11 - 5) * 1.2f;
            p.lifetime = 1.2f;
            particles.push_back(p);
        }
    }


    // init lava
    void Game::initLava()
    {
        // track current lava tile 
        int idx = 0;
        for (int row = 0; row < numRows && idx < LAVA_COUNT; row++)
        {
            for (int col = 0; col < numCols && idx < LAVA_COUNT; col++)
            {
                if (levelData[row][col] == 5)
                {
                    lavaX[idx] = col * 70.f;
                    lavaY[idx] = row * 30.f;
                    // set speed
                    lavaVelX[idx] = 3.0f;

                    lavaShape[idx].setSize(sf::Vector2f(70, 30));
                    lavaShape[idx].setFillColor(sf::Color(255, 130, 0));
                    lavaShape[idx].setPosition(sf::Vector2f(lavaX[idx], lavaY[idx]));

                    idx++;
                }
            }
        }
    }

    void Game::updateLava()
    {
        for (int i = 0; i < LAVA_COUNT; i++)
        {
            // scroll with the world
            lavaX[i] -= scrollSpeed;

            // apply bounce
            // if positive moves rigth if negative - left
            lavaX[i] += lavaVelX[i];

            // update shape position
            lavaShape[i].setPosition(sf::Vector2f(lavaX[i], lavaY[i]));

            // check collision with red tiles
            for (int row = 0; row < numRows; row++)
            {
                for (int col = 0; col < numCols; col++)
                {
                    if (levelData[row][col] != 1)
                    {
                        continue;
                    }
                    
                    if (lavaShape[i].getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                    {
                        // reverse direction and step back
                        lavaVelX[i] = -lavaVelX[i];
                        lavaX[i] += lavaVelX[i];
                        lavaShape[i].setPosition(sf::Vector2f(lavaX[i], lavaY[i]));
                        break;
                    }
                }
            }

            // check if player touches lava
            if (playerShape.getGlobalBounds().findIntersection(lavaShape[i].getGlobalBounds()))
            {
                deathSound.play();
                spawnDeathParticles();
                init();
                return;
            }
        }
    }

   

int main()
{
    Game game; 
    game.init();
    game.run(); 
    return 0;
}