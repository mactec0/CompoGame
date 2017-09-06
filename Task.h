#pragma once

enum TASK_TYPE{
    NOTHING,
    MINE,
    BUILD,
    TRAIN,
    DRINK,
};


enum{
    MINE_ROAD_TO_ORE=1,
    MINE_MINING,
    MINE_ROAD_TO_STOREHOUSE,
    
    NORMAL_ROAD_TO_STOREHOUSE,
    
    BUILD_ROAD_TO_CONSTRUCTION,
    BUILD_BUILD,
    
    TRAIN_ROAD_TO_TRAINROOM,
    TRAIN_TRAIN_START,
    TRAIN_TRAIN_STOP,
    
    DRINK_ROAD_TO_WATER_FILTER,
    
};


class cTask{
public:
    cTask(){
        Active=false;
        type=NOTHING;
        state=MINE_ROAD_TO_ORE;
        
    }
    
    bool Active;
    int type,state;
    sf::Clock clock;
    int Delay;
    uint64_t ObjID;
    sf::Vector2i Pos;
    
    
    
    void SetDelay(int iDelay){
        Delay=iDelay;
        clock.restart();
    }
    
    bool ActiveAction(){
        if(clock.getElapsedTime().asMilliseconds()>Delay){
            clock.restart();
            return true;
        }
        return false;
    }

};
