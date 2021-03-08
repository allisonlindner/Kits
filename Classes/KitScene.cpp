//
// Created by lindner.allison on 22/02/2021.
//

#include "KitScene.h"
#include "PadTile.h"

USING_NS_CC;
using namespace rapidjson;

cocos2d::Scene *KitScene::createScene(std::string p_kitName) {
    auto scene = KitScene::create();
    scene->m_kitName = p_kitName;
    scene->setupLayout();
    
    return scene;
}

bool KitScene::init() {
    if(!Scene::init()) {
        return false;
    }

    return true;
}
void KitScene::setupLayout() {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    // Background Color
    auto layerColor = LayerColor::create(Color4B(36, 43, 46, 255), visibleSize.width, visibleSize.height);
    layerColor->setPosition(origin);

    // Open Menu Button
    auto xSprite = Sprite::create("x_bg.png");
    auto menu = MenuItemSprite::create(xSprite, xSprite, xSprite,
                                       CC_CALLBACK_1(KitScene::menuCallback, this));
    auto menuLabel = MenuItemLabel::create(Label::createWithTTF("MENU", "fonts/PTSansProBlk.OTF", 40));
    auto menuSize = menu->getContentSize();
    menuLabel->setAnchorPoint(Vec2(0.5, 0.5));
    menuLabel->setPosition(menuSize.width/2.0f, (menuSize.height/2.0f) + 5);
    menu->addChild(menuLabel);
    menu->setAnchorPoint(Vec2(0, 0.5));
    menu->setPosition(origin.x + 10, visibleSize.height - (menuSize.height/2.0f) - 40);
    menu->setContentSize(xSprite->getContentSize());

    // Header Line
    auto line = DrawNode::create(2.0f);
    line->drawLine(Vec2(origin.x, origin.y + visibleSize.height - menuSize.height - 60),
                   Vec2(origin.x + visibleSize.width, origin.y + visibleSize.height - menuSize.height - 60),
                   Color4F(0,0,0,1));

    // Kit Name Title
    auto kitLabel = Label::createWithTTF("KIT", "fonts/PTSansProLight.OTF", 40);
    auto kitNameLabel = Label::createWithTTF(m_kitName, "fonts/PTSansProBlk.OTF", 40);
    kitNameLabel->setAnchorPoint(Vec2(0, 0.5));
    kitNameLabel->setPosition(kitLabel->getContentSize().width + 4, kitLabel->getContentSize().height/2.0f);
    kitLabel->setAnchorPoint(Vec2(0, 0.5));
    kitLabel->setPosition(origin.x + menuSize.width + 30, visibleSize.height - (menuSize.height/2.0f) - 40);
    kitLabel->addChild(kitNameLabel);

    this->addChild(layerColor);
    this->addChild(kitLabel);
    this->addChild(line);
    this->addChild(menu);
    
    network::Downloader* downloader = new network::Downloader();
    
    char path[256];
    char searchPath[256];
    char url[256];
    
    auto name = m_kitName;
    
    std::string tmpName = "";
    for(size_t i = 0; i < name.length(); i++)
    {
        if(name[i] != ' ')
            tmpName += name[i];
        else
            tmpName += "%20";
    }
    
    sprintf(path, "%sKits/%s/Sounds_OGG.zip", FileUtils::getInstance()->getWritablePath().c_str(), m_kitName.c_str());
    sprintf(searchPath, "%sKits/%s", FileUtils::getInstance()->getWritablePath().c_str(), m_kitName.c_str());
    sprintf(url, "https://storage.superpads.opalastudios.com/superpads/%s/Sounds_OGG.zip", tmpName.c_str());
    
    if(!FileUtils::getInstance()->isDirectoryExist(searchPath)) {
        FileUtils::getInstance()->createDirectory(searchPath);
    }
    
    FileUtils::getInstance()->setSearchPaths({searchPath});
    
    if(!FileUtils::getInstance()->isFileExist("Sounds_OGG.zip")) {
        downloader->createDownloadFileTask(url, path);
        
        downloader->onFileTaskSuccess = ([this] (const network::DownloadTask& task) {
            log("downloader task success: %s", task.storagePath.c_str());
            this->unzipFiles();
            this->setupPads();
        });
        
        downloader->onTaskError = ([] (const network::DownloadTask& task, int errorCode, int errorCodeInternal, const std::string& errorStr) {
            log("downloader task failed : %s, identifier(%s) error code(%d), internal error code(%d) desc(%s)"
                , task.requestURL.c_str()
                , task.identifier.c_str()
                , errorCode
                , errorCodeInternal
                , errorStr.c_str());
        });
    } else {
        log("%sKits/%s/Sounds_OGG.zip - Already exists.", FileUtils::getInstance()->getWritablePath().c_str(), m_kitName.c_str());
        this->unzipFiles();
        this->setupPads();
    }
}

void KitScene::menuCallback(Ref *sender) {
    log("PRESSED MENU");
    Director::getInstance()->popScene();
}

void KitScene::unzipFiles() {
    char path[256];
    char unzipPath[256];
    
    sprintf(path, "%sKits/%s/Sounds_OGG.zip", FileUtils::getInstance()->getWritablePath().c_str(), m_kitName.c_str());
    sprintf(unzipPath, "%sKits/%s/data", FileUtils::getInstance()->getWritablePath().c_str(), m_kitName.c_str());
    
    cocos2d::ZipFile zFile = cocos2d::ZipFile(path);
    
    std::string fileName = zFile.getFirstFilename();
    std::string file = fileName;

    ssize_t filesize;
    unsigned char* data = zFile.getFileData(fileName, &filesize);

    std::string directoryName = unzipPath;

    if (!cocos2d::FileUtils::getInstance()->isDirectoryExist(directoryName)) {
        cocos2d::FileUtils::getInstance()->createDirectory(directoryName);
    }
    
    while (data != nullptr) {
        std::string fullFileName = directoryName + file;

        log("filename DIR : %s\n",fullFileName.c_str());

        if(fullFileName[fullFileName.size()-1] == '/'){
            cocos2d::FileUtils::getInstance()->createDirectory(fullFileName);

            free(data);
            fileName = zFile.getNextFilename();
            file = fileName;

            data = zFile.getFileData(fileName, &filesize);
            continue;
        }

        FILE *fp = fopen(fullFileName.c_str(), "wb");

        if (fp) {
            fwrite(data, 1, filesize, fp);
            fclose(fp);
        }

        free(data);
        fileName = zFile.getNextFilename();
        file = fileName;

        data = zFile.getFileData(fileName, &filesize);
    }
}

void KitScene::setupPads() {
    char path[256];
    sprintf(path, "%sKits/%s/dataSounds/%s.txt", FileUtils::getInstance()->getWritablePath().c_str(), m_kitName.c_str(), m_kitName.c_str());
    
    std::ifstream jsonStream;
    jsonStream.open (path);
    
    std::string jsonContent = "";
    std::string getLineContent;
    
    while(std::getline(jsonStream, getLineContent)) {
        jsonContent += getLineContent;
    }
    
    jsonStream.close();
    
    log("%s", jsonContent.c_str());
    
    Document d;
    d.Parse(jsonContent.c_str());
    
    rapidjson::Value& padColors = d["colors"];
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto padWH = (visibleSize.width - 60.0f)/3.0f;
    
    int padNumber = 1;
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 4; j++) {
            char padN[16];
            sprintf(padN, "pad%i", (1 + (j*3)) + i);
            std::string padColor = padColors[padN].GetString();
            log("Pad %i - %s", (1 + (j*3)) + i, padColor.c_str());
            
            auto padType = PadType::Blue;
            
            if(padColor == "azul_loop") {
                padType = PadType::Blue;
            } else if(padColor == "amarelo") {
                padType = PadType::Orange;
            } else if(padColor == "rosa") {
                padType = PadType::Pink;
            } else if(padColor == "verde") {
                padType = PadType::Green;
            }
            
            auto pad = PadTile::createWithType(padType, padWH, padWH);
            pad->setPosition(origin.x +((float)i * padWH) + 20.0f + ((float)i * 10.0f) + (padWH/2.0f),
                             origin.y + visibleSize.height - 150.0f - ((1.0f + (float)j) * padWH) - ((float)j * 10.0f));

            this->addChild(pad);
            
            padNumber++;
        }
    }
}
