//
// Created by lindner.allison on 22/02/2021.
//

#ifndef PROJ_ANDROID_KITSCENE_H
#define PROJ_ANDROID_KITSCENE_H

#include "cocos2d.h"
#include "rapidjson/document.h"
#include "network/CCDownloader.h"
#include <algorithm>
#include <fstream>
#include <stdio.h>

class KitScene : public cocos2d::Scene {
private:
    void setupLayout();
    void unzipFiles();
    std::string m_kitName;
    
public:
    static cocos2d::Scene* createScene(std::string p_kitName);
    virtual bool init();
    CREATE_FUNC(KitScene);
    void setupPads();
    
    void menuCallback(cocos2d::Ref* sender);
};


#endif //PROJ_ANDROID_KITSCENE_H
