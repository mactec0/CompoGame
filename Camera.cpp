#include "Camera.h"
#include <iostream>

cCamera::cCamera(){
    flZoom=1;
    CameraScroll=sf::Vector2f(0,0);
    LastCursorPos.x=Globals.Width/2;
    LastCursorPos.y=Globals.Height/2;
    Type=0;
    vecPos=sf::Vector2f(58,64);
}

cCamera::~cCamera(){
    
}


int cCamera::GetType(){
    return Type;
}

void cCamera::SetType(int i){
    Type=i;
}

void cCamera::Update(sf::Time deltaTime){
    const float flCamMarginMove=0.1f;
    float flWidthMargin=flCamMarginMove*Globals.Width;
    float flHeightMargin=flCamMarginMove*Globals.Height;
    flZoom+=deltaTime.asSeconds()*Globals.dScroll;
    
    if(flZoom>1)
        flZoom=1;
    
    if(flZoom<0.5f)
        flZoom=0.5f;
    
    if(!GameConsole->IsConsoleOpened()){
        float flMoveCameraSpeed=6;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
            flMoveCameraSpeed*=3;
        
        bool bMoveUP=false,
             bMoveDOWN=false,
             bMoveLEFT=false,
             bMoveRIGHT=false;
        
        if(Type==CORNER_CAM){
            
            if(LastCursorPos.y<flHeightMargin)
                bMoveUP=true;
            if(LastCursorPos.y>Globals.Height-flHeightMargin)
                bMoveDOWN=true;
            if(LastCursorPos.x<flWidthMargin)
                bMoveLEFT=true;
            if(LastCursorPos.x>Globals.Width-flWidthMargin)
                bMoveRIGHT=true;
            
        }
        
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::LSystem)){
            float flW=Globals.Width/2;
            float flH=Globals.Height/2;
            float WDiff=Globals.Width-this->GetCursorPos().x;
            float HDiff=Globals.Height-this->GetCursorPos().y;
            
            if(WDiff>0){
                vecPos.y+=deltaTime.asSeconds()*flMoveCameraSpeed*(Globals.TileWidth/Globals.TileHeight);
                vecPos.x-=deltaTime.asSeconds()*flMoveCameraSpeed;
            }else if(WDiff<0){
                vecPos.y+=deltaTime.asSeconds()*flMoveCameraSpeed*(Globals.TileWidth/Globals.TileHeight);
                vecPos.x-=deltaTime.asSeconds()*flMoveCameraSpeed;
            }
        }
        
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)||bMoveLEFT){
            vecPos.y+=deltaTime.asSeconds()*flMoveCameraSpeed*(Globals.TileWidth/Globals.TileHeight);
            vecPos.x-=deltaTime.asSeconds()*flMoveCameraSpeed;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)||bMoveRIGHT) {
            vecPos.y-=deltaTime.asSeconds()*flMoveCameraSpeed*(Globals.TileWidth/Globals.TileHeight);
            vecPos.x+=deltaTime.asSeconds()*flMoveCameraSpeed;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)||bMoveUP){
            vecPos.y-=deltaTime.asSeconds()*flMoveCameraSpeed;
            vecPos.x-=deltaTime.asSeconds()*flMoveCameraSpeed*(Globals.TileWidth/Globals.TileHeight);
        }else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)||bMoveDOWN) {
            vecPos.y+=deltaTime.asSeconds()*flMoveCameraSpeed;
            vecPos.x+=deltaTime.asSeconds()*flMoveCameraSpeed*(Globals.TileWidth/Globals.TileHeight);
        }
    }
    
    
    switch (Type) {
        case STANDARD:
            CameraScroll=sf::Vector2f(0.f,0.f);
            break;
        case PANORAMA:
            CameraScroll.x=-LastCursorPos.x+Globals.Width/2;
            CameraScroll.y=-LastCursorPos.y+Globals.Height/2;
            if(CameraScroll.x>Globals.Width/2)
                CameraScroll.x=Globals.Width/2;
            if(CameraScroll.y>Globals.Height/2)
                CameraScroll.y=Globals.Height/2;
            if(CameraScroll.y<-Globals.Height/2)
                CameraScroll.y=-Globals.Height/2;
            if(CameraScroll.x<-Globals.Width/2)
                CameraScroll.x=-Globals.Width/2;
            CameraScroll.x/=2;
            break;
        case CORNER_CAM:
            break;
        default:
            break;
    }
    
    
    
}


void cCamera::UpdateMapCursorPos(sf::RenderWindow *hwnd){
    sf::Vector2i position = sf::Mouse::getPosition(*hwnd);
    sf::Vector2f mouse_Map = hwnd->mapPixelToCoords(position);
    LastMapCursorPos = S2W(sf::Vector2i((int)mouse_Map.x,(int)mouse_Map.y));
}

void cCamera::SetView(sf::RenderWindow *hwnd){
    LastCursorPos = sf::Mouse::getPosition(*hwnd);
    
    oldView = hwnd->getView();
    sf::View view = oldView;
    view.zoom(flZoom);
    hwnd->setView(view);
}

void cCamera::ReturnToDefaultView(sf::RenderWindow *hwnd){
    hwnd->setView(oldView);
}


sf::Vector2f S2W(sf::Vector2i Screen){  
    float ScreenX = Screen.x+(-Camera->GetCameraScroll().x), ScreenY = Screen.y + (-Camera->GetCameraScroll().y);
    float map_x = (ScreenX / (Globals.TileWidth / 2) + ScreenY / (Globals.TileHeight / 2)) / 2;
    float map_y = (ScreenY / (Globals.TileHeight / 2) - (ScreenX / (Globals.TileWidth / 2))) / 2;
    map_x+=Camera->GetPos().x;
    map_y+=Camera->GetPos().y;
    return sf::Vector2f(map_x, map_y);
}

sf::Vector2i W2S(sf::Vector2f Pos){
    Pos-=Camera->GetPos();
    sf::Vector2f Screen((Pos.x-Pos.y)*(Globals.TileWidth / 2),(Pos.x+Pos.y)*(Globals.TileHeight / 2));
    Screen+=Camera->GetCameraScroll();
    return sf::Vector2i(floor(Screen.x),floor(Screen.y));
}

sf::Vector2f flW2S(sf::Vector2f Pos){
    Pos-=Camera->GetPos();
    sf::Vector2f Screen((Pos.x-Pos.y)*(Globals.TileWidth / 2),(Pos.x+Pos.y)*(Globals.TileHeight / 2));
    Screen+=Camera->GetCameraScroll();
    return sf::Vector2f(floor(Screen.x),floor(Screen.y));
}




