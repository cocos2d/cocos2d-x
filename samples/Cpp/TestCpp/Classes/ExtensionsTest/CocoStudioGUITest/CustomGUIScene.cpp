

#include "CustomGUIScene.h"
#include "CocoStudioGUITest.h"
#include "CustomTest/CustomImageTest/CustomImageTest.h"
#include "CustomTest/CustomParticleWidgetTest/CustomParticleWidgetTest.h"


enum
{
    LINE_SPACE = 40,
    kItemTagBasic = 1000,
};

enum
{
    CUSTOM_IMAGE = 0,
    CUSTOM_PARTICLE_WIDGET,
    CUSTOM_MAX_COUNT,
};

static const std::string testsName[CUSTOM_MAX_COUNT] =
{
    "custom gui ImageTest",
    "custom gui ParticleWidgetTest",
};

////////////////////////////////////////////////////////
//
// CustomGUITestMainLayer
//
////////////////////////////////////////////////////////

static CCPoint _curPos = CCPointZero;

void CustomGUITestMainLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    _itemMenu = CCMenu::create();
    _itemMenu->setPosition( _curPos );
    CCMenuItemFont::setFontName("Arial");
    CCMenuItemFont::setFontSize(24);
    for (int i = 0; i < CUSTOM_MAX_COUNT; ++i)
    {
        CCMenuItemFont* pItem = CCMenuItemFont::create(testsName[i].c_str(), this,
                                                       menu_selector(CustomGUITestMainLayer::menuCallback));
        pItem->setPosition(ccp(s.width / 2, s.height / 4 * 3 - (i + 1) * LINE_SPACE));
        _itemMenu->addChild(pItem, kItemTagBasic + i);
    }
    setTouchEnabled(true);
    addChild(_itemMenu);
}

void CustomGUITestMainLayer::menuCallback(CCObject* pSender)
{
    CCMenuItemFont* pItem = (CCMenuItemFont*)pSender;
    int nIndex = pItem->getZOrder() - kItemTagBasic;
    
    switch (nIndex)
    {
        case CUSTOM_IMAGE:
        {
            CustomImageScene* pScene = new CustomImageScene();
            pScene->runThisTest();
            pScene->release();
        }
            break;
            
        case CUSTOM_PARTICLE_WIDGET:
        {
            CustomParticleWidgetScene* pScene = new CustomParticleWidgetScene();
            pScene->runThisTest();
            pScene->release();
        }
            
        default:
            break;
    }
        
//    CCDirector::sharedDirector()->replaceScene(pScene);
}

void CustomGUITestMainLayer::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    _beginPos = touch->getLocation();
}

void CustomGUITestMainLayer::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    
    CCPoint touchLocation = touch->getLocation();
    float nMoveY = touchLocation.y - _beginPos.y;
    
    CCPoint curPos  = _itemMenu->getPosition();
    CCPoint nextPos = ccp(curPos.x, curPos.y + nMoveY);
    
    if (nextPos.y < 0.0f)
    {
        _itemMenu->setPosition(CCPointZero);
        return;
    }
    
    if (nextPos.y > ((CUSTOM_MAX_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height))
    {
        _itemMenu->setPosition(ccp(0, ((CUSTOM_MAX_COUNT + 1)* LINE_SPACE - VisibleRect::getVisibleRect().size.height)));
        return;
    }
    
    _itemMenu->setPosition(nextPos);
    _beginPos = touchLocation;
    _curPos   = nextPos;
}

////////////////////////////////////////////////////////
//
// CustomGUITestScene
//
////////////////////////////////////////////////////////

void CustomGUITestScene::onEnter()
{
    CCScene::onEnter();
    
    CCLabelTTF* label = CCLabelTTF::create("Back", "Arial", 20);
    //#endif
    CCMenuItemLabel* pMenuItem = CCMenuItemLabel::create(label, this, menu_selector(CustomGUITestScene::BackCallback));
    
    CCMenu* pMenu =CCMenu::create(pMenuItem, NULL);
    
    pMenu->setPosition( CCPointZero );
    pMenuItem->setPosition( ccp( VisibleRect::right().x - 50, VisibleRect::bottom().y + 25) );
    
    addChild(pMenu, 1);
}

void CustomGUITestScene::runThisTest()
{
    CCLayer* pLayer = new CustomGUITestMainLayer();
    addChild(pLayer);
    pLayer->release();
    
    CCDirector::sharedDirector()->replaceScene(this);
}

void CustomGUITestScene::BackCallback(CCObject* pSender)
{
    CocoStudioGUITestScene* pScene = new CocoStudioGUITestScene();
    pScene->runThisTest();
    pScene->release();
}
