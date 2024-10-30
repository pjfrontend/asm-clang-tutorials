#include "StatusBar.hpp"

StatusBar::StatusBar(sf::Vector2f position,
                     float barWidth, float barHeight,
                     float value, float max_value)
{
    // Create the red background (max health)
    redBar = sf::RectangleShape(sf::Vector2f(barWidth, barHeight));
    redBar.setFillColor(sf::Color::Red);
    redBar.setPosition(position); // Position of the health bar

    // Calculate the width of the yellow bar based on current health
    float yellowBarWidth = (value / max_value) * barWidth;

    // Create the yellow foreground (current health)
    yellowBar = sf::RectangleShape(sf::Vector2f(yellowBarWidth, barHeight));
    yellowBar.setFillColor(sf::Color::Yellow);
    yellowBar.setPosition(position); // Same position as red bar
}

StatusBar::~StatusBar()
{
}

void StatusBar::draw(sf::RenderWindow &window)
{
    window.draw(redBar);
    window.draw(yellowBar);
}