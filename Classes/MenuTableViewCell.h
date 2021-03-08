//
//  MenuTableViewCell.h
//  Kits-mobile
//
//  Created by Opala Teste on 04/03/21.
//

#ifndef __MENU_TABLEVIEWCELL_H__
#define __MENU_TABLEVIEWCELL_H__

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include <stdio.h>

class MenuTableViewCell : public cocos2d::extension::TableViewCell {
private:
    cocos2d::Label* m_kitLabel;
    cocos2d::Label* m_musicLabel;
    cocos2d::Label* m_artistsLabel;
    
public:
    std::string kitName;
    
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    void setup(const std::string& p_name, const std::string& p_musicName, const std::string& p_artistName);
    void update(const std::string& p_name, const std::string& p_musicName, const std::string& p_artistName);
};

#endif /* __MENU_TABLEVIEWCELL_H__ */
