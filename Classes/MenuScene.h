//
// Created by lindner.allison on 25/02/2021.
//

#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H

#include "cocos2d.h"

class MenuScene : public cocos2d::Scene {
private:
    cocos2d::MenuItem* createMenuItem(const char* p_name, const char* p_musicName, const char* p_artistName);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MenuScene);
};


#endif //PROJ_ANDROID_MENUSCENE_H
