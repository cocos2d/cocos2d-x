#include "HiResTest.h"
#include "../testResource.h"

#define MAX_LAYERS          2;
static int sceneIdx = -1;

CCLayer* nextHiResAction();
CCLayer* restartHiResAction();
CCLayer* backHiResAction();

CCLayer* createHiResLayer(int idx)
{
    CCLayer* pLayer = NULL;

    switch (idx)
    {
    case 0:
        CCDirector::sharedDirector()->enableRetinaDisplay(false);
        pLayer = new HiResTest1();
        break;
    case 1:
        CCDirector::sharedDirector()->enableRetinaDisplay(true);
        pLayer = new HiResTest2();
        break;
    }

    return pLayer;
}

CCLayer* nextHiResAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYERS;

    CCLayer* pLayer = createHiResLayer(sceneIdx);
    return pLayer;
}

CCLayer* restartHiResAction()
{
    CCLayer* pLayer = createHiResLayer(sceneIdx);
    return pLayer;
}

CCLayer* backHiResAction()
{
    sceneIdx--;
    if( sceneIdx < 0 )
        sceneIdx += MAX_LAYERS;

    CCLayer* pLayer = createHiResLayer(sceneIdx);
    return pLayer;
}

////////////////////////////////////
//
// HiResDemo
//
///////////////////////////////////
void HiResDemo::onEnter()
{
    CCLayer::onEnter();

    CCSize s = CCDirector::sharedDirector()->getWinSize();

    CCLabelTTF *label = CCLabelTTF::labelWithString(title().c_str(), "Arial", 32);
    label->setPosition(ccp(s.width/2, s.height-50));
    addChild(label, 1);

    std::string sSubTitle = subtitle();
    if (sSubTitle.length())
    {
        CCLabelTTF *subLabel = CCLabelTTF::labelWithString(sSubTitle.c_str(), "Thonburi", 16);
        subLabel->setPosition(ccp(s.width/2, s.height-80));
        addChild(subLabel, 1);
    }
    
    CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(s_pPathB1, s_pPathB2, this, menu_selector(HiResDemo::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(s_pPathR1, s_pPathR2, this, menu_selector(HiResDemo::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(s_pPathF1, s_pPathF2, this, menu_selector(HiResDemo::nextCallback) );

    CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition( CCPointMake( s.width/2 - 100,30) );
    item2->setPosition( CCPointMake( s.width/2, 30) );
    item3->setPosition( CCPointMake( s.width/2 + 100,30) );

    addChild(menu, 1);
}

std::string HiResDemo::title()
{
    return "No title";
}

std::string HiResDemo::subtitle()
{
    return "";
}

void HiResDemo::restartCallback(CCObject* pSender)
{
    CCLayer* pLayer = restartHiResAction();

    if (pLayer)
    {
        pLayer->autorelease();
        CCScene* pScene = new HiResTestScene();
        pScene->addChild(pLayer);

        CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
    }
}

void HiResDemo::nextCallback(CCObject* pSender)
{
    CCLayer* pLayer = nextHiResAction();

    if (pLayer)
    {
        pLayer->autorelease();
        CCScene* pScene = new HiResTestScene();
        pScene->addChild(pLayer);

        CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
    }
}

void HiResDemo::backCallback(CCObject* pSender)
{
    CCLayer* pLayer = backHiResAction();

    if (pLayer)
    {
        pLayer->autorelease();
        CCScene* pScene = new HiResTestScene();
        pScene->addChild(pLayer);

        CCDirector::sharedDirector()->replaceScene(pScene);
        pScene->release();
    }
}

////////////////////////////////////
//
// HiResTest1
//
///////////////////////////////////
void HiResTest1::onEnter()
{

    HiResDemo::onEnter();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::spriteWithFile("Images/grossini.png");
    addChild(sprite);
    sprite->setPosition(ccp(size.width/2, size.height/2));
}

std::string HiResTest1::title()
{
    return "High resolution image test";
}

std::string HiResTest1::subtitle()
{
    return "Image without high resolution resource";
}

////////////////////////////////////
//
// HiResTest2
//
///////////////////////////////////
void HiResTest2::onEnter()
{

    HiResDemo::onEnter();

    CCSize size = CCDirector::sharedDirector()->getWinSize();

    CCSprite *sprite = CCSprite::spriteWithFile("Images/bugs/picture.png");
    addChild(sprite);
    sprite->setPosition(ccp(size.width/2, size.height/2));
}

std::string HiResTest2::title()
{
    return "High resolution image test";
}

std::string HiResTest2::subtitle()
{
    return "Image with high resolution resource";
}

////////////////////////////////////
//
// HiResTestScene
//
///////////////////////////////////
bool HiResTestScene::sm_bRitinaDisplay = false;

void HiResTestScene::runThisTest()
{
    sm_bRitinaDisplay = CCDirector::sharedDirector()->isRetinaDisplay();

    CCLayer* pLayer = nextHiResAction();
    addChild(pLayer);

    pLayer->release();
    CCDirector::sharedDirector()->replaceScene(this);
}

void HiResTestScene::MainMenuCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->enableRetinaDisplay(sm_bRitinaDisplay);
    TestScene::MainMenuCallback(pSender);
}
