#include<SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"

// Handle interrupt events
void handleEvents(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event))
    {
        switch (event.type)
        {
            case sf::Event::Closed:
                window.close();
                break;
            default:
                break;
        }
    }
}

int main()
{
    // Create Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Close | sf::Style::Resize);

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../resources/char_red.png");
    Player player(&playerTexture, sf::Vector2u(8, 11), 0.1, 200);


    
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
        handleEvents(window);
        player.Update(deltaTime);

        // Clear the canvas
        window.clear(sf::Color(245, 245, 245, 255));
        
        // Do the drawing here
        player.Draw(window);

        // Display the frame
        window.display();
    }

    return 0;
}