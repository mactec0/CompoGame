#include "Utils.h"
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>

sf::Vector2f Ang2Vec(float Ang){
    return sf::Vector2f(cos(Ang*(M_PI/180))*1.f,sin(Ang*(M_PI/180))*1.f);
}
