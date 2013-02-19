#include "DrawPrimitivesTest.h"

using namespace std;

static int sceneIdx = -1;


CCLayer* nextSpriteTestAction();
CCLayer* backSpriteTestAction();
CCLayer* restartSpriteTestAction();

typedef CCLayer* (*NEWDRAWPRIMITIVESFUNC)();
#define DRAWPRIMITIVES_CREATE_FUNC(className) \
static CCLayer* create##className() \
{ return new className(); }

DRAWPRIMITIVES_CREATE_FUNC(DrawPrimitivesTest);
DRAWPRIMITIVES_CREATE_FUNC(DrawNodeTest);

static NEWDRAWPRIMITIVESFUNC createFunctions[] =
{
    createDrawPrimitivesTest,
    createDrawNodeTest,
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static CCLayer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();
    
    return pLayer;
}

static CCLayer* restartAction()
{
    CCLayer* pLayer = (createFunctions[sceneIdx])();
    pLayer->autorelease();
    
    return pLayer;
}

// BaseLayer

BaseLayer::BaseLayer()
{
    
}

void BaseLayer::onEnter()
{
    CCLayer::onEnter();
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLabelTTF *label = CCLabelTTF::create(title().c_str(), "Arial", 32);
    addChild(label);
    label->setPosition(ccp(s.width/2, s.height-50));
    
    string subTitle = subtitle();
    if (subTitle.size() > 0)
    {
        CCLabelTTF *l = CCLabelTTF::create(subTitle.c_str(), "Thonburi", 16);
        addChild(l, 1);
        l->setPosition(ccp(s.width/2, s.height-80));
    }
    
    CCMenuItemImage *item1 = CCMenuItemImage::create("Images/b1.png", "Images/b2.png", this, menu_selector(BaseLayer::backCallback));
    CCMenuItemImage *item2 = CCMenuItemImage::create("Images/r1.png", "Images/r2.png", this, menu_selector(BaseLayer::restartCallback));
    CCMenuItemImage *item3 = CCMenuItemImage::create("Images/f1.png", "Images/f2.png", this, menu_selector(BaseLayer::nextCallback));
    
    CCMenu *menu = CCMenu::create(item1, item2, item3, NULL);
    menu->setPosition(CCPointZero);
    
    item1->setPosition(ccp(s.width/2 - item2->getContentSize().width*2, item2->getContentSize().height/2));
    item2->setPosition(ccp(s.width/2, item2->getContentSize().height/2));
    item3->setPosition(ccp(s.width/2 + item2->getContentSize().width*2, item2->getContentSize().height/2));
    addChild(menu, 100);
}

void BaseLayer::restartCallback(cocos2d::CCObject *pSender)
{
    CCScene *s = new DrawPrimitivesTestScene();
    s->addChild(restartAction());
    
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void BaseLayer::nextCallback(cocos2d::CCObject *pSender)
{
    CCScene *s = new DrawPrimitivesTestScene();;
    s->addChild(nextAction());
    
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

void BaseLayer::backCallback(cocos2d::CCObject *pSender)
{
    CCScene *s = new DrawPrimitivesTestScene();
    s->addChild(backAction());
    
    CCDirector::sharedDirector()->replaceScene(s);
    s->release();
}

string BaseLayer::title()
{
    return "No title";
}

string BaseLayer::subtitle()
{
    return "";
}

// DrawPrimitivesTest

DrawPrimitivesTest::DrawPrimitivesTest()
{
}

void DrawPrimitivesTest::draw()
{
    
	CHECK_GL_ERROR_DEBUG();
    
	// draw a simple line
	// The default state is:
	// Line Width: 1
	// color: 255,255,255,255 (white, non-transparent)
	// Anti-Aliased
    //	glEnable(GL_LINE_SMOOTH);
    ccDrawLine( VisibleRect::leftBottom(), VisibleRect::rightTop() );
    
	CHECK_GL_ERROR_DEBUG();
    
	// line: color, width, aliased
	// glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
	// GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
    //	glDisable(GL_LINE_SMOOTH);
	glLineWidth( 5.0f );
	ccDrawColor4B(255,0,0,255);
    ccDrawLine( VisibleRect::leftTop(), VisibleRect::rightBottom() );
    
	CHECK_GL_ERROR_DEBUG();
    
	// TIP:
	// If you are going to use always the same color or width, you don't
	// need to call it before every draw
	//
	// Remember: OpenGL is a state-machine.
    
	// draw big point in the center
	ccPointSize(64);
	ccDrawColor4B(0,0,255,128);
    ccDrawPoint( VisibleRect::center() );
    
	CHECK_GL_ERROR_DEBUG();
    
	// draw 4 small points
	CCPoint points[] = { ccp(60,60), ccp(70,70), ccp(60,70), ccp(70,60) };
	ccPointSize(4);
	ccDrawColor4B(0,255,255,255);
	ccDrawPoints( points, 4);
    
	CHECK_GL_ERROR_DEBUG();
    
	// draw a green circle with 10 segments
	glLineWidth(16);
	ccDrawColor4B(0, 255, 0, 255);
    ccDrawCircle( VisibleRect::center(), 100, 0, 10, false);
    
	CHECK_GL_ERROR_DEBUG();
    
	// draw a green circle with 50 segments with line to center
	glLineWidth(2);
	ccDrawColor4B(0, 255, 255, 255);
    ccDrawCircle( VisibleRect::center(), 50, CC_DEGREES_TO_RADIANS(90), 50, true);
    
	CHECK_GL_ERROR_DEBUG();
    
	// open yellow poly
	ccDrawColor4B(255, 255, 0, 255);
	glLineWidth(10);
	CCPoint vertices[] = { ccp(0,0), ccp(50,50), ccp(100,50), ccp(100,100), ccp(50,100) };
	ccDrawPoly( vertices, 5, false);
    
	CHECK_GL_ERROR_DEBUG();
	
	// filled poly
	glLineWidth(1);
	CCPoint filledVertices[] = { ccp(0,120), ccp(50,120), ccp(50,170), ccp(25,200), ccp(0,170) };
	ccDrawSolidPoly(filledVertices, 5, ccc4f(0.5f, 0.5f, 1, 1 ) );
    
    
	// closed purble poly
	ccDrawColor4B(255, 0, 255, 255);
	glLineWidth(2);
	CCPoint vertices2[] = { ccp(30,130), ccp(30,230), ccp(50,200) };
	ccDrawPoly( vertices2, 3, true);
    
	CHECK_GL_ERROR_DEBUG();
    
	// draw quad bezier path
    ccDrawQuadBezier(VisibleRect::leftTop(), VisibleRect::center(), VisibleRect::rightTop(), 50);
    
	CHECK_GL_ERROR_DEBUG();
    
	// draw cubic bezier path
    ccDrawCubicBezier(VisibleRect::center(), ccp(VisibleRect::center().x+30,VisibleRect::center().y+50), ccp(VisibleRect::center().x+60,VisibleRect::center().y-50),VisibleRect::right(),100);
    
	CHECK_GL_ERROR_DEBUG();
    
    //draw a solid polygon
	CCPoint vertices3[] = {ccp(60,160), ccp(70,190), ccp(100,190), ccp(90,160)};
    ccDrawSolidPoly( vertices3, 4, ccc4f(1,1,0,1) );
    
	// restore original values
	glLineWidth(1);
	ccDrawColor4B(255,255,255,255);
	ccPointSize(1);
    
	CHECK_GL_ERROR_DEBUG();
}

string DrawPrimitivesTest::title()
{
    return "draw primitives";
}

string DrawPrimitivesTest::subtitle()
{
    return "Drawing Primitives. Use CCDrawNode instead";
}

// DrawNodeTest
DrawNodeTest::DrawNodeTest()
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCDrawNode *draw = CCDrawNode::create();
    addChild(draw, 10);
    
    // Draw 10 circles
    for( int i=0; i < 10; i++)
    {
        draw->drawDot(ccp(s.width/2, s.height/2), 10*(10-i), ccc4f(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    
    // Draw polygons
    CCPoint points[] = { CCPoint(s.height/4,0), CCPoint(s.width,s.height/5), CCPoint(s.width/3*2,s.height) };
    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), ccc4f(1,0,0,0.5), 4, ccc4f(0,0,1,1));
    
    // star poly (triggers buggs)
    {
        const float o=80;
        const float w=20;
        const float h=50;
        CCPoint star[] = {
            CCPoint(o+w,o-h), CCPoint(o+w*2, o),						// lower spike
            CCPoint(o + w*2 + h, o+w ), CCPoint(o + w*2, o+w*2),		// right spike
            //				{o +w, o+w*2+h}, {o,o+w*2},					// top spike
            //				{o -h, o+w}, {o,o},							// left spike
        };
        
        draw->drawPolygon(star, sizeof(star)/sizeof(star[0]), ccc4f(1,0,0,0.5), 1, ccc4f(0,0,1,1));
    }
    
    // star poly (doesn't trigger bug... order is important un tesselation is supported.
    {
        const float o=180;
        const float w=20;
        const float h=50;
        CCPoint star[] = {
            CCPoint(o,o), CCPoint(o+w,o-h), CCPoint(o+w*2, o),		// lower spike
            CCPoint(o + w*2 + h, o+w ), CCPoint(o + w*2, o+w*2),	// right spike
            CCPoint(o +w, o+w*2+h), CCPoint(o,o+w*2),				// top spike
            CCPoint(o -h, o+w),                                     // left spike
        };
        
        draw->drawPolygon(star, sizeof(star)/sizeof(star[0]), ccc4f(1,0,0,0.5), 1, ccc4f(0,0,1,1));
    }
    
    
    // Draw segment
    draw->drawSegment(ccp(20,s.height), ccp(20,s.height/2), 10, ccc4f(0, 1, 0, 1));

    draw->drawSegment(ccp(10,s.height/2), ccp(s.width/2, s.height/2), 40, ccc4f(1, 0, 1, 0.5));
}

string DrawNodeTest::title()
{
    return "Test CCDrawNode";
}

string DrawNodeTest::subtitle()
{
    return "Testing DrawNode - batched draws. Concave polygons are BROKEN";
}

void DrawPrimitivesTestScene::runThisTest()
{
    CCLayer* pLayer = nextAction();
    addChild(pLayer);

    CCDirector::sharedDirector()->replaceScene(this);
}
