#pragma once
#include <SFML/Graphics.hpp>
#include "TextureManger.h"
#include "Utils.h"
#include "SoundManger.h"
#include "Globals.h"
#include "GlobalRender.h"




void AddEvent(int ID, int type);

enum{
    MAINMENU_PANEL,
    MAINMENU_BUTTON_NEWGAME,
    MAINMENU_BUTTON_CONTINUE,
    MAINMENU_BUTTON_SETTINGS,
    MAINMENU_CREDITS,
    MAINMENU_BUTTON_EXIT,

    SETTINGS_WINDOW,
    SETTINGS_MUSIC_CHECKBOX,
    SETTINGS_MUSIC_SLIDER,
    SETTINGS_SOUNDS_CHECKBOX,
    SETTINGS_SOUNDS_SLIDER,
    SETTINGS_CAMERA_TYPE,
    SETTINGS_CAMERA_TEXT,
    SETTINGS_CLOSE,
    
    GAME_WINDOW,
    GAME_RESUME,
    GAME_SETTINGS,
    GAME_EXIT_TO_MENU,
    GAME_EXIT_TO_DESKTOP,
    
    GAMETAB_PANEL,
    GAMETAB_MENU,
    GAMETAB_TEXT_STONE,
    GAMETAB_TEXT_URANIUM,
    GAMETAB_TEXT_METAL,
	GAME_TAB_MINUTES,
	GAME_TAB_SECONDS,
    
    BUILD_WINDOW,
    BUILD_DESC,
    BUILD_LIST,
    BUILD_BUTTON_BUILD,
    BUILD_ICON1,
    BUILD_ICON2,
    BUILD_ICON3,
    BUILD_COST_TEXT1,
    BUILD_COST_TEXT2,
    BUILD_COST_TEXT3,
    BUILD_CLOSE,

	BUILD_ICO,
	BUILD_PANEL,
    
    TRAIN_ROOM_WINDOW,
    TRAIN_ROOM_DESC,
    TRAIN_ROOM_BUTTON_TRAIN,
    TRAIN_ROOM_CLOSE,
    
    INTRO_WINDOW,
    INTRO_TEXT,
    INTRO_CLOSE,
    
    SERVICE_WINDOW,
    SERVICE_TEXT,
    SERVICE_CLOSE,
    
    TEST_TEXT,
    RESOURCES_HWND,
    RESOURCES_HWND_X,
    TEST_SLIDER,
    ELEMENTS_MAX,
};

enum CONTROL_STATE{
    NORMAL,
    HOVER,
    PUSHED,
    CLICKED,
    CHECKED,
    CHANGED,
    OPENED,
};

struct sGuiEvent{
    sGuiEvent(){}
    sGuiEvent(int ID, int type){
        this->ID=ID;
        this->type=type;
    }
    
    sGuiEvent(int ID, int type, int iVar){
        this->ID=ID;
        this->type=type;
        this->iVar=iVar;
    }
    int ID;
    int type;
    float flVar;
    int iVar;
};


//Panel POS
enum PANEL_POS{
    left,
    right,
    center,
    up,
    down
};

enum GUI_ELEMENT{
    TEXT,
    IMG,
    WINDOW,
    BUTTON,
    SLIDER,
    CHECKBOX
};

struct sMouseState{
    bool bLeftClicked, bLeftLast;
    bool bRightClicked, bRightLast;
    int ID;
    sf::Clock Timer;
    sf::Vector2i Pos;
};


struct sBaseElement{
    sf::Vector2i Pos;
    sf::Vector2i Size;
    sf::Int32 LastClicked;
    bool bVisible;
    int type;
    sBaseElement* parent;
    std::vector<sBaseElement*> children;
    int ID;
    virtual void Draw(sf::RenderWindow *hwnd) = 0;
    virtual void Control(sMouseState &state) = 0;
    sf::Vector2i GetPos(){
        if(parent)
            return Pos+parent->GetPos();
        return Pos;
    }
    void AddChild(sBaseElement* element){
        element->parent=this;
        children.push_back(element);
    }
};

struct sWindow: public sBaseElement{
    int TabSize;
    sf::Vector2i TouchPOS;
    std::string Title;
    bool TabClicked;
    sWindow(sf::Vector2i iPos, sf::Vector2i iSize, std::string iText, int iID, int iTabSize=-1, bool Visible=true){
        Pos=iPos;
        Title=iText;
        type=TEXT;
        ID=iID;
        Size=iSize;
        bVisible=Visible;
        TabSize=iTabSize;
        LastClicked=0;
        parent=nullptr;
        TabClicked=false;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        if(!bVisible)
            return;
        GlobalRender->DrawWindow(Vec2Vec<int, float>(GetPos()), Size);
        
        for(auto element: children)
            element->Draw(hwnd);
        
    }
    
    virtual void Control(sMouseState &state){
        if(!bVisible)
            return;
        
        int oldStateID=state.ID;
        for(auto child:children)
            child->Control(state);
        
        if(state.ID!=oldStateID){//child clicked
            LastClicked=state.Timer.getElapsedTime().asMilliseconds();
        }
            
        if(state.bLeftClicked&&!state.bLeftLast&&state.ID==-1){
            //catch
            if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
               state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+TabSize)
            {
                TouchPOS=state.Pos;
                state.ID=ID;
                LastClicked=state.Timer.getElapsedTime().asMilliseconds();
                TabClicked=true;
            }else if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
               state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
            {
                TouchPOS=state.Pos;
                state.ID=ID;
                LastClicked=state.Timer.getElapsedTime().asMilliseconds();
            }
            
        }else if(state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
            if(TabClicked){
                Pos-=(TouchPOS-state.Pos);
                TouchPOS=state.Pos;
            }
        }else if(!state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
            //restore
            state.ID=-1;
            TabClicked=false;
        }
    }
};

struct sStaticPanel: public sBaseElement{
    sf::Vector2i TouchPOS;
    std::string Title;
    bool TabClicked;
    int PosX,PosY;
    sStaticPanel(int iPosX, int iPosY, sf::Vector2i iSize, int iID, bool Visible=true){
        Pos=sf::Vector2i(0,0);
        type=TEXT;
        PosX=iPosX;
        PosY=iPosY;
        ID=iID;
        Size=iSize;
        bVisible=Visible;
        LastClicked=0;
        parent=nullptr;
        TabClicked=false;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        if(!bVisible)
            return;
        for(auto element: children)
            element->Draw(hwnd);
        
    }
    
    virtual void Control(sMouseState &state){
        if(!bVisible)
            return;
        Pos=sf::Vector2i(0,0);
        switch(PosX){
            case PANEL_POS::left:
                Pos.x=0;
                break;
            case PANEL_POS::right:
                Pos.x=Globals.Width-Size.x;
                break;
            case PANEL_POS::center:
                Pos.x=(Globals.Width/2.f)-(Size.x/2.f);
                break;
        }
        switch(PosY){
            case PANEL_POS::up:
                Pos.y=0;
                break;
            case PANEL_POS::down:
                Pos.y=Globals.Height-Size.y;
                break;
            case PANEL_POS::center:
                Pos.y=(Globals.Height/2.f)-(Size.y/2.f);
                break;
        }
        
        int oldStateID=state.ID;
        for(auto child:children)
            child->Control(state);
        
        if(state.ID!=oldStateID){
            
        }
        
    }
};



struct sButton: public sBaseElement{
    std::string Title;
    sf::Sprite spriteNormal, spriteHover, spriteClicked;
    int BoxRenderState;
    int textSize;
    sButton(sf::Vector2i iPos, sf::Vector2i iSize, std::string iText, sf::Texture *tex, sf::Texture *tex2, sf::Texture *tex3, int iID,  bool Visible=true, int itextSize=-1){
        Pos=iPos;
        Title=iText;
        type=TEXT;
        ID=iID;
        Size=iSize;
        bVisible=Visible;
        if(tex)
            spriteNormal.setTexture(*tex);
        if(tex2)
            spriteHover.setTexture(*tex2);
        if(tex3)
        spriteClicked.setTexture(*tex3);
        parent=nullptr;
        BoxRenderState=NORMAL;
        textSize=itextSize;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        if(textSize!=-1){
            GlobalRender->DrawSimpleButton(sf::Vector2f(GetPos().x,GetPos().y), Size, Title, 16,BoxRenderState);
        
        }else{
            switch(BoxRenderState){
                case NORMAL:
                    spriteNormal.setPosition(Vec2Vec<int, float>(GetPos()));
                    hwnd->draw(spriteNormal);
                    break;
                case HOVER:
                    spriteHover.setPosition(Vec2Vec<int, float>(GetPos()));
                    hwnd->draw(spriteHover);
                    break;
                case PUSHED:
                    spriteClicked.setPosition(Vec2Vec<int, float>(GetPos()));
                    hwnd->draw(spriteClicked);
                    break;
                    
            }
        }
        
        
    }
    virtual void Control(sMouseState &state);
    
};

struct sCheckBox: public sBaseElement{
    std::string Title;
    int BoxRenderState;
    bool Checked;
    sCheckBox(sf::Vector2i iPos, sf::Vector2i iSize, std::string iText, int iID, bool bChecked=false, bool Visible=true){
        Pos=iPos;
        Title=iText;
        type=TEXT;
        ID=iID;
        Size=iSize;
        bVisible=Visible;
        Checked=bChecked;
        parent=nullptr;
        BoxRenderState=NORMAL;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        GlobalRender->DrawCheckBox(Vec2Vec<int, float>(GetPos()), Title, Checked);
    }
    
    virtual void Control(sMouseState &state);
};

struct sSlider: public sBaseElement{
    std::string Title;
    int Length;
    int Value, Max;
    int ButtonPos;
    sSlider(sf::Vector2i iPos, int Length, int Val, int Max, int iID,  bool Visible=true){
        Pos=iPos;
        type=TEXT;
        ID=iID;
        this->Length=Length;
        bVisible=Visible;
        parent=nullptr;
        Value=Val;
        this->Max=Max;
        Size=sf::Vector2i(Length,8);
        ButtonPos=((float)Val/(float)Max)*Length;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        GlobalRender->DrawSlider<int>(Vec2Vec<int, float>(GetPos()), Length, ButtonPos, Value);
    }
    
    virtual void Control(sMouseState &state);
};


struct sListBox: public sBaseElement{
    int BoxRenderState;
    const char **TextList;
    int ListSize;
    int CurrentID;
    int HoverID;
    sListBox(sf::Vector2i iPos, sf::Vector2i iSize, const char **TextList, int iListSize,int iID, bool Visible=true){
        Pos=iPos;
        type=TEXT;
        ID=iID;
        Size=iSize;
        bVisible=Visible;
        parent=nullptr;
        ListSize=iListSize;
        this->TextList=TextList;
        BoxRenderState=NORMAL;
        CurrentID=0;
        HoverID=-1;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        if(!bVisible)
            return;
        
        GlobalRender->DrawRect(Vec2Vec<int,float>(GetPos()), Size, GlobalRender->GetBaseColor(1), GlobalRender->GetBaseColor((BoxRenderState==CONTROL_STATE::NORMAL?0:2)), 3);
        
        GlobalRender->PrintTextCenterY<std::string>(TextList[CurrentID],Vec2Vec<int,float>(GetPos()+sf::Vector2i(4,Size.y/4)),sf::Color::Black,FontManger->GetFont(0),20);
        
        
        if(BoxRenderState==CONTROL_STATE::OPENED){
            for(int i=0;i<ListSize;i++){
                int j=i+1;
                GlobalRender->DrawRect(Vec2Vec<int,float>(GetPos()+sf::Vector2i(0,j*Size.y)), Size, GlobalRender->GetBaseColor(1), GlobalRender->GetBaseColor((HoverID==i)?0:2), 2);
                GlobalRender->PrintTextCenterY<std::string>(TextList[i],Vec2Vec<int,float>(GetPos()+sf::Vector2i(4,Size.y/4+j*Size.y)),sf::Color::Black,FontManger->GetFont(0),20);
            }
        }
        
    }
    virtual void Control(sMouseState &state);
    
};


struct sImg: public sBaseElement{
    sImg(sf::Vector2i iPos, sf::Texture *tex, int iID, bool Visible=true){
        Pos=iPos;
        type=TEXT;
        ID=iID;
        img.setTexture(*tex);
        bVisible=Visible;
    }
    sf::Sprite img;
    virtual void Draw(sf::RenderWindow *hwnd){
        img.setPosition(Vec2Vec<int,float>(GetPos()));
        hwnd->draw(img);
    }
    
    virtual void Control(sMouseState &state){
        
    }
    
    
};


template <typename T>
struct sText: public sBaseElement{
    sText(sf::Vector2i iPos, T iText, int iID, int iFont, int iSize, sf::Color col, bool bCenter=false, bool Visible=true){
        Pos=iPos;
        Text=iText;
        type=TEXT;
        ID=iID;
        bVisible=Visible;
        Font=iFont;
        Size=iSize;
        Color=col;
        Center=bCenter;
    }
    virtual void Draw(sf::RenderWindow *hwnd){
        sf::Vector2f vecPos=Vec2Vec<int,float>(GetPos());
        std::stringstream ss;
        ss<<Text;
        GlobalRender->PrintString(ss.str(), vecPos, Color, FontManger->GetFont(Font), Size, Center);
    }
    
    virtual void Control(sMouseState &state){
        
    }
    
    void SetVar(T var){
        Text=var;
    }
    
    T Text;
    int Font;
    int Size;
    bool Center;
    sf::Color Color;
};

static const char* sBuildList[] = {
    "Storehouse",
    "Pipe",
    "Barracks",
    "Water Filter",
    "Service station",
};

static const char* sCameraType[] = {
    "Standard",
    "Panorama",
    "Corner",
};



class cGUI{
    sMouseState MouseState;
    std::vector<sBaseElement*> Windows;
    std::vector<sGuiEvent>Events;
public:
    
    cGUI(){
        MouseState.ID=-1;
        MouseState.bLeftClicked=false;
        MouseState.bLeftLast=false;
        MouseState.bRightClicked=false;
        MouseState.bRightLast=false;
        MouseState.Timer.restart();
        
        
        Windows.push_back(new sWindow(sf::Vector2i(570,255),sf::Vector2i(140,210), "Settings",SETTINGS_WINDOW, 30,false));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sCheckBox(sf::Vector2i(20,30), sf::Vector2i(20,20), "Music", SETTINGS_MUSIC_CHECKBOX,true));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sSlider(sf::Vector2i(20,60), 100, 100, 100, SETTINGS_MUSIC_SLIDER));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sCheckBox(sf::Vector2i(20,100), sf::Vector2i(20,20), "Sounds", SETTINGS_SOUNDS_CHECKBOX,true));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sSlider(sf::Vector2i(20,130), 100, 100, 100, SETTINGS_SOUNDS_SLIDER));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sListBox(sf::Vector2i(20,175),sf::Vector2i(100,20),sCameraType,3, SETTINGS_CAMERA_TYPE));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sText<std::string>(sf::Vector2i(20,155), "Camera Type", SETTINGS_CAMERA_TEXT, FONT_MAIN, 16, sf::Color::Black));
        GetWindow(SETTINGS_WINDOW)->AddChild(new sButton(sf::Vector2i(140-32,0), sf::Vector2i(32,32), "Close", TextureManger->GetTexture(OBJ_BUTTON_X1),TextureManger->GetTexture(OBJ_BUTTON_X2),TextureManger->GetTexture(OBJ_BUTTON_X3), SETTINGS_CLOSE));
        
       
        
        Windows.push_back(new sStaticPanel(PANEL_POS::center,PANEL_POS::down,sf::Vector2i(420,560),MAINMENU_PANEL));
        GetWindow(MAINMENU_PANEL)->AddChild(new sButton(sf::Vector2i(74,320), sf::Vector2i(272,52), "New Game", nullptr,nullptr,nullptr, MAINMENU_BUTTON_NEWGAME, true, 22));
        GetWindow(MAINMENU_PANEL)->AddChild(new sButton(sf::Vector2i(74,320+60*1), sf::Vector2i(272,52), "Settings", nullptr,nullptr,nullptr, MAINMENU_BUTTON_SETTINGS, true, 22));
        GetWindow(MAINMENU_PANEL)->AddChild(new sButton(sf::Vector2i(74,320+60*2), sf::Vector2i(272,52), "Quit", nullptr,nullptr,nullptr, MAINMENU_BUTTON_EXIT, true, 22));
        
       
        Windows.push_back(new sWindow(sf::Vector2i(540,200),sf::Vector2i(200,200), "Game window",GAME_WINDOW, 15,false));
        GetWindow(GAME_WINDOW)->AddChild(new sButton(sf::Vector2i(15,15), sf::Vector2i(170,40), "Resume", nullptr,nullptr,nullptr, GAME_RESUME,true,20));
        GetWindow(GAME_WINDOW)->AddChild(new sButton(sf::Vector2i(15,60), sf::Vector2i(170,40), "Settings", nullptr,nullptr,nullptr, GAME_SETTINGS,true,20));
        GetWindow(GAME_WINDOW)->AddChild(new sButton(sf::Vector2i(15,105), sf::Vector2i(170,40), "Exit to menu", nullptr,nullptr,nullptr, GAME_EXIT_TO_MENU,true,20));
        GetWindow(GAME_WINDOW)->AddChild(new sButton(sf::Vector2i(15,150), sf::Vector2i(170,40), "Exit to Desktop", nullptr,nullptr,nullptr, GAME_EXIT_TO_DESKTOP,true,20));
        
        
        
        Windows.push_back(new sStaticPanel(PANEL_POS::left,PANEL_POS::up,sf::Vector2i(28,100),GAMETAB_PANEL,false));
        GetWindow(GAMETAB_PANEL)->AddChild(new sButton(sf::Vector2i(3,0), sf::Vector2i(70,24), "Menu", nullptr,nullptr,nullptr, GAMETAB_MENU,true,14));
        GetWindow(GAMETAB_PANEL)->AddChild(new sText<int>(sf::Vector2i(190,0), 150, GAMETAB_TEXT_STONE, FONT_MAIN, 18, sf::Color::Black));
        GetWindow(GAMETAB_PANEL)->AddChild(new sText<int>(sf::Vector2i(415,0), 0, GAMETAB_TEXT_URANIUM, FONT_MAIN, 18, sf::Color::Black));
        GetWindow(GAMETAB_PANEL)->AddChild(new sText<int>(sf::Vector2i(610,0), 0, GAMETAB_TEXT_METAL, FONT_MAIN, 18, sf::Color::Black));
		GetWindow(GAMETAB_PANEL)->AddChild(new sText<std::string>(sf::Vector2i(814, 0), "20", GAME_TAB_MINUTES, FONT_MAIN, 18, sf::Color::Black));
		GetWindow(GAMETAB_PANEL)->AddChild(new sText<std::string>(sf::Vector2i(838, 0), "00", GAME_TAB_SECONDS, FONT_MAIN, 18, sf::Color::Black));

		
        
        Windows.push_back(new sWindow(sf::Vector2i(200,200),sf::Vector2i(300,240), "Build",BUILD_WINDOW, 30,false));
        GetWindow(BUILD_WINDOW)->AddChild(new sImg(sf::Vector2i(15,100), TextureManger->GetTexture(OBJ_ICON_STONE), BUILD_ICON1));
        GetWindow(BUILD_WINDOW)->AddChild(new sImg(sf::Vector2i(15,132), TextureManger->GetTexture(OBJ_ICON_URANIUM), BUILD_ICON2));
        GetWindow(BUILD_WINDOW)->AddChild(new sImg(sf::Vector2i(15,164), TextureManger->GetTexture(OBJ_ICON_METAL), BUILD_ICON3));
        GetWindow(BUILD_WINDOW)->AddChild(new sText<int>(sf::Vector2i(50,102), 150, BUILD_COST_TEXT1, FONT_MAIN, 18, sf::Color::Black));
        GetWindow(BUILD_WINDOW)->AddChild(new sText<int>(sf::Vector2i(50,134), 0, BUILD_COST_TEXT2, FONT_MAIN, 18, sf::Color::Black));
        GetWindow(BUILD_WINDOW)->AddChild(new sText<int>(sf::Vector2i(50,166), 0, BUILD_COST_TEXT3, FONT_MAIN, 18, sf::Color::Black));
        GetWindow(BUILD_WINDOW)->AddChild(new sText<std::string>(sf::Vector2i(15,50), "It is used to store all\nyour resources.", BUILD_DESC, FONT_MAIN, 16, sf::Color::Black,0));
        GetWindow(BUILD_WINDOW)->AddChild(new sListBox(sf::Vector2i(20,20),sf::Vector2i(230,20),sBuildList,5, BUILD_LIST));
        GetWindow(BUILD_WINDOW)->AddChild(new sButton(sf::Vector2i(15, 200), sf::Vector2i(60,30), "BUILD", nullptr,nullptr,nullptr, BUILD_BUTTON_BUILD, true, 18));
        GetWindow(BUILD_WINDOW)->AddChild(new sButton(sf::Vector2i(300-32,0), sf::Vector2i(32,32), "Close", TextureManger->GetTexture(OBJ_BUTTON_X1),TextureManger->GetTexture(OBJ_BUTTON_X2),TextureManger->GetTexture(OBJ_BUTTON_X3), BUILD_CLOSE));
        
        Windows.push_back(new sWindow(sf::Vector2i(400,200),sf::Vector2i(190,120), "TrainRoom",TRAIN_ROOM_WINDOW, 30,false));
        GetWindow(TRAIN_ROOM_WINDOW)->AddChild(new sButton(sf::Vector2i(35, 20), sf::Vector2i(120,45), "TRAIN", nullptr,nullptr,nullptr, TRAIN_ROOM_BUTTON_TRAIN, true, 18));
        GetWindow(TRAIN_ROOM_WINDOW)->AddChild(new sButton(sf::Vector2i(190-32,0), sf::Vector2i(32,32), "Close", TextureManger->GetTexture(OBJ_BUTTON_X1),TextureManger->GetTexture(OBJ_BUTTON_X2),TextureManger->GetTexture(OBJ_BUTTON_X3), TRAIN_ROOM_CLOSE));
        GetWindow(TRAIN_ROOM_WINDOW)->AddChild(new sText<std::string>(sf::Vector2i(15,85), "*It will change their\n current abilities.", BUILD_DESC, FONT_MAIN, 12, sf::Color::Red,0));
        
        Windows.push_back(new sWindow(sf::Vector2i(495,140),sf::Vector2i(290,350), "Intro",INTRO_WINDOW, 30,0));
        GetWindow(INTRO_WINDOW)->AddChild(new sButton(sf::Vector2i(290-32,0), sf::Vector2i(32,32), "Close", TextureManger->GetTexture(OBJ_BUTTON_X1),TextureManger->GetTexture(OBJ_BUTTON_X2),TextureManger->GetTexture(OBJ_BUTTON_X3), INTRO_CLOSE));
        GetWindow(INTRO_WINDOW)->AddChild(new sText<std::string>(sf::Vector2i(15,20), "It's year 2337.\nAfter many years of \nextracting, there is no place \non earth to find Uranium. \n\nYou are the leader of \nUranium excavation mission.\nUnfortunately your ship was \ndestroyed during the landing. \nNow you have to find a way to \ncommunicate with the base to\ninform about this situation \nand give deatils about \ndestination.\nBefore the next ship arrives, \ngather as much Uranium \nas you can.\nGood luck!", INTRO_TEXT, FONT_MAIN, 16, sf::Color::Black,0));
        
        Windows.push_back(new sWindow(sf::Vector2i(495,140),sf::Vector2i(250,120), "Intro",SERVICE_WINDOW, 30,0));
        GetWindow(SERVICE_WINDOW)->AddChild(new sButton(sf::Vector2i(250-32,0), sf::Vector2i(32,32), "Close", TextureManger->GetTexture(OBJ_BUTTON_X1),TextureManger->GetTexture(OBJ_BUTTON_X2),TextureManger->GetTexture(OBJ_BUTTON_X3), SERVICE_CLOSE));
        GetWindow(SERVICE_WINDOW)->AddChild(new sText<std::string>(sf::Vector2i(15,20), "You have successfully\nestablished connection\nwith the base. Next ship\nwill arrive soon, until\nthen collect uranium.", SERVICE_TEXT, FONT_MAIN, 16, sf::Color::Black,0));
        

        
		Windows.push_back(new sStaticPanel(PANEL_POS::right, PANEL_POS::down, sf::Vector2i(1, 1), BUILD_PANEL, false));
		GetWindow(BUILD_PANEL)->AddChild(new sButton(sf::Vector2i(-84, -84), sf::Vector2i(84, 84), "Build", TextureManger->GetTexture(OBJ_BUILD_ICO1), TextureManger->GetTexture(OBJ_BUILD_ICO2), TextureManger->GetTexture(OBJ_BUILD_ICO3), BUILD_ICO));

        /*
	BUILD_ICO,
	BUILD_PANEL,*/

        
    }
    void Draw(sf::RenderWindow *hwnd){
        for(int i=Windows.size()-1;i>=0;i--)
            Windows[i]->Draw(hwnd);
    }
    
    void Update(sf::RenderWindow *hwnd){
        MouseState.Pos = sf::Mouse::getPosition(*hwnd);
        MouseState.bLeftClicked=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        MouseState.bRightClicked=sf::Mouse::isButtonPressed(sf::Mouse::Right);
        
        for(auto window: Windows)
            window->Control(MouseState);
        
        MouseState.bLeftLast=sf::Mouse::isButtonPressed(sf::Mouse::Left);
        MouseState.bRightLast=sf::Mouse::isButtonPressed(sf::Mouse::Right);
        
        
        if(MouseState.ID!=-1){
            std::sort(Windows.begin(), Windows.end(),
                      [] (sBaseElement * v1, sBaseElement * v2) { return v1->LastClicked > v2->LastClicked; });
        }
        
    }
    
    void AddEvent(sGuiEvent event){
        Events.push_back(event);
    }
    bool GetEvent(sGuiEvent& event){
        if(Events.size()>0){
            event=Events.back();
            Events.pop_back();
            return true;
        }
        return false;
    }
    
    void SetVisible(int ID, bool Visible){
        for(sBaseElement *window: Windows)
            if(window->ID==ID)
                window->bVisible=Visible;
    }
    
    sBaseElement *GetWindow(int ID){
        for(sBaseElement *window: Windows)
            if(window->ID==ID)
                return window;
        return nullptr;
    }
    
    sBaseElement *GetElement(sBaseElement *parent, int ID){
        for(sBaseElement *child: parent->children){
            if(child->ID==ID)
                return child;
            if(child->children.size()>0){
                sBaseElement *GrandChild=GetElement(child, ID);
                if(GrandChild!=nullptr)
                    return GrandChild;
            }
        }
           
        return nullptr;
    }
    
    
    void HideAll(){
        for(sBaseElement *window: Windows)
            window->bVisible=false;
    }
    
    bool Active(){ return (MouseState.ID==-1)?false:true;}
    
};


extern cGUI *GUI;

