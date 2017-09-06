#pragma once
#include <string>
#include "Globals.h"
#include <SFML/Graphics.hpp>
#include <sstream>

enum {
    KEY_Unknown = -1,
    KEY_A = 0,
    KEY_B,
    KEY_C,
    KEY_D,
    KEY_E,
    KEY_F,
    KEY_G,
    KEY_H,
    KEY_I,
    KEY_J,
    KEY_K,
    KEY_L,
    KEY_M,
    KEY_N,
    KEY_O,
    KEY_P,
    KEY_Q,
    KEY_R,
    KEY_S,
    KEY_T,
    KEY_U,
    KEY_V,
    KEY_W,
    KEY_X,
    KEY_Y,
    KEY_Z,
    KEY_Num0,
    KEY_Num1,
    KEY_Num2,
    KEY_Num3,
    KEY_Num4,
    KEY_Num5,
    KEY_Num6,
    KEY_Num7,
    KEY_Num8,
    KEY_Num9,
    KEY_Escape,
    KEY_LControl,
    KEY_LShift,
    KEY_LAlt,
    KEY_LSystem,
    KEY_RControl,
    KEY_RShift,
    KEY_RAlt,
    KEY_RSystem,
    KEY_Menu,
    KEY_LBracket,
    KEY_RBracket,
    KEY_SemiColon,
    KEY_Comma,
    KEY_Period,
    KEY_Quote,
    KEY_Slash,
    KEY_BackSlash,
    KEY_Tilde,
    KEY_Equal,
    KEY_Dash,
    KEY_Space,
    KEY_Return,
    KEY_BackSpace,
    KEY_Tab,
    KEY_PageUp,
    KEY_PageDown,
    KEY_End,
    KEY_Home,
    KEY_Insert,
    KEY_Delete,
    KEY_Add,
    KEY_Subtract,
    KEY_Multiply,
    KEY_Divide,
    KEY_Left,
    KEY_Right,
    KEY_Up,
    KEY_Down,
    KEY_Numpad0,
    KEY_Numpad1,
    KEY_Numpad2,
    KEY_Numpad3,
    KEY_Numpad4,
    KEY_Numpad5,
    KEY_Numpad6,
    KEY_Numpad7,
    KEY_Numpad8,
    KEY_Numpad9,
    KEY_F1,
    KEY_F2,
    KEY_F3,
    KEY_F4,
    KEY_F5,
    KEY_F6,
    KEY_F7,
    KEY_F8,
    KEY_F9,
    KEY_F10,
    KEY_F11,
    KEY_F12,
    KEY_F13,
    KEY_F14,
    KEY_F15,
    KEY_Pause,
    KEY_KeyCount,
    KEY_MAX
};


class cKeyManger {
    bool bisClicked[KEY_MAX];
    std::string szCharacters;
    std::string HugeCharacters;
public:
    cKeyManger() {
        for (int i = 0; i < KEY_MAX; i++){
            bisClicked[i] = false;
        }
        
        szCharacters = "abcdefghijklmnopqrstuvwxyz0123456789``````````[];,.\"/\\~=-   ";
        HugeCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ  ";
    }
    
    void Reset() {
        for (int i = 0; i < KEY_MAX; i++){
            bisClicked[i] = false;
        }
    }

    void SetValue(int i, bool v) {
        bisClicked[i] = v;
    }

    char GetKey(int i) {
        if (i<0 || i>szCharacters.length())
            return '?';
        return szCharacters[i];
    }
    char GetKeyHuge(int i) {
        if (i<0 || i>HugeCharacters.length())
            return '?';
        return HugeCharacters[i];
    }
    
    bool Clicked(int i) { 
        return bisClicked[i];
    }
    
};

extern cKeyManger* KeyManger;
