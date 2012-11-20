#include "DrawPrimitivesTest.h"

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
    //    glEnable(GL_LINE_SMOOTH);
    ccDrawLine( VisibleRect::leftBottom(), VisibleRect::rightTop() );

    CHECK_GL_ERROR_DEBUG();

    // line: color, width, aliased
    // glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
    // GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
    //    glDisable(GL_LINE_SMOOTH);
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

void DrawPrimitivesTestScene::runThisTest()
{
    CCLayer* pLayer = new DrawPrimitivesTest();
    addChild(pLayer);
    pLayer->release();

    CCDirector::sharedDirector()->replaceScene(this);
}
