// https://gamecodeschool.com/sfml/coding-a-simple-pong-game-with-sfml/
#include "Bat.hpp"
#include "Ball.hpp"
#include <sstream>
#include <cstdlib>
#include <SFML/Graphics.hpp>

// This is where our game starts from
int main()
{
    int windowWidth = 800;
    int windowHeight = 600;
    // Make a window that is 1024 by 768 pixels
    // And has the title "Pong"
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), "Pong");
    sf::View view = window.getDefaultView();

    int score = 0;
    int lives = 3;

    // create a bat
    Bat bat(windowWidth / 2, windowHeight - 20);

    // create a ball
    Ball ball(windowWidth / 2, 1);

    // Create a "Text" object called "message". Weird but we will learn about objects soon
    sf::Text hud;

    // We need to choose a font
    sf::Font font;
    // http://www.dafont.com/theme.php?cat=302
    font.loadFromFile("DS-DIGIT.ttf");

    // Set the font to our message
    hud.setFont(font);

    // Make it really big
    hud.setCharacterSize(75);

    // Choose a color
    hud.setFillColor(sf::Color::White);

    // This "while" loop goes round and round- perhaps forever
    while (window.isOpen())
    {
        /*
            Handle the player input
            *********************************************************************
            *********************************************************************
            *********************************************************************
        */

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                view.setSize({static_cast<float>(event.size.width),
                              static_cast<float>(event.size.height)});
                window.setView(view);
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            // move left...
            bat.moveLeft();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            // move right...
            bat.moveRight();
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
        {
            // quit...
            // Someone closed the window- bye
            window.close();
        }

        /*
        Update the frame
        *********************************************************************
        *********************************************************************
        *********************************************************************
    */

        // Handle ball hitting the bottom
        if (ball.getPosition().top > windowHeight)
        {
            // reverse the ball direction
            ball.hitBottom();

            // Remove a life
            lives--;

            // Check for zero lives
            if (lives < 1)
            {
                // reset the score
                score = 0;
                // reset the lives
                lives = 3;
            }
        }

        // Handle ball hitting top
        if (ball.getPosition().top < 0)
        {
            ball.reboundBatOrTop();

            // Add a point to the players score
            score++;
        }

        // Handle ball hitting sides
        if (ball.getPosition().left < 0 || ball.getPosition().left + 10 > windowWidth)
        {
            ball.reboundSides();
        }

        // Has the ball hit the bat?
        if (ball.getPosition().intersects(bat.getPosition()))
        {
            // Hit detected so reverse the ball and score a point
            ball.reboundBatOrTop();
        }

        ball.update();
        bat.update();

        // Update the HUD text
        std::stringstream ss;
        ss << "Score:" << score << "    Lives:" << lives;
        hud.setString(ss.str());

        /*
                   Draw the frame
                   *********************************************************************
                   *********************************************************************
                   *********************************************************************
               */

        // Clear everything from the last frame
        window.clear(sf::Color(26, 128, 182, 255));

        window.draw(bat.getShape());

        window.draw(ball.getShape());

        // Draw our score
        window.draw(hud);

        // Show everything we just drew
        window.display();
    } // This is the end of the "while" loop

    return 0;
}