//
//  S_CCMenu.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/20/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_S_CCMenu_h
#define TestCocos2dX_S_CCMenu_h

#include <JavaScriptCore/JavaScriptCore.h>
#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class S_CCMenu : CCMenu
{
public:
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
};

class S_CCMenuItem : CCMenuItem
{
	JSObjectRef m_Callback;
public:
	S_CCMenuItem() : CCMenuItem(), m_Callback(NULL) {};
	
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE

	JS_STATIC_FUNC_DEF(jsGetIsEnabled);
	JS_STATIC_FUNC_DEF(jsSetIsEnabled);

	virtual void menuHandler(CCObject* pSender);
};

class S_CCMenuItemLabel : CCMenuItemLabel
{
	JSObjectRef m_Callback;
public:
	S_CCMenuItemLabel() : CCMenuItemLabel(), m_Callback(NULL) {};
	
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
	
	virtual void menuHandler(CCObject* pSender);
};

class S_CCMenuItemSprite : CCMenuItemSprite
{
	JSObjectRef m_Callback;
public:
	S_CCMenuItemSprite() : CCMenuItemSprite(), m_Callback(NULL) {};
	
	SCRIPTABLE_BOILERPLATE
	SCRIPTABLE_BOILERPLATE_CCNODE
	
	virtual void menuHandler(CCObject* pSender);
};

#endif
