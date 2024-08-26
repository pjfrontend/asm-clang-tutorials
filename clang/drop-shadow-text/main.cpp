#include <SFML/Graphics.hpp>
#include "utils/TextDropShadow.hpp"

const static std::string FONT_NAME = "Roboto-Regular.ttf";

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Drop shadow text");

    TextDropShadow t = TextDropShadow("hello world", "Roboto-Regular.ttf", {0, 0}, 64);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear(sf::Color::Blue);
        t.draw(&window);
        window.display();
    }

    return 0;
}