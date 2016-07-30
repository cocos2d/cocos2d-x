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
 Drawing OpenGL ES primitives.
 - drawPoint, drawPoints
 - drawLine
 - drawRect, drawSolidRect
 - drawPoly, drawSolidPoly
 - drawCircle
 - drawQuadBezier
 - drawCubicBezier
 - drawCatmullRom
 - drawCardinalSpline
 
 You can change the color, point size, width by calling:
 - drawColor4B(), drawColor4F()
 - ccPointSize()
 - glLineWidth()
 
 @warning These functions draws the Line, Vec2, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch. Instead you should use DrawNode
 
 */

NS_CC_BEGIN

/**
 * @addtogroup _2d
 * @{
 */

class PointArray;

/**
* @js cc.DrawingPrimitiveCanvas/cc.DrawingPrimitiveWebGL
*/
namespace DrawPrimitives
{
    /**
     * Initializes the drawing primitives.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL init();

    /**
     * Frees allocated resources by the drawing primitives.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL free();

    /** Draws a point given x and y coordinate measured in points
     *
     * @param point A Vec2 with a point given x and y coordinate.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawPoint(const Vec2& point);

    /** Draws an array of points.
     *
     * @param points A point coordinates.
     * @param numberOfPoints The number of points.
     * @since v0.7.2
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawPoints(const Vec2 *points, unsigned int numberOfPoints);

    /** Draws a line given the origin and destination point measured in points
     *
     * @param origin A Vec2 Type point used to the line origin.
     * @param destination A Vec2 Type point used to the line destination.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawLine(const Vec2& origin, const Vec2& destination);

    /** Draws a rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @param origin The rectangle origin.
     * @param destination The rectangle destination.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawRect(Vec2 origin, Vec2 destination);

    /** Draws a solid rectangle given the origin and destination point measured in points.
     * The origin and the destination can not have the same x and y coordinate.
     *
     * @param origin The rectangle origin.
     * @param destination The rectangle destination.
     * @param color The rectangle color.
     * @since 1.1
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidRect(Vec2 origin, Vec2 destination, Color4F color);

    /** Draws a polygon given a pointer to point coordinates and the number of vertices measured in points.
     * The polygon can be closed or open.
     *
     * @param vertices A pointer to point coordinates.
     * @param numOfVertices The number of vertices measured in points.
     * @param closePolygon The polygon can be closed or open.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawPoly(const Vec2 *vertices, unsigned int numOfVertices, bool closePolygon);

    /** Draws a solid polygon given a pointer to CGPoint coordinates, the number of vertices measured in points, and a color.
     *
     * @param poli A solid polygon given a pointer to CGPoint coordinates.
     * @param numberOfPoints The number of vertices measured in points.
     * @param color The solid polygon color.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, Color4F color);

    /** Draws a circle given the center, radius and number of segments. 
     *
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angle.
     * @param segments The number of segments.
     * @param drawLineToCenter Whether or not draw the line from the origin to center.
     * @param scaleX The scale value in x.
     * @param scaleY The scale value in y.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
    
    /** Draws a circle given the center, radius and number of segments.
     *
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angle.
     * @param segments The number of segments.
     * @param drawLineToCenter Whether or not draw the line from the origin to center.
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCircle(const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);

    /** Draws a solid circle given the center, radius and number of segments.
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angle.
     * @param segments The number of segments.
     * @param scaleX The scale value in x.
     * @param scaleY The scale value in y.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY);
    
    /** Draws a solid circle given the center, radius and number of segments.
     * @param center The circle center point.
     * @param radius The circle rotate of radius.
     * @param angle  The circle angle.
     * @param segments The number of segments.
     * @js NA
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawSolidCircle(const Vec2& center, float radius, float angle, unsigned int segments);

    /** Draws a quad bezier path.
     *
     * @param origin The origin of the bezier path.
     * @param control The control of the bezier path.
     * @param destination The destination of the bezier path.
     * @param segments The number of segments.
     * @warning This function could be pretty slow. Use it only for debugging purposes.
     * @since v0.8
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments);

    /** Draws a cubic bezier path.
     *
     * @param origin The origin of the bezier path.
     * @param control1 The first control of the bezier path.
     * @param control2 The second control of the bezier path.
     * @param destination The destination of the bezier path.
     * @param segments The number of segments.
     * @warning This function could be pretty slow. Use it only for debugging purposes.
     * @since v0.8
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);

    /** Draws a Catmull Rom path.
     *
     * @param arrayOfControlPoints A point array  of control point.
     * @param segments The number of segments.
     * @warning This function could be pretty slow. Use it only for debugging purposes.
     * @since v2.0
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCatmullRom(PointArray *arrayOfControlPoints, unsigned int segments);

    /** Draws a Cardinal Spline path.
     *
     * @param config A array point.
     * @param tension The tension of the spline.
     * @param segments The number of segments.
     * @warning This function could be pretty slow. Use it only for debugging purposes.
     * @since v2.0
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL drawCardinalSpline(PointArray *config, float tension,  unsigned int segments);

    /** Set the drawing color with 4 unsigned bytes.
     *
     * @param r The red color with a unsigned bytes.
     * @param g The green color with a unsigned bytes.
     * @param b The blue color with a unsigned bytes.
     * @param a Alpha with a unsigned bytes.
     * @since v2.0
     * @js setDrawColor
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL setDrawColor4B(GLubyte r, GLubyte g, GLubyte b, GLubyte a);

    /** Set the drawing color with 4 floats.
     *
     * @param r The red color with an floats.
     * @param g The green color with an floats.
     * @param b The blue color with an floats.
     * @param a Alpha with an floats.
     * @since v2.0
     * @js setDrawColor
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL setDrawColor4F(GLfloat r, GLfloat g, GLfloat b, GLfloat a);

    /** Set the point size in points. Default 1.
     *
     * @param pointSize The point size with an float.
     * @since v2.0
     */
    CC_DEPRECATED_ATTRIBUTE void CC_DLL setPointSize(GLfloat pointSize);

};

// end of global group
/** @} */

NS_CC_END

#endif // __CCDRAWING_PRIMITIVES__
