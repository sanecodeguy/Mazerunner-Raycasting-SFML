
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "map.cpp"
#include "player.cpp"
#include "render.cpp"
#include "render.h"
#include "resources.cpp"
#include "sprite.cpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "sound.cpp"
using namespace sound;
enum class GameState
{
    Game,
    Menu
};
int main()
{
    GameState currentState = GameState::Game;
    sf::RenderWindow window(sf::VideoMode(screen_w, screen_h), "Maze Runner : The Golden Door", sf::Style::Close | sf::Style::Titlebar);
    std::vector<std::vector<int>> grid = {
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 2, 2, 2, 0, 3, 3, 3, 0, 4, 4, 4, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 2, 0, 0, 0, 3, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 2, 0, 1, 1, 3, 0, 4, 4, 4, 0, 1, 1, 1, 1, 1, 1, 0, 1}, {1, 0, 2, 0, 1, 0, 3, 0, 4, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 2, 0, 1, 0, 3, 0, 4, 4, 4, 0, 1, 0, 3, 3, 3, 0, 0, 1}, {1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 4, 0, 1, 0, 3, 0, 0, 0, 0, 1}, {1, 0, 3, 0, 1, 0, 1, 1, 1, 0, 4, 0, 1, 0, 3, 0, 1, 1, 0, 1}, {1, 0, 3, 0, 1, 0, 1, 0, 0, 0, 4, 0, 1, 0, 3, 0, 1, 0, 0, 1}, {1, 0, 3, 0, 1, 0, 1, 0, 2, 2, 4, 0, 1, 0, 3, 0, 1, 0, 1, 1}, {1, 0, 3, 0, 1, 0, 1, 0, 2, 0, 4, 0, 1, 0, 3, 0, 1, 0, 0, 1}, {1, 0, 0, 0, 1, 0, 1, 0, 2, 0, 4, 0, 1, 0, 3, 3, 3, 0, 0, 1}, {1, 1, 1, 1, 1, 0, 1, 0, 2, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}, {1, 0, 2, 2, 2, 0, 1, 0, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 2, 0, 0, 0, 1, 0, 2, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1}, {1, 0, 2, 0, 1, 1, 1, 0, 2, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 2, 0, 1, 0, 0, 0, 2, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1}, {1, 0, 3, 3, 3, 0, 1, 1, 3, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 3, 3, 3, 3, 3, 3, 0, 1}, {1, 0, 3, 0, 3, 3, 1, 0, 3, 3, 1, 0, 3, 0, 0, 0, 0, 0, 0, 1}, {1, 0, 3, 0, 0, 0, 1, 0, 0, 0, 1, 0, 3, 0, 1, 1, 1, 1, 0, 1}, {1, 0, 3, 0, 1, 1, 1, 1, 1, 0, 1, 0, 3, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 3, 0, 1, 0, 3, 3, 0, 1}, {1, 0, 4, 4, 4, 0, 1, 1, 1, 0, 1, 0, 3, 0, 1, 0, 0, 0, 0, 1}, {1, 0, 4, 0, 0, 0, 1, 0, 0, 0, 1, 0, 3, 0, 1, 1, 1, 1, 0, 1}, {1, 0, 4, 0, 1, 1, 1, 0, 3, 3, 1, 0, 0, 0, 0, 4, 3, 2, 2, 1}, {1, 0, 0, 0, 0, 0, 0, 0, 3, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 5}, {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};
    Map map(grid);
    Player maincharacter;
    Render render;
    render.init();
    std::vector<sprite> sprites;
    std::srand(static_cast<unsigned int>(std::time(0)));
    float offset = 0.3f;
    float sprite_width = 1.3f;
    float sprite_height = 1.3f;
    for (int i = 0; i < 32; i++)
    {
        int x, y;
        bool validPosition = false;

        while (!validPosition)
        {
            y = std::rand() % (grid[0].size() - 2) + 1;
            x = std::rand() % (grid.size() - 2) + 1;
            validPosition = true;
            for (int dx = -sprite_width; dx < sprite_width; dx++)
            {
                for (int dy = -sprite_height; dy < sprite_height; dy++)
                {

                    if (map.isWall(x + dx, y + dy) || x + dx < 0 || y + dy < 0 || x + dx >= grid[0].size() || y + dy >= grid.size())
                    {
                        validPosition = false;
                        break;
                    }
                }
                if (!validPosition)
                    break;
            }
        }
        sprites.push_back(sprite{{static_cast<float>(x), static_cast<float>(y)}, 0, false, 0.1f, 0.1f, 0.0f});
    }

    maincharacter.position = sf::Vector2f(1.2f, 1.2f);
    if (!Resources::wallTexture.loadFromFile("wall.png"))
        std::cerr << "unable to load wall textures \n";
    if (!Resources::weaponsound.loadFromFile("walk1.ogg"))
        std::cerr << "unable to load sound buffer \n";
    Resources::weaponsound2.loadFromFile("walk2.ogg");
    Resources::weaponsound3.loadFromFile("walk3.ogg");
    Resources::gamesound.loadFromFile("hero.ogg");
    Resources::menusound.loadFromFile("loop.ogg");
    Resources::hitsprite.loadFromFile("spritehit.ogg");
    Resources::playerbit.loadFromFile("playerbit.ogg");
    Resources::spritehit.loadFromFile("playerhit.ogg");
    // maincharacter.HealthFont.loadFromFile("font.otf");
    sf::Texture win,lost;
    win.loadFromFile("won.png");
    lost.loadFromFile("lost.png");
    sf::RectangleShape WIN(sf::Vector2f(800,500));
    WIN.setTexture(&win);

    // maincharacter.Health.setFont(maincharacter.HealthFont);

    sf::Clock clock;
    window.setMouseCursorVisible(false);
    sf::Vector2i lastMousePos = sf::Mouse::getPosition(window);
    sound::play(Resources::gamesound);

    while (window.isOpen())
    {

        float deltaT = clock.restart().asSeconds();
        sf::Event e;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2i mouseDelta = mousePos - lastMousePos;

        lastMousePos = mousePos;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
            {
                window.close();
            }
            if (e.type == sf::Event::KeyPressed && e.key.code == sf::Keyboard::Escape)
            {
                if (currentState == GameState::Game)
                {
                    currentState = GameState::Menu;
                }
                else if (currentState == GameState::Menu)
                {
                    currentState = GameState::Game;
                }
            }
            
        }
         for (auto &sprite : sprites)
            {
                sprite.animationTimer += 0.025f;

                if (sprite.animationTimer >= sprite.animationSpeed)
                {
                    sprite.animationTimer -= sprite.animationSpeed;
                    sprite.animationFrame = (sprite.animationFrame + 1) % 5;
                }
            }
        if (currentState == GameState::Game)
        {
            if(Resources::DoorFound)
            currentState=GameState::Menu;
        if(Resources::GameLost==true){currentState=GameState::Menu;}

           
            sound::update();
            maincharacter.update(deltaT, map, window, sprites);
            for (auto &spr : sprites)
            {
                spr.update(maincharacter.position, map, deltaT, window, maincharacter.health, maincharacter.Health);
            }
            window.clear();
            render.draw3D(window, maincharacter, map, sprites, deltaT);
        }
        else
        {
          if(Resources::DoorFound)
           window.draw(WIN);
           else 
           {
            WIN.setTexture(&lost);
            window.draw(WIN);
           }
        }
        window.display();
    }
}