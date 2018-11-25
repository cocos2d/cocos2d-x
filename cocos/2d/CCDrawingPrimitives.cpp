/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2013 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2016 Chukong Technologies Inc.
Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.

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

#include "2d/CCDrawingPrimitives.h"

#include <string.h>
#include <cmath>

#include "2d/CCActionCatmullRom.h"
#include "base/CCDirector.h"
#include "renderer/CCGLProgramCache.h"
#include "renderer/CCRenderer.h"
#include "platform/CCGL.h"

NS_CC_BEGIN

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (push)
#pragma warning (disable: 4996)
#endif

#ifndef M_PI
    #define M_PI       3.14159265358979323846
#endif

namespace DrawPrimitives {

static bool s_initialized = false;
static GLProgram* s_shader = nullptr;
static int s_colorLocation = -1;
static Color4F s_color(1.0f,1.0f,1.0f,1.0f);
static int s_pointSizeLocation = -1;
static GLfloat s_pointSize = 1.0f;


static void lazy_init()
{
    if( ! s_initialized ) {

        //
        // Position and 1 color passed as a uniform (to simulate glColor4ub )
        //
        s_shader = GLProgramCache::getInstance()->getGLProgram(GLProgram::SHADER_NAME_POSITION_U_COLOR);
        s_shader->retain();
        
        s_colorLocation = s_shader->getUniformLocation("u_color");
        CHECK_GL_ERROR_DEBUG();
        s_pointSizeLocation = s_shader->getUniformLocation("u_pointSize");
        CHECK_GL_ERROR_DEBUG();

        s_initialized = true;
    }
}

// When switching from background to foreground on android, we want the parameters to be initialized again
void init()
{
    lazy_init();
}

void free()
{
    CC_SAFE_RELEASE_NULL(s_shader);
    s_initialized = false;
}

void drawPoint(const Vec2& point)
{
    lazy_init();

    Vec2 p;
    p.x = point.x;
    p.y = point.y;

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    s_shader->use();
    s_shader->setUniformsForBuiltins();

    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);
    s_shader->setUniformLocationWith1f(s_pointSizeLocation, s_pointSize);

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, &p);

    glDrawArrays(GL_POINTS, 0, 1);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,1);
}

void drawPoints( const Vec2 *points, unsigned int numberOfPoints )
{
    lazy_init();

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);
    s_shader->setUniformLocationWith1f(s_pointSizeLocation, s_pointSize);

    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, points);
    glDrawArrays(GL_POINTS, 0, (GLsizei) numberOfPoints);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, numberOfPoints);
}


void drawLine(const Vec2& origin, const Vec2& destination)
{
    lazy_init();

    Vec2 vertices[2] = {
        Vec2(origin.x, origin.y),
        Vec2(destination.x, destination.y)
    };

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_LINES, 0, 2);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,2);
}

void drawRect( Vec2 origin, Vec2 destination )
{
    drawLine(Vec2(origin.x, origin.y), Vec2(destination.x, origin.y));
    drawLine(Vec2(destination.x, origin.y), Vec2(destination.x, destination.y));
    drawLine(Vec2(destination.x, destination.y), Vec2(origin.x, destination.y));
    drawLine(Vec2(origin.x, destination.y), Vec2(origin.x, origin.y));
}

void drawSolidRect(Vec2 origin, Vec2 destination, Color4F color)
{
    Vec2 vertices[] = {
        origin,
        Vec2(destination.x, origin.y),
        destination,
        Vec2(origin.x, destination.y)
    };

    drawSolidPoly(vertices, 4, color );
}

void drawPoly(const Vec2 *poli, unsigned int numberOfPoints, bool closePolygon)
{
    lazy_init();

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, poli);

    if( closePolygon )
        glDrawArrays(GL_LINE_LOOP, 0, (GLsizei) numberOfPoints);
    else
        glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) numberOfPoints);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, numberOfPoints);
}

void drawSolidPoly(const Vec2 *poli, unsigned int numberOfPoints, Color4F color)
{
    lazy_init();

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, poli);
    glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) numberOfPoints);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, numberOfPoints);
}

void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY)
{
    lazy_init();

    int additionalSegment = 1;
    if (drawLineToCenter)
        additionalSegment++;

    const float coef = 2.0f * (float)M_PI/segments;

    GLfloat *vertices = (GLfloat*)calloc( 2*(segments+2), sizeof(GLfloat));
    if( ! vertices )
        return;

    for(unsigned int i = 0;i <= segments; i++) {
        float rads = i*coef;
        GLfloat j = radius * cosf(rads + angle) * scaleX + center.x;
        GLfloat k = radius * sinf(rads + angle) * scaleY + center.y;

        vertices[i*2] = j;
        vertices[i*2+1] = k;
    }
    vertices[(segments+1)*2] = center.x;
    vertices[(segments+1)*2+1] = center.y;

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments+additionalSegment);

    ::free( vertices );

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,segments+additionalSegment);
}

void drawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter)
{
    drawCircle(center, radius, angle, segments, drawLineToCenter, 1.0f, 1.0f);
}

void drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY)
{
    lazy_init();
    
    const float coef = 2.0f * (float)M_PI/segments;
    
    GLfloat *vertices = (GLfloat*)calloc( 2*(segments+2), sizeof(GLfloat));
    if( ! vertices )
        return;
    
    for(unsigned int i = 0;i <= segments; i++) {
        float rads = i*coef;
        GLfloat j = radius * cosf(rads + angle) * scaleX + center.x;
        GLfloat k = radius * sinf(rads + angle) * scaleY + center.y;
        
        vertices[i*2] = j;
        vertices[i*2+1] = k;
    }
    vertices[(segments+1)*2] = center.x;
    vertices[(segments+1)*2+1] = center.y;
    
    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);
    
    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);

    glDrawArrays(GL_TRIANGLE_FAN, 0, (GLsizei) segments+1);
    
    ::free( vertices );
    
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,segments+1);
}

void drawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments)
{
    drawSolidCircle(center, radius, angle, segments, 1.0f, 1.0f);
}

void drawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments)
{
    lazy_init();

    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];

    float t = 0.0f;
    for(unsigned int i = 0; i < segments; i++)
    {
        vertices[i].x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
        vertices[i].y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
        t += 1.0f / segments;
    }
    vertices[segments].x = destination.x;
    vertices[segments].y = destination.y;

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);
    CC_SAFE_DELETE_ARRAY(vertices);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,segments+1);
}

void drawCatmullRom( PointArray *points, unsigned int segments )
{
    drawCardinalSpline( points, 0.5f, segments );
}

void drawCardinalSpline( PointArray *config, float tension,  unsigned int segments )
{
    lazy_init();

    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];

    ssize_t p;
    float lt;
    float deltaT = 1.0f / config->count();

    for( unsigned int i=0; i < segments+1;i++) {

        float dt = (float)i / segments;

        // border
        if( dt == 1 ) {
            p = config->count() - 1;
            lt = 1;
        } else {
            p = dt / deltaT;
            lt = (dt - deltaT * (float)p) / deltaT;
        }

        // Interpolate
        Vec2 pp0 = config->getControlPointAtIndex(p-1);
        Vec2 pp1 = config->getControlPointAtIndex(p+0);
        Vec2 pp2 = config->getControlPointAtIndex(p+1);
        Vec2 pp3 = config->getControlPointAtIndex(p+2);

        Vec2 newPos = ccCardinalSplineAt( pp0, pp1, pp2, pp3, tension, lt);
        vertices[i].x = newPos.x;
        vertices[i].y = newPos.y;
    }

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*)&s_color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);

    CC_SAFE_DELETE_ARRAY(vertices);
    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,segments+1);
}

void drawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments)
{
    lazy_init();

    Vec2* vertices = new (std::nothrow) Vec2[segments + 1];

    float t = 0;
    for (unsigned int i = 0; i < segments; i++)
    {
        vertices[i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
        vertices[i].y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
        t += 1.0f / segments;
    }
    vertices[segments].x = destination.x;
    vertices[segments].y = destination.y;

    s_shader->use();
    s_shader->setUniformsForBuiltins();
    s_shader->setUniformLocationWith4fv(s_colorLocation, (GLfloat*) &s_color.r, 1);

    glEnableVertexAttribArray(GLProgram::VERTEX_ATTRIB_POSITION);
    glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertices);
    glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);
    CC_SAFE_DELETE_ARRAY(vertices);

    CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1,segments+1);
}

void setDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
    s_color.r = r;
    s_color.g = g;
    s_color.b = b;
    s_color.a = a;
}

void setPointSize( GLfloat pointSize )
{
    s_pointSize = pointSize * CC_CONTENT_SCALE_FACTOR();

    // TODO: glPointSize( pointSize );

}

void setDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
    s_color.r = r/255.0f;
    s_color.g = g/255.0f;
    s_color.b = b/255.0f;
    s_color.a = a/255.0f;
}

} // DrawPrimitives namespace

#if defined(__GNUC__) && ((__GNUC__ >= 4) || ((__GNUC__ == 3) && (__GNUC_MINOR__ >= 1)))
#pragma GCC diagnostic warning "-Wdeprecated-declarations"
#elif _MSC_VER >= 1400 //vs 2005 or higher
#pragma warning (pop)
#endif

NS_CC_END
