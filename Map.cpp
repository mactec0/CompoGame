#include "Map.h"
#include "ObjectManager.h"

cMap::cMap(){
    Width=0;
    Height=0;
    TileWidth=0;
    TileHeight=0;
    strTilesetPath="";
    bMapAllocated=false;
    
    
    Globals.TileWidth=150;
    Globals.TileHeight=106;
    Width=128;
    Height=128;
    
    if(!bMapAllocated)
        this->alloc(Width, Height);
    
    
    Path = new cPathFinder(Width,Height);
    
    
    for(int i=0;i<3;i++){
        sf::Sprite newSprite;
        newSprite.setTexture(*TextureManger->GetTexture(OBJ_GROUND_TILE+i));
        vSprites.push_back(newSprite);
    }
}

cMap::~cMap(){
    
}

void cMap::Generate(){
    ResetMap();
    for(int y=0;y<Height;y++){
        for(int x=0;x<Width;x++){
                Path->SetUnAvailable(x, y, false);
        }
    }
    
    sf::Vector2f MapCenter(Width/2,Height/2);
    ObjectManger->vObjects.push_back(new cDestroyedShip(MapCenter));
    ObjectManger->vObjects.push_back(new cEntityBasePlayer(MapCenter+sf::Vector2f(0,3)));
    ObjectManger->vObjects.push_back(new cEntityBasePlayer(MapCenter+sf::Vector2f(1,3)));
    ObjectManger->vObjects.push_back(new cEntityBasePlayer(MapCenter+sf::Vector2f(2,3)));
    
    
    for(int i=0;i<18;i++)
        PlaceValley(sf::Vector2i(rand()%128,rand()%128), rand()%20+6, rand()%2);
    
    const sf::Vector2i neighbors[]={ {0,0},{ 0, 1 }, { 1, 0 }, { 0, -1 }, { -1, 0 },
        { -1, -1 }, { 1, 1 }, { -1, 1 }, { 1, -1 }};
    
    bool OreSize=false;
    int OreType=0;
    sf::Vector2i NewPos;
    
    for(int y=1;y<Height-1;y++){
        for(int x=1;x<Width-1;x++){
            
            if(Length2D<float>(sf::Vector2f(x,y)-MapCenter)<6){
                continue;
            }
            
            if(rand()%18!=0)
                continue;
            
            if(DATA_LAYER[y][x])
                continue;
            
            if(Path->isAccessible(sf::Vector2i(x,y)))
            switch(rand()%18){
                case 1:
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    OreSize=rand()%2;
                    OreType=rand()%3;
                    for(int i=0;i<9;i++){
                        NewPos=sf::Vector2i(y,x)+neighbors[i];
                        if(Path->isAccessible(NewPos)&&DATA_LAYER[NewPos.y][NewPos.x]==0&&rand()%3==0){
                            if(OreType==0){
                                if(rand()%2)
                                    ObjectManger->vObjects.push_back(new cTallMetalOre(sf::Vector2f(NewPos.x,NewPos.y)));
                                else
                                    ObjectManger->vObjects.push_back(new cSmallMetalOre(sf::Vector2f(NewPos.x,NewPos.y)));
                            }else if(OreType==1){
                                if(rand()%2)
                                    ObjectManger->vObjects.push_back(new cTallStoneOre(sf::Vector2f(NewPos.x,NewPos.y)));
                                else
                                    ObjectManger->vObjects.push_back(new cSmallStoneOre(sf::Vector2f(NewPos.x,NewPos.y)));
                            }else if(OreType==2){
                                if(rand()%2)
                                    ObjectManger->vObjects.push_back(new cTallUraniumOre(sf::Vector2f(NewPos.x,NewPos.y)));
                                else
                                    ObjectManger->vObjects.push_back(new cSmallUraniumOre(sf::Vector2f(NewPos.x,NewPos.y)));
                            }
                        }
                    }
                    
                    break;
                case 7:
                    ObjectManger->vObjects.push_back(new cCraterLarge(sf::Vector2f(x,y)));
                    break;
                case 8:
                    ObjectManger->vObjects.push_back(new cMeteorHalf(sf::Vector2f(x,y)));
                    break;
                case 9:
                    if(Length2D<float>(sf::Vector2f(x,y)-MapCenter)>18)
                    ObjectManger->vObjects.push_back(new cAlienBonez(sf::Vector2f(x,y)));
                    break;
                break;
            
            }
            
        }
    }
    
    for(auto object : *ObjectManger->GetObjectList()){
        if(object->type==BUILDING&&object->EntType==ALIEN_BONES){
            for(int i=1;i<9;i++){
                sf::Vector2i NewPos=sf::Vector2i(object->GetPos().x,object->GetPos().y)+neighbors[i];
                if(Path->isAccessible(NewPos)&&DATA_LAYER[NewPos.y][NewPos.x]==0&&rand()%7==0){
                    ObjectManger->vObjects.push_back(new cEntityAlien(sf::Vector2f(NewPos.x,NewPos.y)));
                }
            }
        }
    }
}

void cMap::PlaceValley(sf::Vector2i Pos, int length, bool Direction){
    for(int i=0;i<length;i++){
        sf::Vector2i NewPos=Pos;
        if(Direction)
            NewPos+=sf::Vector2i(0,i);
        else
            NewPos+=sf::Vector2i(i,0);
        
        if(NewPos.x<128&&NewPos.y<128){
            if(DATA_LAYER[NewPos.y][NewPos.x]==0){
                DATA_LAYER[NewPos.y][NewPos.x]=Direction?1:2;
            }else{
                return;
            }
        }
        
    }

}

bool cMap::Load(const char *fname){
    std::ifstream f(fname);
    int iReadDataHeader=-1;
    int LayerType=-1;
    if(!f.good()){
        printf("Cannot find file\n");
        return false;
    }
    
    std::string LineData;
    while (std::getline(f, LineData)){
        if(LineData[0]=='['){//CHANGE HEADER
            char szHeader[32];
            sscanf((char*)LineData.c_str(),"[%s]",szHeader);
            szHeader[strlen(szHeader)-1]=0x00;
            if(strcmp(szHeader, "header")==0){
                iReadDataHeader=MAP_TYPE_DATA::HEADER;
            }else if(strcmp(szHeader, "tilesets")==0){
                iReadDataHeader=MAP_TYPE_DATA::TILESET;
            }else if(strcmp(szHeader, "layer")==0){
                iReadDataHeader=MAP_TYPE_DATA::LAYER;
                if(!bMapAllocated)
                    this->alloc(Width, Height); 
            }
        }else if(LineData[0]!='\n'){//ENTRY
            std::size_t iEqualPlace=LineData.find("=");
            if(iEqualPlace!=std::string::npos){
                std::string strEntryName=LineData.substr(0,iEqualPlace);
                
                if(strEntryName=="width"){
                    Width=GetFromSTR<int>(LineData.substr(iEqualPlace+1));
                }else if(strEntryName=="height"){
                    Height=GetFromSTR<int>(LineData.substr(iEqualPlace+1));
                }else if(strEntryName=="tilewidth"){
                    TileWidth=GetFromSTR<int>(LineData.substr(iEqualPlace+1));
                    Globals.TileWidth=TileWidth;
                }else if(strEntryName=="tileheight"){
                    TileHeight=GetFromSTR<int>(LineData.substr(iEqualPlace+1));
                    Globals.TileHeight=TileHeight;
                }else if(strEntryName=="orientation"){
                    strOrientation=GetFromSTR<std::string>(LineData.substr(iEqualPlace+1));
                }else if(strEntryName=="tileset"){
                    strTilesetPath=GetFromSTR<std::string>(LineData.substr(iEqualPlace+1));
                    strTilesetPath=strTilesetPath.substr(0,strTilesetPath.find(","));
                }else if(strEntryName=="type"){
                    LayerType=GetFromSTR<int>(LineData.substr(iEqualPlace+1));
                }else if(strEntryName=="data"){
                    std::string MapData="";
                    std::string DataLine;
                    bool bEndOFMapData=false;
                    while(!bEndOFMapData){
                        if(std::getline(f, DataLine)){
                            if(DataLine.length()==0){
                                bEndOFMapData=true;
                            }else{
                                MapData+=DataLine;
                            }
                        }else{
                            bEndOFMapData=true;
                        }
                    }
                    std::replace(MapData.begin(), MapData.end(), ',', ' ');
                    std::stringstream DataStream(MapData);
                    
                    for(int y=0;y<Height;y++){
                        for(int x=0;x<Width;x++){
                            int TileID=0;
                            if(DataStream>>TileID)
                                switch (LayerType) {
                                    case LAYER_1:
                                        DATA_LAYER[y][x]=TileID;
                                        break;
                                    case LAYER_2:
                                        COLLISION_LAYER[y][x]=TileID;
                                        break;
                                    default:
                                        break;
                                }
                        }
                    }
                }
                
            
            }
            
        }
    }
    
    //LoadTileSet(strTilesetPath.c_str());
    
    Path = new cPathFinder(Width,Height);
    for(int y=0;y<Height;y++){
        for(int x=0;x<Width;x++){
            if(COLLISION_LAYER[y][x]==0)
                Path->SetUnAvailable(x, y, false);
            else
                Path->SetUnAvailable(x, y, true);
        }
    }
    Path->FindPath(sf::Vector2i(0,0),sf::Vector2i(0,99));
}

bool cMap::LoadTileSet(const char *fname){
    if(titleset_tex.loadFromFile(strTilesetPath)){
        int iX=titleset_tex.getSize().x/TileWidth;
        int iY=titleset_tex.getSize().y/TileHeight; 
        for(int y=0;y<iY;y++){
            for(int x=0;x<iX;x++){
                sf::Sprite newSprite;
                newSprite.setTexture(titleset_tex);
                newSprite.setTextureRect(sf::Rect<int>(x*TileWidth,y*TileHeight,TileWidth,TileHeight));
                vSprites.push_back(newSprite);
            }
        }
    }
	return true;
}

void cMap::Update(sf::Time deltaTime){

}

 
void cMap::Draw(sf::RenderWindow *hwnd){
    
    sf::Vector2f Cmap_pos = Camera->GetMapCursorPos();
    if (Cmap_pos.x < 0)
        Cmap_pos.x = 0;
    if (Cmap_pos.y < 0)
        Cmap_pos.y = 0;
    
    sf::Vector2f vecUpLeftCorner = S2W(sf::Vector2i(0, 0));
    sf::Vector2f vecDownRightCorner = S2W(sf::Vector2i(Globals.Width, Globals.Height));
    sf::Vector2f vecUpRightCorner = S2W(sf::Vector2i(Globals.Width,0));
    sf::Vector2f vecDownLeftCorner = S2W(sf::Vector2i(0, Globals.Height));
    
    DrawMax= sf::Vector2i(floor(vecDownRightCorner.x)+1, floor(vecDownRightCorner.y)+1);
    if(DrawMax.x>Width)
        DrawMax.x=Width;
    if(DrawMax.y>Height)
        DrawMax.y=Height;
    
    DrawMin= sf::Vector2i(floor(vecUpLeftCorner.x), floor(vecUpRightCorner.y));
    if(DrawMin.x<0)
        DrawMin.x=0;
    if(DrawMin.y<0)
        DrawMin.y=0;
    
    for(int y=DrawMin.y;y<Height;y++){
        if (y > vecDownLeftCorner.y+1)
            break;
        int FirstXTileID = -1;
        for(int x=DrawMin.x;x<Width;x++){
            if (x > vecDownRightCorner.x + 1)
                break;
            
            float cartx = x;
            float carty = y;
            
            cartx-=Camera->GetPos().x;
            carty-=Camera->GetPos().y;
            
            float fx = (cartx - carty) * (Globals.TileWidth / 2);
            float fy = (cartx + carty) * (Globals.TileHeight / 2);
            fx += Camera->GetCameraScroll().x;
            fy += Camera->GetCameraScroll().y;
            
            fx-=(Globals.TileWidth / 2);
            
            if (Globals.Width < fx)
                break;
            
            if (Globals.Height < fy)
                break;
            
            
            if (Globals.Width<fx ||
                Globals.Height<fy ||
                0>fx + Globals.TileWidth ||
                0>fy + Globals.TileHeight)
                continue;
            
            if (FirstXTileID == -1) {
                FirstXTileID = x;
                DrawMin.x = x-1;
                if (DrawMin.x < 0)
                    DrawMin.x = 0;
            }
            
            
            sf::Vector2<float> vecDrawPos(fx,fy);
            if(VisibleArea.isVisible(sf::Vector2f(x,y))){
                if(DATA_LAYER[y][x])
                    this->DrawTile(vecDrawPos, 0, hwnd);
                this->DrawTile(vecDrawPos, DATA_LAYER[y][x], hwnd);
            }else{
                this->DrawTile(vecDrawPos, DATA_LAYER[y][x], hwnd, sf::Color(255,255,255,100));
            }
            
            
        }
    }
}

void cMap::DrawTile(sf::Vector2<float> vec, int ID, sf::RenderWindow *hwnd, sf::Color col){
    if(ID>=0&&ID<vSprites.size()){
        vSprites[ID].setPosition(vec);
        vSprites[ID].setColor(col);
        hwnd->draw(vSprites[ID]);
        vSprites[ID].setColor(sf::Color(255,255,255,255));
    }
}




void cMap::ResetMap(){
    for(int y=0;y<Height;y++){
        for(int x=0;x<Width;x++){
            DATA_LAYER[y][x]=0;
            COLLISION_LAYER[y][x]=0;
        }
    }
}

void cMap::alloc(int x, int y){
    DATA_LAYER = new uint16_t*[y];
    for(int i = 0; i < y; ++i)
        DATA_LAYER[i] = new uint16_t[x];
    
    COLLISION_LAYER = new bool*[y];
    for(int i = 0; i < y; ++i)
        COLLISION_LAYER[i] = new bool[x];
    
    bMapAllocated=true;
    ResetMap();
}
