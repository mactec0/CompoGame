#pragma once
#include <sstream>
#include <string>
#include <cmath>
#include <stdint.h>
#include <SFML/Graphics.hpp>

template <typename T>
inline T GetFromSTR(std::string str){
    std::stringstream ss(str);
    T ret;
    ss>>ret;
    return ret;
}

template <typename T>
inline std::string ToStr(T str) {
	std::stringstream ss;
	std::string ret;
	ss << str;
	ss >> ret;
	return ret;
}

template <typename T>
float Length2D(sf::Vector2<T> vec){
    return sqrt(vec.x*vec.x+vec.y*vec.y);
}

template <typename T1,typename T2>
sf::Vector2<T2> Vec2Vec(sf::Vector2<T1> vec){
    return sf::Vector2<T2>((T2)vec.x,(T2)vec.y);
}

sf::Vector2f Ang2Vec(float Ang);
