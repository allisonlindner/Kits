//
//  MenuTableViewCell.cpp
//  Kits-mobile
//
//  Created by Opala Teste on 04/03/21.
//

#include "MenuTableViewCell.h"

USING_NS_CC;
using namespace cocos2d::ui;

void MenuTableViewCell::draw(Renderer *renderer, const Mat4 &transform, uint32_t flags)
{
    TableViewCell::draw(renderer, transform, flags);
}

void MenuTableViewCell::setup(const std::string &p_name, const std::string &p_musicName, const std::string &p_artistName) {
    auto menuItem = Widget::create();
    auto menuBG = Sprite::create("kit_menu_bg.png");
    menuBG->setAnchorPoint(Vec2(0.5, 0.0));
    menuBG->setPosition(Vec2(this->getContentSize().width/2.0f, 0.0f));
    menuBG->setContentSize(Size(this->getContentSize().width, 210));

    auto menuNameBG = Sprite::create("kit_menu_name_bg.png");
    menuNameBG->setAnchorPoint(Vec2(0, 0.5));
    menuNameBG->setPosition(20, 114.5f);
    menuNameBG->setContentSize(Size(189, 189));
    menuBG->addChild(menuNameBG);

    m_kitLabel = Label::createWithTTF("KIT\n" + p_name, "fonts/PTSansProBlk.OTF", 40, Size::ZERO, TextHAlignment::CENTER);
    m_kitLabel->setAnchorPoint(Vec2(0.5, 0.5));
    m_kitLabel->setPosition(94.5, 94.5);
    menuNameBG->addChild(m_kitLabel);

    auto kitArrow = Sprite::create("kit_menu_arrow.png");
    kitArrow->setContentSize(Size(67, 67));
    kitArrow->setAnchorPoint(Vec2(1, 0));
    kitArrow->setPosition(menuBG->getContentSize().width, 0);
    menuBG->addChild(kitArrow);

    // Labels
    auto inspiredByLabel = Label::createWithTTF("INSPIRADO EM", "fonts/PTSansProLight.OTF", 25, Size::ZERO, TextHAlignment::LEFT);
    auto pinkLine = Sprite::create("pink_line.png");
    m_musicLabel = Label::createWithTTF(p_musicName, "fonts/PTSansProBlk.OTF", 32, Size::ZERO, TextHAlignment::LEFT);
    m_artistsLabel = Label::createWithTTF(p_artistName, "fonts/PTSansProRegular.OTF", 27, Size::ZERO, TextHAlignment::LEFT);
    
    pinkLine->setScale(0.8f);
    pinkLine->setAnchorPoint(Vec2(0, 1));
    inspiredByLabel->setAnchorPoint(Vec2(0, 0));
    pinkLine->setPosition(0, 0);
    inspiredByLabel->addChild(pinkLine);

    inspiredByLabel->setPosition(0, m_musicLabel->getContentSize().height + 15);
    m_musicLabel->addChild(inspiredByLabel);

    m_artistsLabel->setAnchorPoint(Vec2(0, 1));
    m_artistsLabel->setPosition(0, 5);
    m_musicLabel->addChild(m_artistsLabel);

    m_musicLabel->setAnchorPoint(Vec2(0, 0.5));
    m_musicLabel->setPosition(menuNameBG->getContentSize().width + 30, menuNameBG->getContentSize().height/2.0f);
    menuNameBG->addChild(m_musicLabel);

    menuItem->addChild(menuBG);
    this->addChild(menuItem);
}

void MenuTableViewCell::update(const std::string& p_name, const std::string& p_musicName, const std::string& p_artistName) {
    m_kitLabel->setString("KIT\n" + p_name);
    m_musicLabel->setString(p_musicName);
    m_artistsLabel->setString(p_artistName);
}
