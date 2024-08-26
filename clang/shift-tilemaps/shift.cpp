#include <SFML/Graphics.hpp>
#include <vector>
#include "maps.hpp"
#include "utils/TileMap.hpp"

const int TILE_SIZE = 32;
const int GRID_SIZE = 3;
const int MAP_WIDTH = 16;
const int MAP_HEIGHT = 9;
const std::string TILESET_SPRITE = "assets/tileset.png";

std::vector<std::vector<TileMap>> tilemaps(GRID_SIZE, std::vector<TileMap>(GRID_SIZE));

void shift_tilemaps(const std::string &direction)
{
    if (direction == "left")
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            auto placeholder = tilemaps[i][2];
            tilemaps[i][2] = tilemaps[i][1];
            tilemaps[i][1] = tilemaps[i][0];
            // tilemaps[i][0] = TileMap();
            tilemaps[i][0] = placeholder;
        }
    }
    else if (direction == "right")
    {
        for (int i = 0; i < GRID_SIZE; ++i)
        {
            auto placeholder = tilemaps[i][0];
            tilemaps[i][0] = tilemaps[i][1];
            tilemaps[i][1] = tilemaps[i][2];
            // tilemaps[i][2] = TileMap();
            tilemaps[i][2] = placeholder;
        }
    }
    else if (direction == "up")
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            auto placeholder = tilemaps[2][j];
            tilemaps[2][j] = tilemaps[1][j];
            tilemaps[1][j] = tilemaps[0][j];
            // tilemaps[0][j] = TileMap();
            tilemaps[0][j] = placeholder;
        }
    }
    else if (direction == "down")
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            auto placeholder = tilemaps[0][j];
            tilemaps[0][j] = tilemaps[1][j];
            tilemaps[1][j] = tilemaps[2][j];
            // tilemaps[2][j] = TileMap();
            tilemaps[2][j] = placeholder;
        }
    }
}

int main()
{
    sf::RenderWindow window(
        sf::VideoMode(
            MAP_WIDTH * TILE_SIZE,
            MAP_HEIGHT * TILE_SIZE),
        "Tilemap Shifting with SFML");
    sf::View view = window.getDefaultView();

    // Load initial tilemaps
    for (int i = 0; i < GRID_SIZE; ++i)
    {
        for (int j = 0; j < GRID_SIZE; ++j)
        {
            int tiles[MAP_WIDTH * MAP_HEIGHT];
            auto v = all_maps[i * GRID_SIZE + j];
            std::copy(v.begin(), v.end(), tiles);
            tilemaps[i][j].load(
                TILESET_SPRITE,
                sf::Vector2u(TILE_SIZE, TILE_SIZE),
                tiles,
                MAP_WIDTH,
                MAP_HEIGHT);
        }
    }

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
                view.setSize({static_cast<float>(event.size.width),
                              static_cast<float>(event.size.height)});
                window.setView(view);
            }

            // Handle shifting based on user input
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Left)
                    shift_tilemaps("left");
                if (event.key.code == sf::Keyboard::Right)
                    shift_tilemaps("right");
                if (event.key.code == sf::Keyboard::Up)
                    shift_tilemaps("up");
                if (event.key.code == sf::Keyboard::Down)
                    shift_tilemaps("down");
            }
        }

        window.clear();

        for (int i = 0; i < GRID_SIZE; ++i)
        {
            for (int j = 0; j < GRID_SIZE; ++j)
            {
                window.draw(tilemaps[i][j]);
            }
        }

        window.display();
    }

    return 0;
}
