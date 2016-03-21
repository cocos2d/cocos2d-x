/****************************************************************************
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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
#include "scripting/lua-bindings/manual/cocostudio/lua_cocos2dx_csloader_manual.hpp"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimeline.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "editor-support/cocostudio/ActionTimeline/CCActionTimelineNode.h"

int lua_cocos2dx_csloader_CSLoader_createTimeline(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "cc.CSLoader:createTimeline");
        if(!ok)
            return 0;
        cocostudio::timeline::ActionTimeline* ret = cocos2d::CSLoader::createTimeline(arg0);
        object_to_luaval<cocostudio::timeline::ActionTimeline>(tolua_S, "ccs.ActionTimeline",(cocostudio::timeline::ActionTimeline*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.CSLoader:createTimeline",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_CSLoader_createTimeline'.",&tolua_err);
#endif
    return 0;
}

int lua_cocos2dx_csloader_CSLoader_createNode(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.CSLoader",0,&tolua_err)) goto tolua_lerror;
#endif
    
    argc = lua_gettop(tolua_S)-1;
    
    do
    {
        if (argc == 2)
        {
            std::string filename;
            ok &= luaval_to_std_string(tolua_S, 2,&filename, "cc.CSLoader:createNode");
            if (!ok) { break; }
            
#if COCOS2D_DEBUG >= 1
            if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err) )
            {
                goto tolua_lerror;
            }
#endif
            
            LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,3,0));
            auto callback = [handler, tolua_S](cocos2d::Ref* ref){
                if (nullptr == ref)
                    return;
                toluafix_pushusertype_ccobject(tolua_S, ref->_ID, &(ref->_luaID), (void*)ref,"cc.Ref");
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 1);
            };
            
            cocos2d::Node* ret = cocos2d::CSLoader::createNode(filename, callback);
            ScriptHandlerMgr::getInstance()->addCustomHandler((void*)ret, handler);
            object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do
    {
        if (argc == 1)
        {
            std::string filename;
            ok &= luaval_to_std_string(tolua_S, 2,&filename, "cc.CSLoader:createNode");
            if (!ok) { break; }
            cocos2d::Node* ret = cocos2d::CSLoader::createNode(filename);
            object_to_luaval<cocos2d::Node>(tolua_S, "cc.Node",(cocos2d::Node*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "cc.CSLoader:createNode",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_csloader_CSLoader_createNode'.",&tolua_err);
#endif
    return 0;
}

int register_all_cocos2dx_csloader_manual(lua_State* L)
{
    lua_pushstring(L, "cc.CSLoader");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "createTimeline", lua_cocos2dx_csloader_CSLoader_createTimeline);
        tolua_function(L, "createNode", lua_cocos2dx_csloader_CSLoader_createNode);
    }
    lua_pop(L, 1);
    
    return 0;
}

