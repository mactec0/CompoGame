#include "SoundManger.h"


cSoundManger::cSoundManger(){
#ifdef __APPLE__
    if (!LoadSound(resourcePath()+ "sfx/jumpland.wav", SOUND_LAND))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/Menu Selection Click.wav", SOUND_BUTTONSELECT))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/click.wav", SOUND_BUTTONCLICK))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/wrong.wav", SOUND_WRONG))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/mine.wav", SOUND_MINE))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/HammerHit.wav", SOUND_HAMMER_HIT))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/OreDestroyed.wav", SOUND_ORE_DESTROYED))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/LaserShoot.wav", SOUND_LASER_SHOOT))
        exit(0);
    
    if (!LoadSound(resourcePath()+ "sfx/monster1.wav", SOUND_MONSTER1))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/monster2.wav", SOUND_MONSTER2))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/monster3.wav", SOUND_MONSTER3))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/monster4.wav", SOUND_MONSTER4))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/monsterHIT.wav", SOUND_MONSTER_HIT))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/monsterDIE.wav", SOUND_MONSTER_DIE))
        exit(0);
    
    if (!LoadSound(resourcePath()+ "sfx/hit1.ogg", SOUND_PLAYER_HIT1))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/hit2.ogg", SOUND_PLAYER_HIT2))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/hit3.ogg", SOUND_PLAYER_HIT3))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/hit4.ogg", SOUND_PLAYER_HIT4))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/hit5.ogg", SOUND_PLAYER_HIT5))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/die1.ogg", SOUND_PLAYER_DIE))
        exit(0);
    
    
    if (!LoadSound(resourcePath()+ "sfx/punch1.ogg", SOUND_PUNCH1))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/punch2.ogg", SOUND_PUNCH2))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/punch3.ogg", SOUND_PUNCH3))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/punch4.ogg", SOUND_PUNCH4))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/punch5.ogg", SOUND_PUNCH5))
        exit(0);
    
    
    if (!LoadSound(resourcePath()+ "sfx/transition.wav", SOUND_TRANSITION))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/win.wav", SOUND_WIN))
        exit(0);
    if (!LoadSound(resourcePath()+ "sfx/game_over.wav", SOUND_GAMEOVER))
        exit(0);
    
    if (!LoadSound(resourcePath()+ "sfx/spin.wav", SOUND_SPIN))
        exit(0);
#else

	if (!LoadSound("sfx/jumpland.wav", SOUND_LAND))
		exit(0);
	if (!LoadSound("sfx/Menu Selection Click.wav", SOUND_BUTTONSELECT))
		exit(0);
	if (!LoadSound("sfx/click.wav", SOUND_BUTTONCLICK))
		exit(0);
	if (!LoadSound("sfx/wrong.wav", SOUND_WRONG))
		exit(0);
	if (!LoadSound("sfx/mine.wav", SOUND_MINE))
		exit(0);
	if (!LoadSound("sfx/HammerHit.wav", SOUND_HAMMER_HIT))
		exit(0);
	if (!LoadSound("sfx/OreDestroyed.wav", SOUND_ORE_DESTROYED))
		exit(0);
	if (!LoadSound("sfx/LaserShoot.wav", SOUND_LASER_SHOOT))
		exit(0);

	if (!LoadSound("sfx/monster1.wav", SOUND_MONSTER1))
		exit(0);
	if (!LoadSound("sfx/monster2.wav", SOUND_MONSTER2))
		exit(0);
	if (!LoadSound("sfx/monster3.wav", SOUND_MONSTER3))
		exit(0);
	if (!LoadSound("sfx/monster4.wav", SOUND_MONSTER4))
		exit(0);
	if (!LoadSound("sfx/monsterHIT.wav", SOUND_MONSTER_HIT))
		exit(0);
	if (!LoadSound("sfx/monsterDIE.wav", SOUND_MONSTER_DIE))
		exit(0);

	if (!LoadSound("sfx/hit1.ogg", SOUND_PLAYER_HIT1))
		exit(0);
	if (!LoadSound("sfx/hit2.ogg", SOUND_PLAYER_HIT2))
		exit(0);
	if (!LoadSound("sfx/hit3.ogg", SOUND_PLAYER_HIT3))
		exit(0);
	if (!LoadSound("sfx/hit4.ogg", SOUND_PLAYER_HIT4))
		exit(0);
	if (!LoadSound("sfx/hit5.ogg", SOUND_PLAYER_HIT5))
		exit(0);
	if (!LoadSound("sfx/die1.ogg", SOUND_PLAYER_DIE))
		exit(0);


	if (!LoadSound("sfx/punch1.ogg", SOUND_PUNCH1))
		exit(0);
	if (!LoadSound("sfx/punch2.ogg", SOUND_PUNCH2))
		exit(0);
	if (!LoadSound("sfx/punch3.ogg", SOUND_PUNCH3))
		exit(0);
	if (!LoadSound("sfx/punch4.ogg", SOUND_PUNCH4))
		exit(0);
	if (!LoadSound("sfx/punch5.ogg", SOUND_PUNCH5))
		exit(0);

    
    
    if (!LoadSound("sfx/transition.wav", SOUND_TRANSITION))
        exit(0);
    if (!LoadSound("sfx/win.wav", SOUND_WIN))
        exit(0);
    if (!LoadSound("sfx/game_over.wav", SOUND_GAMEOVER))
        exit(0);
    
	if (!LoadSound("sfx/spin.wav", SOUND_SPIN))
		exit(0);
    
#endif

    Volume=100;
    Enabled=true;
}

bool cSoundManger::LoadSound(std::string fname, int ID){
    if (!soundBuffers[ID].loadFromFile(fname)){
        std::cout<<"[ERROR] cannot load "<<fname<<"\n";
        return false;
    }
    
    std::cout<<"[INFO] "<<fname<<" loaded\n";
    return true;
}


void cSoundManger::PlaySound(int ID){
    if(!Enabled)
        return;
    
    vSounds.erase(std::remove_if(vSounds.begin(), vSounds.end(),
                                 [](const sf::Sound* i){
                                     if(i->getStatus()==sf::SoundSource::Status::Stopped){
                                         delete i;
                                         return true;
                                     }
                                     return false;
                                 }),vSounds.end());
    
    vSounds.push_back(new sf::Sound(soundBuffers[ID]));
    vSounds.back()->play();

}




void cSoundManger::SetVolume(int value){
    Volume=value;
}

void cSoundManger::CleanUP(){
    vSounds.clear();
}

cSoundManger::~cSoundManger(){
    
}

