#include "ActionsTest.h"
#include "CCIntervalAction.h"
#include "touch_dispatcher/CCTouchDispatcher.h"

static Int32 s_nActionIdx = -1;

CCLayer* CreateLayer(Int32 nIndex)
{
    CCLayer * pLayer = NULL;

    switch (nIndex)
    {
    case ACTION_DEMO_LAYER:
        pLayer = new ActionsDemo(); break;
    case ACTION_ROTATE_LAYER:
        pLayer = new ActionRotate(); break;
    default:
        break;
    }

    return pLayer;
}

CCLayer* NextAction()
{
    ++s_nActionIdx;
    s_nActionIdx = s_nActionIdx % ACTION_LAYER_COUNT;

    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* BackAction()
{
    --s_nActionIdx;
    if( s_nActionIdx < 0 )
        s_nActionIdx += ACTION_LAYER_COUNT;	

    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}

CCLayer* RestartAction()
{
    CCLayer* pLayer = CreateLayer(s_nActionIdx);
    pLayer->autorelease();

    return pLayer;
}



void ActionsDemo::onEnter()
{
    __super::onEnter();

    // Example:
    // You can create a sprite using a Texture2D
    CCTexture2D *tex = new CCTexture2D();
    UIImage* pImage = new UIImage();
    pImage->initWithContentsOfFile("/NEWPLUS/TDA_DATA/UserData/grossini.png");
    tex->initWithImage( pImage );
    m_grossini = CCSprite::spriteWithTexture(tex);
    m_grossini->retain();
    delete pImage;
    tex->release();

    // Example:
    // Or you can create an sprite using a filename. PNG, JPEG and BMP files are supported. Probably TIFF too
    m_tamara = CCSprite::spriteWithFile("/NEWPLUS/TDA_DATA/UserData/grossinis_sister1.png"); 
    m_tamara->retain();

    m_kathia = CCSprite::spriteWithFile("/NEWPLUS/TDA_DATA/UserData/grossinis_sister2.png");
    m_kathia->retain();

    addChild(m_grossini, 1);
    addChild(m_tamara, 2);
    addChild(m_kathia, 3);

    centerSprites(3);
//     CGSize s = CCDirector::getSharedDirector()->getWinSize();
//     m_grossini->setPosition( CGPointMake(s.width/4, s.height/2));
//     m_tamara->setPosition( CGPointMake(s.width/2, s.height/2));
//     m_kathia->setPosition( CGPointMake(3 * s.width/4, s.height/2));

    setIsTouchEnabled(true);
/**
@todo add title and menu
*/
//     CCLabel* label = CCLabel::labelWithString(title(), L"Arial", 28);
//     addChild(label, 1);
//     label->setPosition( CGPointMake(s.width/2, s.height-50) );
// 
//     NSString strSubtitle = subtitle();

//     if( ! strSubtitle.empty() ) 

//     {

//         CCLabel* l = CCLabel::labelWithString(strSubtitle, L"Thonburi", 16);

//         addChild(l, 1);

//         l->setPosition( CGPointMake(s.width/2, s.height-80) );

//     }	

// 
//     CCMenuItemImage *item1 = CCMenuItemImage::itemFromNormalImage(L"images/b1.png", L"images/b2.png", this, menu_selector(ActionDemo::backCallback) );
//     CCMenuItemImage *item2 = CCMenuItemImage::itemFromNormalImage(L"images/r1.png",L"images/r2.png", this, menu_selector(ActionDemo::restartCallback) );
//     CCMenuItemImage *item3 = CCMenuItemImage::itemFromNormalImage(L"images/f1.png", L"images/f2.png", this, menu_selector(ActionDemo::nextCallback) );
// 
//     CCMenu *menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
// 
//     menu->setPosition( CGPointZero );
//     item1->setPosition( CGPointMake( s.width/2 - 100,30) );
//     item2->setPosition( CGPointMake( s.width/2, 30) );
//     item3->setPosition( CGPointMake( s.width/2 + 100,30) );
// 
//     addChild(menu, 1);
}

void ActionsDemo::registerWithTouchDispatcher()
{
    CCTouchDispatcher::getSharedDispatcher()->addTargetedDelegate(dynamic_cast<CCLayer*>(this), 0, true);
}

bool ActionsDemo::ccTouchBegan(CCTouch *pTouch, UIEvent *pEvent)
{
    CCScene* s = CCScene::node();
    s->addChild( NextAction() );
    CCDirector::getSharedDirector()->replaceScene(s);
    return true;
}

void ActionsDemo::centerSprites(unsigned int numberOfSprites)
{
    CGSize s = CCDirector::getSharedDirector()->getWinSize();

    if( numberOfSprites == 1 ) 
    {
        m_tamara->setIsVisible(false);
        m_kathia->setIsVisible(false);
        m_grossini->setPosition(CGPointMake(s.width/2, s.height/2));
    }
    else if( numberOfSprites == 2 ) 
    {		
        m_kathia->setPosition( CGPointMake(s.width/3, s.height/2));
        m_tamara->setPosition( CGPointMake(2*s.width/3, s.height/2));
        m_grossini->setIsVisible(false);
    } 
    else if( numberOfSprites == 3 ) 
    {
        m_grossini->setPosition( CGPointMake(s.width/4, s.height/2));
        m_tamara->setPosition( CGPointMake(s.width/2, s.height/2));
        m_kathia->setPosition( CGPointMake(3 * s.width/4, s.height/2));
    }
}

void ActionRotate::onEnter()
{
    __super::onEnter();

    centerSprites(1);

    CCIntervalAction*  actionTo = CCRotateTo::actionWithDuration( 2, 45);
    CCIntervalAction*  actionTo2 = CCRotateTo::actionWithDuration( 2, -45);
    CCIntervalAction*  actionTo0 = CCRotateTo::actionWithDuration(2 , 0);
    m_grossini->runAction( CCSequence::actions(actionTo, actionTo0, NULL));

//     CCIntervalAction*  actionBy = CCRotateBy::actionWithDuration(2 ,  360);
//     CCIntervalAction*  actionByBack = actionBy->reverse();
//     m_grossini->runAction( CCSequence::actions(actionBy, actionByBack, NULL));

    //m_kathia->runAction( CCSequence::actions(actionTo2, actionTo0->copy()->autorelease(), NULL));
}
