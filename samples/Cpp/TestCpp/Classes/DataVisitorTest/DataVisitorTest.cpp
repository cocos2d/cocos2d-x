#include "DataVisitorTest.h"
#include "../testResource.h"

std::string PrettyPrinterDemo::title()
{
    return "PrettyPrinter Test";
}

std::string PrettyPrinterDemo::subtitle()
{
    return "Please see log!";
}

void PrettyPrinterDemo::addSprite()
{
    // create sprites
    
    Sprite *s1 = Sprite::create("Images/grossini.png");
    Sprite *s2 = Sprite::create("Images/grossini_dance_01.png");
    Sprite *s3 = Sprite::create("Images/grossini_dance_02.png");
    Sprite *s4 = Sprite::create("Images/grossini_dance_03.png");
    Sprite *s5 = Sprite::create("Images/grossini_dance_04.png");
    
    s1->setPosition(ccp(50, 50));
    s2->setPosition(ccp(60, 50));
    s3->setPosition(ccp(70, 50));
    s4->setPosition(ccp(80, 50));
    s5->setPosition(ccp(90, 50));
    
    this->addChild(s1);
    this->addChild(s2);
    this->addChild(s3);
    this->addChild(s4);
    this->addChild(s5);
}

void PrettyPrinterDemo::onEnter()
{
    Layer::onEnter();
    Size s = Director::sharedDirector()->getWinSize();
    
    LabelTTF* label = LabelTTF::create(title().c_str(), "Arial", 28);
    label->setPosition( ccp(s.width/2, s.height * 4/5) );
    this->addChild(label, 1);
    
    std::string strSubtitle = subtitle();
    if(strSubtitle.empty() == false)
    {
        LabelTTF* subLabel = LabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        subLabel->setPosition( ccp(s.width/2, s.height * 3/5) );
        this->addChild(subLabel, 1);
    }
    
    // Test code
    PrettyPrinter vistor;
    
    // print dictionary
    Dictionary* pDict = Dictionary::createWithContentsOfFile("animations/animations.plist");
    pDict->acceptVisitor(vistor);
    CCLog("%s", vistor.getResult().c_str());
    CCLog("-------------------------------");
    
    Set myset;
    for (int i = 0; i < 30; ++i) {
        myset.addObject(String::createWithFormat("str: %d", i));
    }
    vistor.clear();
    myset.acceptVisitor(vistor);
    CCLog("%s", vistor.getResult().c_str());
    CCLog("-------------------------------");
    
    vistor.clear();
    addSprite();
    pDict = TextureCache::sharedTextureCache()->snapshotTextures();
    pDict->acceptVisitor(vistor);
    CCLog("%s", vistor.getResult().c_str());
}

void DataVisitorTestScene::runThisTest()
{
    Layer *layer = new PrettyPrinterDemo();
    layer->autorelease();
    addChild(layer);

    Director::sharedDirector()->replaceScene(this);
}
