#pragma once
#include <SFML/Graphics.hpp>
#include "Globals.h"
#include "InGameConsole.h"
#include <cmath>

enum{
    STANDARD,
    PANORAMA,
    CORNER_CAM,
};


sf::Vector2f S2W(sf::Vector2i Screen);
sf::Vector2i W2S(sf::Vector2f Pos);
sf::Vector2f flW2S(sf::Vector2f Pos);

class cCamera{
    int Type;
    float flZoom;
    sf::View oldView;
    sf::Vector2f CameraScroll;
    sf::Vector2i LastCursorPos; 
    sf::Vector2f LastMapCursorPos;
    
    sf::Vector2f vecPos;
public:
    cCamera();
    ~cCamera();
    
    void Update(sf::Time deltaTime);
    
    void SetView(sf::RenderWindow *hwnd);
    void ReturnToDefaultView(sf::RenderWindow *hwnd);
    
    sf::Vector2f GetCameraScroll(){ return CameraScroll; }
    sf::Vector2f GetPos(){ return vecPos; }
    sf::Vector2i GetCursorPos(){ return LastCursorPos; }
    sf::Vector2f GetMapCursorPos(){ return LastMapCursorPos; }
    void UpdateMapCursorPos(sf::RenderWindow *hwnd);
    int GetType();
    void SetType(int i);

	void GoToBase() {vecPos = sf::Vector2f(58, 64);}
    
};


extern cCamera *Camera;




