//
//  ZScheduler.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 12/6/11.
//  Copyright (c) 2011 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_ZScheduler_h
#define TestCocos2dX_ZScheduler_h

#include "cocos2d.h"
#include "ScriptingCore.h"

using namespace cocos2d;

class JSScheduleCallback : public CCObject
{

public:
	virtual ~JSScheduleCallback();
	void timerCallBack(ccTime dt);
	JSValueRef   callback;
	JSValueRef   thisObject;
	int id;
};

struct cmp_objects
{
	bool operator()(const int &a, const int &b)
	{
		return (unsigned long)a < (unsigned long)b;
	}
};

typedef std::map<int, JSScheduleCallback *> callback_map;

class S_CCScheduler
{	
	
public:
	SCRIPTABLE_BOILERPLATE

	JS_STATIC_FUNC_DEF(jsSchedule);
	JS_STATIC_FUNC_DEF(jsUnschedule);
};

#endif
