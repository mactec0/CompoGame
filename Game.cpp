#include <stdio.h>
#include "Game.h"
#include "ResourcePath.hpp"


cGame::cGame(sf::RenderWindow *hwnd) {
    this->hwnd=hwnd;
    
    GameWorld = new cMap();
    
    
    GlobalRender = new cGlobalRender(hwnd);
    
    FPSCounter=0;
    FPSDisplay=0;
    FPSClock.restart();
    GameState=MAINMENU;
    SpashScreen = new cSpashScreen();
    
    ParticleSystem->AddEffect(sf::Vector2f(100,100), FIRE,0);
    ParticleSystem->AddEffect(sf::Vector2f(100,400), FIRE,1);
    ParticleSystem->AddEffect(sf::Vector2f(0,0), STARS,2);
    
    MusicPlayer->Play(MUSIC_MENU);
    Score=0;
}



void cGame::Render(sf::RenderWindow *hwnd) {
    GameConsole->Control();
    
    sf::View oldView;
    sf::View View;
    std::stringstream ss;
    
    switch (GameState) {
        case MAINMENU:
            hwnd->clear(sf::Color::Black);
            ParticleSystem->Draw(hwnd);
            SpashScreen->DrawMenuPlane(hwnd);
            GUI->Draw(hwnd);
            break;
        case INGAME:
            hwnd->clear(sf::Color::Black);
            GlobalRender->DrawRect(sf::Vector2f(0,0), sf::Vector2i(Globals.Width,Globals.Height), sf::Color(89,64,47,255), sf::Color::Red, 0);
            Camera->SetView(hwnd);//GameWorld view
            Camera->UpdateMapCursorPos(hwnd);
            ObjectManger->SetVisibleArea();
            GameWorld->Draw(hwnd);
            ObjectManger->Draw(hwnd);
            ParticleSystem->Draw(hwnd);
            Selector->Draw(hwnd);
            Camera->ReturnToDefaultView(hwnd);
            GlobalRender->DrawTab();

			{//Timer
				const int MaxTimeMin = TIMELIMIT;
				const int MaxTimeSec = 60 * MaxTimeMin;
				int Mins = (MaxTimeSec - Globals.GameTimer.getElapsedTime().asSeconds())/60;
				int Seconds = 60*(MaxTimeMin -Mins)-Globals.GameTimer.getElapsedTime().asSeconds();
				sText<std::string> *text_Mins = (sText<std::string>*)GUI->GetElement(GUI->GetWindow(GAMETAB_PANEL), GAME_TAB_MINUTES);
				if (text_Mins)
					text_Mins->SetVar(ToStr<int>(Mins));
				std::string sec = ToStr<int>(Seconds);
				if (sec.length() < 2)
					sec = "0" + sec;
				sText<std::string> *text_Sec = (sText<std::string>*)GUI->GetElement(GUI->GetWindow(GAMETAB_PANEL), GAME_TAB_SECONDS);
				if (text_Sec)
					text_Sec->SetVar(sec);
			}

            GUI->Draw(hwnd);

            break;
        case INGAMEOVER:
            GameWorld->Draw(hwnd);
            GlobalRender->PrintText<std::string>("GAME OVER", sf::Vector2f(Globals.Width/2,Globals.Height/2), sf::Color::Red, FontManger->GetFont(0), 76,true);
            if(Timer.getElapsedTime().asSeconds()>5){
                GUI->HideAll();
                GameState=MAINMENU;
                ObjectManger->Clear();
                GUI->SetVisible(MAINMENU_PANEL, true);
                ParticleSystem->AddEffect(sf::Vector2f(100,100), FIRE,0);
                ParticleSystem->AddEffect(sf::Vector2f(100,400), FIRE,1);
                ParticleSystem->AddEffect(sf::Vector2f(0,0), STARS,2);
                MusicPlayer->StopAll();
                MusicPlayer->Play(MUSIC_MENU);
            }
            break;
        case INSCORE:
            GameWorld->Draw(hwnd);
            GlobalRender->PrintText<std::string>("Well Done!", sf::Vector2f(Globals.Width/2,Globals.Height/2-50), sf::Color::Cyan, FontManger->GetFont(0), 76,true);
            ss<<"Score: ";ss<<Score;
            GlobalRender->PrintText<std::string>(ss.str(), sf::Vector2f(Globals.Width/2,Globals.Height/2+50), sf::Color::Cyan, FontManger->GetFont(0), 76,true);
            if(Timer.getElapsedTime().asSeconds()>8){
                GUI->HideAll();
                GameState=MAINMENU;
                ObjectManger->Clear();
                GUI->SetVisible(MAINMENU_PANEL, true);
                ParticleSystem->AddEffect(sf::Vector2f(100,100), FIRE,0);
                ParticleSystem->AddEffect(sf::Vector2f(100,400), FIRE,1);
                ParticleSystem->AddEffect(sf::Vector2f(0,0), STARS,2);
                MusicPlayer->StopAll();
                MusicPlayer->Play(MUSIC_MENU);
            }
            break;
            
        case INLOADINGGAME:
            oldView = hwnd->getView();
            View=oldView;
            hwnd->clear(sf::Color::Black);
            if(!SpashScreen->ShouldDrawMap()){
                View.zoom(SpashScreen->GetZoom());
                hwnd->setView(View);
                ParticleSystem->Draw(hwnd);
                SpashScreen->DrawMenuPlane(hwnd);
            }else{
                Camera->SetView(hwnd);
                Camera->UpdateMapCursorPos(hwnd);
                ObjectManger->SetVisibleArea();
                GameWorld->Draw(hwnd);
                ObjectManger->Draw(hwnd);
                Camera->ReturnToDefaultView(hwnd);
            }
            
            GUI->Draw(hwnd);
            hwnd->setView(oldView);
            if(SpashScreen->DrawTransition(hwnd)){
                ParticleSystem->ClearAll();
                MusicPlayer->Play(MUSIC_GAME);
                GUI->SetVisible(GAMETAB_PANEL, true);
                GUI->SetVisible(BUILD_PANEL, true);
                GUI->SetVisible(INTRO_WINDOW, true);
                GameState=INGAME;
            }
            break;
            
    }
    
    if(CVARS->iGetValue(var_GiveStone)) {
        LocalPlayer.SetStone(LocalPlayer.GetStone()+CVARS->iGetValue(var_GiveStone));
        CVARS->iSetValue(var_GiveStone, 0);
    }else if(CVARS->iGetValue(var_GiveMetal)) {
        LocalPlayer.SetMetal(LocalPlayer.GetMetal()+CVARS->iGetValue(var_GiveMetal));
        CVARS->iSetValue(var_GiveMetal, 0);
    }else if(CVARS->iGetValue(var_GiveUranium)) {
        LocalPlayer.SetUranium(LocalPlayer.GetUranium()+CVARS->iGetValue(var_GiveUranium));
        CVARS->iSetValue(var_GiveUranium, 0);
    }
    
    
    //fps
    FPSCounter++;
    if (FPSClock.getElapsedTime().asMilliseconds() > 1000) {
        FPSDisplay = FPSCounter;
        FPSCounter = 0;
        FPSClock.restart();
    } 
    if (CVARS->iGetValue(var_ShowFPS)) {
        std::stringstream ss;
        ss << "FPS: ";
        ss << FPSDisplay;
        GlobalRender->Print(ss.str(), sf::Vector2f(10, 10), 24);
    }
    
    
    GameConsole->draw(hwnd);
    KeyManger->Reset();
    
    
    if(GameState==INGAME)
    sf::Vector2f pos=S2W(Camera->GetCursorPos()); 
}


void cGame::Update(sf::Time dtime){
    
    if(dtime.asMilliseconds()>500)//delta too big lag, ignore
        return;
    
    
    ParticleSystem->Update(dtime);
    if(GameState==INGAME){
        if(KeyManger->Clicked(KEY_B))
            GUI->SetVisible(BUILD_WINDOW, true);
        
        Camera->SetView(hwnd);
        Camera->UpdateMapCursorPos(hwnd);
        
        
        Selector->Update();
        Camera->Update(dtime);
        Camera->SetType(CVARS->iGetValue(var_CameraMode));
        ObjectManger->Update(dtime);
        
        Camera->ReturnToDefaultView(hwnd);
        
        if((ObjectManger->ServiceStationExist()&&Globals.GameTimer.getElapsedTime().asSeconds()>TIMELIMIT*60)){
            GameState=INSCORE;
            SoundManger->CleanUP();
            SoundManger->PlaySound(SOUND_WIN);
            Timer.restart();
            Score=(ObjectManger->GetNumberOfPlayers()*LocalPlayer.GetUranium()*(ObjectManger->GetPlayersHealthSum()/2));
        }
        
        if((ObjectManger->GetNumberOfPlayers()==0)||
           (!ObjectManger->ServiceStationExist()&&Globals.GameTimer.getElapsedTime().asSeconds()>TIMELIMIT*60)){
            GameState=INGAMEOVER;
            SoundManger->CleanUP();
            SoundManger->PlaySound(SOUND_GAMEOVER);
            Timer.restart();
        }
        
    }else if(GameState==MAINMENU){
        SpashScreen->UpdateMenuPlane(dtime); 
    }else if(GameState==INLOADINGGAME){
        SpashScreen->UpdateMenuPlane(dtime);
        
        if(SpashScreen->ShouldDrawMap()){
            Camera->SetView(hwnd);
            Camera->UpdateMapCursorPos(hwnd);
            Selector->Update();
            Camera->Update(dtime);
            Camera->SetType(CVARS->iGetValue(var_CameraMode));
            ObjectManger->Update(dtime);
            Camera->ReturnToDefaultView(hwnd);
        }
    }
    
    GUI->Update(hwnd);
    
    sGuiEvent event;
    while(GUI->GetEvent(event)){
        switch (event.type) {
            case CLICKED:
                
                if(event.ID==GAMETAB_MENU)
                    GUI->SetVisible(GAME_WINDOW, true);
                
                if(event.ID==TRAIN_ROOM_BUTTON_TRAIN)
                    Selector->Train();
				if (event.ID == BUILD_ICO)
                    GUI->SetVisible(BUILD_WINDOW, true);
                if(event.ID==SERVICE_CLOSE)
                    GUI->SetVisible(SERVICE_WINDOW, false);
                if(event.ID==TRAIN_ROOM_CLOSE)
                    GUI->SetVisible(TRAIN_ROOM_WINDOW, false);
                if(event.ID==INTRO_CLOSE)
                    GUI->SetVisible(INTRO_WINDOW, false);
                if(event.ID==GAME_RESUME)
                    GUI->SetVisible(GAME_WINDOW, false);
                if(event.ID==GAME_SETTINGS)
                    GUI->SetVisible(SETTINGS_WINDOW, true);
                if(event.ID==GAME_EXIT_TO_MENU){
                    GUI->HideAll();
                    GameState=MAINMENU; 
                    ObjectManger->Clear();
                    GUI->SetVisible(MAINMENU_PANEL, true);
                    ParticleSystem->AddEffect(sf::Vector2f(100,100), FIRE,0);
                    ParticleSystem->AddEffect(sf::Vector2f(100,400), FIRE,1);
                    ParticleSystem->AddEffect(sf::Vector2f(0,0), STARS,2);
                    MusicPlayer->StopAll();
                    MusicPlayer->Play(MUSIC_MENU);
                }
                if(event.ID==GAME_EXIT_TO_DESKTOP)
                    exit(0);
                
                
                if(event.ID==MAINMENU_BUTTON_EXIT)
                    exit(0);
                if(event.ID==MAINMENU_BUTTON_SETTINGS)
                    GUI->SetVisible(SETTINGS_WINDOW, true);
                if(event.ID==SETTINGS_CLOSE)
                    GUI->SetVisible(SETTINGS_WINDOW, false);
                if(event.ID==BUILD_CLOSE)
                    GUI->SetVisible(BUILD_WINDOW, false);
                if(event.ID==MAINMENU_BUTTON_NEWGAME){
                    LocalPlayer.SetMetal(0);
                    LocalPlayer.SetUranium(0);
                    LocalPlayer.SetStone(150);
                    GameState=INLOADINGGAME;
                    GUI->HideAll();
                    MusicPlayer->StopAll();
                    SpashScreen->ResetTransition();
                    
                    Camera->GoToBase();
                    Globals.GameTimer.restart();
                    
                    ObjectManger->Clear();
                    GameWorld->Generate();
                    
                    SoundManger->PlaySound(SOUND_TRANSITION);
                }
                
                
                if(event.ID==BUILD_BUTTON_BUILD){
                    switch(LocalPlayer.BuildID){
                        case STORE_HOUSE:
                            Selector->SetBuilder(OBJ_BUILDING_CORRIDOR_OPEN_NE);
                            break;
                        case TRAINROOM:
                            Selector->SetBuilder(OBJ_BUILDING_OPEN_NE);
                            break;
                        case SERVICE_STATION:
                            Selector->SetBuilder(OBJ_FRAME_HIGH_TILE_NE);
                            break;
                        case WATER_FILTER:
                            Selector->SetBuilder(OBJ_BARREL_LARGE_NE);
                            break;
                        case PIPE:
                            Selector->SetBuilder(OBJ_PIPE_STRAIGHT_NE);
                            break;
                    };
                    
                }
                
                break;
            case CHANGED:
                if(event.ID==SETTINGS_CAMERA_TYPE){
                    Camera->SetType(event.iVar);
                    CVARS->iSetValue(var_CameraMode,event.iVar);
                }
                
                if(event.ID==BUILD_LIST){
                    sText<std::string>*desc=(sText<std::string>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_DESC);
                    if(desc!=nullptr){
                        if(event.iVar==0){
                            desc->SetVar("It is used to store all\nyour resources.");
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT1))->SetVar(150);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT2))->SetVar(0);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT3))->SetVar(0);
                            LocalPlayer.BuildID=STORE_HOUSE;
                            LocalPlayer.SetPayAmount(sResources(150,0,0));
                        }else if(event.iVar==1){
                            desc->SetVar("You can transport water\nwith it.");
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT1))->SetVar(0);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT2))->SetVar(0);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT3))->SetVar(25);
                            LocalPlayer.BuildID=PIPE;
                            LocalPlayer.SetPayAmount(sResources(0,0,15));
                        }else if(event.iVar==2){
                            desc->SetVar("You can train your astronauts\nthere so they can\nface aliens.");
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT1))->SetVar(250);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT2))->SetVar(0);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT3))->SetVar(100);
                            LocalPlayer.BuildID=TRAINROOM;
                            LocalPlayer.SetPayAmount(sResources(250,0,100));
                        }else if(event.iVar==3){
                            desc->SetVar("It is required for filtration.\nRegenerates whole health.\n(breaks after 3 uses)");
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT1))->SetVar(75);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT2))->SetVar(0);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT3))->SetVar(40);
                            LocalPlayer.BuildID=WATER_FILTER;
                            LocalPlayer.SetPayAmount(sResources(75,0,40));
                        }else if(event.iVar==4){
                            desc->SetVar("It is used to comunicate\nwith the base.");
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT1))->SetVar(180);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT2))->SetVar(0);
                            ((sText<int>*)GUI->GetElement(GUI->GetWindow(BUILD_WINDOW), BUILD_COST_TEXT3))->SetVar(555);
                            LocalPlayer.BuildID=SERVICE_STATION;
                            LocalPlayer.SetPayAmount(sResources(180,0,555));
                        }
                    }
                }
                if(event.ID==SETTINGS_MUSIC_SLIDER){
                    MusicPlayer->SetVolume(event.iVar);
                }
                if(event.ID==SETTINGS_SOUNDS_SLIDER){
                    SoundManger->SetVolume(event.iVar);
                }
                break;
                
            case CHECKED:
                if(event.ID==SETTINGS_MUSIC_CHECKBOX){
                    MusicPlayer->SetEnable(event.iVar);
                    if(GameState==MAINMENU)
                        MusicPlayer->Play(MUSIC_MENU);
                    else
                        MusicPlayer->Play(MUSIC_GAME);
                }
                if(event.ID==SETTINGS_SOUNDS_CHECKBOX){
                    SoundManger->Enabled=event.iVar;
                }
                break;
            default:
                break;
        }
    }
    
    
   // GameWorld->Update(dtime);
}

cGame::~cGame() {
    
    
}

