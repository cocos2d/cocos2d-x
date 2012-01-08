/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2011      Zynga Inc.

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
	
/**
 @file
 Drawing OpenGL ES primitives.
 - ccDrawPoint
 - ccDrawLine
 - ccDrawPoly
 - ccDrawCircle
 - ccDrawQuadBezier
 - ccDrawCubicBezier
 
 You can change the color, width and other property by calling the
 glColor4ub(), glLineWidth(), glPointSize().
 
 @warning These functions draws the Line, Point, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch.
 */

#include "CCGeometry.h"	// for CCPoint
namespace   cocos2d {

/** draws a point given x and y coordinate measured in points */
void CC_DLL ccDrawPoint( const CCPoint& point );

/** draws an array of points.
 @since v0.7.2
 */
void CC_DLL ccDrawPoints( const CCPoint *points, unsigned int numberOfPoints );

/** draws a line given the origin and destination point measured in points */
void CC_DLL ccDrawLine( const CCPoint& origin, const CCPoint& destination );

/** draws a poligon given a pointer to CCPoint coordiantes and the number of vertices measured in points.
The polygon can be closed or open
*/
void CC_DLL ccDrawPoly( const CCPoint *vertices, int numOfVertices, bool closePolygon );

/** draws a poligon given a pointer to CCPoint coordiantes and the number of vertices measured in points.
The polygon can be closed or open and optionally filled with current GL color
*/
void CC_DLL ccDrawPoly( const CCPoint *vertices, int numOfVertices, bool closePolygon , bool fill);

/** draws a circle given the center, radius and number of segments. */
void CC_DLL ccDrawCircle( const CCPoint& center, float radius, float angle, int segments, bool drawLineToCenter);

/** draws a quad bezier path
 @since v0.8
 */
void CC_DLL ccDrawQuadBezier(const CCPoint& origin, const CCPoint& control, const CCPoint& destination, int segments);

/** draws a cubic bezier path
 @since v0.8
 */
void CC_DLL ccDrawCubicBezier(const CCPoint& origin, const CCPoint& control1, const CCPoint& control2, const CCPoint& destination, int segments);
}//namespace   cocos2d 

#endif // __CCDRAWING_PRIMITIVES__
