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
    MUSIC_MENU,
    MUSIC_GAME,
    MUSIC_MAX,
};

class cMusicPlayer{
    bool Enabled;
    sf::Music vMusic[MUSIC_MAX];
public:
    cMusicPlayer();
    ~cMusicPlayer();
    
    bool Load(std::string fname, int ID);
    void StopAll();
    void Play(int ID);
    void SetVolume(int value);
    void SetEnable(bool val);
};

extern cMusicPlayer *MusicPlayer;
