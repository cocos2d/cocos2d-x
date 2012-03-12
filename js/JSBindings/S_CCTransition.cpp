//
//  S_CCTransition.cpp
//  cocos2d-x
//
//  Created By XXX on 02/03/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#include <JavaScriptCore/JavaScriptCore.h>
#include "S_CCTransition.h"

using namespace cocos2d;

#pragma mark - CCTransitionScene

JSClassRef js_S_CCTransitionScene_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionScene)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionScene, CCTransitionScene)

JSStaticFunction* S_CCTransitionScene::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionScene::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionScene::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSceneOriented

JSClassRef js_S_CCTransitionSceneOriented_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSceneOriented)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSceneOriented, CCTransitionSceneOriented)

JSStaticFunction* S_CCTransitionSceneOriented::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSceneOriented::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation orientation = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionSceneOriented::initWithDuration(t, scene, orientation)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionRotoZoom

JSClassRef js_S_CCTransitionRotoZoom_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionRotoZoom)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionRotoZoom, CCTransitionRotoZoom)

JSStaticFunction* S_CCTransitionRotoZoom::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionRotoZoom::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionRotoZoom::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionJumpZoom

JSClassRef js_S_CCTransitionJumpZoom_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionJumpZoom)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionJumpZoom, CCTransitionJumpZoom)

JSStaticFunction* S_CCTransitionJumpZoom::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionJumpZoom::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionJumpZoom::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionMoveInL

JSClassRef js_S_CCTransitionMoveInL_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionMoveInL)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionMoveInL, CCTransitionMoveInL)

JSStaticFunction* S_CCTransitionMoveInL::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionMoveInL::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionMoveInL::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionMoveInR

JSClassRef js_S_CCTransitionMoveInR_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionMoveInR)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionMoveInR, CCTransitionMoveInR)

JSStaticFunction* S_CCTransitionMoveInR::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionMoveInR::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionMoveInR::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionMoveInT

JSClassRef js_S_CCTransitionMoveInT_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionMoveInT)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionMoveInT, CCTransitionMoveInT)

JSStaticFunction* S_CCTransitionMoveInT::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionMoveInT::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionMoveInT::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionMoveInB

JSClassRef js_S_CCTransitionMoveInB_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionMoveInB)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionMoveInB, CCTransitionMoveInB)

JSStaticFunction* S_CCTransitionMoveInB::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionMoveInB::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionMoveInB::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSlideInL

JSClassRef js_S_CCTransitionSlideInL_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSlideInL)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSlideInL, CCTransitionSlideInL)

JSStaticFunction* S_CCTransitionSlideInL::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSlideInL::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionSlideInL::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSlideInR

JSClassRef js_S_CCTransitionSlideInR_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSlideInR)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSlideInR, CCTransitionSlideInR)

JSStaticFunction* S_CCTransitionSlideInR::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSlideInR::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionSlideInR::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSlideInB

JSClassRef js_S_CCTransitionSlideInB_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSlideInB)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSlideInB, CCTransitionSlideInB)

JSStaticFunction* S_CCTransitionSlideInB::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSlideInB::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionSlideInB::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSlideInT

JSClassRef js_S_CCTransitionSlideInT_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSlideInT)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSlideInT, CCTransitionSlideInT)

JSStaticFunction* S_CCTransitionSlideInT::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSlideInT::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionSlideInT::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionShrinkGrow

JSClassRef js_S_CCTransitionShrinkGrow_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionShrinkGrow)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionShrinkGrow, CCTransitionShrinkGrow)

JSStaticFunction* S_CCTransitionShrinkGrow::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionShrinkGrow::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionShrinkGrow::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFlipX

JSClassRef js_S_CCTransitionFlipX_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFlipX)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFlipX, CCTransitionFlipX)

JSStaticFunction* S_CCTransitionFlipX::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFlipX::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation o = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionFlipX::initWithDuration(t, scene, o)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFlipY

JSClassRef js_S_CCTransitionFlipY_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFlipY)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFlipY, CCTransitionFlipY)

JSStaticFunction* S_CCTransitionFlipY::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFlipY::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation o = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionFlipY::initWithDuration(t, scene, o)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFlipAngular

JSClassRef js_S_CCTransitionFlipAngular_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFlipAngular)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFlipAngular, CCTransitionFlipAngular)

JSStaticFunction* S_CCTransitionFlipAngular::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFlipAngular::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation o = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionFlipAngular::initWithDuration(t, scene, o)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionZoomFlipX

JSClassRef js_S_CCTransitionZoomFlipX_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionZoomFlipX)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionZoomFlipX, CCTransitionZoomFlipX)

JSStaticFunction* S_CCTransitionZoomFlipX::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionZoomFlipX::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation o = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionZoomFlipX::initWithDuration(t, scene, o)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionZoomFlipY

JSClassRef js_S_CCTransitionZoomFlipY_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionZoomFlipY)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionZoomFlipY, CCTransitionZoomFlipY)

JSStaticFunction* S_CCTransitionZoomFlipY::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionZoomFlipY::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation o = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionZoomFlipY::initWithDuration(t, scene, o)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionZoomFlipAngular

JSClassRef js_S_CCTransitionZoomFlipAngular_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionZoomFlipAngular)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionZoomFlipAngular, CCTransitionZoomFlipAngular)

JSStaticFunction* S_CCTransitionZoomFlipAngular::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionZoomFlipAngular::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 3) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		tOrientation o = (tOrientation)JSValueToNumber(ctx, arguments[2], NULL);
		if (scene && CCTransitionZoomFlipAngular::initWithDuration(t, scene, o)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFade

JSClassRef js_S_CCTransitionFade_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFade)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFade, CCTransitionFade)

JSStaticFunction* S_CCTransitionFade::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFade::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionFade::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionCrossFade

JSClassRef js_S_CCTransitionCrossFade_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionCrossFade)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionCrossFade, CCTransitionCrossFade)

JSStaticFunction* S_CCTransitionCrossFade::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionCrossFade::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionCrossFade::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionTurnOffTiles

JSClassRef js_S_CCTransitionTurnOffTiles_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionTurnOffTiles)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionTurnOffTiles, CCTransitionTurnOffTiles)

JSStaticFunction* S_CCTransitionTurnOffTiles::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionTurnOffTiles::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionTurnOffTiles::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSplitCols

JSClassRef js_S_CCTransitionSplitCols_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSplitCols)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSplitCols, CCTransitionSplitCols)

JSStaticFunction* S_CCTransitionSplitCols::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSplitCols::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionSplitCols::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionSplitRows

JSClassRef js_S_CCTransitionSplitRows_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionSplitRows)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionSplitRows, CCTransitionSplitRows)

JSStaticFunction* S_CCTransitionSplitRows::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionSplitRows::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionSplitRows::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFadeTR

JSClassRef js_S_CCTransitionFadeTR_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFadeTR)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFadeTR, CCTransitionFadeTR)

JSStaticFunction* S_CCTransitionFadeTR::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFadeTR::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionFadeTR::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFadeBL

JSClassRef js_S_CCTransitionFadeBL_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFadeBL)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFadeBL, CCTransitionFadeBL)

JSStaticFunction* S_CCTransitionFadeBL::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFadeBL::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionFadeBL::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFadeUp

JSClassRef js_S_CCTransitionFadeUp_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFadeUp)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFadeUp, CCTransitionFadeUp)

JSStaticFunction* S_CCTransitionFadeUp::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFadeUp::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionFadeUp::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}

#pragma mark - CCTransitionFadeDown

JSClassRef js_S_CCTransitionFadeDown_class;

SCRIPTABLE_BOILERPLATE_IMP(S_CCTransitionFadeDown)
SCRIPTABLE_BOILERPLATE_IMP_CCNODE(S_CCTransitionFadeDown, CCTransitionFadeDown)

JSStaticFunction* S_CCTransitionFadeDown::jsStaticFunctions()
{
	return NULL;
}

bool S_CCTransitionFadeDown::initWithContext(JSContextRef ctx, JSObjectRef obj, size_t argumentCount, const JSValueRef arguments[])
{
	bool result = false;
	if (argumentCount == 2) {
		ccTime t = JSValueToNumber(ctx, arguments[0], NULL);
		CCScene *scene = (CCScene *)JSObjectGetPrivate((JSObjectRef)arguments[1]);
		if (scene && CCTransitionFadeDown::initWithDuration(t, scene)) {
			result = true;
		}
	}
	if (result) {
		setUserData(obj);
	}
	return result;
}
