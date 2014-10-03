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

#include "TransitionsTest.h"
#include "../testResource.h"

#define TRANSITION_DURATION (1.2f)

class FadeWhiteTransition : public TransitionFade 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFade::create(t, s, Color3B::WHITE); 
    }
};

class FlipXLeftOver : public TransitionFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER);
    }
};

class FlipXRightOver : public TransitionFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
    }
};

class FlipYUpOver : public TransitionFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipY::create(t, s, TransitionScene::Orientation::UP_OVER); 
    }
};

class FlipYDownOver : public TransitionFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER); 
    }
};

class FlipAngularLeftOver : public TransitionFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER); 
    }
};

class FlipAngularRightOver : public TransitionFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
    }
};

class ZoomFlipXLeftOver : public TransitionZoomFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::LEFT_OVER); 
    }
};

class ZoomFlipXRightOver : public TransitionZoomFlipX 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipX::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
    }
};

class ZoomFlipYUpOver : public TransitionZoomFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::UP_OVER); 

    }
};

class ZoomFlipYDownOver : public TransitionZoomFlipY 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipY::create(t, s, TransitionScene::Orientation::DOWN_OVER); 
    }
};

class ZoomFlipAngularLeftOver : public TransitionZoomFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::LEFT_OVER); 
    }
};

class ZoomFlipAngularRightOver : public TransitionZoomFlipAngular 
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionZoomFlipAngular::create(t, s, TransitionScene::Orientation::RIGHT_OVER);
    }
};

class PageTransitionForward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionPageTurn::create(t, s, false);
    }
};

class PageTransitionBackward : public TransitionPageTurn
{
public:
    static TransitionScene* create(float t, Scene* s)
    {
        return TransitionPageTurn::create(t, s, true);
    }
};

#define STRINGIFY(x) #x

#define TRANS(__className__) {                                      \
    [](float t, Scene* s){ return __className__::create(t,s);},     \
        STRINGIFY(__className__),                                   \
    }
struct _transitions {
    std::function<TransitionScene*(float t, Scene* s)> function;
    const char * name;
} transitions[] = {
    TRANS(TransitionJumpZoom),
    TRANS(TransitionProgressRadialCCW),
    TRANS(TransitionProgressRadialCW),
    TRANS(TransitionProgressHorizontal),
    TRANS(TransitionProgressVertical),
    TRANS(TransitionProgressInOut),
    TRANS(TransitionProgressOutIn),

    TRANS(TransitionCrossFade),

    TRANS(PageTransitionForward),
    TRANS(PageTransitionBackward),
    TRANS(TransitionFadeTR),
    TRANS(TransitionFadeBL),
    TRANS(TransitionFadeUp),
    TRANS(TransitionFadeDown),

    TRANS(TransitionTurnOffTiles),

    TRANS(TransitionSplitRows),
    TRANS(TransitionSplitCols),

    TRANS(TransitionFade),
    TRANS(FadeWhiteTransition),

    TRANS(FlipXLeftOver),
    TRANS(FlipXRightOver),
    TRANS(FlipYUpOver),
    TRANS(FlipYDownOver),
    TRANS(FlipAngularLeftOver),
    TRANS(FlipAngularRightOver),

    TRANS(ZoomFlipXLeftOver),
    TRANS(ZoomFlipXRightOver),
    TRANS(ZoomFlipYUpOver),
    TRANS(ZoomFlipYDownOver),
    TRANS(ZoomFlipAngularLeftOver),
    TRANS(ZoomFlipAngularRightOver),

    TRANS(TransitionShrinkGrow),
    TRANS(TransitionRotoZoom),

    TRANS(TransitionMoveInL),
    TRANS(TransitionMoveInR),
    TRANS(TransitionMoveInT),
    TRANS(TransitionMoveInB),

    TRANS(TransitionSlideInL),
    TRANS(TransitionSlideInR),
    TRANS(TransitionSlideInT),
    TRANS(TransitionSlideInB),
};


#define MAX_LAYER (sizeof(transitions) / sizeof(transitions[0]))


static int s_nSceneIdx = 0;

TransitionScene* createTransition(int index, float t, Scene* s)
{
    // fix bug #486, without setDepthTest(false), FlipX,Y will flickers
    Director::getInstance()->setDepthTest(false);

    return transitions[index].function(t,s);
}


void TransitionsTestScene::runThisTest()
{
    auto layer = new (std::nothrow) TestLayer1();
    addChild(layer);
    layer->release();

    Director::getInstance()->replaceScene(this);
}

TestLayer1::TestLayer1(void)
{
    float x,y;

    auto size = Director::getInstance()->getWinSize();
    x = size.width;
    y = size.height;

    auto bg1 = Sprite::create(s_back1);
    bg1->setPosition( Vec2(size.width/2, size.height/2) );
    addChild(bg1, -1);

    auto title = Label::createWithTTF( (transitions[s_nSceneIdx]).name, "fonts/Thonburi.ttf", 32 );
    addChild(title);
    title->setColor( Color3B(255,32,32) );
    title->setPosition( Vec2(x/2, y-100) );

    auto label = Label::createWithTTF("SCENE 1", "fonts/Marker Felt.ttf", 38);
    label->setColor( Color3B(16,16,255));
    label->setPosition( Vec2(x/2,y/2));    
    addChild( label);

    // menu
    auto item1 = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(TestLayer1::backCallback, this) );
    auto item2 = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(TestLayer1::restartCallback, this) );
    auto item3 = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(TestLayer1::nextCallback, this) );

    auto menu = Menu::create(item1, item2, item3, nullptr);

    menu->setPosition( Vec2::ZERO );
    item1->setPosition(Vec2(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(Vec2(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);    

    schedule( CC_SCHEDULE_SELECTOR(TestLayer1::step), 1.0f); 
}

TestLayer1::~TestLayer1(void)
{

}

void TestLayer1::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) TransitionsTestScene();

    auto layer = new (std::nothrow) TestLayer2();
    s->addChild(layer);

    auto scene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    layer->release();
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }    
}

void TestLayer1::nextCallback(Ref* sender)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    auto s = new (std::nothrow) TransitionsTestScene();

    auto layer = new (std::nothrow) TestLayer2();
    s->addChild(layer);

    auto scene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    layer->release();
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void TestLayer1::backCallback(Ref* sender)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;    

    auto s = new (std::nothrow) TransitionsTestScene();

    auto layer = new (std::nothrow) TestLayer2();
    s->addChild(layer);

    auto scene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    layer->release();
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void TestLayer1::step(float dt)
{

}

void TestLayer1::onEnter()
{
    Layer::onEnter();
    log("Scene 1 onEnter");
}

void TestLayer1::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("Scene 1: onEnterTransitionDidFinish");
}

void TestLayer1::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    log("Scene 1: onExitTransitionDidStart");
}

void TestLayer1::onExit()
{
    Layer::onExit();
    Director::getInstance()->setDepthTest(false);
    log("Scene 1 onExit");
}

TestLayer2::TestLayer2()
{
    float x,y;

    auto size = Director::getInstance()->getWinSize();
    x = size.width;
    y = size.height;

    auto bg1 = Sprite::create(s_back2);
    bg1->setPosition( Vec2(size.width/2, size.height/2) );
    addChild(bg1, -1);

    auto title = Label::createWithTTF((transitions[s_nSceneIdx]).name, "fonts/Thonburi.ttf", 32 );
    addChild(title);
    title->setColor( Color3B(255,32,32) );
    title->setPosition( Vec2(x/2, y-100) );

    auto label = Label::createWithTTF("SCENE 2", "fonts/Marker Felt.ttf", 38);
    label->setColor( Color3B(16,16,255));
    label->setPosition( Vec2(x/2,y/2));    
    addChild( label);

    // menu
    auto item1 = MenuItemImage::create(s_pathB1, s_pathB2, CC_CALLBACK_1(TestLayer2::backCallback, this) );
    auto item2 = MenuItemImage::create(s_pathR1, s_pathR2, CC_CALLBACK_1(TestLayer2::restartCallback, this) );
    auto item3 = MenuItemImage::create(s_pathF1, s_pathF2, CC_CALLBACK_1(TestLayer2::nextCallback, this) );

    auto menu = Menu::create(item1, item2, item3, nullptr);

    menu->setPosition( Vec2::ZERO );
    item1->setPosition(Vec2(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(Vec2(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(Vec2(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));

    addChild(menu, 1);    

    schedule(CC_SCHEDULE_SELECTOR(TestLayer2::step), 1.0f);
}

TestLayer2::~TestLayer2()
{

}

void TestLayer2::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) TransitionsTestScene();

    auto layer = new (std::nothrow) TestLayer1();
    s->addChild(layer);

    auto scene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    layer->release();
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void TestLayer2::nextCallback(Ref* sender)
{
    s_nSceneIdx++;
    s_nSceneIdx = s_nSceneIdx % MAX_LAYER;

    auto s = new (std::nothrow) TransitionsTestScene();

    auto layer = new (std::nothrow) TestLayer1();
    s->addChild(layer);

    auto scene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    layer->release();
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void TestLayer2::backCallback(Ref* sender)
{
    s_nSceneIdx--;
    int total = MAX_LAYER;
    if( s_nSceneIdx < 0 )
        s_nSceneIdx += total;    

    auto s = new (std::nothrow) TransitionsTestScene();

    auto layer = new (std::nothrow) TestLayer1();
    s->addChild(layer);

    auto scene = createTransition(s_nSceneIdx, TRANSITION_DURATION, s);
    s->release();
    layer->release();
    if (scene)
    {
        Director::getInstance()->replaceScene(scene);
    }
}

void TestLayer2::step(float dt)
{

}

void TestLayer2::onEnter()
{
    Layer::onEnter();
    log("Scene 2 onEnter");
}

void TestLayer2::onEnterTransitionDidFinish()
{
    Layer::onEnterTransitionDidFinish();
    log("Scene 2: onEnterTransitionDidFinish");
}

void TestLayer2::onExitTransitionDidStart()
{
    Layer::onExitTransitionDidStart();
    log("Scene 2: onExitTransitionDidStart");
}

void TestLayer2::onExit()
{
    Layer::onExit();
    Director::getInstance()->setDepthTest(false);
    log("Scene 2 onExit");
}
