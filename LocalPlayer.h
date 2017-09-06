#pragma once
#include "GUI.h"

struct sResources{
    sResources(int v1, int v2, int v3){
        Stone=v1;
        Uranium=v2;
        Metal=v3;
    }
    sResources(){
        Stone=0;
        Uranium=0;
        Metal=0;
    }
    
    inline bool operator=(sResources in) {
        Stone=in.Stone;
        Uranium=in.Uranium;
        Metal=in.Metal;
		return true;
    }
    
    int GetSum(){return Stone+Uranium+Metal;}
    int Stone,Uranium,Metal;
    
};

enum BUILD{
    BSTOREHOUSE,
    BPIPE,
    BTRANSMITSTATION,
    BTRAINROOM,
};

class cLocalPlayer{
    sResources Resources;
    sResources ToPay;
public:
    int BuildID;
    cLocalPlayer(){
        Reset();
    }
    void Reset(){
        Resources.Stone=150;
        Resources.Uranium=0;
        Resources.Metal=0;
        
        
        ToPay.Stone=150;
        ToPay.Uranium=0;
        ToPay.Metal=0;
        
        BuildID=0;
    }
    
    void SetPayAmount(sResources toPay){
        ToPay=toPay;
    }
    
    bool Pay(){
        if(Resources.Stone>=ToPay.Stone&&
           Resources.Uranium>=ToPay.Uranium&&
           Resources.Metal>=ToPay.Metal){
            SetStone(Resources.Stone-ToPay.Stone);
            SetUranium(Resources.Uranium-ToPay.Uranium);
            SetMetal(Resources.Metal-ToPay.Metal);
            return true;
        }
        return false;
    }
    
    int GetStone(){return Resources.Stone;}
    int GetUranium(){return Resources.Uranium;}
    int GetMetal(){return Resources.Metal;}
    void SetStone(int var){
        sText<int> *text_control = (sText<int>*)GUI->GetElement(GUI->GetWindow(GAMETAB_PANEL), GAMETAB_TEXT_STONE);
        if(text_control)
            text_control->SetVar(var);
        Resources.Stone=var;
    }
    void SetUranium(int var){
        sText<int> *text_control = (sText<int>*)GUI->GetElement(GUI->GetWindow(GAMETAB_PANEL), GAMETAB_TEXT_URANIUM);
        if(text_control)
            text_control->SetVar(var);
        Resources.Uranium=var;
    }
    void SetMetal(int var){
        sText<int> *text_control = (sText<int>*)GUI->GetElement(GUI->GetWindow(GAMETAB_PANEL), GAMETAB_TEXT_METAL);
        if(text_control)
            text_control->SetVar(var);
        Resources.Metal=var;
    }
    
};

extern cLocalPlayer LocalPlayer;



