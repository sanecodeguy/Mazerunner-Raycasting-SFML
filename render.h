#pragma once

#include<SFML/Graphics.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <vector>
#include"sprite.h"
#include"player.h"
#include"map.h"
#include"bullet.h"
constexpr float screen_w=800.0f;
constexpr float screen_h=500.0f;
class Render
{
public:
void init();
void draw3D(sf::RenderTarget &target,Player &player,const Map &map, std::vector<sprite>&sprites,float deltaT);
void drawRays(sf::RenderTarget &target,const Player &player,const Map &map);
private:
float zbuffer[(size_t)screen_w];
std::vector<Bullet> bullets;  
sf::Texture bulletTexture;  
sf::Texture healthtexture;
sf::Texture weapon;
sf::Sprite weaponsprite,healthSprite;
sf::Image floortexture,rooftexture;
};