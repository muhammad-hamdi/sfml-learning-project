#include<SFML/Graphics.hpp>
#include<iostream>
#include "Player.h"
#include"Platform.h"

static const float VIEW_HEIGHT  = 600;


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

sf::Vector2f lerp(sf::Vector2f v0, sf::Vector2f v1, float t) {
    return (1 - t) * v0 + t * v1;
}

int main()
{
    // Create Window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!", sf::Style::Close | sf::Style::Resize);

    sf::View view(sf::Vector2f(0.0, 0.0f), sf::Vector2f(800, VIEW_HEIGHT));

    sf::Texture playerTexture;
    playerTexture.loadFromFile("../resources/char_red.png");
    Player player(&playerTexture, sf::Vector2u(8, 11), 0.1, 200);

    Platform platform1(nullptr, sf::Vector2f(100.f, 100.f), sf::Vector2f(50.f, 50.f));
    Platform platform2(nullptr, sf::Vector2f(200.f, 300.f), sf::Vector2f(200.f, 300.f));
    
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
        platform1.getCollider().checkCollision(player.getCollider(), 0.f);
        platform1.getCollider().checkCollision(platform2.getCollider(), 0.f);
        platform2.getCollider().checkCollision(player.getCollider(), 1.f);
        platform2.getCollider().checkCollision(platform1.getCollider(), 0.f);

        view.setCenter(lerp(view.getCenter(), player.getPosition(), deltaTime * 4));
        

        // Clear the canvas
        window.clear(sf::Color(215, 215, 215, 255));
        window.setView(view);
        
        // Do the drawing here
        player.Draw(window);
        platform1.Draw(window);
        platform2.Draw(window);

        // Display the frame
        window.display();
    }

    return 0;
}