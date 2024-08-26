#include <SFML/Graphics.hpp>
#include <cmath>

// Function to normalize a vector
sf::Vector2f normalize(const sf::Vector2f &source)
{
    float length = std::sqrt((source.x * source.x) + (source.y * source.y));
    if (length != 0)
        return sf::Vector2f(source.x / length, source.y / length);
    else
        return source;
}

void move_towards(sf::RectangleShape sprite1, sf::RectangleShape sprite2, float dtAsSeconds, float speed)
{
    sf::Vector2f targetPosition = sprite2.getPosition();

    // Calculate the direction vector from sprite1 to sprite2
    sf::Vector2f direction = targetPosition - sprite1.getPosition();
    direction = normalize(direction);

    // Move sprite1 towards sprite2
    sprite1.move(direction * speed * dtAsSeconds);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "sprite Moving Towards Another sprite");

    // Define the two sprites
    sf::RectangleShape sprite1(sf::Vector2f(50.0f, 50.0f));
    sprite1.setFillColor(sf::Color::Red);
    sprite1.setPosition(100.0f, 100.0f);

    sf::RectangleShape sprite2(sf::Vector2f(50.0f, 50.0f));
    sprite2.setFillColor(sf::Color::Blue);
    sprite2.setPosition(600.0f, 400.0f);

    sf::Clock clock;
    float speed = 100.0f; // Speed of the moving sprite in pixels per second

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sf::Time deltaTime = clock.restart();
        auto dtAsSeconds = deltaTime.asSeconds();

        // update
        move_towards(sprite1, sprite2, dtAsSeconds, speed);

        window.clear();
        window.draw(sprite1);
        window.draw(sprite2);
        window.display();
    }

    return 0;
}
