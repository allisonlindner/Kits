//
// Created by lindner.allison on 23/02/2021.
//

#include "PadTile.h"

USING_NS_CC;

bool PadTile::init() {
    return Node::init();
}

PadTile *PadTile::createWithType(PadType p_type, float p_width, float p_height) {
    auto pad = PadTile::create();
    pad->m_type = p_type;
    pad->setContentSize(Size(p_width, p_height));
    pad->setupPad();

    return pad;
}

void PadTile::setupPad() {
    const char* padFileName;
    switch (m_type) {
        case PadType::Blue:
            padFileName = "pad_blue.png";
            break;
        case PadType::Green:
            padFileName = "pad_green.png";
            break;
        case PadType::Orange:
            padFileName = "pad_orange.png";
            break;
        case PadType::Pink:
            padFileName = "pad_pink.png";
            break;
    }

    auto sprite = Sprite::create(padFileName);
    sprite->setContentSize(getContentSize());

    auto pad = MenuItemSprite::create(sprite, sprite);
    pad->setAnchorPoint(Vec2(0.5f,0.5f));
    pad->setPosition(0,0);

    this->addChild(pad);
}
