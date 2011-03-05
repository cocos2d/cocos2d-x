#include "HiResTest.h"
#include "../testResource.h"

#define MAX_LAYERS          2;
static int sceneIdx = -1;

CCLayer* createHiResLayer(int idx)
{
    CCLayer* pLayer = NULL;

    switch (idx)
    {
    case 0:
        pLayer = new HiResTest1(); break;
    case 1:
        pLayer = new HiResTest2(); break;
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

    /**
    @todo CCLabelTTF
    */
//     CCLabelTTF *label = [CCLabelTTF labelWithString:[self title] fontName:@"Arial" fontSize:32];
//     [self addChild: label z:1];
//     [label setPosition: ccp(s.width/2, s.height-50)];
//     CCString *subtitle = [self subtitle];
//     if( subtitle ) {
//         CCLabelTTF *l = [CCLabelTTF labelWithString:subtitle fontName:@"Thonburi" fontSize:16];
//         [self addChild:l z:1];
//         [l setPosition:ccp(s.width/2, s.height-80)];
//     }

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
    return "Standard image";
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
    return "@2x images";
}

std::string HiResTest2::subtitle()
{
    return "Issue #910";
}

////////////////////////////////////
//
// HiResTestScene
//
///////////////////////////////////
void HiResTestScene::runThisTest()
{
    CCLayer* pLayer = nextHiResAction();
    addChild(pLayer);

    pLayer->release();
    CCDirector::sharedDirector()->replaceScene(this);
}
