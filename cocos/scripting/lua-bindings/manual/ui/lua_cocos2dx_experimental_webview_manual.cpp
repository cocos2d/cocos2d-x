/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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

#include "scripting/lua-bindings/manual/ui/lua_cocos2dx_experimental_video_manual.hpp"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "ui/UIWebView.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"



static int lua_cocos2dx_experimental_WebView_setOnShouldStartLoading(lua_State* L)
{
    
    int argc = 0;
    cocos2d::experimental::ui::WebView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::experimental::ui::WebView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_experimental_WebView_setOnShouldStartLoading'\n", nullptr);
		return 0;
	}
#endif

    argc = lua_gettop(L) - 1;

    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        std::function<bool(experimental::ui::WebView *sender, const std::string &url)> callback = [L,handler](experimental::ui::WebView *sender, const std::string &url)->bool{
            toluafix_pushusertype_ccobject(L, sender->_ID, &(sender->_luaID), (void*)sender,"ccexp.WebView");
            tolua_pushcppstring(L, url);
            return LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        self->setOnShouldStartLoading(callback);
        
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.WebView:setOnShouldStartLoading",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_cocos2dx_experimental_WebView_setOnShouldStartLoading'.", &tolua_err);
#endif
    return 0;
}

static int lua_cocos2dx_experimental_WebView_setOnDidFinishLoading(lua_State* L)
{
    
    int argc = 0;
    cocos2d::experimental::ui::WebView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::experimental::ui::WebView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_experimental_WebView_setOnDidFinishLoading'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        std::function<void(experimental::ui::WebView *sender, const std::string &url)> callback = [L,handler](experimental::ui::WebView *sender, const std::string &url){
            toluafix_pushusertype_ccobject(L, sender->_ID, &(sender->_luaID), (void*)sender,"ccexp.WebView");
            tolua_pushcppstring(L, url);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        self->setOnDidFinishLoading(callback);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.WebView:setOnDidFinishLoading",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_cocos2dx_experimental_WebView_setOnDidFinishLoading'.", &tolua_err);
#endif
    return 0;
}

static int lua_cocos2dx_experimental_WebView_setOnDidFailLoading(lua_State* L)
{
    
    int argc = 0;
    cocos2d::experimental::ui::WebView* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccexp.WebView",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::experimental::ui::WebView*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
    if (nullptr == self) {
        tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_experimental_WebView_setOnDidFailLoading'\n", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(L) - 1;
    
    if (argc == 1)
    {
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(L,2,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        
        LUA_FUNCTION handler = (  toluafix_ref_function(L,2,0));
        std::function<void(experimental::ui::WebView *sender, const std::string &url)> callback = [L,handler](experimental::ui::WebView *sender, const std::string &url){
            toluafix_pushusertype_ccobject(L, sender->_ID, &(sender->_luaID), (void*)sender,"ccexp.WebView");
            tolua_pushcppstring(L, url);
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
        };
        
        ScriptHandlerMgr::getInstance()->addCustomHandler((void*)self, handler);
        self->setOnDidFailLoading(callback);
        return 0;
    }
    luaL_error(L, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.WebView:setOnDidFailLoading",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_cocos2dx_experimental_WebView_setOnDidFailLoading'.", &tolua_err);
#endif
    return 0;
}

static void extendWebView(lua_State* L)
{
    lua_pushstring(L, "ccexp.WebView");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "setOnShouldStartLoading", lua_cocos2dx_experimental_WebView_setOnShouldStartLoading);
        tolua_function(L, "setOnDidFinishLoading", lua_cocos2dx_experimental_WebView_setOnDidFinishLoading);
        tolua_function(L, "setOnDidFailLoading", lua_cocos2dx_experimental_WebView_setOnDidFailLoading);
    }
    lua_pop(L, 1);
}

int register_all_cocos2dx_experimental_webview_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendWebView(L);
    
    return 0;
}

#endif
