#include "lua_cocos2dx_experimental_manual.hpp"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS)

#include "UIVideoPlayer.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"



static int lua_cocos2dx_experimental_video_VideoPlayer_addEventListener(lua_State* L)
{
    
    int argc = 0;
    cocos2d::experimental::ui::VideoPlayer* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
    if (!tolua_isusertype(L,1,"ccexp.VideoPlayer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<cocos2d::experimental::ui::VideoPlayer*>(tolua_tousertype(L,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(L,"invalid 'self' in function 'lua_cocos2dx_Widget_addTouchEventListener'\n", nullptr);
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
        
        self->addEventListener([=](cocos2d::Ref* ref, cocos2d::experimental::ui::VideoPlayer::EventType eventType){
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            
            stack->pushObject(ref, "cc.Ref");
            stack->pushInt((int)eventType);
            
            stack->executeFunctionByHandler(handler, 2);
        });
        
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "addEventListener",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(L, "#ferror in function 'lua_cocos2dx_experimental_VideoPlayer_addEventListener'.", &tolua_err);
#endif
    return 0;
}

static void extendVideoPlayer(lua_State* L)
{
    lua_pushstring(L, "ccexp.VideoPlayer");
    lua_rawget(L, LUA_REGISTRYINDEX);
    if (lua_istable(L,-1))
    {
        tolua_function(L, "addEventListener", lua_cocos2dx_experimental_video_VideoPlayer_addEventListener);
    }
    lua_pop(L, 1);
}

static int lua_cocos2dx_experimental_FastTMXLayer_getTileGIDAt(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::FastTMXLayer* cobj = nullptr;
    bool ok  = true;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif
    
    
#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccexp.FastTMXLayer",0,&tolua_err)) goto tolua_lerror;
#endif
    
    cobj = (cocos2d::experimental::FastTMXLayer*)tolua_tousertype(tolua_S,1,0);
    
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_experimental_FastTMXLayer_getTileGIDAt'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        cocos2d::Vec2 arg0;
        
        ok &= luaval_to_vec2(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        int ret = cobj->getTileGIDAt(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        tolua_pushnumber(tolua_S,(lua_Number)0);
        return 2;
    }
    if (argc == 2)
    {
        cocos2d::Vec2 arg0;
        int arg1 = 0;
        
        ok &= luaval_to_vec2(tolua_S, 2, &arg0);
        ok &= luaval_to_int32(tolua_S, 3, &arg1);
        
        if(!ok)
            return 0;
        
        unsigned int ret = cobj->getTileGIDAt(arg0, (cocos2d::TMXTileFlags*)&arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        tolua_pushnumber(tolua_S,(lua_Number)arg1);
        return 2;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getTileGIDAt",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_experimental_FastTMXLayer_getTileGIDAt'.",&tolua_err);
#endif
    
    return 0;
}

static void extendFastTMXLayer(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ccexp.FastTMXLayer");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "getTileGIDAt", lua_cocos2dx_experimental_FastTMXLayer_getTileGIDAt);
    }
    lua_pop(tolua_S, 1);
}

int register_all_cocos2dx_experimental_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendVideoPlayer(L);
    extendFastTMXLayer(L);
    
    return 0;
}

#endif
