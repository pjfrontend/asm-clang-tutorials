#pragma once
#include <SFML/Graphics.hpp>

sf::Vector2i convert_1D_to_2D_vector(int index, int row_size)
{
    int row = index / row_size;
    int col = index % row_size;
    return {col, row};
}

int convert_2D_to_1D_vector(int x, int y, int row_size)
{
    return y * row_size + x;
}