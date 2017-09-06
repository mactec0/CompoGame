#include "ObjectManager.h"
#include "PathFinding.h"
#include "LocalPlayer.h"
#include "Map.h"


cConstruction::~cConstruction(){
    ObjectManger->AddObject(BuildID, GetPos());
}


bool cBaseEntity::GoToObject(int ID){
    if(ID!=-1){
        cBaseBuilding *Object = (cBaseBuilding*)ObjectManger->GetObject(ID);
        if(Object!=nullptr){
            const sf::Vector2i neighbors[]={{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
                { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }};
            Task.Pos=sf::Vector2i(-1,-1);
            
            for(int i=0;i<8;i++)
                if(!Path->OutOfBounds(Vec2Vec<float,int>(Object->GetPos())+neighbors[i])&&Path->isAccessible(Vec2Vec<float,int>(Object->GetPos())+neighbors[i])){
                    Task.Pos=Vec2Vec<float,int>(Object->GetPos())+neighbors[i];
                    break;
                }
            
            if(Task.Pos==sf::Vector2i(-1,-1))
                return false;
            
            auto Path =GameWorld->GetPath(Vec2Vec<float,int>(GetPos()), (Task.Pos));
            if(!Path.empty()){
                this->vecMove.clear();
                this->Task.Active=true;
                for(auto WayPoint: Path)
                    this->AddMove(Vec2Vec<int,float>(WayPoint));
                
            }else{
                Task.Active=false;
            }
        }else{
            Task.Active=false;
        }
        
    }else{
        std::cout<<"Cannot find path\n";
        Task.Active=false;
    }
    return Task.Active;
}


void cBaseEntity::MineTask(int taskObjID){
    
    if(GoToObject(taskObjID)){
        Task.Active=true;
        Task.type=MINE;
        Task.ObjID=taskObjID;
        Task.state=MINE_ROAD_TO_ORE;
    
    }
}

void cBaseEntity::BuildTask(int taskObjID){
    if(GoToObject(taskObjID)){
        Task.Active=true;
        Task.type=BUILD;
        Task.ObjID=taskObjID;
        Task.state=BUILD_ROAD_TO_CONSTRUCTION;
        
    }
}



bool cBaseEntity::SetTaskPath(sf::Vector2i pos){
    const sf::Vector2i neighbors[]={{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }};
    Task.Pos=sf::Vector2i(-1,-1);
    std::vector<sf::Vector2i> vecPos;
    
    for(int i=0;i<8;i++)
        if(!Path->OutOfBounds(pos+neighbors[i])&&Path->isAccessible(pos+neighbors[i])){
            vecPos.push_back(pos+neighbors[i]);
            break;
        }
    
    if(vecPos.size()<=0)
        return false;
    
    Task.Pos=vecPos[rand()%vecPos.size()];
    
    auto Path = GameWorld->GetPath(Vec2Vec<float,int>(GetPos()), (Task.Pos));
    if(!Path.empty()){
        this->vecMove.clear();
        this->Task.Active=true;
        for(auto WayPoint: Path)
            this->AddMove(Vec2Vec<int,float>(WayPoint));
        return true;
    }
    return false;
}


void cEntityBasePlayer::Update(sf::Time deltaTime){
    if(Task.Active){
		if(vecMove.size()==0)
        if(Task.type==MINE&&Task.state==MINE_ROAD_TO_ORE){
            if(Length2D<float>((Vec2Vec<int,float>(Task.Pos)+sf::Vector2f(0.5f,0.5f)-Pos))<=1.2f){
                Task.state=MINE_MINING;
                Task.SetDelay(1000);
                vecMove.clear();
            }
        }else if(Task.type==MINE&&(Task.state==MINE_ROAD_TO_STOREHOUSE||Task.state==NORMAL_ROAD_TO_STOREHOUSE)){
            if(Length2D<float>((Vec2Vec<int,float>(Task.Pos)+sf::Vector2f(0.5f,0.5f))-Pos)<=1.2f){
                Task.Active=false;
                vecMove.clear();
                LocalPlayer.SetStone(LocalPlayer.GetStone()+Resources.Stone);Resources.Stone=0;
                LocalPlayer.SetMetal(LocalPlayer.GetMetal()+Resources.Metal);Resources.Metal=0;
                LocalPlayer.SetUranium(LocalPlayer.GetUranium()+Resources.Uranium);Resources.Uranium=0;
                if(Task.state==MINE_ROAD_TO_STOREHOUSE)
                MineTask(Task.ObjID);
            }
        }else if(Task.type==DRINK&&Task.state==DRINK_ROAD_TO_WATER_FILTER){
            if(Length2D<float>((Vec2Vec<int,float>(Task.Pos)+sf::Vector2f(0.5f,0.5f))-Pos)<=1.2f){
                Task.Active=false;
                vecMove.clear();
                cWaterFilter *WaterFilter = (cWaterFilter*)ObjectManger->GetObject(Task.ObjID);
                if(WaterFilter!=nullptr){
                    if(Health<MaxHealth)
                        WaterFilter->Health-=10;
                    Health=MaxHealth;
                }
            }
        }
        
        
        if(Task.type==TRAIN&&Task.state==TRAIN_ROAD_TO_TRAINROOM){
            if(vecMove.size()==0&& Length2D<float>((Vec2Vec<int, float>(Task.Pos) + sf::Vector2f(0.5f, 0.5f) - Pos)) <= 1.2f){
                Task.state=TRAIN_TRAIN_START;
                Task.clock.restart();
                SoundManger->PlaySound(SOUND_SPIN);
            }
        }else if(Task.type==TRAIN&&(Task.state==TRAIN_TRAIN_START||Task.state==TRAIN_TRAIN_STOP)){
            vecMove.clear();
            lookDirection=(int)(Task.clock.getElapsedTime().asMilliseconds()/25)%8;
            if(Task.state==TRAIN_TRAIN_START&&Task.clock.getElapsedTime().asMilliseconds()>400){
                Task.state=TRAIN_TRAIN_STOP;
                EntType=ASTRONAUT_WARRIOR;
                MineAbility=5;
                Speed=2.f;
                Health=150;
                MaxHealth=150;
            }else if(Task.state==TRAIN_TRAIN_STOP&&Task.clock.getElapsedTime().asMilliseconds()>800){
                Task.Active=false;
            }
        }
        
        if(Task.type==BUILD&&Task.state==BUILD_ROAD_TO_CONSTRUCTION){
            if(Length2D<float>((Vec2Vec<int,float>(Task.Pos)+sf::Vector2f(0.5f,0.5f)-Pos))<=1.2f){
                Task.state=BUILD_BUILD;
                Task.SetDelay(750);
                vecMove.clear();
            }
        }else if(Task.type==BUILD&&Task.state==BUILD_BUILD){
            cBaseBuilding *Object = (cBaseBuilding*)ObjectManger->GetObject(Task.ObjID);
            if(Object==nullptr){
                Task.Active=false;
                return;
            }
            
            if(Object->Health<=0){
                Task.Active=false;
                vecMove.clear();
                
            }
        }
        
        
        
        
        if(Task.type==BUILD&&Task.state==BUILD_BUILD&&Task.ActiveAction()){
            cBaseBuilding *Object = (cBaseBuilding*)ObjectManger->GetObject(Task.ObjID);
            if(Object!=nullptr){
                Object->Health-=10;
                SoundManger->PlaySound(SOUND_HAMMER_HIT);
                ParticleSystem->AddEffect(Vec2Vec<int,float>(Task.Pos)+sf::Vector2f(0.7f,-0.5f), MINE_HIT,0);
                
            }else{
                Task.Active=false;
                
            }
            
        }
        
        if(Task.type==MINE&&Resources.GetSum()>=MineAbility&& Task.state!=MINE_ROAD_TO_STOREHOUSE){
            Task.state=MINE_ROAD_TO_STOREHOUSE;
            int StoreHouseID = ObjectManger->GetNearestEnt(STORE_HOUSE, GetPos());
            if(StoreHouseID!=-1){
                cBaseBuilding *StoreHouse = (cBaseBuilding*)ObjectManger->GetObject(StoreHouseID);
                if(StoreHouse!=nullptr&&SetTaskPath(Vec2Vec<float,int>(StoreHouse->GetPos()))){
                    Task.Active=true;
                }else{
                    Task.Active=false;
                }
                
            }else{
                std::cout<<"Cannot find Path\n";
                Task.Active=false;
            }
            
        }else if(Task.type==MINE&&Task.state==MINE_MINING){
            cBaseBuilding *Ore = (cBaseBuilding*)ObjectManger->GetObject(Task.ObjID);
            if(Ore==nullptr||Ore->Health<=0){
                this->Task.Active=true;
            }
            
            if(Task.ActiveAction()){
                cBaseBuilding *Ore = (cBaseBuilding*)ObjectManger->GetObject(Task.ObjID);
                if(Ore!=nullptr){
                    SoundManger->PlaySound(SOUND_MINE);
                    ParticleSystem->AddEffect(Ore->GetPos()+sf::Vector2f(0.0f,-0.0f), MINE_HIT,0);
                    Ore->Health-=10;
                    switch(Ore->EntType){
                        case URANIUM_ORE:
                            Resources.Uranium++;
                            break;
                        case METAL_ORE:
                            Resources.Metal++;
                            break;
                        case STONE_ORE:
                            Resources.Stone++;
                            break;
                            
                    };
                }else{
                    Task.Active=false;
                }
            }
        }
        
        
    }
    
    UpdateMove(deltaTime);
    
    if(vecMove.empty()){
        if(EntType==ASTRONAUT_WARRIOR&&!Task.Active&&
           ThinkTimer.getElapsedTime().asSeconds()>1.75f){
            int newID=-1;
            float flDist=2.8f;
            for(auto object : *ObjectManger->GetObjectList()){
                if(object->EntType!=ALIEN)
                    continue;
                float flCurrentDist=Length2D<float>(object->GetPos()-Pos);
                if(flCurrentDist>flDist)
                    continue;
                flDist=flCurrentDist;
                newID=object->unique_ID;
            }
            
            if(newID!=-1){
                cBaseEntity *Alien = (cBaseEntity*)ObjectManger->GetObject(newID);
                if(Alien!=nullptr){
                    ThinkTimer.restart();
                    Alien->Health-=rand()%20+10;
                    ParticleSystem->AddEffect(Alien->GetPos(), BLOOD,0);
                    //draw laser
                    SoundManger->PlaySound(SOUND_LASER_SHOOT);
                    if(Alien->Health>0)
                        SoundManger->PlaySound(SOUND_MONSTER_HIT);
                    else
                        SoundManger->PlaySound(SOUND_MONSTER_DIE);
                    
                    
                    LaserTimer.restart();
                    LaserEnd=Alien->GetPos();
                    
                    sf::Vector2f vecDir=(Alien->GetPos()-Pos);
                    float flAngle=atan2f(vecDir.y, vecDir.x)*180.f/M_PI;
                    flAngle+=45.f;//isometric
                    if(flAngle>180.f)
                        flAngle-=360.f;
                    if(flAngle>180.f)
                        flAngle+=380.f;
                    
                    if(std::abs(flAngle)<22.5f)
                        lookDirection=DIRECTION::E;
                    else if(std::abs(flAngle)<67.5f)
                        lookDirection=(flAngle>0)?DIRECTION::SE:DIRECTION::NE;
                    else if(std::abs(flAngle)<112.5f)
                        lookDirection=(flAngle>0)?DIRECTION::S:DIRECTION::N;
                    else if(std::abs(flAngle)<157.5f)
                        lookDirection=(flAngle>0)?DIRECTION::SW:DIRECTION::NW;
                    else
                        lookDirection=DIRECTION::W;
                
                }
            }
        }
        
    }
    
}


void cBaseEntity::Update(sf::Time deltaTime){}

void cBaseEntity::UpdateMove(sf::Time deltaTime){
    LastPos=Pos;
    if(Timer.getElapsedTime().asMilliseconds()>35){
        Timer.restart();
        if(state==STATE::MOVE||state==STATE::ATTACK){//animation
            Timer.restart();
            animation_state++;
            if(animation_state>=5)
                animation_state=-5;
        }else if(state==STATE::STAY&&animation_state!=-5){
            animation_state++;
            if(animation_state>=5)
                animation_state=-5;
        }
        if(animation_state==4){
            SoundManger->PlaySound(SOUND_LAND);
        }
    }
    
    if(!vecMove.empty()){
        sf::Vector2f vecWayPoint=vecMove.back()+sf::Vector2f(0.5f,0.5f);
        if(Length2D<float>(vecWayPoint-Pos)>0.5){
            float flDist=Length2D<float>(vecWayPoint-Pos);
            sf::Vector2f vecMoveDir=(vecWayPoint-Pos)/flDist;
            Pos+=Speed*vecMoveDir*deltaTime.asSeconds();
            state=STATE::MOVE;
            
            float flAngle=atan2f(vecMoveDir.y, vecMoveDir.x)*180.f/M_PI;
            flAngle+=45.f;//isometric
            if(flAngle>180.f)
                flAngle-=360.f;
            if(flAngle>180.f)
                flAngle+=380.f;
            
            if(std::abs(flAngle)<22.5f)
                lookDirection=DIRECTION::E;
            else if(std::abs(flAngle)<67.5f)
                lookDirection=(flAngle>0)?DIRECTION::SE:DIRECTION::NE;
            else if(std::abs(flAngle)<112.5f)
                lookDirection=(flAngle>0)?DIRECTION::S:DIRECTION::N;
            else if(std::abs(flAngle)<157.5f)
                lookDirection=(flAngle>0)?DIRECTION::SW:DIRECTION::NW;
            else
                lookDirection=DIRECTION::W;
            
        }else{
            vecMove.pop_back();
        }
    }

    if(vecMove.empty()){
        state=STATE::STAY;
    }
    
    Collision->SetOffset(Pos);
}



void cEntityBasePlayer::ReturnToStoreHouseAlone(int StoreHouseID){
    if(GoToObject(StoreHouseID)){
        Task.Active=true;
        Task.type=MINE;
        Task.ObjID=StoreHouseID;
        Task.state=NORMAL_ROAD_TO_STOREHOUSE;
    }
}

void cEntityBasePlayer::Drink(int FilterID){
    if(GoToObject(FilterID)){
        Task.Active=true;
        Task.type=DRINK;
        Task.ObjID=FilterID;
        Task.state=DRINK_ROAD_TO_WATER_FILTER;
    }
}

void cEntityBasePlayer::Trian(int TrainRoomID){
    if(EntType!=ASTRONAUT_STANDARD)
        return;
    if(GoToObject(TrainRoomID)){
        Task.Active=true;
        Task.type=TRAIN;
        Task.state=TRAIN_ROAD_TO_TRAINROOM;
        return;
    }
    
    Task.Active=false;
}


void cEntityAlien::Update(sf::Time deltaTime){
    
    if(SoundTimer.getElapsedTime().asSeconds()>3){
        if(rand()%3==0){
            SoundManger->PlaySound(SOUND_MONSTER1+rand()%4);
        }
        SoundTimer.restart();
    }
    
    if(TargetID!=-1){
        cBaseBuilding *Player = (cBaseBuilding*)ObjectManger->GetObject(TargetID);
        if(Player!=nullptr){
            float flCurrentDist=Length2D<float>(Player->GetPos()-Pos);
            if(flCurrentDist>0.6f&&vecMove.size()==0){
                if(flCurrentDist<8.f&&Path->isAccessible(Vec2Vec<float,int>(Player->GetPos()))){
                    auto Path = GameWorld->GetPath(Vec2Vec<float,int>(GetPos()), Vec2Vec<float,int>(Player->GetPos()));
                    if(!Path.empty()){
                        this->vecMove.clear();
                        this->Task.Active=true;
                        for(auto WayPoint: Path)
                            this->AddMove(Vec2Vec<int,float>(WayPoint));
                        return;
                    }
                }else{
                    TargetID=-1;
                }
            }else if(flCurrentDist<=1.f){
                if(1500<ThinkTimer.getElapsedTime().asMilliseconds()){
                    ThinkTimer.restart();
                    Player->Health-=(rand()%15+5);
                    SoundManger->PlaySound(SOUND_PUNCH1+rand()%5);
                    if(Player->Health>0)
                        SoundManger->PlaySound(SOUND_PLAYER_HIT1+rand()%5);
                    ParticleSystem->AddEffect(Player->GetPos()+sf::Vector2f(0.0f,0.0f), BLOOD,0);
                }
            }
        }else{
            TargetID=-1;
        }
    }else if(vecMove.size()==0){
        int newID=-1;
        float flDist=12.f;
        sf::Vector2f objPos;
        for(auto object : *ObjectManger->GetObjectList()){
            if(object->EntType!=ASTRONAUT_WARRIOR&&object->EntType!=ASTRONAUT_STANDARD)
                continue;
            float flCurrentDist=Length2D<float>(object->GetPos()-Pos);
            if(flCurrentDist>flDist)
                continue;
            flDist=flCurrentDist;
            newID=object->unique_ID;
            objPos=object->GetPos();
        }
        
        if(newID!=-1){
            TargetID=newID;
        }else{
            if(ThinkDelay<ThinkTimer.getElapsedTime().asMilliseconds())
            if(rand()%3!=0){
                sf::Vector2i randMove(rand()%8-4,rand()%8-4);
                
                if(Path->isAccessible(Vec2Vec<float,int>(objPos)+randMove)){
                    auto Path = GameWorld->GetPath(Vec2Vec<float,int>(GetPos()), Vec2Vec<float,int>(objPos)+randMove);
                    if(!Path.empty()){
                        this->vecMove.clear();
                        this->Task.Active=true;
                        for(auto WayPoint: Path)
                            this->AddMove(Vec2Vec<int,float>(WayPoint));
                        return;
                    }
                }
            }else{
                ThinkDelay=rand()%2500+500;
                ThinkTimer.restart();
            }
        
        }
    }
    
    UpdateMove(deltaTime);
}




