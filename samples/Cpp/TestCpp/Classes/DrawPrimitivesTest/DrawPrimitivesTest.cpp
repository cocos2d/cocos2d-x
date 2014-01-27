#include "DrawPrimitivesTest.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

using namespace std;

static int sceneIdx = -1;


Layer* nextSpriteTestAction();
Layer* backSpriteTestAction();
Layer* restartSpriteTestAction();

typedef Layer* (*NEWDRAWPRIMITIVESFUNC)();
#define DRAWPRIMITIVES_CREATE_FUNC(className) \
static Layer* create##className() \
{ return new className(); }

DRAWPRIMITIVES_CREATE_FUNC(DrawPrimitivesTest);
DRAWPRIMITIVES_CREATE_FUNC(DrawNodeTest);

static NEWDRAWPRIMITIVESFUNC createFunctions[] =
{
    createDrawPrimitivesTest,
    createDrawNodeTest,
};

#define MAX_LAYER    (sizeof(createFunctions) / sizeof(createFunctions[0]))

static Layer* nextAction()
{
    sceneIdx++;
    sceneIdx = sceneIdx % MAX_LAYER;
    
    auto layer = (createFunctions[sceneIdx])();
    layer->autorelease();
    
    return layer;
}

static Layer* backAction()
{
    sceneIdx--;
    int total = MAX_LAYER;
    if( sceneIdx < 0 )
        sceneIdx += total;
    
    auto layer = (createFunctions[sceneIdx])();
    layer->autorelease();
    
    return layer;
}

static Layer* restartAction()
{
    auto layer = (createFunctions[sceneIdx])();
    layer->autorelease();
    
    return layer;
}

// BaseLayer

BaseLayer::BaseLayer()
{
    
}

void BaseLayer::onEnter()
{
    BaseTest::onEnter();
}

void BaseLayer::restartCallback(cocos2d::Object *pSender)
{
    auto s = new DrawPrimitivesTestScene();
    s->addChild(restartAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseLayer::nextCallback(cocos2d::Object *pSender)
{
    auto s = new DrawPrimitivesTestScene();;
    s->addChild(nextAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

void BaseLayer::backCallback(cocos2d::Object *pSender)
{
    auto s = new DrawPrimitivesTestScene();
    s->addChild(backAction());
    
    Director::getInstance()->replaceScene(s);
    s->release();
}

string BaseLayer::title() const
{
    return "No title";
}

string BaseLayer::subtitle() const
{
    return "";
}

// DrawPrimitivesTest

DrawPrimitivesTest::DrawPrimitivesTest()
{
}

void DrawPrimitivesTest::draw()
{
    _customCommand.init(_globalZOrder);
    _customCommand.func = CC_CALLBACK_0(DrawPrimitivesTest::onDraw, this);
    Director::getInstance()->getRenderer()->addCommand(&_customCommand);
}

void DrawPrimitivesTest::onDraw()
{
    kmMat4 oldMat;
    kmGLGetMatrix(KM_GL_MODELVIEW, &oldMat);
    kmGLLoadMatrix(&_modelViewTransform);
    
    //draw
    CHECK_GL_ERROR_DEBUG();
    
    // draw a simple line
    // The default state is:
    // Line Width: 1
    // color: 255,255,255,255 (white, non-transparent)
    // Anti-Aliased
    //  glEnable(GL_LINE_SMOOTH);
    DrawPrimitives::drawLine( VisibleRect::leftBottom(), VisibleRect::rightTop() );
    
    CHECK_GL_ERROR_DEBUG();
    
    // line: color, width, aliased
    // glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
    // GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
    //  glDisable(GL_LINE_SMOOTH);
    glLineWidth( 5.0f );
    DrawPrimitives::setDrawColor4B(255,0,0,255);
    DrawPrimitives::drawLine( VisibleRect::leftTop(), VisibleRect::rightBottom() );
    
    CHECK_GL_ERROR_DEBUG();
    
    // TIP:
    // If you are going to use always thde same color or width, you don't
    // need to call it before every draw
    //
    // Remember: OpenGL is a state-machine.
    
    // draw big point in the center
    DrawPrimitives::setPointSize(64);
    DrawPrimitives::setDrawColor4B(0,0,255,128);
    DrawPrimitives::drawPoint( VisibleRect::center() );
    
    CHECK_GL_ERROR_DEBUG();
    
    // draw 4 small points
    Point points[] = { Point(60,60), Point(70,70), Point(60,70), Point(70,60) };
    DrawPrimitives::setPointSize(4);
    DrawPrimitives::setDrawColor4B(0,255,255,255);
    DrawPrimitives::drawPoints( points, 4);
    
    CHECK_GL_ERROR_DEBUG();
    
    // draw a green circle with 10 segments
    glLineWidth(16);
    DrawPrimitives::setDrawColor4B(0, 255, 0, 255);
    DrawPrimitives::drawCircle( VisibleRect::center(), 100, 0, 10, false);
    
    CHECK_GL_ERROR_DEBUG();
    
    // draw a green circle with 50 segments with line to center
    glLineWidth(2);
    DrawPrimitives::setDrawColor4B(0, 255, 255, 255);
    DrawPrimitives::drawCircle( VisibleRect::center(), 50, CC_DEGREES_TO_RADIANS(90), 50, true);
    
    CHECK_GL_ERROR_DEBUG();
    
    // draw a pink solid circle with 50 segments
    glLineWidth(2);
    DrawPrimitives::setDrawColor4B(255, 0, 255, 255);
    DrawPrimitives::drawSolidCircle( VisibleRect::center() + Point(140,0), 40, CC_DEGREES_TO_RADIANS(90), 50, 1.0f, 1.0f);
    
    CHECK_GL_ERROR_DEBUG();
    
    // open yellow poly
    DrawPrimitives::setDrawColor4B(255, 255, 0, 255);
    glLineWidth(10);
    Point vertices[] = { Point(0,0), Point(50,50), Point(100,50), Point(100,100), Point(50,100) };
    DrawPrimitives::drawPoly( vertices, 5, false);
    
    CHECK_GL_ERROR_DEBUG();
    
    // filled poly
    glLineWidth(1);
    Point filledVertices[] = { Point(0,120), Point(50,120), Point(50,170), Point(25,200), Point(0,170) };
    DrawPrimitives::drawSolidPoly(filledVertices, 5, Color4F(0.5f, 0.5f, 1, 1 ) );
    
    
    // closed purble poly
    DrawPrimitives::setDrawColor4B(255, 0, 255, 255);
    glLineWidth(2);
    Point vertices2[] = { Point(30,130), Point(30,230), Point(50,200) };
    DrawPrimitives::drawPoly( vertices2, 3, true);
    
    CHECK_GL_ERROR_DEBUG();
    
    // draw quad bezier path
    DrawPrimitives::drawQuadBezier(VisibleRect::leftTop(), VisibleRect::center(), VisibleRect::rightTop(), 50);
    
    CHECK_GL_ERROR_DEBUG();
    
    // draw cubic bezier path
    DrawPrimitives::drawCubicBezier(VisibleRect::center(), Point(VisibleRect::center().x+30,VisibleRect::center().y+50), Point(VisibleRect::center().x+60,VisibleRect::center().y-50),VisibleRect::right(),100);
    
    CHECK_GL_ERROR_DEBUG();
    
    //draw a solid polygon
    Point vertices3[] = {Point(60,160), Point(70,190), Point(100,190), Point(90,160)};
    DrawPrimitives::drawSolidPoly( vertices3, 4, Color4F(1,1,0,1) );
    
    // restore original values
    glLineWidth(1);
    DrawPrimitives::setDrawColor4B(255,255,255,255);
    DrawPrimitives::setPointSize(1);
    
    CHECK_GL_ERROR_DEBUG();
    
    //end draw
    kmGLLoadMatrix(&oldMat);
}

string DrawPrimitivesTest::title() const
{
    return "draw primitives";
}

string DrawPrimitivesTest::subtitle() const
{
    return "Drawing Primitives. Use DrawNode instead";
}

// DrawNodeTest
DrawNodeTest::DrawNodeTest()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto draw = DrawNode::create();
    addChild(draw, 10);
    
    // Draw 10 circles
    for( int i=0; i < 10; i++)
    {
        draw->drawDot(Point(s.width/2, s.height/2), 10*(10-i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    
    // Draw polygons
    Point points[] = { Point(s.height/4,0), Point(s.width,s.height/5), Point(s.width/3*2,s.height) };
    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 4, Color4F(0,0,1,1));
    
    // star poly (triggers buggs)
    {
        const float o=80;
        const float w=20;
        const float h=50;
        Point star[] = {
            Point(o+w,o-h), Point(o+w*2, o),                        // lower spike
            Point(o + w*2 + h, o+w ), Point(o + w*2, o+w*2),        // right spike
            //              {o +w, o+w*2+h}, {o,o+w*2},                 // top spike
            //              {o -h, o+w}, {o,o},                         // left spike
        };
        
        draw->drawPolygon(star, sizeof(star)/sizeof(star[0]), Color4F(1,0,0,0.5), 1, Color4F(0,0,1,1));
    }
    
    // star poly (doesn't trigger bug... order is important un tesselation is supported.
    {
        const float o=180;
        const float w=20;
        const float h=50;
        Point star[] = {
            Point(o,o), Point(o+w,o-h), Point(o+w*2, o),        // lower spike
            Point(o + w*2 + h, o+w ), Point(o + w*2, o+w*2),    // right spike
            Point(o +w, o+w*2+h), Point(o,o+w*2),               // top spike
            Point(o -h, o+w),                                     // left spike
        };
        
        draw->drawPolygon(star, sizeof(star)/sizeof(star[0]), Color4F(1,0,0,0.5), 1, Color4F(0,0,1,1));
    }
    
    
    // Draw segment
    draw->drawSegment(Point(20,s.height), Point(20,s.height/2), 10, Color4F(0, 1, 0, 1));

    draw->drawSegment(Point(10,s.height/2), Point(s.width/2, s.height/2), 40, Color4F(1, 0, 1, 0.5));

	// Draw triangle
    draw->drawTriangle(Point(10, 10), Point(70, 30), Point(100, 140), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
	
	// Draw some beziers
    draw->drawQuadraticBezier(Point(s.width - 150, s.height - 150), Point(s.width - 70, s.height - 10), Point(s.width - 10, s.height - 10), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));

    draw->drawCubicBezier(Point(s.width - 250, 40), Point(s.width - 70, 100), Point(s.width - 30, 250), Point(s.width - 10, s.height - 50), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
}

string DrawNodeTest::title() const
{
    return "Test DrawNode";
}

string DrawNodeTest::subtitle() const
{
    return "Testing DrawNode - batched draws. Concave polygons are BROKEN";
}

void DrawPrimitivesTestScene::runThisTest()
{
    auto layer = nextAction();
    addChild(layer);

    Director::getInstance()->replaceScene(this);
}
