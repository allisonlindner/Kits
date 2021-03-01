//
// Created by lindner.allison on 22/02/2021.
//

#ifndef PROJ_ANDROID_KITSCENE_H
#define PROJ_ANDROID_KITSCENE_H

#include "cocos2d.h"

class KitScene : public cocos2d::Scene {
private:
    void setupPads();
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(KitScene);
};


#endif //PROJ_ANDROID_KITSCENE_H
