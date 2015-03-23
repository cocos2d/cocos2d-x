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
 * @brief Node that draws dots, segments and polygons.
 * Faster than the "drawing primitives" since they draws everything in one single batch.
 * @since v2.1
 */
class CC_DLL DrawNode : public Node
{
public:
    /** creates and initialize a DrawNode node.
     *
     * @return Return an autorelease object.
     */
    static DrawNode* create();
    
    /** Draw a point.
     *
     * @param point A Vec2 used to point.
     * @param pointSize The point size.
     * @param color The point color.
     */
    void drawPoint(const Vec2& point, const float pointSize, const Color4F &color);
    
    /** Draw a group point.
     *
     * @param position A Vec2 pointer.
     * @param numberOfPoints The number of points.
     * @param color The point color.
     */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const Color4F &color);
    
    /** Draw a group point.
     *
     * @param position A Vec2 pointer.
     * @param numberOfPoints The number of points.
     * @param pointSize The point size.
     * @param color The point color.
     */
    void drawPoints(const Vec2 *position, unsigned int numberOfPoints, const float pointSize, const Color4F &color);
    
    /** Draw an line from origin to destination with color. 
     * 
     * @param origin The line origin.
     * @param destination The line destination.
     * @param color The line color.
     */
    void drawLine(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** Draws a rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @param origin The rectangle origin.
     * @param destination The rectangle destination.
     * @param color The rectangle color.
     */
    void drawRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** Draws a polygon given a pointer to point coordinates and the number of vertices measured in points.
     * The polygon can be closed or open.
     *
     * @param poli A pointer to point coordinates.
     * @param numberOfPoints The number of vertices measured in points.
     * @param closePolygon The polygon can be closed or open.
     * @param color The polygon color.
     */
    void drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon, const Color4F &color);
    
    /** Draws a circle given the center, radius and number of segments.
     *
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angel.
     * @param segments The number of segments.
     * @param drawLineToCenter Whether or not draw the line from the origin to center.
     * @param scaleX The scale value in x.
     * @param scaleY The scale value in y.
     * @param color Set the circle color.
     */
    void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY, const Color4F &color);
    
    /** Draws a circle given the center, radius and number of segments.
     *
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angel.
     * @param segments The number of segments.
     * @param drawLineToCenter Whether or not draw the line from the origin to center.
     * @param color Set the circle color.
     */
    void drawCircle(const Vec2 &center, float radius, float angle, unsigned int segments, bool drawLineToCenter, const Color4F &color);
    
    /** Draws a quad bezier path.
     *
     * @param origin The origin of the bezier path.
     * @param control The control of the bezier path.
     * @param destination The destination of the bezier path.
     * @param segments The The number of segments.
     * @param color Set the quad bezier color.
     */
    void drawQuadBezier(const Vec2 &origin, const Vec2 &control, const Vec2 &destination, unsigned int segments, const Color4F &color);

    /** Draw a cubic bezier curve with color and number of segments
     *
     * @param origin The origin of the bezier path.
     * @param control1 The first control of the bezier path.
     * @param control2 The second control of the bezier path.
     * @param destination The destination of the bezier path.
     * @param segments The The number of segments.
     * @param color Set the cubic bezier color.
     */
    void drawCubicBezier(const Vec2 &origin, const Vec2 &control1, const Vec2 &control2, const Vec2 &destination, unsigned int segments, const Color4F &color);
    
    /** Draws a Cardinal Spline path.
     *
     * @param config A array point.
     * @param tension The tension of the spline.
     * @param segments The The number of segments.
     * @param color Set the Spline color.
     */
    void drawCardinalSpline(PointArray *config, float tension,  unsigned int segments, const Color4F &color);
    
    /** Draws a Catmull Rom path.
     *
     * @param points A point array  of control point.
     * @param segments The The number of segments.
     * @param color The Catmull Rom color.
     */
    void drawCatmullRom(PointArray *points, unsigned int segments, const Color4F &color);
    
    /** draw a dot at a position, with a given radius and color. 
     *
     * @param pos The dot center.
     * @param radius The dot radius.
     * @param color The dot color.
     */
    void drawDot(const Vec2 &pos, float radius, const Color4F &color);
    
    /** Draws a rectangle with 4 points.
     *
     * @param p1 The rectangle vertex point.
     * @param p2 The rectangle vertex point.
     * @param p3 The rectangle vertex point.
     * @param p4 The rectangle vertex point.
     * @param color The rectangle color.
     */
    void drawRect(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Vec2& p4, const Color4F &color);
    
    /** Draws a solid rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @param origin The rectangle origin.
     * @param destination The rectangle destination.
     * @param color The rectangle color.
     */
    void drawSolidRect(const Vec2 &origin, const Vec2 &destination, const Color4F &color);
    
    /** Draws a solid polygon given a pointer to CGPoint coordinates, the number of vertices measured in points, and a color.
     *
     * @param poli A solid polygon given a pointer to CGPoint coordinates.
     * @param numberOfPoints The number of vertices measured in points.
     * @param color The solid polygon color.
     */
    void drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, const Color4F &color);
    
    /** Draws a solid circle given the center, radius and number of segments.
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angel.
     * @param segments The number of segments.
     * @param scaleX The scale value in x.
     * @param scaleY The scale value in y.
     * @param color The solid circle color.
     */
    void drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY, const Color4F &color);
    
    /** Draws a solid circle given the center, radius and number of segments.
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angel.
     * @param segments The number of segments.
     * @param color The solid circle color.
     */
    void drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, const Color4F& color);
    
    /** draw a segment with a radius and color. 
     *
     * @param from The segment origin.
     * @param to The segment destination.
     * @param radius The segment radius.
     * @param color The segment color.
     */
    void drawSegment(const Vec2 &from, const Vec2 &to, float radius, const Color4F &color);
    
    /** draw a polygon with a fill color and line color
    * @code
    * When this function bound into js or lua,the parameter will be changed
    * In js: var drawPolygon(var Arrayofpoints, var fillColor, var width, var borderColor)
    * In lua:local drawPolygon(local pointTable,local tableCount,local fillColor,local width,local borderColor)
    * @endcode
    * @param verts A pointer to point coordinates.
    * @param count The number of verts measured in points.
    * @param fillColor The color will fill in polygon.
    * @param borderWidth The border of line width.
    * @param borderColor The border of line color.
    */
    void drawPolygon(const Vec2 *verts, int count, const Color4F &fillColor, float borderWidth, const Color4F &borderColor);
	
    /** draw a triangle with color. 
     *
     * @param p1 The triangle vertex point.
     * @param p2 The triangle vertex point.
     * @param p3 The triangle vertex point.
     * @param color The triangle color.
     */
    void drawTriangle(const Vec2 &p1, const Vec2 &p2, const Vec2 &p3, const Color4F &color);

    /** draw a quadratic bezier curve with color and number of segments, use drawQuadBezier instead.
     *
     * @param from The origin of the bezier path.
     * @param control The control of the bezier path.
     * @param to The destination of the bezier path.
     * @param segments The The number of segments.
     * @param color The quadratic bezier color.
     */
    CC_DEPRECATED_ATTRIBUTE void drawQuadraticBezier(const Vec2& from, const Vec2& control, const Vec2& to, unsigned int segments, const Color4F &color);
    
    /** Clear the geometry in the node's buffer. */
    void clear();
    /** Get the color mixed mode.
    * @js NA
    * @lua NA
    */
    const BlendFunc& getBlendFunc() const;
    /** Set the color mixed mode.
    * @code
    * When this function bound into js or lua,the parameter will be changed
    * In js: var setBlendFunc(var src, var dst)
    * @endcode
    * @lua NA
    */
    void setBlendFunc(const BlendFunc &blendFunc);

    void onDraw(const Mat4 &transform, uint32_t flags);
    void onDrawGLLine(const Mat4 &transform, uint32_t flags);
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
