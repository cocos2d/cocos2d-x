#ifndef LUACOCOS2D_H
#define LUACOCOS2D_H
#include "cocos2d.h"
#include "tolua++.h"

#include <stdio.h>
#include "CCKeypadDispatcher.h"
#include "CCRibbon.h"
#include "CCParallaxNode.h"
#include "CCAutoreleasePool.h"
#include "CCIMEDispatcher.h"
#include "CCMutableArray.h"
//#define  TOLUA_RELEASE
#if  defined(_WIN32) && defined(_DEBUG)
#pragma warning (disable:4800)
#endif
int  tolua_Cocos2d_open(lua_State* tolua_S);

#endif//LUACOCOS2D_H