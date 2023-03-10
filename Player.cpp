#include "Player.h"
#include<math.h>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed): animation(texture, imageCount, switchTime), speed(speed), collider(shape), sprite(*texture)
{
    row = 0;
    facingRight = true;

    shape.setSize(sf::Vector2f(40.f, 65.f));
    shape.setOrigin(shape.getSize()/2.f);
    sprite.setScale(2.f, 2.f);
    sprite.setOrigin(shape.getOrigin());
    shape.setPosition(150.f, 150.f);
    centerPoint.color = sf::Color::Black;
    // shape.setTexture(texture);
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
    sprite.setTextureRect(animation.uvRect);
    shape.move(vel * speed * deltaTime);
    sprite.setPosition(shape.getPosition().x - 12.f, shape.getPosition().y - 15.f);
    centerPoint.position = sf::Vector2f(sprite.getGlobalBounds().left + sprite.getGlobalBounds().width, sprite.getGlobalBounds().top + sprite.getGlobalBounds().height);
}

void Player::Draw(sf::RenderWindow &window)
{
    window.draw(shape);
    window.draw(sprite);
    window.draw(&centerPoint, 1, sf::Points);
}
