//
// Created by lindner.allison on 23/02/2021.
//

#ifndef PROJ_ANDROID_PADTILE_H
#define PROJ_ANDROID_PADTILE_H

#include "cocos2d.h"

enum class PadType { Blue, Green, Orange, Pink };

class PadTile : public cocos2d::Node {
private:
    PadType m_type;
    void setupPad();
public:
    CREATE_FUNC(PadTile);
    virtual bool init();

    static PadTile* createWithType(PadType p_type, float p_width, float p_height);
};


#endif //PROJ_ANDROID_PADTILE_H
