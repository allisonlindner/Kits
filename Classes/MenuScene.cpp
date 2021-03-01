//
// Created by lindner.allison on 25/02/2021.
//

#include "MenuScene.h"

USING_NS_CC;

cocos2d::Scene *MenuScene::createScene() {
    return MenuScene::create();
}

bool MenuScene::init() {
    if(!Scene::init()) {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Background Color
    auto layerColor = LayerColor::create(Color4B(36, 43, 46, 255), visibleSize.width, visibleSize.height);
    layerColor->setPosition(origin);

    // Open Menu Button
    auto menuButton = MenuItemImage::create("x_bg.png", "x_bg.png");
    auto menuLabel = Sprite::create("x.png");
    auto menuSize = menuButton->getContentSize();
    menuLabel->setAnchorPoint(Vec2(0.5, 0.5));
    menuLabel->setPosition(menuSize.width/2.0f, (menuSize.height/2.0f) + 5);
    menuLabel->setContentSize(Size(38, 38));
    menuButton->setPosition((menuSize.width / 2.0f) + 10, visibleSize.height - (menuSize.height / 2.0f) - 40);
    menuButton->addChild(menuLabel);

    // Menu BG
    auto menuBGColor = LayerColor::create(Color4B(47, 56, 59, 255), visibleSize.width, menuSize.height + 60);
    menuBGColor->setPosition(Vec2(0, visibleSize.height - menuSize.height - 60));

    // Menu

    auto menu = Menu::create();
    menu->addChild(createMenuItem("TESTE", "TESTE", "TESTE"));

    this->addChild(layerColor);
    this->addChild(menuBGColor);
    this->addChild(menuButton);
    this->addChild(menu);

    return true;
}

cocos2d::MenuItem* MenuScene::createMenuItem(const char *p_name, const char *p_musicName, const char *p_artistName) {
    auto visibleSize = Director::getInstance()->getVisibleSize();

    auto menuItem = MenuItem::create();
    auto menuBG = Sprite::create("kit_menu_bg.png");
    menuBG->setContentSize(Size(visibleSize.width - 80, 229));

    auto menuNameBG = Sprite::create("kit_menu_name_bg.png");
    menuNameBG->setAnchorPoint(Vec2(0, 0.5));
    menuNameBG->setPosition(20, 114.5f);
    menuNameBG->setContentSize(Size(189, 189));
    menuBG->addChild(menuNameBG);

    auto kitLabel = Label::createWithTTF("KIT\nNOME", "fonts/PTSansProBlk.OTF", 40, Size::ZERO, TextHAlignment::CENTER);
    kitLabel->setAnchorPoint(Vec2(0.5, 0.5));
    kitLabel->setPosition(94.5, 94.5);
    menuNameBG->addChild(kitLabel);

    auto kitArrow = Sprite::create("kit_menu_arrow.png");
    kitArrow->setContentSize(Size(67, 67));
    kitArrow->setAnchorPoint(Vec2(1, 0));
    kitArrow->setPosition(menuBG->getContentSize().width, 0);
    menuBG->addChild(kitArrow);

    menuItem->addChild(menuBG);

    return menuItem;
}
