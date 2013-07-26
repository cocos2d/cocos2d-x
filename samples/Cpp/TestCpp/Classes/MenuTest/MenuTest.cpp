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
    setTouchPriority(Menu::HANDLER_PRIORITY + 1);
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);

    // Font Item    
    Sprite* spriteNormal = Sprite::create(s_MenuItem, Rect(0,23*2,115,23));
    Sprite* spriteSelected = Sprite::create(s_MenuItem, Rect(0,23*1,115,23));
    Sprite* spriteDisabled = Sprite::create(s_MenuItem, Rect(0,23*0,115,23));

    MenuItemSprite* item1 = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, CC_CALLBACK_1(MenuLayerMainMenu::menuCallback, this) );
    
    // Image Item
    MenuItem* item2 = MenuItemImage::create(s_SendScore, s_PressSendScore, CC_CALLBACK_1(MenuLayerMainMenu::menuCallback2, this) );

    // Label Item (LabelAtlas)
    LabelAtlas* labelAtlas = LabelAtlas::create("0123456789", "fonts/labelatlas.png", 16, 24, '.');
    MenuItemLabel* item3 = MenuItemLabel::create(labelAtlas, CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackDisabled, this) );
    item3->setDisabledColor( Color3B(32,32,64) );
    item3->setColor( Color3B(200,200,255) );
    
    // Font Item
    MenuItemFont *item4 = MenuItemFont::create("I toggle enable items", [&](Object *sender) {
		_disabledItem->setEnabled(! _disabledItem->isEnabled() );
	});

    item4->setFontSizeObj(20);
    item4->setFontName("Marker Felt");
    
    // Label Item (LabelBMFont)
    LabelBMFont* label = LabelBMFont::create("configuration", "fonts/bitmapFontTest3.fnt");
    MenuItemLabel* item5 = MenuItemLabel::create(label, CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackConfig, this));

    // Testing issue #500
    item5->setScale( 0.8f );

    // Events
    MenuItemFont::setFontName("Marker Felt");
    MenuItemFont *item6 = MenuItemFont::create("Priority Test", CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackPriorityTest, this));
    
    // Bugs Item
    MenuItemFont *item7 = MenuItemFont::create("Bugs", CC_CALLBACK_1(MenuLayerMainMenu::menuCallbackBugsTest, this));

    // Font Item
    MenuItemFont* item8 = MenuItemFont::create("Quit", CC_CALLBACK_1(MenuLayerMainMenu::onQuit, this));
    
    MenuItemFont* item9 = MenuItemFont::create("Remove menu item when moving", CC_CALLBACK_1(MenuLayerMainMenu::menuMovingCallback, this));
    
    ActionInterval* color_action = TintBy::create(0.5f, 0, -255, -255);
    ActionInterval* color_back = color_action->reverse();
    Sequence* seq = Sequence::create(color_action, color_back, NULL);
    item8->runAction(RepeatForever::create(seq));

    Menu* menu = Menu::create( item1, item2, item3, item4, item5, item6, item7, item8, item9, NULL);
    menu->alignItemsVertically();
    
    
    // elastic effect
    Size s = Director::getInstance()->getWinSize();
    
    int i=0;
    Node* child;
    Array * pArray = menu->getChildren();
    Object* pObject = NULL;
    CCARRAY_FOREACH(pArray, pObject)
    {
        if(pObject == NULL)
            break;

        child = static_cast<Node*>(pObject);

        Point dstPoint = child->getPosition();
        int offset = (int) (s.width/2 + 50);
        if( i % 2 == 0)
            offset = -offset;
        
        child->setPosition( Point( dstPoint.x + offset, dstPoint.y) );
        child->runAction( 
                          EaseElasticOut::create(MoveBy::create(2, Point(dstPoint.x - offset,0)), 0.35f) 
                        );
        i++;
    }

    _disabledItem = item3; item3->retain();
    _disabledItem->setEnabled( false );

    addChild(menu);
    menu->setPosition(Point(s.width/2, s.height/2));
}

bool MenuLayerMainMenu::ccTouchBegan(Touch *touch, Event * event)
{
    return true;
}

void MenuLayerMainMenu::ccTouchEnded(Touch *touch, Event * event)
{
}

void MenuLayerMainMenu::ccTouchCancelled(Touch *touch, Event * event)
{
}

void MenuLayerMainMenu::ccTouchMoved(Touch *touch, Event * event)
{
}

MenuLayerMainMenu::~MenuLayerMainMenu()
{
    _disabledItem->release();
}

void MenuLayerMainMenu::menuCallback(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(1);
}

void MenuLayerMainMenu::menuCallbackConfig(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(3);
}

void MenuLayerMainMenu::allowTouches(float dt)
{
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->setPriority(Menu::HANDLER_PRIORITY+1, this);
    unscheduleAllSelectors();
    log("TOUCHES ALLOWED AGAIN");
}

void MenuLayerMainMenu::menuCallbackDisabled(Object* sender) 
{
    // hijack all touch events for 5 seconds
    Director* director = Director::getInstance();
    director->getTouchDispatcher()->setPriority(Menu::HANDLER_PRIORITY-1, this);
    schedule(schedule_selector(MenuLayerMainMenu::allowTouches), 5.0f);
    log("TOUCHES DISABLED FOR 5 SECONDS");
}

void MenuLayerMainMenu::menuCallback2(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(2);
}

void MenuLayerMainMenu::menuCallbackPriorityTest(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(4);
}

void MenuLayerMainMenu::menuCallbackBugsTest(Object *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(5);
}

void MenuLayerMainMenu::onQuit(Object* sender)
{
    //[[Director sharedDirector] end];
    //getCocosApp()->exit();
}

void MenuLayerMainMenu::menuMovingCallback(Object *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(6);
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
        MenuItemImage* item1 = MenuItemImage::create(s_PlayNormal, s_PlaySelect, CC_CALLBACK_1(MenuLayer2::menuCallback, this));
        MenuItemImage* item2 = MenuItemImage::create(s_HighNormal, s_HighSelect, CC_CALLBACK_1(MenuLayer2::menuCallbackOpacity, this));
        MenuItemImage* item3 = MenuItemImage::create(s_AboutNormal, s_AboutSelect, CC_CALLBACK_1(MenuLayer2::menuCallbackAlign, this));
        
        item1->setScaleX( 1.5f );
        item2->setScaleX( 0.5f );
        item3->setScaleX( 0.5f );
        
        Menu* menu = Menu::create(item1, item2, item3, NULL);
        
        Size s = Director::getInstance()->getWinSize();
        menu->setPosition(Point(s.width/2, s.height/2));

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
        Menu *menu = static_cast<Menu*>( getChildByTag(100+i) );
        menu->setPosition( _centeredMenu );
        if(i==0) 
        {
            // TIP: if no padding, padding = 5
            menu->alignItemsHorizontally();            
            Point p = menu->getPosition();
            menu->setPosition(p + Point(0,30));
            
        } 
        else 
        {
            // TIP: but padding is configurable
            menu->alignItemsHorizontallyWithPadding(40);
            Point p = menu->getPosition();
            menu->setPosition(p - Point(0,30));
        }        
    }
}

void MenuLayer2::alignMenusV()
{
    for(int i=0;i<2;i++) 
    {
        Menu *menu = static_cast<Menu*>( getChildByTag(100+i) );
        menu->setPosition( _centeredMenu );
        if(i==0) 
        {
            // TIP: if no padding, padding = 5
            menu->alignItemsVertically();            
            Point p = menu->getPosition();
            menu->setPosition(p + Point(100,0));
        } 
        else 
        {
            // TIP: but padding is configurable
            menu->alignItemsVerticallyWithPadding(40);    
            Point p = menu->getPosition();
            menu->setPosition(p - Point(100,0));
        }        
    }
}

void MenuLayer2::menuCallback(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

void MenuLayer2::menuCallbackOpacity(Object* sender)
{
    Menu* menu = static_cast<Menu*>( static_cast<Node*>(sender)->getParent() );
    GLubyte opacity = menu->getOpacity();
    if( opacity == 128 )
        menu->setOpacity(255);
    else
        menu->setOpacity(128);     
}

void MenuLayer2::menuCallbackAlign(Object* sender)
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
    MenuItemFont::setFontName("Marker Felt");
    MenuItemFont::setFontSize(28);

    LabelBMFont* label = LabelBMFont::create("Enable AtlasItem", "fonts/bitmapFontTest3.fnt");
    MenuItemLabel* item1 = MenuItemLabel::create(label, [&](Object *sender) {
		//CCLOG("Label clicked. Toogling AtlasSprite");
		_disabledItem->setEnabled( ! _disabledItem->isEnabled() );
		_disabledItem->stopAllActions();
	});
    MenuItemFont* item2 = MenuItemFont::create("--- Go Back ---", [&](Object *sender) {
		    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
	});

    Sprite *spriteNormal   = Sprite::create(s_MenuItem,  Rect(0,23*2,115,23));
    Sprite *spriteSelected = Sprite::create(s_MenuItem,  Rect(0,23*1,115,23));
    Sprite *spriteDisabled = Sprite::create(s_MenuItem,  Rect(0,23*0,115,23));
    
    
    MenuItemSprite* item3 = MenuItemSprite::create(spriteNormal, spriteSelected, spriteDisabled, [](Object *sender) {
		log("sprite clicked!");
	});
    _disabledItem = item3;  item3->retain();
    _disabledItem->setEnabled( false );
    
    Menu *menu = Menu::create( item1, item2, item3, NULL);    
    menu->setPosition( Point(0,0) );

    Size s = Director::getInstance()->getWinSize();
    
    item1->setPosition( Point(s.width/2 - 150, s.height/2) );
    item2->setPosition( Point(s.width/2 - 200, s.height/2) );
    item3->setPosition( Point(s.width/2, s.height/2 - 100) );
    
    JumpBy* jump = JumpBy::create(3, Point(400,0), 50, 4);
    item2->runAction( RepeatForever::create(Sequence::create( jump, jump->reverse(), NULL)));

    ActionInterval* spin1 = RotateBy::create(3, 360);
    ActionInterval* spin2 = spin1->clone();
    ActionInterval* spin3 = spin1->clone();
    
    item1->runAction( RepeatForever::create(spin1) );
    item2->runAction( RepeatForever::create(spin2) );
    item3->runAction( RepeatForever::create(spin3) );
    
    addChild( menu ); 

    menu->setPosition(Point(0,0));
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
    MenuItemFont*title1 = MenuItemFont::create("Sound");
    title1->setEnabled(false);
    MenuItemFont::setFontName( "Marker Felt" );
    MenuItemFont::setFontSize(34);
    MenuItemToggle* item1 = MenuItemToggle::createWithCallback( CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "On" ),
                                                                MenuItemFont::create( "Off"),
                                                                NULL );
    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    MenuItemFont* title2 = MenuItemFont::create( "Music" );
    title2->setEnabled(false);
    MenuItemFont::setFontName( "Marker Felt" );
    MenuItemFont::setFontSize(34);
    MenuItemToggle *item2 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "On" ),
                                                                MenuItemFont::create( "Off"),
                                                                NULL );
    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    MenuItemFont* title3 = MenuItemFont::create( "Quality" );
    title3->setEnabled( false );
    MenuItemFont::setFontName( "Marker Felt" );
    MenuItemFont::setFontSize(34);
    MenuItemToggle *item3 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "High" ),
                                                                MenuItemFont::create( "Low" ),
                                                                NULL );
    
    MenuItemFont::setFontName( "American Typewriter" );
    MenuItemFont::setFontSize(18);
    MenuItemFont* title4 = MenuItemFont::create( "Orientation" );
    title4->setEnabled(false);
    MenuItemFont::setFontName( "Marker Felt" );
    MenuItemFont::setFontSize(34);
    MenuItemToggle *item4 = MenuItemToggle::createWithCallback(CC_CALLBACK_1(MenuLayer4::menuCallback, this),
                                                                MenuItemFont::create( "Off" ), 
                                                                NULL );
    
    //UxArray* more_items = UxArray::arrayWithObjects(
    //                                                 MenuItemFont::create( "33%" ),
    //                                                 MenuItemFont::create( "66%" ),
    //                                                 MenuItemFont::create( "100%" ),
    //                                                 NULL );
    // TIP: you can manipulate the items like any other MutableArray
    item4->getSubItems()->addObject( MenuItemFont::create( "33%" ) ); 
    item4->getSubItems()->addObject( MenuItemFont::create( "66%" ) ); 
    item4->getSubItems()->addObject( MenuItemFont::create( "100%" ) ); 
    
    // you can change the one of the items by doing this
    item4->setSelectedIndex( 2 );
    
    MenuItemFont::setFontName( "Marker Felt" );
    MenuItemFont::setFontSize( 34 );
    
    LabelBMFont *label = LabelBMFont::create( "go back", "fonts/bitmapFontTest3.fnt" );
    MenuItemLabel* back = MenuItemLabel::create(label, CC_CALLBACK_1(MenuLayer4::backCallback, this) );
    
    Menu *menu = Menu::create(
                  title1, title2,
                  item1, item2,
                  title3, title4,
                  item3, item4,
                  back, NULL ); // 9 items.
    
    menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
    
    addChild( menu );

    Size s = Director::getInstance()->getWinSize();
    menu->setPosition(Point(s.width/2, s.height/2));
}

MenuLayer4::~MenuLayer4()
{
}

void MenuLayer4::menuCallback(Object* sender)
{
    //CCLOG("selected item: %x index:%d", dynamic_cast<MenuItemToggle*>(sender)->selectedItem(), dynamic_cast<MenuItemToggle*>(sender)->selectedIndex() ); 
}

void MenuLayer4::backCallback(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

MenuLayerPriorityTest::MenuLayerPriorityTest()
{
    // Testing empty menu
    _menu1 = Menu::create();
    _menu2 = Menu::create();


    // Menu 1
    MenuItemFont::setFontName("Marker Felt");
    MenuItemFont::setFontSize(18);
    MenuItemFont *item1 = MenuItemFont::create("Return to Main Menu", CC_CALLBACK_1(MenuLayerPriorityTest::menuCallback, this));
    MenuItemFont *item2 = MenuItemFont::create("Disable menu for 5 seconds", [&](Object *sender) {
		_menu1->setEnabled(false);
		DelayTime *wait = DelayTime::create(5);
		CallFunc *enable = CallFunc::create( [&]() {
			    _menu1->setEnabled(true);
		});
		Sequence* seq = Sequence::create(wait, enable, NULL);
		_menu1->runAction(seq);
	});


    _menu1->addChild(item1);
    _menu1->addChild(item2);

    _menu1->alignItemsVerticallyWithPadding(2);

    addChild(_menu1);

    // Menu 2
    _priority = true;
    MenuItemFont::setFontSize(48);
    item1 = MenuItemFont::create("Toggle priority", [&](Object *sender) {
		if( _priority) {
			_menu2->setHandlerPriority(Menu::HANDLER_PRIORITY + 20);
			_priority = false;
		} else {
			_menu2->setHandlerPriority(Menu::HANDLER_PRIORITY - 20);
			_priority = true;
		}
	});

    item1->setColor(Color3B(0,0,255));
    _menu2->addChild(item1);
    addChild(_menu2);
}

MenuLayerPriorityTest::~MenuLayerPriorityTest()
{

}

void MenuLayerPriorityTest::menuCallback(Object* sender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
//    [[Director sharedDirector] poscene];
}

// BugsTest
BugsTest::BugsTest()
{
    MenuItemFont *issue1410 = MenuItemFont::create("Issue 1410", CC_CALLBACK_1(BugsTest::issue1410MenuCallback, this));
    MenuItemFont *issue1410_2 = MenuItemFont::create("Issue 1410 #2", CC_CALLBACK_1(BugsTest::issue1410v2MenuCallback, this));
    MenuItemFont *back = MenuItemFont::create("Back", CC_CALLBACK_1(BugsTest::backMenuCallback, this));
    
    Menu *menu = Menu::create(issue1410, issue1410_2, back, NULL);
    addChild(menu);
    menu->alignItemsVertically();
    
    Size s = Director::getInstance()->getWinSize();
    menu->setPosition(Point(s.width/2, s.height/2));
}

void BugsTest::issue1410MenuCallback(Object *sender)
{
    Menu *menu = static_cast<Menu*>( static_cast<Node*>(sender)->getParent() );
    menu->setTouchEnabled(false);
    menu->setTouchEnabled(true);
    
    log("NO CRASHES");
}

void BugsTest::issue1410v2MenuCallback(cocos2d::Object *pSender)
{
    Menu *menu = static_cast<Menu*>( static_cast<MenuItem*>(pSender)->getParent() );
    menu->setTouchEnabled(true);
    menu->setTouchEnabled(false);
    
    log("NO CRASHES. AND MENU SHOULD STOP WORKING");
}

void BugsTest::backMenuCallback(cocos2d::Object *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

RemoveMenuItemWhenMove::RemoveMenuItemWhenMove()
{
    Size s = Director::getInstance()->getWinSize();
    
    LabelTTF* label = LabelTTF::create("click item and move, should not crash", "Arial", 20);
    label->setPosition(Point(s.width/2, s.height - 30));
    addChild(label);
    
    item = MenuItemFont::create("item 1");
    item->retain();
    
    MenuItemFont *back = MenuItemFont::create("go back", CC_CALLBACK_1(RemoveMenuItemWhenMove::goBack, this));
    
    Menu *menu = Menu::create(item, back, NULL);
    addChild(menu);
    menu->alignItemsVertically();
    
    menu->setPosition(Point(s.width/2, s.height/2));
    
    setTouchEnabled(true);
}

void RemoveMenuItemWhenMove::goBack(Object *pSender)
{
    static_cast<LayerMultiplex*>(_parent)->switchTo(0);
}

RemoveMenuItemWhenMove::~RemoveMenuItemWhenMove()
{
    CC_SAFE_RELEASE(item);
}

void RemoveMenuItemWhenMove::registerWithTouchDispatcher(void)
{
    Director::getInstance()->getTouchDispatcher()->addTargetedDelegate(this, -129, false);
}

bool RemoveMenuItemWhenMove::ccTouchBegan(Touch  *touch, Event  *event)
{
    return true;
}

void RemoveMenuItemWhenMove::ccTouchMoved(Touch  *touch, Event  *event)
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
    Layer* layer1 = new MenuLayerMainMenu();
    Layer* layer2 = new MenuLayer2();
    Layer* layer3 = new MenuLayer3();
    Layer* layer4 = new MenuLayer4();
    Layer* layer5 = new MenuLayerPriorityTest();
    Layer* layer6 = new BugsTest();
    Layer* layer7 = new RemoveMenuItemWhenMove();

    LayerMultiplex* layer = LayerMultiplex::create(layer1, layer2, layer3, layer4, layer5, layer6, layer7, NULL);
    addChild(layer, 0); 

    layer1->release();
    layer2->release();
    layer3->release();
    layer4->release();
    layer5->release();
    layer6->release();
    layer7->release();

    Director::getInstance()->replaceScene(this);
}
