#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

enum{
    FONT_MAIN,
    FONT_CONSOLE,
    FONT_MAXNUM,
};

class cFontManger{
    sf::Font fonts[FONT_MAXNUM];
public:
    cFontManger();
    ~cFontManger();
    
    bool LoadFont(std::string fname, int ID);
    
    sf::Font *GetFont(int ID);
};

extern cFontManger *FontManger;
