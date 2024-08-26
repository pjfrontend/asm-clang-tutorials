// https://stackoverflow.com/questions/61447069/sfml-window-resizing-is-very-ugly
#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);
    // create own view
    sf::View view = window.getDefaultView();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            if (event.type == sf::Event::Resized)
            {
                // resize my view
                view.setSize({static_cast<float>(event.size.width),
                              static_cast<float>(event.size.height)});
                window.setView(view); // and align shape
            }
        }

        window.clear();
        window.draw(shape);
        window.display();
    }

    return 0;
}