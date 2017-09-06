#pragma once
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "TextureManger.h" 
#include "GlobalRender.h"
#include "KeyManger.h"
#include "InGameConsole.h"
#include "CVAR.h"
#include <stdio.h>
#include "Camera.h"
#include "Map.h"
#include "GUI.h"
#include "Selector.h"
#include "ObjectManager.h"
#include "SoundManger.h"
#include "SplashScreen.h"
#include "ParticleSystem.h"
#include "MusicPlayer.h"
#include "LocalPlayer.h"
#include "VisibleArea.h"
#define TIMELIMIT 25

enum GAMESTATE{
    MAINMENU,
    INLOADINGGAME,
    INGAME,
    INGAMEOVER,
    INSCORE,
};

class cGame { 
    int GameState;
    int FPSCounter;
    int FPSDisplay;
    sf::Clock FPSClock;
    sf::RenderWindow *hwnd;
    cSpashScreen *SpashScreen;
    sf::Clock Timer;
    int Score;
public:
    cGame(sf::RenderWindow *hwnd);
    ~cGame();
    
    void Render(sf::RenderWindow *hwnd);
    void Update(sf::Time dtime);
    
    int GetState(){return GameState;}
};

