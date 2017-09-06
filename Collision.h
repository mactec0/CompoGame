#pragma once
#include <SFML/Graphics.hpp>
#include "Utils.h"

enum{
    Collision_TILE,
    Collision_RECT,
    Collision_Radius,
    Collision_NONE,
    
};

class cCollison {
    int type;
    sf::Vector2f vecOffset;
    sf::Vector2f vecSize;
    float radius;
    
public:
    cCollison()
    {};
    
    cCollison(int CollisionType)
    :type(CollisionType)
    {};
    
    cCollison(int CollisionType, sf::Vector2f nsize)
    :type(CollisionType), vecSize(nsize)
    {  };
    
    void SetBounds(sf::Vector2f sOffset, sf::Vector2f Size) {
        this->vecOffset = sOffset;
        this->vecSize = Size;
    }
    
    sf::Vector2f GetOffset() { return vecOffset;  }
    sf::Vector2f GetSize() { return vecSize; }
    float GetRadius() { return radius; }
    
    void SetType(int type) {
        this->type = type;
    }
    void SetRadius(float radius) {
        this->radius = radius;
    }
    
    void SetOffset(sf::Vector2f Offset) {
        this->vecOffset = Offset;
    }
    
    int GetType() { return type; }
    
    bool Intersect(cCollison *obj){
        if(type==obj->type&&type==Collision_Radius){
            float Dist=Length2D<float>(vecOffset-obj->GetOffset());
            float Radius2=radius+obj->GetRadius();
            Radius2/=Globals.TileHeight;//convert to world ~ more a less
            if(Dist<Radius2)
                return true;
        }
        return false;
    }
};



