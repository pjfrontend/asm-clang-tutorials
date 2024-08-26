// https://conkerjo.wordpress.com/2009/06/13/spatial-hashing-implementation-for-fast-2d-collisions/
// http://xna-uk.net/blogs/randomchaos/archive/2008/03/09/geographic-grid-registration-an-alternative-to-quadtrees-and-octrees.aspx

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <string>

// Represents a game object
struct GameObject
{
    std::string id;
    float x, y;   // Position
    float radius; // Radius
};

// Hash function for pairs of integers
struct pair_hash
{
    template <class T1, class T2>
    std::size_t operator()(const std::pair<T1, T2> &pair) const
    {
        return std::hash<T1>()(pair.first) ^ std::hash<T2>()(pair.second);
    }
};

class SpatialManager
{
public:
    SpatialManager(int sceneWidth, int sceneHeight, int cellSize)
        : sceneWidth(sceneWidth), sceneHeight(sceneHeight), cellSize(cellSize)
    {
        cols = sceneWidth / cellSize;
        rows = sceneHeight / cellSize;
    }

    void clearBuckets()
    {
        buckets.clear();
    }

    void registerObject(const GameObject &obj)
    {
        auto cellIds = getIdForObj(obj);
        for (const auto &cellId : cellIds)
        {
            buckets[cellId].push_back(obj);
        }
    }

    std::vector<GameObject> getNearby(const GameObject &obj)
    {
        std::vector<GameObject> nearbyObjects;
        auto cellIds = getIdForObj(obj);
        for (const auto &cellId : cellIds)
        {
            nearbyObjects.insert(nearbyObjects.end(), buckets[cellId].begin(), buckets[cellId].end());
        }
        std::vector<GameObject> nearbyUniqueDifferentObjects;
        for (const auto &nearObj : nearbyObjects)
        {
            if (nearObj.id != obj.id)
            {
                nearbyUniqueDifferentObjects.push_back(nearObj);
            }
        }
        return nearbyUniqueDifferentObjects;
    }

private:
    int sceneWidth, sceneHeight, cellSize;
    int cols, rows;
    std::unordered_map<std::pair<int, int>, std::vector<GameObject>, pair_hash> buckets;

    std::vector<std::pair<int, int>> getIdForObj(const GameObject &obj)
    {
        std::vector<std::pair<int, int>> cellIds;
        int minX = static_cast<int>(std::floor((obj.x - obj.radius) / cellSize));
        int minY = static_cast<int>(std::floor((obj.y - obj.radius) / cellSize));
        int maxX = static_cast<int>(std::floor((obj.x + obj.radius) / cellSize));
        int maxY = static_cast<int>(std::floor((obj.y + obj.radius) / cellSize));

        for (int x = minX; x <= maxX; ++x)
        {
            for (int y = minY; y <= maxY; ++y)
            {
                cellIds.emplace_back(x, y);
            }
        }

        return cellIds;
    }
};

int main()
{
    SpatialManager manager(100, 100, 25);

    GameObject obj1{"obj1", 30, 30, 10};
    GameObject obj2{"obj2", 40, 40, 10};
    GameObject obj3{"obj3", 100, 100, 10};

    manager.registerObject(obj1);
    manager.registerObject(obj2);
    manager.registerObject(obj3);

    auto nearby = manager.getNearby(obj1);

    std::cout << "Nearby objects to obj1: " << nearby.size() << std::endl;

    for (auto n : nearby)
    {
        std::cout << "Nearby object to obj1 id: " << n.id << std::endl;
    }

    return 0;
}
