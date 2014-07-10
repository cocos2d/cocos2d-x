#include "lua_cocos2dx_experimental_video_manual.hpp"

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

int register_all_cocos2dx_experimental_video_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;
    
    extendVideoPlayer(L);
    
    return 0;
}

#endif
