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
    MenuLayer* pLayer = new MenuLayer();
    pLayer->initWithEntryID(entryId);
    pLayer->autorelease();

    return pLayer;
}

bool MenuLayer::initWithEntryID(int entryId)
{
    CCDirector* pDirector = CCDirector::sharedDirector();
	CCPoint visibleOrigin = pDirector->getVisibleOrigin();
	CCSize visibleSize = pDirector->getVisibleSize();

    m_entryID = entryId;
    
    setTouchEnabled( true );
    
    Box2DView* view = Box2DView::viewWithEntryID( entryId );
    addChild(view, 0, kTagBox2DNode);
    view->setScale(15);
    view->setAnchorPoint( ccp(0,0) );
    view->setPosition( ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height/3) );
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_MARMALADE)
//    CCLabelBMFont* label = CCLabelBMFont::create(view->title().c_str(),  "fonts/arial16.fnt");
//#else    
    CCLabelTTF* label = CCLabelTTF::create(view->title().c_str(), "Arial", 28);
//#endif
    addChild(label, 1);
    label->setPosition( ccp(visibleOrigin.x+visibleSize.width/2, visibleOrigin.y+visibleSize.height-50) );

    CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(MenuLayer::backCallback) );
    CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png","Images/r2.png", this, menu_selector(MenuLayer::restartCallback) );
    CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(MenuLayer::nextCallback) );

    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);

    menu->setPosition( CCPointZero );
    item1->setPosition(ccp(VisibleRect::center().x - item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item2->setPosition(ccp(VisibleRect::center().x, VisibleRect::bottom().y+item2->getContentSize().height/2));
    item3->setPosition(ccp(VisibleRect::center().x + item2->getContentSize().width*2, VisibleRect::bottom().y+item2->getContentSize().height/2));
    
    addChild(menu, 1);    

    return true;
}

void MenuLayer::restartCallback(CCObject* sender)
{
    CCScene* s = new Box2dTestBedScene();
    MenuLayer* box = MenuLayer::menuWithEntryID(m_entryID);
    s->addChild( box );
    CCDirector::sharedDirector()->replaceScene( s );
    s->release();
}

void MenuLayer::nextCallback(CCObject* sender)
{
    CCScene* s = new Box2dTestBedScene();
    int next = m_entryID + 1;
    if( next >= g_totalEntries)
        next = 0;
    MenuLayer* box = MenuLayer::menuWithEntryID(next);
    s->addChild( box );
    CCDirector::sharedDirector()->replaceScene( s );
    s->release();
}

void MenuLayer::backCallback(CCObject* sender)
{
    CCScene* s = new Box2dTestBedScene();
    int next = m_entryID - 1;
    if( next < 0 ) {
        next = g_totalEntries - 1;
    }
    
    MenuLayer* box = MenuLayer::menuWithEntryID(next);

    s->addChild( box );
    CCDirector::sharedDirector()->replaceScene( s );
    s->release();
}

void MenuLayer::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

bool MenuLayer::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    return true;
}

//-(void) MenuLayer::ccTouchEnded:(UITouch *)touch withEvent:(CCEvent *)event
//{
//}
//
//-(void) MenuLayer::ccTouchCancelled:(UITouch *)touch withEvent:(CCEvent *)event
//{
//}

void MenuLayer::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint diff = touch->getDelta();    
    CCNode *node = getChildByTag( kTagBox2DNode );
    CCPoint currentPos = node->getPosition();
    node->setPosition( ccpAdd(currentPos, diff) );
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
    CCLayer::draw();

    ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );

    kmGLPushMatrix();

    m_test->m_world->DrawDebugData();

    kmGLPopMatrix();

    CHECK_GL_ERROR_DEBUG();
}

Box2DView::~Box2DView()
{
    delete m_test;
}

void Box2DView::registerWithTouchDispatcher()
{
    // higher priority than dragging
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, -10, true);
}

bool Box2DView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
    CCPoint touchLocation = touch->getLocation();    

    CCPoint nodePosition = convertToNodeSpace( touchLocation );
//    NSLog(@"pos: %f,%f -> %f,%f", touchLocation.x, touchLocation.y, nodePosition.x, nodePosition.y);

    return m_test->MouseDown(b2Vec2(nodePosition.x,nodePosition.y));    
}

void Box2DView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
    CCPoint touchLocation = touch->getLocation();    
    CCPoint nodePosition = convertToNodeSpace( touchLocation );
    
    m_test->MouseMove(b2Vec2(nodePosition.x,nodePosition.y));        
}

void Box2DView::ccTouchEnded(CCTouch* touch, CCEvent* event)
{
    CCPoint touchLocation = touch->getLocation();    
    CCPoint nodePosition = convertToNodeSpace( touchLocation );
    
    m_test->MouseUp(b2Vec2(nodePosition.x,nodePosition.y));
}

// void Box2DView::accelerometer(UIAccelerometer* accelerometer, CCAcceleration* acceleration)
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

    CCDirector::sharedDirector()->replaceScene(this);
}
