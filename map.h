#pragma once
#include<SFML/Graphics.hpp>
#include<vector>

class Map
{
    public:

  bool isWalkable(const sf::Vector2f& position) const {
    
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    
    if (x >= 0 && x < grid[0].size() && y >= 0 && y < grid.size()) {
        return grid[y][x] == 0;  
    }

    
    return false;
}

    Map(float tilesize,int width,int height);
    Map(std::vector<std::vector<int>>grid);
    int getmapcell(int x,int y)const;
    void setmapcell(int x,int y,int value);
 bool isWall(int x, int y) {
        return grid[y][x] == 1;  
    }
    const std::vector<std::vector<int>>&getgrid()const;
    
    void draw(sf::RenderTarget &target,float tilesize);
    private:
    std::vector<std::vector<int>>grid;
};