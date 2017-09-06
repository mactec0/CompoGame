#include "Game.h"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>


cParticleSystem *ParticleSystem;
cTextureManger *TextureManger;
cInGameConsole *GameConsole;
cGlobalRender *GlobalRender;
cObjectManger *ObjectManger;
cMusicPlayer *MusicPlayer;
cSoundManger *SoundManger;
cLocalPlayer LocalPlayer;
cVisibleArea VisibleArea;
cFontManger *FontManger;
cKeyManger* KeyManger;
cSelector *Selector;
cPathFinder *Path;
CVARManger* CVARS;
cGlobals Globals;
cCamera *Camera;
cMap *GameWorld;
cGUI *GUI;




int main(int, char const**)
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(1280, 800), L"Game");
    window.setFramerateLimit(144);
     
    ParticleSystem = new cParticleSystem();
    TextureManger = new cTextureManger();
    ObjectManger = new cObjectManger();
    KeyManger = new cKeyManger();
    CVARS = new CVARManger();
    Selector = new cSelector();
    GameConsole = new cInGameConsole();
    SoundManger = new cSoundManger();
    FontManger = new cFontManger();
    MusicPlayer= new cMusicPlayer();
    cGame *Game;
    Game = new cGame(&window);
    Camera = new cCamera();
    GUI =new cGUI();
    
    
    sf::Clock GameClock;
    bool ScrollSetThisTick;
    
    while (window.isOpen())
    {
        sf::Time deltaTime=GameClock.restart();
        Globals.dScroll=0;
        sf::Event event;
        ScrollSetThisTick=false;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::Resized) {
                Globals.Height = event.size.height;
                Globals.Width = event.size.width;
                window.setView(sf::View(sf::FloatRect(0, 0, Globals.Width, Globals.Height)));
            }
            if(event.type == sf::Event::MouseWheelScrolled){
                if(event.mouseWheelScroll.delta!=0&&!ScrollSetThisTick){
                    
                } 
            }
            
            
            for (int i = 0; i < KEY_MAX; i++)
                if (event.type == sf::Event::KeyPressed && event.key.code == i){
                    KeyManger->SetValue(i,true);
                }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
                if(Game->GetState()==GAMESTATE::MAINMENU)
                    window.close();
                if(Game->GetState()==GAMESTATE::INGAME){
                    GUI->SetVisible(GAME_WINDOW, true);
                }
            }
            if(CVARS->iGetValue(var_Quit))
                window.close();
        }
        
        
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab))
			Camera->GoToBase();
        
         
        
        Game->Update(deltaTime);
        Game->Render(&window);
        window.display();
    }
    
    return EXIT_SUCCESS;
}
