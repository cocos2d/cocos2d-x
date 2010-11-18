/****************************************************************************
Copyright (c) 2010 cocos2d-x.org

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
  - drawPoint
  - drawLine
  - drawPoly
  - drawCircle
 
 You can change the color, width and other property by calling the
 glColor4ub(), glLineWitdh(), glPointSize().
 
 @warning These functions draws the Line, Point, Polygon, immediately. They aren't batched. If you are going to make a game that depends on these primitives, I suggest creating a batch.
 */

#include "CGGeometry.h"	// for CGPoint
namespace   cocos2d {

/** draws a point given x and y coordinate */
void CCX_DLL ccDrawPoint( CGPoint point );

/** draws an array of points.
 @since v0.7.2
 */
void CCX_DLL ccDrawPoints( CGPoint *points, unsigned int numberOfPoints );

/** draws a line given the origin and destination point */
void CCX_DLL ccDrawLine( CGPoint origin, CGPoint destination );

/** draws a poligon given a pointer to CGPoint coordiantes and the number of vertices. The polygon can be closed or open
 */
void CCX_DLL ccDrawPoly( CGPoint *vertices, int numOfVertices, bool closePolygon );

/** draws a circle given the center, radius and number of segments. */
void CCX_DLL ccDrawCircle( CGPoint center, float radius, float angle, int segments, bool drawLineToCenter);

/** draws a quad bezier path
 @since v0.8
 */
void CCX_DLL ccDrawQuadBezier(CGPoint origin, CGPoint control, CGPoint destination, int segments);

/** draws a cubic bezier path
 @since v0.8
 */
void CCX_DLL ccDrawCubicBezier(CGPoint origin, CGPoint control1, CGPoint control2, CGPoint destination, int segments);
}//namespace   cocos2d 

#endif // __CCDRAWING_PRIMITIVES__
