//
//  ZDirector.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_ZNode_h
#define TestCocos2dX_ZNode_h

#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class S_CCNode : public cocos2d::CCNode, public S_TouchDelegate
{	
public:	
	S_CCNode() : CCNode () {}
	
	JS_STATIC_FUNC_DEF(jsAddChild);
	JS_STATIC_FUNC_DEF(jsRemoveChild);
	JS_STATIC_FUNC_DEF(jsRemoveChildByTag);
	JS_STATIC_FUNC_DEF(jsRemoveAllChildrenWithCleanup);
	JS_STATIC_FUNC_DEF(jsSetPosition);
	JS_STATIC_FUNC_DEF(jsGetPosition);
	JS_STATIC_FUNC_DEF(jsSetRotation);
	JS_STATIC_FUNC_DEF(jsGetRotation);
	JS_STATIC_FUNC_DEF(jsSetAnchorPoint);
	JS_STATIC_FUNC_DEF(jsGetAnchorPoint);
	JS_STATIC_FUNC_DEF(jsSetIsVisible);
	JS_STATIC_FUNC_DEF(jsGetIsVisible);
	JS_STATIC_FUNC_DEF(jsSetScale);
	JS_STATIC_FUNC_DEF(jsGetScale);
	JS_STATIC_FUNC_DEF(jsSetScaleX);
	JS_STATIC_FUNC_DEF(jsGetScaleX);
	JS_STATIC_FUNC_DEF(jsSetScaleY);
	JS_STATIC_FUNC_DEF(jsGetScaleY);
	JS_STATIC_FUNC_DEF(jsSetSkewX);
	JS_STATIC_FUNC_DEF(jsGetSkewX);
	JS_STATIC_FUNC_DEF(jsSetSkewY);
	JS_STATIC_FUNC_DEF(jsGetSkewY);
	JS_STATIC_FUNC_DEF(jsSetTag);
	JS_STATIC_FUNC_DEF(jsGetTag);
	JS_STATIC_FUNC_DEF(jsGetChildByTag);
	JS_STATIC_FUNC_DEF(jsRunAction);
	
	// RGBAProtocol
	JS_STATIC_FUNC_DEF(jsSetColor);
	JS_STATIC_FUNC_DEF(jsGetColor);
	JS_STATIC_FUNC_DEF(jsSetOpacity);
	JS_STATIC_FUNC_DEF(jsGetOpacity);
	
	// touch handler
	JS_STATIC_FUNC_DEF(jsRegisterAsTouchHandler);
	JS_STATIC_FUNC_DEF(jsUnregisterAsTouchHandler);
	
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
};

class S_CCScene : public CCScene, public S_TouchDelegate
{
public:
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
	
	S_CCScene() : CCScene () {}
};

#endif
