#pragma once

#include <stdio.h>
#include <stdint.h>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Utils.h"
#include "Camera.h"
#include "TextureManger.h"
#include "PathFinding.h"
#include "VisibleArea.h"
#include <SFML/Graphics.hpp>


enum MAP_TYPE_DATA{
    HEADER,
    TILESET,
    LAYER,
};

enum{
    LAYER_1=1,
    LAYER_2,
    LAYER_3
};

class cMap{
    uint16_t **DATA_LAYER;
    bool **COLLISION_LAYER; 
    bool bMapAllocated;
    
    
    int Width,Height,TileWidth,TileHeight;
    std::string strOrientation;
    std::string strTilesetPath;
    
    sf::Texture titleset_tex;
    std::vector<sf::Sprite> vSprites;
    sf::Vector2i DrawMin, DrawMax;
    
public:
    cMap();
    ~cMap();
    
    uint16_t GetID(int x, int y){ return DATA_LAYER[y][x];}
    
    void DrawTile(sf::Vector2<float> vec, int ID, sf::RenderWindow *hwnd, sf::Color col = sf::Color(255,255,255));
    bool Load(const char *fname);
    bool LoadTileSet(const char *fname);
    
    void Update(sf::Time deltaTime);
    void Draw(sf::RenderWindow *hwnd); 
    
    std::vector<sf::Vector2i> GetPath(sf::Vector2i vecStart, sf::Vector2i vecEnd){
        return Path->AStar(vecStart,vecEnd);
    }
    
    void Generate();
    
    void PlaceValley(sf::Vector2i Pos, int length, bool Direction);
    
private:
    void alloc(int x, int y);
    void ResetMap();
    

};

extern cMap *GameWorld;

