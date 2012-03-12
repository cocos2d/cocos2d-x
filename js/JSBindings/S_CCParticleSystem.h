//
//  S_CCParticleSystem.h
//  cocos2d-x
//
//  Created By XXX on 02/15/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#ifndef cocos2dx_javascript_S_CCParticleSystem_h
#define cocos2dx_javascript_S_CCParticleSystem_h

#include "cocos2d.h"
#include "ScriptingCore.h"

class S_CCParticleSystem : public cocos2d::ARCH_OPTIMAL_PARTICLE_SYSTEM
{
public:

	S_CCParticleSystem() : ARCH_OPTIMAL_PARTICLE_SYSTEM() {};

	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
	
	JS_STATIC_FUNC_DEF(jsSetGravity);
	JS_STATIC_FUNC_DEF(jsGetSpeed);
	JS_STATIC_FUNC_DEF(jsSetSpeed);
	JS_STATIC_FUNC_DEF(jsGetSpeedVar);
	JS_STATIC_FUNC_DEF(jsSetSpeedVar);
	JS_STATIC_FUNC_DEF(jsGetTangentialAccel);
	JS_STATIC_FUNC_DEF(jsSetTangentialAccel);
	JS_STATIC_FUNC_DEF(jsGetTangentialAccelVar);
	JS_STATIC_FUNC_DEF(jsSetTangentialAccelVar);
	JS_STATIC_FUNC_DEF(jsGetRadialAccel);
	JS_STATIC_FUNC_DEF(jsSetRadialAccel);
	JS_STATIC_FUNC_DEF(jsGetRadialAccelVar);
	JS_STATIC_FUNC_DEF(jsSetRadialAccelVar);
	JS_STATIC_FUNC_DEF(jsGetStartRadius);
	JS_STATIC_FUNC_DEF(jsSetStartRadius);
	JS_STATIC_FUNC_DEF(jsGetStartRadiusVar);
	JS_STATIC_FUNC_DEF(jsSetStartRadiusVar);
	JS_STATIC_FUNC_DEF(jsGetEndRadius);
	JS_STATIC_FUNC_DEF(jsSetEndRadius);
	JS_STATIC_FUNC_DEF(jsGetEndRadiusVar);
	JS_STATIC_FUNC_DEF(jsSetEndRadiusVar);
	JS_STATIC_FUNC_DEF(jsGetRotatePerSecond);
	JS_STATIC_FUNC_DEF(jsSetRotatePerSecond);
	JS_STATIC_FUNC_DEF(jsGetRotatePerSecondVar);
	JS_STATIC_FUNC_DEF(jsSetRotatePerSecondVar);
	JS_STATIC_FUNC_DEF(jsAddParticle);
	JS_STATIC_FUNC_DEF(jsStopSystem);
	JS_STATIC_FUNC_DEF(jsResetSystem);
	JS_STATIC_FUNC_DEF(jsIsFull);
};

#endif

