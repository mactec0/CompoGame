#pragma once
#include <string>
#include <vector>
#include <cstring>
#include <sstream>

enum {
    var_Quit,
    var_ShowFPS,
    var_CameraMode,
    var_DrawObjBounds,
    var_Spawn,
    var_GiveStone,
    var_GiveUranium,
    var_GiveMetal,
};

struct sCVAR {
    sCVAR(int id, std::string name, int iValue) {
        this->id = id;
        this->name = name;
        this->iValue = iValue;
    }
    sCVAR(int id, std::string name, std::string strValue) {
        this->id = id;
        this->name = name;
        this->strValue = strValue;
    }
    int id;
    std::string name;
    int iValue;
    float fValue;
    std::string strValue;
};

class CVARManger {
    std::vector<sCVAR> cvars;
public:
    CVARManger() {
        AddVar(sCVAR(var_Quit,"quit",0));
        AddVar(sCVAR(var_ShowFPS, "showfps", 0));
        AddVar(sCVAR(var_CameraMode, "cameramode", 0));
        AddVar(sCVAR(var_DrawObjBounds, "drawobjbounds", 0));
        AddVar(sCVAR(var_Spawn, "spawn", 0));
        
        AddVar(sCVAR(var_GiveStone, "givestone", 0));
        AddVar(sCVAR(var_GiveUranium, "giveuranium", 0));
        AddVar(sCVAR(var_GiveMetal, "givemetal", 0));
    }
    
    void AddVar(sCVAR var) {
        cvars.push_back(var);
    }
    
    int iGetValue(int i) {
        return cvars[i].iValue;
    }
    
    bool SetValue(std::string cmd, std::string value) {
        for (int i = 0; i < cvars.size(); i++) {
            if (std::strcmp(cvars[i].name.c_str(), cmd.c_str()) == 0)
            {
                if (value.size() <= 0) {
                    iSetValue(cvars[i].id, 1);
                }
                else {
                    iSetValue(cvars[i].id,StrToInt(value));
                }
                return true;
            }
        }
        return false;
    }
    
    int StrToInt(std::string str) {
        std::stringstream ss;
        ss << str;
        int i;
        ss >> i;
        return i;
    }
    float StrToFloat(std::string str) {
        std::stringstream ss;
        ss << str;
        float i;
        ss >> i;
        return i;
    }
    
    void iSetValue(int id, int v) {
        for (int i = 0; i < cvars.size(); i++) 
            if(cvars[i].id==id)
                cvars[i].iValue=v;
    }
};

extern CVARManger* CVARS;

/* test prosze nie biÊ */
