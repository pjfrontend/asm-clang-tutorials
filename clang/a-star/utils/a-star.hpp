#pragma once
#include <vector>
#include <queue>
#include <algorithm>
#include <cmath>
#include <unordered_map>

struct Node
{
    int x, y;
    float f, g, h;
    Node *parent;

    Node(int x, int y, float g = 0, float h = 0, Node *parent = nullptr)
        : x(x), y(y), g(g), h(h), f(g + h), parent(parent) {}

    bool operator<(const Node &other) const
    {
        return f > other.f; // for priority queue to work as min-heap
    }
};

std::vector<std::pair<int, int>> getNeighbors(int x, int y, const std::vector<int> &grid, int rows, int cols)
{
    std::vector<std::pair<int, int>> neighbors;
    const int dirs[4][2] = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
    for (const auto &dir : dirs)
    {
        int nx = x + dir[0];
        int ny = y + dir[1];
        bool is_floor = grid[nx * cols + ny] == 0; // Any value greater than zero is treated as an obstacle
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && is_floor)
        {
            neighbors.emplace_back(nx, ny);
        }
    }
    return neighbors;
}

float heuristic(int x1, int y1, int x2, int y2)
{
    return std::abs(x1 - x2) + std::abs(y1 - y2); // Manhattan distance
}

std::vector<std::pair<int, int>> reconstructPath(Node *node)
{
    std::vector<std::pair<int, int>> path;
    while (node)
    {
        path.emplace_back(node->x, node->y);
        node = node->parent;
    }
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::pair<int, int>> aStar(const std::vector<int> &grid, int rows, int cols, std::pair<int, int> start, std::pair<int, int> goal)
{
    std::vector<std::vector<bool>> closedSet(rows, std::vector<bool>(cols, false));
    std::priority_queue<Node> openSet;
    std::unordered_map<int, Node *> openSetMap; // for fast lookup and updates
    openSet.emplace(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));

    std::unordered_map<int, Node *> allNodes; // to keep track of all allocated nodes for proper memory cleanup

    while (!openSet.empty())
    {
        Node current = openSet.top();
        openSet.pop();
        openSetMap.erase(current.x * cols + current.y);

        if (current.x == goal.first && current.y == goal.second)
        {
            std::vector<std::pair<int, int>> path = reconstructPath(&current);
            for (auto &entry : allNodes)
                delete entry.second; // clean up
            return path;
        }

        closedSet[current.x][current.y] = true;

        for (const auto &neighbor : getNeighbors(current.x, current.y, grid, rows, cols))
        {
            int nx = neighbor.first, ny = neighbor.second;

            if (closedSet[nx][ny])
                continue;

            float tentative_g = current.g + 1;
            Node *neighborNode = new Node(nx, ny, tentative_g, heuristic(nx, ny, goal.first, goal.second), new Node(current));

            int key = nx * cols + ny;
            if (openSetMap.find(key) == openSetMap.end() || tentative_g < openSetMap[key]->g)
            {
                openSet.push(*neighborNode);
                openSetMap[key] = neighborNode;
                allNodes[key] = neighborNode; // store the node pointer
            }
            else
            {
                delete neighborNode; // clean up
            }
        }
    }

    for (auto &entry : allNodes)
        delete entry.second; // clean up if no path is found
    return {};               // return empty path if no path is found
}
