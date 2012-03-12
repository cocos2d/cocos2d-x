//
//  S_Audio.h
//  TestCocos2dX
//
//  Created by Rolando Abarca on 1/31/12.
//  Copyright (c) 2012 Zynga Inc. All rights reserved.
//

#ifndef TestCocos2dX_S_Audio_h
#define TestCocos2dX_S_Audio_h

#include "cocos2d.h"
#include "ScriptingCore.h"

class S_CCAudioManager
{
public:
	SCRIPTABLE_BOILERPLATE
	
	JS_STATIC_FUNC_DEF(jsPreloadBackgroundMusic);
	JS_STATIC_FUNC_DEF(jsPlayBackgroundMusic);
	JS_STATIC_FUNC_DEF(jsStopBackgroundMusic);
	JS_STATIC_FUNC_DEF(jsPauseBackgroundMusic);
	JS_STATIC_FUNC_DEF(jsSetBackgroundMusicVolume);
	JS_STATIC_FUNC_DEF(jsGetBackgroundMusicVolume);
	JS_STATIC_FUNC_DEF(jsPlayEffect);
	JS_STATIC_FUNC_DEF(jsStopEffect);
	JS_STATIC_FUNC_DEF(jsStopAllEffects);
};

#endif
