#include "lua_cocos2dx_cocosdenshion_auto.hpp"
#include "SimpleAudioEngine.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:preloadBackgroundMusic"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->preloadBackgroundMusic(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:preloadBackgroundMusic",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->stopBackgroundMusic();
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "cc.SimpleAudioEngine:stopBackgroundMusic");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->stopBackgroundMusic(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:stopBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopAllEffects(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopAllEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopAllEffects'", nullptr);
            return 0;
        }
        cobj->stopAllEffects();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:stopAllEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopAllEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getBackgroundMusicVolume(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getBackgroundMusicVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getBackgroundMusicVolume'", nullptr);
            return 0;
        }
        double ret = cobj->getBackgroundMusicVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:getBackgroundMusicVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getBackgroundMusicVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->resumeBackgroundMusic();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:resumeBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setBackgroundMusicVolume(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setBackgroundMusicVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.SimpleAudioEngine:setBackgroundMusicVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setBackgroundMusicVolume'", nullptr);
            return 0;
        }
        cobj->setBackgroundMusicVolume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:setBackgroundMusicVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setBackgroundMusicVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadEffect(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:preloadEffect"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadEffect'", nullptr);
            return 0;
        }
        cobj->preloadEffect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:preloadEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_isBackgroundMusicPlaying(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_isBackgroundMusicPlaying'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_isBackgroundMusicPlaying'", nullptr);
            return 0;
        }
        bool ret = cobj->isBackgroundMusicPlaying();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:isBackgroundMusicPlaying",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_isBackgroundMusicPlaying'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getEffectsVolume(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getEffectsVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getEffectsVolume'", nullptr);
            return 0;
        }
        double ret = cobj->getEffectsVolume();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:getEffectsVolume",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getEffectsVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_willPlayBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_willPlayBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_willPlayBackgroundMusic'", nullptr);
            return 0;
        }
        bool ret = cobj->willPlayBackgroundMusic();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:willPlayBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_willPlayBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseEffect(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.SimpleAudioEngine:pauseEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseEffect'", nullptr);
            return 0;
        }
        cobj->pauseEffect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:pauseEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playEffect"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->playEffect(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        bool arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playEffect"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.SimpleAudioEngine:playEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->playEffect(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 3) 
    {
        const char* arg0;
        bool arg1;
        double arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playEffect"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.SimpleAudioEngine:playEffect");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.SimpleAudioEngine:playEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->playEffect(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 4) 
    {
        const char* arg0;
        bool arg1;
        double arg2;
        double arg3;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playEffect"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.SimpleAudioEngine:playEffect");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.SimpleAudioEngine:playEffect");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.SimpleAudioEngine:playEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->playEffect(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    if (argc == 5) 
    {
        const char* arg0;
        bool arg1;
        double arg2;
        double arg3;
        double arg4;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playEffect"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.SimpleAudioEngine:playEffect");

        ok &= luaval_to_number(tolua_S, 4,&arg2, "cc.SimpleAudioEngine:playEffect");

        ok &= luaval_to_number(tolua_S, 5,&arg3, "cc.SimpleAudioEngine:playEffect");

        ok &= luaval_to_number(tolua_S, 6,&arg4, "cc.SimpleAudioEngine:playEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'", nullptr);
            return 0;
        }
        unsigned int ret = cobj->playEffect(arg0, arg1, arg2, arg3, arg4);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:playEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_rewindBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_rewindBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_rewindBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->rewindBackgroundMusic();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:rewindBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_rewindBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playBackgroundMusic"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->playBackgroundMusic(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 2) 
    {
        const char* arg0;
        bool arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:playBackgroundMusic"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "cc.SimpleAudioEngine:playBackgroundMusic");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->playBackgroundMusic(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:playBackgroundMusic",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeAllEffects(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeAllEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeAllEffects'", nullptr);
            return 0;
        }
        cobj->resumeAllEffects();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:resumeAllEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeAllEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setEffectsVolume(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setEffectsVolume'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0, "cc.SimpleAudioEngine:setEffectsVolume");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setEffectsVolume'", nullptr);
            return 0;
        }
        cobj->setEffectsVolume(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:setEffectsVolume",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setEffectsVolume'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopEffect(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.SimpleAudioEngine:stopEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopEffect'", nullptr);
            return 0;
        }
        cobj->stopEffect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:stopEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseBackgroundMusic(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseBackgroundMusic'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseBackgroundMusic'", nullptr);
            return 0;
        }
        cobj->pauseBackgroundMusic();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:pauseBackgroundMusic",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseBackgroundMusic'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseAllEffects(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseAllEffects'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseAllEffects'", nullptr);
            return 0;
        }
        cobj->pauseAllEffects();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:pauseAllEffects",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseAllEffects'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_unloadEffect(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_unloadEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "cc.SimpleAudioEngine:unloadEffect"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_unloadEffect'", nullptr);
            return 0;
        }
        cobj->unloadEffect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:unloadEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_unloadEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeEffect(lua_State* tolua_S)
{
    int argc = 0;
    CocosDenshion::SimpleAudioEngine* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (CocosDenshion::SimpleAudioEngine*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeEffect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        unsigned int arg0;

        ok &= luaval_to_uint32(tolua_S, 2,&arg0, "cc.SimpleAudioEngine:resumeEffect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeEffect'", nullptr);
            return 0;
        }
        cobj->resumeEffect(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "cc.SimpleAudioEngine:resumeEffect",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeEffect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_end(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_end'", nullptr);
            return 0;
        }
        CocosDenshion::SimpleAudioEngine::end();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SimpleAudioEngine:end",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_end'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.SimpleAudioEngine",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getInstance'", nullptr);
            return 0;
        }
        CocosDenshion::SimpleAudioEngine* ret = CocosDenshion::SimpleAudioEngine::getInstance();
        object_to_luaval<CocosDenshion::SimpleAudioEngine>(tolua_S, "cc.SimpleAudioEngine",(CocosDenshion::SimpleAudioEngine*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "cc.SimpleAudioEngine:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_cocosdenshion_SimpleAudioEngine_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SimpleAudioEngine)");
    return 0;
}

int lua_register_cocos2dx_cocosdenshion_SimpleAudioEngine(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.SimpleAudioEngine");
    tolua_cclass(tolua_S,"SimpleAudioEngine","cc.SimpleAudioEngine","",nullptr);

    tolua_beginmodule(tolua_S,"SimpleAudioEngine");
        tolua_function(tolua_S,"preloadMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadBackgroundMusic);
        tolua_function(tolua_S,"stopMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopBackgroundMusic);
        tolua_function(tolua_S,"stopAllEffects",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopAllEffects);
        tolua_function(tolua_S,"getMusicVolume",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getBackgroundMusicVolume);
        tolua_function(tolua_S,"resumeMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeBackgroundMusic);
        tolua_function(tolua_S,"setMusicVolume",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setBackgroundMusicVolume);
        tolua_function(tolua_S,"preloadEffect",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_preloadEffect);
        tolua_function(tolua_S,"isMusicPlaying",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_isBackgroundMusicPlaying);
        tolua_function(tolua_S,"getEffectsVolume",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getEffectsVolume);
        tolua_function(tolua_S,"willPlayMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_willPlayBackgroundMusic);
        tolua_function(tolua_S,"pauseEffect",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseEffect);
        tolua_function(tolua_S,"playEffect",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playEffect);
        tolua_function(tolua_S,"rewindMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_rewindBackgroundMusic);
        tolua_function(tolua_S,"playMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_playBackgroundMusic);
        tolua_function(tolua_S,"resumeAllEffects",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeAllEffects);
        tolua_function(tolua_S,"setEffectsVolume",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_setEffectsVolume);
        tolua_function(tolua_S,"stopEffect",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_stopEffect);
        tolua_function(tolua_S,"pauseMusic",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseBackgroundMusic);
        tolua_function(tolua_S,"pauseAllEffects",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_pauseAllEffects);
        tolua_function(tolua_S,"unloadEffect",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_unloadEffect);
        tolua_function(tolua_S,"resumeEffect",lua_cocos2dx_cocosdenshion_SimpleAudioEngine_resumeEffect);
        tolua_function(tolua_S,"destroyInstance", lua_cocos2dx_cocosdenshion_SimpleAudioEngine_end);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_cocosdenshion_SimpleAudioEngine_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(CocosDenshion::SimpleAudioEngine).name();
    g_luaType[typeName] = "cc.SimpleAudioEngine";
    g_typeCast["SimpleAudioEngine"] = "cc.SimpleAudioEngine";
    return 1;
}
TOLUA_API int register_all_cocos2dx_cocosdenshion(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_cocosdenshion_SimpleAudioEngine(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

