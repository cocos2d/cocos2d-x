/****************************************************************************
 Copyright (c) 2013 cocos2d-x.org
 
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

const int kCCVertexAttrib_Position = GLProgram::VERTEX_ATTRIB_POSITION;
const int kCCVertexAttrib_Color = GLProgram::VERTEX_ATTRIB_COLOR;
const int kCCVertexAttrib_TexCoords = GLProgram::VERTEX_ATTRIB_TEX_COORDS;
const int kCCVertexAttrib_MAX = GLProgram::VERTEX_ATTRIB_MAX;

const int kCCUniformPMatrix = GLProgram::UNIFORM_P_MATRIX;
const int kCCUniformMVMatrix = GLProgram::UNIFORM_MV_MATRIX;
const int kCCUniformMVPMatrix = GLProgram::UNIFORM_MVP_MATRIX;
const int kCCUniformTime = GLProgram::UNIFORM_TIME;
const int kCCUniformSinTime = GLProgram::UNIFORM_SIN_TIME;
const int kCCUniformCosTime = GLProgram::UNIFORM_COS_TIME;
const int kCCUniformRandom01 = GLProgram::UNIFORM_RANDOM01;
const int kCCUniformSampler = GLProgram::UNIFORM_SAMPLER;
const int kCCUniform_MAX = GLProgram::UNIFORM_MAX;

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

const int kCCVertexAttribFlag_None = GL::VERTEX_ATTRIB_FLAT_NONE;
const int kCCVertexAttribFlag_Position = GL::VERTEX_ATTRIB_FLAG_POSITION;
const int kCCVertexAttribFlag_Color = GL::VERTEX_ATTRIB_FLAG_COLOR;
const int kCCVertexAttribFlag_TexCoords = GL::VERTEX_ATTRIB_FLAG_TEX_COORDS;
const int kCCVertexAttribFlag_PosColorTex = GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX;

const int kCCProgressTimerTypeRadial = ProgressTimer::RADIAL;
const int kCCProgressTimerTypeBar = ProgressTimer::BAR;

const Director::Projection kCCDirectorProjection2D = Director::Projection::_2D;
const Director::Projection kCCDirectorProjection3D = Director::Projection::_3D;
const Director::Projection kCCDirectorProjectionCustom = Director::Projection::CUSTOM;
const Director::Projection kCCDirectorProjectionDefault = Director::Projection::DEFAULT;

const int kCCParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
const int kCCParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
const int kCCParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

const ParticleSystem::Mode kCCParticleModeGravity = ParticleSystem::Mode::GRAVITY;
const ParticleSystem::Mode kCCParticleModeRadius = ParticleSystem::Mode::RADIUS;
const int kCCParticleDefaultCapacity = kParticleDefaultCapacity;

const ParticleSystem::PositionType kCCPositionTypeFree =  ParticleSystem::PositionType::FREE;
const ParticleSystem::PositionType kCCPositionTypeRelative =  ParticleSystem::PositionType::RELATIVE;
const ParticleSystem::PositionType kCCPositionTypeGrouped =  ParticleSystem::PositionType::GROUPED;

const Label::VAlignment kCCVerticalTextAlignmentTop = Label::VAlignment::TOP;
const Label::VAlignment kCCVerticalTextAlignmentCenter = Label::VAlignment::CENTER;
const Label::VAlignment kCCVerticalTextAlignmentBottom = Label::VAlignment::BOTTOM;

const Label::HAlignment kCCTextAlignmentLeft = Label::HAlignment::LEFT;
const Label::HAlignment kCCTextAlignmentCenter = Label::HAlignment::CENTER;
const Label::HAlignment kCCTextAlignmentRight = Label::HAlignment::RIGHT;

const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGBA8888 = Texture2D::PixelFormat::RGBA8888;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB888 = Texture2D::PixelFormat::RGB888;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB565 = Texture2D::PixelFormat::RGB565;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_A8 = Texture2D::PixelFormat::A8;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_I8 = Texture2D::PixelFormat::I8;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_AI88 = Texture2D::PixelFormat::AI88;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGBA4444 = Texture2D::PixelFormat::RGBA4444;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB5A1 = Texture2D::PixelFormat::RGB5A1;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_PVRTC4 = Texture2D::PixelFormat::PVRTC4;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_PVRTC2 = Texture2D::PixelFormat::PVRTC2;
const Texture2D::PixelFormat kCCTexture2DPixelFormat_Default = Texture2D::PixelFormat::DEFAULT;

const int kCCMenuHandlerPriority = Menu::HANDLER_PRIORITY;
const Menu::State kCCMenuStateWaiting = Menu::State::WAITING;
const Menu::State kCCMenuStateTrackingTouch = Menu::State::TRACKING_TOUCH;

const Touch::DispatchMode kCCTouchesOneByOne = Touch::DispatchMode::ONE_BY_ONE;
const Touch::DispatchMode kCCTouchesAllAtOnce = Touch::DispatchMode::ALL_AT_ONCE;

const Image::Format kCCImageFormatPNG = Image::Format::PNG;
const Image::Format kCCImageFormatJPEG = Image::Format::JPG;

const TransitionScene::Orientation kCCTransitionOrientationLeftOver = TransitionScene::Orientation::LEFT_OVER;
const TransitionScene::Orientation kCCTransitionOrientationRightOver = TransitionScene::Orientation::RIGHT_OVER;
const TransitionScene::Orientation kCCTransitionOrientationUpOver = TransitionScene::Orientation::UP_OVER;
const TransitionScene::Orientation kCCTransitionOrientationDownOver = TransitionScene::Orientation::DOWN_OVER;

const int kCCPrioritySystem = Scheduler::PRIORITY_SYSTEM;
const int kCCPriorityNonSystemMin = Scheduler::PRIORITY_NON_SYSTEM_MIN;

const int kCCActionTagInvalid = kActionTagInvalid;

const int kCCNodeTagInvalid = kNodeTagInvalid;

const int kCCNodeOnEnter = kNodeOnEnter;
const int kCCNodeOnExit = kNodeOnExit;
const int kCCNodeOnEnterTransitionDidFinish = kNodeOnEnterTransitionDidFinish;
const int kCCNodeOnExitTransitionDidStart = kNodeOnExitTransitionDidStart;
const int kCCNodeOnCleanup = kNodeOnCleanup;


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