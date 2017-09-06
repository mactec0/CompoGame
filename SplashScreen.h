#pragma once
#include "FontManger.h"
#include "TextureManger.h"
#include "Globals.h"
#include "ParticleSystem.h"
#include <SFML/Graphics.hpp>

class cSpashScreen{
    sf::Sprite MenuSpaceCraft;
    float PosSpaceCraftY;
    bool bFlip;
    
    bool bTransitionPart;
    float flTransition;
    float flZoom;
    
public:
    cSpashScreen(){
        MenuSpaceCraft.setTexture(*TextureManger->GetTexture(OBJ_SPACECRAT4_W));
        MenuSpaceCraft.setPosition((Globals.Width/2)-(TextureManger->GetTexture(OBJ_SPACECRAT4_W)->getSize().x/2), 54);
        Reset();
    }
    
    void Reset(){
        PosSpaceCraftY=54;
        bFlip=true;
    }
    
    void ResetTransition(){
        bTransitionPart=false;
        flTransition=0;
        flZoom=1.f;
    }
    
    ~cSpashScreen(){
    
    }
    
    void UpdateMenuPlane(sf::Time dtime){
        static float flSpeed=25;
        
        flSpeed+=dtime.asSeconds()*20;
        if(flSpeed>25)
            flSpeed=25;
        
        PosSpaceCraftY+=(bFlip)?dtime.asSeconds()*flSpeed:-dtime.asSeconds()*flSpeed;
        
        if(PosSpaceCraftY>70){
            PosSpaceCraftY=70;
            bFlip=!bFlip;
            flSpeed=2;
        }
        if(PosSpaceCraftY<40){
            PosSpaceCraftY=40;
            bFlip=!bFlip;
            flSpeed=2;
        }
        
        ParticleSystem->SetPos(sf::Vector2f((Globals.Width/2)+(TextureManger->GetTexture(OBJ_SPACECRAT4_W)->getSize().x/2)-6,PosSpaceCraftY+60), 0);
        ParticleSystem->SetPos(sf::Vector2f((Globals.Width/2)+(TextureManger->GetTexture(OBJ_SPACECRAT4_W)->getSize().x/2)-6,PosSpaceCraftY+120), 1);
        
        if(bTransitionPart)
            flTransition-=dtime.asSeconds()*255;
        else
            flTransition+=dtime.asSeconds()*255/2;
        
        flZoom-=dtime.asSeconds()*0.6f;
        if(flZoom<0)
            flZoom=0;
    }
    
    void DrawMenuPlane(sf::RenderWindow *hwnd){
        MenuSpaceCraft.setPosition((Globals.Width/2)-(TextureManger->GetTexture(OBJ_SPACECRAT4_W)->getSize().x/2), PosSpaceCraftY);
        hwnd->draw(MenuSpaceCraft);
    }
    
    bool ShouldDrawMap(){
        return bTransitionPart;
    }
    
    float GetZoom(){
        return flZoom;
    }
    
    bool DrawTransition(sf::RenderWindow *hwnd){
        if(flTransition>255){
            flTransition=255;
            bTransitionPart=true;
        }
        
        if(flTransition<0){
            flTransition=0;
        }
        
        sf::RectangleShape rect(sf::Vector2f(0, 0));
        rect.setSize(sf::Vector2f(Globals.Width, Globals.Height));
        rect.setFillColor(sf::Color(0,0,0,flTransition));
        hwnd->draw(rect);
        
        return (flTransition==0&&bTransitionPart);
    }
};










