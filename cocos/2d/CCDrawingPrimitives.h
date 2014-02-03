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
    

#include "ccTypes.h"
#include "ccMacros.h"
#include "CCGeometry.h"    // for Point

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
 
 @warning These functions draws the Line, Point, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch. Instead you should use DrawNode
 
 */

NS_CC_BEGIN

/**
 * @addtogroup global
 * @{
 */

class PointArray;

namespace DrawPrimitives
{
    /** Initializes the drawing primitives */
    void init();

    /** Frees allocated resources by the drawing primitives */
    void free();

    /** draws a point given x and y coordinate measured in points */
    void drawPoint( const Point& point );

    /** draws an array of points.
     @since v0.7.2
     */
    void drawPoints( const Point *points, unsigned int numberOfPoints );

    /** draws a line given the origin and destination point measured in points */
    void drawLine( const Point& origin, const Point& destination );

    /** draws a rectangle given the origin and destination point measured in points. */
    void drawRect( Point origin, Point destination );

    /** draws a solid rectangle given the origin and destination point measured in points.
        @since 1.1
     */
    void drawSolidRect( Point origin, Point destination, Color4F color );

    /** draws a polygon given a pointer to Point coordinates and the number of vertices measured in points.
    The polygon can be closed or open
    */
    void drawPoly( const Point *vertices, unsigned int numOfVertices, bool closePolygon );

    /** draws a solid polygon given a pointer to CGPoint coordinates, the number of vertices measured in points, and a color.
     */
    void drawSolidPoly( const Point *poli, unsigned int numberOfPoints, Color4F color );

    /** draws a circle given the center, radius and number of segments. */
    void drawCircle( const Point& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
    void drawCircle( const Point& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);

    /** draws a solid circle given the center, radius and number of segments. */
    void drawSolidCircle( const Point& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY);
    void drawSolidCircle( const Point& center, float radius, float angle, unsigned int segments);

    /** draws a quad bezier path
     @warning This function could be pretty slow. Use it only for debugging purposes.
     @since v0.8
     */
    void drawQuadBezier(const Point& origin, const Point& control, const Point& destination, unsigned int segments);

    /** draws a cubic bezier path
     @warning This function could be pretty slow. Use it only for debugging purposes.
     @since v0.8
     */
    void drawCubicBezier(const Point& origin, const Point& control1, const Point& control2, const Point& destination, unsigned int segments);

    /** draws a Catmull Rom path.
     @warning This function could be pretty slow. Use it only for debugging purposes.
     @since v2.0
     */
    void drawCatmullRom( PointArray *arrayOfControlPoints, unsigned int segments );

    /** draws a Cardinal Spline path.
     @warning This function could be pretty slow. Use it only for debugging purposes.
     @since v2.0
     */
    void drawCardinalSpline( PointArray *config, float tension,  unsigned int segments );

    /** set the drawing color with 4 unsigned bytes
     @since v2.0
     */
    void setDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a );

    /** set the drawing color with 4 floats
     @since v2.0
     */
    void setDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a );

    /** set the point size in points. Default 1.
     @since v2.0
     */
    void setPointSize( GLfloat pointSize );

};

// end of global group
/// @}

NS_CC_END

#endif // __CCDRAWING_PRIMITIVES__
