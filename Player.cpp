#include "Player.h"
#include<math.h>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed): animation(texture, imageCount, switchTime), speed(speed)
{
    row = 0;
    facingRight = true;

    shape.setSize(sf::Vector2f(100.f, 100.f));
    shape.setPosition(150.f, 150.f);
    shape.setTexture(texture);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
    sf::Vector2f vel;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) vel.y -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) vel.x -= 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) vel.y += 1;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) vel.x += 1;
    float magnitude = sqrt(vel.x*vel.x + vel.y*vel.y);
    magnitude != 0 ? vel /= magnitude : vel;
    // bool moving = abs(vel.x) > 0.f || abs(vel.y) > 0;
    if (abs(vel.x) == 0.f && abs(vel.y) == 0) {
        row = 0;
    } else {
        row = 2;
        if (vel.x > 0) {
            facingRight = true;
        } else if (vel.x < 0) {
            facingRight = false;
        }
    }
    animation.Update(row, deltaTime, facingRight, row ? 0 : 6);
    shape.setTextureRect(animation.uvRect);
    shape.move(vel * speed * deltaTime);
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(shape);
}
