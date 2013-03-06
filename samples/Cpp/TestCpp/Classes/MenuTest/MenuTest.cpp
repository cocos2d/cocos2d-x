#include "MenuTest.h"
#include "../testResource.h"

enum {
    kTagMenu = 1,
    kTagMenu0 = 0,                       
    kTagMenu1 = 1,
};

#define MID_CALLBACK    1000
#define MID_CALLBACK2    1001
#define MID_DISABLED    1002
#define MID_ENABLE        1003
#define MID_CONFIG        1004
#define MID_QUIT        1005
#define MID_OPACITY        1006
#define MID_ALIGN        1007
#define MID_CALLBACK3    1008
#define MID_BACKCALLBACK 1009

//------------------------------------------------------------------
//
// MenuLayerMainMenu
//
//------------------------------------------------------------------
MenuLayerMainMenu::MenuLayerMainMenu()
{
    setTouchEnabled(true);
    setTouchPriority(kCCMenuHandlerPriority + 1);
    setTouchMode(kCCTouchesOneByOne);

    // Font Item    
    CCSprite* spriteNormal = CCSprite::create(s_MenuItem, CCRectMake(0,23*2,115,23));
    CCSprite* spriteSelected = CCSprite::create(s_MenuItem, CCRectMake(0,23*1,115,23));
    CCSprite* spriteDisabled = CCSprite::create(s_MenuItem, CCRectMake(0,23*0,115,23));

    CCMenuItemSprite* item1 = CCMenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, this, menu_selector(MenuLayerMainMenu::menuCallback) );
    
    // Image Item
    CCMenuItem* item2 = CCMenuItemImage::create(s_SendScore, s_PressSendScore, this, menu_selector(MenuLayerMainMenu::menuCallback2) );

    // Label Item (LabelAtlas)
    CCLabelAtlas* labelAtlas = CCLabelAtlas::create("0123456789", "fonts/labelatlas.png", 16, 24, '.');
    CCMenuItemLabel* item3 = CCMenuItemLabel::create(labelAtlas, this, menu_selector(MenuLayerMainMenu::menuCallbackDisabled) );
    item3->setDisabledColor( ccc3(32,32,64) );
    item3->setColor( ccc3(200,200,255) );
    
    // Font Item
    CCMenuItemFont *item4 = CCMenuItemFont::create("I toggle enable items", this, menu_selector(MenuLayerMainMenu::menuCallbackEnable) );

    item4->setFontSizeObj(20);
    item4->setFontName("Marker Felt");
    
    // Label Item (CCLabelBMFont)
    CCLabelBMFont* label = CCLabelBMFont::create("configuration", "fonts/bitmapFontTest3.fnt");
    CCMenuItemLabel* item5 = CCMenuItemLabel::create(label, this, menu_selector(MenuLayerMainMenu::menuCallbackConfig));

    // Testing issue #500
    item5->setScale( 0.8f );

    // Events
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont *item6 = CCMenuItemFont::create("Priority Test", this, menu_selector(MenuLayerMainMenu::menuCallbackPriorityTest));
    
    // Bugs Item
    CCMenuItemFont *item7 = CCMenuItemFont::create("Bugs", this, menu_selector(MenuLayerMainMenu::menuCallbackBugsTest));

    // Font Item
    CCMenuItemFont* item8 = CCMenuItemFont::create("Quit", this, menu_selector(MenuLayerMainMenu::onQuit));
    
    CCMenuItemFont* item9 = CCMenuItemFont::create("Remove menu item when moving", this,
                                                   menu_selector(MenuLayerMainMenu::menuMovingCallback));
    
    CCActionInterval* color_action = CCTintBy::create(0.5f, 0, -255, -255);
    CCActionInterval* color_back = color_action->reverse();
    CCSequence* seq = CCSequence::create(color_action, color_back, NULL);
    item8->runAction(CCRepeatForever::create(seq));

    CCMenu* menu = CCMenu::create( item1, item2, item3, item4, item5, item6, item7, item8, item9, NULL);
    menu->alignItemsVertically();
    
    
    // elastic effect
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    int i=0;
    CCNode* child;
    CCArray * pArray = menu->getChildren();
    CCObject* pObject = NULL;
    CCARRAY_FOREACH(pArray, pObject)
    {
        if(pObject == NULL)
            break;

        child = (CCNode*)pObject;

        CCPoint dstPoint = child->getPosition();
        int offset = (int) (s.width/2 + 50);
        if( i % 2 == 0)
            offset = -offset;
        
        child->setPosition( ccp( dstPoint.x + offset, dstPoint.y) );
        child->runAction( 
                          CCEaseElasticOut::create(CCMoveBy::create(2, ccp(dstPoint.x - offset,0)), 0.35f) 
                        );
        i++;
    }

    m_disabledItem = item3; item3->retain();
    m_disabledItem->setEnabled( false );

    addChild(menu);
    menu->setPosition(ccp(s.width/2, s.height/2));
}

bool MenuLayerMainMenu::ccTouchBegan(CCTouch *touch, CCEvent * pEvent)
{
    return true;
}

void MenuLayerMainMenu::ccTouchEnded(CCTouch *touch, CCEvent * pEvent)
{
}

void MenuLayerMainMenu::ccTouchCancelled(CCTouch *touch, CCEvent * pEvent)
{
}

void MenuLayerMainMenu::ccTouchMoved(CCTouch *touch, CCEvent * pEvent)
{
}

MenuLayerMainMenu::~MenuLayerMainMenu()
{
    m_disabledItem->release();
}

void MenuLayerMainMenu::menuCallback(CCObject* sender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(1);
}

void MenuLayerMainMenu::menuCallbackConfig(CCObject* sender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(3);
}

void MenuLayerMainMenu::allowTouches(float dt)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->setPriority(kCCMenuHandlerPriority+1, this);
    unscheduleAllSelectors();
    CCLog("TOUCHES ALLOWED AGAIN");
}

void MenuLayerMainMenu::menuCallbackDisabled(CCObject* sender) 
{
    // hijack all touch events for 5 seconds
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->setPriority(kCCMenuHandlerPriority-1, this);
    schedule(schedule_selector(MenuLayerMainMenu::allowTouches), 5.0f);
    CCLog("TOUCHES DISABLED FOR 5 SECONDS");
}

void MenuLayerMainMenu::menuCallbackEnable(CCObject* sender) 
{
    m_disabledItem->setEnabled(! m_disabledItem->isEnabled() );
}

void MenuLayerMainMenu::menuCallback2(CCObject* sender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(2);
}

void MenuLayerMainMenu::menuCallbackPriorityTest(CCObject* pSender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(4);
}

void MenuLayerMainMenu::menuCallbackBugsTest(CCObject *pSender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(5);
}

void MenuLayerMainMenu::onQuit(CCObject* sender)
{
    //[[Director sharedDirector] end];
    //getCocosApp()->exit();
}

void MenuLayerMainMenu::menuMovingCallback(CCObject *pSender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(6);
}

//------------------------------------------------------------------
//
// MenuLayer2
//
//------------------------------------------------------------------
MenuLayer2::MenuLayer2()
{
    for( int i=0;i < 2;i++ ) 
    {
        CCMenuItemImage* item1 = CCMenuItemImage::create(s_PlayNormal, s_PlaySelect, this, menu_selector(MenuLayer2::menuCallback));
        CCMenuItemImage* item2 = CCMenuItemImage::create(s_HighNormal, s_HighSelect, this, menu_selector(MenuLayer2::menuCallbackOpacity) );
        CCMenuItemImage* item3 = CCMenuItemImage::create(s_AboutNormal, s_AboutSelect, this, menu_selector(MenuLayer2::menuCallbackAlign) );
        
        item1->setScaleX( 1.5f );
        item2->setScaleX( 0.5f );
        item3->setScaleX( 0.5f );
        
        CCMenu* menu = CCMenu::create(item1, item2, item3, NULL);
        
        CCSize s = CCDirector::sharedDirector()->getWinSize();
        menu->setPosition(ccp(s.width/2, s.height/2));

        menu->setTag( kTagMenu );
        
        addChild(menu, 0, 100+i);

        m_centeredMenu = menu->getPosition();
    }

    m_alignedH = true;
    alignMenusH();
}

MenuLayer2::~MenuLayer2()
{
}

void MenuLayer2::alignMenusH()
{
    for(int i=0;i<2;i++) 
    {
        CCMenu *menu = (CCMenu*)getChildByTag(100+i);
        menu->setPosition( m_centeredMenu );
        if(i==0) 
        {
            // TIP: if no padding, padding = 5
            menu->alignItemsHorizontally();            
            CCPoint p = menu->getPosition();
            menu->setPosition( ccpAdd(p, ccp(0,30)) );
            
        } 
        else 
        {
            // TIP: but padding is configurable
            menu->alignItemsHorizontallyWithPadding(40);
            CCPoint p = menu->getPosition();
            menu->setPosition( ccpSub(p, ccp(0,30)) );
        }        
    }
}

void MenuLayer2::alignMenusV()
{
    for(int i=0;i<2;i++) 
    {
        CCMenu *menu = (CCMenu*)getChildByTag(100+i);
        menu->setPosition( m_centeredMenu );
        if(i==0) 
        {
            // TIP: if no padding, padding = 5
            menu->alignItemsVertically();            
            CCPoint p = menu->getPosition();
            menu->setPosition( ccpAdd(p, ccp(100,0)) );            
        } 
        else 
        {
            // TIP: but padding is configurable
            menu->alignItemsVerticallyWithPadding(40);    
            CCPoint p = menu->getPosition();
            menu->setPosition( ccpSub(p, ccp(100,0)) );
        }        
    }
}

void MenuLayer2::menuCallback(CCObject* sender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(0);
}

void MenuLayer2::menuCallbackOpacity(CCObject* sender)
{
    CCMenu* menu = (CCMenu*)(((CCNode*)(sender))->getParent());
    GLubyte opacity = menu->getOpacity();
    if( opacity == 128 )
        menu->setOpacity(255);
    else
        menu->setOpacity(128);     
}

void MenuLayer2::menuCallbackAlign(CCObject* sender)
{
    m_alignedH = ! m_alignedH;
    
    if( m_alignedH )
        alignMenusH();
    else
        alignMenusV(); 
}

//------------------------------------------------------------------
//
// MenuLayer3
//
//------------------------------------------------------------------
MenuLayer3::MenuLayer3()
{
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont::setFontSize(28);

    CCLabelBMFont* label = CCLabelBMFont::create("Enable AtlasItem", "fonts/bitmapFontTest3.fnt");
    CCMenuItemLabel* item1 = CCMenuItemLabel::create(label, this, menu_selector(MenuLayer3::menuCallback2) );
    CCMenuItemFont* item2 = CCMenuItemFont::create("--- Go Back ---", this, menu_selector(MenuLayer3::menuCallback) );
    
    CCSprite *spriteNormal   = CCSprite::create(s_MenuItem,  CCRectMake(0,23*2,115,23));
    CCSprite *spriteSelected = CCSprite::create(s_MenuItem,  CCRectMake(0,23*1,115,23));
    CCSprite *spriteDisabled = CCSprite::create(s_MenuItem,  CCRectMake(0,23*0,115,23));
    
    
    CCMenuItemSprite* item3 = CCMenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, this, menu_selector(MenuLayer3::menuCallback3));
    m_disabledItem = item3;  item3->retain();
    m_disabledItem->setEnabled( false );
    
    CCMenu *menu = CCMenu::create( item1, item2, item3, NULL);    
    menu->setPosition( ccp(0,0) );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    item1->setPosition( ccp(s.width/2 - 150, s.height/2) );
    item2->setPosition( ccp(s.width/2 - 200, s.height/2) );
    item3->setPosition( ccp(s.width/2, s.height/2 - 100) );
    
    CCJumpBy* jump = CCJumpBy::create(3, ccp(400,0), 50, 4);
    item2->runAction( CCRepeatForever::create(CCSequence::create( jump, jump->reverse(), NULL)));

    CCActionInterval* spin1 = CCRotateBy::create(3, 360);
    CCActionInterval* spin2 = (CCActionInterval*)(spin1->copy()->autorelease());
    CCActionInterval* spin3 = (CCActionInterval*)(spin1->copy()->autorelease());
    
    item1->runAction( CCRepeatForever::create(spin1) );
    item2->runAction( CCRepeatForever::create(spin2) );
    item3->runAction( CCRepeatForever::create(spin3) );
    
    addChild( menu ); 

    menu->setPosition(ccp(0,0));
}

MenuLayer3::~MenuLayer3()
{
    m_disabledItem->release();
}

void MenuLayer3::menuCallback(CCObject* sender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(0);
}

void MenuLayer3::menuCallback2(CCObject* sender)
{
    //CCLOG("Label clicked. Toogling AtlasSprite");
    m_disabledItem->setEnabled( ! m_disabledItem->isEnabled() );
    m_disabledItem->stopAllActions();
}

void MenuLayer3::menuCallback3(CCObject* sender)
{
    //CCLOG("MenuItemSprite clicked");
}

//------------------------------------------------------------------
//
// MenuLayer4
//
//------------------------------------------------------------------
MenuLayer4::MenuLayer4()
{
    CCMenuItemFont::setFontName("American Typewriter");
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont*title1 = CCMenuItemFont::create("Sound");
    title1->setEnabled(false);
    CCMenuItemFont::setFontName( "Marker Felt" );
    CCMenuItemFont::setFontSize(34);
    CCMenuItemToggle* item1 = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(MenuLayer4::menuCallback), 
                                                                CCMenuItemFont::create( "On" ),
                                                                CCMenuItemFont::create( "Off"),
                                                                NULL );
    
    CCMenuItemFont::setFontName( "American Typewriter" );
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont* title2 = CCMenuItemFont::create( "Music" );
    title2->setEnabled(false);
    CCMenuItemFont::setFontName( "Marker Felt" );
    CCMenuItemFont::setFontSize(34);
    CCMenuItemToggle *item2 = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(MenuLayer4::menuCallback),
                                                                CCMenuItemFont::create( "On" ),
                                                                CCMenuItemFont::create( "Off"),
                                                                NULL );
    
    CCMenuItemFont::setFontName( "American Typewriter" );
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont* title3 = CCMenuItemFont::create( "Quality" );
    title3->setEnabled( false );
    CCMenuItemFont::setFontName( "Marker Felt" );
    CCMenuItemFont::setFontSize(34);
    CCMenuItemToggle *item3 = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(MenuLayer4::menuCallback), 
                                                                CCMenuItemFont::create( "High" ),
                                                                CCMenuItemFont::create( "Low" ),
                                                                NULL );
    
    CCMenuItemFont::setFontName( "American Typewriter" );
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont* title4 = CCMenuItemFont::create( "Orientation" );
    title4->setEnabled(false);
    CCMenuItemFont::setFontName( "Marker Felt" );
    CCMenuItemFont::setFontSize(34);
    CCMenuItemToggle *item4 = CCMenuItemToggle::createWithTarget(this, 
                                                                menu_selector(MenuLayer4::menuCallback), 
                                                                CCMenuItemFont::create( "Off" ), 
                                                                NULL );
    
    //UxArray* more_items = UxArray::arrayWithObjects(
    //                                                 CCMenuItemFont::create( "33%" ),
    //                                                 CCMenuItemFont::create( "66%" ),
    //                                                 CCMenuItemFont::create( "100%" ),
    //                                                 NULL );
    // TIP: you can manipulate the items like any other CCMutableArray
    item4->getSubItems()->addObject( CCMenuItemFont::create( "33%" ) ); 
    item4->getSubItems()->addObject( CCMenuItemFont::create( "66%" ) ); 
    item4->getSubItems()->addObject( CCMenuItemFont::create( "100%" ) ); 
    
    // you can change the one of the items by doing this
    item4->setSelectedIndex( 2 );
    
    CCMenuItemFont::setFontName( "Marker Felt" );
    CCMenuItemFont::setFontSize( 34 );
    
    CCLabelBMFont *label = CCLabelBMFont::create( "go back", "fonts/bitmapFontTest3.fnt" );
    CCMenuItemLabel* back = CCMenuItemLabel::create(label, this, menu_selector(MenuLayer4::backCallback) );
    
    CCMenu *menu = CCMenu::create(
                  title1, title2,
                  item1, item2,
                  title3, title4,
                  item3, item4,
                  back, NULL ); // 9 items.
    
    menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
    
    addChild( menu );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    menu->setPosition(ccp(s.width/2, s.height/2));
}

MenuLayer4::~MenuLayer4()
{
}

void MenuLayer4::menuCallback(CCObject* sender)
{
    //CCLOG("selected item: %x index:%d", dynamic_cast<CCMenuItemToggle*>(sender)->selectedItem(), dynamic_cast<CCMenuItemToggle*>(sender)->selectedIndex() ); 
}

void MenuLayer4::backCallback(CCObject* sender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(0);
}

MenuLayerPriorityTest::MenuLayerPriorityTest()
{
    // Testing empty menu
    m_pMenu1 = CCMenu::create();
    m_pMenu2 = CCMenu::create();


    // Menu 1
    CCMenuItemFont::setFontName("Marker Felt");
    CCMenuItemFont::setFontSize(18);
    CCMenuItemFont *item1 = CCMenuItemFont::create("Return to Main Menu", this, menu_selector(MenuLayerPriorityTest::menuCallback));
    CCMenuItemFont *item2 = CCMenuItemFont::create("Disable menu for 5 seconds", this, menu_selector(MenuLayerPriorityTest::disableMenuCallback));


    m_pMenu1->addChild(item1);
    m_pMenu1->addChild(item2);

    m_pMenu1->alignItemsVerticallyWithPadding(2);

    addChild(m_pMenu1);

    // Menu 2
    m_bPriority = true;
    CCMenuItemFont::setFontSize(48);
    item1 = CCMenuItemFont::create("Toggle priority", this, menu_selector(MenuLayerPriorityTest::togglePriorityCallback));
    item1->setColor(ccc3(0,0,255));
    m_pMenu2->addChild(item1);
    addChild(m_pMenu2);
}

MenuLayerPriorityTest::~MenuLayerPriorityTest()
{

}

void MenuLayerPriorityTest::menuCallback(CCObject* pSender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(0);
//    [[CCDirector sharedDirector] popScene];
}

void MenuLayerPriorityTest::disableMenuCallback(CCObject* pSender)
{
    m_pMenu1->setEnabled(false);
    CCDelayTime *wait = CCDelayTime::create(5);
    CCCallFunc *enable = CCCallFunc::create(this, callfunc_selector(MenuLayerPriorityTest::enableMenuCallback));

    CCSequence* seq = CCSequence::create(wait, enable, NULL);
    m_pMenu1->runAction(seq);
}

void MenuLayerPriorityTest::enableMenuCallback()
{
    m_pMenu1->setEnabled(true);
}

void MenuLayerPriorityTest::togglePriorityCallback(CCObject* pSender)
{
    if( m_bPriority) {
        m_pMenu2->setHandlerPriority(kCCMenuHandlerPriority + 20);
        m_bPriority = false;
    } else {
        m_pMenu2->setHandlerPriority(kCCMenuHandlerPriority - 20);
        m_bPriority = true;
    }
}

// BugsTest
BugsTest::BugsTest()
{
    CCMenuItemFont *issue1410 = CCMenuItemFont::create("Issue 1410", this, menu_selector(BugsTest::issue1410MenuCallback));
    CCMenuItemFont *issue1410_2 = CCMenuItemFont::create("Issue 1410 #2", this, menu_selector(BugsTest::issue1410v2MenuCallback));
    CCMenuItemFont *back = CCMenuItemFont::create("Back", this, menu_selector(BugsTest::backMenuCallback));
    
    CCMenu *menu = CCMenu::create(issue1410, issue1410_2, back, NULL);
    addChild(menu);
    menu->alignItemsVertically();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    menu->setPosition(ccp(s.width/2, s.height/2));
}

void BugsTest::issue1410MenuCallback(cocos2d::CCObject *pSender)
{
    CCMenu *menu = (CCMenu*)((CCMenuItem*)pSender)->getParent();
    menu->setTouchEnabled(false);
    menu->setTouchEnabled(true);
    
    CCLog("NO CRASHES");
}

void BugsTest::issue1410v2MenuCallback(cocos2d::CCObject *pSender)
{
    CCMenu *menu = (CCMenu*)((CCMenuItem*)pSender)->getParent();
    menu->setTouchEnabled(true);
    menu->setTouchEnabled(false);
    
    CCLog("NO CRASHES. AND MENU SHOULD STOP WORKING");
}

void BugsTest::backMenuCallback(cocos2d::CCObject *pSender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(0);
}

RemoveMenuItemWhenMove::RemoveMenuItemWhenMove()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF* label = CCLabelTTF::create("click item and move, should not crash", "Arial", 20);
    label->setPosition(ccp(s.width/2, s.height - 30));
    addChild(label);
    
    item = CCMenuItemFont::create("item 1");
    item->retain();
    
    CCMenuItemFont *back = CCMenuItemFont::create("go back", this, menu_selector(RemoveMenuItemWhenMove::goBack));
    
    CCMenu *menu = CCMenu::create(item, back, NULL);
    addChild(menu);
    menu->alignItemsVertically();
    
    menu->setPosition(ccp(s.width/2, s.height/2));
    
    setTouchEnabled(true);
}

void RemoveMenuItemWhenMove::goBack(CCObject *pSender)
{
    ((CCLayerMultiplex*)m_pParent)->switchTo(0);
}

RemoveMenuItemWhenMove::~RemoveMenuItemWhenMove()
{
    CC_SAFE_RELEASE(item);
}

void RemoveMenuItemWhenMove::registerWithTouchDispatcher(void)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, false);
}

bool RemoveMenuItemWhenMove::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

void RemoveMenuItemWhenMove::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    if (item)
    {
        item->removeFromParentAndCleanup(true);
        item->release();
        item = NULL;
    }
}

void MenuTestScene::runThisTest()
{
    CCLayer* pLayer1 = new MenuLayerMainMenu();
    CCLayer* pLayer2 = new MenuLayer2();
    CCLayer* pLayer3 = new MenuLayer3();
    CCLayer* pLayer4 = new MenuLayer4();
    CCLayer* pLayer5 = new MenuLayerPriorityTest();
    CCLayer* pLayer6 = new BugsTest();
    CCLayer* pLayer7 = new RemoveMenuItemWhenMove();

    CCLayerMultiplex* layer = CCLayerMultiplex::create(pLayer1, pLayer2, pLayer3, pLayer4, pLayer5, pLayer6, pLayer7, NULL);
    addChild(layer, 0); 

    pLayer1->release();
    pLayer2->release();
    pLayer3->release();
    pLayer4->release();
    pLayer5->release();
    pLayer6->release();
    pLayer7->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
