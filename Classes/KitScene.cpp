//
// Created by lindner.allison on 22/02/2021.
//

#include "KitScene.h"
#include "PadTile.h"

USING_NS_CC;

cocos2d::Scene *KitScene::createScene() {
    return KitScene::create();
}

bool KitScene::init() {
    if(!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Background Color
    auto layerColor = LayerColor::create(Color4B(36, 43, 46, 255), visibleSize.width, visibleSize.height);
    layerColor->setPosition(origin);

    // Open Menu Button
    auto menu = MenuItemImage::create("x_bg.png", "x_bg.png");
    auto menuLabel = Label::createWithTTF("MENU", "fonts/PTSansProBlk.OTF", 40);
    auto menuSize = menu->getContentSize();
    menuLabel->setAnchorPoint(Vec2(0.5, 0.5));
    menuLabel->setPosition(menuSize.width/2.0f, (menuSize.height/2.0f) + 5);
    menu->setPosition((menuSize.width/2.0f) + 10, visibleSize.height - (menuSize.height/2.0f) - 40);
    menu->addChild(menuLabel);

    // Header Line
    auto line = DrawNode::create(2.0f);
    line->drawLine(Vec2(0,visibleSize.height - menuSize.height - 60),
                   Vec2(visibleSize.width,visibleSize.height - menuSize.height - 60),
                   Color4F(0,0,0,1));

    // Kit Name Title
    auto kitLabel = Label::createWithTTF("KIT", "fonts/PTSansProLight.OTF", 40);
    auto kitNameLabel = Label::createWithTTF("NAME", "fonts/PTSansProBlk.OTF", 40);
    kitNameLabel->setAnchorPoint(Vec2(0, 0.5));
    kitNameLabel->setPosition(kitLabel->getContentSize().width + 4, kitLabel->getContentSize().height/2.0f);
    kitLabel->setAnchorPoint(Vec2(0, 0.5));
    kitLabel->setPosition(menuSize.width + 30, visibleSize.height - (menuSize.height/2.0f) - 40);
    kitLabel->addChild(kitNameLabel);

    this->addChild(layerColor);
    this->addChild(menu);
    this->addChild(kitLabel);
    this->addChild(line);

    setupPads();

    return true;
}

void KitScene::setupPads() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto padWH = (visibleSize.width - 60.0f)/3.0f;

    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            auto pad = PadTile::createWithType(PadType::Blue, padWH, padWH);
            pad->setPosition(((float)i * padWH) + 20.0f + ((float)i * 10.0f) + (padWH/2.0f),
                            visibleSize.height - 150.0f - ((1.0f + (float)j) * padWH) - ((float)j * 10.0f));

            this->addChild(pad);
        }
    }
}
