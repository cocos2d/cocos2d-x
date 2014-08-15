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
    auto item1 = MenuItemFont::create( "Test pushScene", CC_CALLBACK_1(SceneTestLayer1::onPushScene, this));
    auto item2 = MenuItemFont::create( "Test pushScene w/transition", CC_CALLBACK_1(SceneTestLayer1::onPushSceneTran, this));
    auto item3 = MenuItemFont::create( "Quit", CC_CALLBACK_1(SceneTestLayer1::onQuit, this));
    
    auto menu = Menu::create( item1, item2, item3, nullptr );
    menu->alignItemsVertically();
    
    addChild( menu );
    
    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create(s_pathGrossini);
    addChild(sprite);
    sprite->setPosition( Vec2(s.width-40, s.height/2) );
    auto rotate = RotateBy::create(2, 360);
    auto repeat = RepeatForever::create(rotate);
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

void SceneTestLayer1::onPushScene(Ref* sender)
{
    auto scene = new SceneTestScene();
    auto layer = new SceneTestLayer2();
    scene->addChild( layer, 0 );
    Director::getInstance()->pushScene( scene );
    scene->release();
    layer->release();
}

void SceneTestLayer1::onPushSceneTran(Ref* sender)
{
    auto scene = new SceneTestScene();
    auto layer = new SceneTestLayer2();
    scene->addChild( layer, 0 );

    Director::getInstance()->pushScene( TransitionSlideInT::create(1, scene) );
    scene->release();
    layer->release();
}


void SceneTestLayer1::onQuit(Ref* sender)
{
    //getCocosApp()->exit();
    //CCDirector::getInstance()->poscene();

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

    auto item1 = MenuItemFont::create( "replaceScene", CC_CALLBACK_1(SceneTestLayer2::onReplaceScene, this));
    auto item2 = MenuItemFont::create( "replaceScene w/transition", CC_CALLBACK_1(SceneTestLayer2::onReplaceSceneTran, this));
    auto item3 = MenuItemFont::create( "Go Back", CC_CALLBACK_1(SceneTestLayer2::onGoBack, this));
    
    auto menu = Menu::create( item1, item2, item3, nullptr );
    menu->alignItemsVertically();
    
    addChild( menu );

    auto s = Director::getInstance()->getWinSize();
    auto sprite = Sprite::create(s_pathGrossini);
    addChild(sprite);
    sprite->setPosition( Vec2(s.width-40, s.height/2) );
    auto rotate = RotateBy::create(2, 360);
    auto repeat = RepeatForever::create(rotate);
    sprite->runAction(repeat);

    schedule( schedule_selector(SceneTestLayer2::testDealloc) );
}

void SceneTestLayer2::testDealloc(float dt)
{
    //_timeCounter += dt;
    //if( _timeCounter > 10 )
    //    onReplaceScene(this);
}

void SceneTestLayer2::onGoBack(Ref* sender)
{
    Director::getInstance()->popScene();
}

void SceneTestLayer2::onReplaceScene(Ref* sender)
{
    auto scene = new SceneTestScene();
    auto layer = SceneTestLayer3::create();
    scene->addChild( layer, 0 );
    Director::getInstance()->replaceScene( scene );
    scene->release();
}


void SceneTestLayer2::onReplaceSceneTran(Ref* sender)
{
    auto scene = new SceneTestScene();
    auto layer = SceneTestLayer3::create();
    scene->addChild( layer, 0 );
    Director::getInstance()->replaceScene( TransitionFlipX::create(2, scene) );
    scene->release();
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
    if (LayerColor::initWithColor(Color4B(0,0,255,255)))
    {
        auto s = Director::getInstance()->getWinSize();

        auto item0 = MenuItemFont::create("Touch to pushScene (self)", CC_CALLBACK_1(SceneTestLayer3::item0Clicked, this));
        auto item1 = MenuItemFont::create("Touch to poscene", CC_CALLBACK_1(SceneTestLayer3::item1Clicked, this));
        auto item2 = MenuItemFont::create("Touch to popToRootScene", CC_CALLBACK_1(SceneTestLayer3::item2Clicked, this));
        auto item3 = MenuItemFont::create("Touch to popToSceneStackLevel(2)", CC_CALLBACK_1(SceneTestLayer3::item3Clicked, this));

        auto menu = Menu::create(item0, item1, item2, item3, nullptr);
        this->addChild(menu);
        menu->alignItemsVertically();

        this->schedule(schedule_selector(SceneTestLayer3::testDealloc));

        auto sprite = Sprite::create(s_pathGrossini);
        addChild(sprite);
        sprite->setPosition( Vec2(s.width/2, 40) );
        auto rotate = RotateBy::create(2, 360);
        auto repeat = RepeatForever::create(rotate);
        sprite->runAction(repeat);
        return true;
    }
    return false;
}

void SceneTestLayer3::testDealloc(float dt)
{
    log("Layer3:testDealloc");
}

void SceneTestLayer3::item0Clicked(Ref* sender)
{
    auto s = Director::getInstance()->getWinSize();
    auto newScene = Scene::createWithSize(s);
    newScene->addChild(SceneTestLayer3::create());
    Director::getInstance()->pushScene(TransitionFade::create(0.5, newScene, Color3B(0,255,255)));
}

void SceneTestLayer3::item1Clicked(Ref* sender)
{
    Director::getInstance()->popScene();
}

void SceneTestLayer3::item2Clicked(Ref* sender)
{
    Director::getInstance()->popToRootScene();
}

void SceneTestLayer3::item3Clicked(Ref* sender)
{
    Director::getInstance()->popToSceneStackLevel(2);
}

void SceneTestScene::runThisTest()
{
    auto layer = new SceneTestLayer1();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}
