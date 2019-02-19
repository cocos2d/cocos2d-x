/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "DrawPrimitivesTest.h"
#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

USING_NS_CC;

using namespace std;

DrawPrimitivesTests::DrawPrimitivesTests()
{
    ADD_TEST_CASE(DrawNodeTest);
    ADD_TEST_CASE(Issue11942Test);
}

string DrawPrimitivesBaseTest::title() const
{
    return "No title";
}

// DrawNodeTest
DrawNodeTest::DrawNodeTest()
{
    auto s = Director::getInstance()->getWinSize();
    
    auto draw = DrawNode::create();
    addChild(draw, 10);
    
    draw->drawPoint(Vec2(s.width/2-120, s.height/2-120), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    draw->drawPoint(Vec2(s.width/2+120, s.height/2+120), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    // draw 4 small points
    Vec2 position[] = { Vec2(60,60), Vec2(70,70), Vec2(60,70), Vec2(70,60) };
    draw->drawPoints( position, 4, 5, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
 
    // draw a line
    draw->drawLine(Vec2(0,0), Vec2(s.width, s.height), Color4F(1.0, 0.0, 0.0, 0.5));
    
    // draw a rectangle
    draw->drawRect(Vec2(23,23), Vec2(7,7), Color4F(1,1,0,1));
    
    draw->drawRect(Vec2(15,30), Vec2(30,15), Vec2(15,0), Vec2(0,15), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    // draw a circle
    draw->drawCircle(VisibleRect::center() + Vec2(140,0), 100, CC_DEGREES_TO_RADIANS(90), 50, true, 1.0f, 2.0f, Color4F(1.0, 0.0, 0.0, 0.5));
    
    draw->drawCircle(VisibleRect::center() - Vec2(140,0), 50, CC_DEGREES_TO_RADIANS(90), 30, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

    // Draw some beziers
    draw->drawQuadBezier(Vec2(s.width - 150, s.height - 150), Vec2(s.width - 70, s.height - 10), Vec2(s.width - 10, s.height - 10), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    draw->drawQuadBezier(Vec2(0, s.height), Vec2(s.width/2, s.height/2), Vec2(s.width, s.height), 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    draw->drawCubicBezier(VisibleRect::center(), Vec2(VisibleRect::center().x+30,VisibleRect::center().y+50), Vec2(VisibleRect::center().x+60,VisibleRect::center().y-50),VisibleRect::right(),100, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    draw->drawCubicBezier(Vec2(s.width - 250, 40), Vec2(s.width - 70, 100), Vec2(s.width - 30, 250), Vec2(s.width - 10, s.height - 50), 10, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    auto array = PointArray::create(20);
    array->addControlPoint(Vec2(0,0));
    array->addControlPoint(Vec2(80,80));
    array->addControlPoint(Vec2(s.width-80,80));
    array->addControlPoint(Vec2(s.width-80,s.height-80));
    array->addControlPoint(Vec2(80,s.height-80));
    array->addControlPoint(Vec2(80,80));
    array->addControlPoint(Vec2(s.width/2, s.height/2));
    draw->drawCardinalSpline(array, 0.5, 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    auto array2 = PointArray::create(20);
    array2->addControlPoint(Vec2(s.width / 2, 30));
    array2->addControlPoint(Vec2(s.width  -80, 30));
    array2->addControlPoint(Vec2(s.width - 80, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, s.height - 80));
    array2->addControlPoint(Vec2(s.width / 2, 30));
    draw->drawCatmullRom(array2, 50, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    // open random color poly
    Vec2 vertices[] = { Vec2(0,0), Vec2(50,50), Vec2(100,50), Vec2(100,100), Vec2(50,100) };
    draw->drawPoly( vertices, 5, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    // closed random color poly
    Vec2 vertices2[] = { Vec2(30,130), Vec2(30,230), Vec2(50,200) };
    draw->drawPoly( vertices2, 3, true, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    // Draw 10 circles
    for( int i=0; i < 10; i++)
    {
        draw->drawDot(Vec2(s.width/2, s.height/2), 10*(10-i), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }
    
    // Draw polygons
    Vec2 points[] = { Vec2(s.height/4,0), Vec2(s.width,s.height/5), Vec2(s.width/3*2,s.height) };
    draw->drawPolygon(points, sizeof(points)/sizeof(points[0]), Color4F(1,0,0,0.5), 4, Color4F(0,0,1,0.5));
    
    // star poly (triggers buggs)
    {
        const float o=80;
        const float w=20;
        const float h=50;
        Vec2 star[] = {
            Vec2(o+w,o-h), Vec2(o+w*2, o),                        // lower spike
            Vec2(o + w*2 + h, o+w ), Vec2(o + w*2, o+w*2),        // right spike
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
        Vec2 star[] = {
            Vec2(o,o), Vec2(o+w,o-h), Vec2(o+w*2, o),        // lower spike
            Vec2(o + w*2 + h, o+w ), Vec2(o + w*2, o+w*2),    // right spike
            Vec2(o +w, o+w*2+h), Vec2(o,o+w*2),               // top spike
            Vec2(o -h, o+w),                                     // left spike
        };
        
        draw->drawPolygon(star, sizeof(star)/sizeof(star[0]), Color4F(1,0,0,0.5), 1, Color4F(0,0,1,1));
    }
    
    //draw a solid polygon
    Vec2 vertices3[] = {Vec2(60,160), Vec2(70,190), Vec2(100,190), Vec2(90,160)};
    draw->drawSolidPoly( vertices3, 4, Color4F(1,1,0,1) );
    
    //draw a solid rectangle
    draw->drawSolidRect(Vec2(10,10), Vec2(20,20), Color4F(1,1,0,1));
    
    //draw a solid circle
    draw->drawSolidCircle( VisibleRect::center() + Vec2(140,0), 40, CC_DEGREES_TO_RADIANS(90), 50, 2.0f, 2.0f, Color4F(0.0, 1.0, 0.0, 1.0));
    
    // Draw segment
    draw->drawSegment(Vec2(20,s.height), Vec2(20,s.height/2), 10, Color4F(0, 1, 0, 1));
    
    draw->drawSegment(Vec2(10,s.height/2), Vec2(s.width/2, s.height/2), 40, Color4F(1, 0, 1, 0.5));

    // Draw triangle
    draw->drawTriangle(Vec2(10, 10), Vec2(70, 30), Vec2(100, 140), Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 0.5));
    
    for (int i = 0; i < 100; i++) {
        draw->drawPoint(Vec2(i*7, 5), (float)i/5+1, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    }

    auto draw1 = DrawNode::create();
    this->addChild(draw1, 10);
    draw1->setLineWidth(4);
    draw1->drawLine(Vec2(0, s.height), Vec2(s.width, s.height - 20), Color4F::YELLOW);
    draw1->drawLine(Vec2(0, 0), Vec2(s.width, s.height - 20), Color4F::YELLOW);

    draw->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2),FadeOut::create(1.2), NULL)));
    draw1->runAction(RepeatForever::create(Sequence::create(FadeIn::create(1.2),FadeOut::create(1.2), NULL)));
}

string DrawNodeTest::title() const
{
    return "Test DrawNode";
}

string DrawNodeTest::subtitle() const
{
    return "Testing DrawNode - batched draws. Concave polygons are BROKEN";
}

//
// Issue11942Test
//
Issue11942Test::Issue11942Test()
{
    auto draw = DrawNode::create();
    addChild(draw, 10);

    // draw a circle
    draw->setLineWidth(1);
    draw->drawCircle(VisibleRect::center() - Vec2(140,0), 50, CC_DEGREES_TO_RADIANS(90), 30, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    draw->setLineWidth(10);
    draw->drawCircle(VisibleRect::center() + Vec2(140,0), 50, CC_DEGREES_TO_RADIANS(90), 30, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
}

string Issue11942Test::title() const
{
    return "GitHub Issue #11942";
}

string Issue11942Test::subtitle() const
{
    return "drawCircle() with width";
}
