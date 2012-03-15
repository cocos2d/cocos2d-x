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
#include "ccGLStateCache.h"
#include "CCShaderCache.h"
#include "CCGLProgram.h"
#include <string.h>
#include <cmath>

NS_CC_BEGIN
#ifndef M_PI
	#define M_PI       3.14159265358979323846
#endif

static bool initialized = false;
static CCGLProgram *shader_ = NULL;
static int colorLocation_ = -1;
static ccColor4F color_ = {1,1,1,1};
static int pointSizeLocation_ = -1;
static GLfloat pointSize_ = 1;

static void lazy_init( void )
{
	if( ! initialized ) {

		//
		// Position and 1 color passed as a uniform (to similate glColor4ub )
		//
		shader_ = new CCGLProgram();
		shader_->initWithVertexShaderFilename("Position_uColor.vsh", "Position_uColor.fsh");

		shader_->addAttribute("aVertex" ,kCCVertexAttrib_Position);

		shader_->link();

		shader_->updateUniforms();

		colorLocation_ = glGetUniformLocation( shader_->program_, "u_color");
		pointSizeLocation_ = glGetUniformLocation( shader_->program_, "u_pointSize");

		initialized = true;
	}

}

void ccDrawPoint( const CCPoint& point )
{
	lazy_init();

	ccVertex2F p;
	p.x = point.x;
	p.y = point.y;

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );
	glUniform1f( pointSizeLocation_, pointSize_ );

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, &p);

	glDrawArrays(GL_POINTS, 0, 1);
}

void ccDrawPoints( const CCPoint *points, unsigned int numberOfPoints )
{
	lazy_init();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );
	glUniform1f( pointSizeLocation_, pointSize_ );

	// XXX: Mac OpenGL error. arrays can't go out of scope before draw is executed
	ccVertex2F* newPoints = new ccVertex2F[numberOfPoints];

	// iPhone and 32-bit machines optimization
	if( sizeof(CCPoint) == sizeof(ccVertex2F) )
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, points);

	else
	{
		// Mac on 64-bit
		for( unsigned int i=0; i<numberOfPoints;i++) {
			newPoints[i].x = points[i].x;
			newPoints[i].y = points[i].y;
		}
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, newPoints);
	}

	glDrawArrays(GL_POINTS, 0, (GLsizei) numberOfPoints);

	CC_SAFE_DELETE_ARRAY(newPoints);
}


void ccDrawLine( const CCPoint& origin, const CCPoint& destination )
{
	lazy_init();

	ccVertex2F vertices[2] = {
		{origin.x, origin.y},
		{destination.x, destination.y}
	};


	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINES, 0, 2);
}


void ccDrawPoly( const CCPoint *poli, unsigned int numberOfPoints, bool closePolygon )
{
	lazy_init();

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );

	// XXX: Mac OpenGL error. arrays can't go out of scope before draw is executed
	ccVertex2F* newPoli = new ccVertex2F[numberOfPoints];

	// iPhone and 32-bit machines optimization
	if( sizeof(CCPoint) == sizeof(ccVertex2F) )
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, poli);

	else
	{
		// Mac on 64-bit
		for( unsigned int i=0; i<numberOfPoints;i++) {
			newPoli[i].x = poli[i].x;
			newPoli[i].y = poli[i].y;
		}
		glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, newPoli);
	}

	if( closePolygon )
		glDrawArrays(GL_LINE_LOOP, 0, (GLsizei) numberOfPoints);
	else
		glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) numberOfPoints);

	CC_SAFE_DELETE_ARRAY(newPoli);
}

void ccDrawCircle( const CCPoint& center, float radius, float angle, int segments, bool drawLineToCenter)
{
	lazy_init();

	int additionalSegment = 1;
	if (drawLineToCenter)
		additionalSegment++;

	const float coef = 2.0f * (float)M_PI/segments;

	GLfloat *vertices = (GLfloat*)calloc( sizeof(GLfloat)*2*(segments+2), 1);
	if( ! vertices )
		return;

	for(unsigned int i = 0;i <= segments; i++) {
		float rads = i*coef;
		GLfloat j = radius * cosf(rads + angle) + center.x;
		GLfloat k = radius * sinf(rads + angle) + center.y;

		vertices[i*2] = j;
		vertices[i*2+1] = k;
	}
	vertices[(segments+1)*2] = center.x;
	vertices[(segments+1)*2+1] = center.y;

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments+additionalSegment);

	free( vertices );
}

void ccDrawQuadBezier(const CCPoint& origin, const CCPoint& control, const CCPoint& destination, int segments)
{
	lazy_init();

	ccVertex2F* vertices = new ccVertex2F[segments + 1];

	float t = 0.0f;
	for(unsigned int i = 0; i < segments; i++)
	{
		vertices[i].x = powf(1 - t, 2) * origin.x + 2.0f * (1 - t) * t * control.x + t * t * destination.x;
		vertices[i].y = powf(1 - t, 2) * origin.y + 2.0f * (1 - t) * t * control.y + t * t * destination.y;
		t += 1.0f / segments;
	}
	vertices[segments].x = destination.x;
	vertices[segments].y = destination.y;

	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);
	CC_SAFE_DELETE_ARRAY(vertices);
}

void ccDrawCubicBezier(const CCPoint& origin, const CCPoint& control1, const CCPoint& control2, const CCPoint& destination, int segments)
{
	lazy_init();

	ccVertex2F* vertices = new ccVertex2F[segments + 1];

	float t = 0;
	for(unsigned int i = 0; i < segments; i++)
	{
		vertices[i].x = powf(1 - t, 3) * origin.x + 3.0f * powf(1 - t, 2) * t * control1.x + 3.0f * (1 - t) * t * t * control2.x + t * t * t * destination.x;
		vertices[i].y = powf(1 - t, 3) * origin.y + 3.0f * powf(1 - t, 2) * t * control1.y + 3.0f * (1 - t) * t * t * control2.y + t * t * t * destination.y;
		t += 1.0f / segments;
	}
	vertices[segments].x = destination.x;
	vertices[segments].y = destination.y;


	ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position );
	ccGLUseProgram( shader_->program_ );
	ccGLUniformModelViewProjectionMatrix( shader_ );

	glUniform4f( colorLocation_, color_.r, color_.g, color_.b, color_.a );

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_LINE_STRIP, 0, (GLsizei) segments + 1);
	CC_SAFE_DELETE_ARRAY(vertices);
}

void ccDrawColor4f( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
	color_.r = r;
	color_.g = g;
	color_.b = b;
	color_.a = a;
}

void ccPointSize( GLfloat pointSize )
{
	pointSize_ = pointSize * CC_CONTENT_SCALE_FACTOR();

	//TODO :glPointSize( pointSize );

}

void ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
	color_.r = r/255.0f;
	color_.g = g/255.0f;
	color_.b = b/255.0f;
	color_.a = a/255.0f;
}

NS_CC_END
