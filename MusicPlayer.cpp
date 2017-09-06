#include "MusicPlayer.h"


cMusicPlayer::cMusicPlayer(){
#ifdef __APPLE__
    if (!Load(resourcePath()+ "music/nebula.ogg", MUSIC_MENU))
        exit(0);
    if (!Load(resourcePath()+ "music/dark fallout.ogg", MUSIC_GAME))
        exit(0);
    
#else
	if (!Load("music/nebula.ogg", MUSIC_MENU))
		exit(0);
	if (!Load("music/dark fallout.ogg", MUSIC_GAME))
		exit(0);
    
#endif
    Enabled=true;
}

bool cMusicPlayer::Load(std::string fname, int ID){
    if (!vMusic[ID].openFromFile(fname)){
        std::cout<<"[ERROR] cannot load "<<fname<<"\n";
        return false;
    }
    std::cout<<"[INFO] "<<fname<<" loaded\n";
    return true;
}

void cMusicPlayer::StopAll(){
    for(int i =0;i<MUSIC_MAX;i++)
        vMusic[i].stop();
}


void cMusicPlayer::SetVolume(int value){
    for(int i=0;i<MUSIC_MAX;i++)
        vMusic[i].setVolume(value);
}

void cMusicPlayer::SetEnable(bool val){
    Enabled=val;
    if(!val)
        StopAll();
}

void cMusicPlayer::Play(int ID){
    if(Enabled)
    vMusic[ID].play();
}

cMusicPlayer::~cMusicPlayer(){
    
}

