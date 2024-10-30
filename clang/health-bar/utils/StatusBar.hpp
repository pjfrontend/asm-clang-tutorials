#pragma once
#include <SFML/Graphics.hpp>

class StatusBar
{
    sf::RectangleShape redBar;
    sf::RectangleShape yellowBar;

public:
    StatusBar(sf::Vector2f position, float barWidth, float barHeight, float value, float max_value);
    ~StatusBar();
    void draw(sf::RenderWindow &window);
};
