/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 * Copyright (c) 2012 cocos2d-x.org
 * Copyright (c) 2013-2014 Chukong Technologies Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

/*
 * Code copied & pasted from SpacePatrol game https://github.com/slembcke/SpacePatrol
 *
 * Renamed and added some changes for cocos2d
 *
 */

#ifndef __CCDRAWNODES_CCDRAW_NODE_H__
#define __CCDRAWNODES_CCDRAW_NODE_H__

#include "2d/CCNode.h"
#include "base/ccTypes.h"
#include "renderer/CCCustomCommand.h"
#include "math/CCMath.h"

NS_CC_BEGIN

class PointArray;
/**
 * @addtogroup _2d
 * @{
 */


/** @class DrawNode
 * @brief @~english Node that draws dots, segments and polygons.
 * Faster than the "drawing primitives" since they draws everything in one single batch.
 * @~chinese 绘制点、线段和多边形的节点。
 * 由于它使用了"批处理"（Batch draw），因此它绘制点、线段、多边形都要比“drawing primitives”快。
 * @since v2.1
 */
class CC_DLL DrawNode : public Node
{
public:
    /** @~english creates and initialize a DrawNode node.
     * @~chinese 创建并初始化DrawNode节点.
     * @return @~english Return an autorelease object.
     * @~chinese 返回一个自动释放对象.
     */
    static DrawNode* create();
    
    /** @~english Draw a point.
     *
     * @~chinese 画一个点。
     * 
     * @param point @~english A Vec2 point.
     * @~chinese 一个Vec2类型的点
     * @param pointSize @~english The point size.
     * @~chinese 点的大小
     * @param color @~english The point color.
     * @~chinese 点的颜色
     * @js NA
     */
    void drawPoint(const Vec2& point, const float pointSize, const Color4F &color);
    
    /** @~english Draw a group point.
     *
     * @~chinese 画一组点。
     * 
     * @param position @~english A Vec2 pointer.
     * @~chinese 一个Vec2指针。
     * @param numberOfPoints @~english The number of points.
     * @~chinese 点的数量。
     * @param color @~english The point color.
     * @~chinese 点的颜色。
     * @js NA
     */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color);
    
    /** @~english Draw a group point.
     *
     * @~chinese 画一组点。
     * 
     * @param position @~english A Vec2 pointer.
     * @~chinese 一个Vec2指针。
     * @param numberOfPoints @~english The number of points.
     * @~chinese 点的数量。
     * @param pointSize @~english The point size.
     * @~chinese 点的大小。
     * @param color @~english The point color.
     * @~chinese 点的颜色。
     * @js NA
     */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const float pointSize, const Color4F &color);
    
    /** @~english Draw an line from origin to destination with color. 
     * 
     * @~chinese 使用指定颜色画一条从起始点到目的地点的线。
     * 
     * @param origin @~english The line origin.
     * @~chinese 起始点的坐标
     * @param destination @~english The line destination.
     * @~chinese 目的地点的坐标
     * @param color @~english The line color.
     * @~chinese 线的颜色。
     * @js NA
     */
    void drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** @~english Draws a rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @~chinese 给定一个起始点坐标和目的地点坐标画一个矩形，坐标的单位是“Point”
     * 起始点坐标和目的地点坐标不能相同。
     * 
     * @param origin @~english The rectangle origin.
     * @~chinese 矩形的原点坐标。
     * @param destination @~english The rectangle destination.
     * @~chinese 矩形的目的地点坐标。
     * @param color @~english The rectangle color.
     * @~chinese 矩形的颜色。
     */
    void drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** @~english Draws a polygon given a pointer to point coordinates and the number of vertices measured in points.
     * The polygon can be closed or open.
     *
     * @~chinese 给定一个指向一组点坐标的指针和坐标点数量来绘制多边形
     * 多边形可以闭合，也可以不闭合。
     * 
     * @param poli @~english A pointer to point coordinates.
     * @~chinese 一个指向一组点坐标的指针
     * @param numberOfPoints @~english The number of vertices measured in points.
     * @~chinese 顶点的数量.
     * @param closePolygon @~english The polygon can be closed or open.
     * @~chinese 多边形是否闭合
     * @param color @~english The polygon color.
     * @~chinese 多边形的颜色。
     */
    void drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color);
    
    /** @~english Draws a circle given the center, radius, number of segments and a border color.
     *
     * @~chinese 给定圆的中心,半径，线段数量和线段颜色来绘制一个圆。如果要绘制带填充色的圆，请使用 drawSolidCircle函数。
     * 
     * @param center @~english The circle center point.
     * @~chinese 圆中心点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆的半径
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param drawLineToCenter @~english Whether or not draw the line from the origin to center.
     * @~chinese 是否从原点往中心点画一条线。
     * @param scaleX @~english The scale value in x.
     * @~chinese x的缩放值。
     * @param scaleY @~english The scale value in y.
     * @~chinese y的缩放值。
     * @param color @~english Set the circle color.
     * @~chinese 圆的颜色。
     */
    void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color);
    
    /** @~english Draws a circle given the center, radius and number of segments.
     *
     * @~chinese 给定圆的中心,半径和线段数量来绘制一个圆。
     * 
     * @param center @~english The circle center point.
     * @~chinese 圆中心点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆的半径
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param drawLineToCenter @~english Whether or not draw the line from the origin to center.
     * @~chinese 是否从原点往中心点画一条线
     * @param color @~english Set the circle color.
     * @~chinese 圆的颜色
     */
    void drawCircle(const Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const Color4F &color);
    
    /** @~english Draws a quad bezier path.
     *
     * @~chinese 画了一个四次贝塞尔曲线路径。
     * 
     * @param origin @~english The origin of the bezier path.
     * @~chinese 贝塞尔曲线路径的原点。
     * @param control @~english The control of the bezier path.
     * @~chinese 贝塞尔曲线的控制点。
     * @param destination @~english The destination of the bezier path.
     * @~chinese 贝塞尔曲线的终点
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @param color @~english Set the quad bezier color.
     * @~chinese 设置四次贝塞尔曲线的颜色。
     */
    void drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, unsigned int segments, const Color4F &color);

    /** @~english Draw a cubic bezier curve with color and number of segments
     *
     * @~chinese 使用给定数量的线段和颜色绘制一个三次贝塞尔曲线。
     * 
     * @param origin @~english The origin of the bezier path.
     * @~chinese 贝塞尔曲线路径的原点。
     * @param control1 @~english The first control of the bezier path.
     * @~chinese 贝塞尔曲线路径的第一个控制点。
     * @param control2 @~english The second control of the bezier path.
     * @~chinese 贝塞尔曲线路径的第二个控制点。
     * @param destination @~english The destination of the bezier path.
     * @~chinese 贝塞尔曲线路径的目的地点。
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @param color @~english Set the cubic bezier color.
     * @~chinese 设置三次贝塞尔曲线的颜色。
     */
    void drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, unsigned int segments, const Color4F &color);
    
    /** @~english Draws a Cardinal Spline path.
     *
     * @~chinese 绘制一个基数样条路径。
     * 
     * @param config @~english A array point.
     * @~chinese 一个点数组。
     * @param tension @~english The tension of the spline.
     * @~chinese 样条的张力。
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @param color @~english Set the Spline color.
     * @~chinese 设置样条的颜色。
     */
    void drawCardinalSpline(PointArray *config, float tension,  unsigned int segments, const Color4F &color);
    
    /** @~english Draws a Catmull Rom path.
     *
     * @~chinese 绘制一个卡特莫尔罗(Catmull Rom)路径。
     * 
     * @param points @~english A point array  of control point.
     * @~chinese 一个控制点数组。
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @param color @~english The Catmull Rom color.
     * @~chinese 卡特莫尔罗的颜色。
     */
    void drawCatmullRom(PointArray *points, unsigned int segments, const Color4F &color);
    
    /** @~english draw a dot at a position, with a given radius and color. 
     *
     * @~chinese 在给定坐标点、半径和颜色值画一个点。
     * 
     * @param pos @~english The dot center.
     * @~chinese 点中心。
     * @param radius @~english The dot radius.
     * @~chinese 点半径。
     * @param color @~english The dot color.
     * @~chinese 点的颜色。
     */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    /** @~english Draws a rectangle with 4 points.
     *
     * @~chinese 画一个包含4个顶点的矩形
     * 
     * @param p1 @~english The rectangle vertex point.
     * @~chinese 矩形的顶点。
     * @param p2 @~english The rectangle vertex point.
     * @~chinese 矩形的顶点。
     * @param p3 @~english The rectangle vertex point.
     * @~chinese 矩形的顶点。
     * @param p4 @~english The rectangle vertex point.
     * @~chinese 矩形的顶点。
     * @param color @~english The rectangle color.
     * @~chinese 矩形的颜色。
     */
    void drawRect(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2& p4, const Color4F &color);
    
    /** @~english Draws a solid rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @~chinese 使用给定的原点和目的地点绘制一个实心矩形。
     * 原点和目的地点不能有相同的x和y坐标。
     * 
     * @param origin @~english The rectangle origin.
     * @~chinese 矩形的原点。
     * @param destination @~english The rectangle destination.
     * @~chinese 矩形的目的地。
     * @param color @~english The rectangle color.
     * @~chinese 矩形的颜色。
     * @js NA
     */
    void drawSolidRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** @~english Draws a solid polygon given with a pointer to coordinates, the number of vertices measured in points, and a color.
     *
     * @~chinese 给定一组坐标点画一个实心多边形,顶点数据包含个数和颜色.
     * 
     * @param poli @~english A pointer to Vec2 coordinates.
     * @~chinese 一个指向Vec2数组的指针。
     * @param numberOfPoints @~english The number of vertices measured in points.
     * @~chinese 顶点的数量,单位是“Point”
     * @param color @~english The solid polygon color.
     * @~chinese 实心多边形的颜色。
     * @js NA
     */
    void drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, const Color4F &color);
    
    /** @~english Draws a solid circle given the center, radius and number of segments.
     * @~chinese 给定圆的中心,半径和线段的数量绘制一个实心圆。
     * @param center @~english The circle center point.
     * @~chinese 圆中心点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆的半径。
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param scaleX @~english The scale value in x.
     * @~chinese x的缩放值
     * @param scaleY @~english The scale value in y.
     * @~chinese y的缩放值
     * @param color @~english The solid circle color.
     * @~chinese 实心圆的颜色。
     * @js NA
     */
    void drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY, const Color4F &color);
    
    /** @~english Draws a solid circle given the center, radius and number of segments.
     * @~chinese 给定圆的中心,半径和线段的数量绘制一个实心圆。
     * @param center @~english The circle center point.
     * @~chinese 圆中心点。
     * @param radius @~english The circle rotate of radius.
     * @~chinese 圆的半径。
     * @param angle  @~english The circle angle.
     * @~chinese 圆的角度。
     * @param segments @~english The number of segments.
     * @~chinese 线段的数量。
     * @param color @~english The solid circle color.
     * @~chinese 实心圆的颜色。
     * @js NA
     */
    void drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, const Color4F& color);
    
    /** @~english draw a segment with a radius and color. 
     *
     * @~chinese 使用指定半径和颜色绘制一条线段。
     * 
     * @param from @~english The segment origin.
     * @~chinese 线段的原点。
     * @param to @~english The segment destination.
     * @~chinese 线段的目的地点。
     * @param radius @~english The segment radius.
     * @~chinese 线段半径。
     * @param color @~english The segment color.
     * @~chinese 线段的颜色。
     */
    void drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
    
    /** @~english draw a polygon with a fill color and line color
    * @~chinese 使用给定的填充颜色和线条颜色绘制一个多边形。
    *
    * @param verts @~english A pointer to point coordinates.
    * @~chinese 一个指向顶点数组的指针。
    * @param count @~english The number of verts measured in points.
     * @~chinese 顶点的数量
    * @param fillColor @~english The color will fill in polygon.
     * @~chinese 多边形的填充颜色。
    * @param borderWidth @~english The border of line width.
     * @~chinese 多边形的线宽。
    * @param borderColor @~english The border of line color.
     * @~chinese 多边形的线宽的颜色。
    * @js NA
    */
    void drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	
    /** @~english draw a triangle with color, the color will fill in the triangle.
     *
     * @~chinese 使用给定颜色绘制一个三角形,该颜色会填充矩形。
     * 
     * @param p1 @~english The triangle vertex point.
     * @~chinese 三角形的顶点。
     * @param p2 @~english The triangle vertex point.
     * @~chinese 三角形的顶点。
     * @param p3 @~english The triangle vertex point.
     * @~chinese 三角形的顶点。
     * @param color @~english The triangle color.
     * @~chinese 三角形的颜色。
     * @js NA
     */
    void drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color);

    /** @~english draw a quadratic bezier curve with color and number of segments, use drawQuadBezier instead.
     *
     * @~chinese 给定线段颜色和线段数量画一条二次贝塞尔曲线. 该函数已不推荐使用，使用drawQuadBezier代替。
     * 
     * @param from @~english The origin of the bezier path.
     * @~chinese 贝塞尔曲线路径的原点。
     * @param control @~english The control of the bezier path.
     * @~chinese 贝塞尔曲线路径的控制点。
     * @param to @~english The destination of the bezier path.
     * @~chinese 贝塞尔曲线的路径目的地坐标点。
     * @param segments @~english The The number of segments.
     * @~chinese 线段的数量。
     * @param color @~english The quadratic bezier color.
     * @~chinese 二次贝塞尔曲线的颜色。
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color);
    
    /** @~english Clear the geometry in the node's buffer.  @~chinese 清除节点的缓冲区中的几何数据。*/

    void clear();

    /** @~english Get the color mixed mode.
     * @~chinese 获取颜色混合模式。
    * @lua NA
    */
    const BlendFunc& getBlendFunc() const;

    /** @~english Set the color mixed mode.
     * @~chinese 设置颜色混合模式。
    * @lua NA
    */
    void setBlendFunc(const BlendFunc &blendFunc);

    /**
     * @js NA
     */
    void onDraw(const Mat4 &transform, uint32_t flags);
    /**
     * @js NA
     */
    void onDrawGLLine(const Mat4 &transform, uint32_t flags);
    /**
     * @js NA
     */
    void onDrawGLPoint(const Mat4 &transform, uint32_t flags);
    
    // Overrides
    virtual void draw(Renderer *renderer, const Mat4 &transform, uint32_t flags) override;
    
CC_CONSTRUCTOR_ACCESS:
    DrawNode();
    virtual ~DrawNode();
    virtual bool init() override;

protected:
    void ensureCapacity(int count);
    void ensureCapacityGLPoint(int count);
    void ensureCapacityGLLine(int count);

    GLuint      _vao;
    GLuint      _vbo;
    GLuint      _vaoGLPoint;
    GLuint      _vboGLPoint;
    GLuint      _vaoGLLine;
    GLuint      _vboGLLine;

    int         _bufferCapacity;
    GLsizei     _bufferCount;
    V2F_C4B_T2F *_buffer;
    
    int         _bufferCapacityGLPoint;
    GLsizei     _bufferCountGLPoint;
    V2F_C4B_T2F *_bufferGLPoint;
    Color4F     _pointColor;
    int         _pointSize;
    
    int         _bufferCapacityGLLine;
    GLsizei     _bufferCountGLLine;
    V2F_C4B_T2F *_bufferGLLine;

    BlendFunc   _blendFunc;
    CustomCommand _customCommand;
    CustomCommand _customCommandGLPoint;
    CustomCommand _customCommandGLLine;

    bool        _dirty;
    bool        _dirtyGLPoint;
    bool        _dirtyGLLine;

private:
    CC_DISALLOW_COPY_AND_ASSIGN(DrawNode);
};
/** @} */

NS_CC_END

#endif // __CCDRAWNODES_CCDRAW_NODE_H__
