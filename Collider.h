#pragma once
#include<SFML/Graphics.hpp>

class Collider {
public:
    Collider(sf::RectangleShape& shape): shape(shape)
    {
        
    }

    ~Collider(){}

    void move(float dx, float dy) { shape.move(dx, dy); }

    bool checkCollision(Collider & other, sf::Vector2f & direction, float push) {
        sf::Vector2f otherPosition = other.getPosition();
        sf::Vector2f otherHalfsize = other.getHalfSize();
        sf::Vector2f thisPosition = getPosition();
        sf::Vector2f thisHalfsize = getHalfSize();
        float deltaX = otherPosition.x - thisPosition.x;
        float deltaY = otherPosition.y - thisPosition.y;
        float intersectX = abs(deltaX) - (otherHalfsize.x + thisHalfsize.x);
        float intersectY = abs(deltaY) - (otherHalfsize.y + thisHalfsize.y);

        if (intersectX < 0.f && intersectY < 0.f) {
            push = std::min(std::max(push, 0.f), 1.f); // clamp push between 0, 1

            if(intersectX > intersectY) {
                if (deltaX > 0.0f) {
                    move(intersectX * (1.f - push), 0.f);
                    other.move(-intersectX * push, 0.f);

                    direction.x = 1.0f;
                    direction.y = 0.0f;
                }
                else
                {
                    move(-intersectX * (1.f - push), 0.f);
                    other.move(intersectX * push, 0.f);

                    direction.x = -1.0f;
                    direction.y = 0.0f;
                }
            }
            else
            {
                if (deltaY > 0.0f) {
                    move(0.f, intersectY * (1.f - push));
                    other.move(0.f, -intersectY * push);

                    direction.x = 0.0f;
                    direction.y = 1.0f;
                }
                else
                {
                    move(0.f, -intersectY * (1.f - push));
                    other.move(0.f, intersectY * push);

                    direction.x = 0.0f;
                    direction.y = -1.0f;
                }
            }

            return true;
        }

        return false;
    }

    sf::Vector2f getPosition() { return shape.getPosition(); }
    sf::Vector2f getHalfSize() { return shape.getSize() / 2.f; }

private:
    sf::RectangleShape& shape;
};
