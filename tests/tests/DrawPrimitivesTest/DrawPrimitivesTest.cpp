#include "DrawPrimitivesTest.h"

DrawPrimitivesTest::DrawPrimitivesTest()
{
}

void DrawPrimitivesTest::draw()
{
	CCSize s = CCDirector::sharedDirector()->getWinSize();

	CHECK_GL_ERROR_DEBUG();

	// draw a simple line
	// The default state is:
	// Line Width: 1
	// color: 255,255,255,255 (white, non-transparent)
	// Anti-Aliased
	//	glEnable(GL_LINE_SMOOTH);
	ccDrawLine( ccp(0, 0), ccp(s.width, s.height) );

	CHECK_GL_ERROR_DEBUG();

	// line: color, width, aliased
	// glLineWidth > 1 and GL_LINE_SMOOTH are not compatible
	// GL_SMOOTH_LINE_WIDTH_RANGE = (1,1) on iPhone
	//	glDisable(GL_LINE_SMOOTH);
	glLineWidth( 5.0f );
	ccDrawColor4B(255,0,0,255);
	ccDrawLine( ccp(0, s.height), ccp(s.width, 0) );

	CHECK_GL_ERROR_DEBUG();

	// TIP:
	// If you are going to use always the same color or width, you don't
	// need to call it before every draw
	//
	// Remember: OpenGL is a state-machine.

	// draw big point in the center
	ccPointSize(64);
	ccDrawColor4B(0,0,255,128);
	ccDrawPoint( ccp(s.width / 2, s.height / 2) );

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
	ccDrawCircle( ccp(s.width/2,  s.height/2), 100, 0, 10, false);

	CHECK_GL_ERROR_DEBUG();

	// draw a green circle with 50 segments with line to center
	glLineWidth(2);
	ccDrawColor4B(0, 255, 255, 255);
	ccDrawCircle( ccp(s.width/2, s.height/2), 50, CC_DEGREES_TO_RADIANS(90), 50, true);

	CHECK_GL_ERROR_DEBUG();

	// open yellow poly
	ccDrawColor4B(255, 255, 0, 255);
	glLineWidth(10);
	CCPoint vertices[] = { ccp(0,0), ccp(50,50), ccp(100,50), ccp(100,100), ccp(50,100) };
	ccDrawPoly( vertices, 5, false);

	CHECK_GL_ERROR_DEBUG();

	// closed purble poly
	ccDrawColor4B(255, 0, 255, 255);
	glLineWidth(2);
	CCPoint vertices2[] = { ccp(30,130), ccp(30,230), ccp(50,200) };
	ccDrawPoly( vertices2, 3, true);

	CHECK_GL_ERROR_DEBUG();

	// draw quad bezier path
	ccDrawQuadBezier(ccp(0,s.height), ccp(s.width/2,s.height/2), ccp(s.width,s.height), 50);

	CHECK_GL_ERROR_DEBUG();

	// draw cubic bezier path
	ccDrawCubicBezier(ccp(s.width/2, s.height/2), ccp(s.width/2+30,s.height/2+50), ccp(s.width/2+60,s.height/2-50),ccp(s.width, s.height/2),100);

	CHECK_GL_ERROR_DEBUG();

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
