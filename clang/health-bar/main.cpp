#include <SFML/Graphics.hpp>
#include "utils/StatusBar.hpp"

int main()
{
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Health Bar Example");

    // Health values
    float maxHealth = 100.0f;
    float currentHealth = 75.0f; // Change this to simulate different health levels

    // Bar dimensions
    float barWidth = 300.0f;
    float barHeight = 25.0f;
    StatusBar bar = StatusBar(sf::Vector2f(0, 0), barWidth, barHeight, currentHealth, maxHealth);

    // Game loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Clear the window
        window.clear(sf::Color::Black);

        // Draw the health bar
        bar.draw(window);

        // Display the updated window
        window.display();
    }

    return 0;
}
