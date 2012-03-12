//
//  ZSpriteFrameCache.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/12/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_ZSpriteFrameCache_h
#define TestCocos2dX_ZSpriteFrameCache_h

#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class S_CCSpriteFrameCache
{	
	
public:
	SCRIPTABLE_BOILERPLATE
	
	JS_STATIC_FUNC_DEF(jsAddSpriteFramesWithFile);
};

#endif
