#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
class Resources
{
public:
static sf::Texture wallTexture;
static sf::Texture spriteTexture;
static sf::Texture spriteTexture2;
static bool DoorFound;
static bool GameLost;
static sf::SoundBuffer weaponsound,weaponsound2,weaponsound3,gamesound,menusound,hitsprite,playerbit,spritehit;
};