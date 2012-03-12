//
//  S_CCAnimation.h
//  cocos2d-x
//
//  Created By XXX on 02/22/2012
//  Copyright (c) 2011 XXX. All rights reserved.
//

#ifndef cocos2dx_javascript_S_CCAnimation_h
#define cocos2dx_javascript_S_CCAnimation_h

#include "cocos2d.h"
#include "ScriptingCore.h"

class S_CCAnimation : public cocos2d::CCAnimation
{
	JSObjectRef jsObject;
public:

	S_CCAnimation() : CCAnimation() {};

	SCRIPTABLE_BOILERPLATE
	JS_STATIC_FUNC_DEF(jsAddFrame);
};

#endif

