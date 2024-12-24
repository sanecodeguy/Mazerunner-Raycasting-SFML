#include"map.h"
#include<SFML/Graphics.hpp>



int::Map::getmapcell(int x,int y)const
{
    if(y>=0 && y<grid.size() && x>=0 && x<grid[y].size())
    return grid[y][x];
    else return 0;
}
void::Map::setmapcell(int x,int y,int value)
{
    if(y>=0 && y<grid.size() && x>=0 && x<grid[y].size())
    this->grid[y][x]=value;
}
void::Map::draw(sf::RenderTarget &target,float tilesize)
{
    sf::RectangleShape background(
        sf::Vector2f( (float)grid[0].size()*tilesize,(float)grid.size()*tilesize));
        background.setFillColor(sf::Color::Cyan);
        target.draw(background);
        sf::RectangleShape cell(sf::Vector2f(tilesize*0.95f,tilesize*0.95f));

for(auto y=0;y<grid.size();y++)
{
    for(auto x=0;x<grid.size();x++)
    {
        if(grid[y][x]==0)cell.setFillColor(sf::Color::Black);
        else if(grid[y][x]==1)cell.setFillColor(sf::Color::White);
        cell.setPosition(sf::Vector2f(x,y)*tilesize + sf::Vector2f(tilesize*0.025f,tilesize*0.025f));
        target.draw(cell);
    }
}

}

Map::Map(std::vector<std::vector<int>>grid):grid(grid){;}

const std::vector<std::vector<int>>&Map::getgrid()const
{
    return this->grid;
}
