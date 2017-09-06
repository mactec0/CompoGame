#pragma once
#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <sstream>
#include "Globals.h"
#include "FontManger.h"
#include "TextureManger.h"


class cGlobalRender {
    bool bCanPrint;
    sf::RenderWindow *hwnd;
    sf::Color BaseColor[3];
public:
    cGlobalRender(sf::RenderWindow *hwnd) {
        this->hwnd = hwnd;
        bCanPrint = false;
        BaseColor[0]=sf::Color::Black;
        BaseColor[1]=sf::Color(110,110,110,255);
        BaseColor[2]=sf::Color(40, 41, 160,255);
        
    }
    
    sf::Color GetBaseColor(int ID){
        return BaseColor[ID];
    }
    
    void DrawSprite(sf::Vector2f pos, sf::Texture tex){
        sf::Sprite sprite(tex);
        sprite.setPosition(pos);
        hwnd->draw(sprite);
    }
    
    void DrawTab(){
        DrawFilledRect(sf::Vector2f(0,0),sf::Vector2i(Globals.Width,27),BaseColor[0]);
        DrawFilledRect(sf::Vector2f(3,0),sf::Vector2i(Globals.Width-6,24),BaseColor[1]);
        
        
        
        DrawFilledRect(sf::Vector2f(71,0),sf::Vector2i(2,27),BaseColor[0]);
        DrawSprite(sf::Vector2f(80,0),*TextureManger->GetTexture(OBJ_ICON_STONE));
        PrintText<std::string>("Stone", sf::Vector2f(104,0), sf::Color::Black, FontManger->GetFont(0), 18,false);
        
        DrawFilledRect(sf::Vector2f(190+80,0),sf::Vector2i(2,27),BaseColor[0]);
        DrawSprite(sf::Vector2f(200+80,0),*TextureManger->GetTexture(OBJ_ICON_URANIUM));
        PrintText<std::string>("Uranium", sf::Vector2f(228+80,0), sf::Color::Black, FontManger->GetFont(0), 18,false);
        
        DrawFilledRect(sf::Vector2f(400+80,0),sf::Vector2i(2,27),BaseColor[0]);
        DrawSprite(sf::Vector2f(410+80,0),*TextureManger->GetTexture(OBJ_ICON_METAL));
        PrintText<std::string>("Metal", sf::Vector2f(434+80,0), sf::Color::Black, FontManger->GetFont(0), 18,false);
		
		DrawFilledRect(sf::Vector2f(680, 0), sf::Vector2i(2, 27), BaseColor[0]);
		PrintText<std::string>("Time left   :", sf::Vector2f(700, 0), sf::Color::Black, FontManger->GetFont(0), 18, false);
        
    }
    
    
    void DrawSimpleButton(sf::Vector2f vecPos, sf::Vector2i vecSize, std::string str, int size, int state){
        sf::Color b1=BaseColor[2],b2=BaseColor[1],t=BaseColor[0];
        
        if(state==1){//hover
            b1=b2;
        }else if(state==2){//pushed
            std::swap(b1,b2);
        }
        
        DrawFilledRect(vecPos,vecSize,BaseColor[0]);
        DrawFilledRect(vecPos+sf::Vector2f(1,1),vecSize-sf::Vector2i(2,2),b1);
        DrawFilledRect(vecPos+sf::Vector2f(3,3),vecSize-sf::Vector2i(6,6),BaseColor[0]);
        DrawFilledRect(vecPos+sf::Vector2f(4,4),vecSize-sf::Vector2i(8,8),b2);
        PrintText<std::string>(str, sf::Vector2f(vecPos.x+vecSize.x/2,vecPos.y+vecSize.y/2), t, FontManger->GetFont(0), size,true);
    }
    
    void DrawWindow(sf::Vector2f vecPos, sf::Vector2i vecSize){
        DrawFilledRect(vecPos,vecSize,BaseColor[0]);
        DrawFilledRect(vecPos+sf::Vector2f(3,3),vecSize-sf::Vector2i(6,6),BaseColor[2]);
        DrawFilledRect(vecPos+sf::Vector2f(6,6),vecSize-sf::Vector2i(12,12),BaseColor[0]);
        DrawFilledRect(vecPos+sf::Vector2f(8,8),vecSize-sf::Vector2i(16,16),BaseColor[1]);
    }
    template <typename T>
    void DrawSlider(sf::Vector2f vecPos, int Length, int pos, T Val){
        DrawFilledRect(vecPos-sf::Vector2f(1,0),sf::Vector2i(Length+2,6),BaseColor[0]);
        DrawFilledRect(vecPos+sf::Vector2f(1,0),sf::Vector2i(Length-1,4),BaseColor[0]);
        DrawFilledRect(vecPos+sf::Vector2f(1,1),sf::Vector2i(pos,3),BaseColor[2]);
        
        DrawFilledRect(vecPos+sf::Vector2f(pos-2,-3),sf::Vector2i(4,10),BaseColor[0]);
        PrintText<T>(Val, vecPos+sf::Vector2f(Length/2,10), sf::Color::Black, FontManger->GetFont(0), 12);
    }
    
    void DrawCheckBox(sf::Vector2f vecPos, std::string text, bool bChecked){
        sf::Vector2i vecSize{20,20};
        DrawFilledRect(vecPos,vecSize,BaseColor[0]);
        sf::Color BoxColor=bChecked?BaseColor[2]:BaseColor[1];
        DrawFilledRect(vecPos+sf::Vector2f(3,3),vecSize-sf::Vector2i(6,6),BoxColor);
        PrintString(text, vecPos+sf::Vector2f(26,0), sf::Color::Black, FontManger->GetFont(0), 20);
        
    }
    
    void DrawCircle(sf::Vector2f vecPos, float flRadius, sf::Color color){
        sf::CircleShape shape(flRadius);
        shape.setFillColor(color);
        shape.setPosition(vecPos-sf::Vector2f(flRadius,flRadius));
        hwnd->draw(shape);
    }
    
    void DrawOutlineCircle(sf::Vector2f vecPos, float flRadius, sf::Color color){
        sf::CircleShape shape(flRadius);
        shape.setFillColor(sf::Color(0,0,0,0));
        shape.setOutlineColor(color);
        shape.setOutlineThickness(2);
        shape.setPosition(vecPos-sf::Vector2f(flRadius,flRadius));
        hwnd->draw(shape);
    }
    
    void DrawRect(sf::Vector2f vecPos,sf::Vector2i vecSize, sf::Color color1, sf::Color color2, float thickness) {
        sf::RectangleShape MainConsoleRect;
        MainConsoleRect.setPosition(vecPos);
        MainConsoleRect.setSize(sf::Vector2f(vecSize));
        MainConsoleRect.setFillColor(color1);
        MainConsoleRect.setOutlineColor(color2);
        MainConsoleRect.setOutlineThickness(thickness);
        hwnd->draw(MainConsoleRect);
    }
    
    void DrawFilledRect(sf::Vector2f vecPos,sf::Vector2i vecSize, sf::Color color) {
        sf::RectangleShape MainConsoleRect;
        MainConsoleRect.setPosition(vecPos);
        MainConsoleRect.setSize(sf::Vector2f(vecSize));
        MainConsoleRect.setFillColor(color);
        hwnd->draw(MainConsoleRect);
    }
    
    void Print(std::string str, sf::Vector2f vec2d, int size) {
        sf::Text text;
        text.setFont(*FontManger->GetFont(0));
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(vec2d);
        hwnd->draw(text);
    }
    
    void PrintString(std::string str, sf::Vector2f vec2d, sf::Color col, sf::Font *font, int size, bool Center=false){
        sf::Text text;
        text.setFont(*font);
        text.setString(str);
        text.setCharacterSize(size);
        text.setPosition(vec2d);
        text.setFillColor(col);
        hwnd->draw(text);
    }
    template <typename T>
    void PrintText(T var, sf::Vector2f vec2d,  sf::Color col, sf::Font *font, int size, bool bCenter=true) {
        std::stringstream ss;
        ss<<var;
        sf::Text text;
        text.setFont(*font);
        text.setString(ss.str());
        text.setCharacterSize(size);
        text.setFillColor(col);
        if(bCenter){
            vec2d.x-=text.getLocalBounds().width/2;
            vec2d.y-=text.getLocalBounds().height/2;
        }
        text.setPosition(vec2d);
        hwnd->draw(text);
    }
    
    template <typename T>
    void PrintTextCenterY(T var, sf::Vector2f vec2d,  sf::Color col, sf::Font *font, int size) {
        std::stringstream ss;
        ss<<var;
        sf::Text text;
        text.setFont(*font);
        text.setString(ss.str());
        text.setCharacterSize(size);
        text.setFillColor(col);
        vec2d.y-=text.getLocalBounds().height/2;
        text.setPosition(vec2d);
        hwnd->draw(text);
    }
    
    
    void PrintInt(int var, sf::Vector2f vec2d,  sf::Color col, sf::Font *font, int size, bool bCenter=true) {
        std::stringstream ss;
        ss<<var;
        sf::Text text;
        text.setFont(*font);
        text.setString(ss.str());
        text.setCharacterSize(size);
        text.setPosition(vec2d);
        text.setFillColor(col);
        hwnd->draw(text);
    }
    
    sf::RenderWindow *GetWindow() {
        return hwnd;
    }
};

extern cGlobalRender *GlobalRender;
