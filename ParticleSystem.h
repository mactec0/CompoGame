#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Globals.h"
#include "Utils.h"
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>

enum ParticleSystem{
    FIRE,
    MINE_HIT,
    STARS,
    BLOOD,
};

sf::Color HsvToRgb(float h, float s, float v);

struct sParticle{
    sParticle(sf::Vector2f Pos, float flAngle, float flRotation, float flSpeed, sf::Color col, int iLifeSpan, sf::CircleShape Shape, int type, bool bDrawOnMap=false){
        this->flAngle=flAngle;
        this->flRotation=flRotation;
        this->flSpeed=flSpeed;
        this->col=col;
        this->Shape=Shape;
        this->Pos=Pos;
        this->type=type;
        this->bDrawOnMap=bDrawOnMap;
        this->iLifeSpan=iLifeSpan;
        timer.restart();
    }
    ~sParticle(){
        
    }
    
    bool bDrawOnMap;
    sf::Clock timer;
    float flAngle;
    float flRotation;
    float flSpeed;
    int iLifeSpan;
    int type;
    sf::Color col;
    sf::CircleShape Shape;
    sf::Vector2f Pos;
    
    void Draw(sf::RenderWindow *hwnd){
        if(type==FIRE){
            float gVal=255.f*((float)timer.getElapsedTime().asMilliseconds()/(float)iLifeSpan);
            if(gVal>255.f)
                gVal=255;
            Shape.setFillColor(sf::Color(230,gVal,0,255));
        }else{
            Shape.setFillColor(col);
        }
        //Shape.setOrigin(Shape.getRadius()/2,Shape.getRadius()/2);
        //Shape.rotate(flRotation*timer.getElapsedTime().asMilliseconds());
        if(bDrawOnMap)
            Shape.setPosition(flW2S(Pos));
        else
            Shape.setPosition(Pos);
        
        hwnd->draw(Shape);
    }
    
    void Update(sf::Time deltaTime){
        Pos.x += (deltaTime.asSeconds()*flSpeed)*(cos(flAngle*M_PI/180));
        Pos.y += (deltaTime.asSeconds()*flSpeed)*(sin(flAngle*M_PI/180));
    }
    
    bool bIsValid(){
        if(iLifeSpan>timer.getElapsedTime().asMilliseconds())
            return true;
        return false;
    }
};

struct sParticleSystem{
    sParticleSystem(sf::Vector2f Pos, int type,int ID, float flAngle=0, int iLifeSpan=0, bool bDrawOnMap=false){
        this->flAngle=flAngle;
        if(type==MINE_HIT)
            this->flAngle=220-20+rand()%40;
            ParticlesCreated=0;
        this->type=type;
        this->iLifeSpan=iLifeSpan;
        this->Pos=Pos;
        this->ID=ID;
        this->bDrawOnMap=bDrawOnMap;
        timer.restart();
    }
    
    ~sParticleSystem(){
        vParticles.erase(std::remove_if(vParticles.begin(), vParticles.end(),[](sParticle* i){
            delete i;
            return true;
        }),vParticles.end());
    }
    
    void Update(sf::Time deltaTime){
        
        if(type==FIRE){
            vParticles.erase(std::remove_if(vParticles.begin(), vParticles.end(),[](sParticle* i){
                if(!i->bIsValid()){
                    delete i;
                    return true;
                }
                return false;
            }),vParticles.end());
            
            if(timer.getElapsedTime().asMilliseconds()>10)
            {
                timer.restart();
                for(int i=0;i<3;i++){
                    float partAng= flAngle-30+rand()%60;
                    float diff = abs(flAngle-partAng);
                    float Lifespan=((30+10-diff)/30)*800;
                    if(Lifespan>960)Lifespan=960;
                    vParticles.push_back(new sParticle(Pos, partAng, 0, 125, sf::Color::Magenta, Lifespan, sf::CircleShape(2+rand()%3,4),type));
                }
            }
        }else if(type==STARS){
            
            vParticles.erase(std::remove_if(vParticles.begin(), vParticles.end(),[](sParticle* i){
                if(i->Pos.x>Globals.Width){
                    delete i;
                    return true;
                }
                return false;
            
            }),vParticles.end());
            if(timer.getElapsedTime().asMilliseconds()>10)
            {
                timer.restart();
                for(int i=0;i<2;i++){
                    vParticles.push_back(new sParticle(sf::Vector2f(-5,rand()%Globals.Height), 0,0, 300+rand()%100, sf::Color(255,255,255,140+rand()%100), 2000, sf::CircleShape(2+rand()%3,3),type,bDrawOnMap));
                }
            }
        }else if(type==MINE_HIT){
            vParticles.erase(std::remove_if(vParticles.begin(), vParticles.end(),[](sParticle* i){
                if(!i->bIsValid()){
                    delete i;
                    return true;
                }
                return false;
            }),vParticles.end());
            
            if(timer.getElapsedTime().asMilliseconds()>100&&ParticlesCreated<3)
            {
                ParticlesCreated++;
                timer.restart();
                float partAng= flAngle-15+rand()%30;
                float Lifespan=150;
                vParticles.push_back(new sParticle(Pos, partAng, 0, 6, sf::Color(70,38,40,255), Lifespan, sf::CircleShape(8,5),type,true));
                
            }
        }else if(type ==BLOOD){
            vParticles.erase(std::remove_if(vParticles.begin(), vParticles.end(),[](sParticle* i){
                if(!i->bIsValid()){
                    delete i;
                    return true;
                }
                return false;
            }),vParticles.end());
            
            if(timer.getElapsedTime().asMilliseconds()>10&&ParticlesCreated<16)
            {
                ParticlesCreated++;
                timer.restart();
                float partAng= rand()%360;
                float Lifespan=80;
                vParticles.push_back(new sParticle(Pos, partAng, 0, 5, sf::Color(255,50,50,255), Lifespan, sf::CircleShape(4,3),type,true));
                
            }
        
        }
        
        for(auto Particle : vParticles)
           Particle->Update(deltaTime);
        
        
    }
    
    void Draw(sf::RenderWindow *hwnd){
        for(auto Particle : vParticles)
            Particle->Draw(hwnd);
    }
    
    int GetNumerOfParticles(){
        return vParticles.size();
    }
    
    bool RemoveSystem(){
        if(type==MINE_HIT&&ParticlesCreated>2&&vParticles.size()==0)
            return true;
        return false;
    }
    
    std::vector<sParticle*> vParticles;
    sf::Vector2f Pos;
    sf::Clock timer;
    float flCreateDuration;
    int type;
    float flAngle;
    int iLifeSpan;
    int ID;
    bool bDrawOnMap;
    int ParticlesCreated;
};

class cParticleSystem{
    std::vector<sParticleSystem*> vParticleSystems;
public:
    void SetPos(sf::Vector2f Pos, int ID){
        for(auto PSystem : vParticleSystems)
            if(PSystem->ID==ID)
                PSystem->Pos=Pos;
    }
    
    void Update(sf::Time deltaTime){
        
        vParticleSystems.erase(std::remove_if(vParticleSystems.begin(), vParticleSystems.end(),[](sParticleSystem* i){
            if(i->RemoveSystem()){
                delete i;
                return true;
            }
            return false;
        }),vParticleSystems.end());
        
        
        for(auto PSystem : vParticleSystems)
            PSystem->Update(deltaTime);
    }
    
    void Draw(sf::RenderWindow *hwnd){
        for(auto PSystem : vParticleSystems)
            PSystem->Draw(hwnd);
    }
    
    void AddEffect(sf::Vector2f Pos, int type,int ID, float Angle=0, bool iLifespan=0, bool bDrawOnMap = false){
        vParticleSystems.push_back(new sParticleSystem(Pos,type, ID, Angle, iLifespan, bDrawOnMap));
    }
    
    int GetNumerOfParticles(){
        int ret=0;
        for(auto PSystem : vParticleSystems)
            ret+=PSystem->GetNumerOfParticles();
        return ret;
    }
    
    void ClearAll(){
        vParticleSystems.erase(std::remove_if(vParticleSystems.begin(), vParticleSystems.end(),[](sParticleSystem* i){
            delete i;
            return true;
        }),vParticleSystems.end());
        
    }

};

extern cParticleSystem *ParticleSystem;
