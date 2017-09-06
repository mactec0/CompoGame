#include "FontManger.h"


cFontManger::cFontManger(){
#ifdef __APPLE__
    if (!LoadFont(resourcePath()+"font/VCR_OSD_MONO_1.001.ttf", FONT_MAIN))
        exit(0);
    if (!LoadFont(resourcePath()+ "font/VCR_OSD_MONO_1.001.ttf", FONT_CONSOLE))//"font/visitor2.ttf"
        exit(0); 
#else

	if (!LoadFont("gfx/font/VCR_OSD_MONO_1.001.ttf", FONT_MAIN))
		exit(0);
	if (!LoadFont("gfx/font/VCR_OSD_MONO_1.001.ttf", FONT_CONSOLE))
		exit(0);
#endif
}

cFontManger::~cFontManger(){
    
}


bool cFontManger::LoadFont(std::string fname, int ID){
    if (!fonts[ID].loadFromFile(fname)){
        std::cout<<"[ERROR] cannot load "<<fname<<"\n";
        return false;
    }
    
    std::cout<<"[INFO] "<<fname<<" loaded\n";
    return true;
}

sf::Font *cFontManger::GetFont(int ID){
    return &fonts[ID];
}
