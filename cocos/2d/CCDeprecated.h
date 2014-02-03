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
#include "CCGeometry.h"
#include "ccTypes.h"

NS_CC_BEGIN

/**
 * @addtogroup data_structures
 * @{
 */

/** Helper macro that creates a Point
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE inline Point ccp(float x, float y)
{
    return Point(x, y);
}

/** Returns opposite of point.
 @return Point
 @since v0.7.2
 @deprecated please use Point::-, for example: -v1
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpNeg(const Point& v)
{
    return -v;
}

/** Calculates sum of two points.
 @return Point
 @since v0.7.2
 @deprecated please use Point::+, for example: v1 + v2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpAdd(const Point& v1, const Point& v2)
{
    return v1 + v2;
}

/** Calculates difference of two points.
 @return Point
 @since v0.7.2
 @deprecated please use Point::-, for example: v1 - v2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpSub(const Point& v1, const Point& v2)
{
    return v1 - v2;
}

/** Returns point multiplied by given factor.
 @return Point
 @since v0.7.2
 @deprecated please use Point::*, for example: v1 * v2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpMult(const Point& v, const float s)
{
    return v * s;
}

/** Calculates midpoint between two points.
 @return Point
 @since v0.7.2
 @deprecated please use it like (v1 + v2) / 2.0f
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpMidpoint(const Point& v1, const Point& v2)
{
    return v1.getMidpoint(v2);
}

/** Calculates dot product of two points.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline float
ccpDot(const Point& v1, const Point& v2)
{
    return v1.dot(v2);
}

/** Calculates cross product of two points.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline float
ccpCross(const Point& v1, const Point& v2)
{
    return v1.cross(v2);
}

/** Calculates perpendicular of v, rotated 90 degrees counter-clockwise -- cross(v, perp(v)) >= 0
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpPerp(const Point& v)
{
    return v.getPerp();
}

/** Calculates perpendicular of v, rotated 90 degrees clockwise -- cross(v, rperp(v)) <= 0
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpRPerp(const Point& v)
{
    return v.getRPerp();
}

/** Calculates the projection of v1 over v2.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpProject(const Point& v1, const Point& v2)
{
    return v1.project(v2);
}

/** Rotates two points.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpRotate(const Point& v1, const Point& v2)
{
    return v1.rotate(v2);
}

/** Unrotates two points.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point
ccpUnrotate(const Point& v1, const Point& v2)
{
    return v1.unrotate(v2);
}

/** Calculates the square length of a Point (not calling sqrt() )
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline float
ccpLengthSQ(const Point& v)
{
    return v.getLengthSq();
}


/** Calculates the square distance between two points (not calling sqrt() )
 @return float
 @since v1.1
 */
CC_DEPRECATED_ATTRIBUTE static inline float
ccpDistanceSQ(const Point p1, const Point p2)
{
    return (p1 - p2).getLengthSq();
}


/** Calculates distance between point an origin
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline float ccpLength(const Point& v)
{
    return v.getLength();
}

/** Calculates the distance between two points
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline float ccpDistance(const Point& v1, const Point& v2)
{
    return v1.getDistance(v2);
}

/** Returns point multiplied to a length of 1.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpNormalize(const Point& v)
{
    return v.normalize();
}

/** Converts radians to a normalized vector.
 @return Point
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpForAngle(const float a)
{
    return Point::forAngle(a);
}

/** Converts a vector to radians.
 @return float
 @since v0.7.2
 */
CC_DEPRECATED_ATTRIBUTE static inline float ccpToAngle(const Point& v)
{
    return v.getAngle();
}


/** Clamp a point between from and to.
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpClamp(const Point& p, const Point& from, const Point& to)
{
    return p.getClampPoint(from, to);
}

/** Quickly convert Size to a Point
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpFromSize(const Size& s)
{
    return Point(s);
}

/** Run a math operation function on each point component
 * absf, fllorf, ceilf, roundf
 * any function that has the signature: float func(float);
 * For example: let's try to take the floor of x,y
 * ccpCompOp(p,floorf);
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpCompOp(const Point& p, float (*opFunc)(float))
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
CC_DEPRECATED_ATTRIBUTE static inline Point ccpLerp(const Point& a, const Point& b, float alpha)
{
    return a.lerp(b, alpha);
}


/** @returns if points have fuzzy equality which means equal with some degree of variance.
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline bool ccpFuzzyEqual(const Point& a, const Point& b, float variance)
{
    return a.fuzzyEquals(b, variance);
}


/** Multiplies a and b components, a.x*b.x, a.y*b.y
 @returns a component-wise multiplication
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpCompMult(const Point& a, const Point& b)
{
    return Point(a.x * b.x, a.y * b.y);
}

/** @returns the signed angle in radians between two vector directions
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline float ccpAngleSigned(const Point& a, const Point& b)
{
    return a.getAngle(b);
}

/** @returns the angle in radians between two vector directions
 @since v0.99.1
 */
CC_DEPRECATED_ATTRIBUTE static inline float ccpAngle(const Point& a, const Point& b)
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
CC_DEPRECATED_ATTRIBUTE static inline Point ccpRotateByAngle(const Point& v, const Point& pivot, float angle)
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
CC_DEPRECATED_ATTRIBUTE static inline bool ccpLineIntersect(const Point& p1, const Point& p2,
                                                     const Point& p3, const Point& p4,
                                                     float *s, float *t)
{
    return Point::isLineIntersect(p1, p2, p3, p4, s, t);
}

/*
 ccpSegmentIntersect returns true if Segment A-B intersects with segment C-D
 @since v1.0.0
 */
CC_DEPRECATED_ATTRIBUTE static inline bool ccpSegmentIntersect(const Point& A, const Point& B, const Point& C, const Point& D)
{
    return Point::isSegmentIntersect(A, B, C, D);
}

/*
 ccpIntersectPoint returns the intersection point of line A-B, C-D
 @since v1.0.0
 */
CC_DEPRECATED_ATTRIBUTE static inline Point ccpIntersectPoint(const Point& A, const Point& B, const Point& C, const Point& D)
{
    return Point::getIntersectPoint(A, B, C, D);
}

CC_DEPRECATED_ATTRIBUTE inline Point CCPointMake(float x, float y)
{
    return Point(x, y);
}

CC_DEPRECATED_ATTRIBUTE inline Size CCSizeMake(float width, float height)
{
    return Size(width, height);
}

CC_DEPRECATED_ATTRIBUTE inline Rect CCRectMake(float x, float y, float width, float height)
{
    return Rect(x, y, width, height);
}


CC_DEPRECATED_ATTRIBUTE extern const Point CCPointZero;

/* The "zero" size -- equivalent to Size(0, 0). */
CC_DEPRECATED_ATTRIBUTE extern const Size CCSizeZero;

/* The "zero" rectangle -- equivalent to Rect(0, 0, 0, 0). */
CC_DEPRECATED_ATTRIBUTE extern const Rect CCRectZero;


CC_DEPRECATED_ATTRIBUTE extern const Color3B ccWHITE;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccYELLOW;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccGREEN;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccBLUE;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccRED;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccMAGENTA;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccBLACK;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccORANGE;
CC_DEPRECATED_ATTRIBUTE extern const Color3B ccGRAY;

CC_DEPRECATED_ATTRIBUTE extern const BlendFunc kCCBlendFuncDisable;

CC_DEPRECATED_ATTRIBUTE static inline Color3B ccc3(GLubyte r, GLubyte g, GLubyte b)
{
    return Color3B(r, g, b);
}

CC_DEPRECATED_ATTRIBUTE static inline bool ccc3BEqual(const Color3B &col1, const Color3B &col2)
{
    return col1.r == col2.r && col1.g == col2.g && col1.b == col2.b;
}

CC_DEPRECATED_ATTRIBUTE static inline Color4B
ccc4(const GLubyte r, const GLubyte g, const GLubyte b, const GLubyte o)
{
    return Color4B(r, g, b, o);
}

CC_DEPRECATED_ATTRIBUTE static inline Color4F ccc4FFromccc3B(Color3B c)
{
    return Color4F(c.r/255.f, c.g/255.f, c.b/255.f, 1.f);
}

CC_DEPRECATED_ATTRIBUTE static inline Color4F
ccc4f(const GLfloat r, const GLfloat g, const GLfloat b, const GLfloat a)
{
    return Color4F(r, g, b, a);
}

CC_DEPRECATED_ATTRIBUTE static inline Color4F ccc4FFromccc4B(Color4B c)
{
    return Color4F(c.r/255.f, c.g/255.f, c.b/255.f, c.a/255.f);
}

CC_DEPRECATED_ATTRIBUTE static inline Color4B ccc4BFromccc4F(Color4F c)
{
	return Color4B((GLubyte)(c.r*255), (GLubyte)(c.g*255), (GLubyte)(c.b*255), (GLubyte)(c.a*255));
}

CC_DEPRECATED_ATTRIBUTE static inline bool ccc4FEqual(Color4F a, Color4F b)
{
    return a.r == b.r && a.g == b.g && a.b == b.b && a.a == b.a;
}

CC_DEPRECATED_ATTRIBUTE static inline Vertex2F vertex2(const float x, const float y)
{
    Vertex2F c(x, y);
    return c;
}

CC_DEPRECATED_ATTRIBUTE static inline Vertex3F vertex3(const float x, const float y, const float z)
{
    Vertex3F c(x, y, z);
    return c;
}

CC_DEPRECATED_ATTRIBUTE static inline Tex2F tex2(const float u, const float v)
{
    Tex2F t(u , v);
    return t;
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformMake(float a, float b, float c, float d, float tx, float ty)
{
    return AffineTransformMake(a, b, c, d, tx, ty);
}

CC_DEPRECATED_ATTRIBUTE static inline Point CCPointApplyAffineTransform(const Point& point, const AffineTransform& t)
{
    return PointApplyAffineTransform(point, t);
}

CC_DEPRECATED_ATTRIBUTE static inline Size CCSizeApplyAffineTransform(const Size& size, const AffineTransform& t)
{
    return SizeApplyAffineTransform(size, t);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformMakeIdentity()
{
    return AffineTransformMakeIdentity();
}

CC_DEPRECATED_ATTRIBUTE static inline Rect CCRectApplyAffineTransform(const Rect& rect, const AffineTransform& anAffineTransform)
{
    return RectApplyAffineTransform(rect, anAffineTransform);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformTranslate(const AffineTransform& t, float tx, float ty)
{
    return AffineTransformTranslate(t, tx, ty);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformRotate(const AffineTransform& aTransform, float anAngle)
{
    return AffineTransformRotate(aTransform, anAngle);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformScale(const AffineTransform& t, float sx, float sy)
{
    return AffineTransformScale(t, sx, sy);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformConcat(const AffineTransform& t1, const AffineTransform& t2)
{
    return AffineTransformConcat(t1, t2);
}

CC_DEPRECATED_ATTRIBUTE static inline bool CCAffineTransformEqualToTransform(const AffineTransform& t1, const AffineTransform& t2)
{
    return AffineTransformEqualToTransform(t1, t2);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformInvert(const AffineTransform& t)
{
    return AffineTransformInvert(t);
}

CC_DEPRECATED_ATTRIBUTE static inline AffineTransform CCAffineTransformIdentity()
{
    return AffineTransformMakeIdentity();
}

// CC prefix compatibility
CC_DEPRECATED_ATTRIBUTE typedef Object CCObject;
CC_DEPRECATED_ATTRIBUTE typedef Event CCEvent;
CC_DEPRECATED_ATTRIBUTE typedef DataVisitor CCDataVisitor;
CC_DEPRECATED_ATTRIBUTE typedef PrettyPrinter CCPrettyPrinter;
CC_DEPRECATED_ATTRIBUTE typedef Acceleration CCAcceleration;
CC_DEPRECATED_ATTRIBUTE typedef TextureAtlas CCTextureAtlas;
CC_DEPRECATED_ATTRIBUTE typedef Configuration CCConfiguration;
CC_DEPRECATED_ATTRIBUTE typedef PointArray CCPointArray;
CC_DEPRECATED_ATTRIBUTE typedef RemoveSelf CCRemoveSelf;
CC_DEPRECATED_ATTRIBUTE typedef IMEDelegate CCIMEDelegate;
CC_DEPRECATED_ATTRIBUTE typedef IMEKeyboardNotificationInfo CCIMEKeyboardNotificationInfo;
CC_DEPRECATED_ATTRIBUTE typedef TextFieldDelegate CCTextFieldDelegate;
CC_DEPRECATED_ATTRIBUTE typedef TextFieldTTF CCTextFieldTTF;
CC_DEPRECATED_ATTRIBUTE typedef __NotificationCenter CCNotificationCenter;
CC_DEPRECATED_ATTRIBUTE typedef __NotificationCenter NotificationCenter;
//CC_DEPRECATED_ATTRIBUTE typedef TargetedTouchDelegate CCTargetedTouchDelegate;
//CC_DEPRECATED_ATTRIBUTE typedef StandardTouchDelegate CCStandardTouchDelegate;
//CC_DEPRECATED_ATTRIBUTE typedef TouchDelegate CCTouchDelegate;
CC_DEPRECATED_ATTRIBUTE typedef Image CCImage;
CC_DEPRECATED_ATTRIBUTE typedef UserDefault CCUserDefault;

CC_DEPRECATED_ATTRIBUTE typedef Action CCAction;
CC_DEPRECATED_ATTRIBUTE typedef FiniteTimeAction CCFiniteTimeAction;
CC_DEPRECATED_ATTRIBUTE typedef Speed CCSpeed;
CC_DEPRECATED_ATTRIBUTE typedef Follow CCFollow;
CC_DEPRECATED_ATTRIBUTE typedef GLProgram CCGLProgram;
CC_DEPRECATED_ATTRIBUTE typedef Touch CCTouch;
CC_DEPRECATED_ATTRIBUTE typedef Texture2D CCTexture2D;
CC_DEPRECATED_ATTRIBUTE typedef Node CCNode;
CC_DEPRECATED_ATTRIBUTE typedef Node CCNodeRGBA;
CC_DEPRECATED_ATTRIBUTE typedef Node CCRGBAProtocol;
CC_DEPRECATED_ATTRIBUTE typedef SpriteFrame CCSpriteFrame;
CC_DEPRECATED_ATTRIBUTE typedef AnimationFrame CCAnimationFrame;
CC_DEPRECATED_ATTRIBUTE typedef Animation CCAnimation;
CC_DEPRECATED_ATTRIBUTE typedef ActionInterval CCActionInterval;
CC_DEPRECATED_ATTRIBUTE typedef Sequence CCSequence;
CC_DEPRECATED_ATTRIBUTE typedef Repeat CCRepeat;
CC_DEPRECATED_ATTRIBUTE typedef RepeatForever CCRepeatForever;
CC_DEPRECATED_ATTRIBUTE typedef Spawn CCSpawn;
CC_DEPRECATED_ATTRIBUTE typedef RotateTo CCRotateTo;
CC_DEPRECATED_ATTRIBUTE typedef RotateBy CCRotateBy;
CC_DEPRECATED_ATTRIBUTE typedef MoveBy CCMoveBy;
CC_DEPRECATED_ATTRIBUTE typedef MoveTo CCMoveTo;
CC_DEPRECATED_ATTRIBUTE typedef SkewTo CCSkewTo;
CC_DEPRECATED_ATTRIBUTE typedef SkewBy CCSkewBy;
CC_DEPRECATED_ATTRIBUTE typedef JumpBy CCJumpBy;
CC_DEPRECATED_ATTRIBUTE typedef JumpTo CCJumpTo;
CC_DEPRECATED_ATTRIBUTE typedef BezierBy CCBezierBy;
CC_DEPRECATED_ATTRIBUTE typedef BezierTo CCBezierTo;
CC_DEPRECATED_ATTRIBUTE typedef ScaleTo CCScaleTo;
CC_DEPRECATED_ATTRIBUTE typedef ScaleBy CCScaleBy;
CC_DEPRECATED_ATTRIBUTE typedef Blink CCBlink;
CC_DEPRECATED_ATTRIBUTE typedef FadeIn CCFadeIn;
CC_DEPRECATED_ATTRIBUTE typedef FadeOut CCFadeOut;
CC_DEPRECATED_ATTRIBUTE typedef FadeTo CCFadeTo;
CC_DEPRECATED_ATTRIBUTE typedef TintTo CCTintTo;
CC_DEPRECATED_ATTRIBUTE typedef TintBy CCTintBy;
CC_DEPRECATED_ATTRIBUTE typedef DelayTime CCDelayTime;
CC_DEPRECATED_ATTRIBUTE typedef Animate CCAnimate;
CC_DEPRECATED_ATTRIBUTE typedef TargetedAction CCTargetedAction;
CC_DEPRECATED_ATTRIBUTE typedef ActionCamera CCActionCamera;
CC_DEPRECATED_ATTRIBUTE typedef OrbitCamera CCOrbitCamera;
CC_DEPRECATED_ATTRIBUTE typedef ActionManager CCActionManager;
CC_DEPRECATED_ATTRIBUTE typedef ActionEase CCActionEase;
CC_DEPRECATED_ATTRIBUTE typedef EaseRateAction CCEaseRateAction;
CC_DEPRECATED_ATTRIBUTE typedef EaseIn CCEaseIn;
CC_DEPRECATED_ATTRIBUTE typedef EaseOut CCEaseOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseInOut CCEaseInOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseExponentialIn CCEaseExponentialIn;
CC_DEPRECATED_ATTRIBUTE typedef EaseExponentialOut CCEaseExponentialOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseExponentialInOut CCEaseExponentialInOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseSineIn CCEaseSineIn;
CC_DEPRECATED_ATTRIBUTE typedef EaseSineOut CCEaseSineOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseSineInOut CCEaseSineInOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseElastic CCEaseElastic;
CC_DEPRECATED_ATTRIBUTE typedef EaseElasticIn CCEaseElasticIn;
CC_DEPRECATED_ATTRIBUTE typedef EaseElasticOut CCEaseElasticOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseElasticInOut CCEaseElasticInOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseBounce CCEaseBounce;
CC_DEPRECATED_ATTRIBUTE typedef EaseBounceIn CCEaseBounceIn;
CC_DEPRECATED_ATTRIBUTE typedef EaseBounceOut CCEaseBounceOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseBounceInOut CCEaseBounceInOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseBackIn CCEaseBackIn;
CC_DEPRECATED_ATTRIBUTE typedef EaseBackOut CCEaseBackOut;
CC_DEPRECATED_ATTRIBUTE typedef EaseBackInOut CCEaseBackInOut;
CC_DEPRECATED_ATTRIBUTE typedef ActionInstant CCActionInstant;
CC_DEPRECATED_ATTRIBUTE typedef Show CCShow;
CC_DEPRECATED_ATTRIBUTE typedef Hide CCHide;
CC_DEPRECATED_ATTRIBUTE typedef ToggleVisibility CCToggleVisibility;
CC_DEPRECATED_ATTRIBUTE typedef FlipX CCFlipX;
CC_DEPRECATED_ATTRIBUTE typedef FlipY CCFlipY;
CC_DEPRECATED_ATTRIBUTE typedef Place CCPlace;
CC_DEPRECATED_ATTRIBUTE typedef CallFunc CCCallFunc;
CC_DEPRECATED_ATTRIBUTE typedef CallFuncN CCCallFuncN;
CC_DEPRECATED_ATTRIBUTE typedef __CCCallFuncND CCCallFuncND;
CC_DEPRECATED_ATTRIBUTE typedef __CCCallFuncO CCCallFuncO;
CC_DEPRECATED_ATTRIBUTE typedef GridAction CCGridAction;
CC_DEPRECATED_ATTRIBUTE typedef Grid3DAction CCGrid3DAction;
CC_DEPRECATED_ATTRIBUTE typedef TiledGrid3DAction CCTiledGrid3DAction;
CC_DEPRECATED_ATTRIBUTE typedef StopGrid CCStopGrid;
CC_DEPRECATED_ATTRIBUTE typedef ReuseGrid CCReuseGrid;
CC_DEPRECATED_ATTRIBUTE typedef Waves3D CCWaves3D;
CC_DEPRECATED_ATTRIBUTE typedef FlipX3D CCFlipX3D;
CC_DEPRECATED_ATTRIBUTE typedef FlipY3D CCFlipY3D;
CC_DEPRECATED_ATTRIBUTE typedef Lens3D CCLens3D;
CC_DEPRECATED_ATTRIBUTE typedef Ripple3D CCRipple3D;
CC_DEPRECATED_ATTRIBUTE typedef Shaky3D CCShaky3D;
CC_DEPRECATED_ATTRIBUTE typedef Liquid CCLiquid;
CC_DEPRECATED_ATTRIBUTE typedef Waves CCWaves;
CC_DEPRECATED_ATTRIBUTE typedef Twirl CCTwirl;
CC_DEPRECATED_ATTRIBUTE typedef PageTurn3D CCPageTurn3D;
CC_DEPRECATED_ATTRIBUTE typedef ProgressTo CCProgressTo;
CC_DEPRECATED_ATTRIBUTE typedef ProgressFromTo CCProgressFromTo;
CC_DEPRECATED_ATTRIBUTE typedef ShakyTiles3D CCShakyTiles3D;
CC_DEPRECATED_ATTRIBUTE typedef ShatteredTiles3D CCShatteredTiles3D;
CC_DEPRECATED_ATTRIBUTE typedef ShuffleTiles CCShuffleTiles;
CC_DEPRECATED_ATTRIBUTE typedef FadeOutTRTiles CCFadeOutTRTiles;
CC_DEPRECATED_ATTRIBUTE typedef FadeOutBLTiles CCFadeOutBLTiles;
CC_DEPRECATED_ATTRIBUTE typedef FadeOutUpTiles CCFadeOutUpTiles;
CC_DEPRECATED_ATTRIBUTE typedef FadeOutDownTiles CCFadeOutDownTiles;
CC_DEPRECATED_ATTRIBUTE typedef TurnOffTiles CCTurnOffTiles;
CC_DEPRECATED_ATTRIBUTE typedef WavesTiles3D CCWavesTiles3D;
CC_DEPRECATED_ATTRIBUTE typedef JumpTiles3D CCJumpTiles3D;
CC_DEPRECATED_ATTRIBUTE typedef SplitRows CCSplitRows;
CC_DEPRECATED_ATTRIBUTE typedef SplitCols CCSplitCols;
CC_DEPRECATED_ATTRIBUTE typedef ActionTween CCActionTween;
CC_DEPRECATED_ATTRIBUTE typedef CardinalSplineTo CCCardinalSplineTo;
CC_DEPRECATED_ATTRIBUTE typedef CardinalSplineBy CCCardinalSplineBy;
CC_DEPRECATED_ATTRIBUTE typedef CatmullRomTo CCCatmullRomTo;
CC_DEPRECATED_ATTRIBUTE typedef CatmullRomBy CCCatmullRomBy;
CC_DEPRECATED_ATTRIBUTE typedef AtlasNode CCAtlasNode;
CC_DEPRECATED_ATTRIBUTE typedef TextureProtocol CCTextureProtocol;
CC_DEPRECATED_ATTRIBUTE typedef BlendProtocol CCBlendProtocol;
CC_DEPRECATED_ATTRIBUTE typedef DrawNode CCDrawNode;
CC_DEPRECATED_ATTRIBUTE typedef Camera CCCamera;
CC_DEPRECATED_ATTRIBUTE typedef LabelAtlas CCLabelAtlas;
CC_DEPRECATED_ATTRIBUTE typedef LabelProtocol CCLabelProtocol;
CC_DEPRECATED_ATTRIBUTE typedef Director CCDirector;
CC_DEPRECATED_ATTRIBUTE typedef GridBase CCGridBase;
CC_DEPRECATED_ATTRIBUTE typedef Grid3D CCGrid3D;
CC_DEPRECATED_ATTRIBUTE typedef TiledGrid3D CCTiledGrid3D;
CC_DEPRECATED_ATTRIBUTE typedef Sprite CCSprite;
CC_DEPRECATED_ATTRIBUTE typedef LabelTTF CCLabelTTF;
CC_DEPRECATED_ATTRIBUTE typedef SpriteBatchNode CCSpriteBatchNode;
CC_DEPRECATED_ATTRIBUTE typedef LabelBMFont CCLabelBMFont;
CC_DEPRECATED_ATTRIBUTE typedef Layer CCLayer;
//CC_DEPRECATED_ATTRIBUTE typedef KeypadDelegate CCKeypadDelegate;
CC_DEPRECATED_ATTRIBUTE typedef Layer CCLayerRGBA;
CC_DEPRECATED_ATTRIBUTE typedef LayerColor CCLayerColor;
CC_DEPRECATED_ATTRIBUTE typedef LayerGradient CCLayerGradient;
CC_DEPRECATED_ATTRIBUTE typedef LayerMultiplex CCLayerMultiplex;
CC_DEPRECATED_ATTRIBUTE typedef Scene CCScene;
CC_DEPRECATED_ATTRIBUTE typedef TransitionEaseScene CCTransitionEaseScene;
CC_DEPRECATED_ATTRIBUTE typedef TransitionScene CCTransitionScene;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSceneOriented CCTransitionSceneOriented;
CC_DEPRECATED_ATTRIBUTE typedef TransitionRotoZoom CCTransitionRotoZoom;
CC_DEPRECATED_ATTRIBUTE typedef TransitionJumpZoom CCTransitionJumpZoom;
CC_DEPRECATED_ATTRIBUTE typedef TransitionMoveInL CCTransitionMoveInL;
CC_DEPRECATED_ATTRIBUTE typedef TransitionMoveInR CCTransitionMoveInR;
CC_DEPRECATED_ATTRIBUTE typedef TransitionMoveInT CCTransitionMoveInT;
CC_DEPRECATED_ATTRIBUTE typedef TransitionMoveInB CCTransitionMoveInB;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSlideInL CCTransitionSlideInL;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSlideInR CCTransitionSlideInR;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSlideInB CCTransitionSlideInB;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSlideInT CCTransitionSlideInT;
CC_DEPRECATED_ATTRIBUTE typedef TransitionShrinkGrow CCTransitionShrinkGrow;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFlipX CCTransitionFlipX;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFlipY CCTransitionFlipY;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFlipAngular CCTransitionFlipAngular;
CC_DEPRECATED_ATTRIBUTE typedef TransitionZoomFlipX CCTransitionZoomFlipX;
CC_DEPRECATED_ATTRIBUTE typedef TransitionZoomFlipY CCTransitionZoomFlipY;
CC_DEPRECATED_ATTRIBUTE typedef TransitionZoomFlipAngular CCTransitionZoomFlipAngular;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFade CCTransitionFade;
CC_DEPRECATED_ATTRIBUTE typedef TransitionCrossFade CCTransitionCrossFade;
CC_DEPRECATED_ATTRIBUTE typedef TransitionTurnOffTiles CCTransitionTurnOffTiles;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSplitCols CCTransitionSplitCols;
CC_DEPRECATED_ATTRIBUTE typedef TransitionSplitRows CCTransitionSplitRows;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFadeTR CCTransitionFadeTR;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFadeBL CCTransitionFadeBL;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFadeUp CCTransitionFadeUp;
CC_DEPRECATED_ATTRIBUTE typedef TransitionFadeDown CCTransitionFadeDown;
CC_DEPRECATED_ATTRIBUTE typedef TransitionPageTurn CCTransitionPageTurn;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgress CCTransitionProgress;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgressRadialCCW CCTransitionProgressRadialCCW;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgressRadialCW CCTransitionProgressRadialCW;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgressHorizontal CCTransitionProgressHorizontal;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgressVertical CCTransitionProgressVertical;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgressInOut CCTransitionProgressInOut;
CC_DEPRECATED_ATTRIBUTE typedef TransitionProgressOutIn CCTransitionProgressOutIn;
CC_DEPRECATED_ATTRIBUTE typedef MenuItem CCMenuItem;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemLabel CCMenuItemLabel;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemAtlasFont CCMenuItemAtlasFont;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemFont CCMenuItemFont;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemSprite CCMenuItemSprite;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemImage CCMenuItemImage;
CC_DEPRECATED_ATTRIBUTE typedef MenuItemToggle CCMenuItemToggle;
CC_DEPRECATED_ATTRIBUTE typedef Menu CCMenu;
CC_DEPRECATED_ATTRIBUTE typedef ClippingNode CCClippingNode;
CC_DEPRECATED_ATTRIBUTE typedef MotionStreak CCMotionStreak;
CC_DEPRECATED_ATTRIBUTE typedef ProgressTimer CCProgressTimer;
CC_DEPRECATED_ATTRIBUTE typedef RenderTexture CCRenderTexture;
CC_DEPRECATED_ATTRIBUTE typedef ParticleBatchNode CCParticleBatchNode;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSystem CCParticleSystem;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSystemQuad CCParticleSystemQuad;
CC_DEPRECATED_ATTRIBUTE typedef ParticleFire CCParticleFire;
CC_DEPRECATED_ATTRIBUTE typedef ParticleFireworks CCParticleFireworks;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSun CCParticleSun;
CC_DEPRECATED_ATTRIBUTE typedef ParticleGalaxy CCParticleGalaxy;
CC_DEPRECATED_ATTRIBUTE typedef ParticleFlower CCParticleFlower;
CC_DEPRECATED_ATTRIBUTE typedef ParticleMeteor CCParticleMeteor;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSpiral CCParticleSpiral;
CC_DEPRECATED_ATTRIBUTE typedef ParticleExplosion CCParticleExplosion;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSmoke CCParticleSmoke;
CC_DEPRECATED_ATTRIBUTE typedef ParticleSnow CCParticleSnow;
CC_DEPRECATED_ATTRIBUTE typedef ParticleRain CCParticleRain;
CC_DEPRECATED_ATTRIBUTE typedef FileUtils CCFileUtils;
CC_DEPRECATED_ATTRIBUTE typedef Application CCApplication;
CC_DEPRECATED_ATTRIBUTE typedef ShaderCache CCShaderCache;
CC_DEPRECATED_ATTRIBUTE typedef AnimationCache CCAnimationCache;
CC_DEPRECATED_ATTRIBUTE typedef SpriteFrameCache CCSpriteFrameCache;
CC_DEPRECATED_ATTRIBUTE typedef TextureCache CCTextureCache;
CC_DEPRECATED_ATTRIBUTE typedef ParallaxNode CCParallaxNode;
CC_DEPRECATED_ATTRIBUTE typedef TMXObjectGroup CCTMXObjectGroup;
CC_DEPRECATED_ATTRIBUTE typedef TMXLayerInfo CCTMXLayerInfo;
CC_DEPRECATED_ATTRIBUTE typedef TMXTilesetInfo CCTMXTilesetInfo;
CC_DEPRECATED_ATTRIBUTE typedef TMXMapInfo CCTMXMapInfo;
CC_DEPRECATED_ATTRIBUTE typedef TMXLayer CCTMXLayer;
CC_DEPRECATED_ATTRIBUTE typedef TMXTiledMap CCTMXTiledMap;
CC_DEPRECATED_ATTRIBUTE typedef TileMapAtlas CCTileMapAtlas;
CC_DEPRECATED_ATTRIBUTE typedef Timer CCTimer;
CC_DEPRECATED_ATTRIBUTE typedef Scheduler CCScheduler;
CC_DEPRECATED_ATTRIBUTE typedef GLView CCEGLView;

CC_DEPRECATED_ATTRIBUTE typedef Component CCComponent;
CC_DEPRECATED_ATTRIBUTE typedef AffineTransform CCAffineTransform;
CC_DEPRECATED_ATTRIBUTE typedef Point CCPoint;
CC_DEPRECATED_ATTRIBUTE typedef Size CCSize;
CC_DEPRECATED_ATTRIBUTE typedef Rect CCRect;
CC_DEPRECATED_ATTRIBUTE typedef Color3B ccColor3B;
CC_DEPRECATED_ATTRIBUTE typedef Color4F ccColor4F;
CC_DEPRECATED_ATTRIBUTE typedef Color4B ccColor4B;
CC_DEPRECATED_ATTRIBUTE typedef Vertex2F ccVertex2F;
CC_DEPRECATED_ATTRIBUTE typedef Vertex3F ccVertex3F;
CC_DEPRECATED_ATTRIBUTE typedef Tex2F ccTex2F;
CC_DEPRECATED_ATTRIBUTE typedef PointSprite ccPointSprite;
CC_DEPRECATED_ATTRIBUTE typedef Quad2 ccQuad2;
CC_DEPRECATED_ATTRIBUTE typedef Quad3 ccQuad3;
CC_DEPRECATED_ATTRIBUTE typedef V2F_C4B_T2F ccV2F_C4B_T2F;
CC_DEPRECATED_ATTRIBUTE typedef V2F_C4F_T2F ccV2F_C4F_T2F;
CC_DEPRECATED_ATTRIBUTE typedef V3F_C4B_T2F ccV3F_C4B_T2F;
CC_DEPRECATED_ATTRIBUTE typedef V2F_C4B_T2F_Triangle ccV2F_C4B_T2F_Triangle;
CC_DEPRECATED_ATTRIBUTE typedef V2F_C4B_T2F_Quad ccV2F_C4B_T2F_Quad;
CC_DEPRECATED_ATTRIBUTE typedef V3F_C4B_T2F_Quad ccV3F_C4B_T2F_Quad;
CC_DEPRECATED_ATTRIBUTE typedef V2F_C4F_T2F_Quad ccV2F_C4F_T2F_Quad;
CC_DEPRECATED_ATTRIBUTE typedef BlendFunc ccBlendFunc;
CC_DEPRECATED_ATTRIBUTE typedef T2F_Quad ccT2F_Quad;
CC_DEPRECATED_ATTRIBUTE typedef AnimationFrameData ccAnimationFrameData;
CC_DEPRECATED_ATTRIBUTE typedef FontShadow ccFontShadow;
CC_DEPRECATED_ATTRIBUTE typedef FontStroke ccFontStroke;
CC_DEPRECATED_ATTRIBUTE typedef FontDefinition ccFontDefinition;

CC_DEPRECATED_ATTRIBUTE typedef TextVAlignment CCVerticalTextAlignment;
CC_DEPRECATED_ATTRIBUTE typedef TextHAlignment CCTextAlignment;
CC_DEPRECATED_ATTRIBUTE typedef ProgressTimer::Type CCProgressTimerType;

CC_DEPRECATED_ATTRIBUTE typedef void* CCZone;

CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttrib_Position = GLProgram::VERTEX_ATTRIB_POSITION;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttrib_Color = GLProgram::VERTEX_ATTRIB_COLOR;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttrib_TexCoords = GLProgram::VERTEX_ATTRIB_TEX_COORDS;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttrib_MAX = GLProgram::VERTEX_ATTRIB_MAX;

CC_DEPRECATED_ATTRIBUTE const int kCCUniformPMatrix = GLProgram::UNIFORM_P_MATRIX;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformMVMatrix = GLProgram::UNIFORM_MV_MATRIX;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformMVPMatrix = GLProgram::UNIFORM_MVP_MATRIX;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformTime = GLProgram::UNIFORM_TIME;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformSinTime = GLProgram::UNIFORM_SIN_TIME;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformCosTime = GLProgram::UNIFORM_COS_TIME;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformRandom01 = GLProgram::UNIFORM_RANDOM01;
CC_DEPRECATED_ATTRIBUTE const int kCCUniformSampler = GLProgram::UNIFORM_SAMPLER;
CC_DEPRECATED_ATTRIBUTE const int kCCUniform_MAX = GLProgram::UNIFORM_MAX;

CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionTextureColor;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionTextureColorAlphaTest;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionColor;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionTexture;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionTexture_uColor;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionTextureA8Color;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_Position_uColor;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCShader_PositionLengthTexureColor;

// uniform names
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformPMatrix_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformMVMatrix_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformMVPMatrix_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformTime_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformSinTime_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformCosTime_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformRandom01_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformSampler_s;
CC_DEPRECATED_ATTRIBUTE extern const char* kCCUniformAlphaTestValue;

// Attribute names
CC_DEPRECATED_ATTRIBUTE extern const char*    kCCAttributeNameColor;
CC_DEPRECATED_ATTRIBUTE extern const char*    kCCAttributeNamePosition;
CC_DEPRECATED_ATTRIBUTE extern const char*    kCCAttributeNameTexCoord;

CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_None = GL::VERTEX_ATTRIB_FLAT_NONE;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_Position = GL::VERTEX_ATTRIB_FLAG_POSITION;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_Color = GL::VERTEX_ATTRIB_FLAG_COLOR;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_TexCoords = GL::VERTEX_ATTRIB_FLAG_TEX_COORDS;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_PosColorTex = GL::VERTEX_ATTRIB_FLAG_POS_COLOR_TEX;

CC_DEPRECATED_ATTRIBUTE const ProgressTimer::Type kCCProgressTimerTypeRadial = ProgressTimer::Type::RADIAL;
CC_DEPRECATED_ATTRIBUTE const ProgressTimer::Type kCCProgressTimerTypeBar = ProgressTimer::Type::BAR;
CC_DEPRECATED_ATTRIBUTE typedef ProgressTimer::Type ProgressTimerType;

CC_DEPRECATED_ATTRIBUTE const Director::Projection kCCDirectorProjection2D = Director::Projection::_2D;
CC_DEPRECATED_ATTRIBUTE const Director::Projection kCCDirectorProjection3D = Director::Projection::_3D;
CC_DEPRECATED_ATTRIBUTE const Director::Projection kCCDirectorProjectionCustom = Director::Projection::CUSTOM;
CC_DEPRECATED_ATTRIBUTE const Director::Projection kCCDirectorProjectionDefault = Director::Projection::DEFAULT;
CC_DEPRECATED_ATTRIBUTE typedef Director::Projection ccDirectorProjection;

CC_DEPRECATED_ATTRIBUTE const TextVAlignment kCCVerticalTextAlignmentTop = TextVAlignment::TOP;
CC_DEPRECATED_ATTRIBUTE const TextVAlignment kCCVerticalTextAlignmentCenter = TextVAlignment::CENTER;
CC_DEPRECATED_ATTRIBUTE const TextVAlignment kCCVerticalTextAlignmentBottom = TextVAlignment::BOTTOM;

CC_DEPRECATED_ATTRIBUTE const TextHAlignment kCCTextAlignmentLeft = TextHAlignment::LEFT;
CC_DEPRECATED_ATTRIBUTE const TextHAlignment kCCTextAlignmentCenter = TextHAlignment::CENTER;
CC_DEPRECATED_ATTRIBUTE const TextHAlignment kCCTextAlignmentRight = TextHAlignment::RIGHT;

CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGBA8888 = Texture2D::PixelFormat::RGBA8888;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB888 = Texture2D::PixelFormat::RGB888;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB565 = Texture2D::PixelFormat::RGB565;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_A8 = Texture2D::PixelFormat::A8;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_I8 = Texture2D::PixelFormat::I8;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_AI88 = Texture2D::PixelFormat::AI88;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGBA4444 = Texture2D::PixelFormat::RGBA4444;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_RGB5A1 = Texture2D::PixelFormat::RGB5A1;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_PVRTC4 = Texture2D::PixelFormat::PVRTC4;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_PVRTC2 = Texture2D::PixelFormat::PVRTC2;
CC_DEPRECATED_ATTRIBUTE const Texture2D::PixelFormat kCCTexture2DPixelFormat_Default = Texture2D::PixelFormat::DEFAULT;

CC_DEPRECATED_ATTRIBUTE typedef Texture2D::PixelFormat CCTexture2DPixelFormat;


CC_DEPRECATED_ATTRIBUTE const int kCCParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
CC_DEPRECATED_ATTRIBUTE const int kCCParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
CC_DEPRECATED_ATTRIBUTE const int kCCParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

CC_DEPRECATED_ATTRIBUTE const int kParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
CC_DEPRECATED_ATTRIBUTE const int kParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
CC_DEPRECATED_ATTRIBUTE const int kParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

CC_DEPRECATED_ATTRIBUTE const ParticleSystem::Mode kCCParticleModeGravity = ParticleSystem::Mode::GRAVITY;
CC_DEPRECATED_ATTRIBUTE const ParticleSystem::Mode kCCParticleModeRadius = ParticleSystem::Mode::RADIUS;
CC_DEPRECATED_ATTRIBUTE const int kCCParticleDefaultCapacity = kParticleDefaultCapacity;

CC_DEPRECATED_ATTRIBUTE const ParticleSystem::PositionType kCCPositionTypeFree =  ParticleSystem::PositionType::FREE;
CC_DEPRECATED_ATTRIBUTE const ParticleSystem::PositionType kCCPositionTypeRelative =  ParticleSystem::PositionType::RELATIVE;
CC_DEPRECATED_ATTRIBUTE const ParticleSystem::PositionType kCCPositionTypeGrouped =  ParticleSystem::PositionType::GROUPED;

CC_DEPRECATED_ATTRIBUTE typedef ParticleSystem::PositionType tPositionType;

#define kCCLabelAutomaticWidth  kLabelAutomaticWidth


CC_DEPRECATED_ATTRIBUTE const Menu::State kCCMenuStateWaiting = Menu::State::WAITING;
CC_DEPRECATED_ATTRIBUTE const Menu::State kCCMenuStateTrackingTouch = Menu::State::TRACKING_TOUCH;

CC_DEPRECATED_ATTRIBUTE typedef Menu::State tMenuState;

CC_DEPRECATED_ATTRIBUTE const Touch::DispatchMode kCCTouchesOneByOne = Touch::DispatchMode::ONE_BY_ONE;
CC_DEPRECATED_ATTRIBUTE const Touch::DispatchMode kCCTouchesAllAtOnce = Touch::DispatchMode::ALL_AT_ONCE;

CC_DEPRECATED_ATTRIBUTE typedef Touch::DispatchMode ccTouchesMode;

CC_DEPRECATED_ATTRIBUTE const Image::Format kCCImageFormatPNG = Image::Format::PNG;
CC_DEPRECATED_ATTRIBUTE const Image::Format kCCImageFormatJPEG = Image::Format::JPG;

CC_DEPRECATED_ATTRIBUTE typedef Image::Format tImageFormat;

CC_DEPRECATED_ATTRIBUTE const TransitionScene::Orientation kCCTransitionOrientationLeftOver = TransitionScene::Orientation::LEFT_OVER;
CC_DEPRECATED_ATTRIBUTE const TransitionScene::Orientation kCCTransitionOrientationRightOver = TransitionScene::Orientation::RIGHT_OVER;
CC_DEPRECATED_ATTRIBUTE const TransitionScene::Orientation kCCTransitionOrientationUpOver = TransitionScene::Orientation::UP_OVER;
CC_DEPRECATED_ATTRIBUTE const TransitionScene::Orientation kCCTransitionOrientationDownOver = TransitionScene::Orientation::DOWN_OVER;

CC_DEPRECATED_ATTRIBUTE typedef TransitionScene::Orientation tOrientation;

CC_DEPRECATED_ATTRIBUTE const int kCCPrioritySystem = Scheduler::PRIORITY_SYSTEM;
CC_DEPRECATED_ATTRIBUTE const int kCCPriorityNonSystemMin = Scheduler::PRIORITY_NON_SYSTEM_MIN;

CC_DEPRECATED_ATTRIBUTE const int kCCActionTagInvalid = Action::INVALID_TAG;
CC_DEPRECATED_ATTRIBUTE const int kCCNodeTagInvalid = Node::INVALID_TAG;

CC_DEPRECATED_ATTRIBUTE const int kCCNodeOnEnter = kNodeOnEnter;
CC_DEPRECATED_ATTRIBUTE const int kCCNodeOnExit = kNodeOnExit;
CC_DEPRECATED_ATTRIBUTE const int kCCNodeOnEnterTransitionDidFinish = kNodeOnEnterTransitionDidFinish;
CC_DEPRECATED_ATTRIBUTE const int kCCNodeOnExitTransitionDidStart = kNodeOnExitTransitionDidStart;
CC_DEPRECATED_ATTRIBUTE const int kCCNodeOnCleanup = kNodeOnCleanup;


CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageEnglish     = LanguageType::ENGLISH;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageChinese     = LanguageType::CHINESE;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageFrench      = LanguageType::FRENCH;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageItalian     = LanguageType::ITALIAN;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageGerman      = LanguageType::GERMAN;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageSpanish     = LanguageType::SPANISH;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageRussian     = LanguageType::RUSSIAN;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageKorean      = LanguageType::KOREAN;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageJapanese    = LanguageType::JAPANESE;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageHungarian   = LanguageType::HUNGARIAN;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguagePortuguese  = LanguageType::PORTUGUESE;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageArabic      = LanguageType::ARABIC;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguageNorwegian   = LanguageType::NORWEGIAN;
CC_DEPRECATED_ATTRIBUTE const LanguageType kLanguagePolish      = LanguageType::POLISH;
CC_DEPRECATED_ATTRIBUTE typedef LanguageType ccLanguageType;


CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetWindows      = Application::Platform::OS_WINDOWS;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetLinux        = Application::Platform::OS_LINUX;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetMacOS        = Application::Platform::OS_MAC;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetAndroid      = Application::Platform::OS_ANDROID;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetIphone       = Application::Platform::OS_IPHONE;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetIpad         = Application::Platform::OS_IPAD;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetBlackBerry   = Application::Platform::OS_BLACKBERRY;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetNaCl         = Application::Platform::OS_NACL;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetEmscripten   = Application::Platform::OS_EMSCRIPTEN;
CC_DEPRECATED_ATTRIBUTE const Application::Platform kTargetTizen        = Application::Platform::OS_TIZEN;
CC_DEPRECATED_ATTRIBUTE typedef Application::Platform TargetPlatform;

CC_DEPRECATED_ATTRIBUTE const ResolutionPolicy kResolutionExactFit      = ResolutionPolicy::EXACT_FIT;
CC_DEPRECATED_ATTRIBUTE const ResolutionPolicy kResolutionNoBorder      = ResolutionPolicy::NO_BORDER;
CC_DEPRECATED_ATTRIBUTE const ResolutionPolicy kResolutionShowAll       = ResolutionPolicy::SHOW_ALL;
CC_DEPRECATED_ATTRIBUTE const ResolutionPolicy kResolutionFixedHeight   = ResolutionPolicy::FIXED_HEIGHT;
CC_DEPRECATED_ATTRIBUTE const ResolutionPolicy kResolutionFixedWidth    = ResolutionPolicy::FIXED_WIDTH;
CC_DEPRECATED_ATTRIBUTE const ResolutionPolicy kResolutionUnKnown       = ResolutionPolicy::UNKNOWN;


#define kCCTMXTileHorizontalFlag      kTMXTileHorizontalFlag
#define kCCTMXTileVerticalFlag        kTMXTileVerticalFlag
#define kCCTMXTileDiagonalFlag        kTMXTileDiagonalFlag
#define kCCFlipedAll                  kFlipedAll
#define kCCFlippedMask                kFlippedMask


/** use log() instead */
CC_DEPRECATED_ATTRIBUTE void CC_DLL CCLog(const char * pszFormat, ...) CC_FORMAT_PRINTF(1, 2);

CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawInit();
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawFree();
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawPoint( const Point& point );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawPoints( const Point *points, unsigned int numberOfPoints );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawLine( const Point& origin, const Point& destination );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawRect( Point origin, Point destination );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawSolidRect( Point origin, Point destination, Color4F color );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawPoly( const Point *vertices, unsigned int numOfVertices, bool closePolygon );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawSolidPoly( const Point *poli, unsigned int numberOfPoints, Color4F color );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawCircle( const Point& center, float radius, float angle, unsigned int segments, bool drawLineToCenter, float scaleX, float scaleY);
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawCircle( const Point& center, float radius, float angle, unsigned int segments, bool drawLineToCenter);
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawSolidCircle( const Point& center, float radius, float angle, unsigned int segments, float scaleX, float scaleY);
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawSolidCircle( const Point& center, float radius, float angle, unsigned int segments);
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawQuadBezier(const Point& origin, const Point& control, const Point& destination, unsigned int segments);
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawCubicBezier(const Point& origin, const Point& control1, const Point& control2, const Point& destination, unsigned int segments);
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawCatmullRom( PointArray *arrayOfControlPoints, unsigned int segments );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawCardinalSpline( PointArray *config, float tension,  unsigned int segments );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawColor4B( GLubyte r, GLubyte g, GLubyte b, GLubyte a );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccDrawColor4F( GLfloat r, GLfloat g, GLfloat b, GLfloat a );
CC_DEPRECATED_ATTRIBUTE void CC_DLL ccPointSize( GLfloat pointSize );


CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLInvalidateStateCache() { GL::invalidateStateCache(); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLUseProgram(GLuint program) { GL::useProgram(program); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLDeleteProgram(GLuint program){ GL::deleteProgram(program); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLBlendFunc(GLenum sfactor, GLenum dfactor) { GL::blendFunc(sfactor, dfactor); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLBlendResetToCache() { GL::blendResetToCache(); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccSetProjectionMatrixDirty() { GL::setProjectionMatrixDirty(); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLEnableVertexAttribs(unsigned int flags) { GL::enableVertexAttribs(flags); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLBindTexture2D(GLuint textureId) { GL::bindTexture2D(textureId); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLBindTexture2DN(GLuint textureUnit, GLuint textureId) { GL::bindTexture2DN(textureUnit, textureId); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLDeleteTexture(GLuint textureId) { GL::deleteTexture(textureId); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLDeleteTextureN(GLuint textureUnit, GLuint textureId) { GL::deleteTextureN(textureUnit, textureId); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLBindVAO(GLuint vaoId) { GL::bindVAO(vaoId); }
CC_DEPRECATED_ATTRIBUTE inline void CC_DLL ccGLEnable( int flags ) { /* ignore */ };
CC_DEPRECATED_ATTRIBUTE typedef int ccGLServerState;

CC_DEPRECATED_ATTRIBUTE typedef Data CCData;
CC_DEPRECATED_ATTRIBUTE typedef __Set CCSet;
CC_DEPRECATED_ATTRIBUTE typedef __SetIterator CCSetIterator;
CC_DEPRECATED_ATTRIBUTE typedef __Set Set;
CC_DEPRECATED_ATTRIBUTE typedef __SetIterator SetIterator;

CC_DEPRECATED_ATTRIBUTE typedef __Array CCArray;
CC_DEPRECATED_ATTRIBUTE typedef __Array Array;

CC_DEPRECATED_ATTRIBUTE typedef __Dictionary Dictionary;
CC_DEPRECATED_ATTRIBUTE typedef __Dictionary CCDictionary;

CC_DEPRECATED_ATTRIBUTE typedef __Double Double;
CC_DEPRECATED_ATTRIBUTE typedef __Double CCDouble;
CC_DEPRECATED_ATTRIBUTE typedef __Float Float;
CC_DEPRECATED_ATTRIBUTE typedef __Float CCFloat;
CC_DEPRECATED_ATTRIBUTE typedef __Integer Integer;
CC_DEPRECATED_ATTRIBUTE typedef __Integer CCInteger;
CC_DEPRECATED_ATTRIBUTE typedef __Bool Bool;
CC_DEPRECATED_ATTRIBUTE typedef __Bool CCBool;
CC_DEPRECATED_ATTRIBUTE typedef __String CCString;
CC_DEPRECATED_ATTRIBUTE typedef __String String;

CC_DEPRECATED_ATTRIBUTE typedef __RGBAProtocol RGBAProtocol;
CC_DEPRECATED_ATTRIBUTE typedef __NodeRGBA NodeRGBA;
CC_DEPRECATED_ATTRIBUTE typedef __LayerRGBA LayerRGBA;

NS_CC_END


#endif // __COCOS2D_CCDEPRECATED_H__
