
#include"render.h"
#include <SFML/Graphics/PrimitiveType.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Window.hpp>
#include<cmath>
#include <vector>
#include"resources.h"
#include "sprite.h"
#include<string>
#include<iostream>
#include<sstream>

constexpr float tilesize=20.0f;
constexpr float max_raycasting_steps=60;
constexpr float FOV=60.0f;
constexpr auto numrays=2000;
constexpr float column_w=screen_w/(float)numrays;
constexpr float camera_z=0.5f*screen_h;
struct Ray
{
sf::Vector2f hitPos;
float distance;
bool hit;
bool isHitVertical;
};
static Ray castRay(sf::Vector2f start,float angleD,const Map&map);

void::Render::drawRays(sf::RenderTarget &target, const Player&player,const Map&map)
{
for(float angle=player.angle - FOV/2.0f;angle<player.angle+FOV;angle+=0.5f)
{
Ray ray=castRay(player.position,angle,map);
if(ray.hit)
{
sf::Vertex line[]={
    sf::Vertex(player.position),
    sf::Vertex(ray.hitPos),
};
target.draw(line,2,sf::Lines);
}
 }
}
Ray castRay(sf::Vector2f start,float angleD,const Map&map)
{
constexpr float PI=3.141592653589793;

float angle=angleD*PI/180.f;
float hTan=-1.0f/std::tan(angle);
float vTan=-std::tan(angle);
sf::Vector2f offset;
auto vdof=0,hdof=0;
float vdist=std::numeric_limits<float>::max();
float hdist=std::numeric_limits<float>::max();
sf::Vector2f vrayPos,hrayPos;

bool hit=false;
if(cos(angle)>0.001f)
{
    vrayPos.x=std::floor(start.x/tilesize)*tilesize+tilesize;
    vrayPos.y=(start.x-vrayPos.x)*vTan+start.y;
    offset.x=tilesize;
    offset.y=-offset.x*vTan;
}
else if(cos(angle)<-0.001f)
{
    vrayPos.x=std::floor(start.x/tilesize)*tilesize-0.01f;
    vrayPos.y=(start.x-vrayPos.x)*vTan+start.y;
    offset.x=-tilesize;
    offset.y=-offset.x*vTan;
}
else vdof=max_raycasting_steps;

const auto &grid=map.getgrid();
for(;vdof<max_raycasting_steps;vdof++)
{
     int mapX=(int)(vrayPos.x/tilesize);
     int mapY=(int)(vrayPos.y/tilesize);
     if(mapY<grid.size() && mapX<grid[mapY].size() && grid[mapY][mapX])
     {
        hit=true;
        vdist=std::sqrt(
            (vrayPos.x-start.x)*(vrayPos.x-start.x)+
            (vrayPos.y-start.y)*(vrayPos.y-start.y)
        ); 
        break;
     }

     vrayPos+=offset;
}

if(sin(angle)>0.001f)
{
    hrayPos.y=std::floor(start.y/tilesize)*tilesize+tilesize;
    hrayPos.x=(start.y-hrayPos.y)*hTan+start.x;
    offset.y=tilesize;
    offset.x=-offset.y*hTan;
}
else if(sin(angle)<-0.001f)
{
    hrayPos.y=std::floor(start.y/tilesize)*tilesize-0.01f;
    hrayPos.x=(start.y-hrayPos.y)*hTan+start.x;
    offset.y=-tilesize;
    offset.x=-offset.y*hTan;
}
else hdof=max_raycasting_steps;
for(;hdof<max_raycasting_steps;hdof++)
{
     int mapX=(int)(hrayPos.x/tilesize);
     int mapY=(int)(hrayPos.y/tilesize);
     if(mapY<grid.size() && mapX<grid[mapY].size() && grid[mapY][mapX])
     {
        hit=true;
hdist=std::sqrt(
            (hrayPos.x-start.x)*(hrayPos.x-start.x)+
            (hrayPos.y-start.y)*(hrayPos.y-start.y)
        );
        break;
     }

     hrayPos+=offset;
}
int DoorDistance=std::min(hdist,vdist);

return Ray{hdist<vdist?hrayPos:vrayPos,std::min(hdist,vdist),hit,vdist<hdist};
}
void Render::draw3D(sf::RenderTarget &target, Player &player, const Map &map,std::vector<sprite>&sprites,float deltaT) {
    sf::RectangleShape rectangle(sf::Vector2f(screen_w, screen_h / 2.0f));
    rectangle.setFillColor(sf::Color(100, 170, 250)); 
    target.draw(rectangle); 
constexpr float PI = 3.141592653589793;
float radians = player.angle * PI / 180.0f;
sf::Vector2f position = player.position;
sf::Vector2f direction{std::cos(radians), std::sin(radians)};
sf::Vector2f plane{-direction.y, direction.x * 0.66f}; 

uint8_t floorpixels[(size_t)screen_w * (size_t)screen_h * 4] = {};  

uint8_t roofpixels[(size_t)screen_w * (size_t)screen_h * 4] = {};   


for (size_t y = screen_h / 2.0f; y < screen_h; y++) {
    
    sf::Vector2f rayDirLeft{direction - plane};
    sf::Vector2f rayDirRight{direction + plane};

    
    float rowDist = camera_z / ((float)y - screen_h / 2);

    
    sf::Vector2f floorStep = rowDist * (rayDirRight - rayDirLeft) / screen_w;

    
    sf::Vector2f floor = position + rowDist * rayDirLeft;

    
    float textsize = this->floortexture.getSize().x; 

    for (size_t x = 0; x < screen_w; x++) {
        
        sf::Vector2i cell{floor};  
        sf::Vector2i textCoord{(int)(textsize * (floor.x - (float)cell.x)),
                               (int)(textsize * (floor.y - (float)cell.y))};

        
        textCoord.x = (textCoord.x + (int)textsize) % (int)textsize;
        textCoord.y = (textCoord.y + (int)textsize) % (int)textsize;

        
        sf::Color color = floortexture.getPixel(textCoord.x, textCoord.y);

        
        floorpixels[(x + y * (size_t)screen_w) * 4 + 0] = color.r;
        floorpixels[(x + y * (size_t)screen_w) * 4 + 1] = color.g;
        floorpixels[(x + y * (size_t)screen_w) * 4 + 2] = color.b;
        floorpixels[(x + y * (size_t)screen_w) * 4 + 3] = color.a;

        
        floor += floorStep;
    }
}


for (size_t y = 0; y < screen_h / 2.0f; y++) {
    
    sf::Vector2f rayDirLeft{direction - plane};
    sf::Vector2f rayDirRight{direction + plane};

    
    float rowDist = camera_z / ((float)screen_h / 2 - (float)y);

    
    sf::Vector2f roofStep = rowDist * (rayDirRight - rayDirLeft) / screen_w;

    
    sf::Vector2f roof = position + rowDist * rayDirLeft;

    
    float textsize = this->rooftexture.getSize().x; 

    for (size_t x = 0; x < screen_w; x++) {
        
        sf::Vector2i cell{roof};  
        sf::Vector2i textCoord{(int)(textsize * (roof.x - (float)cell.x)),
                               (int)(textsize * (roof.y - (float)cell.y))};

        
        textCoord.x = (textCoord.x + (int)textsize) % (int)textsize;
        textCoord.y = (textCoord.y + (int)textsize) % (int)textsize;

        
        sf::Color color = rooftexture.getPixel(textCoord.x, textCoord.y);

        
        roofpixels[(x + y * (size_t)screen_w) * 4 + 0] = color.r;
        roofpixels[(x + y * (size_t)screen_w) * 4 + 1] = color.g;
        roofpixels[(x + y * (size_t)screen_w) * 4 + 2] = color.b;
        roofpixels[(x + y * (size_t)screen_w) * 4 + 3] = color.a;

        
        roof += roofStep;
    }
}


sf::Image floorImage;
floorImage.create(screen_w, screen_h, floorpixels);

sf::Image roofImage;
roofImage.create(screen_w, screen_h, roofpixels);


sf::Texture floorTexture, roofTexture;
floorTexture.loadFromImage(floorImage);
roofTexture.loadFromImage(roofImage);

sf::Sprite floorSprite(floorTexture);
sf::Sprite roofSprite(roofTexture);


target.draw(roofSprite);
target.draw(floorSprite);

    sf::VertexArray walls{sf::Lines};
    for(auto i=0;i<screen_w;i++)
    {
        float cameraX=i*2.0f/screen_w-1.0f;
        sf::Vector2f raypos=player.position;
        sf::Vector2f raydir=direction+plane*cameraX;
        sf::Vector2f deltaDistance{
            std::abs(1.0f/raydir.x),
            std::abs(1.0f/raydir.y),
        };
        sf::Vector2i mapPos{raypos};
        sf::Vector2i step;
        sf::Vector2f sideDist;

        if(raydir.x<0.0f)
        {
            step.x=-1;
            sideDist.x=(-mapPos.x+raypos.x)*deltaDistance.x;
        }
        else if(raydir.x>0.0f)
        {
            step.x=1;
            sideDist.x=(mapPos.x-raypos.x+1.0f)*deltaDistance.x;
        }

        if(raydir.y<0.0f)
        {
            step.y=-1;
            sideDist.y=(-mapPos.y+raypos.y)*deltaDistance.y;
        }
        else if(raydir.y>0.0f)
        {
            step.y=1;
            sideDist.y=(mapPos.y-raypos.y+1.0f)*deltaDistance.y;
        }

        bool didhit{},ishitvertical{};
        int hit{};
        auto depth=0;
        while(hit==0 && depth<max_raycasting_steps)
        {
            if(sideDist.x<sideDist.y)
            {
                 sideDist.x+=deltaDistance.x;
                 mapPos.x+=step.x; 
                 ishitvertical=false;
            }
            else{
                 sideDist.y+=deltaDistance.y;
                 mapPos.y+=step.y; 
                 ishitvertical=true;
            }
            const auto &grid=map.getgrid();
            int x=mapPos.x, y=mapPos.y;
            hit=grid[y][x];
              depth++;

        }
        if (hit > 0) {
    float prepwalldist = ishitvertical ? sideDist.y - deltaDistance.y : sideDist.x - deltaDistance.x;

    if (hit == 5) {
        constexpr float doorDistanceThreshold = 0.5f; 
        if (prepwalldist <= doorDistanceThreshold) {
            // std::cout << "Door Found ";
            Resources::DoorFound=true;
            
        }
    }

    float wallHeight = screen_h / prepwalldist;
    float wallstart = (-wallHeight + screen_h) / 2.0f;
    float wallend = (wallHeight + screen_h) / 2.0f;

    float textsize = Resources::wallTexture.getSize().y; 
    float wallX = ishitvertical ? raypos.x + prepwalldist * raydir.x : raypos.y + prepwalldist * raydir.y;
    wallX -= std::floor(wallX);
    float textX = wallX * textsize;

    sf::Color color = sf::Color(255, 255, 255);
    walls.append(sf::Vertex(sf::Vector2f((float)i, wallstart), color, sf::Vector2f(textX + (hit - 1) * textsize, 0.0f)));
    walls.append(sf::Vertex(sf::Vector2f((float)i, wallend), color, sf::Vector2f(textX + (hit - 1) * textsize, textsize)));
    this->zbuffer[i] = prepwalldist;
}
    
         
    }
sf::RenderStates states{&Resources::wallTexture};
target.draw(walls,states);
int frameWidth = 16;  
int frameHeight = 16; 
int gapWidth = 1;     
int totalFrames = 5;  
int buffer=0;
for (auto &sprite : sprites) {
    // Update sprite animation


    // Calculate sprite position relative to the player
    sf::Vector2f spritePos = sprite.position - player.position;

    // Perform transformation
    float invDet = 1.0f / (plane.x * direction.y - plane.y * direction.x);
    sf::Vector2f transformed{
        invDet * (direction.y * spritePos.x - direction.x * spritePos.y),
        invDet * (-plane.y * spritePos.x + plane.x * spritePos.y)
    };

    // Render sprite if it's in front of the camera
    if (transformed.y > 0.0f) { 
        int spriteScreenX = screen_w / 2 * (1 + transformed.x / transformed.y);
        int spriteSize = std::abs(screen_h / transformed.y);

        int drawStartY = std::max((int)screen_h / 2 - spriteSize / 2, 0);
        int drawEndY = std::min((int)screen_h / 2 + spriteSize / 2, (int)screen_h - 1);

        int drawStartX = std::max(spriteScreenX - spriteSize / 2, 0);
        int drawEndX = std::min(spriteScreenX + spriteSize / 2, (int)screen_w - 1);

        // Render the sprite
        for (int x = drawStartX; x < drawEndX; ++x) {
            if (transformed.y < zbuffer[x]) { 
                int textureX = (x - (spriteScreenX - spriteSize / 2)) * frameWidth / spriteSize;

                sf::RectangleShape spriteRect(sf::Vector2f(1.0f, spriteSize)); 
                spriteRect.setPosition(x, drawStartY);
                spriteRect.setSize(sf::Vector2f(1.0f, drawEndY - drawStartY));

                // Determine the current animation frame and apply texture
                int frameX = sprite.animationFrame * (frameWidth + gapWidth);
                int frameY = 0;

                sf::IntRect textureRect(frameX + textureX, frameY, 1, frameHeight);
                spriteRect.setTexture(&Resources::spriteTexture);
                spriteRect.setTextureRect(textureRect);

                target.draw(spriteRect);
            }
        }
    }
}

sf::Texture blood;
blood.loadFromFile("blood.png");
sf::RectangleShape pain(sf::Vector2f(screen_w,screen_h));

pain.setTexture(&blood);



    
    
    

float bobbingAmplitude = 5.0f; 
    float horizontalAmplitude = 2.0f; 
    float bobbingOffsetY = bobbingAmplitude * std::sin(player.bobbingTime * 6.0f); 
    float bobbingOffsetX = horizontalAmplitude * std::cos(player.bobbingTime * 3.0f);

    
    static sf::Clock flickTimer; 
    static bool isFlicking = false; 
    const sf::Time flickDuration = sf::seconds(0.05f); 
    static float weaponRotation = 0.0f; 

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !isFlicking) {
        isFlicking = true; 
        flickTimer.restart();
    }

    if (isFlicking) {
        
        float elapsedTime = flickTimer.getElapsedTime().asSeconds();
        if (elapsedTime < flickDuration.asSeconds()) {
            weaponRotation = -35.0f * (1.0f - elapsedTime / flickDuration.asSeconds()); 
        } else {
            
            isFlicking = false;
            weaponRotation = 0.0f; 
        }
    }

    
    sf::Sprite weaponSprite;
    weaponSprite.setTexture(weapon);
    weaponSprite.setOrigin(weapon.getSize().x / 2.f, weapon.getSize().y / 2.f); 
    weaponSprite.setPosition(screen_w / 2 + bobbingOffsetX, screen_h - weapon.getSize().y / 2.f + bobbingOffsetY);
    weaponSprite.setRotation(weaponRotation); 
    weaponSprite.setScale(25.0f, 25.0f);

    target.draw(weaponSprite);

    int healthSection = 0;  
    
    if (player.health >= 67.0f) {
        healthSection = 2;  
    } else if (player.health >= 34.0f) {
        healthSection = 1;  
    }
if(player.health==90)
Resources::GameLost=true;
    
    healthSprite.setTextureRect(sf::IntRect(healthSection * 16, 0, 16, 16));
    healthSprite.setScale(3,3);
    healthSprite.setPosition(10.0f, 10.0f);
    target.draw(healthSprite);
    std::cout<<player.health<<" \n";
    
}
    

void::Render::init()    
{
    this->floortexture.loadFromFile("floor.png");
    this->rooftexture.loadFromFile("floor.png");
    Resources::spriteTexture.loadFromFile("poppix.png");
    Resources::spriteTexture2.loadFromFile("poppi2.png");
    this->weapon.loadFromFile("weapon.png");
    this->weaponsprite=sf::Sprite(weapon);
    if (!bulletTexture.loadFromFile("bullet.png")) 
       ;
        healthtexture.loadFromFile("life.png");
        this->healthSprite=sf::Sprite(healthtexture);
    
}