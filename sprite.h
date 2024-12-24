#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include "map.h"
#include"sound.h"
#include"resources.h"
// #include"player.cpp"

class sprite {
public:
    sf::Vector2f position;
    int animationFrame = 0;
    bool playergotbit=false;
    float health=100.0f;
    float animationSpeed = 0.1f;
    float animationTimer = 0.0f;
    bool isChasing = false;
    bool hasSeenPlayer = false;
    float chaseDistance = 10000.0f;
    float moveSpeed = 0.15f;
    float offsetDistance = 0.01f;
    float maintainDistance = 1.4f;
    float width = 1.0f;
    float height = 1.0f;
    bool hasbeenhit = false;
    sf::Color color = sf::Color::White;
    float shootCooldown = 3.0f;
    float shootTimer = 0.0f;

    
    float soundDelayTimer = 0.0f;
     float soundDelay = 1.0f;

    
    bool showOverlay = false;            
    float overlayTimer = 0.0f;           
     float overlayDuration = 0.5f; 

    bool canSeePlayer(const sf::Vector2f& playerPos, const Map& map) {
        float distance = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));
        if (distance <= chaseDistance) {
            sf::Vector2f direction = playerPos - position;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) direction /= length;

            const float rayStep = 1.0f;
            sf::Vector2f rayPosition = position;
            while (std::sqrt(std::pow(rayPosition.x - playerPos.x, 2) + std::pow(rayPosition.y - playerPos.y, 2)) > rayStep) {
                rayPosition += direction * rayStep;
                if (!map.isWalkable(rayPosition)) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    void update(sf::Vector2f& playerPos, const Map& map, float deltaTime, sf::RenderWindow& window,float &playerhealth,sf::Text &Health) {
        
        soundDelayTimer -= deltaTime;
        if (showOverlay) {
            overlayTimer -= deltaTime;
            if (overlayTimer <= 0.0f) {
                showOverlay = false; 
            }
        }
        

        
        if (canSeePlayer(playerPos, map)) {
            hasSeenPlayer = true;
        }

        if (hasSeenPlayer) {
            sf::Vector2f direction = playerPos - position;
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            if (length > 0) direction /= length;

            float distanceToPlayer = std::sqrt(std::pow(playerPos.x - position.x, 2) + std::pow(playerPos.y - position.y, 2));

            
            if (distanceToPlayer < maintainDistance) {
              playergotbit=true;
                showOverlay = true;
                overlayTimer = overlayDuration;
                playerhealth-=0.05f;
                if (soundDelayTimer <= 0.0f) {
                    sound::play(Resources::playerbit);

                    soundDelayTimer = soundDelay;
                    // sound::play(Resources::spritehit);
                }

                
                sf::Vector2f newPosition = position - direction * moveSpeed;
                if (map.isWalkable(newPosition)) {
                    position = newPosition;
                }
            } else {
                playergotbit=false;
                sf::Vector2f attemptedMove = position + direction * moveSpeed;
                if (map.isWalkable(attemptedMove)) {
                    position = attemptedMove;
                }
            }
        }

        
        if (showOverlay) {
            sf::RectangleShape redOverlay(sf::Vector2f(800.0f, 500.0f));
            redOverlay.setFillColor(sf::Color(255, 0, 0, 200)); 
            redOverlay.setPosition(0.0f, 0.0f);
            window.draw(redOverlay);
        }
    }
};
