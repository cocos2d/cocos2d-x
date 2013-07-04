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
    MenuItemFont* item1 = MenuItemFont::create( "Test pushScene", CC_CALLBACK_1(SceneTestLayer1::onPushScene, this));
    MenuItemFont* item2 = MenuItemFont::create( "Test pushScene w/transition", CC_CALLBACK_1(SceneTestLayer1::onPushSceneTran, this));
    MenuItemFont* item3 = MenuItemFont::create( "Quit", CC_CALLBACK_1(SceneTestLayer1::onQuit, this));
    
    Menu* menu = Menu::create( item1, item2, item3, NULL );
    menu->alignItemsVertically();
    
    addChild( menu );
    
    Size s = Director::sharedDirector()->getWinSize();
    Sprite* sprite = Sprite::create(s_pPathGrossini);
    addChild(sprite);
    sprite->setPosition( ccp(s.width-40, s.height/2) );
    ActionInterval* rotate = RotateBy::create(2, 360);
    Action* repeat = RepeatForever::create(rotate);
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
    Layer::onEnter();
}

void SceneTestLayer1::onEnterTransitionDidFinish()
{
    CCLOG("SceneTestLayer1#onEnterTransitionDidFinish");
    Layer::onEnterTransitionDidFinish();
}

SceneTestLayer1::~SceneTestLayer1()
{
    //NSLog(@"SceneTestLayer1 - dealloc");
}

void SceneTestLayer1::onPushScene(Object* pSender)
{
    Scene* scene = new SceneTestScene();
    Layer* pLayer = new SceneTestLayer2();
    scene->addChild( pLayer, 0 );
    Director::sharedDirector()->pushScene( scene );
    scene->release();
    pLayer->release();
}

void SceneTestLayer1::onPushSceneTran(Object* pSender)
{
    Scene* scene = new SceneTestScene();
    Layer* pLayer = new SceneTestLayer2();
    scene->addChild( pLayer, 0 );

    Director::sharedDirector()->pushScene( TransitionSlideInT::create(1, scene) );
    scene->release();
    pLayer->release();
}


void SceneTestLayer1::onQuit(Object* pSender)
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

    MenuItemFont* item1 = MenuItemFont::create( "replaceScene", CC_CALLBACK_1(SceneTestLayer2::onReplaceScene, this));
    MenuItemFont* item2 = MenuItemFont::create( "replaceScene w/transition", CC_CALLBACK_1(SceneTestLayer2::onReplaceSceneTran, this));
    MenuItemFont* item3 = MenuItemFont::create( "Go Back", CC_CALLBACK_1(SceneTestLayer2::onGoBack, this));
    
    Menu* menu = Menu::create( item1, item2, item3, NULL );
    menu->alignItemsVertically();
    
    addChild( menu );

    Size s = Director::sharedDirector()->getWinSize();
    Sprite* sprite = Sprite::create(s_pPathGrossini);
    addChild(sprite);
    sprite->setPosition( ccp(s.width-40, s.height/2) );
    ActionInterval* rotate = RotateBy::create(2, 360);
    Action* repeat = RepeatForever::create(rotate);
    sprite->runAction(repeat);

    schedule( schedule_selector(SceneTestLayer2::testDealloc) );
}

void SceneTestLayer2::testDealloc(float dt)
{
    //_timeCounter += dt;
    //if( _timeCounter > 10 )
    //    onReplaceScene(this);
}

void SceneTestLayer2::onGoBack(Object* pSender)
{
    Director::sharedDirector()->popScene();
}

void SceneTestLayer2::onReplaceScene(Object* pSender)
{
    Scene* pScene = new SceneTestScene();
    Layer* pLayer = SceneTestLayer3::create();
    pScene->addChild( pLayer, 0 );
    Director::sharedDirector()->replaceScene( pScene );
    pScene->release();
}


void SceneTestLayer2::onReplaceSceneTran(Object* pSender)
{
    Scene* pScene = new SceneTestScene();
    Layer* pLayer = SceneTestLayer3::create();
    pScene->addChild( pLayer, 0 );
    Director::sharedDirector()->replaceScene( TransitionFlipX::create(2, pScene) );
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
    if (LayerColor::initWithColor(ccc4(0,0,255,255)))
    {
        Size s = Director::sharedDirector()->getWinSize();

        MenuItemFont *item0 = MenuItemFont::create("Touch to pushScene (self)", CC_CALLBACK_1(SceneTestLayer3::item0Clicked, this));
        MenuItemFont *item1 = MenuItemFont::create("Touch to popScene", CC_CALLBACK_1(SceneTestLayer3::item1Clicked, this));
        MenuItemFont *item2 = MenuItemFont::create("Touch to popToRootScene", CC_CALLBACK_1(SceneTestLayer3::item2Clicked, this));
        MenuItemFont *item3 = MenuItemFont::create("Touch to popToSceneStackLevel(2)", CC_CALLBACK_1(SceneTestLayer3::item3Clicked, this));

        Menu *menu = Menu::create(item0, item1, item2, item3, NULL);
        this->addChild(menu);
        menu->alignItemsVertically();

        this->schedule(schedule_selector(SceneTestLayer3::testDealloc));

        Sprite* sprite = Sprite::create(s_pPathGrossini);
        addChild(sprite);
        sprite->setPosition( ccp(s.width/2, 40) );
        ActionInterval* rotate = RotateBy::create(2, 360);
        Action* repeat = RepeatForever::create(rotate);
        sprite->runAction(repeat);
        return true;
    }
    return false;
}

void SceneTestLayer3::testDealloc(float dt)
{
    CCLog("Layer3:testDealloc");
}

void SceneTestLayer3::item0Clicked(Object* pSender)
{
    Scene *newScene = Scene::create();
    newScene->addChild(SceneTestLayer3::create());
    Director::sharedDirector()->pushScene(TransitionFade::create(0.5, newScene, ccc3(0,255,255)));
}

void SceneTestLayer3::item1Clicked(Object* pSender)
{
    Director::sharedDirector()->popScene();
}

void SceneTestLayer3::item2Clicked(Object* pSender)
{
    Director::sharedDirector()->popToRootScene();
}

void SceneTestLayer3::item3Clicked(Object* pSender)
{
    Director::sharedDirector()->popToSceneStackLevel(2);
}

void SceneTestScene::runThisTest()
{
    Layer* pLayer = new SceneTestLayer1();
    addChild(pLayer);
    pLayer->release();

    Director::sharedDirector()->replaceScene(this);
}
