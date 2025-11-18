#pragma once
#include<SFML/Graphics.hpp>

class Grid{
    public:
    float x = 0;
    float y = 0;
    static constexpr int gridSize = 20; // rozmiar mapy gridSize*gridSize
    static constexpr float tileSize  = 32.f; // rozmiar jednej płytki 
    sf::RectangleShape tile;
    static void initTilemap(Grid tilemap[gridSize][gridSize]);
    static sf::Texture darkTex;
    static sf::Texture darkTwoTex;
};