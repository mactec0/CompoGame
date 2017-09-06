#pragma once
#include <vector>
#include "Object.h"
#include "CVAR.h"
#include "VisibleArea.h"

struct sBuildRequest{
    int ID;
    sf::Vector2f pos;
};

class cObjectManger {
    std::vector<cObject*> vSortedObjects;
    std::vector<sBuildRequest> vBuildRequest;
public:
    std::vector<cObject*> vObjects;
    cObjectManger();
    ~cObjectManger();
    
    void AddObject(int BuildID, sf::Vector2f pos);
    
    void Draw(sf::RenderWindow *hwnd);
    
    void SetVisibleArea();
    
    void Update(sf::Time deltaTime);
    
    int GetNearestEnt(int type, sf::Vector2f pos);
    
    cObject *GetObject(int unique_ID);
    
    std::vector<cObject*> *GetObjectList(){ return &vObjects; }
    
    void Clear();
    
    int GetNumberOfPlayers();
    
    bool ServiceStationExist();
    
    int GetPlayersHealthSum();
    
};

extern cObjectManger *ObjectManger;
