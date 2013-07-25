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

/** Add deprecated global functions and variables here
 */

#ifndef __COCOS2D_CCDEPRECATED_H__
#define __COCOS2D_CCDEPRECATED_H__

#include <math.h>
#include "cocoa/CCGeometry.h"
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
 ccpSegmentIntersect returns YES if Segment A-B intersects with segment C-D
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


CC_DEPRECATED_ATTRIBUTE const Point CCPointZero = Point::ZERO;

/* The "zero" size -- equivalent to Size(0, 0). */
CC_DEPRECATED_ATTRIBUTE const Size CCSizeZero = Size::ZERO;

/* The "zero" rectangle -- equivalent to Rect(0, 0, 0, 0). */
CC_DEPRECATED_ATTRIBUTE const Rect CCRectZero = Rect::ZERO;


CC_DEPRECATED_ATTRIBUTE const Color3B ccWHITE = Color3B::WHITE;
CC_DEPRECATED_ATTRIBUTE const Color3B ccYELLOW = Color3B::YELLOW;
CC_DEPRECATED_ATTRIBUTE const Color3B ccGREEN = Color3B::GREEN;
CC_DEPRECATED_ATTRIBUTE const Color3B ccBLUE = Color3B::BLUE;
CC_DEPRECATED_ATTRIBUTE const Color3B ccRED = Color3B::RED;
CC_DEPRECATED_ATTRIBUTE const Color3B ccMAGENTA = Color3B::MAGENTA;
CC_DEPRECATED_ATTRIBUTE const Color3B ccBLACK = Color3B::BLACK;
CC_DEPRECATED_ATTRIBUTE const Color3B ccORANGE = Color3B::ORANGE;
CC_DEPRECATED_ATTRIBUTE const Color3B ccGRAY = Color3B::GRAY;

CC_DEPRECATED_ATTRIBUTE const BlendFunc kBlendFuncDisable = BlendFunc::BLEND_FUNC_DISABLE;

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

#define CCAffineTransformMake AffineTransformMake
#define CCPointApplyAffineTransform PointApplyAffineTransform
#define CCSizeApplyAffineTransform SizeApplyAffineTransform

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

#define CCAffineTransformIdentity   AffineTransformIdentity


// CC prefix compatibility
CC_DEPRECATED_ATTRIBUTE typedef Object CCObject;
CC_DEPRECATED_ATTRIBUTE typedef Event CCEvent;
CC_DEPRECATED_ATTRIBUTE typedef Integer CCInteger;
CC_DEPRECATED_ATTRIBUTE typedef String CCString;
CC_DEPRECATED_ATTRIBUTE typedef Bool CCBool;
CC_DEPRECATED_ATTRIBUTE typedef Float CCFloat;
CC_DEPRECATED_ATTRIBUTE typedef Double CCDouble;
CC_DEPRECATED_ATTRIBUTE typedef Data CCData;
CC_DEPRECATED_ATTRIBUTE typedef Set CCSet;
CC_DEPRECATED_ATTRIBUTE typedef Array CCArray;
CC_DEPRECATED_ATTRIBUTE typedef Dictionary CCDictionary;
CC_DEPRECATED_ATTRIBUTE typedef DataVisitor CCDataVisitor;
CC_DEPRECATED_ATTRIBUTE typedef PrettyPrinter CCPrettyPrinter;
CC_DEPRECATED_ATTRIBUTE typedef Acceleration CCAcceleration;
CC_DEPRECATED_ATTRIBUTE typedef TextureAtlas CCTextureAtlas;
CC_DEPRECATED_ATTRIBUTE typedef Configuration CCConfiguration;
CC_DEPRECATED_ATTRIBUTE typedef PointArray CCPointArray;
CC_DEPRECATED_ATTRIBUTE typedef SetIterator CCSetIterator;
CC_DEPRECATED_ATTRIBUTE typedef RemoveSelf CCRemoveSelf;
CC_DEPRECATED_ATTRIBUTE typedef IMEDelegate CCIMEDelegate;
CC_DEPRECATED_ATTRIBUTE typedef IMEKeyboardNotificationInfo CCIMEKeyboardNotificationInfo;
CC_DEPRECATED_ATTRIBUTE typedef TextFieldDelegate CCTextFieldDelegate;
CC_DEPRECATED_ATTRIBUTE typedef TextFieldTTF CCTextFieldTTF;
CC_DEPRECATED_ATTRIBUTE typedef NotificationCenter CCNotificationCenter;
CC_DEPRECATED_ATTRIBUTE typedef TargetedTouchDelegate CCTargetedTouchDelegate;
CC_DEPRECATED_ATTRIBUTE typedef StandardTouchDelegate CCStandardTouchDelegate;
CC_DEPRECATED_ATTRIBUTE typedef TouchDelegate CCTouchDelegate;
CC_DEPRECATED_ATTRIBUTE typedef Image CCImage;
CC_DEPRECATED_ATTRIBUTE typedef UserDefault CCUserDefault;

CC_DEPRECATED_ATTRIBUTE typedef Action CCAction;
CC_DEPRECATED_ATTRIBUTE typedef FiniteTimeAction CCFiniteTimeAction;
CC_DEPRECATED_ATTRIBUTE typedef Speed CCSpeed;
CC_DEPRECATED_ATTRIBUTE typedef Follow CCFollow;
CC_DEPRECATED_ATTRIBUTE typedef GLProgram CCGLProgram;
CC_DEPRECATED_ATTRIBUTE typedef Touch CCTouch;
CC_DEPRECATED_ATTRIBUTE typedef Set CCSet;
CC_DEPRECATED_ATTRIBUTE typedef Texture2D CCTexture2D;
CC_DEPRECATED_ATTRIBUTE typedef Node CCNode;
CC_DEPRECATED_ATTRIBUTE typedef NodeRGBA CCNodeRGBA;
CC_DEPRECATED_ATTRIBUTE typedef RGBAProtocol CCRGBAProtocol;
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
CC_DEPRECATED_ATTRIBUTE typedef TouchDelegate CCTouchDelegate;
CC_DEPRECATED_ATTRIBUTE typedef KeypadDelegate CCKeypadDelegate;
CC_DEPRECATED_ATTRIBUTE typedef LayerRGBA CCLayerRGBA;
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
CC_DEPRECATED_ATTRIBUTE typedef EGLView CCEGLView;

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

CC_DEPRECATED_ATTRIBUTE typedef VerticalTextAlignment CCVerticalTextAlignment;
CC_DEPRECATED_ATTRIBUTE typedef TextAlignment CCTextAlignment;
CC_DEPRECATED_ATTRIBUTE typedef ProgressTimer::Type CCProgressTimerType;

CC_DEPRECATED_ATTRIBUTE typedef void* CCZone;

#define kCCVertexAttrib_Position     kVertexAttrib_Position
#define kCCVertexAttrib_Color        kVertexAttrib_Color
#define kCCVertexAttrib_TexCoords    kVertexAttrib_TexCoords
#define kCCVertexAttrib_MAX          kVertexAttrib_MAX

#define kCCUniformPMatrix    kUniformPMatrix
#define kCCUniformMVMatrix   kUniformMVMatrix
#define kCCUniformMVPMatrix  kUniformMVPMatrix
#define kCCUniformTime       kUniformTime
#define kCCUniformSinTime    kUniformSinTime
#define kCCUniformCosTime    kUniformCosTime
#define kCCUniformRandom01   kUniformRandom01
#define kCCUniformSampler    kUniformSampler
#define kCCUniform_MAX       kUniform_MAX


#define kCCShader_PositionTextureColor              kShader_PositionTextureColor
#define kCCShader_PositionTextureColorAlphaTest     kShader_PositionTextureColorAlphaTest
#define kCCShader_PositionColor                     kShader_PositionColor
#define kCCShader_PositionTexture                   kShader_PositionTexture
#define kCCShader_PositionTexture_uColor            kShader_PositionTexture_uColor
#define kCCShader_PositionTextureA8Color            kShader_PositionTextureA8Color
#define kCCShader_Position_uColor                   kShader_Position_uColor
#define kCCShader_PositionLengthTexureColor         kShader_PositionLengthTexureColor

// uniform names
#define kCCUniformPMatrix_s				kUniformPMatrix_s
#define kCCUniformMVMatrix_s			kUniformMVMatrix_s
#define kCCUniformMVPMatrix_s			kUniformMVPMatrix_s
#define kCCUniformTime_s				kUniformTime_s
#define kCCUniformSinTime_s				kUniformSinTime_s
#define kCCUniformCosTime_s				kUniformCosTime_s
#define kCCUniformRandom01_s			kUniformRandom01_s
#define kCCUniformSampler_s				kUniformSampler_s
#define kCCUniformAlphaTestValue		kUniformAlphaTestValue

// Attribute names
#define    kCCAttributeNameColor           kAttributeNameColor
#define    kCCAttributeNamePosition        kAttributeNamePosition
#define    kCCAttributeNameTexCoord        kAttributeNameTexCoord

CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_None = VERTEX_ATTRIB_FLAT_NONE;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_Position = VERTEX_ATTRIB_FLAG_POSITION;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_Color = VERTEX_ATTRIB_FLAG_COLOR;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_TexCoords = VERTEX_ATTRIB_FLAG_TEX_COORDS;
CC_DEPRECATED_ATTRIBUTE const int kCCVertexAttribFlag_PosColorTex = VERTEX_ATTRIB_FLAG_POS_COLOR_TEX;

#define kCCProgressTimerTypeRadial ProgressTimer::RADIAL
#define kCCProgressTimerTypeBar    ProgressTimer::BAR
CC_DEPRECATED_ATTRIBUTE typedef enum ProgressTimer::Type ProgressTimerType;

CC_DEPRECATED_ATTRIBUTE const int kCCDirectorProjection2D = Director::PROJECTION_2D;
CC_DEPRECATED_ATTRIBUTE const int kCCDirectorProjection3D = Director::PROJECTION_3D; 
CC_DEPRECATED_ATTRIBUTE const int kCCDirectorProjectionCustom = Director::PROJECTION_CUSTOM;
CC_DEPRECATED_ATTRIBUTE const int kCCDirectorProjectionDefault = Director::PROJECTION_DEFAULT;
CC_DEPRECATED_ATTRIBUTE typedef enum Director::Projection ccDirectorProjection;

CC_DEPRECATED_ATTRIBUTE const int ConfigurationError = Configuration::ERROR;
CC_DEPRECATED_ATTRIBUTE const int ConfigurationString = Configuration::STRING;
CC_DEPRECATED_ATTRIBUTE const int ConfigurationInt = Configuration::INT;
CC_DEPRECATED_ATTRIBUTE const int ConfigurationDouble = Configuration::DOUBLE;
CC_DEPRECATED_ATTRIBUTE const int ConfigurationBoolean = Configuration::BOOLEAN;
CC_DEPRECATED_ATTRIBUTE typedef enum Configuration::Type ccConfigurationType;

#define kCCVerticalTextAlignmentTop     kVerticalTextAlignmentTop
#define kCCVerticalTextAlignmentCenter  kVerticalTextAlignmentCenter
#define kCCVerticalTextAlignmentBottom  kVerticalTextAlignmentBottom

#define kCCTextAlignmentLeft        kTextAlignmentLeft
#define kCCTextAlignmentCenter      kTextAlignmentCenter
#define kCCTextAlignmentRight       kTextAlignmentRight


#define kCCTexture2DPixelFormat_RGBA8888    kTexture2DPixelFormat_RGBA8888
#define kCCTexture2DPixelFormat_RGB888      kTexture2DPixelFormat_RGB888
#define kCCTexture2DPixelFormat_RGB565      kTexture2DPixelFormat_RGB565
#define kCCTexture2DPixelFormat_A8          kTexture2DPixelFormat_A8
#define kCCTexture2DPixelFormat_I8          kTexture2DPixelFormat_I8
#define kCCTexture2DPixelFormat_AI88        kTexture2DPixelFormat_AI88
#define kCCTexture2DPixelFormat_RGBA4444    kTexture2DPixelFormat_RGBA4444
#define kCCTexture2DPixelFormat_RGB5A1      kTexture2DPixelFormat_RGB5A1
#define kCCTexture2DPixelFormat_PVRTC4      kTexture2DPixelFormat_PVRTC4
#define kCCTexture2DPixelFormat_PVRTC2      kTexture2DPixelFormat_PVRTC2
#define kCCTexture2DPixelFormat_Default       kTexture2DPixelFormat_Default

#define kCCLabelAutomaticWidth  kLabelAutomaticWidth

CC_DEPRECATED_ATTRIBUTE const int kCCParticleDurationInfinity = ParticleSystem::DURATION_INFINITY;
CC_DEPRECATED_ATTRIBUTE const int kCCParticleStartSizeEqualToEndSize = ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE;
CC_DEPRECATED_ATTRIBUTE const int kCCParticleStartRadiusEqualToEndRadius = ParticleSystem::START_RADIUS_EQUAL_TO_END_RADIUS;

CC_DEPRECATED_ATTRIBUTE const int kCCParticleModeGravity = ParticleSystem::MODE_GRAVITY;
CC_DEPRECATED_ATTRIBUTE const int kCCParticleModeRadius = ParticleSystem::MODE_RADIUS;

CC_DEPRECATED_ATTRIBUTE const int kCCPositionTypeFree =  ParticleSystem::FREE;
CC_DEPRECATED_ATTRIBUTE const int kCCPositionTypeRelative =  ParticleSystem::RELATIVE;
CC_DEPRECATED_ATTRIBUTE const int kCCPositionTypeGrouped =  ParticleSystem::GROUPED;
CC_DEPRECATED_ATTRIBUTE typedef enum ParticleSystem::PositionType tPositionType;

#define kCCBlendFuncDisable   kBlendFuncDisable

#define kCCMenuHandlerPriority        kMenuHandlerPriority
#define kCCMenuStateWaiting           kMenuStateWaiting
#define kCCMenuStateTrackingTouch     kMenuStateTrackingTouch

#define kCCTouchesOneByOne      kTouchesOneByOne
#define kCCTouchesAllAtOnce     kTouchesAllAtOnce

#define kCCImageFormatPNG   kImageFormatPNG
#define kCCImageFormatJPEG  kImageFormatJPEG

#define kCCTransitionOrientationLeftOver    kTransitionOrientationLeftOver
#define kCCTransitionOrientationRightOver   kTransitionOrientationRightOver
#define kCCTransitionOrientationUpOver      kTransitionOrientationUpOver
#define kCCTransitionOrientationDownOver    kTransitionOrientationDownOver

#define kCCPrioritySystem           kPrioritySystem
#define kCCPriorityNonSystemMin     kPriorityNonSystemMin

#define kCCTMXTileHorizontalFlag      kTMXTileHorizontalFlag
#define kCCTMXTileVerticalFlag        kTMXTileVerticalFlag
#define kCCTMXTileDiagonalFlag        kTMXTileDiagonalFlag
#define kCCFlipedAll                  kFlipedAll
#define kCCFlippedMask                kFlippedMask


/** use log() instead */
CC_DEPRECATED_ATTRIBUTE void CC_DLL CCLog(const char * pszFormat, ...) CC_FORMAT_PRINTF(1, 2);

// end of data_structures group
/// @}

NS_CC_END


#endif // __COCOS2D_CCDEPRECATED_H__
