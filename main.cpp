#include<SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"
#include"Platform.h"

static const float VIEW_HEIGHT  = 600;

sf::Vector2f lerp(sf::Vector2f v0, sf::Vector2f v1, float t) {
    return (1 - t) * v0 + t * v1;
}

void resizeView(const sf::RenderWindow& window, sf::View& view) {
    float aspectRatio = float(window.getSize().x) / float(window.getSize().y);
    view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

// Handle interrupt events
void handleEvents(sf::RenderWindow& window, sf::View& view) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            case sf::Event::Resized:
                resizeView(window, view);
        }
    }
}

int main()
{
    // Create Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Close | sf::Style::Resize);

    sf::View view(sf::Vector2f(0.0, 0.0f), sf::Vector2f(800, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../resources/char_red.png");
    Player player(&playerTexture, sf::Vector2u(8, 11), 0.1, 200);

    std::vector<Platform> platforms;

    platforms.push_back(Platform(nullptr, sf::Vector2f(100.f, 100.f), sf::Vector2f(50.f, 50.f)));
    platforms.push_back(Platform(nullptr, sf::Vector2f(200.f, 300.f), sf::Vector2f(200.f, 300.f)));
    
    // sf::Font font;
    // if (!font.loadFromFile("../resources/sansation.ttf"))
    //         return EXIT_FAILURE;

    // sf::Text fpsText("FPS: ", font, 14);
    // fpsText.setFillColor(sf::Color::Yellow);

    // Set fps to 60
    // window.setFramerateLimit(60);

    // init clock for deltaTime
    sf::Clock clock;
    float deltaTime = 0.0;
    while (window.isOpen())
    {
        // Calculate deltaTime
        deltaTime = clock.restart().asSeconds();

        // events
        handleEvents(window, view);
        player.Update(deltaTime);

        sf::Vector2f direction;

        for(Platform& plat : platforms) {
            if(plat.getCollider().checkCollision(player.getCollider(), direction, 1.f))
            {
                player.onCollision(direction);
            }
        }

        view.setCenter(lerp(view.getCenter(), player.getPosition(), deltaTime * 4));
        

        // Clear the canvas
        window.clear(sf::Color(215, 215, 215, 255));
        window.setView(view);
        
        // Do the drawing here
        player.Draw(window);
        for(Platform& plat : platforms) {
            plat.Draw(window);
        }

        // Display the frame
        window.display();
    }

    return 0;
}