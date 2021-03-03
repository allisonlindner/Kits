//
// Created by lindner.allison on 25/02/2021.
//

#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H

#include "cocos2d.h"
#include <string.h>
#include <stdio.h>

class MenuScene : public cocos2d::Scene {
private:
    static cocos2d::ui::Widget* createMenuItem(const std::string& p_name, const std::string& p_musicName, const std::string& p_artistName);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(MenuScene);
};


#endif //PROJ_ANDROID_MENUSCENE_H
