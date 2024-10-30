#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

// Utility functions for angle calculations
float distance(sf::Vector2f a, sf::Vector2f b)
{
    return std::sqrt(std::pow(b.x - a.x, 2) + std::pow(b.y - a.y, 2));
}

// Function to calculate the angle (in radians) between two vectors
float angleBetween(sf::Vector2f a, sf::Vector2f b)
{
    float dot = a.x * b.x + a.y * b.y; // Dot product
    float det = a.x * b.y - a.y * b.x; // Determinant
    return std::atan2(det, dot);
}

// Clamp the angle to a specified range [minAngle, maxAngle]
float clampAngle(float angle, float minAngle, float maxAngle)
{
    return std::max(minAngle, std::min(maxAngle, angle));
}

// Function to rotate vector 'v' by angle 'theta' (in radians)
sf::Vector2f rotateVector(sf::Vector2f v, float theta)
{
    float cosTheta = std::cos(theta);
    float sinTheta = std::sin(theta);
    return sf::Vector2f(v.x * cosTheta - v.y * sinTheta, v.x * sinTheta + v.y * cosTheta);
}

// FABRIK with asymmetric joint angle constraints
void FABRIKWithConstraints(std::vector<sf::Vector2f> &joints, sf::Vector2f target, const std::vector<float> &lengths,
                           const std::vector<float> &minAngles, const std::vector<float> &maxAngles, float tolerance)
{
    const int maxIterations = 10; // Limit the number of iterations
    int jointCount = joints.size();

    // Calculate the total length of the chain
    float totalLength = 0.0f;
    for (float length : lengths)
    {
        totalLength += length;
    }

    // Distance from base to target
    float baseToTargetDist = distance(joints[0], target);

    // If the target is too far, stretch the chain towards the target while maintaining proportions
    if (baseToTargetDist > totalLength)
    {
        sf::Vector2f direction = (target - joints[0]) / baseToTargetDist; // Normalize direction
        for (int i = 1; i < jointCount; ++i)
        {
            joints[i] = joints[i - 1] + direction * lengths[i - 1];
        }
        return;
    }

    // Otherwise, proceed with FABRIK algorithm
    sf::Vector2f basePosition = joints[0];

    for (int iteration = 0; iteration < maxIterations; ++iteration)
    {
        // Forward pass: Move the end effector to the target
        joints[jointCount - 1] = target;
        for (int i = jointCount - 2; i >= 0; --i)
        {
            float d = distance(joints[i + 1], joints[i]);
            float lambda = lengths[i] / d;
            joints[i] = joints[i + 1] + (joints[i] - joints[i + 1]) * lambda;
        }

        // Backward pass: Move the base back to its original position
        joints[0] = basePosition;
        for (int i = 1; i < jointCount; ++i)
        {
            float d = distance(joints[i], joints[i - 1]);
            float lambda = lengths[i - 1] / d;
            joints[i] = joints[i - 1] + (joints[i] - joints[i - 1]) * lambda;

            // Apply joint angle constraints
            if (i > 1)
            {                                                          // Skip the first joint (base)
                sf::Vector2f prevBone = joints[i - 1] - joints[i - 2]; // Vector of the previous bone
                sf::Vector2f currBone = joints[i] - joints[i - 1];     // Vector of the current bone

                float currentAngle = angleBetween(prevBone, currBone);          // Current angle between bones
                float clampedAngle = clampAngle(currentAngle, minAngles[i - 1], // Clamp the angle
                                                maxAngles[i - 1]);

                // If the angle was clamped, adjust the joint position
                if (currentAngle != clampedAngle)
                {
                    float angleDiff = clampedAngle - currentAngle;
                    sf::Vector2f rotatedBone = rotateVector(currBone, angleDiff); // Rotate the bone
                    joints[i] = joints[i - 1] + rotatedBone;                      // Adjust the joint position
                }
            }
        }

        // Check if the end effector is close enough to the target
        if (distance(joints[jointCount - 1], target) < tolerance)
        {
            break;
        }
    }
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "FABRIK with Asymmetric Joint Constraints");

    std::vector<float> lengths = {100.0f, 75.0f, 50.0f}; // Lengths of the bones
    const int numJoints = lengths.size() + 1;
    std::vector<sf::Vector2f> joints(numJoints);

    // Minimum and maximum allowed angles for each joint (in radians)
    // For example, a knee joint may have more negative flexion than positive extension
    std::vector<float> minAngles = {-3.14159f / 2, -3.14159f / 4, -3.14159f / 6};
    std::vector<float> maxAngles = {3.14159f / 4, 3.14159f / 2, 3.14159f / 6};

    sf::Vector2f basePosition(400.0f, 300.0f);
    joints[0] = basePosition;

    for (int i = 1; i < numJoints; ++i)
    {
        joints[i] = joints[i - 1] + sf::Vector2f(lengths[i - 1], 0); // Initial placement along x-axis
    }

    sf::Vector2f target = joints.back();
    float tolerance = 1.0f;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        target = (sf::Vector2f)sf::Mouse::getPosition(window);
        FABRIKWithConstraints(joints, target, lengths, minAngles, maxAngles, tolerance);
        window.clear(sf::Color::Black);

        // Draw the articulated chain
        for (int i = 0; i < numJoints - 1; ++i)
        {
            sf::Vertex line[] =
                {
                    sf::Vertex(joints[i], sf::Color::White),
                    sf::Vertex(joints[i + 1], sf::Color::White)};
            window.draw(line, 2, sf::Lines);
        }

        window.display();
    }

    return 0;
}
