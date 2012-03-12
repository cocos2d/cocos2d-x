//
//  node.cpp
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/2/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#include <iostream>
#include "cocos2d.h"

#include "ScriptingCore.h"
#include "S_Classes.h"
#include "S_CCDirector.h"
#include "S_CCScheduler.h"
#include "S_CCSpriteFrameCache.h"
#include "S_CCNode.h"
#include "S_CCSprite.h"
#include "S_CCLabel.h"
#include "S_CCMenu.h"
#include "S_CCActions.h"
#include "S_CCAudio.h"
#include "S_CCScheduler.h"
#include "S_CCTransition.h"
#include "S_CCParticleSystem.h"
#include "S_CCAnimation.h"

void sc_genericCppFinalize(JSObjectRef object)
{
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	if (JSValueIsObjectOfClass(ctx, (JSValueRef)object, js_S_CCNode_class)) {
		CCNode *node = (CCNode *)JSObjectGetPrivate(object);
		CCLog("releasing node from JS: %x", node);
		if (node) {
			// remove our reference otherwise we might get another release
			node->setUserData(NULL);
			node->release();
		}
	} else if (JSValueIsObjectOfClass(ctx, (JSValueRef)object, js_S_CCAction_class)) {
		CCAction *action = (CCAction *)JSObjectGetPrivate(object);
		CCLog("releasing action from JS: %x", action);
		if (action) {
			action->stop();
			action->release();
		}
	}
}

#pragma mark - CCPoint & CCColor

JSClassRef		__jsCCPoint_class;
JSClassRef		__jsCCColor_class;

JSObjectRef		jsCCPointConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
void			jsCCPointFinalize(JSObjectRef object);
bool			jsCCPointHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName);
JSValueRef		jsCCPointGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception);
bool			jsCCPointSetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);

JSObjectRef		jsCCColorConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception);
void			jsCCColorFinalize(JSObjectRef object);
bool			jsCCColorHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName);
JSValueRef		jsCCColorGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception);
bool			jsCCColorSetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception);

JSObjectRef jsCCPointConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	CCPoint *pt = new CCPoint();
	if (argumentCount == 2) {
		pt->x = JSValueToNumber(ctx, arguments[0], NULL);
		pt->y = JSValueToNumber(ctx, arguments[1], NULL);
	}
	return JSObjectMake(ctx, __jsCCPoint_class, pt);
}

void jsCCPointFinalize(JSObjectRef object)
{
	CCPoint *pt = (CCPoint *)JSObjectGetPrivate(object);
	if (pt) {
		delete pt;
	}
}

bool jsCCPointHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	char *buff = (char *)JSStringGetCharactersPtr(propertyName);
	if (buff[0] == 'x' || buff[0] == 'y') {
		return true;
	}
	return false;
}

JSValueRef jsCCPointGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	char *buff = (char *)JSStringGetCharactersPtr(propertyNameJS);
	CCPoint *pt = (CCPoint *)JSObjectGetPrivate(object);
	if (pt && buff[0] == 'x') {
		return JSValueMakeNumber(ctx, pt->x);
	} else if (pt && buff[0] == 'y') {
		return JSValueMakeNumber(ctx, pt->y);
	}
	return JSValueMakeUndefined(ctx);
}

bool jsCCPointSetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception)
{
	char *buff = (char *)JSStringGetCharactersPtr(propertyName);
	CCPoint *pt = (CCPoint *)JSObjectGetPrivate(object);
	if (pt && buff[0] == 'x') {
		pt->x = JSValueToNumber(ctx, value, NULL);
		return true;
	} else if (pt && buff[0] == 'y') {
		pt->y = JSValueToNumber(ctx, value, NULL);
		return true;
	}
	return false;
}

JSValueRef jsCCPointDistance(JSContextRef ctx, JSObjectRef function, JSObjectRef thisObject, size_t argumentCount, const JSValueRef arguments[], JSValueRef *exception)
{
	CCPoint *pt = (CCPoint *)JSObjectGetPrivate(thisObject);
	if (pt && argumentCount == 1) {
		CCPoint *pt2 = (CCPoint *)JSObjectGetPrivate((JSObjectRef)arguments[0]);
		return JSValueMakeNumber(ctx, ccpDistance(*pt, *pt2));
	}
	return JSValueMakeUndefined(ctx);
}

JSObjectRef jsCCColorConstructor(JSContextRef ctx, JSObjectRef constructor, size_t argumentCount, const JSValueRef arguments[], JSValueRef* exception)
{
	ccColor3B *color = (ccColor3B *)malloc(sizeof(ccColor3B));
	if (argumentCount == 3) {
		color->r = JSValueToNumber(ctx, arguments[0], NULL);
		color->g = JSValueToNumber(ctx, arguments[1], NULL);
		color->b = JSValueToNumber(ctx, arguments[2], NULL);
	}
	return JSObjectMake(ctx, __jsCCColor_class, color);
}

void jsCCColorFinalize(JSObjectRef object)
{
	ccColor3B *color = (ccColor3B *)JSObjectGetPrivate(object);
	if (color) {
		free(color);
	}
}

bool jsCCColorHasProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName)
{
	char *buff = (char *)JSStringGetCharactersPtr(propertyName);
	if (buff[0] == 'r' || buff[0] == 'g' || buff[0] == 'b') {
		return true;
	}
	return false;
}

JSValueRef jsCCColorGetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyNameJS, JSValueRef* exception)
{
	char *buff = (char *)JSStringGetCharactersPtr(propertyNameJS);
	ccColor3B *color = (ccColor3B *)JSObjectGetPrivate(object);
	if (color && buff[0] == 'r') {
		return JSValueMakeNumber(ctx, color->r);
	} else if (color && buff[0] == 'g') {
		return JSValueMakeNumber(ctx, color->g);
	} else if (color && buff[0] == 'b') {
		return JSValueMakeNumber(ctx, color->b);
	}
	return JSValueMakeUndefined(ctx);
}

bool jsCCColorSetProperty(JSContextRef ctx, JSObjectRef object, JSStringRef propertyName, JSValueRef value, JSValueRef* exception)
{
	char *buff = (char *)JSStringGetCharactersPtr(propertyName);
	ccColor3B *color = (ccColor3B *)JSObjectGetPrivate(object);
	if (color && buff[0] == 'r') {
		color->r = JSValueToNumber(ctx, value, NULL);
		return true;
	} else if (color && buff[0] == 'g') {
		color->g = JSValueToNumber(ctx, value, NULL);
		return true;
	} else if (color && buff[0] == 'b') {
		color->b = JSValueToNumber(ctx, value, NULL);
		return true;
	}
	return false;
}

#pragma mark - S_TouchDelegate

void __executeJSCallbackForTouchEvent(const char *event, JSObjectRef thisObject, CCSet *pTouches)
{
	JSStringRef jsName = JSStringCreateWithUTF8CString(event);
	JSContextRef ctx = ScriptingCore::getInstance().getGlobalContext();
	if (JSObjectHasProperty(ctx, thisObject, jsName)) {
		size_t len = pTouches->count();
		// FIXME
		// we could have a static array of the max permited touch size created only once
		// and reused
		JSValueRef *arguments = (JSValueRef *)calloc(len, sizeof(JSValueRef));
		int idx = 0;
		CCDirector *director = CCDirector::sharedDirector();
		for (CCSetIterator it = pTouches->begin(); it != pTouches->end(); it++, idx++) {
			CCTouch *touch = (CCTouch *)(*it);
			// we want the points as GL (most of the time)
			CCPoint oPoint = director->convertToGL(touch->locationInView(0));
			CCPoint *point = new CCPoint(oPoint.x, oPoint.y);
			// create new JS object and pass it as the argument
			JSObjectRef jsPoint = JSObjectMake(ctx, __jsCCPoint_class, point);
			arguments[idx] = jsPoint;
		}
		JSObjectRef cb = JSValueToObject(ctx, JSObjectGetProperty(ctx, thisObject, jsName, NULL), NULL);
		JSObjectRef array = JSObjectMakeArray(ctx, len, arguments, NULL);
		JSObjectCallAsFunction(ctx, cb, thisObject, 1, (JSValueRef *)&array, NULL);
		free(arguments);
	}
	JSStringRelease(jsName);
}

void S_TouchDelegate::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	CCNode *node = dynamic_cast<CCNode *>(this);
	if (node) {
		// call ccTouchesBegan on the scripting side if it exists
		JSObjectRef thisObject = (JSObjectRef)node->getUserData();
		if (thisObject) {
			__executeJSCallbackForTouchEvent("touchesBegan", thisObject, pTouches);
		}
	}
}

void S_TouchDelegate::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
	CCNode *node = dynamic_cast<CCNode *>(this);
	if (node) {
		// call ccTouchesBegan on the scripting side if it exists
		JSObjectRef thisObject = (JSObjectRef)node->getUserData();
		if (thisObject) {
			__executeJSCallbackForTouchEvent("touchesMoved", thisObject, pTouches);
		}
	}
}

void S_TouchDelegate::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	CCNode *node = dynamic_cast<CCNode *>(this);
	if (node) {
		// call ccTouchesBegan on the scripting side if it exists
		JSObjectRef thisObject = (JSObjectRef)node->getUserData();
		if (thisObject) {
			__executeJSCallbackForTouchEvent("touchesEnded", thisObject, pTouches);
		}
	}
}

void S_TouchDelegate::ccTouchesCancelled(CCSet *pTouches, CCEvent *pEvent)
{
	CCNode *node = dynamic_cast<CCNode *>(this);
	if (node) {
		// call ccTouchesBegan on the scripting side if it exists
		JSObjectRef thisObject = (JSObjectRef)node->getUserData();
		if (thisObject) {
			__executeJSCallbackForTouchEvent("touchesCancelled", thisObject, pTouches);
		}
	}
}

#pragma mark - ScriptingCore

ScriptingCore::ScriptingCore()
{
	m_globalContext = JSGlobalContextCreate(NULL);
	m_globalObject = JSContextGetGlobalObject(m_globalContext);
	JSObjectSetPrivate(m_globalObject, this);
	
	// static global functions and objects	
	JSStringRef tmp = JSStringCreateWithUTF8CString("require");
	JSObjectSetProperty(m_globalContext, m_globalObject, tmp, JSObjectMakeFunctionWithCallback(m_globalContext, tmp, js_require), kJSPropertyAttributeReadOnly, NULL);
	JSStringRelease(tmp);

	tmp = JSStringCreateWithUTF8CString("exit");
	JSObjectSetProperty(m_globalContext, m_globalObject, tmp, JSObjectMakeFunctionWithCallback(m_globalContext, tmp, js_exit), kJSPropertyAttributeReadOnly, NULL);
	JSStringRelease(tmp);
	
	tmp = JSStringCreateWithUTF8CString("debug");
	m_debugObject = JSObjectMake(m_globalContext, NULL, NULL);
	JSObjectSetProperty(m_globalContext, m_globalObject, tmp, m_debugObject, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum, NULL);
	JSStringRelease(tmp);

	tmp = JSStringCreateWithUTF8CString("log");
	JSObjectSetProperty(m_globalContext, m_debugObject, tmp, JSObjectMakeFunctionWithCallback(m_globalContext, tmp, js_log), kJSPropertyAttributeReadOnly, NULL);
	JSStringRelease(tmp);

	// create cocos2d namespace
	tmp = JSStringCreateWithUTF8CString("cocos2d");
	m_cocos2dNamespace = JSObjectMake(m_globalContext, NULL, NULL);
	JSObjectSetProperty(m_globalContext, m_globalObject, tmp, m_cocos2dNamespace, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontEnum, NULL);
	JSStringRelease(tmp);

	// register binding classes
	js_S_CCDirector_class = registerClass<S_CCDirector>("Director", NULL);
	js_S_CCScheduler_class = registerClass<S_CCScheduler>("Scheduler", NULL);
	js_S_CCSpriteFrameCache_class = registerClass<S_CCSpriteFrameCache>("SpriteFrameCache", NULL);
	js_S_CCNode_class = registerClass<S_CCNode>("Node", NULL);
	js_S_CCScene_class = registerClass<S_CCScene>("Scene", js_S_CCNode_class);
	js_S_CCSprite_class = registerClass<S_CCSprite>("Sprite", js_S_CCNode_class);
	js_S_CCSpriteBatchNode_class = registerClass<S_CCSpriteBatchNode>("SpriteBatchNode", js_S_CCSprite_class);
	js_S_CCMenu_class = registerClass<S_CCMenu>("Menu", js_S_CCNode_class);
	js_S_CCMenuItem_class = registerClass<S_CCMenuItem>("MenuItem", js_S_CCNode_class);
	js_S_CCMenuItemLabel_class = registerClass<S_CCMenuItemLabel>("MenuItemLabel", js_S_CCMenuItem_class);
	js_S_CCMenuItemSprite_class = registerClass<S_CCMenuItemSprite>("MenuItemSprite", js_S_CCMenuItem_class);
	js_S_CCLabelTTF_class = registerClass<S_CCLabelTTF>("LabelTTF", js_S_CCSprite_class);
	js_S_CCParticleSystem_class = registerClass<S_CCParticleSystem>("ParticleSystem", js_S_CCNode_class);
	js_S_CCAnimation_class = registerClass<S_CCAnimation>("Animation", NULL);

	js_S_CCAction_class = registerClass<S_CCAction>("Action", NULL);
	js_S_CCSequence_class = registerClass<S_CCSequence>("Sequence", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCRepeat_class = registerClass<S_CCRepeat>("Repeat", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCRepeatForever_class = registerClass<S_CCRepeatForever>("RepeatForever", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCSpawn_class = registerClass<S_CCSpawn>("Spawn", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCRotateTo_class = registerClass<S_CCRotateTo>("RotateTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCRotateBy_class = registerClass<S_CCRotateBy>("RotateBy", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCMoveTo_class = registerClass<S_CCMoveTo>("MoveTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCMoveBy_class = registerClass<S_CCMoveBy>("MoveBy", js_S_CCMoveTo_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCSkewTo_class = registerClass<S_CCSkewTo>("SkewTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCSkewBy_class = registerClass<S_CCSkewBy>("SkewBy", js_S_CCSkewTo_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCJumpBy_class = registerClass<S_CCJumpBy>("JumpBy", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCJumpTo_class = registerClass<S_CCJumpTo>("JumpTo", js_S_CCJumpBy_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCBezierBy_class = registerClass<S_CCBezierBy>("BezierBy", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCBezierTo_class = registerClass<S_CCBezierTo>("BezierTo", js_S_CCBezierBy_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCScaleTo_class = registerClass<S_CCScaleTo>("ScaleTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCScaleBy_class = registerClass<S_CCScaleBy>("ScaleBy", js_S_CCScaleTo_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCBlink_class = registerClass<S_CCBlink>("Blink", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeIn_class = registerClass<S_CCFadeIn>("FadeIn", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeOut_class = registerClass<S_CCFadeOut>("FadeOut", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeTo_class = registerClass<S_CCFadeTo>("FadeTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTintTo_class = registerClass<S_CCTintTo>("TintTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTintBy_class = registerClass<S_CCTintBy>("TintBy", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCDelayTime_class = registerClass<S_CCDelayTime>("DelayTime", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCReverseTime_class = registerClass<S_CCReverseTime>("ReverseTime", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCAnimate_class = registerClass<S_CCAnimate>("Animate", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCCallFunc_class = registerClass<S_CCCallFunc>("CallFunc", js_S_CCAction_class);
	js_S_CCActionEase_class = registerClass<S_CCActionEase>("ActionEase", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseRateAction_class = registerClass<S_CCEaseRateAction>("EaseRateAction", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseIn_class = registerClass<S_CCEaseIn>("EaseIn", js_S_CCEaseRateAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseOut_class = registerClass<S_CCEaseOut>("EaseOut", js_S_CCEaseRateAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseInOut_class = registerClass<S_CCEaseInOut>("EaseInOut", js_S_CCEaseRateAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseExponentialIn_class = registerClass<S_CCEaseExponentialIn>("EaseExponentialIn", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseExponentialOut_class = registerClass<S_CCEaseExponentialOut>("EaseExponentialOut", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseExponentialInOut_class = registerClass<S_CCEaseExponentialInOut>("EaseExponentialInOut", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseSineIn_class = registerClass<S_CCEaseSineIn>("EaseSineIn", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseSineOut_class = registerClass<S_CCEaseSineOut>("EaseSineOut", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseSineInOut_class = registerClass<S_CCEaseSineInOut>("EaseSineInOut", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseElastic_class = registerClass<S_CCEaseElastic>("EaseElastic", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseElasticIn_class = registerClass<S_CCEaseElasticIn>("EaseElasticIn", js_S_CCEaseElastic_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseElasticOut_class = registerClass<S_CCEaseElasticOut>("EaseElasticOut", js_S_CCEaseElastic_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseElasticInOut_class = registerClass<S_CCEaseElasticInOut>("EaseElasticInOut", js_S_CCEaseElastic_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBounce_class = registerClass<S_CCEaseBounce>("EaseBounce", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBounceIn_class = registerClass<S_CCEaseBounceIn>("EaseBounceIn", js_S_CCEaseBounce_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBounceOut_class = registerClass<S_CCEaseBounceOut>("EaseBounceOut", js_S_CCEaseBounce_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBounceInOut_class = registerClass<S_CCEaseBounceInOut>("EaseBounceInOut", js_S_CCEaseBounce_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBackIn_class = registerClass<S_CCEaseBackIn>("EaseBackIn", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBackOut_class = registerClass<S_CCEaseBackOut>("EaseBackOut", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCEaseBackInOut_class = registerClass<S_CCEaseBackInOut>("EaseBackInOut", js_S_CCActionEase_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCGridAction_class = registerClass<S_CCGridAction>("GridAction", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCGrid3DAction_class = registerClass<S_CCGrid3DAction>("Grid3DAction", js_S_CCGridAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTiledGrid3DAction_class = registerClass<S_CCTiledGrid3DAction>("TiledGrid3DAction", js_S_CCGridAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCAccelDeccelAmplitude_class = registerClass<S_CCAccelDeccelAmplitude>("AccelDeccelAmplitude", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCAccelAmplitude_class = registerClass<S_CCAccelAmplitude>("AccelAmplitude", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCDeccelAmplitude_class = registerClass<S_CCDeccelAmplitude>("DeccelAmplitude", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCWaves3D_class = registerClass<S_CCWaves3D>("Waves3D", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFlipX3D_class = registerClass<S_CCFlipX3D>("FlipX3D", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFlipY3D_class = registerClass<S_CCFlipY3D>("FlipY3D", js_S_CCFlipX3D_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCLens3D_class = registerClass<S_CCLens3D>("Lens3D", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCRipple3D_class = registerClass<S_CCRipple3D>("Ripple3D", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCShaky3D_class = registerClass<S_CCShaky3D>("Shaky3D", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCLiquid_class = registerClass<S_CCLiquid>("Liquid", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCWaves_class = registerClass<S_CCWaves>("Waves", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTwirl_class = registerClass<S_CCTwirl>("Twirl", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCPageTurn3D_class = registerClass<S_CCPageTurn3D>("PageTurn3D", js_S_CCGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCProgressTo_class = registerClass<S_CCProgressTo>("ProgressTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCProgressFromTo_class = registerClass<S_CCProgressFromTo>("ProgressFromTo", js_S_CCAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCShakyTiles3D_class = registerClass<S_CCShakyTiles3D>("ShakyTiles3D", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCShatteredTiles3D_class = registerClass<S_CCShatteredTiles3D>("ShatteredTiles3D", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCShuffleTiles_class = registerClass<S_CCShuffleTiles>("ShuffleTiles", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeOutTRTiles_class = registerClass<S_CCFadeOutTRTiles>("FadeOutTRTiles", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeOutBLTiles_class = registerClass<S_CCFadeOutBLTiles>("FadeOutBLTiles", js_S_CCFadeOutTRTiles_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeOutUpTiles_class = registerClass<S_CCFadeOutUpTiles>("FadeOutUpTiles", js_S_CCFadeOutTRTiles_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCFadeOutDownTiles_class = registerClass<S_CCFadeOutDownTiles>("FadeOutDownTiles", js_S_CCFadeOutUpTiles_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTurnOffTiles_class = registerClass<S_CCTurnOffTiles>("TurnOffTiles", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCWavesTiles3D_class = registerClass<S_CCWavesTiles3D>("WavesTiles3D", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCJumpTiles3D_class = registerClass<S_CCJumpTiles3D>("JumpTiles3D", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCSplitRows_class = registerClass<S_CCSplitRows>("SplitRows", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCSplitCols_class = registerClass<S_CCSplitCols>("SplitCols", js_S_CCTiledGrid3DAction_class /* PLEASE CHECK PARENT RELATION */);

	js_S_CCAudioManager_class = registerClass<S_CCAudioManager>("AudioManager", NULL);
	js_S_CCScheduler_class = registerClass<S_CCScheduler>("Scheduler", NULL);

	js_S_CCTransitionScene_class = registerClass<S_CCTransitionScene>("TransitionScene", js_S_CCScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSceneOriented_class = registerClass<S_CCTransitionSceneOriented>("TransitionSceneOriented", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionRotoZoom_class = registerClass<S_CCTransitionRotoZoom>("TransitionRotoZoom", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionJumpZoom_class = registerClass<S_CCTransitionJumpZoom>("TransitionJumpZoom", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionMoveInL_class = registerClass<S_CCTransitionMoveInL>("TransitionMoveInL", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionMoveInR_class = registerClass<S_CCTransitionMoveInR>("TransitionMoveInR", js_S_CCTransitionMoveInL_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionMoveInT_class = registerClass<S_CCTransitionMoveInT>("TransitionMoveInT", js_S_CCTransitionMoveInL_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionMoveInB_class = registerClass<S_CCTransitionMoveInB>("TransitionMoveInB", js_S_CCTransitionMoveInL_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSlideInL_class = registerClass<S_CCTransitionSlideInL>("TransitionSlideInL", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSlideInR_class = registerClass<S_CCTransitionSlideInR>("TransitionSlideInR", js_S_CCTransitionSlideInL_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSlideInB_class = registerClass<S_CCTransitionSlideInB>("TransitionSlideInB", js_S_CCTransitionSlideInL_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSlideInT_class = registerClass<S_CCTransitionSlideInT>("TransitionSlideInT", js_S_CCTransitionSlideInL_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionShrinkGrow_class = registerClass<S_CCTransitionShrinkGrow>("TransitionShrinkGrow", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFlipX_class = registerClass<S_CCTransitionFlipX>("TransitionFlipX", js_S_CCTransitionSceneOriented_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFlipY_class = registerClass<S_CCTransitionFlipY>("TransitionFlipY", js_S_CCTransitionSceneOriented_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFlipAngular_class = registerClass<S_CCTransitionFlipAngular>("TransitionFlipAngular", js_S_CCTransitionSceneOriented_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionZoomFlipX_class = registerClass<S_CCTransitionZoomFlipX>("TransitionZoomFlipX", js_S_CCTransitionSceneOriented_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionZoomFlipY_class = registerClass<S_CCTransitionZoomFlipY>("TransitionZoomFlipY", js_S_CCTransitionSceneOriented_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionZoomFlipAngular_class = registerClass<S_CCTransitionZoomFlipAngular>("TransitionZoomFlipAngular", js_S_CCTransitionSceneOriented_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFade_class = registerClass<S_CCTransitionFade>("TransitionFade", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionCrossFade_class = registerClass<S_CCTransitionCrossFade>("TransitionCrossFade", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionTurnOffTiles_class = registerClass<S_CCTransitionTurnOffTiles>("TransitionTurnOffTiles", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSplitCols_class = registerClass<S_CCTransitionSplitCols>("TransitionSplitCols", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionSplitRows_class = registerClass<S_CCTransitionSplitRows>("TransitionSplitRows", js_S_CCTransitionSplitCols_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFadeTR_class = registerClass<S_CCTransitionFadeTR>("TransitionFadeTR", js_S_CCTransitionScene_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFadeBL_class = registerClass<S_CCTransitionFadeBL>("TransitionFadeBL", js_S_CCTransitionFadeTR_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFadeUp_class = registerClass<S_CCTransitionFadeUp>("TransitionFadeUp", js_S_CCTransitionFadeTR_class /* PLEASE CHECK PARENT RELATION */);
	js_S_CCTransitionFadeDown_class = registerClass<S_CCTransitionFadeDown>("TransitionFadeDown", js_S_CCTransitionFadeTR_class /* PLEASE CHECK PARENT RELATION */);
	
	// register the CCPoint & CCColor classes
	JSClassDefinition jsPointClassDef = kJSClassDefinitionEmpty;
	
	JSStaticFunction pointFuncs[] = {
		{"distance", jsCCPointDistance, kJSPropertyAttributeReadOnly | kJSPropertyAttributeDontDelete},
		{0, 0, 0}
	};
	
	jsPointClassDef.version = 0;
	jsPointClassDef.attributes = kJSClassAttributeNone;
	jsPointClassDef.className = "Point";
	jsPointClassDef.callAsConstructor = jsCCPointConstructor;
	jsPointClassDef.finalize = jsCCPointFinalize;
	jsPointClassDef.hasProperty = jsCCPointHasProperty;
	jsPointClassDef.getProperty = jsCCPointGetProperty;
	jsPointClassDef.setProperty = jsCCPointSetProperty;
	jsPointClassDef.staticFunctions = pointFuncs;

	tmp = JSStringCreateWithUTF8CString("Point");
	__jsCCPoint_class = JSClassCreate(&jsPointClassDef);
	JSObjectRef ptObj = JSObjectMake(m_globalContext, __jsCCPoint_class, NULL);
	JSObjectSetProperty(m_globalContext, m_cocos2dNamespace, tmp, ptObj, kJSPropertyAttributeNone, NULL);
	JSStringRelease(tmp);
	
	JSClassDefinition jsColorClassDef = kJSClassDefinitionEmpty;
	jsPointClassDef.version = 0;
	jsPointClassDef.attributes = kJSClassAttributeNone;
	jsPointClassDef.className = "Color";
	jsPointClassDef.callAsConstructor = jsCCColorConstructor;
	jsPointClassDef.finalize = jsCCColorFinalize;
	jsPointClassDef.hasProperty = jsCCColorHasProperty;
	jsPointClassDef.getProperty = jsCCColorGetProperty;
	jsPointClassDef.setProperty = jsCCColorSetProperty;

	tmp = JSStringCreateWithUTF8CString("Color");
	__jsCCColor_class = JSClassCreate(&jsColorClassDef);
	JSObjectRef clObj = JSObjectMake(m_globalContext, __jsCCColor_class, NULL);
	JSObjectSetProperty(m_globalContext, m_cocos2dNamespace, tmp, clObj, kJSPropertyAttributeNone, NULL);
	JSStringRelease(tmp);

	// init debugger
	m_debugController = new JSCDebuggerController(m_globalContext, this);
}

ScriptingCore::~ScriptingCore()
{
	JSClassRelease(js_S_CCDirector_class);
	JSClassRelease(js_S_CCScheduler_class);
	JSClassRelease(js_S_CCSpriteFrameCache_class);
	JSClassRelease(js_S_CCNode_class);
	JSClassRelease(js_S_CCScene_class);
	JSClassRelease(js_S_CCSprite_class);
	JSClassRelease(js_S_CCSpriteBatchNode_class);
	JSClassRelease(js_S_CCMenu_class);
	JSClassRelease(js_S_CCMenuItem_class);
	JSClassRelease(js_S_CCMenuItemLabel_class);
	JSClassRelease(js_S_CCMenuItemSprite_class);
	JSClassRelease(js_S_CCLabelTTF_class);
	JSClassRelease(js_S_CCAction_class);
	JSClassRelease(js_S_CCMoveBy_class);
	JSClassRelease(js_S_CCSequence_class);
	JSClassRelease(js_S_CCCallFunc_class);
	JSClassRelease(js_S_CCAudioManager_class);
	JSClassRelease(js_S_CCParticleSystem_class);
		
	delete m_debugController;
	JSGlobalContextRelease(m_globalContext);
}

void ScriptingCore::runScript(const char *fpath)
{
	struct timeval st, ed;
	
	gettimeofday(&st, NULL);
	
	const char *realPath = CCFileUtils::fullPathFromRelativePath(fpath);
	NSString *nsPath = [NSString stringWithUTF8String:realPath];
	NSUInteger hash = [nsPath hash];
	
	std::map<int,bool>::iterator it = m_loadedFiles.find(hash);
	if (it != m_loadedFiles.end()) {
		return;
	}
	
	m_loadedFiles[hash] = true;
	NSString *data = [NSString stringWithContentsOfFile:nsPath encoding:NSUTF8StringEncoding error:NULL];
	
	JSStringRef sourceURL = JSStringCreateWithUTF8CString(fpath);
	JSStringRef script = JSStringCreateWithUTF8CString([data UTF8String]);
	JSValueRef exception = NULL;
	
	char *buff = (char *)calloc(1, 512);
	bool syntaxOk = JSCheckScriptSyntax(m_globalContext, script, sourceURL, 1, &exception);
	if (!syntaxOk) {
		if (exception) {
			formatException(exception, buff);
			fprintf(stdout, "%s\n", buff);
		} else {
			fprintf(stdout, "unknown syntax error parsing file %s\n", fpath);
		}
	} else if (syntaxOk) {
		JSEvaluateScript(m_globalContext, script, NULL, sourceURL, 1, &exception);
		if (exception) {
			formatException(exception, buff);
			fprintf(stdout, "%s\n", buff);
		}
	}
	fflush(stdout);
	free(buff);
	
	JSStringRelease(sourceURL);
	JSStringRelease(script);
	
	gettimeofday(&ed, NULL);
	float total = (ed.tv_sec - st.tv_sec) + (ed.tv_usec - st.tv_usec) / 1000000.0f;
	fprintf(stdout, "total time for parsing %s\t%f\n", fpath, total);
}

void ScriptingCore::formatException(JSValueRef exception, char *buff)
{
	JSStringRef resultStringJS = JSValueToStringCopy(m_globalContext, exception, NULL);
	NSString *b = (NSString*)JSStringCopyCFString(kCFAllocatorDefault, resultStringJS);
	JSStringRelease(resultStringJS);
	[b autorelease];
	
	if (JSValueGetType(m_globalContext, exception) != kJSTypeObject)
	{
		const char *tmpstr = [b UTF8String];
		memcpy(buff, tmpstr, strlen(tmpstr));
	}
	
	// Iterate over all properties of the exception
	JSObjectRef jsObject = JSValueToObject(m_globalContext, exception, NULL);
	JSPropertyNameArrayRef jsNames = JSObjectCopyPropertyNames(m_globalContext, jsObject);
	int i, nameCount = JSPropertyNameArrayGetCount(jsNames);
	NSString *line = NULL, *sourceURL = NULL;
	for (i=0; i<nameCount; i++)
	{
		JSStringRef jsName = JSPropertyNameArrayGetNameAtIndex(jsNames, i);
		NSString *name = (NSString *)JSStringCopyCFString(kCFAllocatorDefault, jsName);
		JSStringRelease(jsName);
		[name autorelease];
		
		JSValueRef	jsValueRef = JSObjectGetProperty(m_globalContext, jsObject, jsName, NULL);
		JSStringRef	valueJS = JSValueToStringCopy(m_globalContext, jsValueRef, NULL);
		NSString* value = (NSString*)JSStringCopyCFString(kCFAllocatorDefault, valueJS);
		JSStringRelease(valueJS);
		[value autorelease];
		
		if ([name isEqualToString:@"line"])			line = value;
		if ([name isEqualToString:@"sourceURL"])	sourceURL = value;
	}
	
	NSString *result = [NSString stringWithFormat:@"%@ on line %@ of %@", b, line, sourceURL];
	const char *tmpstr = [result UTF8String];
	memcpy(buff, tmpstr, strlen(tmpstr));
}

void ScriptingCore::resetLoadedFiles()
{
	m_loadedFiles.clear();
}

template <class T>
JSClassRef ScriptingCore::registerClass(const char *name, JSClassRef parentClass)
{
	return registerClass<T>(name, parentClass, m_cocos2dNamespace);
}

template <class T>
JSClassRef ScriptingCore::registerClass(const char *name, JSClassRef parentClass, JSObjectRef namespaceObject)
{
	JSClassDefinition js_newClass = kJSClassDefinitionEmpty;
	js_newClass.version = 0;
	js_newClass.attributes = kJSClassAttributeNone;
	js_newClass.className = name;
	js_newClass.parentClass = parentClass;
	js_newClass.callAsConstructor = T::jsConstructor;
	// generic destructor only for parent classes, otherwise the destructor
	// will be called twice
	js_newClass.finalize = (parentClass ? NULL : sc_genericCppFinalize);
	js_newClass.hasProperty = T::jsHasProperty;
	js_newClass.getProperty = T::jsGetProperty;
	js_newClass.staticFunctions = T::jsStaticFunctions();

	JSStringRef tmp = JSStringCreateWithUTF8CString(name);
	JSClassRef klass = JSClassCreate(&js_newClass);
	JSObjectRef obj = JSObjectMake(m_globalContext, klass, NULL);
	JSObjectSetProperty(m_globalContext, namespaceObject, tmp, obj, kJSPropertyAttributeNone, NULL);
	JSStringRelease(tmp);

	return klass;
}

void ScriptingCore::didReachException(const char *scriptURL, JSValueRef exception, int lineNumber)
{
	char *buff = (char *)malloc(256);
	JSStringRef jsStr = JSValueToStringCopy(m_globalContext, exception, NULL);
	int len = JSStringGetLength(jsStr);
	JSStringGetUTF8CString(jsStr, buff, len+1);
	
	CCLog("%s - at %s:%d", buff, scriptURL, lineNumber);
	fflush(stdout);
	
	JSStringRelease(jsStr);
	free(buff);
	
	CCDirector::sharedDirector()->pause();
}

void ScriptingCore::shouldPauseJS()
{
	CCLog("Should pause JS");
}

void ScriptingCore::didPause(DebuggerState *state)
{
}
