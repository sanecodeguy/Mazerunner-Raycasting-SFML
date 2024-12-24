#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

class Particle {
public:
    sf::Vector2f position;
    sf::Vector2f velocity;
    float lifetime; // in seconds
    sf::Sprite sprite;
    Particle(sf::Vector2f& startPos, const sf::Vector2f& startVel, float life, sf::Texture& texture)
        : position(startPos), velocity(startVel), lifetime(life) {
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
        sprite.setPosition(position);
        sprite.setScale(0.1f, 0.1f); // Scale down for particle size
    }

    void update(float deltaT) {
        position += velocity * deltaT;
        lifetime -= deltaT;
        sprite.setPosition(position);
    }

    bool isDead() const {
        return lifetime <= 0;
    }
};
