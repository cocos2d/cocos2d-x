/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2011 ForzeField Studios S.L
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

#include "CCVertex.h"
#include "ccMacros.h"

NS_CC_BEGIN

void ccVertexLineToPolygon(Point *points, float stroke, Vertex2F *vertices, unsigned int offset, unsigned int nuPoints)
{
    nuPoints += offset;
    if(nuPoints<=1) return;

    stroke *= 0.5f;

    unsigned int idx;
    unsigned int nuPointsMinus = nuPoints-1;

    for(unsigned int i = offset; i<nuPoints; i++)
    {
        idx = i*2;
        Point p1 = points[i];
        Point perpVector;

        if(i == 0)
            perpVector = (p1 - points[i+1]).normalize().getPerp();
        else if(i == nuPointsMinus)
            perpVector = (points[i-1] - p1).normalize().getPerp();
        else
        {
            Point p2 = points[i+1];
            Point p0 = points[i-1];

            Point p2p1 = (p2 - p1).normalize();
            Point p0p1 = (p0 - p1).normalize();

            // Calculate angle between vectors
            float angle = acosf(p2p1.dot(p0p1));

            if(angle < CC_DEGREES_TO_RADIANS(70))
                perpVector = p2p1.getMidpoint(p0p1).normalize().getPerp();
            else if(angle < CC_DEGREES_TO_RADIANS(170))
                perpVector = p2p1.getMidpoint(p0p1).normalize();
            else
                perpVector = (p2 - p0).normalize().getPerp();
        }
        perpVector = perpVector * stroke;

        vertices[idx] = Vertex2F(p1.x+perpVector.x, p1.y+perpVector.y);
        vertices[idx+1] = Vertex2F(p1.x-perpVector.x, p1.y-perpVector.y);

    }

    // Validate vertexes
    offset = (offset==0) ? 0 : offset-1;
    for(unsigned int i = offset; i<nuPointsMinus; i++)
    {
        idx = i*2;
        const unsigned int idx1 = idx+2;

        Vertex2F p1 = vertices[idx];
        Vertex2F p2 = vertices[idx+1];
        Vertex2F p3 = vertices[idx1];
        Vertex2F p4 = vertices[idx1+1];

        float s;
        //BOOL fixVertex = !ccpLineIntersect(Point(p1.x, p1.y), Point(p4.x, p4.y), Point(p2.x, p2.y), Point(p3.x, p3.y), &s, &t);
        bool fixVertex = !ccVertexLineIntersect(p1.x, p1.y, p4.x, p4.y, p2.x, p2.y, p3.x, p3.y, &s);
        if(!fixVertex)
            if (s<0.0f || s>1.0f)
                fixVertex = true;

        if(fixVertex)
        {
            vertices[idx1] = p4;
            vertices[idx1+1] = p3;
        }
    }
}

bool ccVertexLineIntersect(float Ax, float Ay,
                               float Bx, float By,
                               float Cx, float Cy,
                               float Dx, float Dy, float *T)
{
    float  distAB, theCos, theSin, newX;

    // FAIL: Line undefined
    if ((Ax==Bx && Ay==By) || (Cx==Dx && Cy==Dy)) return false;

    //  Translate system to make A the origin
    Bx-=Ax; By-=Ay;
    Cx-=Ax; Cy-=Ay;
    Dx-=Ax; Dy-=Ay;

    // Length of segment AB
    distAB = sqrtf(Bx*Bx+By*By);

    // Rotate the system so that point B is on the positive X axis.
    theCos = Bx/distAB;
    theSin = By/distAB;
    newX = Cx*theCos+Cy*theSin;
    Cy  = Cy*theCos-Cx*theSin; Cx = newX;
    newX = Dx*theCos+Dy*theSin;
    Dy  = Dy*theCos-Dx*theSin; Dx = newX;

    // FAIL: Lines are parallel.
    if (Cy == Dy) return false;

    // Discover the relative position of the intersection in the line AB
    *T = (Dx+(Cx-Dx)*Dy/(Dy-Cy))/distAB;

    // Success.
    return true;
}

NS_CC_END
