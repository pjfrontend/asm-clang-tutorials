#pragma once
#include <SFML/Graphics.hpp>

class Bat
{
private:
    sf::Vector2f position;

    // A RectangleShape object
    sf::RectangleShape batShape;

    float batSpeed = .7f;

public:
    Bat(float startX, float startY);

    sf::FloatRect getPosition();

    sf::RectangleShape getShape();

    void moveLeft();

    void moveRight();

    void update();
};