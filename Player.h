#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Player
{
public:
    Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);
    ~Player();

    void Update(float deltaTime);
    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() { return shape.getPosition(); }
    Collider& getCollider() {
        return this->collider;
    }

private:
    sf::RectangleShape shape;
    sf::Sprite sprite;
    Animation animation;
    Collider collider;
    sf::Vector2f position;
    sf::Vertex centerPoint;
    unsigned int row;
    float speed;
    bool facingRight;
};