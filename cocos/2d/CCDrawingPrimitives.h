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



#ifndef __CCDRAWING_PRIMITIVES__
#define __CCDRAWING_PRIMITIVES__
    

#include "base/ccTypes.h"
#include "base/ccMacros.h"
#include "math/CCMath.h"


NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

class PointArray;

/**
 @~english
 * IMPORTANT! IMPORTANT! IMPORTANT! IMPORTANT!
 *
 * LEGACY FUNCTIONS
 *
 * USE DrawNode instead
 *
 * Drawing OpenGL ES primitives.
 * - drawPoint, drawPoints
 * - drawLine
 * - drawRect, drawSolidRect
 * - drawPoly, drawSolidPoly
 * - drawCircle
 * - drawQuadBezier
 * - drawCubicBezier
 * - drawCatmullRom
 * - drawCardinalSpline

 * You can change the color, point size, width by calling:
 * - drawColor4B(), drawColor4F()
 * - ccPointSize()
 * - glLineWidth()

 * @~chinese
 *
 * 遗留功能
 *
 * 请使用DrawNode
 * 绘制OpenGL ES原生图案。
 * - drawPoint drawPoints
 * - drawLine
 * - drawRect drawSolidRect
 * - drawPoly drawSolidPoly
 * - drawCircle
 * - drawQuadBezier
 * - drawCubicBezier
 * - drawCatmullRom
 * - drawCardinalSpline
 *
 * 你可以通过调用如下函数改变颜色,大小,宽度:
 * - drawColor4B(),drawColor4F()
 * - ccPointSize()
 * - glLineWidth()
 *
 * @warning @~english These functions draws the Line, Vec2, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch. Instead you should use DrawNode
 * @~chinese 这些函数可以立即绘制线，点，多边形。它们不会采用批次处理。如果你要基于原生绘图做一个游戏,我建议创建一个批处理。或者,您应该使用DrawNode
 *
 */
namespace DrawPrimitives
{
    /**@~english
     * Initializes the drawing primitives.
     * @~chinese 
     * 初始化原生绘图。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL init();

    /**@~english
     * Frees allocated resources by the drawing primitives.
     * @~chinese 
     * 释放原生绘图分配的资源。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL free();

    /** @~english Draws a point given x and y coordinate measured in points
     *
     * @~chinese 通过给定的x，y坐标画一个点，以点为单位
     * 
     * @param point @~english A Vec2 with a point given x and y coordinate.
     * @~chinese 给定的x和y坐标。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawPoint(const Vec2& point);

    /** @~english Draws an array of points.
     *
     * @~chinese 画一组点。
     * 
     * @param points @~english A point coordinates.
     * @~chinese 一堆点的坐标。
     * @param numberOfPoints @~english The number of points.
     * @~chinese 点的数量。
     * @since v0.7.2
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawPoints(const Vec2 *points, unsigned int numberOfPoints);

    /** @~english Draws a line given the origin and destination point measured in points
     *
     * @~chinese 基于给定的起始点和结束点画一条线，以点为单位。
     * 
     * @param origin @~english A Vec2 Type point used to the line origin.
     * @~chinese 线起始点。
     * @param destination @~english A Vec2 Type point used to the line destination.
     * @~chinese 线结束点。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawLine(const Vec2& origin, const Vec2& destination);

    /** @~english Draws a rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @~chinese 基于给定的起始点和结束点画一个长方形，以点为单位。
     * 起始点和结束点不能是同一个点。
     * 
     * @param origin @~english The rectangle origin.
     * @~chinese 矩形起始点。
     * @param destination @~english The rectangle destination.
     * @~chinese 矩形结束点。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawRect(Vec2 origin, Vec2 destination);

    /** @~english Draws a solid rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @~chinese 基于给定的起始点和结束点画一个长方形，以点为单位。
     * 起始点和结束点不能是同一个点。
     *
     * @param origin @~english The rectangle origin.
     * @~chinese 矩形起始点。
     * @param destination @~english The rectangle destination.
     * @~chinese 矩形结束点。
     * @param color @~english The rectangle color.
     * @~chinese 矩形的颜色。
     * @since 1.1
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidRect(Vec2 origin, Vec2 destination, Color4F color);

    /** @~english Draws a polygon given a pointer to point coordinates and the number of vertices measured in points.
     * The polygon can be closed or open.
     *
     * @~chinese 基于给定的点画一个多边形。
     * 多边形可以是关闭或打开状态。
     * 
     * @param vertices @~english A pointer to point coordinates.
     * @~chinese 一个指向一堆点坐标的指针。
     * @param numOfVertices @~english The number of vertices measured in points.
     * @~chinese 顶点的数量。
     * @param closePolygon @~english The polygon can be closed or open.
     * @~chinese 指示多边形关闭或打开。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawPoly(const Vec2 *vertices, unsigned int numOfVertices, bool closePolygon);

    /** @~english Draws a solid polygon given a pointer to Vec2 coordinates, the number of vertices measured in points, and a color.
     *
     * @~chinese 基于给定的点和颜色画一个实心多边形。
     * 
     * @param poli @~english A solid polygon given a pointer to Vec2 coordinates.
     * @~chinese 一个指向一堆点坐标的指针。
     * @param numberOfPoints @~english The number of vertices measured in points.
     * @~chinese 顶点的数量。
     * @param color @~english The solid polygon color.
     * @~chinese 多边形的填充颜色。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, Color4F color);

    /** @~english Draws a circle given the center, radius and number of segments. 
     *
     * @~chinese 基于给定的圆心，半径和线段数量画了一个圆。
     * 
     * @param center @~english The circle center point.
     * @~chinese 圆点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆旋转角度。
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param drawLineToCenter @~english Whether or not draw the line from the origin to center.
     * @~chinese 是否从圆的起始点画线到圆心。
     * @param scaleX @~english The scale value in x.
     * @~chinese x的缩放值。
     * @param scaleY @~english The scale value in y.
     * @~chinese y的缩放值。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
    
    /** @~english Draws a circle given the center, radius and number of segments.
     *
     * @~chinese 基于给定的圆心，半径和线段数量画了一个圆。
     * 
     * @param center @~english The circle center point.
     * @~chinese 圆点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆旋转角度。
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param drawLineToCenter @~english Whether or not draw the line from the origin to center.
     * @~chinese 是否从圆的起始点画线到圆心。
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);

    /** @~english Draws a solid circle given the center, radius and number of segments.
     * @~chinese 基于给定的圆心，半径和线段数量画了一个圆。
     * @param center @~english The circle center point.
     * @~chinese 圆点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆旋转角度。
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param scaleX @~english The scale value in x.
     * @~chinese x的缩放值。
     * @param scaleY @~english The scale value in y.
     * @~chinese y的缩放值。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY);
    
    /** @~english Draws a solid circle given the center, radius and number of segments.
     * @~chinese 基于给定的圆心，半径和线段数量画了一个圆。
     * @param center @~english The circle center point.
     * @~chinese 圆点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆旋转角度。
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments);

    /** @~english Draws a quad bezier path.
     *
     * @~chinese 绘制一个quad贝塞尔曲线路径。
     * 
     * @param origin @~english The origin of the bezier path.
     * @~chinese 贝塞尔曲线路径的起点。
     * @param control @~english The control of the bezier path.
     * @~chinese 贝塞尔曲线的控制点。
     * @param destination @~english The destination of the bezier path.
     * @~chinese 贝塞尔曲线的终点。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @warning @~english This function could be pretty slow. Use it only for debugging purposes.
     * @~chinese 这个函数可能相当缓慢。只在调试时使用它。
     * @since v0.8
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments);

    /** @~english Draws a cubic bezier path.
     *
     * @~chinese 绘制一个cubic贝塞尔曲线路径。
     * 
     * @param origin @~english The origin of the bezier path.
     * @~chinese 贝塞尔曲线路径的起点。
     * @param control1 @~english The first control of the bezier path.
     * @~chinese 第一个贝塞尔曲线路径的控制点。
     * @param control2 @~english The second control of the bezier path.
     * @~chinese 第二个贝塞尔曲线路径的控制点。
     * @param destination @~english The destination of the bezier path.
     * @~chinese 贝塞尔曲线的终点。
     * @param segments @~english The The number of segments.
     * @~chinese The 线段的数量。
     * @warning @~english This function could be pretty slow. Use it only for debugging purposes.
     * @~chinese 这个函数可能相当缓慢。只在调试时使用它。
     * @since v0.8
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);

    /** @~english Draws a Catmull Rom path.
     *
     * @~chinese 绘制一个Catmull Rom路径。
     * 
     * @param arrayOfControlPoints @~english A point array  of control point.
     * @~chinese 一系列点的控制点。
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @warning @~english This function could be pretty slow. Use it only for debugging purposes.
     * @~chinese 这个函数可能相当缓慢。只在调试时使用它。
     * @since v2.0
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCatmullRom(PointArray *arrayOfControlPoints, unsigned int segments);

    /** @~english Draws a Cardinal Spline path.
     *
     * @~chinese 绘制一个CardinalSpline路径。
     * 
     * @param config @~english A array point.
     * @~chinese 一组点。
     * @param tension @~english The tension of the spline.
     * @~chinese spline的张力。
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @warning @~english This function could be pretty slow. Use it only for debugging purposes.
     * @~chinese 这个函数可能相当缓慢。只在调试时使用它。
     * @since v2.0
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCardinalSpline(PointArray *config, float tension,  unsigned int segments);

    /** @~english Set the drawing color with 4 unsigned bytes.
     *
     * @~chinese 设置绘图颜色，单位是Byte。
     * 
     * @param r @~english The red color with a unsigned bytes.
     * @~chinese 红色。
     * @param g @~english The green color with a unsigned bytes.
     * @~chinese 绿色。
     * @param b @~english The blue color with a unsigned bytes.
     * @~chinese 蓝色。
     * @param a @~english Alpha with a unsigned bytes.
     * @~chinese 透明度。
     * @since v2.0
     * @js setDrawColor
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL setDrawColor4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

    /** @~english Set the drawing color with 4 floats.
     *
     * @~chinese 设置绘图颜色，单位是float。
     * 
     * @param r @~english The red color with an floats.
     * @~chinese 红色。
     * @param g @~english The green color with an floats.
     * @~chinese 绿色。
     * @param b @~english The blue color with an floats.
     * @~chinese 蓝色。
     * @param a @~english Alpha with an floats.
     * @~chinese 透明度。
     * @since v2.0
     * @js setDrawColor
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL setDrawColor4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /** @~english Set the point size in points. Default 1.
     *
     * @~chinese 设置点大小的点。默认为1。
     * 
     * @param pointSize @~english The point size with an float.
     * @~chinese 点的大小，单位是float。
     * @since v2.0
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL setPointSize(GLfloat pointSize);

};

// end of _2d group
/// @}

NS_CC_END

#endif // __CCDRAWING_PRIMITIVES__
