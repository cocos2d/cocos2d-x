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
    CCMenuItemFont* item1 = CCMenuItemFont::create( "Test pushScene", CC_CALLBACK_1(SceneTestLayer1::onPushScene, this));
    CCMenuItemFont* item2 = CCMenuItemFont::create( "Test pushScene w/transition", CC_CALLBACK_1(SceneTestLayer1::onPushSceneTran, this));
    CCMenuItemFont* item3 = CCMenuItemFont::create( "Quit", CC_CALLBACK_1(SceneTestLayer1::onQuit, this));
    
    CCMenu* menu = CCMenu::create( item1, item2, item3, NULL );
    menu->alignItemsVertically();
    
    addChild( menu );
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sprite = CCSprite::create(s_pPathGrossini);
    addChild(sprite);
    sprite->setPosition( ccp(s.width-40, s.height/2) );
    CCActionInterval* rotate = CCRotateBy::create(2, 360);
    CCAction* repeat = CCRepeatForever::create(rotate);
    sprite->runAction(repeat);

    schedule( schedule_selector(SceneTestLayer1::testDealloc) );
}

void SceneTestLayer1::testDealloc(float dt)
{
    //CCLOG("SceneTestLayer1:testDealloc");
}

void SceneTestLayer1::onEnter()
{
    CCLOG("SceneTestLayer1#onEnter");
    CCLayer::onEnter();
}

void SceneTestLayer1::onEnterTransitionDidFinish()
{
    CCLOG("SceneTestLayer1#onEnterTransitionDidFinish");
    CCLayer::onEnterTransitionDidFinish();
}

SceneTestLayer1::~SceneTestLayer1()
{
    //NSLog(@"SceneTestLayer1 - dealloc");
}

void SceneTestLayer1::onPushScene(CCObject* pSender)
{
    CCScene* scene = new SceneTestScene();
    CCLayer* pLayer = new SceneTestLayer2();
    scene->addChild( pLayer, 0 );
    CCDirector::sharedDirector()->pushScene( scene );
    scene->release();
    pLayer->release();
}

void SceneTestLayer1::onPushSceneTran(CCObject* pSender)
{
    CCScene* scene = new SceneTestScene();
    CCLayer* pLayer = new SceneTestLayer2();
    scene->addChild( pLayer, 0 );

    CCDirector::sharedDirector()->pushScene( CCTransitionSlideInT::create(1, scene) );
    scene->release();
    pLayer->release();
}


void SceneTestLayer1::onQuit(CCObject* pSender)
{
    //getCocosApp()->exit();
    //CCDirector::sharedDirector()->popScene();

    //// HA HA... no more terminate on sdk v3.0
    //// http://developer.apple.com/iphone/library/qa/qa2008/qa1561.html
    //if( [[UIApplication sharedApplication] respondsToSelector:@selector(terminate)] )
    //    [[UIApplication sharedApplication] performSelector:@selector(terminate)];
}

//------------------------------------------------------------------
//
// SceneTestLayer2
//
//------------------------------------------------------------------

SceneTestLayer2::SceneTestLayer2()
{
    _timeCounter = 0;

    CCMenuItemFont* item1 = CCMenuItemFont::create( "replaceScene", CC_CALLBACK_1(SceneTestLayer2::onReplaceScene, this));
    CCMenuItemFont* item2 = CCMenuItemFont::create( "replaceScene w/transition", CC_CALLBACK_1(SceneTestLayer2::onReplaceSceneTran, this));
    CCMenuItemFont* item3 = CCMenuItemFont::create( "Go Back", CC_CALLBACK_1(SceneTestLayer2::onGoBack, this));
    
    CCMenu* menu = CCMenu::create( item1, item2, item3, NULL );
    menu->alignItemsVertically();
    
    addChild( menu );

    CCSize s = CCDirector::sharedDirector()->getWinSize();
    CCSprite* sprite = CCSprite::create(s_pPathGrossini);
    addChild(sprite);
    sprite->setPosition( ccp(s.width-40, s.height/2) );
    CCActionInterval* rotate = CCRotateBy::create(2, 360);
    CCAction* repeat = CCRepeatForever::create(rotate);
    sprite->runAction(repeat);

    schedule( schedule_selector(SceneTestLayer2::testDealloc) );
}

void SceneTestLayer2::testDealloc(float dt)
{
    //_timeCounter += dt;
    //if( _timeCounter > 10 )
    //    onReplaceScene(this);
}

void SceneTestLayer2::onGoBack(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void SceneTestLayer2::onReplaceScene(CCObject* pSender)
{
    CCScene* pScene = new SceneTestScene();
    CCLayer* pLayer = SceneTestLayer3::create();
    pScene->addChild( pLayer, 0 );
    CCDirector::sharedDirector()->replaceScene( pScene );
    pScene->release();
}


void SceneTestLayer2::onReplaceSceneTran(CCObject* pSender)
{
    CCScene* pScene = new SceneTestScene();
    CCLayer* pLayer = SceneTestLayer3::create();
    pScene->addChild( pLayer, 0 );
    CCDirector::sharedDirector()->replaceScene( CCTransitionFlipX::create(2, pScene) );
    pScene->release();
}

//------------------------------------------------------------------
//
// SceneTestLayer3
//
//------------------------------------------------------------------

SceneTestLayer3::SceneTestLayer3()
{

}

bool SceneTestLayer3::init()
{
    if (CCLayerColor::initWithColor(ccc4(0,0,255,255)))
    {
        CCSize s = CCDirector::sharedDirector()->getWinSize();

        CCMenuItemFont *item0 = CCMenuItemFont::create("Touch to pushScene (self)", CC_CALLBACK_1(SceneTestLayer3::item0Clicked, this));
        CCMenuItemFont *item1 = CCMenuItemFont::create("Touch to popScene", CC_CALLBACK_1(SceneTestLayer3::item1Clicked, this));
        CCMenuItemFont *item2 = CCMenuItemFont::create("Touch to popToRootScene", CC_CALLBACK_1(SceneTestLayer3::item2Clicked, this));
        CCMenuItemFont *item3 = CCMenuItemFont::create("Touch to popToSceneStackLevel(2)", CC_CALLBACK_1(SceneTestLayer3::item3Clicked, this));

        CCMenu *menu = CCMenu::create(item0, item1, item2, item3, NULL);
        this->addChild(menu);
        menu->alignItemsVertically();

        this->schedule(schedule_selector(SceneTestLayer3::testDealloc));

        CCSprite* sprite = CCSprite::create(s_pPathGrossini);
        addChild(sprite);
        sprite->setPosition( ccp(s.width/2, 40) );
        CCActionInterval* rotate = CCRotateBy::create(2, 360);
        CCAction* repeat = CCRepeatForever::create(rotate);
        sprite->runAction(repeat);
        return true;
    }
    return false;
}

void SceneTestLayer3::testDealloc(float dt)
{
    CCLog("Layer3:testDealloc");
}

void SceneTestLayer3::item0Clicked(CCObject* pSender)
{
    CCScene *newScene = CCScene::create();
    newScene->addChild(SceneTestLayer3::create());
    CCDirector::sharedDirector()->pushScene(CCTransitionFade::create(0.5, newScene, ccc3(0,255,255)));
}

void SceneTestLayer3::item1Clicked(CCObject* pSender)
{
    CCDirector::sharedDirector()->popScene();
}

void SceneTestLayer3::item2Clicked(CCObject* pSender)
{
    CCDirector::sharedDirector()->popToRootScene();
}

void SceneTestLayer3::item3Clicked(CCObject* pSender)
{
    CCDirector::sharedDirector()->popToSceneStackLevel(2);
}

void SceneTestScene::runThisTest()
{
    CCLayer* pLayer = new SceneTestLayer1();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
