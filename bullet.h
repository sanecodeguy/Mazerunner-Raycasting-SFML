#pragma once
#include<SFML/Graphics.hpp>
class Bullet {
public:
    sf::Sprite sprite;
    sf::Vector2f velocity;

    Bullet(sf::Texture &bulletTexture, sf::Vector2f startPos, sf::Vector2f direction, float speed) {
        // Set the sprite's initial position
        sprite.setTexture(bulletTexture);
        sprite.setPosition(startPos);

        // Set the velocity based on the direction and speed
        velocity = direction * speed;
        
        // Set initial scale similar to the weapon sprite
        sprite.setScale(25.5f, 25.5f);
        
        // Optional: Set the origin to the center for rotation if necessary
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);
    }

    void update(float deltaTime) {
        // Move the bullet in the direction of its velocity
        sprite.move(velocity * deltaTime);
    }

    void draw(sf::RenderTarget &target) {
        target.draw(sprite);
    }
};
