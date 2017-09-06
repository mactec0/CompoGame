#pragma once
#include "Camera.h"
#include "GlobalRender.h"
#include "ObjectManager.h"
#include "Utils.h"
#include "GUI.h"
#include "Map.h"

enum{
    SELECTOR,
    BUILDER
};

class cSelector{
    bool bisMouseClicked,bisMouseClickedOld, bRightClicked;
    sf::Vector2f vecStart, vecEnd;
    
    int Mode;
    int TextureBuilderID;
    
    int TrainRoomID;

public:
    cSelector(){
        Mode=SELECTOR;
        TrainRoomID=0;
    }
    
    void Train(){
        for(auto object : *ObjectManger->GetObjectList()){
            if(object->EntType==ASTRONAUT_STANDARD||object->EntType==ASTRONAUT_WARRIOR){
                auto Player=(cEntityBasePlayer*)object;
				if(Player->bSelected)
                Player->Trian(TrainRoomID);
            }
        }
    }
    
    void Draw(sf::RenderWindow *hwnd){
        
        if(Mode==SELECTOR){
            
            if(!bisMouseClicked||!bisMouseClickedOld){
                for(auto object : *ObjectManger->GetObjectList()){
                    if(object->type==BUILDING&&object->bDrawn){
                        auto Building=(cBaseBuilding*)object;
                        if(Camera->GetCursorPos().x>Building->GetSpriteRect().left&&
                           Camera->GetCursorPos().y>Building->GetSpriteRect().top&&
                           Camera->GetCursorPos().x<Building->GetSpriteRect().left+Building->GetSpriteRect().width&&
                           Camera->GetCursorPos().y<Building->GetSpriteRect().top+Building->GetSpriteRect().height){
                        GlobalRender->PrintText<std::string>(Building->GetMapName(), sf::Vector2f(Building->GetSpriteRect().left,Building->GetSpriteRect().top)+sf::Vector2f(Building->GetSpriteRect().width/2,Building->GetSpriteRect().height/2), sf::Color::White, FontManger->GetFont(0), 12, true);
                            break;
                        }
                        
                    }
                }
                return;
            }
            
            sf::Vector2f vecStart2D(flW2S(vecStart));
            sf::Vector2f vecEnd2D(flW2S(vecEnd));
            sf::Vector2i size(std::abs(vecStart2D.x-vecEnd2D.x),std::abs(vecStart2D.y-vecEnd2D.y));
            sf::Vector2f Pos;
            Pos.x=(vecStart2D.x<vecEnd2D.x)?vecStart2D.x:vecEnd2D.x;
            Pos.y=(vecStart2D.y<vecEnd2D.y)?vecStart2D.y:vecEnd2D.y;
            GlobalRender->DrawRect(Pos, size, sf::Color(255,200,140,85),sf::Color(250,110,55,255),2);
        }else if(Mode==BUILDER){
            sf::Vector2f vecStart2D(flW2S(sf::Vector2f(floor(vecStart.x),floor(vecStart.y))));
            sf::Sprite Sprite;
            Sprite.setTexture(*TextureManger->GetTexture(TextureBuilderID));
            switch(TextureBuilderID){
                case OBJ_FRAME_HIGH_TILE_NE:
                    Sprite.setOrigin(75, 24);
                    break;
                case OBJ_PIPE_STRAIGHT_NE:
                    Sprite.setOrigin(60, 0);
                    break;
                case OBJ_BARREL_LARGE_NE:
                    Sprite.setOrigin(40, -8);
                    break;
                case OBJ_URANIUM_TALL_ORE_NE:
                case OBJ_STONE_TALL_ORE_NE:
                    Sprite.setOrigin(40, 0);
                    break;
                default:
                    Sprite.setOrigin(75, 120/2);
                    break;
            }
            Sprite.setPosition(vecStart2D);
            Sprite.setColor(sf::Color(255,255,255,100));
            hwnd->draw(Sprite);
        }
    
        //GlobalRender->PrintInt(vecStart.x, sf::Vector2f(10,10), sf::Color::White, FontManger->GetFont(0), 10);
        //GlobalRender->PrintInt(vecStart.y, sf::Vector2f(20,10), sf::Color::White, FontManger->GetFont(0), 10);
        //GlobalRender->PrintInt(vecEnd.x, sf::Vector2f(10,20), sf::Color::White, FontManger->GetFont(0), 10);
        //GlobalRender->PrintInt(vecEnd.y, sf::Vector2f(20,20), sf::Color::White, FontManger->GetFont(0), 10);
    }
    
    void Update(){
        if(GUI->Active())
            return;
        bisMouseClicked=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        if(bisMouseClicked&&!bisMouseClickedOld){
            vecStart=Camera->GetMapCursorPos();
            vecEnd=Camera->GetMapCursorPos();
        }
        
        if(bRightClicked&&Mode==BUILDER)
            Mode=SELECTOR;
        
        if(Mode==BUILDER){
            vecStart=Camera->GetMapCursorPos();
        }
        
        if(Mode==SELECTOR&&bisMouseClicked&&bisMouseClickedOld){
            vecEnd=Camera->GetMapCursorPos();
            
            sf::Vector2i vecStart2D(W2S(vecStart));
            sf::Vector2i vecEnd2D(W2S(vecEnd));
            
            sf::Vector2i size(std::abs(vecStart2D.x-vecEnd2D.x),std::abs(vecStart2D.y-vecEnd2D.y));
            sf::Vector2f Pos;
            Pos.x=(vecStart2D.x<vecEnd2D.x)?vecStart2D.x:vecEnd2D.x;
            Pos.y=(vecStart2D.y<vecEnd2D.y)?vecStart2D.y:vecEnd2D.y;
            for(auto object : *ObjectManger->GetObjectList()){
                if(object->EntType!=ASTRONAUT_WARRIOR&&object->EntType!=ASTRONAUT_STANDARD)
                    continue;
                sf::Vector2i ObjScreenPos=object->GetScreenPos();
                if(ObjScreenPos.x>Pos.x&&ObjScreenPos.y>Pos.y&&
                   ObjScreenPos.x<Pos.x+size.x&&ObjScreenPos.y<Pos.y+size.y)
                    object->Select(true);
                else
                    object->Select(false);
            }
            
            /*sf::Vector2i size(std::abs(vecStart.x-vecEnd.x),std::abs(vecStart.y-vecEnd.y));
            sf::Vector2f Pos;
            Pos.x=(vecStart.x<vecEnd.x)?vecStart.x:vecEnd.x;
            Pos.y=(vecStart.y<vecEnd.y)?vecStart.y:vecEnd.y;
            for(auto object : *ObjectManger->GetObjectList()){
                if(object->GetPos().x>Pos.x&&object->GetPos().y>Pos.y&&
                   object->GetPos().x<Pos.x+size.x&&object->GetPos().y<Pos.y+size.y)
                    object->Select(true);
                else
                    object->Select(false);
            }*/
            
        }
        
        
        if(Mode==BUILDER&&bisMouseClicked){
            Mode=SELECTOR;
            switch(TextureBuilderID){
                case OBJ_URANIUM_TALL_ORE_NE:
                    GameConsole->SendCommand("/spawn 3");
                    break;
                case OBJ_PIPE_STRAIGHT_NE:
                    GameConsole->SendCommand("/spawn 4");
                    break;
                default:
                    GameConsole->SendCommand("/spawn 2");
                    break;
            }
            return;
        }
        
        
        bisMouseClickedOld=bisMouseClicked;
        
        
        if(Mode==SELECTOR&&!bisMouseClicked)
        if(sf::Mouse::isButtonPressed(sf::Mouse::Right)&&!bRightClicked){
            bool bNewTask=false;
            for(auto object : *ObjectManger->GetObjectList()){
                if(object->type==BUILDING&&object->bDrawn){
                    auto Building=(cBaseBuilding*)object;
                    if(Camera->GetCursorPos().x>Building->GetSpriteRect().left&&
                       Camera->GetCursorPos().y>Building->GetSpriteRect().top&&
                       Camera->GetCursorPos().x<Building->GetSpriteRect().left+Building->GetSpriteRect().width&&
                       Camera->GetCursorPos().y<Building->GetSpriteRect().top+Building->GetSpriteRect().height){
                        for(auto ObjectPlayer : *ObjectManger->GetObjectList()){
                            if(ObjectPlayer->type==ENTITY&&ObjectPlayer->bSelected&&ObjectPlayer->bPlayer){
                                if(object->EntType==URANIUM_ORE||
                                   object->EntType==STONE_ORE||
                                   object->EntType==METAL_ORE){//MineTask
                                    bNewTask=true;
                                    auto Entity=(cBaseEntity*)ObjectPlayer;
                                    Entity->Stop();
                                    Entity->MineTask(object->unique_ID);
                                    
                                }else if(object->EntType==STORE_HOUSE){
                                    auto Entity=(cBaseEntity*)ObjectPlayer;
                                    if(Entity->Resources.GetSum()>0&&
                                      (Entity->EntType==ASTRONAUT_STANDARD||Entity->EntType==ASTRONAUT_WARRIOR)){
                                        auto Player=(cEntityBasePlayer*)ObjectPlayer;
                                        Player->ReturnToStoreHouseAlone(object->unique_ID);
                                    }
                                    bNewTask=true;
                                }else if(object->EntType==WATER_FILTER){
                                    auto Entity=(cBaseEntity*)ObjectPlayer;
                                    if(Entity->EntType==ASTRONAUT_STANDARD||
                                       Entity->EntType==ASTRONAUT_WARRIOR){
                                        auto Player=(cEntityBasePlayer*)ObjectPlayer;
                                        Player->Drink(object->unique_ID);
                                    }
                                    bNewTask=true;
                                }else if(object->EntType==TRAINROOM){
                                    TrainRoomID=object->unique_ID;
                                    GUI->SetVisible(TRAIN_ROOM_WINDOW, true);
                                    bNewTask=true;
                                }else if(object->EntType==CONSTRUCTION){
                                    bNewTask=true;
                                    auto Entity=(cBaseEntity*)ObjectPlayer;
                                    Entity->Stop();
                                    Entity->BuildTask(object->unique_ID);
                                }
                                
                            }
                        }
                        
                        if(!bNewTask)
                            SoundManger->PlaySound(SOUND_WRONG);
                        break;
                    }
                    
                }
            }
            
            if(!bNewTask)
            for(auto object : *ObjectManger->GetObjectList()){
                if(object->bSelected&&object->type==ENTITY){
                    auto Entity=(cBaseEntity*)object;
                    auto Path =GameWorld->GetPath(Vec2Vec<float,int>(object->GetPos()), Vec2Vec<float,int>(Camera->GetMapCursorPos()));
                    if(!Path.empty()){
                        Entity->vecMove.clear();
                        Entity->Task.Active=false;
                        for(auto WayPoint: Path)
                        Entity->AddMove(Vec2Vec<int,float>(WayPoint));
                    }
                    
                }
            }
        }
        
        bRightClicked=sf::Mouse::isButtonPressed(sf::Mouse::Right);
         
    }

    void SetBuilder(int ID){
        TextureBuilderID=ID;
        Mode=BUILDER;
    }

};

extern cSelector *Selector;
