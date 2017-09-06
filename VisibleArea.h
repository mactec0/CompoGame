#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "Utils.h"

class cVisibleArea{
    std::vector<sf::Vector2f> vPos;
    float flVisRadius;
public:
    cVisibleArea(){
        flVisRadius=6.f;
    }
    bool isVisible(sf::Vector2f vecIN){
        for(auto LocalPos: vPos)
            if(Length2D<float>(LocalPos-vecIN)<=flVisRadius)
                return true;
        return false;
    }
    
    bool isVisible(sf::Vector2f vecIN, float Radius){
        for(auto LocalPos: vPos)
            if(Length2D<float>(LocalPos-vecIN)<=Radius)
                return true;
        return false;
    }
    
    void AddLocal(sf::Vector2f vecIN){
        vPos.push_back(vecIN);
    }
    
    void Clear(){
        vPos.clear();
    }

};

extern cVisibleArea VisibleArea;
