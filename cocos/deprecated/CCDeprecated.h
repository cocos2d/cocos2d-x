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

/** Add deprecated global functions and variables here
 */

#ifndef __COCOS2D_CCDEPRECATED_H__
#define __COCOS2D_CCDEPRECATED_H__

#include <math.h>
#include "math/CCGeometry.h"
#include "base/ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

/** Helper macro that creates a Vec2
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) inline Vec2 ccp(float x, float y)
{
    return Vec2(x, y);
}

/** Returns opposite of point.
 @return Vec2
 @since v0.7.2
 @deprecated please use Vec2::-, for example: -v1
 */
CC_DEPRECATED(v3) static inline Vec2
ccpNeg(const Vec2& v)
{
    return -v;
}

/** Calculates sum of two points.
 @return Vec2
 @since v0.7.2
 @deprecated please use Vec2::+, for example: v1 + v2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpAdd(const Vec2& v1, const Vec2& v2)
{
    return v1 + v2;
}

/** Calculates difference of two points.
 @return Vec2
 @since v0.7.2
 @deprecated please use Vec2::-, for example: v1 - v2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpSub(const Vec2& v1, const Vec2& v2)
{
    return v1 - v2;
}

/** Returns point multiplied by given factor.
 @return Vec2
 @since v0.7.2
 @deprecated please use Vec2::*, for example: v1 * v2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpMult(const Vec2& v, const float s)
{
    return v * s;
}

/** Calculates midpoint between two points.
 @return Vec2
 @since v0.7.2
 @deprecated please use it like (v1 + v2) / 2.0f
 */
CC_DEPRECATED(v3) static inline Vec2
ccpMidpoint(const Vec2& v1, const Vec2& v2)
{
    return v1.getMidpoint(v2);
}

/** Calculates dot product of two points.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline float
ccpDot(const Vec2& v1, const Vec2& v2)
{
    return v1.dot(v2);
}

/** Calculates cross product of two points.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline float
ccpCross(const Vec2& v1, const Vec2& v2)
{
    return v1.cross(v2);
}

/** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpPerp(const Vec2& v)
{
    return v.getPerp();
}

/** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpRPerp(const Vec2& v)
{
    return v.getRPerp();
}

/** Calculates the projection of v1 over v2.
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpProject(const Vec2& v1, const Vec2& v2)
{
    return v1.project(v2);
}

/** Rotates two points.
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpRotate(const Vec2& v1, const Vec2& v2)
{
    return v1.rotate(v2);
}

/** Unrotates two points.
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2
ccpUnrotate(const Vec2& v1, const Vec2& v2)
{
    return v1.unrotate(v2);
}

/** Calculates the square length of a Vec2 (not calling sqrt() )
 @return float
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline float
ccpLengthSQ(const Vec2& v)
{
    return v.getLengthSq();
}


/** Calculates the square distance between two points (not calling sqrt() )
 @return float
 @since v1.1
 */
CC_DEPRECATED(v3) static inline float
ccpDistanceSQ(const Vec2 p1, const Vec2 p2)
{
    return (p1 - p2).getLengthSq();
}


/** Calculates distance between point an origin
 @return float
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline float ccpLength(const Vec2& v)
{
    return v.getLength();
}

/** Calculates the distance between two points
 @return float
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline float ccpDistance(const Vec2& v1, const Vec2& v2)
{
    return v1.getDistance(v2);
}

/** Returns point multiplied to a length of 1.
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2 ccpNormalize(const Vec2& v)
{
    return v.getNormalized();
}

/** Converts radians to a normalized vector.
 @return Vec2
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline Vec2 ccpForAngle(const float a)
{
    return Vec2::forAngle(a);
}

/** Converts a vector to radians.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED(v3) static inline float ccpToAngle(const Vec2& v)
{
    return v.getAngle();
}


/** Clamp a point between from and to.
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline Vec2 ccpClamp(const Vec2& p, const Vec2& from, const Vec2& to)
{
    return p.getClampPoint(from, to);
}

/** Quickly convert Size to a Vec2
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline Vec2 ccpFromSize(const Size& s)
{
    return Vec2(s);
}

/** Run a math operation function on each point component
 * absf, fllorf, ceilf, roundf
 * any function that has the signature: float func(float);
 * For example: let's try to take the floor of x,y
 * ccpCompOp(p,floorf);
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline Vec2 ccpCompOp(const Vec2& p, float (*opFunc)(float))
{
    return p.compOp(opFunc);
}

/** Linear Interpolation between two points a and b
 @returns
 alpha == 0 ? a
 alpha == 1 ? b
 otherwise a value between a..b
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline Vec2 ccpLerp(const Vec2& a, const Vec2& b, float alpha)
{
    return a.lerp(b, alpha);
}


/** @returns if points have fuzzy equality which means equal with some degree of variance.
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline bool ccpFuzzyEqual(const Vec2& a, const Vec2& b, float variance)
{
    return a.fuzzyEquals(b, variance);
}


/** Multiplies a and b components, a.x*b.x, a.y*b.y
 @returns a component-wise multiplication
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline Vec2 ccpCompMult(const Vec2& a, const Vec2& b)
{
    return Vec2(a.x * b.x, a.y * b.y);
}

/** @returns the signed angle in radians between two vector directions
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline float ccpAngleSigned(const Vec2& a, const Vec2& b)
{
    return a.getAngle(b);
}

/** @returns the angle in radians between two vector directions
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline float ccpAngle(const Vec2& a, const Vec2& b)
{
    return a.getAngle(b);
}

/** Rotates a point counter clockwise by the angle around a pivot
 @param v is the point to rotate
 @param pivot is the pivot, naturally
 @param angle is the angle of rotation cw in radians
 @returns the rotated point
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline Vec2 ccpRotateByAngle(const Vec2& v, const Vec2& pivot, float angle)
{
    return v.rotateByAngle(pivot, angle);
}

/** A general line-line intersection test
 @param p1
 is the startpoint for the first line P1 = (p1 - p2)
 @param p2
 is the endpoint for the first line P1 = (p1 - p2)
 @param p3
 is the startpoint for the second line P2 = (p3 - p4)
 @param p4
 is the endpoint for the second line P2 = (p3 - p4)
 @param s
 is the range for a hitpoint in P1 (pa = p1 + s*(p2 - p1))
 @param t
 is the range for a hitpoint in P3 (pa = p2 + t*(p4 - p3))
 @return bool
 indicating successful intersection of a line
 note that to truly test intersection for segments we have to make
 sure that s & t lie within [0..1] and for rays, make sure s & t > 0
 the hit point is        p3 + t * (p4 - p3);
 the hit point also is    p1 + s * (p2 - p1);
 @since v0.99.1
 */
CC_DEPRECATED(v3) static inline bool ccpLineIntersect(const Vec2& p1, const Vec2& p2,
                                                     const Vec2& p3, const Vec2& p4,
                                                     float *s, float *t)
{
    return Vec2::isLineIntersect(p1, p2, p3, p4, s, t);
}

/*
 ccpSegmentIntersect returns true if Segment A-B intersects with segment C-D
 @since v1.0.0
 */
CC_DEPRECATED(v3) static inline bool ccpSegmentIntersect(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D)
{
    return Vec2::isSegmentIntersect(A, B, C, D);
}

/*
 ccpIntersectPoint returns the intersection point of line A-B, C-D
 @since v1.0.0
 */
CC_DEPRECATED(v3) static inline Vec2 ccpIntersectPoint(const Vec2& A, const Vec2& B, const Vec2& C, const Vec2& D)
{
    return Vec2::getIntersectPoint(A, B, C, D);
}

CC_DEPRECATED(v3) inline Vec2 CCPointMake(float x, float y)
{
    return Vec2(x, y);
}

CC_DEPRECATED(v3) inline Size CCSizeMake(float width, float height)
{
    return Size(width, height);
}

CC_DEPRECATED(v3) inline Rect CCRectMake(float x, float y, float width, float height)
{
    return Rect(x, y, width, height);
}


CC_DEPRECATED(v3) extern const Vec2 CCPointZero;

/* The "zero" size -- equivalent to Size(0, 0). */
CC_DEPRECATED(v3) extern const Size CCSizeZero;

/* The "zero" rectangle -- equivalent to Rect(0, 0, 0, 0). */
CC_DEPRECATED(v3) extern const Rect CCRectZero;


CC_DEPRECATED(v3) extern const Color3B ccWHITE;
CC_DEPRECATED(v3) extern const Color3B ccYELLOW;
CC_DEPRECATED(v3) extern const Color3B ccGREEN;
CC_DEPRECATED(v3) extern const Color3B ccBLUE;
CC_DEPRECATED(v3) extern const Color3B ccRED;
CC_DEPRECATED(v3) extern const Color3B ccMAGENTA;
CC_DEPRECATED(v3) extern const Color3B ccBLACK;
CC_DEPRECATED(v3) extern const Color3B ccORANGE;
CC_DEPRECATED(v3) extern const Color3B ccGRAY;

CC_DEPRECATED(v3) extern const BlendFunc kCCBlendFuncDisable;

CC_DEPRECATED(v3) static inline Color3B ccc3(GLubyte r, GLubyte g, GLubyte b)
{
    return Color3B(r, g, b);
}

CC_DEPRECATED(v3) static inline bool ccc3BEqual(const Color3B &col1, const Color3B &col2)
{
    return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

CC_DEPRECATED(v3) static inline Color4B
ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
    return Color4B(r, g, b, o);
}

CC_DEPRECATED(v3) static inline Color4F ccc4FFromccc3B(Color3B c)
{
    return Color4F(c.r/255.f, c.g/255.f, c.b/255.f, 1.f);
}

CC_DEPRECATED(v3) static inline Color4F
ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a)
{
    return Color4F(r, g, b, a);
}

CC_DEPRECATED(v3) static inline Color4F ccc4FFromccc4B(Color4B c)
{
    return Color4F(c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f);
}

CC_DEPRECATED(v3) static inline Color4B ccc4BFromccc4F(Color4F c)
{
        return Color4B((GLubyte)(c.r*255), (GLubyte)(c.g*255), (GLubyte)(c.b*255), (GLubyte)(c.a*255));
}

CC_DEPRECATED(v3) static inline bool ccc4FEqual(Color4F a, Color4F b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

CC_DEPRECATED(v3) static inline Vec2 vertex2(const float x, const float y)
{
    Vec2 c(x, y);
    return c;
}

CC_DEPRECATED(v3) static inline Vec3 vertex3(const float x, const float y, const float z)
{
    Vec3 c(x, y, z);
    return c;
}

CC_DEPRECATED(v3) static inline Tex2F tex2(const float u, const float v)
{
    Tex2F t(u , v);
    return t;
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformMake(float a, float b, float c, float d, float tx, float ty)
{
    return AffineTransformMake(a, b, c, d, tx, ty);
}

CC_DEPRECATED(v3) static inline Vec2 CCPointApplyAffineTransform(const Vec2& point, const AffineTransform& t)
{
    return PointApplyAffineTransform(point, t);
}

CC_DEPRECATED(v3) static inline Size CCSizeApplyAffineTransform(const Size& size, const AffineTransform& t)
{
    return SizeApplyAffineTransform(size, t);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformMakeIdentity()
{
    return AffineTransformMakeIdentity();
}

CC_DEPRECATED(v3) static inline Rect CCRectApplyAffineTransform(const Rect& rect, const AffineTransform& anAffineTransform)
{
    return RectApplyAffineTransform(rect, anAffineTransform);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformTranslate(const AffineTransform& t, float tx, float ty)
{
    return AffineTransformTranslate(t, tx, ty);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformRotate(const AffineTransform& aTransform, float anAngle)
{
    return AffineTransformRotate(aTransform, anAngle);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformScale(const AffineTransform& t, float sx, float sy)
{
    return AffineTransformScale(t, sx, sy);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformConcat(const AffineTransform& t1, const AffineTransform& t2)
{
    return AffineTransformConcat(t1, t2);
}

CC_DEPRECATED(v3) static inline bool CCAffineTransformEqualToTransform(const AffineTransform& t1, const AffineTransform& t2)
{
    return AffineTransformEqualToTransform(t1, t2);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformInvert(const AffineTransform& t)
{
    return AffineTransformInvert(t);
}

CC_DEPRECATED(v3) static inline AffineTransform CCAffineTransformIdentity()
{
    return AffineTransformMakeIdentity();
}

// CC prefix compatibility
CC_DEPRECATED(v3) typedef GLProgramCache ShaderCache;

CC_DEPRECATED(v3) typedef void* CCZone;

CC_DEPRECATED(v3) const int kCCVertexAttrib_Position = GLProgram::VERTEX_ATTRIB_POSITION;
CC_DEPRECATED(v3) const int kCCVertexAttrib_Color = GLProgram::VERTEX_ATTRIB_COLOR;
CC_DEPRECATED(v3) const int kCCVertexAttrib_TexCoords = GLProgram::VERTEX_ATTRIB_TEX_COORD;
CC_DEPRECATED(v3) const int kCCVertexAttrib_MAX = GLProgram::VERTEX_ATTRIB_MAX;

CC_DEPRECATED(v3) const int kCCUniformPMatrix = GLProgram::UNIFORM_P_MATRIX;
CC_DEPRECATED(v3) const int kCCUniformMVMatrix = GLProgram::UNIFORM_MV_MATRIX;
CC_DEPRECATED(v3) const int kCCUniformMVPMatrix = GLProgram::UNIFORM_MVP_MATRIX;
CC_DEPRECATED(v3) const int kCCUniformTime = GLProgram::UNIFORM_TIME;
CC_DEPRECATED(v3) const int kCCUniformSinTime = GLProgram::UNIFORM_SIN_TIME;
CC_DEPRECATED(v3) const int kCCUniformCosTime = GLProgram::UNIFORM_COS_TIME;
CC_DEPRECATED(v3) const int kCCUniformRandom01 = GLProgram::UNIFORM_RANDOM01;
CC_DEPRECATED(v3) const int kCCUniformSampler = GLProgram::UNIFORM_SAMPLER0;
CC_DEPRECATED(v3) const int kCCUniform_MAX = GLProgram::UNIFORM_MAX;

CC_DEPRECATED(v3) extern const char* kCCShader_PositionTextureColor;
CC_DEPRECATED(v3) extern const char* kCCShader_PositionTextureColorAlphaTest;
CC_DEPRECATED(v3) extern const char* kCCShader_PositionColor;
CC_DEPRECATED(v3) extern const char* kCCShader_PositionTexture;
CC_DEPRECATED(v3) extern const char* kCCShader_PositionTexture_uColor;
CC_DEPRECATED(v3) extern const char* kCCShader_PositionTextureA8Color;
CC_DEPRECATED(v3) extern const char* kCCShader_Position_uColor;
CC_DEPRECATED(v3) extern const char* kCCShader_PositionLengthTexureColor;

// uniform names
CC_DEPRECATED(v3) extern const char* kCCUniformPMatrix_s;
CC_DEPRECATED(v3) extern const char* kCCUniformMVMatrix_s;
CC_DEPRECATED(v3) extern const char* kCCUniformMVPMatrix_s;
CC_DEPRECATED(v3) extern const char* kCCUniformTime_s;
CC_DEPRECATED(v3) extern const char* kCCUniformSinTime_s;
CC_DEPRECATED(v3) extern const char* kCCUniformCosTime_s;
CC_DEPRECATED(v3) extern const char* kCCUniformRandom01_s;
CC_DEPRECATED(v3) extern const char* kCCUniformSampler_s;
CC_DEPRECATED(v3) extern const char* kCCUniformAlphaTestValue;

// Attribute names
CC_DEPRECATED(v3) extern const char*    kCCAttributeNameColor;
CC_DEPRECATED(v3) extern const char*    kCCAttributeNamePosition;
CC_DEPRECATED(v3) extern const char*    kCCAttributeNameTexCoord;

CC_DEPRECATED(v3) const int kCCVertexAttribFlag_None = GL::VERTEX_ATTRIB_FLAG_NONE;
CC_DEPRECATED(v3) const int kCCVertexAttribFlag_Position = GL::VERTEX_ATTRIB_FLAG_POSITION;
CC_DEPRECATED(v3) const int kCCVertexAttribFlag_Color = GL::VERTEX_ATTRIB_FLAG_COLOR;
CC_DEPRECATED(v3) const int kCCVertexAttribFlag_TexCoords = GL::VERTEX_ATTRIB_FLAG_TEX_COORD;
CC_DEPRECATED(v3) const int kCCVertexAttribFlag_PosColorTex = GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX;

CC_DEPRECATED(v3) const ProgressTimer::Type kCCProgressTimerTypeRadial = ProgressTimer::Type::RADIAL;
CC_DEPRECATED(v3) const ProgressTimer::Type kCCProgressTimerTypeBar = ProgressTimer::Type::BAR;
CC_DEPRECATED(v3) typedef ProgressTimer::Type ProgressTimerType;

CC_DEPRECATED(v3) const Director::Projection kCCDirectorProjection2D = Director::Projection::_2D;
CC_DEPRECATED(v3) const Director::Projection kCCDirectorProjection3D = Director::Projection::_3D;
CC_DEPRECATED(v3) const Director::Projection kCCDirectorProjectionCustom = Director::Projection::CUSTOM;
CC_DEPRECATED(v3) const Director::Projection kCCDirectorProjectionDefault = Director::Projection::DEFAULT;
CC_DEPRECATED(v3) typedef Director::Projection ccDirectorProjection;

CC_DEPRECATED(v3) const TextVAlignment kCCVerticalTextAlignmentTop = TextVAlignment::TOP;
CC_DEPRECATED(v3) const TextVAlignment kCCVerticalTextAlignmentCenter = TextVAlignment::CENTER;
CC_DEPRECATED(v3) const TextVAlignment kCCVerticalTextAlignmentBottom = TextVAlignment::BOTTOM;

CC_DEPRECATED(v3) const TextHAlignment kCCTextAlignmentLeft = TextHAlignment::LEFT;
CC_DEPRECATED(v3) const TextHAlignment kCCTextAlignmentCenter = TextHAlignment::CENTER;
CC_DEPRECATED(v3) const TextHAlignment kCCTextAlignmentRight = TextHAlignment::RIGHT;

CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGBA8888 = Texture2D::PixelFormat::RGBA8888;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB888 = Texture2D::PixelFormat::RGB888;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB565 = Texture2D::PixelFormat::RGB565;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_A8 = Texture2D::PixelFormat::A8;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_I8 = Texture2D::PixelFormat::I8;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_AI88 = Texture2D::PixelFormat::AI88;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGBA4444 = Texture2D::PixelFormat::RGBA4444;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB5A1 = Texture2D::PixelFormat::RGB5A1;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_PVRTC4 = Texture2D::PixelFormat::PVRTC4;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_PVRTC2 = Texture2D::PixelFormat::PVRTC2;
CC_DEPRECATED(v3) const Texture2D::PixelFormat kCCTexture2DPixelFormat_Default = Texture2D::PixelFormat::DEFAULT;

CC_DEPRECATED(v3) typedef Texture2D::PixelFormat CCTexture2DPixelFormat;


CC_DEPRECATED(v3) const int kCCParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
CC_DEPRECATED(v3) const int kCCParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
CC_DEPRECATED(v3) const int kCCParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

CC_DEPRECATED(v3) const int kParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
CC_DEPRECATED(v3) const int kParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
CC_DEPRECATED(v3) const int kParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

CC_DEPRECATED(v3) const ParticleSystem::Mode kCCParticleModeGravity = ParticleSystem::Mode::GRAVITY;
CC_DEPRECATED(v3) const ParticleSystem::Mode kCCParticleModeRadius = ParticleSystem::Mode::RADIUS;
CC_DEPRECATED(v3) const int kCCParticleDefaultCapacity = kParticleDefaultCapacity;

CC_DEPRECATED(v3) const ParticleSystem::PositionType kCCPositionTypeFree =  ParticleSystem::PositionType::FREE;
CC_DEPRECATED(v3) const ParticleSystem::PositionType kCCPositionTypeRelative =  ParticleSystem::PositionType::RELATIVE;
CC_DEPRECATED(v3) const ParticleSystem::PositionType kCCPositionTypeGrouped =  ParticleSystem::PositionType::GROUPED;

CC_DEPRECATED(v3) typedef ParticleSystem::PositionType tPositionType;

#define kCCLabelAutomaticWidth  kLabelAutomaticWidth


CC_DEPRECATED(v3) const Menu::State kCCMenuStateWaiting = Menu::State::WAITING;
CC_DEPRECATED(v3) const Menu::State kCCMenuStateTrackingTouch = Menu::State::TRACKING_TOUCH;

CC_DEPRECATED(v3) typedef Menu::State tMenuState;

CC_DEPRECATED(v3) const Touch::DispatchMode kCCTouchesOneByOne = Touch::DispatchMode::ONE_BY_ONE;
CC_DEPRECATED(v3) const Touch::DispatchMode kCCTouchesAllAtOnce = Touch::DispatchMode::ALL_AT_ONCE;

CC_DEPRECATED(v3) typedef Touch::DispatchMode ccTouchesMode;

CC_DEPRECATED(v3) const Image::Format kCCImageFormatPNG = Image::Format::PNG;
CC_DEPRECATED(v3) const Image::Format kCCImageFormatJPEG = Image::Format::JPG;

CC_DEPRECATED(v3) typedef Image::Format tImageFormat;

CC_DEPRECATED(v3) const TransitionScene::Orientation kCCTransitionOrientationLeftOver = TransitionScene::Orientation::LEFT_OVER;
CC_DEPRECATED(v3) const TransitionScene::Orientation kCCTransitionOrientationRightOver = TransitionScene::Orientation::RIGHT_OVER;
CC_DEPRECATED(v3) const TransitionScene::Orientation kCCTransitionOrientationUpOver = TransitionScene::Orientation::UP_OVER;
CC_DEPRECATED(v3) const TransitionScene::Orientation kCCTransitionOrientationDownOver = TransitionScene::Orientation::DOWN_OVER;

CC_DEPRECATED(v3) typedef TransitionScene::Orientation tOrientation;

CC_DEPRECATED(v3) const int kCCPrioritySystem = Scheduler::PRIORITY_SYSTEM;
CC_DEPRECATED(v3) const int kCCPriorityNonSystemMin = Scheduler::PRIORITY_NON_SYSTEM_MIN;

CC_DEPRECATED(v3) const int kCCActionTagInvalid = Action::INVALID_TAG;
CC_DEPRECATED(v3) const int kCCNodeTagInvalid = Node::INVALID_TAG;

CC_DEPRECATED(v3) const int kCCNodeOnEnter = kNodeOnEnter;
CC_DEPRECATED(v3) const int kCCNodeOnExit = kNodeOnExit;
CC_DEPRECATED(v3) const int kCCNodeOnEnterTransitionDidFinish = kNodeOnEnterTransitionDidFinish;
CC_DEPRECATED(v3) const int kCCNodeOnExitTransitionDidStart = kNodeOnExitTransitionDidStart;
CC_DEPRECATED(v3) const int kCCNodeOnCleanup = kNodeOnCleanup;


CC_DEPRECATED(v3) const LanguageType kLanguageEnglish     = LanguageType::ENGLISH;
CC_DEPRECATED(v3) const LanguageType kLanguageChinese     = LanguageType::CHINESE;
CC_DEPRECATED(v3) const LanguageType kLanguageFrench      = LanguageType::FRENCH;
CC_DEPRECATED(v3) const LanguageType kLanguageItalian     = LanguageType::ITALIAN;
CC_DEPRECATED(v3) const LanguageType kLanguageGerman      = LanguageType::GERMAN;
CC_DEPRECATED(v3) const LanguageType kLanguageSpanish     = LanguageType::SPANISH;
CC_DEPRECATED(v3) const LanguageType kLanguageRussian     = LanguageType::RUSSIAN;
CC_DEPRECATED(v3) const LanguageType kLanguageKorean      = LanguageType::KOREAN;
CC_DEPRECATED(v3) const LanguageType kLanguageJapanese    = LanguageType::JAPANESE;
CC_DEPRECATED(v3) const LanguageType kLanguageHungarian   = LanguageType::HUNGARIAN;
CC_DEPRECATED(v3) const LanguageType kLanguagePortuguese  = LanguageType::PORTUGUESE;
CC_DEPRECATED(v3) const LanguageType kLanguageArabic      = LanguageType::ARABIC;
CC_DEPRECATED(v3) const LanguageType kLanguageNorwegian   = LanguageType::NORWEGIAN;
CC_DEPRECATED(v3) const LanguageType kLanguagePolish      = LanguageType::POLISH;
CC_DEPRECATED(v3) typedef LanguageType ccLanguageType;


CC_DEPRECATED(v3) const Application::Platform kTargetWindows      = Application::Platform::OS_WINDOWS;
CC_DEPRECATED(v3) const Application::Platform kTargetLinux        = Application::Platform::OS_LINUX;
CC_DEPRECATED(v3) const Application::Platform kTargetMacOS        = Application::Platform::OS_MAC;
CC_DEPRECATED(v3) const Application::Platform kTargetAndroid      = Application::Platform::OS_ANDROID;
CC_DEPRECATED(v3) const Application::Platform kTargetIphone       = Application::Platform::OS_IPHONE;
CC_DEPRECATED(v3) const Application::Platform kTargetIpad         = Application::Platform::OS_IPAD;
CC_DEPRECATED(v3) const Application::Platform kTargetWinRT        = Application::Platform::OS_WINRT;
CC_DEPRECATED(v3) const Application::Platform kTargetWP8          = Application::Platform::OS_WP8;
CC_DEPRECATED(v3) typedef Application::Platform TargetPlatform;

CC_DEPRECATED(v3) const ResolutionPolicy kResolutionExactFit      = ResolutionPolicy::EXACT_FIT;
CC_DEPRECATED(v3) const ResolutionPolicy kResolutionNoBorder      = ResolutionPolicy::NO_BORDER;
CC_DEPRECATED(v3) const ResolutionPolicy kResolutionShowAll       = ResolutionPolicy::SHOW_ALL;
CC_DEPRECATED(v3) const ResolutionPolicy kResolutionFixedHeight   = ResolutionPolicy::FIXED_HEIGHT;
CC_DEPRECATED(v3) const ResolutionPolicy kResolutionFixedWidth    = ResolutionPolicy::FIXED_WIDTH;
CC_DEPRECATED(v3) const ResolutionPolicy kResolutionUnKnown       = ResolutionPolicy::UNKNOWN;


#define kCCTMXTileHorizontalFlag      kTMXTileHorizontalFlag
#define kCCTMXTileVerticalFlag        kTMXTileVerticalFlag
#define kCCTMXTileDiagonalFlag        kTMXTileDiagonalFlag
#define kCCFlipedAll                  kFlipedAll
#define kCCFlippedMask                kTMXFlippedMask


/** use log() instead */
CC_DEPRECATED(v3) void CC_DLL CCLog(const char * pszFormat, ...) CC_FORMAT_PRINTF(1, 2);

CC_DEPRECATED(v3) void CC_DLL ccDrawInit();
CC_DEPRECATED(v3) void CC_DLL ccDrawFree();
CC_DEPRECATED(v3) void CC_DLL ccDrawPoint( const Vec2& point );
CC_DEPRECATED(v3) void CC_DLL ccDrawPoints( const Vec2 *points, unsigned int numberOfPoints );
CC_DEPRECATED(v3) void CC_DLL ccDrawLine( const Vec2& origin, const Vec2& destination );
CC_DEPRECATED(v3) void CC_DLL ccDrawRect( Vec2 origin, Vec2 destination );
CC_DEPRECATED(v3) void CC_DLL ccDrawSolidRect( Vec2 origin, Vec2 destination, Color4F color );
CC_DEPRECATED(v3) void CC_DLL ccDrawPoly( const Vec2 *vertices, unsigned int numOfVertices, bool closePolygon );
CC_DEPRECATED(v3) void CC_DLL ccDrawSolidPoly( const Vec2 *poli, unsigned int numberOfPoints, Color4F color );
CC_DEPRECATED(v3) void CC_DLL ccDrawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
CC_DEPRECATED(v3) void CC_DLL ccDrawCircle( const Vec2& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);
CC_DEPRECATED(v3) void CC_DLL ccDrawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY);
CC_DEPRECATED(v3) void CC_DLL ccDrawSolidCircle( const Vec2& center, float radius, float angle, unsigned int segments);
CC_DEPRECATED(v3) void CC_DLL ccDrawQuadBezier(const Vec2& origin, const Vec2& control, const Vec2& destination, unsigned int segments);
CC_DEPRECATED(v3) void CC_DLL ccDrawCubicBezier(const Vec2& origin, const Vec2& control1, const Vec2& control2, const Vec2& destination, unsigned int segments);
CC_DEPRECATED(v3) void CC_DLL ccDrawCatmullRom( PointArray *arrayOfControlPoints, unsigned int segments );
CC_DEPRECATED(v3) void CC_DLL ccDrawCardinalSpline( PointArray *config, float tension,  unsigned int segments );
CC_DEPRECATED(v3) void CC_DLL ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a );
CC_DEPRECATED(v3) void CC_DLL ccDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a );
CC_DEPRECATED(v3) void CC_DLL ccPointSize( GLfloat pointSize );


CC_DEPRECATED(v3) inline void CC_DLL ccGLInvalidateStateCache() { GL::invalidateStateCache(); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLUseProgram(GLuint program) { GL::useProgram(program); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLDeleteProgram(GLuint program){ GL::deleteProgram(program); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLBlendFunc(GLenum sfactor, GLenum dfactor) { GL::blendFunc(sfactor, dfactor); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLBlendResetToCache() { GL::blendResetToCache(); }
CC_DEPRECATED(v3) inline void CC_DLL ccSetProjectionMatrixDirty() { GL::setProjectionMatrixDirty(); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLEnableVertexAttribs(unsigned int flags) { GL::enableVertexAttribs(flags); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLBindTexture2D(GLuint textureId) { GL::bindTexture2D(textureId); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLBindTexture2DN(GLuint textureUnit, GLuint textureId) { GL::bindTexture2DN(textureUnit, textureId); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLDeleteTexture(GLuint textureId) { GL::deleteTexture(textureId); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLDeleteTextureN(GLuint textureUnit, GLuint textureId) { GL::deleteTexture(textureId); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLBindVAO(GLuint vaoId) { GL::bindVAO(vaoId); }
CC_DEPRECATED(v3) inline void CC_DLL ccGLEnable( int flags ) { /* ignore */ };
CC_DEPRECATED(v3) typedef int ccGLServerState;

CC_DEPRECATED(v3) typedef Data CCData;
CC_DEPRECATED(v3) typedef __Set CCSet;
CC_DEPRECATED(v3) typedef __SetIterator CCSetIterator;
CC_DEPRECATED(v3) typedef __Set Set;
CC_DEPRECATED(v3) typedef __SetIterator SetIterator;

CC_DEPRECATED(v3) typedef __Array CCArray;
CC_DEPRECATED(v3) typedef __Array Array;

CC_DEPRECATED(v3) typedef __Dictionary Dictionary;
CC_DEPRECATED(v3) typedef __Dictionary CCDictionary;

CC_DEPRECATED(v3) typedef __Double Double;
CC_DEPRECATED(v3) typedef __Double CCDouble;
CC_DEPRECATED(v3) typedef __Float Float;
CC_DEPRECATED(v3) typedef __Float CCFloat;
CC_DEPRECATED(v3) typedef __Integer Integer;
CC_DEPRECATED(v3) typedef __Integer CCInteger;
CC_DEPRECATED(v3) typedef __Bool Bool;
CC_DEPRECATED(v3) typedef __Bool CCBool;
CC_DEPRECATED(v3) typedef __String CCString;
CC_DEPRECATED(v3) typedef __String String;

CC_DEPRECATED(v3) typedef __RGBAProtocol RGBAProtocol;
CC_DEPRECATED(v3) typedef __NodeRGBA NodeRGBA;
CC_DEPRECATED(v3) typedef __LayerRGBA LayerRGBA;

CC_DEPRECATED(v3) typedef __LabelBMFont LabelBMFont;
CC_DEPRECATED(v3) typedef __LabelTTF LabelTTF;

//deprecated attributes and methods for kazMath
CC_DEPRECATED(v3) typedef float kmScalar;

//kmMat4 and kmMat4 stack
CC_DEPRECATED(v3) typedef Mat4 kmMat4;
CC_DEPRECATED(v3) const unsigned int KM_GL_MODELVIEW = 0x1700;
CC_DEPRECATED(v3) const unsigned int KM_GL_PROJECTION = 0x1701;
CC_DEPRECATED(v3) const unsigned int KM_GL_TEXTURE = 0x1702;

CC_DEPRECATED(v3) void CC_DLL kmGLFreeAll(void);
CC_DEPRECATED(v3) void CC_DLL kmGLPushMatrix(void);
CC_DEPRECATED(v3) void CC_DLL kmGLPopMatrix(void);
CC_DEPRECATED(v3) void CC_DLL kmGLMatrixMode(unsigned int mode);
CC_DEPRECATED(v3) void CC_DLL kmGLLoadIdentity(void);
CC_DEPRECATED(v3) void CC_DLL kmGLLoadMatrix(const Mat4* pIn);
CC_DEPRECATED(v3) void CC_DLL kmGLMultMatrix(const Mat4* pIn);
CC_DEPRECATED(v3) void CC_DLL kmGLTranslatef(float x, float y, float z);
CC_DEPRECATED(v3) void CC_DLL kmGLRotatef(float angle, float x, float y, float z);
CC_DEPRECATED(v3) void CC_DLL kmGLScalef(float x, float y, float z);
CC_DEPRECATED(v3) void CC_DLL kmGLGetMatrix(unsigned int mode, Mat4* pOut);

CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Fill(Mat4* pOut, const float* pMat);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Assign(Mat4* pOut, const Mat4* pIn);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Identity(Mat4* pOut);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Inverse(Mat4* pOut, const Mat4* pM);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Transpose(Mat4* pOut, const Mat4* pIn);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Multiply(Mat4* pOut, const Mat4* pM1, const Mat4* pM2);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Translation(Mat4* pOut, const float x, const float y, const float z);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4RotationX(Mat4* pOut, const float radians);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4RotationY(Mat4* pOut, const float radians);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4RotationZ(Mat4* pOut, const float radians);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4RotationAxisAngle(Mat4* pOut, const Vec3* axis, float radians);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4Scaling(Mat4* pOut, const float x, const float y, const float z);

CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4PerspectiveProjection(Mat4* pOut, float fovY, float aspect, float zNear, float zFar);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4OrthographicProjection(Mat4* pOut, float left, float right, float bottom, float top, float nearVal, float farVal);
CC_DEPRECATED(v3) CC_DLL Mat4* kmMat4LookAt(Mat4* pOut, const Vec3* pEye, const Vec3* pCenter, const Vec3* pUp);

//kmVec3
CC_DEPRECATED(v3) typedef Vec3 kmVec3;
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Fill(Vec3* pOut, float x, float y, float z);
CC_DEPRECATED(v3) CC_DLL float kmVec3Length(const Vec3* pIn);
CC_DEPRECATED(v3) CC_DLL float kmVec3LengthSq(const Vec3* pIn);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Lerp(Vec3* pOut, const Vec3* pV1, const Vec3* pV2, float t);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Normalize(Vec3* pOut, const Vec3* pIn);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Cross(Vec3* pOut, const Vec3* pV1, const Vec3* pV2);
CC_DEPRECATED(v3) CC_DLL float kmVec3Dot(const Vec3* pV1, const Vec3* pV2);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Add(Vec3* pOut, const Vec3* pV1, const Vec3* pV2);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Subtract(Vec3* pOut, const Vec3* pV1, const Vec3* pV2);

CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Transform(Vec3* pOut, const Vec3* pV1, const Mat4* pM);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3TransformNormal(Vec3* pOut, const Vec3* pV, const Mat4* pM);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3TransformCoord(Vec3* pOut, const Vec3* pV, const Mat4* pM);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Scale(Vec3* pOut, const Vec3* pIn, const float s);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Assign(Vec3* pOut, const Vec3* pIn);
CC_DEPRECATED(v3) CC_DLL Vec3* kmVec3Zero(Vec3* pOut);

CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_NEG_Z;
CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_POS_Z;
CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_POS_Y;
CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_NEG_Y;
CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_NEG_X;
CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_POS_X;
CC_DEPRECATED(v3) extern const Vec3 KM_VEC3_ZERO;

//kmVec2
CC_DEPRECATED(v3) typedef Vec2 kmVec2;
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Fill(Vec2* pOut, float x, float y);
CC_DEPRECATED(v3) CC_DLL float kmVec2Length(const Vec2* pIn);
CC_DEPRECATED(v3) CC_DLL float kmVec2LengthSq(const Vec2* pIn);
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Normalize(Vec2* pOut, const Vec2* pIn);
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Lerp(Vec2* pOut, const Vec2* pV1, const Vec2* pV2, float t);
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Add(Vec2* pOut, const Vec2* pV1, const Vec2* pV2);
CC_DEPRECATED(v3) CC_DLL float kmVec2Dot(const Vec2* pV1, const Vec2* pV2);
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Subtract(Vec2* pOut, const Vec2* pV1, const Vec2* pV2);
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Scale(Vec2* pOut, const Vec2* pIn, const float s);
CC_DEPRECATED(v3) CC_DLL Vec2* kmVec2Assign(Vec2* pOut, const Vec2* pIn);

CC_DEPRECATED(v3) extern const Vec2 KM_VEC2_POS_Y;
CC_DEPRECATED(v3) extern const Vec2 KM_VEC2_NEG_Y;
CC_DEPRECATED(v3) extern const Vec2 KM_VEC2_NEG_X;
CC_DEPRECATED(v3) extern const Vec2 KM_VEC2_POS_X;
CC_DEPRECATED(v3) extern const Vec2 KM_VEC2_ZERO;

//kmVec4
CC_DEPRECATED(v3) typedef Vec4 kmVec4;
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Fill(Vec4* pOut, float x, float y, float z, float w);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Add(Vec4* pOut, const Vec4* pV1, const Vec4* pV2);
CC_DEPRECATED(v3) CC_DLL float kmVec4Dot(const Vec4* pV1, const Vec4* pV2);
CC_DEPRECATED(v3) CC_DLL float kmVec4Length(const Vec4* pIn);
CC_DEPRECATED(v3) CC_DLL float kmVec4LengthSq(const Vec4* pIn);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Lerp(Vec4* pOut, const Vec4* pV1, const Vec4* pV2, float t);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Normalize(Vec4* pOut, const Vec4* pIn);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Scale(Vec4* pOut, const Vec4* pIn, const float s);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Subtract(Vec4* pOut, const Vec4* pV1, const Vec4* pV2);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Assign(Vec4* pOut, const Vec4* pIn);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4MultiplyMat4(Vec4* pOut, const Vec4* pV, const Mat4* pM);
CC_DEPRECATED(v3) CC_DLL Vec4* kmVec4Transform(Vec4* pOut, const Vec4* pV, const Mat4* pM);

//end of deprecated attributes and methods for kazMath

NS_CC_END


#endif // __COCOS2D_CCDEPRECATED_H__
