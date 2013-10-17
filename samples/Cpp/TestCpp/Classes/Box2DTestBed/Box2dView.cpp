#include "Box2dView.h"
#include "GLES-Render.h"
#include "Test.h"

#define kAccelerometerFrequency 30
#define FRAMES_BETWEEN_PRESSES_FOR_DOUBLE_CLICK 10

extern int g_totalEntries;

Settings settings;

enum 
{
    kTagBox2DNode,
}; 


//------------------------------------------------------------------
//
// MenuLayer
//
//------------------------------------------------------------------
enum
{
    IDC_NEXT = 100,
    IDC_BACK,
    IDC_RESTART
};

MenuLayer::MenuLayer(void)
{
}

MenuLayer::~MenuLayer(void)
{
}

MenuLayer* MenuLayer::menuWithEntryID(int entryId)
{
    auto layer = new MenuLayer();
    layer->initWithEntryID(entryId);
    layer->autorelease();

    return layer;
}

bool MenuLayer::initWithEntryID(int entryId)
{
    auto director = Director::getInstance();
	Point visibleOrigin = director->getVisibleOrigin();
	Size visibleSize = director->getVisibleSize();

    m_entryID = entryId;
    
    setTouchEnabled( true );
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    Box2DView* view = Box2DView::viewWithEntryID( entryId );
    addChild(view, 0, kTagBox2DNode);
    view->setScale(15);
    view->setAnchorPoint( Point(0,0) );
    view->setPosition( Point(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/3) );
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    auto label = LabelBMFont::create(view->title().c_str(),  "fonts/arial16.fnt");
//#else    
    auto label = LabelTTF::create(view->title().c_str(), "Arial", 28);
//#endif
    addChild(label, 1);
    label->setPosition( Point(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height-50) );

    auto item1 = MenuItemImage::create("Images/b1.png", "Images/b2.png", CC_CALLBACK_1(MenuLayer::backCallback, this) );
    auto item2 = MenuItemImage::create("Images/r1.png","Images/r2.png", CC_CALLBACK_1( MenuLayer::restartCallback, this) );
    auto item3 = MenuItemImage::create("Images/f1.png", "Images/f2.png", CC_CALLBACK_1(MenuLayer::nextCallback, this) );

    auto menu = Menu::create(item1, item2, item3, NULL);

    menu->setPosition( Point::ZERO );
    item1->setPosition(Point(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(Point(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(Point(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);
    
    // Removes touch event listener
    EventDispatcher::getInstance()->removeEventListener(_touchListener);
    
    // Adds touch event listener
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);

    listener->onTouchBegan = CC_CALLBACK_2(MenuLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(MenuLayer::onTouchMoved, this);

    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, 1);
    _touchListener = listener;
    return true;
}

void MenuLayer::restartCallback(Object* sender)
{
    auto s = new Box2dTestBedScene();
    auto box = MenuLayer::menuWithEntryID(m_entryID);
    s->addChild( box );
    Director::getInstance()->replaceScene( s );
    s->release();
}

void MenuLayer::nextCallback(Object* sender)
{
    auto s = new Box2dTestBedScene();
    int next = m_entryID + 1;
    if( next >= g_totalEntries)
        next = 0;
    auto box = MenuLayer::menuWithEntryID(next);
    s->addChild( box );
    Director::getInstance()->replaceScene( s );
    s->release();
}

void MenuLayer::backCallback(Object* sender)
{
    auto s = new Box2dTestBedScene();
    int next = m_entryID - 1;
    if( next < 0 ) {
        next = g_totalEntries - 1;
    }
    
    auto box = MenuLayer::menuWithEntryID(next);

    s->addChild( box );
    Director::getInstance()->replaceScene( s );
    s->release();
}

//void MenuLayer::registerWithTouchDispatcher()
//{
//    auto director = Director::getInstance();
//    director->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
//}

bool MenuLayer::onTouchBegan(Touch* touch, Event* event)
{
    return true;
}

//-(void) MenuLayer::ccTouchEnded:(UITouch *)touch withEvent:(Event *)event
//{
//}
//
//-(void) MenuLayer::ccTouchCancelled:(UITouch *)touch withEvent:(Event *)event
//{
//}

void MenuLayer::onTouchMoved(Touch* touch, Event* event)
{
    auto diff = touch->getDelta();    
    auto node = getChildByTag( kTagBox2DNode );
    auto currentPos = node->getPosition();
    node->setPosition(currentPos + diff);
}

//------------------------------------------------------------------
//
// Box2DView
//
//------------------------------------------------------------------
Box2DView::Box2DView(void)
{
}

Box2DView* Box2DView::viewWithEntryID(int entryId)
{
    Box2DView* pView = new Box2DView();
    pView->initWithEntryID(entryId);
    pView->autorelease();

    return pView;
}

bool Box2DView::initWithEntryID(int entryId)
{    
//    setIsAccelerometerEnabled( true );
    setTouchEnabled( true );
    
    schedule( schedule_selector(Box2DView::tick) );

    m_entry = g_testEntries + entryId;
    m_test = m_entry->createFcn();
    setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
    
    // Removes Touch Event Listener
    EventDispatcher::getInstance()->removeEventListener(_touchListener);
    
    // Adds Touch Event Listener
    auto listener = EventListenerTouch::create(Touch::DispatchMode::ONE_BY_ONE);
    listener->setSwallowTouches(true);
    
    listener->onTouchBegan = CC_CALLBACK_2(Box2DView::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(Box2DView::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(Box2DView::onTouchEnded, this);
    
    EventDispatcher::getInstance()->addEventListenerWithFixedPriority(listener, -10);
    _touchListener = listener;
    
    return true;
}

std::string Box2DView::title()
{
    return std::string(m_entry->name);
}

void Box2DView::tick(float dt)
{
    m_test->Step(&settings);
}

void Box2DView::draw()
{
    Layer::draw();

    GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );

    kmGLPushMatrix();

    m_test->m_world->DrawDebugData();

    kmGLPopMatrix();

    CHECK_GL_ERROR_DEBUG();
}

Box2DView::~Box2DView()
{
    delete m_test;
}
//
//void Box2DView::registerWithTouchDispatcher()
//{
//    // higher priority than dragging
//    auto director = Director::getInstance();
//    director->getTouchDispatcher()->addTargetedDelegate(this, -10, true);
//}

bool Box2DView::onTouchBegan(Touch* touch, Event* event)
{
    auto touchLocation = touch->getLocation();    

    auto nodePosition = convertToNodeSpace( touchLocation );
    log("Box2DView::onTouchBegan, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

    return m_test->MouseDown(b2Vec2(nodePosition.x,nodePosition.y));    
}

void Box2DView::onTouchMoved(Touch* touch, Event* event)
{
    auto touchLocation = touch->getLocation();    
    auto nodePosition = convertToNodeSpace( touchLocation );
    
    log("Box2DView::onTouchMoved, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);
    
    m_test->MouseMove(b2Vec2(nodePosition.x,nodePosition.y));        
}

void Box2DView::onTouchEnded(Touch* touch, Event* event)
{
    auto touchLocation = touch->getLocation();    
    auto nodePosition = convertToNodeSpace( touchLocation );
    
    log("Box2DView::onTouchEnded, pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);
    
    m_test->MouseUp(b2Vec2(nodePosition.x,nodePosition.y));
}

// void Box2DView::accelerometer(UIAccelerometer* accelerometer, Acceleration* acceleration)
// {
//     //// Only run for valid values
//     //if (acceleration.y!=0 && acceleration.x!=0)
//     //{
//     //    if (test) test->SetGravity((float)-acceleration.y,(float)acceleration.x);
//     //}
// } 


void Box2dTestBedScene::runThisTest()
{
    addChild(MenuLayer::menuWithEntryID(0));

    Director::getInstance()->replaceScene(this);
}
