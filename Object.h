#pragma once 
#include "TextureManger.h"
#include "Camera.h"
#include "Collision.h"
#include "SoundManger.h"
#include "Utils.h"
#include "Task.h"
#include "ParticleSystem.h"
#include "PathFinding.h"
#include "LocalPlayer.h" 
#define _USE_MATH_DEFINES
#include <math.h>

enum{
    ENTITY,
    BUILDING
};

enum ENT_TYPE{
    STORE_HOUSE,
    PIPE,
    SERVICE_STATION,
    TRAINROOM,
    
    
    ASTRONAUT_STANDARD,
    ASTRONAUT_WARRIOR,
    
    METEOR_HALF,
    CRATER_LARGE,
    
    ALIEN,
    URANIUM_ORE,
    METAL_ORE,
    STONE_ORE,
    CONSTRUCTION,
    DESTROYED_SHIP,
    WATER_FILTER,
    ALIEN_BONES,
};


enum STATE{
    STAY,
    MOVE,
    ATTACK,
};

enum MOVE_ANIM{
    RIGHT=0,
    LEFT=3,
    UP=6,
    DOWN=9
};

enum DIRECTION{
    N,
    E,
    W,
    S,
    NE,
    NW,
    SE,
    SW,
    MAX
};

class cObject {
protected:
public:
    int type;
    bool bDrawn;
    sf::Vector2f Pos;
    sf::Vector2i RenderOff;
    sf::Vector2f LastPos;
    sf::Vector2f MoveTo;
    bool bSelected;
    short state;
    int Health;
    int EntType;
	int MaxHealth;
    uint64_t unique_ID;
    std::vector<sf::Vector2f> vecMove;
    bool bPlayer;
    cObject() {
        static uint64_t obj_count=0;
        Health=100;
        RenderOff=sf::Vector2i(0,0);
        bPlayer=false;
        unique_ID=obj_count;
        obj_count++;
        bDrawn=false;
		MaxHealth = 100;
    }
    
    virtual ~cObject(){
    
    }
    
    sf::Vector2f GetPos(){return Pos;}
    
    sf::Vector2i GetScreenPos(){
        return W2S(Pos);
    }
    void Stop(){MoveTo=Pos;state=STATE::STAY;vecMove.clear();};
    void Select(bool bVar){bSelected=bVar;}
    virtual void Draw(sf::RenderWindow *hwnd) = 0;
    virtual void DrawRenderBounds(sf::RenderWindow *hwnd) = 0;
    virtual void Update(sf::Time deltaTime) = 0;
    
    bool IsPlayer(){
        if(EntType==ASTRONAUT_STANDARD||EntType==ASTRONAUT_WARRIOR)
            return true;
        return false;
    }
    
    
};

class cBaseEntity: public cObject{
public:
    sf::Clock ThinkTimer;
    short lookDirection;
    float Speed;
    sf::Sprite Sprites[DIRECTION::MAX];
    sf::Clock Timer;
    short animation_state;
    float flColideRadius;
    cTask Task;
    sResources Resources;
    int MineAbility;
    cCollison *Collision;
    
    
    cBaseEntity(){
        type=ENTITY;
        MineAbility=0;
        ThinkTimer.restart();
        MaxHealth=100;
        Health=100;
    }
 
    bool IsMoving(){
        return (vecMove.size()>0)?true:false;
    }
    
    void Move(sf::Vector2f nPos){
        vecMove.clear();
        vecMove.push_back(nPos);
    }
    
    void AddMove(sf::Vector2f nPos){
        vecMove.push_back(nPos);
    }
    
    void UpdateMove(sf::Time deltaTime);
    
    bool GoToObject(int ID);
    
    void MineTask(int taskObjID);
    
    void BuildTask(int taskObjID);
    
    virtual void Update(sf::Time deltaTime);
    
    bool IntersectsWith(cBaseEntity *obj){
        if(obj->Collision){
            return Collision->Intersect(obj->Collision);
        }
        return false;
    }
    
    bool SetTaskPath(sf::Vector2i pos);
    
    virtual void RollbackToLastPos(){
        Pos = LastPos;
        Collision->SetOffset(Pos);
    }
    
    virtual void Draw(sf::RenderWindow *hwnd){
        int CurrentAnim=animation_state;
        
        sf::Vector2i veciRenderPos=W2S(Pos);
        sf::Vector2f vecRenderPos(veciRenderPos.x,veciRenderPos.y-(5-abs(CurrentAnim))*4);
        
        Sprites[lookDirection].setPosition(vecRenderPos);
        if(bSelected)
            DrawRenderBounds(hwnd);
        
        
        hwnd->draw(Sprites[lookDirection]);

    }
    
    virtual void DrawRenderBounds(sf::RenderWindow *hwnd){
        sf::Vector2i veciRenderPos=W2S(Pos);
        sf::Vector2f vecRenderPos(veciRenderPos.x,veciRenderPos.y);
        GlobalRender->DrawOutlineCircle(vecRenderPos,flColideRadius,sf::Color(66, 226, 244,255));

    }
    
    
    
    virtual void DIE(){}

};

class cEntityBasePlayer :public cBaseEntity{
    sf::Sprite WeaponSprite[4];
    sf::Vector2f LaserEnd;
    sf::Clock LaserTimer;
    
public:
    cEntityBasePlayer(){}
    cEntityBasePlayer(sf::Vector2f StartPos, bool bIsWarrior=false){
        for(int i=0;i<DIRECTION::MAX;i++){
            Sprites[i].setTexture(*TextureManger->GetTexture(OBJ_ASTRONAUT_N+i));
            Sprites[i].setOrigin(TextureManger->GetTexture(OBJ_ASTRONAUT_N+i)->getSize().x/2.f,TextureManger->GetTexture(OBJ_ASTRONAUT_N+i)->getSize().y*0.8f);
        }
        
        flColideRadius = TextureManger->GetTexture(OBJ_ASTRONAUT_N)->getSize().x*0.4f;
        
        MineAbility=10;
        state=STATE::STAY;
        lookDirection=DIRECTION::S;
        Pos=StartPos;
        LastPos=Pos;
        MoveTo=StartPos;
        Timer.restart();
        animation_state=-5;
        Speed=2.2f;
        bSelected=false;
        Collision= new cCollison(Collision_Radius);
        Collision->SetRadius(flColideRadius);
        Collision->SetOffset(Pos);
        bPlayer=true;
        EntType=ASTRONAUT_STANDARD;
        
        Health=100;
        MaxHealth=100;
        
        LaserEnd=sf::Vector2f(0.f,0.f);
        LaserTimer.restart();
        for(int i=0;i<4;i++){
            WeaponSprite[i].setTexture(*TextureManger->GetTexture(OBJ_ITEM_WEAPON_NE+i));
            WeaponSprite[i].setOrigin(4,14);
        }
        
        if(bIsWarrior){
            MineAbility=5;
            Speed=2.f;
            EntType=ASTRONAUT_WARRIOR;
        }
    }
    
    void ReturnToStoreHouseAlone(int StoreHouseID);
    
    void Drink(int FilterID);
    
    void Trian(int TrainRoomID);

    void DrawLaser(sf::RenderWindow *hwnd){
        if(LaserEnd!=sf::Vector2f(0.f,0.f)&&LaserTimer.getElapsedTime().asMilliseconds()<220){
            sf::Vertex line[] =
            {
                sf::Vertex(Vec2Vec<int,float>(W2S(Pos))),
                sf::Vertex(Vec2Vec<int,float>(W2S(LaserEnd))+sf::Vector2f(0.f,-16.f))
            };
            line[0].color = sf::Color::Red;
            line[1].color = sf::Color::Red;
            
            hwnd->draw(line, 2, sf::Lines);
        }

    }
    
    virtual void Draw(sf::RenderWindow *hwnd){
        int CurrentAnim=animation_state;
        
        sf::Vector2i veciRenderPos=W2S(Pos);
        sf::Vector2f vecRenderPos(veciRenderPos.x,veciRenderPos.y-(5-abs(CurrentAnim))*4);
        
        Sprites[lookDirection].setPosition(vecRenderPos);
        if(bSelected)
            DrawRenderBounds(hwnd);
        
        int WeaponDIR;
        if(EntType==ASTRONAUT_WARRIOR){
            switch(lookDirection){
                case DIRECTION::NW:
                    WeaponDIR=0;
                    WeaponSprite[WeaponDIR].setOrigin(34,15);
                    break;
                case DIRECTION::W:
                    WeaponDIR=0;
                    WeaponSprite[WeaponDIR].setOrigin(16,18);
                    break;
                case DIRECTION::SW:
                    WeaponDIR=3;
                    WeaponSprite[WeaponDIR].setOrigin(4,14);
                    break;
                case DIRECTION::S:
                    WeaponDIR=3;
                    WeaponSprite[WeaponDIR].setOrigin(-8,20);
                    break;
                case DIRECTION::SE:
                    WeaponDIR=2;
                    WeaponSprite[WeaponDIR].setOrigin(-8,38);
                    break;
                case DIRECTION::E:
                    WeaponDIR=2;
                    WeaponSprite[WeaponDIR].setOrigin(8,38);
                    break;
                case DIRECTION::NE:
                    WeaponDIR=1;
                    WeaponSprite[WeaponDIR].setOrigin(30,40);
                    break;
                case DIRECTION::N:
                    WeaponDIR=1;
                    WeaponSprite[WeaponDIR].setOrigin(35,30);
                    break;
            };
            
            
            WeaponSprite[WeaponDIR].setPosition(vecRenderPos);
            if(lookDirection==DIRECTION::NW||
               lookDirection==DIRECTION::W||
               lookDirection==DIRECTION::SW||
               lookDirection==DIRECTION::S){
                hwnd->draw(Sprites[lookDirection]);
                DrawLaser(hwnd);
                hwnd->draw(WeaponSprite[WeaponDIR]);
            }else{
                hwnd->draw(WeaponSprite[WeaponDIR]);
                DrawLaser(hwnd);
                hwnd->draw(Sprites[lookDirection]);
            }
            
        }else{
            
            hwnd->draw(Sprites[lookDirection]);
        
        }
		if (bSelected) {
			float BarLength = 28;
			sf::Vector2f vecBarRenderPos(veciRenderPos.x, veciRenderPos.y);
			sf::Vector2f BarPos(vecBarRenderPos.x - BarLength / 2, vecBarRenderPos.y - 50);
			GlobalRender->DrawFilledRect(BarPos, sf::Vector2i(BarLength, 4), sf::Color::Red);
			GlobalRender->DrawFilledRect(BarPos, sf::Vector2i(((float)Health / (float)MaxHealth)*BarLength, 4), sf::Color::Green);
		}
    }
    
    
    
    ~cEntityBasePlayer(){
        SoundManger->PlaySound(SOUND_PLAYER_DIE);
    }
    
    
    virtual void Update(sf::Time deltaTime);
    
};

 

class cEntityAlien :public cBaseEntity{
    int TargetID;
    int ThinkDelay;
    
    
    sf::Clock SoundTimer;
public:
    cEntityAlien(sf::Vector2f StartPos){
        for(int i=0;i<DIRECTION::MAX;i++){
            Sprites[i].setTexture(*TextureManger->GetTexture(OBJ_ALIEN_N+i));
            Sprites[i].setOrigin(TextureManger->GetTexture(OBJ_ALIEN_N+i)->getSize().x/2.f,TextureManger->GetTexture(OBJ_ALIEN_N+i)->getSize().y*0.8f);
        }
        
        flColideRadius = TextureManger->GetTexture(OBJ_ALIEN_N)->getSize().x*0.4f;
        
        state=STATE::STAY;
        lookDirection=DIRECTION::S;
        Pos=StartPos;
        LastPos=Pos;
        MoveTo=StartPos;
        Timer.restart();
        animation_state=-5;
        Speed=1.75f;
        bSelected=false;
        Collision= new cCollison(Collision_Radius);
        Collision->SetRadius(flColideRadius);
        Collision->SetOffset(Pos);
        bPlayer=false;
        EntType=ALIEN;
        TargetID=-1;
        Health=75;
        MaxHealth=75;
        
        ThinkDelay=0;
        ThinkTimer.restart();
        SoundTimer.restart();
    }
    
    
    ~cEntityAlien(){
    }
    
    virtual void Update(sf::Time deltaTime);
    
};




class cBaseBuilding: public cObject{
public:
    sf::Sprite Sprite;
    sf::Clock Timer;
    float flColideRadius;
    std::string MapName;
    
    cBaseBuilding(){
        type=BUILDING;
        MapName=" ";
    }
    
    virtual void Update(sf::Time deltaTime){
        LastPos=Pos;
    }
    
    virtual void Draw(sf::RenderWindow *hwnd){
        sf::Vector2i vecRenderPos=W2S(Pos);
        Sprite.setPosition(Vec2Vec<int,float>(vecRenderPos));
        
        if(bSelected)
            DrawRenderBounds(hwnd);
        
        
        hwnd->draw(Sprite);
        
    }
    
    virtual void DrawRenderBounds(sf::RenderWindow *hwnd){
        sf::Vector2i veciRenderPos=W2S(Pos)+RenderOff;
        sf::Vector2f vecRenderPos(veciRenderPos.x,veciRenderPos.y);
        GlobalRender->DrawOutlineCircle(vecRenderPos,flColideRadius,sf::Color(66, 226, 244,255));

    }
    
    std::string GetMapName(){return MapName;}
    
    sf::FloatRect GetSpriteRect(){
        return Sprite.getGlobalBounds();
    }
    
};


class cConstruction :public cBaseBuilding{
public:
    int BuildID;
    cConstruction(sf::Vector2f StartPos, int BuildID){
        MapName="Construction";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Health=100;
        switch(BuildID){
            case STORE_HOUSE:
                Sprite.setTexture(*TextureManger->GetTexture(OBJ_BUILDING_CORRIDOR_OPEN_NE));
                Sprite.setOrigin(75, 120/2);
                break;
            case TRAINROOM:
                Sprite.setTexture(*TextureManger->GetTexture(OBJ_BUILDING_OPEN_NE));
                Sprite.setOrigin(75, 120/2);
                break;
            case SERVICE_STATION:
                Sprite.setTexture(*TextureManger->GetTexture(OBJ_FRAME_HIGH_TILE_NE));
                Sprite.setOrigin(75, 24);
                break;
            case WATER_FILTER:
                Sprite.setTexture(*TextureManger->GetTexture(OBJ_BARREL_LARGE_NE));
                Sprite.setOrigin(40, -8);
                break;
        }
        
        Sprite.setColor(sf::Color(250,250,120,255));
        
        this->BuildID=BuildID;
        
        bPlayer=true;
        
        
        EntType=CONSTRUCTION;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cConstruction();
};


class cStoreHouse :public cBaseBuilding{
public:
    cStoreHouse(sf::Vector2f StartPos){
        MapName="Store House";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_BUILDING_CORRIDOR_OPEN_NE));
        Sprite.setOrigin(75, 120/2);
        Sprite.setColor(sf::Color(170,220,150,255));
        
        
        bPlayer=true;
        
        Health=100;
        
        EntType=STORE_HOUSE;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cStoreHouse(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
};

class cAlienBonez :public cBaseBuilding{
public:
    cAlienBonez(sf::Vector2f StartPos){
        MapName="Alien bones";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_ALIEN_BONES_NE+rand()%4));
        Sprite.setOrigin(50, -8);
        
        bPlayer=false;
        
        Health=100;
        
        EntType=ALIEN_BONES;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cAlienBonez(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
};



class cMeteorHalf :public cBaseBuilding{
public:
    cMeteorHalf(sf::Vector2f StartPos){
        MapName="Meteor Half";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_METEOR_HALF_NE+rand()%4));
        Sprite.setOrigin(60, -8);
        
        bPlayer=false;
        
        Health=100;
        
        EntType=METEOR_HALF;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cMeteorHalf(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
};

class cCraterLarge :public cBaseBuilding{
public:
    cCraterLarge(sf::Vector2f StartPos){
        MapName="Crater Large";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_CRATER_LARGE_NE+rand()%4));
        Sprite.setOrigin(47, -16);
        
        bPlayer=false;
        
        Health=100;
        
        EntType=METEOR_HALF;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cCraterLarge(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
};


class cTrainRoom :public cBaseBuilding{
    sf::Sprite TileSprite;
public:
    cTrainRoom(sf::Vector2f StartPos){
        MapName="Barracks";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_BUILDING_OPEN_NE));
        Sprite.setOrigin(75, 60+16);
        TileSprite.setTexture(*TextureManger->GetTexture(OBJ_FRAME_LOW_TILE_NE));
        TileSprite.setOrigin(69, -8+16);
        
        
        
        bPlayer=true;
        
        Health=100;
        
        EntType=TRAINROOM;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cTrainRoom(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
    
    virtual void Draw(sf::RenderWindow *hwnd){
        sf::Vector2i vecTileRenderPos=W2S(Pos);
        TileSprite.setPosition(Vec2Vec<int,float>(vecTileRenderPos));
        
        sf::Vector2i vecRenderPos=W2S(Pos);
        Sprite.setPosition(Vec2Vec<int,float>(vecRenderPos));
        
        hwnd->draw(TileSprite);
        hwnd->draw(Sprite);
    }
};

class cWaterFilter :public cBaseBuilding{
public:
    cWaterFilter(sf::Vector2f StartPos){
        MapName="Water Filter";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_BARREL_LARGE_NE));
        Sprite.setOrigin(40, -8);
        
        
        bPlayer=true;
        
        Health=30;
        
        EntType=WATER_FILTER;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cWaterFilter(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
};

class cPipe :public cBaseBuilding{
    bool StartPipe;
    bool Rotate;
    sf::Vector2f FirstDiff;
public:
    bool bConnected;
    
    cPipe(sf::Vector2f StartPos, bool rotation){
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(rotation?OBJ_PIPE_STRAIGHT_NE:OBJ_PIPE_STRAIGHT_NW));
        Sprite.setOrigin(60, 0);
        Rotate=rotation;
        
        
        Pos=StartPos;
        LastPos=Pos;
        MoveTo=StartPos;
        init();
        StartPipe=true;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
    }
    
    cPipe(sf::Vector2f StartPos, sf::Vector2f Diff){
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture((Diff.y==0)?OBJ_PIPE_STRAIGHT_NE:OBJ_PIPE_STRAIGHT_NW));
        Sprite.setOrigin(60, 0);
        Rotate=(Diff.y==0)?true:false;
        
        FirstDiff=Diff;
        
        Pos=StartPos;
        LastPos=Pos;
        MoveTo=StartPos;
        init();
        StartPipe=false;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
    }
    void Connect(sf::Vector2f diff){
        Sprite.setOrigin(60, 0);
        bConnected=true;
        if(StartPipe){
            if(Rotate){
                if(diff.y==1){
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_SPLIT_NE));
                }else{
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_SPLIT_SE));
                }
            }else{
                if(diff.x==1){
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_SPLIT_SW));
                }else{
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_SPLIT_NW));
                }
            }
        }else{
            if(Rotate){
                if(diff.x==1){
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_STRAIGHT_NE));
                }else if(diff.x==-1){
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_STRAIGHT_NE));
                }else if(diff.y==1){
                    Sprite.setTexture(*TextureManger->GetTexture((FirstDiff.x==-1)?OBJ_PIPE_CORNER_SW:OBJ_PIPE_CORNER_NE));
                    if(FirstDiff.x==-1)
                        Sprite.setOrigin(60, -18);
                }else if(diff.y==-1){
                    Sprite.setTexture(*TextureManger->GetTexture((FirstDiff.x==-1)?OBJ_PIPE_CORNER_SE:OBJ_PIPE_CORNER_NW));
                    if(FirstDiff.x==-1)
                        Sprite.setOrigin(42, 0);
                    
                }
            }else{
                if(diff.x==1){
                    Sprite.setTexture(*TextureManger->GetTexture((FirstDiff.y==-1)?OBJ_PIPE_CORNER_SW:OBJ_PIPE_CORNER_SE));
                    if(FirstDiff.y==-1)
                        Sprite.setOrigin(60, -18);
                    if(FirstDiff.y==1)
                        Sprite.setOrigin(42, 0);
                }else if(diff.x==-1){
                    Sprite.setTexture(*TextureManger->GetTexture((FirstDiff.y==-1)?OBJ_PIPE_CORNER_NE:OBJ_PIPE_CORNER_NW));
                }else if(diff.y==1){
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_STRAIGHT_NW));
                }else if(diff.y==-1){
                    Sprite.setTexture(*TextureManger->GetTexture(OBJ_PIPE_STRAIGHT_NW));
                    
                }
            }
        }
    }
    
    void init(){
        bConnected=false;
        bPlayer=false;
        Health=100;
        EntType=PIPE;
        RenderOff=sf::Vector2i(0,50);
        Timer.restart();
        bSelected=false;
        MapName="PIPE";
    }
    
    ~cPipe(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
    
};

class cServiceStation :public cBaseBuilding{
    sf::Sprite ScreenSprite, AntennaSprite;
public:
    cServiceStation(sf::Vector2f StartPos){
        MapName="Service Station";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_FRAME_HIGH_TILE_NE));
        Sprite.setOrigin(75, 24);
        ScreenSprite.setTexture(*TextureManger->GetTexture(OBJ_CONSOLE_SCREEN_SE));
        ScreenSprite.setOrigin(-6, -12);
        AntennaSprite.setTexture(*TextureManger->GetTexture(OBJ_SATELLITE_DISH_ANTENNA_LARGE_NW));
        AntennaSprite.setOrigin(56, 58);
        
        
        GUI->SetVisible(SERVICE_WINDOW, true);
        
        
        bPlayer=true;
        
        Health=100;
        
        EntType=SERVICE_STATION;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cServiceStation(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
    }
    
    virtual void Draw(sf::RenderWindow *hwnd){
        sf::Vector2i vecScreenRenderPos=W2S(Pos);
        ScreenSprite.setPosition(Vec2Vec<int,float>(vecScreenRenderPos));
        
        sf::Vector2i vecAntennaRenderPos=W2S(Pos);
        AntennaSprite.setPosition(Vec2Vec<int,float>(vecAntennaRenderPos));
        
        sf::Vector2i vecRenderPos=W2S(Pos);
        Sprite.setPosition(Vec2Vec<int,float>(vecRenderPos));
        
        hwnd->draw(Sprite);
        hwnd->draw(AntennaSprite);
        hwnd->draw(ScreenSprite);
    }
};

class cDestroyedShip :public cBaseBuilding{
public:
    cDestroyedShip(sf::Vector2f StartPos){
        MapName="Destroyed Ship";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_SPACESHIP_DESTROYED));
        Sprite.setOrigin(132, -34);
        Sprite.setColor(sf::Color(65,65,65,255));
        
        
        bPlayer=true;
        
        Health=99999999999;
        
        EntType=DESTROYED_SHIP;
        
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=70;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y+1, true);
        Path->SetUnAvailable((int)Pos.x+1, (int)Pos.y, true);
        Path->SetUnAvailable((int)Pos.x+1, (int)Pos.y+1, true);
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cDestroyedShip(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y+1, false);
        Path->SetUnAvailable((int)Pos.x+1, (int)Pos.y, false);
        Path->SetUnAvailable((int)Pos.x+1, (int)Pos.y+1, false);
    }
};




class cTallUraniumOre :public cBaseBuilding{
public:
    cTallUraniumOre(sf::Vector2f StartPos){
        MapName="Uranium Ore";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_URANIUM_TALL_ORE_NE+rand()%4));
        Sprite.setOrigin(40, 0);
        
        Health=1000;
        EntType=URANIUM_ORE;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=10;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cTallUraniumOre(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        SoundManger->PlaySound(SOUND_ORE_DESTROYED);
    }
};

class cTallStoneOre :public cBaseBuilding{
public:
    cTallStoneOre(sf::Vector2f StartPos){
        MapName="Stone Ore";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_STONE_TALL_ORE_NE+rand()%4));
        Sprite.setOrigin(40, 0);
        
        
        Health=1000;
        EntType=STONE_ORE;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=10;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cTallStoneOre(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        SoundManger->PlaySound(SOUND_ORE_DESTROYED);
    }
};

class cTallMetalOre :public cBaseBuilding{
public:
    cTallMetalOre(sf::Vector2f StartPos){
        MapName="Metal Ore";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_STONE_TALL_ORE_NE+rand()%4));
        Sprite.setOrigin(40, 0);
        Sprite.setColor(sf::Color(160,160,160,255));
        
        Health=1000;
        EntType=METAL_ORE;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=10;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cTallMetalOre(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        SoundManger->PlaySound(SOUND_ORE_DESTROYED);
    }
};



class cSmallUraniumOre :public cBaseBuilding{
public:
    cSmallUraniumOre(sf::Vector2f StartPos){
        MapName="Uranium Ore";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_URANIUM_SMALL_ORE_NE+rand()%4));
        Sprite.setOrigin(40, 0);
        
        Health=300;
        EntType=URANIUM_ORE;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=10;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cSmallUraniumOre(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        SoundManger->PlaySound(SOUND_ORE_DESTROYED);
    }
};

class cSmallStoneOre :public cBaseBuilding{
public:
    cSmallStoneOre(sf::Vector2f StartPos){
        MapName="Stone Ore";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_STONE_SMALL_ORE_NE+rand()%4));
        Sprite.setOrigin(40, 0);
        Health=300;
        
        EntType=STONE_ORE;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=10;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cSmallStoneOre(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        SoundManger->PlaySound(SOUND_ORE_DESTROYED);
    }
};


class cSmallMetalOre :public cBaseBuilding{
public:
    cSmallMetalOre(sf::Vector2f StartPos){
        MapName="Metal Ore";
        StartPos.x=floorf(StartPos.x);
        StartPos.y=floorf(StartPos.y);
        Sprite.setTexture(*TextureManger->GetTexture(OBJ_STONE_SMALL_ORE_NE+rand()%4));
        Sprite.setOrigin(40, 0);
        Health=300;
        Sprite.setColor(sf::Color(160,160,160,255));
        
        EntType=METAL_ORE;
        RenderOff=sf::Vector2i(0,50);
        flColideRadius=10;
        Pos=StartPos;
        LastPos=Pos;
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, true);
        
        MoveTo=StartPos;
        Timer.restart();
        bSelected=false;
    }
    
    ~cSmallMetalOre(){
        Path->SetUnAvailable((int)Pos.x, (int)Pos.y, false);
        SoundManger->PlaySound(SOUND_ORE_DESTROYED);
    }
};

