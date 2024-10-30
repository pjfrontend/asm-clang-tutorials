#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Adaptive Soundtrack Example");

    sf::Music track1;
    sf::Music track2;

    if (!track1.openFromFile("canon.ogg"))
    {
        std::cerr << "Error loading canon!" << std::endl;
        return -1;
    }

    if (!track2.openFromFile("canon-piano.ogg"))
    {
        std::cerr << "Error loading canon-piano!" << std::endl;
        return -1;
    }

    // Set looping for continuous playback (optional)
    track1.setLoop(true);
    track2.setLoop(true);

    float maxVolume = 100.0f;
    float crossfadeDuration = 2.0f;

    track1.setVolume(maxVolume);
    track2.setVolume(0.0f);
    track1.play();

    bool isTrack1Playing = true;
    bool crossfading = false;
    auto crossfadeStart = std::chrono::steady_clock::now(); // Timer to manage crossfade duration

    sf::RectangleShape player(sf::Vector2f(50.0f, 50.0f));
    player.setFillColor(sf::Color::Green);
    player.setPosition(375.0f, 275.0f);
    float playerSpeed = 200.0f;

    sf::Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float deltaTime = clock.restart().asSeconds();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            player.move(0.0f, -playerSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            player.move(0.0f, playerSpeed * deltaTime);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            player.move(-playerSpeed * deltaTime, 0.0f);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            player.move(playerSpeed * deltaTime, 0.0f);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !crossfading)
        {
            crossfading = true;
            crossfadeStart = std::chrono::steady_clock::now();

            sf::Time position = (isTrack1Playing) ? track1.getPlayingOffset() : track2.getPlayingOffset();
            if (isTrack1Playing)
            {
                track2.setPlayingOffset(position);
                track2.play();
            }
            else
            {
                track1.setPlayingOffset(position);
                track1.play();
            }
        }

        // Handle crossfading logic without blocking the game
        if (crossfading)
        {
            auto now = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed = now - crossfadeStart;
            float progress = elapsed.count() / crossfadeDuration;

            if (progress >= 1.0f)
            {
                progress = 1.0f;
                crossfading = false;
            }

            if (isTrack1Playing)
            {
                track1.setVolume(maxVolume * (1.0f - progress));
                track2.setVolume(maxVolume * progress);
            }
            else
            {
                track2.setVolume(maxVolume * (1.0f - progress));
                track1.setVolume(maxVolume * progress);
            }

            if (progress == 1.0f)
            {
                if (isTrack1Playing)
                {
                    track1.stop();
                }
                else
                {
                    track2.stop();
                }

                isTrack1Playing = !isTrack1Playing;
            }
        }

        window.clear();
        window.draw(player);
        window.display();
    }

    return 0;
}
