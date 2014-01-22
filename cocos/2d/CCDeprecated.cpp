/****************************************************************************
 Copyright (c) 2013      cocos2d-x.org
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

#include "cocos2d.h"

NS_CC_BEGIN

const Point CCPointZero = Point::ZERO;

/* The "zero" size -- equivalent to Size(0, 0). */
const Size CCSizeZero = Size::ZERO;

/* The "zero" rectangle -- equivalent to Rect(0, 0, 0, 0). */
const Rect CCRectZero = Rect::ZERO;


const Color3B ccWHITE = Color3B::WHITE;
const Color3B ccYELLOW = Color3B::YELLOW;
const Color3B ccGREEN = Color3B::GREEN;
const Color3B ccBLUE = Color3B::BLUE;
const Color3B ccRED = Color3B::RED;
const Color3B ccMAGENTA = Color3B::MAGENTA;
const Color3B ccBLACK = Color3B::BLACK;
const Color3B ccORANGE = Color3B::ORANGE;
const Color3B ccGRAY = Color3B::GRAY;

const BlendFunc kCCBlendFuncDisable = BlendFunc::DISABLE;

const char* kCCShader_PositionTextureColor = GLProgram::SHADER_NAME_POSITION_TEXTURE_COLOR;
const char* kCCShader_PositionTextureColorAlphaTest = GLProgram::SHADER_NAME_POSITION_TEXTURE_ALPHA_TEST;
const char* kCCShader_PositionColor = GLProgram::SHADER_NAME_POSITION_COLOR;
const char* kCCShader_PositionTexture = GLProgram::SHADER_NAME_POSITION_TEXTURE;
const char* kCCShader_PositionTexture_uColor = GLProgram::SHADER_NAME_POSITION_TEXTURE_U_COLOR;
const char* kCCShader_PositionTextureA8Color = GLProgram::SHADER_NAME_POSITION_TEXTURE_A8_COLOR;
const char* kCCShader_Position_uColor = GLProgram::SHADER_NAME_POSITION_U_COLOR;
const char* kCCShader_PositionLengthTexureColor = GLProgram::SHADER_NAME_POSITION_LENGTH_TEXTURE_COLOR;

// uniform names
const char* kCCUniformPMatrix_s = GLProgram::UNIFORM_NAME_P_MATRIX;
const char* kCCUniformMVMatrix_s = GLProgram::UNIFORM_NAME_MV_MATRIX;
const char* kCCUniformMVPMatrix_s = GLProgram::UNIFORM_NAME_MVP_MATRIX;
const char* kCCUniformTime_s = GLProgram::UNIFORM_NAME_TIME;
const char* kCCUniformSinTime_s = GLProgram::UNIFORM_NAME_SIN_TIME;
const char* kCCUniformCosTime_s	= GLProgram::UNIFORM_NAME_COS_TIME;
const char* kCCUniformRandom01_s = GLProgram::UNIFORM_NAME_RANDOM01;
const char* kCCUniformSampler_s	= GLProgram::UNIFORM_NAME_SAMPLER;
const char* kCCUniformAlphaTestValue = GLProgram::UNIFORM_NAME_ALPHA_TEST_VALUE;

// Attribute names
const char* kCCAttributeNameColor = GLProgram::ATTRIBUTE_NAME_COLOR;
const char* kCCAttributeNamePosition = GLProgram::ATTRIBUTE_NAME_POSITION;
const char* kCCAttributeNameTexCoord = GLProgram::ATTRIBUTE_NAME_TEX_COORD;

void ccDrawInit()
{
    DrawPrimitives::init();
}

void ccDrawFree()
{
    DrawPrimitives::free();
}

void ccDrawPoint( const Point& point )
{
    DrawPrimitives::drawPoint(point);
}

void ccDrawPoints( const Point *points, unsigned int numberOfPoints )
{
    DrawPrimitives::drawPoints(points, numberOfPoints);
}

void ccDrawLine( const Point& origin, const Point& destination )
{
    DrawPrimitives::drawLine(origin, destination);
}

void ccDrawRect( Point origin, Point destination )
{
    DrawPrimitives::drawRect(origin, destination);
}

void ccDrawSolidRect( Point origin, Point destination, Color4F color )
{
    DrawPrimitives::drawSolidRect(origin, destination, color);
}

void ccDrawPoly( const Point *vertices, unsigned int numOfVertices, bool closePolygon )
{
    DrawPrimitives::drawPoly(vertices, numOfVertices, closePolygon);
}

void ccDrawSolidPoly( const Point *poli, unsigned int numberOfPoints, Color4F color )
{
    DrawPrimitives::drawSolidPoly(poli, numberOfPoints, color);
}

void ccDrawCircle( const Point& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY)
{
    DrawPrimitives::drawCircle(center, radius, angle, segments, drawLineToCenter, scaleX, scaleY);
}

void ccDrawCircle( const Point& center, float radius, float angle, unsigned int segments, bool drawLineToCenter)
{
    DrawPrimitives::drawCircle(center, radius, angle, segments, drawLineToCenter);
}

void ccDrawSolidCircle( const Point& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY)
{
    DrawPrimitives::drawSolidCircle(center, radius, angle, segments, scaleX, scaleY);
}

void ccDrawSolidCircle( const Point& center, float radius, float angle, unsigned int segments)
{
    DrawPrimitives::drawSolidCircle(center, radius, angle, segments);
}

void ccDrawQuadBezier(const Point& origin, const Point& control, const Point& destination, unsigned int segments)
{
    DrawPrimitives::drawQuadBezier(origin, control, destination, segments);
}

void ccDrawCubicBezier(const Point& origin, const Point& control1, const Point& control2, const Point& destination, unsigned int segments)
{
    DrawPrimitives::drawCubicBezier(origin, control1, control2, destination, segments);
}

void ccDrawCatmullRom( PointArray *arrayOfControlPoints, unsigned int segments )
{
    DrawPrimitives::drawCatmullRom(arrayOfControlPoints, segments);
}

void ccDrawCardinalSpline( PointArray *config, float tension,  unsigned int segments )
{
    DrawPrimitives::drawCardinalSpline(config, tension, segments);
}

void ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a )
{
    DrawPrimitives::setDrawColor4B(r, g, b, a);
}

void ccDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a )
{
    DrawPrimitives::setDrawColor4F(r, g, b, a);
}

void ccPointSize( GLfloat pointSize )
{
    DrawPrimitives::setPointSize(pointSize);
}

NS_CC_END
