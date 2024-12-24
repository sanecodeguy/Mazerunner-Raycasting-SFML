#pragma once
#include<SFML/Audio.hpp>
#include<SFML/System.hpp>
namespace sound
{
void play(const sf::SoundBuffer &source);
void play(const sf::SoundBuffer &source,sf::Vector3f position,bool relative=false);
void update();
}