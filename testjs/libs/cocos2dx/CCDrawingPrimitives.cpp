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

#include "CCDrawingPrimitives.h"
#include "ccTypes.h"
#include "ccMacros.h"
#include "CCGL.h"
#include "CCDirector.h"

#include <string.h>
#include <cmath>

#ifndef M_PI
	#define M_PI       3.14159265358979323846
#endif

namespace   cocos2d {

void ccDrawPoint(const CCPoint& point)
{
	ccVertex2F p = {point.x * CC_CONTENT_SCALE_FACTOR(), point.y * CC_CONTENT_SCALE_FACTOR() };
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, &p);	
	glDrawArrays(GL_POINTS, 0, 1);

	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
}

void ccDrawPoints(const CCPoint *points, unsigned int numberOfPoints)
{
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);

	ccVertex2F *newPoints = new ccVertex2F[numberOfPoints];

	// iPhone and 32-bit machines optimization
	if( sizeof(CCPoint) == sizeof(ccVertex2F) ) 
	{
		// points ?
		if( CC_CONTENT_SCALE_FACTOR() != 1 ) 
		{
			for( unsigned int i= 0; i < numberOfPoints; i++)
			{
				newPoints[i].x = points[i].x * CC_CONTENT_SCALE_FACTOR();
				newPoints[i].y = points[i].y * CC_CONTENT_SCALE_FACTOR();
			}

			glVertexPointer(2, GL_FLOAT, 0, newPoints);

		} else
		{
			glVertexPointer(2, GL_FLOAT, 0, points);
		}

		glDrawArrays(GL_POINTS, 0, (GLsizei)numberOfPoints);

	} else 
	{

		// Mac on 64-bit
		for( unsigned int i = 0; i < numberOfPoints; i++)
		{
			newPoints[i].x = points[i].x;
			newPoints[i].y = points[i].y;
		}

		glVertexPointer(2, GL_FLOAT, 0, newPoints);
		glDrawArrays(GL_POINTS, 0, (GLsizei)numberOfPoints);
	}

	delete[] newPoints;
	
	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
}

void ccDrawLine(const CCPoint& origin, const CCPoint& destination)
{
	ccVertex2F vertices[2] = 
    {
        {origin.x * CC_CONTENT_SCALE_FACTOR(), origin.y * CC_CONTENT_SCALE_FACTOR()},
        {destination.x * CC_CONTENT_SCALE_FACTOR(), destination.y * CC_CONTENT_SCALE_FACTOR()},
    };
	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);	
	glDrawArrays(GL_LINES, 0, 2);
	
	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
}

void ccDrawPoly(const CCPoint *poli, int numberOfPoints, bool closePolygon){
	ccDrawPoly(poli,numberOfPoints,closePolygon,false);
}
void ccDrawPoly(const CCPoint *poli, int numberOfPoints, bool closePolygon, bool fill)
{
    ccVertex2F* newPoint = new ccVertex2F[numberOfPoints];
    if (! newPoint)
    {
        return;
    }
    // Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
    // Needed states: GL_VERTEX_ARRAY, 
    // Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
    glDisable(GL_TEXTURE_2D);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);


    // iPhone and 32-bit machines
    if( sizeof(CCPoint) == sizeof(ccVertex2F) ) 
	{
        // convert to pixels ?
        if( CC_CONTENT_SCALE_FACTOR() != 1 ) 
		{
            memcpy( newPoint, poli, numberOfPoints * sizeof(ccVertex2F) );
            for( int i=0; i<numberOfPoints;i++)
            {
                newPoint[i].x = poli[i].x * CC_CONTENT_SCALE_FACTOR();
                newPoint[i].y = poli[i].y * CC_CONTENT_SCALE_FACTOR();
            }
            glVertexPointer(2, GL_FLOAT, 0, newPoint);

        } 
		else
		{
            glVertexPointer(2, GL_FLOAT, 0, poli);
		}


    } 
	else 
	{
        // 64-bit machines (Mac)

        for( int i=0; i<numberOfPoints;i++)
        {
            newPoint[i].x = poli[i].x;
            newPoint[i].y = poli[i].y;
        }

        glVertexPointer(2, GL_FLOAT, 0, newPoint );

    }

    if( closePolygon )
	{
        glDrawArrays(fill? GL_TRIANGLE_FAN : GL_LINE_LOOP, 0, numberOfPoints);
	}
    else
	{
		glDrawArrays(fill? GL_TRIANGLE_FAN : GL_LINE_STRIP, 0, numberOfPoints);
	}

    // restore default state
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnable(GL_TEXTURE_2D);
    delete[] newPoint;
}

void ccDrawCircle(const CCPoint& center, float r, float a, int segs, bool drawLineToCenter)
{
	int additionalSegment = 1;
	if (drawLineToCenter)
	{
		++additionalSegment;
	}

	const float coef = 2.0f * (float) (M_PI) /segs;

	float *vertices = new float[2*(segs+2)]; //	float *vertices = (float *)malloc( sizeof(float)*2*(segs+2));
	if( ! vertices )
	{
		return;
	}
	
	memset( vertices,0, sizeof(float)*2*(segs+2));
	
	for(int i=0;i<=segs;i++)
	{
		float rads = i*coef;
		float j = r * cosf(rads + a) + center.x;
		float k = r * sinf(rads + a) + center.y;
		
		vertices[i*2] = j * CC_CONTENT_SCALE_FACTOR();
		vertices[i*2+1] =k * CC_CONTENT_SCALE_FACTOR();
	}
	vertices[(segs+1)*2] = center.x * CC_CONTENT_SCALE_FACTOR();
	vertices[(segs+1)*2+1] = center.y * CC_CONTENT_SCALE_FACTOR();
	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);	
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segs+additionalSegment);
	
	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	

	delete[] vertices; //	free(vertices);
}

void ccDrawQuadBezier(const CCPoint& origin, const CCPoint& control, const CCPoint& destination, int segments)
{
	CCPoint *vertices = new CCPoint[segments + 1];
	
	float t = 0.0f;
	for(int i = 0; i < segments; i++)
	{
		float x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
		float y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
		vertices[i] = CCPointMake(x * CC_CONTENT_SCALE_FACTOR(), y * CC_CONTENT_SCALE_FACTOR());
		t += 1.0f / segments;
	}
	vertices[segments] = CCPointMake(destination.x  * CC_CONTENT_SCALE_FACTOR(), destination.y * CC_CONTENT_SCALE_FACTOR());
	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);	
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);
	delete[] vertices;
	
	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
}

void ccDrawCubicBezier(const CCPoint& origin, const CCPoint& control1, const CCPoint& control2, const CCPoint& destination, int segments)
{
	CCPoint *vertices = new CCPoint[segments + 1];
	
	float t = 0;
	for(int i = 0; i < segments; ++i)
	{
		float x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
		float y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
		vertices[i] = CCPointMake(x * CC_CONTENT_SCALE_FACTOR(), y * CC_CONTENT_SCALE_FACTOR());
		t += 1.0f / segments;
	}
	vertices[segments] = CCPointMake(destination.x * CC_CONTENT_SCALE_FACTOR(), destination.y * CC_CONTENT_SCALE_FACTOR());
	
	// Default GL states: GL_TEXTURE_2D, GL_VERTEX_ARRAY, GL_COLOR_ARRAY, GL_TEXTURE_COORD_ARRAY
	// Needed states: GL_VERTEX_ARRAY, 
	// Unneeded states: GL_TEXTURE_2D, GL_TEXTURE_COORD_ARRAY, GL_COLOR_ARRAY	
	glDisable(GL_TEXTURE_2D);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, vertices);	
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);
	delete[] vertices;
	
	// restore default state
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnable(GL_TEXTURE_2D);	
}
}//namespace   cocos2d 
