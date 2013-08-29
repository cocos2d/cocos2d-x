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
    
    CCSprite *s1 = CCSprite::create("Images/grossini.png");
    CCSprite *s2 = CCSprite::create("Images/grossini_dance_01.png");
    CCSprite *s3 = CCSprite::create("Images/grossini_dance_02.png");
    CCSprite *s4 = CCSprite::create("Images/grossini_dance_03.png");
    CCSprite *s5 = CCSprite::create("Images/grossini_dance_04.png");
    
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
    CCLayer::onEnter();
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::create(title().c_str(), "Arial", 28);
    label->setPosition( ccp(s.width/2, s.height * 4/5) );
    this->addChild(label, 1);
    
    std::string strSubtitle = subtitle();
    if(strSubtitle.empty() == false)
    {
        CCLabelTTF* subLabel = CCLabelTTF::create(strSubtitle.c_str(), "Thonburi", 16);
        subLabel->setPosition( ccp(s.width/2, s.height * 3/5) );
        this->addChild(subLabel, 1);
    }
    
    // Test code
    CCPrettyPrinter vistor;
    
    // print dictionary
    CCDictionary* pDict = CCDictionary::createWithContentsOfFile("animations/animations.plist");
    pDict->acceptVisitor(vistor);
    CCLog("%s", vistor.getResult().c_str());
    CCLog("-------------------------------");
    
    CCSet myset;
    for (int i = 0; i < 30; ++i) {
        myset.addObject(CCString::createWithFormat("str: %d", i));
    }
    vistor.clear();
    myset.acceptVisitor(vistor);
    CCLog("%s", vistor.getResult().c_str());
    CCLog("-------------------------------");
    
    vistor.clear();
    addSprite();
    pDict = CCTextureCache::sharedTextureCache()->snapshotTextures();
    pDict->acceptVisitor(vistor);
    CCLog("%s", vistor.getResult().c_str());
}

void DataVisitorTestScene::runThisTest()
{
    CCLayer *layer = new PrettyPrinterDemo();
    layer->autorelease();
    addChild(layer);

    CCDirector::sharedDirector()->replaceScene(this);
}
