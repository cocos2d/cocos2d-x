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
 *
 * LEGACY FUNCTIONS
 *
 * USE DrawNode instead
 *
 */


#ifndef __CCDRAWING_PRIMITIVES__
#define __CCDRAWING_PRIMITIVES__
    

#include "base/ccTypes.h"
#include "base/ccMacros.h"
#include "math/CCMath.h"

/**
 @file
 绘制OpenGL ES原语。
 - drawPoint, drawPoints
 - drawLine
 - drawRect, drawSolidRect
 - drawPoly, drawSolidPoly
 - drawCircle
 - drawQuadBezier
 - drawCubicBezier
 - drawCatmullRom
 - drawCardinalSpline
 
 你可以通过以下函数来改变颜色点的大小：
 - drawColor4B(), drawColor4F()
 - ccPointSize()
 - glLineWidth()
 
 @警告 这些函数在绘制线、Vec2、多边形的时候是立即执行的。他们并不是批处理的。如果你要用这些原语函数来做游戏，我建议你建立一个批处理来完成。你应该使用DrawNode来代替。
 
 */

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

class PointArray;

namespace DrawPrimitives
{
    /** 初始化绘图原语 */
    void init();

    /** 释放绘制原语时所分配的资源 */
    void free();

    /** 给定x、y值绘制一个点。其中x、y使用像素来度量*/
    void drawPoint( const Vec2& point );

    /** 绘制一组点s.
     @since v0.7.2
     */
    void drawPoints( const Vec2 *points, unsigned int numberOfPoints );

    /** 给定起始点与终止点绘制一条线，其中起始点与终止点坐标使用像素来度量 */
    void drawLine( const Vec2& origin, const Vec2& destination );

    /** 给定起始点与终止点绘制一个矩形，其中起始点与终止点坐标使用像素来度量  */
    void drawRect( Vec2 origin, Vec2 destination );

    /** 给定起始点与终止点绘制一个实体矩形，其中起始点与终止点坐标使用像素来度量。
        @since 1.1
     */
    void drawSolidRect( Vec2 origin, Vec2 destination, Color4F color );

    /** 给定一个指向点坐标的指针以及顶点数目绘制一个多边形。其中每个点的坐标使用像素来度量。
    这个多边形可以是封闭的也可以是打开的。
    */
    void drawPoly( const Vec2 *vertices, unsigned int numOfVertices, bool closePolygon );

    /** 给定一个指向点坐标的指针以及顶点数目以及颜色绘制一个实体多边形。其中每个点的坐标使用像素来度量。
     */
    void drawSolidPoly( const Vec2 *poli, unsigned int numberOfPoints, Color4F color );

    /** 给定中心点、半径、分段数来绘制一个圆。 */
    void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
    void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);

    /** 给定中心点、半径、分段数来绘制一个实体圆。 */
    void drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY);
    void drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments);

    /** 绘制一个quad贝塞尔曲线
     @warning 这个函数使用起来可能非常慢。一般只用来做调试使用.
     @since v0.8
     */
    void drawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments);

    /** 绘制一个cubic贝塞尔曲线
     @warning 这个函数使用起来可能非常慢。一般只用来做调试使用.
     @since v0.8
     */
    void drawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);

    /** 绘制一个Catmull-Rom样条曲线.
     @warning This function could be pretty slow. Use it only for debugging purposes.
     @since v2.0
     */
    void drawCatmullRom( PointArray *arrayOfControlPoints, unsigned int segments );

    /** 绘制一个Cardinal样条曲线.
     @warning 这个函数使用起来可能非常慢。一般只用来做调试使用.
     @since v2.0
     */
    void drawCardinalSpline( PointArray *config, float tension,  unsigned int segments );

    /** 用4个无符号比特值来设置绘图颜色
     @since v2.0
     */
    void setDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a );

    /** 用4个浮点值来设置绘图颜色
     @since v2.0
     */
    void setDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a );

    /** 设置点的像素大小。默认为 1。
     @since v2.0
     */
    void setPointSize( GLfloat pointSize );

};

// end of global group
/// @}

NS_CC_END

#endif // __CCDRAWING_PRIMITIVES__
