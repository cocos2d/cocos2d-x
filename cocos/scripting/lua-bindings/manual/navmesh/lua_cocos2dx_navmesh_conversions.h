/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
#ifndef __COCOS_SCRIPTING_LUA_BINDING_MANUAL_NAVMESH_LUA_NAVMESH_CONVERSIONS_H__
#define __COCOS_SCRIPTING_LUA_BINDING_MANUAL_NAVMESH_LUA_NAVMESH_CONVERSIONS_H__

#if CC_USE_NAVMESH

extern "C" {
#include "lua.h"
#include "tolua++.h"
}

#include "scripting/lua-bindings/manual/tolua_fix.h"

namespace cocos2d
{
    struct NavMeshAgentParam;
    struct OffMeshLinkData;
}

extern bool luaval_to_navmeshagentparam(lua_State* L, int lo, cocos2d::NavMeshAgentParam* outValue , const char* funcName = "");
extern bool luaval_to_offmeshlinkdata(lua_State* L, int lo, cocos2d::OffMeshLinkData* outValue , const char* funcName = "");

extern void navmeshagentparam_to_luaval(lua_State* L,const cocos2d::NavMeshAgentParam& inValue);
extern void offmeshlinkdata_to_luaval(lua_State* L,const cocos2d::OffMeshLinkData& inValue);


#endif // #if CC_USE_NAVMESH
#endif // __COCOS_SCRIPTING_LUA_BINDING_MANUAL_NAVMESH_LUA_NAVMESH_CONVERSIONS_H__
