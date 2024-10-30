#include <iostream>
#include <vector>
#include "utils/a-star.hpp"

int main()
{
    int rows = 5;
    int cols = 5;
    const int grid_size = rows * cols;
    int grid[grid_size] = {
        0, 1, 0, 0, 0,
        0, 1, 0, 1, 0,
        0, 0, 0, 1, 0,
        0, 1, 1, 1, 0,
        0, 0, 0, 0, 0};

    // Y, X inverted!
    std::pair<int, int> start = {0, 0};
    std::pair<int, int> goal = {3, 4};
    std::vector<int> vec_grid(grid, grid + grid_size);

    std::vector<std::pair<int, int>> path = aStar(vec_grid, rows, cols, start, goal);

    if (!path.empty())
    {
        std::cout << "Path found:\n";
        for (const auto &p : path)
        {
            std::cout << "(" << p.first << ", " << p.second << ") ";
        }
        std::cout << std::endl;
    }
    else
    {
        std::cout << "No path found." << std::endl;
    }

    return 0;
}