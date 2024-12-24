#include"resources.h"
#include<SFML/Graphics.hpp>

sf::Texture Resources::wallTexture{};
sf::Texture Resources::spriteTexture{};
sf::Texture Resources::spriteTexture2{};
sf::SoundBuffer Resources::weaponsound; 
sf::SoundBuffer Resources::weaponsound2; 
sf::SoundBuffer Resources::weaponsound3; 
sf::SoundBuffer Resources::gamesound; 
sf::SoundBuffer Resources::menusound; 
sf::SoundBuffer Resources::hitsprite; 
sf::SoundBuffer Resources::playerbit; 
sf::SoundBuffer Resources::spritehit; 

bool Resources::DoorFound=false;
bool Resources::GameLost=false;



