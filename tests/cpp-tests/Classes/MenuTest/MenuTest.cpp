/****************************************************************************
 Copyright (c) 2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

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
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(true);
    _touchListener->onTouchBegan = CC_CALLBACK_2(MenuLayerMainMenu::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(MenuLayerMainMenu::onTouchMoved, this);
    _touchListener->onTouchEnded = CC_CALLBACK_2(MenuLayerMainMenu::onTouchEnded, this);
    _touchListener->onTouchCancelled = CC_CALLBACK_2(MenuLayerMainMenu::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, 1);

    // Font Item    
    auto spriteNormal = Sprite::create(s_MenuItem, Rect(0,23*2,115,23));
    auto spriteSelected = Sprite::create(s_MenuItem, Rect(0,23*1,115,23));
    auto spriteDisabled = Sprite::create(s_MenuItem, Rect(0,23*0,115,23));

    auto item1 = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(MenuLayerMainMenu::menuCallback, this) );
    
    // Image Item
    auto item2 = MenuItemImage::create(s_SendScore, s_PressSendScore, CC_CALLBACK_1(MenuLayerMainMenu::menuCallback2, this) );

    // Label Item (LabelAtlas)
    auto labelAtlas = LabelAtlas::create("0123456789", "fonts/labelatlas.png", 16, 24, '.');
    auto item3 = MenuItemLabel::create(labelAtlas, CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackDisabled, this) );
    item3->setDisabledColor( Color3B(32,32,64) );
    item3->setColor( Color3B(200,200,255) );
    
    // Font Item
    auto item4 = MenuItemFont::create("I toggle enable items", [&](Ref *sender) {
		_disabledItem->setEnabled(! _disabledItem->isEnabled() );
	});

    item4->setFontSizeObj(20);
    item4->setFontName("fonts/Marker Felt.ttf");
    
    // Label Item (LabelBMFont)
    auto label = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "configuration");
    auto item5 = MenuItemLabel::create(label, CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackConfig, this));

    // Testing issue #500
    item5->setScale( 0.8f );

    // Events
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    // Bugs Item
    auto item6 = MenuItemFont::create("Bugs", CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackBugsTest, this));

    // Font Item
    auto item7= MenuItemFont::create("Quit", CC_CALLBACK_1(MenuLayerMainMenu::onQuit, this));
    
    auto item8 = MenuItemFont::create("Remove menu item when moving", CC_CALLBACK_1(MenuLayerMainMenu::menuMovingCallback, this));
    
    auto color_action = TintBy::create(0.5f, 0, -255, -255);
    auto color_back = color_action->reverse();
    auto seq = Sequence::create(color_action, color_back, nullptr);
    item7->runAction(RepeatForever::create(seq));

    auto menu = Menu::create( item1, item2, item3, item4, item5, item6, item7, item8,  nullptr);
    menu->alignItemsVertically();
    
    
    // elastic effect
    auto s = Director::getInstance()->getWinSize();
    
    int i=0;
    for(const auto &child : menu->getChildren()) {
        auto dstPoint = child->getPosition();
        int offset = (int) (s.width/2 + 50);
        if( i % 2 == 0)
            offset = -offset;
        
        child->setPosition( Vec2( dstPoint.x + offset, dstPoint.y) );
        child->runAction(
                         EaseElasticOut::create(MoveBy::create(2, Vec2(dstPoint.x - offset,0)), 0.35f)
                         );
        i++;
    }

    _disabledItem = item3; item3->retain();
    _disabledItem->setEnabled( false );

    addChild(menu);
    menu->setPosition(Vec2(s.width/2, s.height/2));
    menu->setScale(0);
    menu->runAction(ScaleTo::create(1,1));
}

bool MenuLayerMainMenu::onTouchBegan(Touch *touch, Event * event)
{
    return true;
}

void MenuLayerMainMenu::onTouchEnded(Touch *touch, Event * event)
{
}

void MenuLayerMainMenu::onTouchCancelled(Touch *touch, Event * event)
{
}

void MenuLayerMainMenu::onTouchMoved(Touch *touch, Event * event)
{
}

MenuLayerMainMenu::~MenuLayerMainMenu()
{
    _eventDispatcher->removeEventListener(_touchListener);
    _disabledItem->release();
}

void MenuLayerMainMenu::menuCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(1);
}

void MenuLayerMainMenu::menuCallbackConfig(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(3);
}

void MenuLayerMainMenu::allowTouches(float dt)
{
    _eventDispatcher->setPriority(_touchListener, 1);
    unscheduleAllSelectors();
    log("TOUCHES ALLOWED AGAIN");
}

void MenuLayerMainMenu::menuCallbackDisabled(Ref* sender) 
{
    // hijack all touch events for 5 seconds
    _eventDispatcher->setPriority(_touchListener, -1);
    schedule(schedule_selector(MenuLayerMainMenu::allowTouches), 5.0f);
    log("TOUCHES DISABLED FOR 5 SECONDS");
}

void MenuLayerMainMenu::menuCallback2(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(2);
}

void MenuLayerMainMenu::menuCallbackBugsTest(Ref *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(4);
}

void MenuLayerMainMenu::onQuit(Ref* sender)
{
    //[[Director sharedDirector] end];
    //getCocosApp()->exit();
}

void MenuLayerMainMenu::menuMovingCallback(Ref *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(5);
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
        auto item1 = MenuItemImage::create(s_PlayNormal, s_PlaySelect, CC_CALLBACK_1(MenuLayer2::menuCallback, this));
        auto item2 = MenuItemImage::create(s_HighNormal, s_HighSelect, CC_CALLBACK_1(MenuLayer2::menuCallbackOpacity, this));
        auto item3 = MenuItemImage::create(s_AboutNormal, s_AboutSelect, CC_CALLBACK_1(MenuLayer2::menuCallbackAlign, this));
        
        item1->setScaleX( 1.5f );
        item2->setScaleX( 0.5f );
        item3->setScaleX( 0.5f );
        
        auto menu = Menu::create(item1, item2, item3, nullptr);
        
        auto s = Director::getInstance()->getWinSize();
        menu->setPosition(Vec2(s.width/2, s.height/2));

        menu->setTag( kTagMenu );
        
        addChild(menu, 0, 100+i);

        _centeredMenu = menu->getPosition();
    }

    _alignedH = true;
    alignMenusH();
}

MenuLayer2::~MenuLayer2()
{
}

void MenuLayer2::alignMenusH()
{
    for(int i=0;i<2;i++) 
    {
        auto menu = static_cast<Menu*>( getChildByTag(100+i) );
        menu->setPosition( _centeredMenu );
        if(i==0) 
        {
            // TIP: if no padding, padding = 5
            menu->alignItemsHorizontally();            
            auto p = menu->getPosition();
            menu->setPosition(p + Vec2(0,30));
            
        } 
        else 
        {
            // TIP: but padding is configurable
            menu->alignItemsHorizontallyWithPadding(40);
            auto p = menu->getPosition();
            menu->setPosition(p - Vec2(0,30));
        }        
    }
}

void MenuLayer2::alignMenusV()
{
    for(int i=0;i<2;i++) 
    {
        auto menu = static_cast<Menu*>( getChildByTag(100+i) );
        menu->setPosition( _centeredMenu );
        if(i==0) 
        {
            // TIP: if no padding, padding = 5
            menu->alignItemsVertically();            
            auto p = menu->getPosition();
            menu->setPosition(p + Vec2(100,0));
        } 
        else 
        {
            // TIP: but padding is configurable
            menu->alignItemsVerticallyWithPadding(40);    
            auto p = menu->getPosition();
            menu->setPosition(p - Vec2(100,0));
        }        
    }
}

void MenuLayer2::menuCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

void MenuLayer2::menuCallbackOpacity(Ref* sender)
{
    auto menu = static_cast<Menu*>( static_cast<Node*>(sender)->getParent() );
    GLubyte opacity = menu->getOpacity();
    if( opacity == 128 )
        menu->setOpacity(255);
    else
        menu->setOpacity(128);     
}

void MenuLayer2::menuCallbackAlign(Ref* sender)
{
    _alignedH = ! _alignedH;
    
    if( _alignedH )
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
    MenuItemFont::setFontName("fonts/Marker Felt.ttf");
    MenuItemFont::setFontSize(28);

    auto label = Label::createWithBMFont("fonts/bitmapFontTest3.fnt", "Enable AtlasItem");
    auto item1 = MenuItemLabel::create(label, [&](Ref *sender) {
		//CCLOG("Label clicked. Toogling AtlasSprite");
		_disabledItem->setEnabled( ! _disabledItem->isEnabled() );
		_disabledItem->stopAllActions();
	});
    auto item2 = MenuItemFont::create("--- Go Back ---", [&](Ref *sender) {
		    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
	});

    auto spriteNormal   = Sprite::create(s_MenuItem,  Rect(0,23*2,115,23));
    auto spriteSelected = Sprite::create(s_MenuItem,  Rect(0,23*1,115,23));
    auto spriteDisabled = Sprite::create(s_MenuItem,  Rect(0,23*0,115,23));
    
    
    auto item3 = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, [](Ref *sender) {
		log("sprite clicked!");
	});
    _disabledItem = item3;  item3->retain();
    _disabledItem->setEnabled( false );
    
    auto menu = Menu::create( item1, item2, item3, nullptr);    
    menu->setPosition( Vec2(0,0) );

    auto s = Director::getInstance()->getWinSize();
    
    item1->setPosition( Vec2(s.width/2 - 150, s.height/2) );
    item2->setPosition( Vec2(s.width/2 - 200, s.height/2) );
    item3->setPosition( Vec2(s.width/2, s.height/2 - 100) );
    
    auto jump = JumpBy::create(3, Vec2(400,0), 50, 4);
    item2->runAction( RepeatForever::create(Sequence::create( jump, jump->reverse(), nullptr)));

    auto spin1 = RotateBy::create(3, 360);
    auto spin2 = spin1->clone();
    auto spin3 = spin1->clone();
    
    item1->runAction( RepeatForever::create(spin1) );
    item2->runAction( RepeatForever::create(spin2) );
    item3->runAction( RepeatForever::create(spin3) );
    
    addChild( menu ); 

    menu->setPosition(Vec2(0,0));
}

MenuLayer3::~MenuLayer3()
{
    _disabledItem->release();
}

//------------------------------------------------------------------
//
// MenuLayer4
//
//------------------------------------------------------------------
MenuLayer4::MenuLayer4()
{
    MenuItemFont::setFontName("American Typewriter");
    MenuItemFont::setFontSize(18);
    auto title1 = MenuItemFont::create("Sound");
    title1->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(34);
    auto item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "On" ),
                                                                MenuItemFont::create( "Off"),
                                                                nullptr );
    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title2 = MenuItemFont::create( "Music" );
    title2->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(34);
    auto item2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "On" ),
                                                                MenuItemFont::create( "Off"),
                                                                nullptr );
    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title3 = MenuItemFont::create( "Quality" );
    title3->setEnabled( false );
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(34);
    auto item3 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "High" ),
                                                                MenuItemFont::create( "Low" ),
                                                                nullptr );
    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    auto title4 = MenuItemFont::create( "Orientation" );
    title4->setEnabled(false);
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize(34);
    auto item4 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "Off" ), 
                                                                nullptr );
    
    // TIP: you can manipulate the items like any other MutableArray
    item4->getSubItems().pushBack( MenuItemFont::create( "33%" ) );
    item4->getSubItems().pushBack( MenuItemFont::create( "66%" ) );
    item4->getSubItems().pushBack( MenuItemFont::create( "100%" ) );
    
    // you can change the one of the items by doing this
    item4->setSelectedIndex( 2 );
    
    MenuItemFont::setFontName( "fonts/Marker Felt.ttf" );
    MenuItemFont::setFontSize( 34 );
    
    auto label = Label::createWithBMFont("fonts/bitmapFontTest3.fnt",  "go back");
    auto back = MenuItemLabel::create(label, CC_CALLBACK_1(MenuLayer4::backCallback, this) );
    
    auto menu = Menu::create(
                  title1, title2,
                  item1, item2,
                  title3, title4,
                  item3, item4,
                  back, nullptr ); // 9 items.
    
    menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
    
    addChild( menu );

    auto s = Director::getInstance()->getWinSize();
    menu->setPosition(Vec2(s.width/2, s.height/2));
}

MenuLayer4::~MenuLayer4()
{
}

void MenuLayer4::menuCallback(Ref* sender)
{
    //CCLOG("selected item: %x index:%d", dynamic_cast<MenuItemToggle*>(sender)->selectedItem(), dynamic_cast<MenuItemToggle*>(sender)->selectedIndex() ); 
}

void MenuLayer4::backCallback(Ref* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

// BugsTest
BugsTest::BugsTest()
{
    auto issue1410 = MenuItemFont::create("Issue 1410", CC_CALLBACK_1(BugsTest::issue1410MenuCallback, this));
    auto issue1410_2 = MenuItemFont::create("Issue 1410 #2", CC_CALLBACK_1(BugsTest::issue1410v2MenuCallback, this));
    auto back = MenuItemFont::create("Back", CC_CALLBACK_1(BugsTest::backMenuCallback, this));
    
    auto menu = Menu::create(issue1410, issue1410_2, back, nullptr);
    addChild(menu);
    menu->alignItemsVertically();
    
    auto s = Director::getInstance()->getWinSize();
    menu->setPosition(Vec2(s.width/2, s.height/2));
}

void BugsTest::issue1410MenuCallback(Ref *sender)
{
    auto menu = static_cast<Menu*>( static_cast<Node*>(sender)->getParent() );
    menu->setEnabled(false);
    menu->setEnabled(true);
    
    log("NO CRASHES");
}

void BugsTest::issue1410v2MenuCallback(cocos2d::Ref *pSender)
{
    auto menu = static_cast<Menu*>( static_cast<MenuItem*>(pSender)->getParent() );
    menu->setEnabled(true);
    menu->setEnabled(false);
    
    log("NO CRASHES. AND MENU SHOULD STOP WORKING");
}

void BugsTest::backMenuCallback(cocos2d::Ref *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

RemoveMenuItemWhenMove::RemoveMenuItemWhenMove()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto label = Label::createWithTTF("click item and move, should not crash", "fonts/arial.ttf", 20);
    label->setPosition(Vec2(s.width/2, s.height - 30));
    addChild(label);
    
    item = MenuItemFont::create("item 1");
    item->retain();
    
    auto back = MenuItemFont::create("go back", CC_CALLBACK_1(RemoveMenuItemWhenMove::goBack, this));
    
    auto menu = Menu::create(item, back, nullptr);
    addChild(menu);
    menu->alignItemsVertically();
    
    menu->setPosition(Vec2(s.width/2, s.height/2));
    
    // Register Touch Event
    _touchListener = EventListenerTouchOneByOne::create();
    _touchListener->setSwallowTouches(false);
    
    _touchListener->onTouchBegan = CC_CALLBACK_2(RemoveMenuItemWhenMove::onTouchBegan, this);
    _touchListener->onTouchMoved = CC_CALLBACK_2(RemoveMenuItemWhenMove::onTouchMoved, this);
    
    _eventDispatcher->addEventListenerWithFixedPriority(_touchListener, -129);
    
}

void RemoveMenuItemWhenMove::goBack(Ref *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

RemoveMenuItemWhenMove::~RemoveMenuItemWhenMove()
{
    _eventDispatcher->removeEventListener(_touchListener);
    CC_SAFE_RELEASE(item);
}

bool RemoveMenuItemWhenMove::onTouchBegan(Touch  *touch, Event  *event)
{
    return true;
}

void RemoveMenuItemWhenMove::onTouchMoved(Touch  *touch, Event  *event)
{
    if (item)
    {
        item->removeFromParentAndCleanup(true);
        item->release();
        item = nullptr;
    }
}

void MenuTestScene::runThisTest()
{
    MenuItemFont::setFontSize(20);
    
    auto layer1 = new MenuLayerMainMenu();
    auto layer2 = new MenuLayer2();
    auto layer3 = new MenuLayer3();
    auto layer4 = new MenuLayer4();
    auto layer5 = new BugsTest();
    auto layer6 = new RemoveMenuItemWhenMove();

    auto layer = LayerMultiplex::create(layer1, layer2, layer3, layer4, layer5, layer6, nullptr);
    addChild(layer, 0); 

    layer1->release();
    layer2->release();
    layer3->release();
    layer4->release();
    layer5->release();
    layer6->release();

    Director::getInstance()->replaceScene(this);
}
