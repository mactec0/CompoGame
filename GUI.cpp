#include "GUI.h"
#include <stdio.h>

 void sButton::Control(sMouseState &state){
    for(auto child:children)
        child->Control(state);
    
    if(state.bLeftClicked&&!state.bLeftLast&&state.ID==-1){
        //catch
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            state.ID=ID;
            BoxRenderState=CONTROL_STATE::PUSHED;
            GUI->AddEvent(sGuiEvent(ID,PUSHED));
        }
        
    }else if(state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            BoxRenderState=CONTROL_STATE::PUSHED;
        }else{
            BoxRenderState=CONTROL_STATE::NORMAL;
        }
        
    }else if(!state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        state.ID=-1;
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            SoundManger->PlaySound(SOUND_BUTTONCLICK);
            GUI->AddEvent(sGuiEvent(ID,CLICKED));
        }
    }
    
    if(state.ID==-1){
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            if(BoxRenderState!=CONTROL_STATE::HOVER)
                SoundManger->PlaySound(SOUND_BUTTONSELECT);
            BoxRenderState=CONTROL_STATE::HOVER;
        }else{
            BoxRenderState=CONTROL_STATE::NORMAL;
        }
        
    }
    
}

void sCheckBox::Control(sMouseState &state){
    for(auto child:children)
        child->Control(state);
    
    if(state.bLeftClicked&&!state.bLeftLast&&state.ID==-1){
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            state.ID=ID;
            BoxRenderState=CONTROL_STATE::CHECKED;
        }
        
    }else if(state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            BoxRenderState=CONTROL_STATE::CHECKED;
        }else{
            BoxRenderState=CONTROL_STATE::NORMAL;
        }
        
    }else if(!state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        //restore
        state.ID=-1;
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            Checked=!Checked;
            
            GUI->AddEvent(sGuiEvent(ID,CHECKED,Checked));
            
        }
    }
    
    if(state.ID==-1){
        BoxRenderState=Checked?CONTROL_STATE::CHECKED:CONTROL_STATE::NORMAL;
    }
    
}

void sListBox::Control(sMouseState &state){
    for(auto child:children)
        child->Control(state);
    
    if(state.bLeftClicked&&!state.bLeftLast&&state.ID==-1){
        //catch
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            state.ID=ID;
            BoxRenderState=CONTROL_STATE::PUSHED;
            HoverID=-1;
        }
        
    }else if(state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            BoxRenderState=CONTROL_STATE::PUSHED;
        }else{
            BoxRenderState=CONTROL_STATE::NORMAL;
        }
        
    }else if(!state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            BoxRenderState=CONTROL_STATE::OPENED;
            SoundManger->PlaySound(SOUND_BUTTONSELECT);
        }else{
            state.ID=-1;
            BoxRenderState=CONTROL_STATE::NORMAL;
            
        }
    }
    
    if(BoxRenderState==CONTROL_STATE::OPENED){
        sf::Vector2i StartPos=sf::Vector2i(GetPos().x,GetPos().y+Size.y);
        bool bHovered=false;
        for(int i=0;i<ListSize;i++){
            if(state.Pos.x>=StartPos.x&&state.Pos.x<StartPos.x+Size.x&&
               state.Pos.y>=StartPos.y+i*Size.y&&state.Pos.y<StartPos.y+Size.y+i*Size.y)
            {
                HoverID=i;
                bHovered=true;
            }
            if(!bHovered)
                HoverID=-1;
        }
        if(state.bLeftClicked){
            if(bHovered)
                CurrentID=HoverID;
            HoverID=-1;
            state.ID=-1;
            BoxRenderState=NORMAL;
            GUI->AddEvent(sGuiEvent(ID,CHANGED,CurrentID));
        }
    }
}


void sSlider::Control(sMouseState &state){
    for(auto child:children)
        child->Control(state);
    
    if(state.bLeftClicked&&!state.bLeftLast&&state.ID==-1){
        //catch
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
            state.ID=ID;
        }
        
    }else if(state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        if(state.Pos.x<GetPos().x)
            state.Pos.x=GetPos().x;
        
        if(state.Pos.x>GetPos().x+Length)
            state.Pos.x=GetPos().x+Length;
        
        int AbsPos=abs(GetPos().x-state.Pos.x);
        Value =((float)AbsPos/(float)Length)*Max;
        
        ButtonPos=state.Pos.x-GetPos().x;
        
    }else if(!state.bLeftClicked&&state.bLeftLast&&state.ID==ID){
        //restore
        state.ID=-1;
        if(state.Pos.x>=GetPos().x&&state.Pos.x<GetPos().x+Size.x&&
           state.Pos.y>=GetPos().y&&state.Pos.y<GetPos().y+Size.y)
        {
        }
        
        
        GUI->AddEvent(sGuiEvent(ID,CHANGED,abs(Value)));
    }
    
    
}





