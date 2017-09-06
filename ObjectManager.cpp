#include "ObjectManager.h"
#include "PathFinding.h"
#include "Map.h"


cObjectManger::cObjectManger(){

}


cObjectManger::~cObjectManger(){

}

void cObjectManger::AddObject(int BuildID, sf::Vector2f pos){
    vBuildRequest.push_back(sBuildRequest());
    vBuildRequest.back().ID=BuildID;
    vBuildRequest.back().pos=pos;
}

void cObjectManger::Draw(sf::RenderWindow *hwnd){
    for(auto object : vSortedObjects){
        object->bDrawn=false;
        if(object->bPlayer){
            object->Draw(hwnd);
            object->bDrawn=true;
        }else if(VisibleArea.isVisible(object->GetPos())){
            object->Draw(hwnd);
            object->bDrawn=true;
        }
    
    }
    vSortedObjects.clear();
}


void cObjectManger::SetVisibleArea(){
    VisibleArea.Clear();
    for(auto object : vObjects){
        if(object->bPlayer)
            VisibleArea.AddLocal(object->GetPos());
    }
}


void cObjectManger::Update(sf::Time deltaTime){
    
    for(auto request : vBuildRequest){
        switch(request.ID){;
            case STORE_HOUSE:
                vObjects.push_back(new cStoreHouse(request.pos));
                break;
            case TRAINROOM:
                vObjects.push_back(new cTrainRoom(request.pos));
                break;
            case SERVICE_STATION:
                vObjects.push_back(new cServiceStation(request.pos));
                break;
            case WATER_FILTER:
                vObjects.push_back(new cWaterFilter(request.pos));
                break;
        }
    }
    vBuildRequest.clear();
    
    
    for(auto object : vObjects){
        if((!VisibleArea.isVisible(object->GetPos())&&object->EntType!=ALIEN)||!VisibleArea.isVisible(object->GetPos(),12)){
            object->vecMove.clear();
            continue;
        }
        
        object->Update(deltaTime);
        bool bRollBack=false;
        for(auto object2 : *this->GetObjectList()){
            if(object==object2)
                continue;
            if(object->type!=ENTITY||object2->type!=ENTITY)
                continue;
            
            auto Entity1=(cBaseEntity*)object;
            auto Entity2=(cBaseEntity*)object2;
            if(Entity1->IntersectsWith(Entity2)){
                if(!Entity1->Task.Active&&!Entity2->Task.Active&&
                   !Entity1->IsMoving()&&!Entity2->IsMoving()){
                    float flAngle=rand()%360-180;
                    sf::Vector2f vecMove=Ang2Vec(flAngle)*0.70f;
                    sf::Vector2f vecNewPos1=Entity1->GetPos()+vecMove;
                    sf::Vector2f vecNewPos2=Entity2->GetPos()-vecMove;
                    if(Path->isAccessible(Vec2Vec<float, int>(vecNewPos1)))
                        Entity1->Move(vecNewPos1);
                    if(Path->isAccessible(Vec2Vec<float, int>(vecNewPos2)))
                        Entity2->Move(vecNewPos2);
                }
            }
        }
        if(bRollBack&&object->type==ENTITY){
            auto Entity=(cBaseEntity*)object;
            Entity->RollbackToLastPos();
        }
    }
    
    sf::Vector2f newPos=sf::Vector2f(floorf(Camera->GetMapCursorPos().x), floorf(Camera->GetMapCursorPos().y));
    //spawn
    if(CVARS->iGetValue(var_Spawn)){
        if(Path->isAccessible(Vec2Vec<float,int>(Camera->GetMapCursorPos())))
        switch(CVARS->iGetValue(var_Spawn)){
            case 1:
                vObjects.push_back(new cEntityBasePlayer(Camera->GetMapCursorPos()));
                break;
            case 2:
                
                if(LocalPlayer.BuildID==WATER_FILTER){
                    for(auto object : vObjects){
                        if(object->type!=BUILDING||object->EntType!=PIPE)
                            continue;
                        
                        if(Length2D<float>(object->GetPos()-newPos)<=1.1f){
                            if(newPos.x==object->GetPos().x&&
                               newPos.y==object->GetPos().y)
                                continue;
                            
                            auto oldPipe=(cPipe*)object;
                            if(oldPipe->bConnected)
                                continue;
                            if(LocalPlayer.Pay()){
                                oldPipe->Connect(newPos-object->GetPos());
                                vObjects.push_back(new cConstruction(Camera->GetMapCursorPos(),LocalPlayer.BuildID));
                                oldPipe->bConnected=false;
                            }else{
                                SoundManger->PlaySound(SOUND_WRONG);
                            }
                            
                        }
                    }
                }else{
                    if(LocalPlayer.Pay()){
                        vObjects.push_back(new cConstruction(Camera->GetMapCursorPos(),LocalPlayer.BuildID));
                    }else{
                        SoundManger->PlaySound(SOUND_WRONG);
                    }
                }
                break;
            case 3:
                vObjects.push_back(new cCraterLarge(Camera->GetMapCursorPos()));
                break;
            case 4:
                if(GameWorld->GetID(Camera->GetMapCursorPos().x,Camera->GetMapCursorPos().y)==2){
                    if(LocalPlayer.Pay()){
                        vObjects.push_back(new cPipe(Camera->GetMapCursorPos(),true));
                    }else{
                        SoundManger->PlaySound(SOUND_WRONG);
                    }
                }else if(GameWorld->GetID(Camera->GetMapCursorPos().x,Camera->GetMapCursorPos().y)==1){
                    if(LocalPlayer.Pay()){
                        vObjects.push_back(new cPipe(Camera->GetMapCursorPos(),false));
                    }else{
                        SoundManger->PlaySound(SOUND_WRONG);
                    }
                }else{
                    for(auto object : vObjects){
                        if(object->type!=BUILDING||object->EntType!=PIPE)
                            continue;
                        
                        if(Length2D<float>(object->GetPos()-newPos)<=1.1f){
                            if(newPos.x==object->GetPos().x&&
                               newPos.y==object->GetPos().y)
                                continue;
                            
                            auto oldPipe=(cPipe*)object;
                            if(oldPipe->bConnected)
                                continue;
                            if(LocalPlayer.Pay()){
                                oldPipe->Connect(newPos-object->GetPos());
                                vObjects.push_back(new cPipe(newPos, newPos-object->GetPos()));
                            }else{
                                SoundManger->PlaySound(SOUND_WRONG);
                            }
                            
                        
                        }
                    }
                }
                break;
            case 5:
                vObjects.push_back(new cStoreHouse(Camera->GetMapCursorPos()));
                break;
            case 6:
                vObjects.push_back(new cEntityAlien(Camera->GetMapCursorPos()));
                break;
            case 7:
                vObjects.push_back(new cEntityBasePlayer(Camera->GetMapCursorPos(),true));
                break; 
        }
         
        CVARS->iSetValue(var_Spawn, 0);
    }
    
    
    vObjects.erase(std::remove_if(vObjects.begin(), vObjects.end(),[](cObject* i){
        if(i->Health<=0){
            delete i;
            return true;
        }
        return false;
    }),vObjects.end());
    
    for(auto object : vObjects)
        vSortedObjects.push_back(object);
    
    std::sort(vSortedObjects.begin(), vSortedObjects.end(),
              [] (cObject * v1, cObject * v2) { return W2S(v1->GetPos()).y+v1->RenderOff.y < W2S(v2->GetPos()).y+v2->RenderOff.y; });
    
    
}

int cObjectManger::GetNearestEnt(int type, sf::Vector2f pos){
    int retID=-1;
    float LastMaxDist=50.f;
    for(auto object : vObjects){
        if(object->type==BUILDING){
            auto Entity=(cBaseEntity*)object;
            float Dist=Length2D<float>(Entity->GetPos()-pos);
            if(Entity->EntType==type&&
               Dist<LastMaxDist){
                LastMaxDist=Dist;
                retID=Entity->unique_ID;
                
            }
        }
    }
    return retID;
}


cObject *cObjectManger::GetObject(int unique_ID){
    for(auto object : vObjects)
        if(object->unique_ID==unique_ID)
            return object;
    return nullptr;
}


void cObjectManger::Clear(){
    vObjects.clear();
    vSortedObjects.clear();
}

int cObjectManger::GetNumberOfPlayers(){
    int ret=0;
    for(auto object : vObjects){
        if(object->type==ENTITY&&(object->EntType==ASTRONAUT_WARRIOR||object->EntType==ASTRONAUT_STANDARD)){
            ret++;
        }
    }
    return ret;
}


bool cObjectManger::ServiceStationExist(){
    for(auto object : vObjects)
        if(object->type==BUILDING&&object->EntType==SERVICE_STATION)
            return true;
    return false;
}


int cObjectManger::GetPlayersHealthSum(){
    int ret=0;
    for(auto object : vObjects){
        if(object->type==ENTITY&&(object->EntType==ASTRONAUT_WARRIOR||object->EntType==ASTRONAUT_STANDARD)){
            ret+=object->Health;
        }
    }
    return ret;
}



