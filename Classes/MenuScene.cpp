//
// Created by lindner.allison on 25/02/2021.
//

#include "MenuScene.h"
#include "MenuTableViewCell.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::network;
using namespace rapidjson;

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

    auto menuButton = MenuItemImage::create("x_bg.png", "x_bg.png");
    auto menuLabel = Sprite::create("x.png");
    auto menuSize = menuButton->getContentSize();
    
    auto menuBGColor = LayerColor::create(Color4B(47, 56, 59, 255), visibleSize.width, menuSize.height + 60);
    menuBGColor->setContentSize(Size(visibleSize.width, menuSize.height + 60));
    menuBGColor->setPosition(Vec2(origin.x, visibleSize.height - menuSize.height - 60));

    menuLabel->setAnchorPoint(Vec2(0.5, 0.5));
    menuLabel->setPosition(menuSize.width/2.0f, menuSize.height/2.0f);
    menuLabel->setContentSize(Size(38, 38));
    
    menuButton->setAnchorPoint(Vec2(0, 0.5));
    menuButton->setPosition(10, menuBGColor->getContentSize().height/2);
    menuButton->addChild(menuLabel);
    
    menuBGColor->addChild(menuButton);

    m_menuTableView = TableView::create(this, Size(visibleSize.width, visibleSize.height - menuBGColor->getContentSize().height - origin.y));
    m_menuTableView->setDirection(ScrollView::Direction::VERTICAL);
    m_menuTableView->setAnchorPoint(Vec2::ZERO);
    m_menuTableView->setPosition(origin);
    m_menuTableView->setDelegate(this);
    m_menuTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);

    this->addChild(layerColor);
    this->addChild(menuBGColor);
    this->addChild(m_menuTableView);
    m_menuTableView->reloadData();
    
    requestKits();

    return true;
}

void MenuScene::tableCellTouched(TableView *table, TableViewCell *cell) {
    
}

Size MenuScene::tableCellSizeForIndex(TableView *table, ssize_t idx) {
    auto width = Director::getInstance()->getWinSize().width;
    
    if(idx == 0) {
        return Size(width, 260);
    }
    
    return Size(width, 210);
}

TableViewCell* MenuScene::tableCellAtIndex(TableView *table, ssize_t idx) {
    auto string = StringUtils::format("%ld", static_cast<long>(idx));
    TableViewCell* cell = table->dequeueCell();
    
    if(!cell) {
        cell = new (std::nothrow) MenuTableViewCell();
        cell->autorelease();
        
        ((MenuTableViewCell*) cell)->setup(m_kitsMap[idx]["name"], m_kitsMap[idx]["musicName"], m_kitsMap[idx]["authorName"]);
    } else {
        ((MenuTableViewCell*) cell)->update(m_kitsMap[idx]["name"], m_kitsMap[idx]["musicName"], m_kitsMap[idx]["authorName"]);
    }
    
    return cell;
}

ssize_t MenuScene::numberOfCellsInTableView(TableView *table) {
    return m_kitsMap.size();
}

// REQUEST KITS
void MenuScene::requestKits() {
    HttpRequest* request = new (std::nothrow) HttpRequest();
    request->setUrl("https://api.superpads.opalastudios.com/api/fetch?version=7");
    request->setRequestType(HttpRequest::Type::GET);
    request->setResponseCallback(CC_CALLBACK_2(MenuScene::onHttpRequestCompleted, this));
    request->setTag("GET test1");
    HttpClient::getInstance()->send(request);
    request->release();
}

// REQUEST

void MenuScene::onHttpRequestCompleted(HttpClient *sender, HttpResponse *response)
{
    if (!response)
    {
        return;
    }
    
    // You can get original request type from: response->request->reqType
    if (0 != strlen(response->getHttpRequest()->getTag()))
    {
        log("%s completed", response->getHttpRequest()->getTag());
    }
    
    long statusCode = response->getResponseCode();
    char statusString[64] = {};
    sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
    log("response code: %ld", statusCode);
    
    if (!response->isSucceed())
    {
        log("response failed");
        log("error buffer: %s", response->getErrorBuffer());
        return;
    }
    
    // dump data
    std::vector<char> *buffer = response->getResponseData();
    std::string dataString = std::string(buffer->begin(), buffer->end());
    log("Http Test, dump data: ");
    log("%s", dataString.c_str());
    log("\n");
    if (response->getHttpRequest()->getReferenceCount() != 2)
    {
        log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
    }
    log("\n");
    log("\n");
    
    Document d;
    d.Parse(dataString.c_str());
    
    rapidjson::Value kits = d["kits"].GetArray();
    
    for(rapidjson::Value::ConstValueIterator itr = kits.Begin(); itr != kits.End(); itr++) {
        auto obj = itr->GetObject();
        log("Name: %s - Music: %s - Author: %s", obj["name"].GetString(), obj["musicName"].GetString(), obj["authorName"].GetString());
        
        std::map<std::string, std::string> objMap;
        objMap["name"] = obj["name"].GetString();
        objMap["musicName"] = obj["musicName"].GetString();
        objMap["authorName"] = obj["authorName"].GetString();
        
        m_kitsMap.push_back(objMap);
    }
    
    m_menuTableView->reloadData();
}
