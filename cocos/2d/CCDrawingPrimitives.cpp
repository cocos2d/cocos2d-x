/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
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

/*
 *
 * IMPORTANT       IMPORTANT        IMPORTANT        IMPORTANT
*
 * LEGACY FUNCTIONS
 *
 * USE DrawNode instead
 *
 */

#include "2d/CCDrawingPrimitives.h"
#include "2d/CCDrawNode.h"
#include "base/CCDirector.h"

NS_CC_BEGIN

namespace DrawPrimitives
{
static Color4F s_color(1.0f,1.0f,1.0f,1.0f);
static float s_pointSize = 1.0f;
static DrawNode* s_drawNode = nullptr;
    
static void lazy_init()
{
    if (nullptr == s_drawNode)
    {
        s_drawNode = DrawNode::create();
        s_drawNode->retain();
    }
}

// When switching from backround to foreground on android, we want the params to be initialized again
void init()
{
    lazy_init();
}

void free()
{
    CC_SAFE_RELEASE_NULL(s_drawNode);
}

void drawPoint(const Vec2& point)
{
    lazy_init();
    s_drawNode->drawPoint(point, s_pointSize, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawPoints(const Vec2* points, unsigned int numberOfPoints)
{
    lazy_init();
    s_drawNode->drawPoints(points, numberOfPoints, s_color, s_pointSize);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawLine(const Vec2& origin, const Vec2& destination)
{
    lazy_init();
    s_drawNode->drawLine(origin, destination, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawRect( Vec2 origin, Vec2 destination )
{
    drawLine(Vec2(origin.x, origin.y), Vec2(destination.x, origin.y));
    drawLine(Vec2(destination.x, origin.y), Vec2(destination.x, destination.y));
    drawLine(Vec2(destination.x, destination.y), Vec2(origin.x, destination.y));
    drawLine(Vec2(origin.x, destination.y), Vec2(origin.x, origin.y));
}

void drawSolidRect(Vec2 origin, Vec2 destination, Color4F color)
{
    Vec2 vertices[] = {
        origin,
        Vec2(destination.x, origin.y),
        destination,
        Vec2(origin.x, destination.y)
    };

    drawSolidPoly(vertices, 4, color );
}

void drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon)
{
    lazy_init();
    s_drawNode->drawPoly(poli, numberOfPoints, closePolygon, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}
    
void drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, Color4F color)
{
    lazy_init();
    s_drawNode->drawSolidPoly(poli, numberOfPoints, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY)
{
    lazy_init();
    s_drawNode->drawCircle(center, radius, angle, segments, drawLineToCenter, scaleX, scaleY, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter)
{
    drawCircle(center, radius, angle, segments, drawLineToCenter, 1.0f, 1.0f);
}

void drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY)
{
    lazy_init();
    s_drawNode->drawSolidCircle(center, radius, angle, segments, scaleX, scaleY, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments)
{
    drawSolidCircle(center, radius, angle, segments, 1.0f, 1.0f);
}

void drawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments)
{
    lazy_init();
    s_drawNode->drawQuadBezier(origin, control, destination, segments, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawCatmullRom( PointArray *points, unsigned int segments )
{
    drawCardinalSpline( points, 0.5f, segments );
}

void drawCardinalSpline(PointArray* config, float tension, unsigned int segments )
{
    lazy_init();
    s_drawNode->drawCardinalSpline(config, tension, segments, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void drawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments)
{
    lazy_init();
    s_drawNode->drawCubicBezier(origin, control1, control2, destination, segments, s_color);
    s_drawNode->drawImmediate(Director::getInstance()->getRenderer(), Mat4(), 0);
    s_drawNode->clear();
}

void setDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
    s_color.r = r;
    s_color.g = g;
    s_color.b = b;
    s_color.a = a;
}

void setPointSize( GLfloat pointSize )
{
    s_pointSize = pointSize * CC_CONTENT_SCALE_FACTOR();
}

void setDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
    s_color.r = r/255.0f;
    s_color.g = g/255.0f;
    s_color.b = b/255.0f;
    s_color.a = a/255.0f;
}

} // DrawPrimitives namespace

NS_CC_END
