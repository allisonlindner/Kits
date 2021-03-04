//
// Created by lindner.allison on 25/02/2021.
//

#ifndef PROJ_ANDROID_MENUSCENE_H
#define PROJ_ANDROID_MENUSCENE_H

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "rapidjson/document.h"
#include <string.h>
#include <stdio.h>
#include <map>
#include <vector>

class MenuScene : public cocos2d::Scene, public cocos2d::extension::TableViewDataSource, public cocos2d::extension::TableViewDelegate {
private:
    std::vector<std::map<std::string, std::string>> m_kitsMap;
    cocos2d::extension::TableView* m_menuTableView;
    
    void requestKits();
public:
    CREATE_FUNC(MenuScene);
    virtual bool init() override;
    
    static cocos2d::Scene* createScene();

    // DataSource and Delegate
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view) override {};
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view) override {}
    virtual void tableCellTouched(cocos2d::extension::TableView *table, cocos2d::extension::TableViewCell *cell) override;
    virtual cocos2d::Size tableCellSizeForIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
    virtual cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx) override;
    virtual ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table) override;
    
    // REQUEST
    void onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response);
};


#endif //PROJ_ANDROID_MENUSCENE_H
