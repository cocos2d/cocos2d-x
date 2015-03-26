#include "MouseTest.h"

template <typename T> std::string tostr(const T& t) { std::ostringstream os; os<<t; return os.str(); }

static int sceneIdx = -1;


static std::function<Layer*()> createFunctions[] =
{
    CL(MouseEventTest),
    CL(HideMouseTest)
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextSpriteTestAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* backSpriteTestAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}

static Layer* restartSpriteTestAction()
{
    auto layer = (createFunctions[sceneIdx])();
    return layer;
}


//------------------------------------------------------------------
//
// BaseMouseTest
//
//------------------------------------------------------------------

BaseMouseTest::BaseMouseTest(void)
: BaseTest()
{
}

BaseMouseTest::~BaseMouseTest(void)
{
}

std::string BaseMouseTest::title() const
{
    return "No title";
}

std::string BaseMouseTest::subtitle() const
{
    return "";
}

void BaseMouseTest::onEnter()
{
    BaseTest::onEnter();
}

void BaseMouseTest::restartCallback(Ref* sender)
{
    auto s = new (std::nothrow) MouseTestScene();
    s->addChild(restartSpriteTestAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseMouseTest::nextCallback(Ref* sender)
{
    auto s = new (std::nothrow) MouseTestScene();
    s->addChild( nextSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseMouseTest::backCallback(Ref* sender)
{
    auto s = new (std::nothrow) MouseTestScene();
    s->addChild( backSpriteTestAction() );
    Director::getInstance()->replaceScene(s);
    s->release();
}

void MouseTestScene::runThisTest()
{
    auto layer = nextSpriteTestAction();
    addChild(layer);
    
    Director::getInstance()->replaceScene(this);
}

//------------------------------------------------------------------
//
// MouseEventTest
//
//------------------------------------------------------------------
MouseEventTest::MouseEventTest()
{
    auto s = Director::getInstance()->getWinSize();

    //Create a label to display the mouse action
    _labelAction = Label::createWithTTF("Click mouse button and see this change", "fonts/arial.ttf", 22);
    _labelAction->setPosition(Vec2(s.width/2, s.height*2/3));
    addChild(_labelAction, 0);

    //Create a label to display the mouse position
    _labelPosition = Label::createWithTTF("Mouse not supported on this device", "fonts/arial.ttf", 22);
    _labelPosition->setPosition(Vec2(s.width/2, s.height/3));
    addChild(_labelPosition);


    _mouseListener = EventListenerMouse::create();
    _mouseListener->onMouseMove = CC_CALLBACK_1(MouseEventTest::onMouseMove, this);
    _mouseListener->onMouseUp = CC_CALLBACK_1(MouseEventTest::onMouseUp, this);
    _mouseListener->onMouseDown = CC_CALLBACK_1(MouseEventTest::onMouseDown, this);
    _mouseListener->onMouseScroll = CC_CALLBACK_1(MouseEventTest::onMouseScroll, this);

    _eventDispatcher->addEventListenerWithSceneGraphPriority(_mouseListener, this);
}

MouseEventTest::~MouseEventTest()
{
    _eventDispatcher->removeEventListener(_mouseListener);
}

void MouseEventTest::onMouseDown(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Down detected, Key: ";
    str += tostr(e->getMouseButton());
    _labelAction->setString(str.c_str());
}

void MouseEventTest::onMouseUp(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Up detected, Key: ";
    str += tostr(e->getMouseButton());
    _labelAction->setString(str.c_str());
}

void MouseEventTest::onMouseMove(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "MousePosition X:";
    str = str + tostr(e->getCursorX()) + " Y:" + tostr(e->getCursorY());
    _labelPosition->setString(str.c_str());
}

void MouseEventTest::onMouseScroll(Event *event)
{
    EventMouse* e = (EventMouse*)event;
    std::string str = "Mouse Scroll detected, X: ";
    str = str + tostr(e->getScrollX()) + " Y: " + tostr(e->getScrollY());
    _labelAction->setString(str.c_str());
}

std::string MouseEventTest::title() const
{
    return "Mouse Event Test";
}

std::string MouseEventTest::subtitle() const
{
    return "This tests the mouse events";
}

//------------------------------------------------------------------
//
// HideMouseTest
//
//------------------------------------------------------------------

HideMouseTest::HideMouseTest()
{
    
    _lis = EventListenerMouse::create();
    _lis->onMouseDown = [](Event* e){
        Director::getInstance()->getOpenGLView()->setCursorVisible(false);
    };
    
    _lis->onMouseUp = [](Event* e){
        Director::getInstance()->getOpenGLView()->setCursorVisible(true);
    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(_lis, this);
}

HideMouseTest::~HideMouseTest()
{
    _eventDispatcher->removeEventListener(_lis);
}

std::string HideMouseTest::title() const
{
    return "Hide/Show Mouse";
}

std::string HideMouseTest::subtitle() const
{
    return "Click to hide mouse";
}

