#pragma once
#include "GlobalRender.h"
#include "KeyManger.h"
#include <vector>
#include "CVAR.h"

class cInGameConsole {
    const int ConsoleHeight = 300;
    bool bOpened;
    float WinOffset;
    sf::Clock deltaClock;
    std::string tInput;
    std::vector <std::string> strConsoleLog;
    sf::Clock pClock;
    
public:
    cInGameConsole() {
        bOpened = false;
        WinOffset = -ConsoleHeight;
        pClock.restart();
    }
    
    
    void Control() {
        if (KeyManger->Clicked(KEY_Tilde)||KeyManger->Clicked(KEY_F9)) {
            bOpened = !bOpened;
            deltaClock.restart();
        }
        if (bOpened) {
            if (isLetterClicked()) {
                tInput += KeyManger->GetKey(GetLetterClicked());
            }
            
            if (KeyManger->Clicked(KEY_Return)) {
                strConsoleLog.push_back(tInput);
                SendCommand(tInput);
                tInput = "";
            }
            if (KeyManger->Clicked(KEY_BackSpace)) {
                if(tInput.length()>0)
                    tInput = tInput.substr(0, tInput.length() - 1);
            }
        }
    }
    
    bool IsConsoleOpened() { return bOpened; }
    
    void SendCommand(std::string str) {
        bool bisCommand=false;
        
        for (int i = 0; i < str.length(); i++)
        {
            if (str[i] != ' ') {
                if (str[i] == '/')
                    bisCommand = true;
                break;
            }
        }
        
        if (bisCommand) {
            std::stringstream ss;
            ss<<str;
            std::string command, value;
            ss >> command;
            ss >> value;
            command.erase(0, 1);
            if(!CVARS->SetValue(command, value))
                strConsoleLog.push_back("Undefined command.");
        }
    }
    
    int GetLetterClicked() {
        for (int i = KEY_A; i <= KEY_Num9; i++)
            if (KeyManger->Clicked(i))
                return i;
        
        for (int i = KEY_LBracket; i <= KEY_Space; i++)
            if (KeyManger->Clicked(i)) {
                if (i == KEY_Tilde)
                    continue;
                return i;
            }
        return -1;
    }
    
    bool isLetterClicked() {
        bool ret = false;
        for (int i = KEY_A; i <= KEY_Num9; i++)
            if (KeyManger->Clicked(i))
                ret = true;
        
        for (int i = KEY_LBracket; i <= KEY_Space; i++)
            if (KeyManger->Clicked(i)) {
                if (i == KEY_Tilde)
                    continue;
                ret = true;
            }
        
        return ret;
    }
    
    void draw(sf::RenderWindow *hwnd) {
        if (bOpened) {
            if (WinOffset < 0)
            {
                sf::Time dt = deltaClock.restart();
                WinOffset += dt.asSeconds()*1000;
            }
            if (WinOffset > 0)
                WinOffset = 0;
        }
        else {
            if (WinOffset > -ConsoleHeight)
            {
                sf::Time dt = deltaClock.restart();
                WinOffset -= dt.asSeconds() * 1000;
            }
            if (WinOffset < -ConsoleHeight)
                WinOffset = -ConsoleHeight;
        }
        if (WinOffset != -ConsoleHeight) {
            if (pClock.getElapsedTime().asMilliseconds() > 1000)
                pClock.restart();
            
            /*sf::Color col1 = sf::Color(0, 0, 0, 255);
            sf::Color col2 = sf::Color(51, 51, 51, 255);
            sf::Color col3 = sf::Color(40, 40, 40, 255);
            sf::Color col4 = sf::Color(60, 60, 60, 255);
            sf::Color col5 = sf::Color(24, 24, 24, 255);*/
            
            sf::Color col1 = sf::Color(0, 0, 0, 255);
            sf::Color col2 = GlobalRender->GetBaseColor(2);
            sf::Color col3 = GlobalRender->GetBaseColor(1);
            sf::Color col4 = GlobalRender->GetBaseColor(2);
            sf::Color col5 = GlobalRender->GetBaseColor(1);
            
            GlobalRender->DrawFilledRect(sf::Vector2f(0, WinOffset), sf::Vector2i(Globals.Width, ConsoleHeight), col1);
            GlobalRender->DrawFilledRect(sf::Vector2f(2, WinOffset), sf::Vector2i(Globals.Width-4, ConsoleHeight-2), col2);
            GlobalRender->DrawFilledRect(sf::Vector2f(2+2, WinOffset), sf::Vector2i(Globals.Width - 4-4, ConsoleHeight - 2-2), col3);
            GlobalRender->DrawFilledRect(sf::Vector2f(2 + 2+2, WinOffset), sf::Vector2i(Globals.Width - 4 - 4-4, ConsoleHeight - 2 - 2-2), col4);
            GlobalRender->DrawFilledRect(sf::Vector2f(2 + 2 + 2+1, WinOffset), sf::Vector2i(Globals.Width - 4 - 4 - 4-2, ConsoleHeight - 2 - 2 - 2-1), col5);
            
            std::string strInput = "]";
            strInput += tInput;
            
            
            
            if (pClock.getElapsedTime().asMilliseconds() < 500)
                strInput += (char)'_';
            
            GlobalRender->Print(strInput, sf::Vector2f(10,WinOffset+ConsoleHeight-34),22);
            
            int iLogList=1;
            for (int i = strConsoleLog.size() - 1; i >= 0; i--) { 
                GlobalRender->Print(strConsoleLog[i], sf::Vector2f(10, WinOffset + ConsoleHeight - 32-18*(iLogList)), 22);
                iLogList++;
            }
            
        }  
    }
    
};

extern cInGameConsole *GameConsole;
