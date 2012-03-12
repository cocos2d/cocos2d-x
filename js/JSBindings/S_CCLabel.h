//
//  S_CCLabel.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 1/13/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_S_CCLabel_h
#define TestCocos2dX_S_CCLabel_h

#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class S_CCLabelTTF : public CCLabelTTF, public S_TouchDelegate
{
public:
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
	
	JS_STATIC_FUNC_DEF(jsSetString);
	JS_STATIC_FUNC_DEF(jsGetString);
};

#endif
