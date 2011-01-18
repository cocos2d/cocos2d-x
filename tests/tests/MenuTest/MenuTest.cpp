#include "MenuTest.h"
#include "../testResource.h"

enum {
	kTagMenu = 1,
	kTagMenu0 = 0,					   
	kTagMenu1 = 1,
};

#define MID_CALLBACK	1000
#define MID_CALLBACK2	1001
#define MID_DISABLED	1002
#define MID_ENABLE		1003
#define MID_CONFIG		1004
#define MID_QUIT		1005
#define MID_OPACITY		1006
#define MID_ALIGN		1007
#define MID_CALLBACK3	1008
#define MID_BACKCALLBACK 1009

//------------------------------------------------------------------
//
// MenuLayer1
//
//------------------------------------------------------------------
MenuLayer1::MenuLayer1()
{
	CCMenuItemFont::setFontSize( 30 );
	CCMenuItemFont::setFontName("Courier New");

	// Font Item
	
	CCSprite* spriteNormal = CCSprite::spriteWithFile(s_MenuItem, CGRectMake(0,23*2,115,23));
	CCSprite* spriteSelected = CCSprite::spriteWithFile(s_MenuItem, CGRectMake(0,23*1,115,23));
	CCSprite* spriteDisabled = CCSprite::spriteWithFile(s_MenuItem, CGRectMake(0,23*0,115,23));
	//dynamic_cast<CCNode*>(mgr)->addChild(spriteNormal);
	//dynamic_cast<CCNode*>(mgr)->addChild(spriteSelected);
	//dynamic_cast<CCNode*>(mgr)->addChild(spriteDisabled);

	CCMenuItemSprite* item1 = CCMenuItemSprite::itemFromNormalSprite(spriteNormal, spriteSelected, spriteDisabled, this, menu_selector(MenuLayer1::menuCallback) );
	
	// Image Item
	CCMenuItem* item2 = CCMenuItemImage::itemFromNormalImage(s_SendScore, s_PressSendScore, this, menu_selector(MenuLayer1::menuCallback2) );

	// Label Item (LabelAtlas)
	CCLabelAtlas* labelAtlas = CCLabelAtlas::labelAtlasWithString("0123456789", "fonts/fps_images.png", 16, 24, '.');
	CCMenuItemLabel* item3 = CCMenuItemLabel::itemWithLabel(labelAtlas, this, menu_selector(MenuLayer1::menuCallbackDisabled) );
	item3->setDisabledColor( ccc3(32,32,64) );
	item3->setColor( ccc3(200,200,255) );
	
	// Font Item
	CCMenuItem *item4 = CCMenuItemFont::itemFromString("I toggle enable items", this, menu_selector(MenuLayer1::menuCallbackEnable) );
	
	// Label Item (BitmapFontAtlas)
	CCLabelBMFont* label = CCLabelBMFont::bitmapFontAtlasWithString("configuration", "fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item5 = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(MenuLayer1::menuCallbackConfig));

	// Testing issue #500
	item5->setScale( 0.8f );

	// Font Item
	CCMenuItemFont* item6 = CCMenuItemFont::itemFromString("Quit", this, menu_selector(MenuLayer1::onQuit));
	
	CCActionInterval* color_action = CCTintBy::actionWithDuration(0.5f, 0, -255, -255);
	CCActionInterval* color_back = color_action->reverse();
	CCFiniteTimeAction* seq = CCSequence::actions(color_action, color_back, NULL);
	item6->runAction(CCRepeatForever::actionWithAction((CCActionInterval*)seq));

	CCMenu* menu = CCMenu::menuWithItems( item1, item2, item3, item4, item5, item6, NULL);
	menu->alignItemsVertically();
	
	
	// elastic effect
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	
	int i=0;
	CCNode* child;
	NSMutableArray<CCNode*> * pArray = menu->getChildren();
    NSMutableArray<CCNode*>::NSMutableArrayIterator it;

	for(it = pArray->begin(); it != pArray->end(); it++)
	{
		if(*it == NULL)
			break;

		child = (CCNode*)(*it);

		CGPoint dstPoint = child->getPosition();
		int offset = (int) (s.width/2 + 50);
		if( i % 2 == 0)
			offset = -offset;
		
		child->setPosition( CGPointMake( dstPoint.x + offset, dstPoint.y) );
		child->runAction( 
							CCEaseElasticOut::actionWithAction(
																CCMoveBy::actionWithDuration(2, CGPointMake(dstPoint.x - offset,0)), 0.35f
															) 
						);
		i++;
	}

	m_disabledItem = item3; item3->retain();
	m_disabledItem->setIsEnabled( false );

	addChild(menu);

}

MenuLayer1::~MenuLayer1()
{
	m_disabledItem->release();
}

void MenuLayer1::menuCallback(NSObject* sender)
{
	((CCMultiplexLayer*)m_pParent)->switchTo(1);
}

void MenuLayer1::menuCallbackConfig(NSObject* sender)
{
	((CCMultiplexLayer*)m_pParent)->switchTo(3);
}

void MenuLayer1::menuCallbackDisabled(NSObject* sender) 
{
}

void MenuLayer1::menuCallbackEnable(NSObject* sender) 
{
	m_disabledItem->setIsEnabled(! m_disabledItem->getIsEnabled() );
}

void MenuLayer1::menuCallback2(NSObject* sender)
{
	((CCMultiplexLayer*)m_pParent)->switchTo(2);
}

void MenuLayer1::onQuit(NSObject* sender)
{
	//[[Director sharedDirector] end];
	//getCocosApp()->exit();
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
		CCMenuItemImage* item1 = CCMenuItemImage::itemFromNormalImage(s_PlayNormal, s_PlaySelect, this, menu_selector(MenuLayer2::menuCallback));
		CCMenuItemImage* item2 = CCMenuItemImage::itemFromNormalImage(s_HighNormal, s_HighSelect, this, menu_selector(MenuLayer2::menuCallbackOpacity) );
		CCMenuItemImage* item3 = CCMenuItemImage::itemFromNormalImage(s_AboutNormal, s_AboutSelect, this, menu_selector(MenuLayer2::menuCallbackAlign) );
		
		item1->setScaleX( 1.5f );
		item2->setScaleX( 0.5f );
		item3->setScaleX( 0.5f );
		
		CCMenu* menu = CCMenu::menuWithItems(item1, item2, item3, NULL);
		
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
			CGPoint p = menu->getPosition();
			menu->setPosition( ccpAdd(p, CGPointMake(0,30)) );
			
		} 
		else 
		{
			// TIP: but padding is configurable
			menu->alignItemsHorizontallyWithPadding(40);
			CGPoint p = menu->getPosition();
			menu->setPosition( ccpSub(p, CGPointMake(0,30)) );
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
			CGPoint p = menu->getPosition();
			menu->setPosition( ccpAdd(p, CGPointMake(100,0)) );			
		} 
		else 
		{
			// TIP: but padding is configurable
			menu->alignItemsVerticallyWithPadding(40);	
			CGPoint p = menu->getPosition();
			menu->setPosition( ccpSub(p, CGPointMake(100,0)) );
		}		
	}
}

void MenuLayer2::menuCallback(NSObject* sender)
{
	((CCMultiplexLayer*)m_pParent)->switchTo(0);
}

void MenuLayer2::menuCallbackOpacity(NSObject* sender)
{
	CCMenu* menu = (CCMenu*)(((CCNode*)(sender))->getParent());
	GLubyte opacity = menu->getOpacity();
	if( opacity == 128 )
		menu->setOpacity(255);
	else
		menu->setOpacity(128);	 
}

void MenuLayer2::menuCallbackAlign(NSObject* sender)
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

	CCLabelBMFont* label = CCLabelBMFont::bitmapFontAtlasWithString("Enable AtlasItem", "fonts/bitmapFontTest3.fnt");
	CCMenuItemLabel* item1 = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(MenuLayer3::menuCallback2) );
	CCMenuItemFont* item2 = CCMenuItemFont::itemFromString("--- Go Back ---", this, menu_selector(MenuLayer3::menuCallback) );
	
	CCSprite *spriteNormal   = CCSprite::spriteWithFile(s_MenuItem,  CGRectMake(0,23*2,115,23));
	CCSprite *spriteSelected = CCSprite::spriteWithFile(s_MenuItem,  CGRectMake(0,23*1,115,23));
	CCSprite *spriteDisabled = CCSprite::spriteWithFile(s_MenuItem,  CGRectMake(0,23*0,115,23));
	
	
	CCMenuItemSprite* item3 = CCMenuItemSprite::itemFromNormalSprite(spriteNormal, spriteSelected, spriteDisabled, this, menu_selector(MenuLayer3::menuCallback3));
	m_disabledItem = item3;  item3->retain();
	m_disabledItem->setIsEnabled( false );
	
	CCMenu *menu = CCMenu::menuWithItems( item1, item2, item3, NULL);	
	menu->setPosition( CGPointMake(0,0) );

	CGSize s = CCDirector::sharedDirector()->getWinSize();
	
	item1->setPosition( CGPointMake(s.width/2 - 150, s.height/2) );
	item2->setPosition( CGPointMake(s.width/2 - 200, s.height/2) );
	item3->setPosition( CGPointMake(s.width/2, s.height/2 - 100) );
	
	CCJumpBy* jump = CCJumpBy::actionWithDuration(3, CGPointMake(400,0), 50, 4);
	item2->runAction( CCRepeatForever::actionWithAction(
								(CCActionInterval*)(CCSequence::actions( jump, jump->reverse(), NULL))
								)
					);
	CCActionInterval* spin1 = CCRotateBy::actionWithDuration(3, 360);
	CCActionInterval* spin2 = (CCActionInterval*)(spin1->copy()->autorelease());
	CCActionInterval* spin3 = (CCActionInterval*)(spin1->copy()->autorelease());
	
	item1->runAction( CCRepeatForever::actionWithAction(spin1) );
	item2->runAction( CCRepeatForever::actionWithAction(spin2) );
	item3->runAction( CCRepeatForever::actionWithAction(spin3) );
	
	addChild( menu ); 
}

MenuLayer3::~MenuLayer3()
{
	m_disabledItem->release();
}

void MenuLayer3::menuCallback(NSObject* sender)
{
	((CCMultiplexLayer*)m_pParent)->switchTo(0);
}

void MenuLayer3::menuCallback2(NSObject* sender)
{
	//UXLOG("Label clicked. Toogling AtlasSprite");
	m_disabledItem->setIsEnabled( ! m_disabledItem->getIsEnabled() );
	m_disabledItem->stopAllActions();
}

void MenuLayer3::menuCallback3(NSObject* sender)
{
	//UXLOG("MenuItemSprite clicked");
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
	CCMenuItemFont*title1 = CCMenuItemFont::itemFromString("Sound");
    title1->setIsEnabled(false);
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(34);
	CCMenuItemToggle* item1 = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(MenuLayer4::menuCallback), 
																CCMenuItemFont::itemFromString( "On" ),
																CCMenuItemFont::itemFromString( "Off"),
																NULL );
    
	CCMenuItemFont::setFontName( "American Typewriter" );
	CCMenuItemFont::setFontSize(18);
	CCMenuItemFont* title2 = CCMenuItemFont::itemFromString( "Music" );
    title2->setIsEnabled(false);
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(34);
	CCMenuItemToggle *item2 = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(MenuLayer4::menuCallback),
																CCMenuItemFont::itemFromString( "On" ),
																CCMenuItemFont::itemFromString( "Off"),
																NULL );
    
	CCMenuItemFont::setFontName( "American Typewriter" );
	CCMenuItemFont::setFontSize(18);
	CCMenuItemFont* title3 = CCMenuItemFont::itemFromString( "Quality" );
    title3->setIsEnabled( false );
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(34);
	CCMenuItemToggle *item3 = CCMenuItemToggle::itemWithTarget(	this, 
																menu_selector(MenuLayer4::menuCallback), 
																CCMenuItemFont::itemFromString( "High" ),
																CCMenuItemFont::itemFromString( "Low" ),
																NULL );
    
	CCMenuItemFont::setFontName( "American Typewriter" );
	CCMenuItemFont::setFontSize(18);
	CCMenuItemFont* title4 = CCMenuItemFont::itemFromString( "Orientation" );
    title4->setIsEnabled(false);
	CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize(34);
	CCMenuItemToggle *item4 = CCMenuItemToggle::itemWithTarget( this, 
																menu_selector(MenuLayer4::menuCallback), 
																CCMenuItemFont::itemFromString( "Off" ), 
																NULL );
	
	//UxArray* more_items = UxArray::arrayWithObjects(
	//												 CCMenuItemFont::itemFromString( "33%" ),
	//												 CCMenuItemFont::itemFromString( "66%" ),
	//												 CCMenuItemFont::itemFromString( "100%" ),
	//												 NULL );
	// TIP: you can manipulate the items like any other NSMutableArray
	item4->getSubItems()->addObject( CCMenuItemFont::itemFromString( "33%" ) ); 
	item4->getSubItems()->addObject( CCMenuItemFont::itemFromString( "66%" ) ); 
	item4->getSubItems()->addObject( CCMenuItemFont::itemFromString( "100%" ) ); 
	
    // you can change the one of the items by doing this
    item4->setSelectedIndex( 2 );
    
    CCMenuItemFont::setFontName( "Marker Felt" );
	CCMenuItemFont::setFontSize( 34 );
	
	CCLabelBMFont *label = CCLabelBMFont::bitmapFontAtlasWithString( "go back", "fonts/bitmapFontTest3.fnt" );
	CCMenuItemLabel* back = CCMenuItemLabel::itemWithLabel(label, this, menu_selector(MenuLayer4::backCallback) );
    
	CCMenu *menu = CCMenu::menuWithItems(
                  title1, title2,
                  item1, item2,
                  title3, title4,
                  item3, item4,
                  back, NULL ); // 9 items.
    
	menu->alignItemsInColumns(2, 2, 2, 2, 1, NULL);
    
	addChild( menu );
}

MenuLayer4::~MenuLayer4()
{
}

void MenuLayer4::menuCallback(NSObject* sender)
{
	//UXLOG("selected item: %x index:%d", dynamic_cast<CCMenuItemToggle*>(sender)->selectedItem(), dynamic_cast<CCMenuItemToggle*>(sender)->selectedIndex() ); 
}

void MenuLayer4::backCallback(NSObject* sender)
{
	((CCMultiplexLayer*)m_pParent)->switchTo(0);
}

void MenuTestScene::runThisTest()
{
    CCLayer* pLayer1 = new MenuLayer1();
    CCLayer* pLayer2 = new MenuLayer2();
    CCLayer* pLayer3 = new MenuLayer3();
    CCLayer* pLayer4 = new MenuLayer4();

    CCMultiplexLayer* layer = CCMultiplexLayer::layerWithLayers(pLayer1, pLayer2, pLayer3, pLayer4, NULL);
    addChild(layer, 0); 

    pLayer1->release();
    pLayer2->release();
    pLayer3->release();
    pLayer4->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
