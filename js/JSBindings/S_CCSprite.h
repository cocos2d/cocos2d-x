//
//  ZSprite.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_ZSprite_h
#define TestCocos2dX_ZSprite_h

#include "cocos2d.h"
#include "ScriptingCore.h"

class S_CCSprite : public cocos2d::CCSprite, public S_TouchDelegate
{

public:
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
};

class S_CCSpriteBatchNode : public cocos2d::CCSpriteBatchNode, public S_TouchDelegate
{
public:
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
};

#endif
