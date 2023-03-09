#pragma once
#include<SFML/Graphics.hpp>
#include"Collider.h"

class Platform
{
public:
    Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position) {
        shape.setSize(size);
        shape.setOrigin(size/2.f);
        if(texture == nullptr){
            shape.setFillColor(sf::Color::Black);
        } else {
            shape.setTexture(texture);
        }
        shape.setPosition(position);
    }

    ~Platform(){}

    void Draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    Collider getCollider() { return Collider(shape); }
private:
    sf::RectangleShape shape;
};