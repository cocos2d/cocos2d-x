#include "lua_cocos2dx_pluginx_auto.hpp"
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"
#include "AgentManager.h"
#include "FacebookAgent.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "lua_pluginx_basic_conversions.h"



int lua_pluginx_protocols_PluginProtocol_getPluginName(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_getPluginName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginProtocol_getPluginName'", nullptr);
            return 0;
        }
        const char* ret = cobj->getPluginName();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.PluginProtocol:getPluginName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_getPluginName'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_PluginProtocol_getPluginVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_getPluginVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginProtocol_getPluginVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getPluginVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.PluginProtocol:getPluginVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_getPluginVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_PluginProtocol_getSDKVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_getSDKVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginProtocol_getSDKVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getSDKVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.PluginProtocol:getSDKVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_getSDKVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_PluginProtocol_setDebugMode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_setDebugMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "plugin.PluginProtocol:setDebugMode");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginProtocol_setDebugMode'", nullptr);
            return 0;
        }
        cobj->setDebugMode(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.PluginProtocol:setDebugMode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_setDebugMode'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_PluginProtocol_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginProtocol)");
    return 0;
}

int lua_register_pluginx_protocols_PluginProtocol(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.PluginProtocol");
    tolua_cclass(tolua_S,"PluginProtocol","plugin.PluginProtocol","",nullptr);

    tolua_beginmodule(tolua_S,"PluginProtocol");
        tolua_function(tolua_S,"getPluginName",lua_pluginx_protocols_PluginProtocol_getPluginName);
        tolua_function(tolua_S,"getPluginVersion",lua_pluginx_protocols_PluginProtocol_getPluginVersion);
        tolua_function(tolua_S,"getSDKVersion",lua_pluginx_protocols_PluginProtocol_getSDKVersion);
        tolua_function(tolua_S,"setDebugMode",lua_pluginx_protocols_PluginProtocol_setDebugMode);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::PluginProtocol).name();
    g_luaType[typeName] = "plugin.PluginProtocol";
    g_typeCast["PluginProtocol"] = "plugin.PluginProtocol";
    return 1;
}

int lua_pluginx_protocols_PluginManager_unloadPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::PluginManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginManager_unloadPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.PluginManager:unloadPlugin"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginManager_unloadPlugin'", nullptr);
            return 0;
        }
        cobj->unloadPlugin(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.PluginManager:unloadPlugin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginManager_unloadPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_PluginManager_loadPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::PluginManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginManager_loadPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.PluginManager:loadPlugin"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginManager_loadPlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::PluginProtocol* ret = cobj->loadPlugin(arg0);
        object_to_luaval<cocos2d::plugin::PluginProtocol>(tolua_S, "plugin.PluginProtocol",(cocos2d::plugin::PluginProtocol*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.PluginManager:loadPlugin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginManager_loadPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_PluginManager_end(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"plugin.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginManager_end'", nullptr);
            return 0;
        }
        cocos2d::plugin::PluginManager::end();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "plugin.PluginManager:end",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginManager_end'.",&tolua_err);
#endif
    return 0;
}
int lua_pluginx_protocols_PluginManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"plugin.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_PluginManager_getInstance'", nullptr);
            return 0;
        }
        cocos2d::plugin::PluginManager* ret = cocos2d::plugin::PluginManager::getInstance();
        object_to_luaval<cocos2d::plugin::PluginManager>(tolua_S, "plugin.PluginManager",(cocos2d::plugin::PluginManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "plugin.PluginManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_pluginx_protocols_PluginManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginManager)");
    return 0;
}

int lua_register_pluginx_protocols_PluginManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.PluginManager");
    tolua_cclass(tolua_S,"PluginManager","plugin.PluginManager","",nullptr);

    tolua_beginmodule(tolua_S,"PluginManager");
        tolua_function(tolua_S,"unloadPlugin",lua_pluginx_protocols_PluginManager_unloadPlugin);
        tolua_function(tolua_S,"loadPlugin",lua_pluginx_protocols_PluginManager_loadPlugin);
        tolua_function(tolua_S,"end", lua_pluginx_protocols_PluginManager_end);
        tolua_function(tolua_S,"getInstance", lua_pluginx_protocols_PluginManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::PluginManager).name();
    g_luaType[typeName] = "plugin.PluginManager";
    g_typeCast["PluginManager"] = "plugin.PluginManager";
    return 1;
}

int lua_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolAnalytics:logTimedEventBegin"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin'", nullptr);
            return 0;
        }
        cobj->logTimedEventBegin(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:logTimedEventBegin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_logError(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_logError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolAnalytics:logError"); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "plugin.ProtocolAnalytics:logError"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_logError'", nullptr);
            return 0;
        }
        cobj->logError(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:logError",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_logError'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0, "plugin.ProtocolAnalytics:setCaptureUncaughtException");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException'", nullptr);
            return 0;
        }
        cobj->setCaptureUncaughtException(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:setCaptureUncaughtException",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        long arg0;

        ok &= luaval_to_long(tolua_S, 2, &arg0, "plugin.ProtocolAnalytics:setSessionContinueMillis");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis'", nullptr);
            return 0;
        }
        cobj->setSessionContinueMillis(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:setSessionContinueMillis",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_logEvent(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_logEvent'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolAnalytics:logEvent"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_logEvent'", nullptr);
            return 0;
        }
        cobj->logEvent(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        const char* arg0;
        std::map<std::basic_string<char>, std::basic_string<char>, std::less<std::basic_string<char> >, std::allocator<std::pair<const std::basic_string<char>, std::basic_string<char> > > >* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolAnalytics:logEvent"); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_object<std::map<std::basic_string<char>, std::basic_string<char>, std::less<std::basic_string<char> >, std::allocator<std::pair<const std::basic_string<char>, std::basic_string<char> > > >>(tolua_S, 3, "std::map<std::basic_string<char>, std::basic_string<char>, std::less<std::basic_string<char> >, std::allocator<std::pair<const std::basic_string<char>, std::basic_string<char> > > >*",&arg1);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_logEvent'", nullptr);
            return 0;
        }
        cobj->logEvent(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:logEvent",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_logEvent'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_startSession(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_startSession'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolAnalytics:startSession"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_startSession'", nullptr);
            return 0;
        }
        cobj->startSession(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:startSession",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_startSession'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_stopSession(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_stopSession'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_stopSession'", nullptr);
            return 0;
        }
        cobj->stopSession();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:stopSession",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_stopSession'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolAnalytics:logTimedEventEnd"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd'", nullptr);
            return 0;
        }
        cobj->logTimedEventEnd(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAnalytics:logTimedEventEnd",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_ProtocolAnalytics_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolAnalytics)");
    return 0;
}

int lua_register_pluginx_protocols_ProtocolAnalytics(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.ProtocolAnalytics");
    tolua_cclass(tolua_S,"ProtocolAnalytics","plugin.ProtocolAnalytics","plugin.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolAnalytics");
        tolua_function(tolua_S,"logTimedEventBegin",lua_pluginx_protocols_ProtocolAnalytics_logTimedEventBegin);
        tolua_function(tolua_S,"logError",lua_pluginx_protocols_ProtocolAnalytics_logError);
        tolua_function(tolua_S,"setCaptureUncaughtException",lua_pluginx_protocols_ProtocolAnalytics_setCaptureUncaughtException);
        tolua_function(tolua_S,"setSessionContinueMillis",lua_pluginx_protocols_ProtocolAnalytics_setSessionContinueMillis);
        tolua_function(tolua_S,"logEvent",lua_pluginx_protocols_ProtocolAnalytics_logEvent);
        tolua_function(tolua_S,"startSession",lua_pluginx_protocols_ProtocolAnalytics_startSession);
        tolua_function(tolua_S,"stopSession",lua_pluginx_protocols_ProtocolAnalytics_stopSession);
        tolua_function(tolua_S,"logTimedEventEnd",lua_pluginx_protocols_ProtocolAnalytics_logTimedEventEnd);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::ProtocolAnalytics).name();
    g_luaType[typeName] = "plugin.ProtocolAnalytics";
    g_typeCast["ProtocolAnalytics"] = "plugin.ProtocolAnalytics";
    return 1;
}

int lua_pluginx_protocols_ProtocolIAP_onPayResult(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolIAP* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolIAP*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolIAP_onPayResult'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::plugin::PayResultCode arg0;
        const char* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "plugin.ProtocolIAP:onPayResult");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "plugin.ProtocolIAP:onPayResult"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolIAP_onPayResult'", nullptr);
            return 0;
        }
        cobj->onPayResult(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolIAP:onPayResult",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolIAP_onPayResult'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolIAP_configDeveloperInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolIAP* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolIAP*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolIAP_configDeveloperInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TIAPDeveloperInfo arg0;

        ok &= pluginx::luaval_to_TIAPDeveloperInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolIAP_configDeveloperInfo'", nullptr);
            return 0;
        }
        cobj->configDeveloperInfo(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolIAP:configDeveloperInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolIAP_configDeveloperInfo'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_ProtocolIAP_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolIAP)");
    return 0;
}

int lua_register_pluginx_protocols_ProtocolIAP(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.ProtocolIAP");
    tolua_cclass(tolua_S,"ProtocolIAP","plugin.ProtocolIAP","plugin.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolIAP");
        tolua_function(tolua_S,"onPayResult",lua_pluginx_protocols_ProtocolIAP_onPayResult);
        tolua_function(tolua_S,"configDeveloperInfo",lua_pluginx_protocols_ProtocolIAP_configDeveloperInfo);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::ProtocolIAP).name();
    g_luaType[typeName] = "plugin.ProtocolIAP";
    g_typeCast["ProtocolIAP"] = "plugin.ProtocolIAP";
    return 1;
}

int lua_pluginx_protocols_ProtocolAds_showAds(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAds_showAds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TAdsInfo arg0;

        ok &= pluginx::luaval_to_TAdsInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAds_showAds'", nullptr);
            return 0;
        }
        cobj->showAds(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        cocos2d::plugin::TAdsInfo arg0;
        cocos2d::plugin::ProtocolAds::AdsPos arg1;

        ok &= pluginx::luaval_to_TAdsInfo(tolua_S, 2, &arg0);

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "plugin.ProtocolAds:showAds");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAds_showAds'", nullptr);
            return 0;
        }
        cobj->showAds(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAds:showAds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAds_showAds'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAds_hideAds(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAds_hideAds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TAdsInfo arg0;

        ok &= pluginx::luaval_to_TAdsInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAds_hideAds'", nullptr);
            return 0;
        }
        cobj->hideAds(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAds:hideAds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAds_hideAds'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAds_queryPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAds_queryPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAds_queryPoints'", nullptr);
            return 0;
        }
        cobj->queryPoints();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAds:queryPoints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAds_queryPoints'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAds_spendPoints(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAds_spendPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "plugin.ProtocolAds:spendPoints");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAds_spendPoints'", nullptr);
            return 0;
        }
        cobj->spendPoints(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAds:spendPoints",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAds_spendPoints'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolAds_configDeveloperInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolAds_configDeveloperInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TAdsDeveloperInfo arg0;

        ok &= pluginx::luaval_to_TAdsDeveloperInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolAds_configDeveloperInfo'", nullptr);
            return 0;
        }
        cobj->configDeveloperInfo(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolAds:configDeveloperInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolAds_configDeveloperInfo'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_ProtocolAds_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolAds)");
    return 0;
}

int lua_register_pluginx_protocols_ProtocolAds(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.ProtocolAds");
    tolua_cclass(tolua_S,"ProtocolAds","plugin.ProtocolAds","plugin.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolAds");
        tolua_function(tolua_S,"showAds",lua_pluginx_protocols_ProtocolAds_showAds);
        tolua_function(tolua_S,"hideAds",lua_pluginx_protocols_ProtocolAds_hideAds);
        tolua_function(tolua_S,"queryPoints",lua_pluginx_protocols_ProtocolAds_queryPoints);
        tolua_function(tolua_S,"spendPoints",lua_pluginx_protocols_ProtocolAds_spendPoints);
        tolua_function(tolua_S,"configDeveloperInfo",lua_pluginx_protocols_ProtocolAds_configDeveloperInfo);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::ProtocolAds).name();
    g_luaType[typeName] = "plugin.ProtocolAds";
    g_typeCast["ProtocolAds"] = "plugin.ProtocolAds";
    return 1;
}

int lua_pluginx_protocols_ProtocolShare_onShareResult(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolShare* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolShare",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolShare*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolShare_onShareResult'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::plugin::ShareResultCode arg0;
        const char* arg1;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "plugin.ProtocolShare:onShareResult");

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp, "plugin.ProtocolShare:onShareResult"); arg1 = arg1_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolShare_onShareResult'", nullptr);
            return 0;
        }
        cobj->onShareResult(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolShare:onShareResult",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolShare_onShareResult'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolShare_configDeveloperInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolShare* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolShare",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolShare*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolShare_configDeveloperInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TShareDeveloperInfo arg0;

        ok &= pluginx::luaval_to_TShareDeveloperInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolShare_configDeveloperInfo'", nullptr);
            return 0;
        }
        cobj->configDeveloperInfo(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolShare:configDeveloperInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolShare_configDeveloperInfo'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_ProtocolShare_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolShare)");
    return 0;
}

int lua_register_pluginx_protocols_ProtocolShare(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.ProtocolShare");
    tolua_cclass(tolua_S,"ProtocolShare","plugin.ProtocolShare","plugin.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolShare");
        tolua_function(tolua_S,"onShareResult",lua_pluginx_protocols_ProtocolShare_onShareResult);
        tolua_function(tolua_S,"configDeveloperInfo",lua_pluginx_protocols_ProtocolShare_configDeveloperInfo);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::ProtocolShare).name();
    g_luaType[typeName] = "plugin.ProtocolShare";
    g_typeCast["ProtocolShare"] = "plugin.ProtocolShare";
    return 1;
}

int lua_pluginx_protocols_ProtocolSocial_showLeaderboard(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolSocial_showLeaderboard'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp, "plugin.ProtocolSocial:showLeaderboard"); arg0 = arg0_tmp.c_str();
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolSocial_showLeaderboard'", nullptr);
            return 0;
        }
        cobj->showLeaderboard(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolSocial:showLeaderboard",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolSocial_showLeaderboard'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolSocial_showAchievements(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolSocial_showAchievements'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolSocial_showAchievements'", nullptr);
            return 0;
        }
        cobj->showAchievements();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolSocial:showAchievements",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolSocial_showAchievements'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolSocial_configDeveloperInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolSocial_configDeveloperInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TSocialDeveloperInfo arg0;

        ok &= pluginx::luaval_to_TSocialDeveloperInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolSocial_configDeveloperInfo'", nullptr);
            return 0;
        }
        cobj->configDeveloperInfo(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolSocial:configDeveloperInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolSocial_configDeveloperInfo'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_ProtocolSocial_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolSocial)");
    return 0;
}

int lua_register_pluginx_protocols_ProtocolSocial(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.ProtocolSocial");
    tolua_cclass(tolua_S,"ProtocolSocial","plugin.ProtocolSocial","plugin.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolSocial");
        tolua_function(tolua_S,"showLeaderboard",lua_pluginx_protocols_ProtocolSocial_showLeaderboard);
        tolua_function(tolua_S,"showAchievements",lua_pluginx_protocols_ProtocolSocial_showAchievements);
        tolua_function(tolua_S,"configDeveloperInfo",lua_pluginx_protocols_ProtocolSocial_configDeveloperInfo);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::ProtocolSocial).name();
    g_luaType[typeName] = "plugin.ProtocolSocial";
    g_typeCast["ProtocolSocial"] = "plugin.ProtocolSocial";
    return 1;
}

int lua_pluginx_protocols_ProtocolUser_configDeveloperInfo(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolUser_configDeveloperInfo'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        cocos2d::plugin::TUserDeveloperInfo arg0;

        ok &= pluginx::luaval_to_TUserDeveloperInfo(tolua_S, 2, &arg0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolUser_configDeveloperInfo'", nullptr);
            return 0;
        }
        cobj->configDeveloperInfo(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolUser:configDeveloperInfo",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolUser_configDeveloperInfo'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolUser_isLoggedIn(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolUser_isLoggedIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolUser_isLoggedIn'", nullptr);
            return 0;
        }
        bool ret = cobj->isLoggedIn();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolUser:isLoggedIn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolUser_isLoggedIn'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolUser_getSessionID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolUser_getSessionID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolUser_getSessionID'", nullptr);
            return 0;
        }
        std::string ret = cobj->getSessionID();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolUser:getSessionID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolUser_getSessionID'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_ProtocolUser_getAccessToken(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolUser_getAccessToken'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_ProtocolUser_getAccessToken'", nullptr);
            return 0;
        }
        std::string ret = cobj->getAccessToken();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.ProtocolUser:getAccessToken",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolUser_getAccessToken'.",&tolua_err);
#endif

    return 0;
}
static int lua_pluginx_protocols_ProtocolUser_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolUser)");
    return 0;
}

int lua_register_pluginx_protocols_ProtocolUser(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.ProtocolUser");
    tolua_cclass(tolua_S,"ProtocolUser","plugin.ProtocolUser","plugin.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolUser");
        tolua_function(tolua_S,"configDeveloperInfo",lua_pluginx_protocols_ProtocolUser_configDeveloperInfo);
        tolua_function(tolua_S,"isLoggedIn",lua_pluginx_protocols_ProtocolUser_isLoggedIn);
        tolua_function(tolua_S,"getSessionID",lua_pluginx_protocols_ProtocolUser_getSessionID);
        tolua_function(tolua_S,"getAccessToken",lua_pluginx_protocols_ProtocolUser_getAccessToken);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::ProtocolUser).name();
    g_luaType[typeName] = "plugin.ProtocolUser";
    g_typeCast["ProtocolUser"] = "plugin.ProtocolUser";
    return 1;
}

int lua_pluginx_protocols_AgentManager_getSocialPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_getSocialPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getSocialPlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::ProtocolSocial* ret = cobj->getSocialPlugin();
        object_to_luaval<cocos2d::plugin::ProtocolSocial>(tolua_S, "plugin.ProtocolSocial",(cocos2d::plugin::ProtocolSocial*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:getSocialPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getSocialPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_getAdsPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_getAdsPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getAdsPlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::ProtocolAds* ret = cobj->getAdsPlugin();
        object_to_luaval<cocos2d::plugin::ProtocolAds>(tolua_S, "plugin.ProtocolAds",(cocos2d::plugin::ProtocolAds*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:getAdsPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getAdsPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_purge(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_purge'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_purge'", nullptr);
            return 0;
        }
        cobj->purge();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:purge",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_purge'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_getUserPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_getUserPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getUserPlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::ProtocolUser* ret = cobj->getUserPlugin();
        object_to_luaval<cocos2d::plugin::ProtocolUser>(tolua_S, "plugin.ProtocolUser",(cocos2d::plugin::ProtocolUser*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:getUserPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getUserPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_getIAPPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_getIAPPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getIAPPlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::ProtocolIAP* ret = cobj->getIAPPlugin();
        object_to_luaval<cocos2d::plugin::ProtocolIAP>(tolua_S, "plugin.ProtocolIAP",(cocos2d::plugin::ProtocolIAP*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:getIAPPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getIAPPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_getSharePlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_getSharePlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getSharePlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::ProtocolShare* ret = cobj->getSharePlugin();
        object_to_luaval<cocos2d::plugin::ProtocolShare>(tolua_S, "plugin.ProtocolShare",(cocos2d::plugin::ProtocolShare*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:getSharePlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getSharePlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_getAnalyticsPlugin(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_AgentManager_getAnalyticsPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getAnalyticsPlugin'", nullptr);
            return 0;
        }
        cocos2d::plugin::ProtocolAnalytics* ret = cobj->getAnalyticsPlugin();
        object_to_luaval<cocos2d::plugin::ProtocolAnalytics>(tolua_S, "plugin.ProtocolAnalytics",(cocos2d::plugin::ProtocolAnalytics*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.AgentManager:getAnalyticsPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getAnalyticsPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_AgentManager_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::plugin::AgentManager::destroyInstance();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "plugin.AgentManager:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_pluginx_protocols_AgentManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"plugin.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_AgentManager_getInstance'", nullptr);
            return 0;
        }
        cocos2d::plugin::AgentManager* ret = cocos2d::plugin::AgentManager::getInstance();
        object_to_luaval<cocos2d::plugin::AgentManager>(tolua_S, "plugin.AgentManager",(cocos2d::plugin::AgentManager*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "plugin.AgentManager:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_AgentManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_pluginx_protocols_AgentManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AgentManager)");
    return 0;
}

int lua_register_pluginx_protocols_AgentManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.AgentManager");
    tolua_cclass(tolua_S,"AgentManager","plugin.AgentManager","",nullptr);

    tolua_beginmodule(tolua_S,"AgentManager");
        tolua_function(tolua_S,"getSocialPlugin",lua_pluginx_protocols_AgentManager_getSocialPlugin);
        tolua_function(tolua_S,"getAdsPlugin",lua_pluginx_protocols_AgentManager_getAdsPlugin);
        tolua_function(tolua_S,"purge",lua_pluginx_protocols_AgentManager_purge);
        tolua_function(tolua_S,"getUserPlugin",lua_pluginx_protocols_AgentManager_getUserPlugin);
        tolua_function(tolua_S,"getIAPPlugin",lua_pluginx_protocols_AgentManager_getIAPPlugin);
        tolua_function(tolua_S,"getSharePlugin",lua_pluginx_protocols_AgentManager_getSharePlugin);
        tolua_function(tolua_S,"getAnalyticsPlugin",lua_pluginx_protocols_AgentManager_getAnalyticsPlugin);
        tolua_function(tolua_S,"destroyInstance", lua_pluginx_protocols_AgentManager_destroyInstance);
        tolua_function(tolua_S,"getInstance", lua_pluginx_protocols_AgentManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::AgentManager).name();
    g_luaType[typeName] = "plugin.AgentManager";
    g_typeCast["AgentManager"] = "plugin.AgentManager";
    return 1;
}

int lua_pluginx_protocols_FacebookAgent_activateApp(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_activateApp'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_activateApp'", nullptr);
            return 0;
        }
        cobj->activateApp();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:activateApp",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_activateApp'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_getPermissionList(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_getPermissionList'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_getPermissionList'", nullptr);
            return 0;
        }
        std::string ret = cobj->getPermissionList();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:getPermissionList",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_getPermissionList'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_getUserID(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_getUserID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_getUserID'", nullptr);
            return 0;
        }
        std::string ret = cobj->getUserID();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:getUserID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_getUserID'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_logout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_logout'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_logout'", nullptr);
            return 0;
        }
        cobj->logout();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:logout",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_logout'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_getSDKVersion(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_getSDKVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_getSDKVersion'", nullptr);
            return 0;
        }
        std::string ret = cobj->getSDKVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:getSDKVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_getSDKVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_isLoggedIn(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_isLoggedIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_isLoggedIn'", nullptr);
            return 0;
        }
        bool ret = cobj->isLoggedIn();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:isLoggedIn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_isLoggedIn'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_getAccessToken(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::plugin::FacebookAgent*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_getAccessToken'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_getAccessToken'", nullptr);
            return 0;
        }
        std::string ret = cobj->getAccessToken();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:getAccessToken",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_getAccessToken'.",&tolua_err);
#endif

    return 0;
}
int lua_pluginx_protocols_FacebookAgent_destroyInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"plugin.FacebookAgent",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_pluginx_protocols_FacebookAgent_destroyInstance'", nullptr);
            return 0;
        }
        cocos2d::plugin::FacebookAgent::destroyInstance();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "plugin.FacebookAgent:destroyInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_destroyInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_pluginx_protocols_FacebookAgent_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (FacebookAgent)");
    return 0;
}

int lua_register_pluginx_protocols_FacebookAgent(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"plugin.FacebookAgent");
    tolua_cclass(tolua_S,"FacebookAgent","plugin.FacebookAgent","",nullptr);

    tolua_beginmodule(tolua_S,"FacebookAgent");
        tolua_function(tolua_S,"activateApp",lua_pluginx_protocols_FacebookAgent_activateApp);
        tolua_function(tolua_S,"getPermissionList",lua_pluginx_protocols_FacebookAgent_getPermissionList);
        tolua_function(tolua_S,"getUserID",lua_pluginx_protocols_FacebookAgent_getUserID);
        tolua_function(tolua_S,"logout",lua_pluginx_protocols_FacebookAgent_logout);
        tolua_function(tolua_S,"getSDKVersion",lua_pluginx_protocols_FacebookAgent_getSDKVersion);
        tolua_function(tolua_S,"isLoggedIn",lua_pluginx_protocols_FacebookAgent_isLoggedIn);
        tolua_function(tolua_S,"getAccessToken",lua_pluginx_protocols_FacebookAgent_getAccessToken);
        tolua_function(tolua_S,"destroyInstance", lua_pluginx_protocols_FacebookAgent_destroyInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::plugin::FacebookAgent).name();
    g_luaType[typeName] = "plugin.FacebookAgent";
    g_typeCast["FacebookAgent"] = "plugin.FacebookAgent";
    return 1;
}
TOLUA_API int register_all_pluginx_protocols(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"plugin",0);
	tolua_beginmodule(tolua_S,"plugin");

	lua_register_pluginx_protocols_FacebookAgent(tolua_S);
	lua_register_pluginx_protocols_PluginProtocol(tolua_S);
	lua_register_pluginx_protocols_ProtocolUser(tolua_S);
	lua_register_pluginx_protocols_ProtocolShare(tolua_S);
	lua_register_pluginx_protocols_ProtocolIAP(tolua_S);
	lua_register_pluginx_protocols_AgentManager(tolua_S);
	lua_register_pluginx_protocols_ProtocolSocial(tolua_S);
	lua_register_pluginx_protocols_ProtocolAnalytics(tolua_S);
	lua_register_pluginx_protocols_ProtocolAds(tolua_S);
	lua_register_pluginx_protocols_PluginManager(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

