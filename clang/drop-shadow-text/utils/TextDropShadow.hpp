#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class TextDropShadow
{
    sf::Font font;
    sf::Text txt;
    sf::Text shadow;
    std::string fontname;
    const int offset = 2;

public:
    std::string message;
    unsigned int size;
    sf::Vector2i pos = {0, 0};

    TextDropShadow(std::string message,
                   std::string fontname,
                   sf::Vector2i pos,
                   unsigned int size) : message(message),
                                        fontname(fontname),
                                        pos(pos),
                                        size(size)
    {
        font.loadFromFile(fontname);
        txt.setFont(font);
        txt.setCharacterSize(size);
        txt.setFillColor(sf::Color::White);
        txt.setString(message);
        txt.setPosition(pos.x, pos.y);

        shadow.setFont(font);
        shadow.setCharacterSize(size);
        shadow.setFillColor(sf::Color::Black);
        shadow.setString(message);
        shadow.setPosition(pos.x + offset, pos.y + offset);
    }

    void draw(sf::RenderWindow *window)
    {
        window->draw(shadow);
        window->draw(txt);
    }
};