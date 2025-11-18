#include "grid.h"

sf::Texture Grid::darkTex("resources/tileDark.png");
sf::Texture Grid::darkTwoTex("resources/tileDark2.png");

void Grid::initTilemap(Grid tilemap[gridSize][gridSize]){
    bool tileChange = true; // pattern szachownicy
    for(int i = 0; i < gridSize; ++i){
        for(int j = 0; j < gridSize; ++j){
            tilemap[i][j].x = tileSize * j;
            tilemap[i][j].y = tileSize * i;
            tilemap[i][j].tile.setSize({tileSize, tileSize});
            if(tileChange){
                tilemap[i][j].tile.setTexture(&darkTex);
                tileChange = !tileChange;
            }else{
                tilemap[i][j].tile.setTexture(&darkTwoTex);
                tileChange = !tileChange;
            }
            tilemap[i][j].tile.setPosition({tilemap[i][j].x, tilemap[i][j].y});
        }
    tileChange = !tileChange;
    }
}