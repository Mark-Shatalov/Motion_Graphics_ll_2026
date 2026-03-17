// platform game.....
// Author :Mark Shatalov

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") // link debug SFML graphics lib
#pragma comment(lib,"sfml-audio-d.lib")    // link debug SFML audio lib
#pragma comment(lib,"sfml-system-d.lib")   // link debug SFML system lib
#pragma comment(lib,"sfml-window-d.lib")   // link debug SFML window lib
#pragma comment(lib,"sfml-network-d.lib")  // link debug SFML network lib
#else 
#pragma comment(lib,"sfml-graphics.lib")   // link release SFML graphics lib
#pragma comment(lib,"sfml-audio.lib")      // link release SFML audio lib
#pragma comment(lib,"sfml-system.lib")     // link release SFML system lib
#pragma comment(lib,"sfml-window.lib")     // link release SFML window lib
#pragma comment(lib,"sfml-network.lib")    // link release SFML network lib
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

       
        for (int row = 0; row < numRows; row++) // iterate grid rows
        {
            for (int col = 0; col < numCols; col++) // iterate grid columns
            {
                // set up rectangle for each cell depending on levelData value
                if (levelData[row][col] == 1) // red blocks
                {
                    level[row][col].setSize(sf::Vector2f(70, 30)); // platform size
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30)); // col = X, row = Y
                    level[row][col].setFillColor(sf::Color::Red); // solid platform color
                }
                if (levelData[row][col] == 0) // empty cells
                {
                    level[row][col].setSize(sf::Vector2f(70, 30)); // empty cell size
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30)); // position
                    level[row][col].setFillColor(sf::Color::Black); // background color for empty
                }
                if (levelData[row][col] == 2) // blue hazard blocks
                {
                    level[row][col].setSize(sf::Vector2f(70, 30)); // hazard size
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30)); // position
                    level[row][col].setFillColor(sf::Color::Blue); // hazard color
                }
				if (levelData[row][col] == 3) // green speed boost blocks
                {
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
					level[row][col].setFillColor(sf::Color::Green); // speed boost which increases scroll speed
					level[row][col].setOutlineColor(sf::Color::Yellow); // add yellow outline
					level[row][col].setOutlineThickness(-2); // make outline thicker for visibility
                }
				if (levelData[row][col] == 4) // white jump boost blocks
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color::White);  // jumpad which gives extra jump height
                }
                if (levelData[row][col] == 5)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color(255, 100, 0)); // create a lava cell 
                }
                if (levelData[row][col] == 6)
                {
                    level[row][col].setSize(sf::Vector2f(70, 30));
                    level[row][col].setPosition(sf::Vector2f(col * 70, row * 30));
                    level[row][col].setFillColor(sf::Color::Yellow); // create a win cell 
                }
            }
            std::cout << std::endl; // newline for console
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
            // check if the close window button is clicked on
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
                timeSinceLastUpdate = sf::Time::Zero; // reset accumulator

                if (gameWon) // if player has won, freeze game and show win screen only
                {
                    window.clear(sf::Color::Black); // clear screen to black

                    sf::RectangleShape winOverlay(sf::Vector2f(800, 600));
                    winOverlay.setFillColor(sf::Color(0, 180, 0, 200));
                    window.draw(winOverlay); // draw win overlay

                    sf::Font font;
                    font.openFromFile("C:/motion/Motion_Graphics_ll_2026/oneButton/PACMAN/ASSETS/FONTS/Jersey20-Regular.ttf");
                    sf::Text winText(font);
					winText.setString("You Win!");
					winText.setCharacterSize(48);
					winText.setPosition(sf::Vector2f(300, 250)); // center text on screen
					winText.setFillColor(sf::Color::White);
					window.draw(winText); // draw win text
                   

                    window.display(); // win screen
                    continue;         // skip 
                }

                for (int row = 0; row < numRows; row++) // move every level rectangle leftwards to simulate scrolling
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        level[row][col].move(sf::Vector2f(-scrollSpeed, 0)); // scroll speed
                    }
                }
                // jump input: if space is pressed and we are not already moving vertically
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space) && velocityY == 0)
                {
                    if (onJumpPad) // if player is standing on a white jump pad block
                    {
                        velocityY = -18.0f; // boosted jump 
                        onJumpPad = false;  // reset jump pad flag after jumping
                    }
                    else
                    {
                        velocityY = -11.8f;
                    }
					jumpSound.play(); // play jump sound effect
                }

                velocityY = velocityY + gravity; // apply gravity to vertical velocity
                playerShape.move(sf::Vector2f(0, velocityY)); // move player vertically
                gravity = 0.6; // default gravity value
                scrollSpeed = 3.7f; // reset scroll speed to base every frame before checking boosts

                // collision detection between player and level cells
                for (int row = 0; row < numRows; row++)
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        if (velocityY >= 0) // if player is falling or stationary vertically
                        {
                            if (levelData[row][col] == 1) // only collide with solid platforms
                            {
                                // check if bounding boxes intersect
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                                {
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y) // if player is above the platform
                                    {
                                        gravity = 0; // stop gravity
                                        velocityY = 0; // stop vertical movement
                                        playerShape.setPosition(sf::Vector2f(playerShape.getPosition().x, level[row][col].getPosition().y)); // align player top to platform top
                                        playerShape.move(sf::Vector2f(0, -playerShape.getGlobalBounds().size.y)); // move player up by its height
                                        break;
                                    }
                                    else {
                                        deathSound.play();
                                        init(); // collided from side/bottom
                                    }
                                }
                            }
                            // landing on white jump pad block
                            if (levelData[row][col] == 4) 
                            {
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                                {
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y) // player is above the pad
                                    {
                                        gravity = 0; // stop gravity while standing on pad
                                        velocityY = 0; // stop vertical movement, player stands on pad
                                        playerShape.setPosition(sf::Vector2f(playerShape.getPosition().x, level[row][col].getPosition().y)); // snap to pad top
                                        playerShape.move(sf::Vector2f(0, -playerShape.getGlobalBounds().size.y)); // sit on pad surface
                                        onJumpPad = true; // flag that player is on a jump pad
                                        break;
                                    }
                                }
                            }
                            // landing on green speed boost block
                            if (levelData[row][col] == 3)
                            {
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds()))
                                {
                                    if (playerShape.getPosition().y < level[row][col].getPosition().y) // player is above the block
                                    {
                                        gravity = 0;   // stop gravity while standing on block
                                        velocityY = 0; // stop vertical movement
                                        playerShape.setPosition(sf::Vector2f(playerShape.getPosition().x, level[row][col].getPosition().y)); // snap to block top
                                        playerShape.move(sf::Vector2f(0, -playerShape.getGlobalBounds().size.y)); // sit on block surface
                                        scrollSpeed = scrollSpeed * speedBuff; // increase scroll speed by 1.3x while standing on green block
                                        break;
                                    }
                                    else
                                    {
                                        deathSound.play();
                                        init(); // hit from side/bottom -> reset
                                    }
                                }
                            }
                        }
                        if (velocityY < 0) // if player is jump
                        {
                            if (levelData[row][col] == 1) // check against solids
                            {
                                if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds())) // head hit platform
                                {
                                    deathSound.play();
                                    init(); // reset level on head collision
                                }
                            }
                        }
                        if (levelData[row][col] == 2) // hazard cells
                        {
                            if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds())) // touching hazard
                            {
                                deathSound.play();
                                init(); // reset on hazard contact
                            }
                        }
                        if (levelData[row][col] == 6) // yellow win cell
                        {
                            if (playerShape.getGlobalBounds().findIntersection(level[row][col].getGlobalBounds())) // player touches win cell
                            {
                                gameWon = true; // set win flag
                            }
                        }
                    }
                }
                if (playerShape.getPosition().y > 600) // fell off bottom of screen
                {
                    deathSound.play();
                    init(); // reset level
                }
                window.clear();
                for (int row = 0; row < numRows; row++) // draw every cell
                {
                    for (int col = 0; col < numCols; col++)
                    {
                        window.draw(level[row][col]); // draw cell rectangle
                    }
                }
                window.draw(playerShape); // draw player on top
                window.display();         // present the rendered frame to the screen
            }
        }
    }


int main()
{
    Game game; // construct game object
    game.init(); // initialize level and player
    game.run(); // enter main loop
    return 0; // return success
}