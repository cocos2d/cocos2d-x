//
//  S_CCActions.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/19/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_S_CCActions_h
#define TestCocos2dX_S_CCActions_h

#include <JavaScriptCore/JavaScriptCore.h>
#include "cocos2d.h"
#include "ScriptingCore.h"

#define GLOBAL_CTX (ScriptingCore::getInstance().getGlobalContext())

using namespace cocos2d;

class S_CCAction : CCAction
{
public:
	// actions do not have a userData field
	JSObjectRef jsObject;
	
	SCRIPTABLE_BOILERPLATE

	S_CCAction() : CCAction(), jsObject(NULL) {};
	~S_CCAction() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	JS_STATIC_FUNC_DEF(jsIsDone);
	JS_STATIC_FUNC_DEF(jsStartWithTarget);
	JS_STATIC_FUNC_DEF(jsStop);
};

class S_CCSequence : public cocos2d::CCSequence
{
public:
	JSObjectRef jsObject;
	
	S_CCSequence() : CCSequence(), jsObject(NULL) {};
	~S_CCSequence() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsActions);
};

class S_CCRepeat : public cocos2d::CCRepeat
{
public:
	JSObjectRef jsObject;
	
	S_CCRepeat() : CCRepeat(), jsObject(NULL) {};
	~S_CCRepeat();

	SCRIPTABLE_BOILERPLATE
};

class S_CCRepeatForever : public cocos2d::CCRepeatForever
{
public:
	JSObjectRef jsObject;
	
	S_CCRepeatForever() : CCRepeatForever(), jsObject(NULL) {};
	~S_CCRepeatForever();

	SCRIPTABLE_BOILERPLATE
};

class S_CCSpawn : public cocos2d::CCSpawn
{
public:
	JSObjectRef jsObject;
	
	S_CCSpawn() : CCSpawn(), jsObject(NULL) {};
	~S_CCSpawn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsActions);
};

class S_CCRotateTo : public cocos2d::CCRotateTo
{
public:
	JSObjectRef jsObject;
	
	S_CCRotateTo() : CCRotateTo(), jsObject(NULL) {};
	~S_CCRotateTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCRotateBy : public cocos2d::CCRotateBy
{
public:
	JSObjectRef jsObject;
	
	S_CCRotateBy() : CCRotateBy(), jsObject(NULL) {};
	~S_CCRotateBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCMoveTo : public cocos2d::CCMoveTo
{
public:
	JSObjectRef jsObject;
	
	S_CCMoveTo() : CCMoveTo(), jsObject(NULL) {};
	~S_CCMoveTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCMoveBy : public cocos2d::CCMoveBy
{
public:
	JSObjectRef jsObject;
	
	S_CCMoveBy() : CCMoveBy(), jsObject(NULL) {};
	~S_CCMoveBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCSkewTo : public cocos2d::CCSkewTo
{
public:
	JSObjectRef jsObject;
	
	S_CCSkewTo() : CCSkewTo(), jsObject(NULL) {};
	~S_CCSkewTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCSkewBy : public cocos2d::CCSkewBy
{
public:
	JSObjectRef jsObject;
	
	S_CCSkewBy() : CCSkewBy(), jsObject(NULL) {};
	~S_CCSkewBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCJumpBy : public cocos2d::CCJumpBy
{
public:
	JSObjectRef jsObject;
	
	S_CCJumpBy() : CCJumpBy(), jsObject(NULL) {};
	~S_CCJumpBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCJumpTo : public cocos2d::CCJumpTo
{
public:
	JSObjectRef jsObject;
	
	S_CCJumpTo() : CCJumpTo(), jsObject(NULL) {};
	~S_CCJumpTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCBezierBy : public cocos2d::CCBezierBy
{
public:
	JSObjectRef jsObject;
	
	S_CCBezierBy() : CCBezierBy(), jsObject(NULL) {};
	~S_CCBezierBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCBezierTo : public cocos2d::CCBezierTo
{
public:
	JSObjectRef jsObject;
	
	S_CCBezierTo() : CCBezierTo(), jsObject(NULL) {};
	~S_CCBezierTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCScaleTo : public cocos2d::CCScaleTo
{
public:
	JSObjectRef jsObject;
	
	S_CCScaleTo() : CCScaleTo(), jsObject(NULL) {};
	~S_CCScaleTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCScaleBy : public cocos2d::CCScaleBy
{
public:
	JSObjectRef jsObject;
	
	S_CCScaleBy() : CCScaleBy(), jsObject(NULL) {};
	~S_CCScaleBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCBlink : public cocos2d::CCBlink
{
public:
	JSObjectRef jsObject;
	
	S_CCBlink() : CCBlink(), jsObject(NULL) {};
	~S_CCBlink() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeIn : public cocos2d::CCFadeIn
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeIn() : CCFadeIn(), jsObject(NULL) {};
	~S_CCFadeIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeOut : public cocos2d::CCFadeOut
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeOut() : CCFadeOut(), jsObject(NULL) {};
	~S_CCFadeOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeTo : public cocos2d::CCFadeTo
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeTo() : CCFadeTo(), jsObject(NULL) {};
	~S_CCFadeTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCTintTo : public cocos2d::CCTintTo
{
public:
	JSObjectRef jsObject;
	
	S_CCTintTo() : CCTintTo(), jsObject(NULL) {};
	~S_CCTintTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCTintBy : public cocos2d::CCTintBy
{
public:
	JSObjectRef jsObject;
	
	S_CCTintBy() : CCTintBy(), jsObject(NULL) {};
	~S_CCTintBy() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCDelayTime : public cocos2d::CCDelayTime
{
public:
	JSObjectRef jsObject;
	
	S_CCDelayTime() : CCDelayTime(), jsObject(NULL) {};
	~S_CCDelayTime() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCReverseTime : public cocos2d::CCReverseTime
{
public:
	JSObjectRef jsObject;
	
	S_CCReverseTime() : CCReverseTime(), jsObject(NULL) {};
	~S_CCReverseTime() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCAnimate : public cocos2d::CCAnimate
{
public:
	JSObjectRef jsObject;
	
	S_CCAnimate() : CCAnimate(), jsObject(NULL) {};
	~S_CCAnimate() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

/////////

class S_CCCallFunc : CCCallFunc
{
	JSObjectRef jsObject;
	JSObjectRef callback;

public:
	SCRIPTABLE_BOILERPLATE
	
	S_CCCallFunc() : CCCallFunc(), jsObject(NULL) {};
	~S_CCCallFunc();
	
	void callfunc();
};

class S_CCActionCamera : public cocos2d::CCActionCamera
{
public:
	JSObjectRef jsObject;
	
	S_CCActionCamera() : CCActionCamera(), jsObject(NULL) {};
	~S_CCActionCamera() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCOrbitCamera : public cocos2d::CCOrbitCamera
{
public:
	JSObjectRef jsObject;
	
	S_CCOrbitCamera() : CCOrbitCamera(), jsObject(NULL) {};
	~S_CCOrbitCamera() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsSphericalRadius);
};

class S_CCActionEase : public cocos2d::CCActionEase
{
public:
	JSObjectRef jsObject;
	
	S_CCActionEase() : CCActionEase(), jsObject(NULL) {};
	~S_CCActionEase() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseRateAction : public cocos2d::CCEaseRateAction
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseRateAction() : CCEaseRateAction(), jsObject(NULL) {};
	~S_CCEaseRateAction() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseIn : public cocos2d::CCEaseIn
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseIn() : CCEaseIn(), jsObject(NULL) {};
	~S_CCEaseIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseOut : public cocos2d::CCEaseOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseOut() : CCEaseOut(), jsObject(NULL) {};
	~S_CCEaseOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseInOut : public cocos2d::CCEaseInOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseInOut() : CCEaseInOut(), jsObject(NULL) {};
	~S_CCEaseInOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseExponentialIn : public cocos2d::CCEaseExponentialIn
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseExponentialIn() : CCEaseExponentialIn(), jsObject(NULL) {};
	~S_CCEaseExponentialIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseExponentialOut : public cocos2d::CCEaseExponentialOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseExponentialOut() : CCEaseExponentialOut(), jsObject(NULL) {};
	~S_CCEaseExponentialOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseExponentialInOut : public cocos2d::CCEaseExponentialInOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseExponentialInOut() : CCEaseExponentialInOut(), jsObject(NULL) {};
	~S_CCEaseExponentialInOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseSineIn : public cocos2d::CCEaseSineIn
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseSineIn() : CCEaseSineIn(), jsObject(NULL) {};
	~S_CCEaseSineIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseSineOut : public cocos2d::CCEaseSineOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseSineOut() : CCEaseSineOut(), jsObject(NULL) {};
	~S_CCEaseSineOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseSineInOut : public cocos2d::CCEaseSineInOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseSineInOut() : CCEaseSineInOut(), jsObject(NULL) {};
	~S_CCEaseSineInOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseElastic : public cocos2d::CCEaseElastic
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseElastic() : CCEaseElastic(), jsObject(NULL) {};
	~S_CCEaseElastic() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseElasticIn : public cocos2d::CCEaseElasticIn
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseElasticIn() : CCEaseElasticIn(), jsObject(NULL) {};
	~S_CCEaseElasticIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseElasticOut : public cocos2d::CCEaseElasticOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseElasticOut() : CCEaseElasticOut(), jsObject(NULL) {};
	~S_CCEaseElasticOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseElasticInOut : public cocos2d::CCEaseElasticInOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseElasticInOut() : CCEaseElasticInOut(), jsObject(NULL) {};
	~S_CCEaseElasticInOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBounce : public cocos2d::CCEaseBounce
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBounce() : CCEaseBounce(), jsObject(NULL) {};
	~S_CCEaseBounce() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBounceIn : public cocos2d::CCEaseBounceIn
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBounceIn() : CCEaseBounceIn(), jsObject(NULL) {};
	~S_CCEaseBounceIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBounceOut : public cocos2d::CCEaseBounceOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBounceOut() : CCEaseBounceOut(), jsObject(NULL) {};
	~S_CCEaseBounceOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBounceInOut : public cocos2d::CCEaseBounceInOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBounceInOut() : CCEaseBounceInOut(), jsObject(NULL) {};
	~S_CCEaseBounceInOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBackIn : public cocos2d::CCEaseBackIn
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBackIn() : CCEaseBackIn(), jsObject(NULL) {};
	~S_CCEaseBackIn() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBackOut : public cocos2d::CCEaseBackOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBackOut() : CCEaseBackOut(), jsObject(NULL) {};
	~S_CCEaseBackOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCEaseBackInOut : public cocos2d::CCEaseBackInOut
{
public:
	JSObjectRef jsObject;
	
	S_CCEaseBackInOut() : CCEaseBackInOut(), jsObject(NULL) {};
	~S_CCEaseBackInOut() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCGridAction : public cocos2d::CCGridAction
{
public:
	JSObjectRef jsObject;
	
	S_CCGridAction() : CCGridAction(), jsObject(NULL) {};
	~S_CCGridAction() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCGrid3DAction : public cocos2d::CCGrid3DAction
{
public:
	JSObjectRef jsObject;
	
	S_CCGrid3DAction() : CCGrid3DAction(), jsObject(NULL) {};
	~S_CCGrid3DAction() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCTiledGrid3DAction : public cocos2d::CCTiledGrid3DAction
{
public:
	JSObjectRef jsObject;
	
	S_CCTiledGrid3DAction() : CCTiledGrid3DAction(), jsObject(NULL) {};
	~S_CCTiledGrid3DAction() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCAccelDeccelAmplitude : public cocos2d::CCAccelDeccelAmplitude
{
public:
	JSObjectRef jsObject;
	
	S_CCAccelDeccelAmplitude() : CCAccelDeccelAmplitude(), jsObject(NULL) {};
	~S_CCAccelDeccelAmplitude() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCAccelAmplitude : public cocos2d::CCAccelAmplitude
{
public:
	JSObjectRef jsObject;
	
	S_CCAccelAmplitude() : CCAccelAmplitude(), jsObject(NULL) {};
	~S_CCAccelAmplitude() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCDeccelAmplitude : public cocos2d::CCDeccelAmplitude
{
public:
	JSObjectRef jsObject;
	
	S_CCDeccelAmplitude() : CCDeccelAmplitude(), jsObject(NULL) {};
	~S_CCDeccelAmplitude() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCWaves3D : public cocos2d::CCWaves3D
{
public:
	JSObjectRef jsObject;
	
	S_CCWaves3D() : CCWaves3D(), jsObject(NULL) {};
	~S_CCWaves3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFlipX3D : public cocos2d::CCFlipX3D
{
public:
	JSObjectRef jsObject;
	
	S_CCFlipX3D() : CCFlipX3D(), jsObject(NULL) {};
	~S_CCFlipX3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFlipY3D : public cocos2d::CCFlipY3D
{
public:
	JSObjectRef jsObject;
	
	S_CCFlipY3D() : CCFlipY3D(), jsObject(NULL) {};
	~S_CCFlipY3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCLens3D : public cocos2d::CCLens3D
{
public:
	JSObjectRef jsObject;
	
	S_CCLens3D() : CCLens3D(), jsObject(NULL) {};
	~S_CCLens3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsSetPosition);
};

class S_CCRipple3D : public cocos2d::CCRipple3D
{
public:
	JSObjectRef jsObject;
	
	S_CCRipple3D() : CCRipple3D(), jsObject(NULL) {};
	~S_CCRipple3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsSetPosition);
};

class S_CCShaky3D : public cocos2d::CCShaky3D
{
public:
	JSObjectRef jsObject;
	
	S_CCShaky3D() : CCShaky3D(), jsObject(NULL) {};
	~S_CCShaky3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCLiquid : public cocos2d::CCLiquid
{
public:
	JSObjectRef jsObject;
	
	S_CCLiquid() : CCLiquid(), jsObject(NULL) {};
	~S_CCLiquid() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCWaves : public cocos2d::CCWaves
{
public:
	JSObjectRef jsObject;
	
	S_CCWaves() : CCWaves(), jsObject(NULL) {};
	~S_CCWaves() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCTwirl : public cocos2d::CCTwirl
{
public:
	JSObjectRef jsObject;
	
	S_CCTwirl() : CCTwirl(), jsObject(NULL) {};
	~S_CCTwirl() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsSetPosition);
};

class S_CCPageTurn3D : public cocos2d::CCPageTurn3D
{
public:
	JSObjectRef jsObject;
	
	S_CCPageTurn3D() : CCPageTurn3D(), jsObject(NULL) {};
	~S_CCPageTurn3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCProgressTo : public cocos2d::CCProgressTo
{
public:
	JSObjectRef jsObject;
	
	S_CCProgressTo() : CCProgressTo(), jsObject(NULL) {};
	~S_CCProgressTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCProgressFromTo : public cocos2d::CCProgressFromTo
{
public:
	JSObjectRef jsObject;
	
	S_CCProgressFromTo() : CCProgressFromTo(), jsObject(NULL) {};
	~S_CCProgressFromTo() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCShakyTiles3D : public cocos2d::CCShakyTiles3D
{
public:
	JSObjectRef jsObject;
	
	S_CCShakyTiles3D() : CCShakyTiles3D(), jsObject(NULL) {};
	~S_CCShakyTiles3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCShatteredTiles3D : public cocos2d::CCShatteredTiles3D
{
public:
	JSObjectRef jsObject;
	
	S_CCShatteredTiles3D() : CCShatteredTiles3D(), jsObject(NULL) {};
	~S_CCShatteredTiles3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCShuffleTiles : public cocos2d::CCShuffleTiles
{
public:
	JSObjectRef jsObject;
	
	S_CCShuffleTiles() : CCShuffleTiles(), jsObject(NULL) {};
	~S_CCShuffleTiles() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeOutTRTiles : public cocos2d::CCFadeOutTRTiles
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeOutTRTiles() : CCFadeOutTRTiles(), jsObject(NULL) {};
	~S_CCFadeOutTRTiles() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeOutBLTiles : public cocos2d::CCFadeOutBLTiles
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeOutBLTiles() : CCFadeOutBLTiles(), jsObject(NULL) {};
	~S_CCFadeOutBLTiles() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeOutUpTiles : public cocos2d::CCFadeOutUpTiles
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeOutUpTiles() : CCFadeOutUpTiles(), jsObject(NULL) {};
	~S_CCFadeOutUpTiles() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCFadeOutDownTiles : public cocos2d::CCFadeOutDownTiles
{
public:
	JSObjectRef jsObject;
	
	S_CCFadeOutDownTiles() : CCFadeOutDownTiles(), jsObject(NULL) {};
	~S_CCFadeOutDownTiles() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCTurnOffTiles : public cocos2d::CCTurnOffTiles
{
public:
	JSObjectRef jsObject;
	
	S_CCTurnOffTiles() : CCTurnOffTiles(), jsObject(NULL) {};
	~S_CCTurnOffTiles() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCWavesTiles3D : public cocos2d::CCWavesTiles3D
{
public:
	JSObjectRef jsObject;
	
	S_CCWavesTiles3D() : CCWavesTiles3D(), jsObject(NULL) {};
	~S_CCWavesTiles3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCJumpTiles3D : public cocos2d::CCJumpTiles3D
{
public:
	JSObjectRef jsObject;
	
	S_CCJumpTiles3D() : CCJumpTiles3D(), jsObject(NULL) {};
	~S_CCJumpTiles3D() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCSplitRows : public cocos2d::CCSplitRows
{
public:
	JSObjectRef jsObject;
	
	S_CCSplitRows() : CCSplitRows(), jsObject(NULL) {};
	~S_CCSplitRows() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

class S_CCSplitCols : public cocos2d::CCSplitCols
{
public:
	JSObjectRef jsObject;
	
	S_CCSplitCols() : CCSplitCols(), jsObject(NULL) {};
	~S_CCSplitCols() { if (jsObject) JSValueUnprotect(GLOBAL_CTX, jsObject); }
	
	SCRIPTABLE_BOILERPLATE
};

#endif
