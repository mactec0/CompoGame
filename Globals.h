#pragma once
#include <SFML/Graphics.hpp>
class cGlobals {
public:
    int Width, Height;
    int TileWidth, TileHeight;
    float dScroll;
	sf::Clock GameTimer;
    
    cGlobals() {
        Width = 1280;
        Height = 800;
        TileWidth=0;
        TileHeight=0;
        dScroll=0;
    }
    
};
extern cGlobals Globals;
