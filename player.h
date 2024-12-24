#pragma once
#include "map.h"
#include<SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <cstddef>
#include <optional>
#include"sprite.h"
#include"particle.h"
constexpr float PI=3.141592653589793;
constexpr float TURN_SPEED=130.5f;
constexpr float MOVE_SPEED=4.0f;
constexpr float Mouse_Turn_Speed=0.08f;
class Player
{
public:
void draw(sf::RenderTarget &target);
float health=100.0;
sf::Texture healthTexture;  
sf::Sprite healthSprite; 
float angle;
void update(float deltaT,const Map&map, sf::RenderWindow &window,std::vector<sprite>& sprites);
sf::Vector2f position;
float bobbingTime = 0.0f; 
sf::Texture particleTexture; // Load this in your Player constructor or initialization
std::vector<Particle> particles;
sf::Vector2f hitPosition;
    sf::Text Health;
    sf::Font HealthFont;
bool playergotbit=false;
private:
  float lastSoundTime = 0.0f;  
    const float soundDelay = .27f; 
    int currentSoundIndex = 0;  
    sf::Clock clock;  
};