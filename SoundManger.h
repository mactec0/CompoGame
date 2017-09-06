#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <cstdlib>
#include <vector>

#ifdef __APPLE__
#include "ResourcePath.hpp"
#endif

enum{
    SOUND_LAND,
    SOUND_BUTTONSELECT,
    SOUND_BUTTONCLICK,
    SOUND_WRONG,
    SOUND_MINE,
    SOUND_HAMMER_HIT,
    SOUND_ORE_DESTROYED,
    SOUND_LASER_SHOOT,
    
    SOUND_PLAYER_HIT1,
    SOUND_PLAYER_HIT2,
    SOUND_PLAYER_HIT3,
    SOUND_PLAYER_HIT4,
    SOUND_PLAYER_HIT5,
    SOUND_PLAYER_DIE,
    
    SOUND_MONSTER1,
    SOUND_MONSTER2,
    SOUND_MONSTER3,
    SOUND_MONSTER4,
    SOUND_MONSTER_HIT,
    SOUND_MONSTER_DIE,
    
    SOUND_PUNCH1,
    SOUND_PUNCH2,
    SOUND_PUNCH3,
    SOUND_PUNCH4,
    SOUND_PUNCH5,
    
    SOUND_SPIN,
    
    SOUND_TRANSITION,
    SOUND_WIN,
    SOUND_GAMEOVER,
    
    SOUND_MAXNUM,
};

 
class cSoundManger{
    sf::SoundBuffer soundBuffers[SOUND_MAXNUM];
    std::vector<sf::Sound*> vSounds;
    int Volume;
public:
    bool Enabled;
    cSoundManger();
    ~cSoundManger();
    
    bool LoadSound(std::string fname, int ID);
    
    void PlaySound(int ID);
    
    void SetVolume(int value);
    
    void CleanUP();
};

extern cSoundManger *SoundManger;
