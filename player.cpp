#include"player.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include<cmath>
#include<iostream>
#include <cmath>
#include"ray.cpp"
#include"sound.h"
#include"resources.h"
void::Player::draw(sf::RenderTarget &target)
{
    sf::CircleShape circle(10.0f);
    circle.setFillColor(sf::Color::Red);
    circle.setOrigin(circle.getRadius(),circle.getRadius());
     circle.setPosition(position);
     sf::RectangleShape line(sf::Vector2f(24.0f,2.0f));
     line.setPosition(position);
     line.setRotation(angle);
     line.setFillColor(sf::Color::Red);
     target.draw(line);
     target.draw(circle);
}
bool arePositionsClose(const sf::Vector2f& a, const sf::Vector2f& b, float epsilon = 0.01f) {
    return std::abs(a.x - b.x) < epsilon && std::abs(a.y - b.y) < epsilon;
}

void Player::update(float deltaT, const Map &map, sf::RenderWindow& window, std::vector<sprite>& sprites)
{
    constexpr float tilesize = 20.0f; 
    static sf::Vector2f lastHitPosition = {0.0f, 0.0f}; 
    static float hitTimer = 0.0f; 
// particleTexture.loadFromFile("particle.png");

// std::cout<<"PLayer Position : "<<position.x;


if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    shootray shotRay = castray(position, angle, sprites, map);
    hitPosition=shotRay.hitPos;
if (shotRay.hit) {
    std::cout << "Sprite hit at position: " << shotRay.hitPos.x << ", " << shotRay.hitPos.y << "\n";
    sound::play(Resources::hitsprite);

    // Temporary storage for indices of sprites to remove
    std::vector<size_t> spritesToRemove;

    for (size_t i = 0; i < sprites.size(); ++i) {
        auto& sprite = sprites[i];

        float sprite_width = 1.3f;
        float sprite_height = 1.3f;

        float left = sprite.position.x - sprite_width / 2;
        float right = sprite.position.x + sprite_width / 2;
        float top = sprite.position.y - sprite_height / 2;
        float bottom = sprite.position.y + sprite_height / 2;

        if (shotRay.hitPos.x >= left && shotRay.hitPos.x <= right &&
            shotRay.hitPos.y >= top && shotRay.hitPos.y <= bottom) {
            if(map.getmapcell(static_cast<int>(sprite.position.x),static_cast<int>(sprite.position.y+0.3f)==0))
            sprite.position = sf::Vector2f(sprite.position.x, sprite.position.y + 0.3f);
            std::cout<<"sprite health : "<<sprite.health<<"\n";
            if(sprite.health>0){sprite.health -= 0.005;break;}
            if (sprite.health <= 0) {
                std::cout << "Sprite marked for removal at position: " 
                          << sprite.position.x << ", " << sprite.position.y << "\n";
                spritesToRemove.push_back(i); // Mark sprite for removal
            }
        }
    }

    // Remove sprites after the loop to avoid modifying the vector during iteration
    for (auto it = spritesToRemove.rbegin(); it != spritesToRemove.rend(); ++it) {
        sprites.erase(sprites.begin() + *it);
        float x=0,y=0;bool placed=false;
        while(!placed)
        {
            x=(float)position.x-rand()%15;
            y=(float)position.y-rand()%15;
            // x-=0.234;
            // y-=0.245;
         if(map.getmapcell(x,y)==0)
         {
        sprites.push_back(sprite{{static_cast<float>(x), static_cast<float>(y)}, 0,false, 0.1f,100.0f, 0.0f});
        std::cout<<"New Sprite Spawned at : ( "<<x<<" , "<<y<<" ) \n";
        placed=true;
         }
        }
    }
}


}
for (auto it = particles.begin(); it != particles.end();) {
    it->update(deltaT);
    if (it->isDead()) {
        it = particles.erase(it); // Remove dead particles
    } else {
        ++it;
    }
}
    
    sf::Vector2i mousePos = sf::Mouse::getPosition(window); 
    sf::Vector2i windowCenter(window.getSize().x / 2, window.getSize().y / 2);

    int mouseDeltaX = mousePos.x - windowCenter.x;

    if (mouseDeltaX != 0) {
        float angleChange = mouseDeltaX * Mouse_Turn_Speed;
        this->angle += angleChange;

        if (this->angle < 0.0f) this->angle += 360.0f;
        if (this->angle >= 360.0f) this->angle -= 360.0f;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        this->angle -= TURN_SPEED * deltaT;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        this->angle += TURN_SPEED * deltaT;

    sf::Vector2f move{};
    float radian = angle * (PI / 180.0f);

     if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        
        float elapsedTime = clock.getElapsedTime().asSeconds();  
        if (elapsedTime - lastSoundTime >= soundDelay) {
            
            sound::play(Resources::weaponsound);
            sound::play(Resources::weaponsound2);
            sound::play(Resources::weaponsound3);
            lastSoundTime = elapsedTime;  
        }

        move.x += cos(radian);
        move.y += sin(radian);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        
        move.x -= cos(radian);
        move.y -= sin(radian);
    }

    move *= MOVE_SPEED * deltaT;

    sf::Vector2f newPosition = position + move;

    float playerSize = 0.03f;  

    if (map.getmapcell(static_cast<int>(newPosition.x + playerSize), static_cast<int>(position.y)) == 0 &&
        map.getmapcell(static_cast<int>(newPosition.x - playerSize), static_cast<int>(position.y)) == 0) {
        position.x = newPosition.x; 
    }

    if (map.getmapcell(static_cast<int>(position.x), static_cast<int>(newPosition.y + playerSize)) == 0 &&
        map.getmapcell(static_cast<int>(position.x), static_cast<int>(newPosition.y - playerSize)) == 0) {
        position.y = newPosition.y; 
    }

    sf::Mouse::setPosition(windowCenter, window);
    float speed = sqrt(move.x * move.x + move.y * move.y);
    if (speed > 0) {
        bobbingTime += deltaT * MOVE_SPEED;
    } else {
        bobbingTime = 0.0f;
    }

    if (bobbingTime > 2 * PI) bobbingTime -= 2 * PI;
}
