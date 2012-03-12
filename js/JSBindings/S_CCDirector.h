//
//  ZDirector.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_ZDirector_h
#define TestCocos2dX_ZDirector_h

#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class S_CCDirector
{	
	
public:
	SCRIPTABLE_BOILERPLATE
	
	JS_STATIC_FUNC_DEF(jsRunWithScene);
	JS_STATIC_FUNC_DEF(jsReplaceScene);
	JS_STATIC_FUNC_DEF(jsPushScene);
	JS_STATIC_FUNC_DEF(jsPopScene);
};

#endif
