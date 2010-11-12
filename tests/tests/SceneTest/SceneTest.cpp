#include "SceneTest.h"
#include "../testResource.h"

//------------------------------------------------------------------
//
// SceneTestLayer1
//
//------------------------------------------------------------------
enum
{
	MID_PUSHSCENE = 100,
	MID_PUSHSCENETRAN,
	MID_QUIT,
	MID_REPLACESCENE,
	MID_REPLACESCENETRAN,
	MID_GOBACK
};

SceneTestLayer1::SceneTestLayer1()
{
	CCMenuItemFont* item1 = CCMenuItemFont::itemFromString( "Test pushScene", this, menu_selector(SceneTestLayer1::onPushScene) );
	CCMenuItemFont* item2 = CCMenuItemFont::itemFromString( "Test pushScene w/transition", this, menu_selector(SceneTestLayer1::onPushSceneTran) );
	CCMenuItemFont* item3 = CCMenuItemFont::itemFromString( "Quit", this, menu_selector(SceneTestLayer1::onQuit) );
	
	CCMenu* menu = CCMenu::menuWithItems( item1, item2, item3, NULL );
	menu->alignItemsVertically();
	
	addChild( menu );
	
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	addChild(sprite);
	sprite->setPosition( CGPointMake(s.width-40, s.height/2) );
	CCIntervalAction* rotate = CCRotateBy::actionWithDuration(2, 360);
	CCAction* repeat = CCRepeatForever::actionWithAction(rotate);
	sprite->runAction(repeat);

	schedule( schedule_selector(SceneTestLayer1::testDealloc) );
}

void SceneTestLayer1::testDealloc(ccTime dt)
{
	//UXLOG("SceneTestLayer1:testDealloc");
}

SceneTestLayer1::~SceneTestLayer1()
{
	//NSLog(@"SceneTestLayer1 - dealloc");
}

void SceneTestLayer1::onPushScene(NSObject* pSender)
{
	CCScene* scene = new SceneTestScene();
    CCLayer* pLayer = new SceneTestLayer2();
    scene->addChild( pLayer, 0 );
	CCDirector::sharedDirector()->pushScene( scene );
    scene->release();
    pLayer->release();
}

void SceneTestLayer1::onPushSceneTran(NSObject* pSender)
{
	CCScene* scene = new SceneTestScene();
    CCLayer* pLayer = new SceneTestLayer2();
    scene->addChild( pLayer, 0 );

	CCDirector::sharedDirector()->pushScene( CCSlideInTTransition::transitionWithDuration(1, scene) );
    scene->release();
    pLayer->release();
}


void SceneTestLayer1::onQuit(NSObject* pSender)
{
	//getCocosApp()->exit();
	//CCDirector::sharedDirector()->popScene();

	//// HA HA... no more terminate on sdk v3.0
	//// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
	//if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
	//	[[UIApplication sharedApplication] performSelector:@selector(terminate)];
}

//------------------------------------------------------------------
//
// SceneTestLayer2
//
//------------------------------------------------------------------

SceneTestLayer2::SceneTestLayer2()
{
	m_timeCounter = 0;

	CCMenuItemFont* item1 = CCMenuItemFont::itemFromString( "replaceScene", this,  menu_selector(SceneTestLayer2::onReplaceScene) );
	CCMenuItemFont* item2 = CCMenuItemFont::itemFromString( "replaceScene w/transition", this, menu_selector(SceneTestLayer2::onReplaceSceneTran) );
	CCMenuItemFont* item3 = CCMenuItemFont::itemFromString( "Go Back", this, menu_selector(SceneTestLayer2::onGoBack) );
	
	CCMenu* menu = CCMenu::menuWithItems( item1, item2, item3, NULL );
	menu->alignItemsVertically();
	
	addChild( menu );

	CGSize s = CCDirector::sharedDirector()->getWinSize();
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	addChild(sprite);
	sprite->setPosition( CGPointMake(s.width-40, s.height/2) );
	CCIntervalAction* rotate = CCRotateBy::actionWithDuration(2, 360);
	CCAction* repeat = CCRepeatForever::actionWithAction(rotate);
	sprite->runAction(repeat);

	schedule( schedule_selector(SceneTestLayer2::testDealloc) );
}

void SceneTestLayer2::testDealloc(ccTime dt)
{
	//m_timeCounter += dt;
	//if( m_timeCounter > 10 )
	//	onReplaceScene(this);
}

void SceneTestLayer2::onGoBack(NSObject* pSender)
{
	CCDirector::sharedDirector()->popScene();
}

void SceneTestLayer2::onReplaceScene(NSObject* pSender)
{
	CCScene* pScene = new SceneTestScene();
    CCLayer* pLayer = new SceneTestLayer3();
    pScene->addChild( pLayer, 0 );
	CCDirector::sharedDirector()->replaceScene( pScene );
    pScene->release();
    pLayer->release();
}


void SceneTestLayer2::onReplaceSceneTran(NSObject* pSender)
{
	CCScene* pScene = new SceneTestScene();
    CCLayer* pLayer = new SceneTestLayer3();
	pScene->addChild( pLayer, 0 );
	CCDirector::sharedDirector()->replaceScene( CCFlipXTransition::transitionWithDuration(2, pScene) );
    pScene->release();
    pLayer->release();
}

//------------------------------------------------------------------
//
// SceneTestLayer3
//
//------------------------------------------------------------------

SceneTestLayer3::SceneTestLayer3()
{
	setIsTouchEnabled( true );
	CCLabel* label = CCLabel::labelWithString("Touch to popScene", "Marker Felt", 28);
	addChild(label);
	CGSize s = CCDirector::sharedDirector()->getWinSize();
	label->setPosition( CGPointMake(s.width/2, s.height/2) );
	
	CCSprite* sprite = CCSprite::spriteWithFile(s_pPathGrossini);
	addChild(sprite);
	sprite->setPosition( CGPointMake(s.width-40, s.height/2) );
	CCIntervalAction* rotate = CCRotateBy::actionWithDuration(2, 360);
	CCAction* repeat = CCRepeatForever::actionWithAction(rotate);
	sprite->runAction(repeat);

	//schedule();
}

void SceneTestLayer3::testDealloc(ccTime dt)
{

}

void SceneTestLayer3::ccTouchesEnded(NSSet* touches, UIEvent* event)
{
	static int i = 0;
	//UXLOG("SceneTestLayer3::ccTouchesEnded(%d)", ++i);
	CCDirector::sharedDirector()->popScene();
}

void SceneTestScene::runThisTest()
{
    CCLayer* pLayer = new SceneTestLayer1();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
