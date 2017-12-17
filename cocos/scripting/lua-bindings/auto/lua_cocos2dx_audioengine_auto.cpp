#include "scripting/lua-bindings/auto/lua_cocos2dx_audioengine_auto.hpp"
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_IOS || CC_TARGET_PLATFORM == CC_PLATFORM_MAC || CC_TARGET_PLATFORM == CC_PLATFORM_WIN32 || CC_TARGET_PLATFORM == CC_PLATFORM_TIZEN
#include "audio/include/AudioEngine.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/LuaBasicConversions.h"

int lua_cocos2dx_audioengine_AudioProfile_constructor(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::experimental::AudioProfile* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioProfile_constructor'", nullptr);
            return 0;
        }
        cobj = new cocos2d::experimental::AudioProfile();
        tolua_pushusertype(tolua_S,(void*)cobj,"ccexp.AudioProfile");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ccexp.AudioProfile:AudioProfile",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioProfile_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_audioengine_AudioProfile_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AudioProfile)");
    return 0;
}

int lua_register_cocos2dx_audioengine_AudioProfile(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.AudioProfile");
    tolua_cclass(tolua_S,"AudioProfile","ccexp.AudioProfile","",nullptr);

    tolua_beginmodule(tolua_S,"AudioProfile");
        tolua_function(tolua_S,"new",lua_cocos2dx_audioengine_AudioProfile_constructor);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::AudioProfile).name();
    g_luaType[typeName] = "ccexp.AudioProfile";
    g_typeCast["AudioProfile"] = "ccexp.AudioProfile";
    return 1;
}

int lua_cocos2dx_audioengine_AudioEngine_lazyInit(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_lazyInit'", nullptr);
            return 0;
        }
        bool ret = cocos2d::experimental::AudioEngine::lazyInit();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:lazyInit",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_lazyInit'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_setCurrentTime(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        double arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:setCurrentTime");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccexp.AudioEngine:setCurrentTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_setCurrentTime'", nullptr);
            return 0;
        }
        bool ret = cocos2d::experimental::AudioEngine::setCurrentTime(arg0, arg1);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:setCurrentTime",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_setCurrentTime'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getVolume(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:getVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getVolume'", nullptr);
            return 0;
        }
        double ret = cocos2d::experimental::AudioEngine::getVolume(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getVolume",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getVolume'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_uncache(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:uncache");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_uncache'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::uncache(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:uncache",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_uncache'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_resumeAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_resumeAll'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::resumeAll();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:resumeAll",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_resumeAll'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_stopAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_stopAll'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::stopAll();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:stopAll",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_stopAll'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_pause(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:pause");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_pause'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::pause(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:pause",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_pause'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance'", nullptr);
            return 0;
        }
        int ret = cocos2d::experimental::AudioEngine::getMaxAudioInstance();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getMaxAudioInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_isEnabled(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_isEnabled'", nullptr);
            return 0;
        }
        bool ret = cocos2d::experimental::AudioEngine::isEnabled();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:isEnabled",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_isEnabled'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getCurrentTime(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:getCurrentTime");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getCurrentTime'", nullptr);
            return 0;
        }
        double ret = cocos2d::experimental::AudioEngine::getCurrentTime(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getCurrentTime",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getCurrentTime'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:setMaxAudioInstance");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance'", nullptr);
            return 0;
        }
        bool ret = cocos2d::experimental::AudioEngine::setMaxAudioInstance(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:setMaxAudioInstance",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_isLoop(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:isLoop");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_isLoop'", nullptr);
            return 0;
        }
        bool ret = cocos2d::experimental::AudioEngine::isLoop(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:isLoop",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_isLoop'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_pauseAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_pauseAll'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::pauseAll();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:pauseAll",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_pauseAll'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_uncacheAll(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_uncacheAll'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::uncacheAll();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:uncacheAll",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_uncacheAll'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_setVolume(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        double arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:setVolume");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "ccexp.AudioEngine:setVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_setVolume'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::setVolume(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:setVolume",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_setVolume'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_preload(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 2)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:preload");
            if (!ok) { break; }
            std::function<void (bool)> arg1;
            do {
			// Lambda binding for lua is not supported.
			assert(false);
		} while(0)
		;
            if (!ok) { break; }
            cocos2d::experimental::AudioEngine::preload(arg0, arg1);
            lua_settop(tolua_S, 1);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:preload");
            if (!ok) { break; }
            cocos2d::experimental::AudioEngine::preload(arg0);
            lua_settop(tolua_S, 1);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccexp.AudioEngine:preload",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_preload'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_setEnabled(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        bool arg0;
        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "ccexp.AudioEngine:setEnabled");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_setEnabled'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::setEnabled(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:setEnabled",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_setEnabled'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_play2d(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:play2d");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_play2d'", nullptr);
            return 0;
        }
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 2)
    {
        std::string arg0;
        bool arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:play2d");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccexp.AudioEngine:play2d");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_play2d'", nullptr);
            return 0;
        }
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 3)
    {
        std::string arg0;
        bool arg1;
        double arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:play2d");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccexp.AudioEngine:play2d");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ccexp.AudioEngine:play2d");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_play2d'", nullptr);
            return 0;
        }
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 4)
    {
        std::string arg0;
        bool arg1;
        double arg2;
        const cocos2d::experimental::AudioProfile* arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:play2d");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccexp.AudioEngine:play2d");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "ccexp.AudioEngine:play2d");
        ok &= luaval_to_object<const cocos2d::experimental::AudioProfile>(tolua_S, 5, "ccexp.AudioProfile",&arg3, "ccexp.AudioEngine:play2d");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_play2d'", nullptr);
            return 0;
        }
        int ret = cocos2d::experimental::AudioEngine::play2d(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:play2d",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_play2d'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getState(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:getState");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getState'", nullptr);
            return 0;
        }
        int ret = (int)cocos2d::experimental::AudioEngine::getState(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getState",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getState'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_resume(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:resume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_resume'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::resume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:resume",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_resume'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_stop(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:stop");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_stop'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::stop(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:stop",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_stop'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_end(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_end'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::end();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:end",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_end'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getDuration(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        int arg0;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:getDuration");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getDuration'", nullptr);
            return 0;
        }
        double ret = cocos2d::experimental::AudioEngine::getDuration(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getDuration",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getDuration'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_setLoop(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        bool arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:setLoop");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "ccexp.AudioEngine:setLoop");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_setLoop'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioEngine::setLoop(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:setLoop",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_setLoop'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getDefaultProfile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getDefaultProfile'", nullptr);
            return 0;
        }
        cocos2d::experimental::AudioProfile* ret = cocos2d::experimental::AudioEngine::getDefaultProfile();
        object_to_luaval<cocos2d::experimental::AudioProfile>(tolua_S, "ccexp.AudioProfile",(cocos2d::experimental::AudioProfile*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getDefaultProfile",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getDefaultProfile'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getProfile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S)-1;

    do 
    {
        if (argc == 1)
        {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ccexp.AudioEngine:getProfile");
            if (!ok) { break; }
            cocos2d::experimental::AudioProfile* ret = cocos2d::experimental::AudioEngine::getProfile(arg0);
            object_to_luaval<cocos2d::experimental::AudioProfile>(tolua_S, "ccexp.AudioProfile",(cocos2d::experimental::AudioProfile*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    do 
    {
        if (argc == 1)
        {
            int arg0;
            ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "ccexp.AudioEngine:getProfile");
            if (!ok) { break; }
            cocos2d::experimental::AudioProfile* ret = cocos2d::experimental::AudioEngine::getProfile(arg0);
            object_to_luaval<cocos2d::experimental::AudioProfile>(tolua_S, "ccexp.AudioProfile",(cocos2d::experimental::AudioProfile*)ret);
            return 1;
        }
    } while (0);
    ok  = true;
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d", "ccexp.AudioEngine:getProfile",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getProfile'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_audioengine_AudioEngine_getPlayingAudioCount(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccexp.AudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_audioengine_AudioEngine_getPlayingAudioCount'", nullptr);
            return 0;
        }
        int ret = cocos2d::experimental::AudioEngine::getPlayingAudioCount();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ccexp.AudioEngine:getPlayingAudioCount",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_audioengine_AudioEngine_getPlayingAudioCount'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_audioengine_AudioEngine_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AudioEngine)");
    return 0;
}

int lua_register_cocos2dx_audioengine_AudioEngine(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccexp.AudioEngine");
    tolua_cclass(tolua_S,"AudioEngine","ccexp.AudioEngine","",nullptr);

    tolua_beginmodule(tolua_S,"AudioEngine");
        tolua_function(tolua_S,"lazyInit", lua_cocos2dx_audioengine_AudioEngine_lazyInit);
        tolua_function(tolua_S,"setCurrentTime", lua_cocos2dx_audioengine_AudioEngine_setCurrentTime);
        tolua_function(tolua_S,"getVolume", lua_cocos2dx_audioengine_AudioEngine_getVolume);
        tolua_function(tolua_S,"uncache", lua_cocos2dx_audioengine_AudioEngine_uncache);
        tolua_function(tolua_S,"resumeAll", lua_cocos2dx_audioengine_AudioEngine_resumeAll);
        tolua_function(tolua_S,"stopAll", lua_cocos2dx_audioengine_AudioEngine_stopAll);
        tolua_function(tolua_S,"pause", lua_cocos2dx_audioengine_AudioEngine_pause);
        tolua_function(tolua_S,"getMaxAudioInstance", lua_cocos2dx_audioengine_AudioEngine_getMaxAudioInstance);
        tolua_function(tolua_S,"isEnabled", lua_cocos2dx_audioengine_AudioEngine_isEnabled);
        tolua_function(tolua_S,"getCurrentTime", lua_cocos2dx_audioengine_AudioEngine_getCurrentTime);
        tolua_function(tolua_S,"setMaxAudioInstance", lua_cocos2dx_audioengine_AudioEngine_setMaxAudioInstance);
        tolua_function(tolua_S,"isLoop", lua_cocos2dx_audioengine_AudioEngine_isLoop);
        tolua_function(tolua_S,"pauseAll", lua_cocos2dx_audioengine_AudioEngine_pauseAll);
        tolua_function(tolua_S,"uncacheAll", lua_cocos2dx_audioengine_AudioEngine_uncacheAll);
        tolua_function(tolua_S,"setVolume", lua_cocos2dx_audioengine_AudioEngine_setVolume);
        tolua_function(tolua_S,"preload", lua_cocos2dx_audioengine_AudioEngine_preload);
        tolua_function(tolua_S,"setEnabled", lua_cocos2dx_audioengine_AudioEngine_setEnabled);
        tolua_function(tolua_S,"play2d", lua_cocos2dx_audioengine_AudioEngine_play2d);
        tolua_function(tolua_S,"getState", lua_cocos2dx_audioengine_AudioEngine_getState);
        tolua_function(tolua_S,"resume", lua_cocos2dx_audioengine_AudioEngine_resume);
        tolua_function(tolua_S,"stop", lua_cocos2dx_audioengine_AudioEngine_stop);
        tolua_function(tolua_S,"endToLua", lua_cocos2dx_audioengine_AudioEngine_end);
        tolua_function(tolua_S,"getDuration", lua_cocos2dx_audioengine_AudioEngine_getDuration);
        tolua_function(tolua_S,"setLoop", lua_cocos2dx_audioengine_AudioEngine_setLoop);
        tolua_function(tolua_S,"getDefaultProfile", lua_cocos2dx_audioengine_AudioEngine_getDefaultProfile);
        tolua_function(tolua_S,"getProfile", lua_cocos2dx_audioengine_AudioEngine_getProfile);
        tolua_function(tolua_S,"getPlayingAudioCount", lua_cocos2dx_audioengine_AudioEngine_getPlayingAudioCount);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::experimental::AudioEngine).name();
    g_luaType[typeName] = "ccexp.AudioEngine";
    g_typeCast["AudioEngine"] = "ccexp.AudioEngine";
    return 1;
}
TOLUA_API int register_all_cocos2dx_audioengine(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"ccexp",0);
	tolua_beginmodule(tolua_S,"ccexp");

	lua_register_cocos2dx_audioengine_AudioProfile(tolua_S);
	lua_register_cocos2dx_audioengine_AudioEngine(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

#endif
