#include <SFML/Graphics.hpp>
#include <vector>

// Function to calculate points along a cubic Bezier curve
std::vector<sf::Vector2f> CalcCubicBezier(
    const sf::Vector2f &start,
    const sf::Vector2f &end,
    const sf::Vector2f &startControl,
    const sf::Vector2f &endControl,
    const size_t numSegments)
{
    std::vector<sf::Vector2f> ret;
    if (!numSegments)
        return ret;

    ret.push_back(start);
    float p = 1.f / numSegments;
    float q = p;
    for (size_t i = 1; i < numSegments; i++, p += q)
        ret.push_back(p * p * p * (end + 3.f * (startControl - endControl) - start) +
                      3.f * p * p * (start - 2.f * startControl + endControl) +
                      3.f * p * (startControl - start) + start);
    ret.push_back(end);
    return ret;
}

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // Window setup
    sf::RenderWindow window(sf::VideoMode(800, 600), "Interactive Cubic Bezier Curve", sf::Style::Default, settings);

    // Initial positions for Bezier points, centered
    sf::Vector2f startPoint(250, 300);
    sf::Vector2f endPoint(550, 300);
    sf::Vector2f startControl(300, 100);
    sf::Vector2f endControl(500, 500);

    // Create control points as circles
    sf::CircleShape startCircle(8);
    startCircle.setFillColor(sf::Color::Red);
    startCircle.setOrigin(8, 8);
    startCircle.setPosition(startPoint);

    sf::CircleShape endCircle(8);
    endCircle.setFillColor(sf::Color::Blue);
    endCircle.setOrigin(8, 8);
    endCircle.setPosition(endPoint);

    sf::CircleShape startControlCircle(8);
    startControlCircle.setFillColor(sf::Color::Green);
    startControlCircle.setOrigin(8, 8);
    startControlCircle.setPosition(startControl);

    sf::CircleShape endControlCircle(8);
    endControlCircle.setFillColor(sf::Color::Yellow);
    endControlCircle.setOrigin(8, 8);
    endControlCircle.setPosition(endControl);

    // Variables to track dragging of circles
    sf::CircleShape *selectedCircle = nullptr;
    sf::Vector2f *selectedPoint = nullptr;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                // Check if the mouse pressed on any of the circles
                if (startCircle.getGlobalBounds().contains(mousePos))
                {
                    selectedCircle = &startCircle;
                    selectedPoint = &startPoint;
                }
                else if (endCircle.getGlobalBounds().contains(mousePos))
                {
                    selectedCircle = &endCircle;
                    selectedPoint = &endPoint;
                }
                else if (startControlCircle.getGlobalBounds().contains(mousePos))
                {
                    selectedCircle = &startControlCircle;
                    selectedPoint = &startControl;
                }
                else if (endControlCircle.getGlobalBounds().contains(mousePos))
                {
                    selectedCircle = &endControlCircle;
                    selectedPoint = &endControl;
                }
            }
            if (event.type == sf::Event::MouseButtonReleased)
            {
                selectedCircle = nullptr;
                selectedPoint = nullptr;
            }
        }

        // Dragging logic
        if (selectedCircle && selectedPoint)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            selectedCircle->setPosition(mousePos);
            *selectedPoint = mousePos;
        }

        // Recalculate Bezier points based on updated control points
        sf::VertexArray vertices(sf::LinesStrip, 0);
        std::vector<sf::Vector2f> points = CalcCubicBezier(startPoint, endPoint, startControl, endControl, 50);
        for (const auto &point : points)
            vertices.append(sf::Vertex(point, sf::Color::White));

        // Draw everything
        window.clear(sf::Color::Black);
        window.draw(vertices);
        window.draw(startCircle);
        window.draw(endCircle);
        window.draw(startControlCircle);
        window.draw(endControlCircle);
        window.display();
    }

    return 0;
}
