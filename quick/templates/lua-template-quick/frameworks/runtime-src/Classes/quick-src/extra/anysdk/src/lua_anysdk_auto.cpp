#include "lua_anysdk_auto.hpp"
#include "AgentManager.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_anysdk_PluginProtocol_getPluginName(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginProtocol_getPluginName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const char* ret = cobj->getPluginName();
        tolua_pushstring(tolua_S,(const char*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPluginName",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginProtocol_getPluginName'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_PluginProtocol_getPluginVersion(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginProtocol_getPluginVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getPluginVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPluginVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginProtocol_getPluginVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_PluginProtocol_setPluginName(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginProtocol_setPluginName'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->setPluginName(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setPluginName",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginProtocol_setPluginName'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_PluginProtocol_getSDKVersion(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginProtocol_getSDKVersion'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getSDKVersion();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSDKVersion",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginProtocol_getSDKVersion'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_PluginProtocol_setDebugMode(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginProtocol* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginProtocol",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginProtocol*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginProtocol_setDebugMode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setDebugMode(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setDebugMode",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginProtocol_setDebugMode'.",&tolua_err);
#endif

    return 0;
}
static int lua_anysdk_PluginProtocol_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginProtocol)");
    return 0;
}

int lua_register_anysdk_PluginProtocol(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.PluginProtocol");
    tolua_cclass(tolua_S,"PluginProtocol","ccanysdk.PluginProtocol","",nullptr);

    tolua_beginmodule(tolua_S,"PluginProtocol");
        tolua_function(tolua_S,"getPluginName",lua_anysdk_PluginProtocol_getPluginName);
        tolua_function(tolua_S,"getPluginVersion",lua_anysdk_PluginProtocol_getPluginVersion);
        tolua_function(tolua_S,"setPluginName",lua_anysdk_PluginProtocol_setPluginName);
        tolua_function(tolua_S,"getSDKVersion",lua_anysdk_PluginProtocol_getSDKVersion);
        tolua_function(tolua_S,"setDebugMode",lua_anysdk_PluginProtocol_setDebugMode);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::PluginProtocol).name();
    g_luaType[typeName] = "ccanysdk.PluginProtocol";
    g_typeCast["PluginProtocol"] = "ccanysdk.PluginProtocol";
    return 1;
}

int lua_anysdk_PluginFactory_purgeFactory(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.PluginFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::PluginFactory::purgeFactory();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "purgeFactory",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginFactory_purgeFactory'.",&tolua_err);
#endif
    return 0;
}
int lua_anysdk_PluginFactory_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.PluginFactory",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::PluginFactory* ret = anysdk::framework::PluginFactory::getInstance();
        object_to_luaval<anysdk::framework::PluginFactory>(tolua_S, "ccanysdk.PluginFactory",(anysdk::framework::PluginFactory*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginFactory_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_anysdk_PluginFactory_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginFactory)");
    return 0;
}

int lua_register_anysdk_PluginFactory(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.PluginFactory");
    tolua_cclass(tolua_S,"PluginFactory","ccanysdk.PluginFactory","",nullptr);

    tolua_beginmodule(tolua_S,"PluginFactory");
        tolua_function(tolua_S,"purgeFactory", lua_anysdk_PluginFactory_purgeFactory);
        tolua_function(tolua_S,"getInstance", lua_anysdk_PluginFactory_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::PluginFactory).name();
    g_luaType[typeName] = "ccanysdk.PluginFactory";
    g_typeCast["PluginFactory"] = "ccanysdk.PluginFactory";
    return 1;
}

int lua_anysdk_PluginManager_unloadPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginManager_unloadPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->unloadPlugin(arg0);
        return 0;
    }
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        cobj->unloadPlugin(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unloadPlugin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginManager_unloadPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_PluginManager_loadPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::PluginManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::PluginManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_PluginManager_loadPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        int arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        anysdk::framework::PluginProtocol* ret = cobj->loadPlugin(arg0, arg1);
        object_to_luaval<anysdk::framework::PluginProtocol>(tolua_S, "ccanysdk.PluginProtocol",(anysdk::framework::PluginProtocol*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "loadPlugin",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginManager_loadPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_PluginManager_end(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::PluginManager::end();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "end",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginManager_end'.",&tolua_err);
#endif
    return 0;
}
int lua_anysdk_PluginManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.PluginManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::PluginManager* ret = anysdk::framework::PluginManager::getInstance();
        object_to_luaval<anysdk::framework::PluginManager>(tolua_S, "ccanysdk.PluginManager",(anysdk::framework::PluginManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_PluginManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_anysdk_PluginManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (PluginManager)");
    return 0;
}

int lua_register_anysdk_PluginManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.PluginManager");
    tolua_cclass(tolua_S,"PluginManager","ccanysdk.PluginManager","",nullptr);

    tolua_beginmodule(tolua_S,"PluginManager");
        tolua_function(tolua_S,"unloadPlugin",lua_anysdk_PluginManager_unloadPlugin);
        tolua_function(tolua_S,"loadPlugin",lua_anysdk_PluginManager_loadPlugin);
        tolua_function(tolua_S,"end", lua_anysdk_PluginManager_end);
        tolua_function(tolua_S,"getInstance", lua_anysdk_PluginManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::PluginManager).name();
    g_luaType[typeName] = "ccanysdk.PluginManager";
    g_typeCast["PluginManager"] = "ccanysdk.PluginManager";
    return 1;
}

int lua_anysdk_ProtocolIAP_getPluginId(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolIAP* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolIAP*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolIAP_getPluginId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getPluginId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPluginId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolIAP_getPluginId'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolIAP_getOrderId(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolIAP* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolIAP*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolIAP_getOrderId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getOrderId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getOrderId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolIAP_getOrderId'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolIAP_resetPayState(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolIAP::resetPayState();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "resetPayState",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolIAP_resetPayState'.",&tolua_err);
#endif
    return 0;
}
static int lua_anysdk_ProtocolIAP_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolIAP)");
    return 0;
}

int lua_register_anysdk_ProtocolIAP(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolIAP");
    tolua_cclass(tolua_S,"ProtocolIAP","ccanysdk.ProtocolIAP","ccanysdk.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolIAP");
        tolua_function(tolua_S,"getPluginId",lua_anysdk_ProtocolIAP_getPluginId);
        tolua_function(tolua_S,"getOrderId",lua_anysdk_ProtocolIAP_getOrderId);
        tolua_function(tolua_S,"resetPayState", lua_anysdk_ProtocolIAP_resetPayState);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolIAP).name();
    g_luaType[typeName] = "ccanysdk.ProtocolIAP";
    g_typeCast["ProtocolIAP"] = "ccanysdk.ProtocolIAP";
    return 1;
}

int lua_anysdk_ProtocolAnalytics_logTimedEventBegin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_logTimedEventBegin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->logTimedEventBegin(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "logTimedEventBegin",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_logTimedEventBegin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAnalytics_logError(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_logError'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        const char* arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        if(!ok)
            return 0;
        cobj->logError(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "logError",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_logError'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAnalytics_setCaptureUncaughtException(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_setCaptureUncaughtException'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        bool arg0;

        ok &= luaval_to_boolean(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setCaptureUncaughtException(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCaptureUncaughtException",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_setCaptureUncaughtException'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAnalytics_setSessionContinueMillis(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_setSessionContinueMillis'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        long arg0;

        ok &= luaval_to_long(tolua_S, 2, &arg0);
        if(!ok)
            return 0;
        cobj->setSessionContinueMillis(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setSessionContinueMillis",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_setSessionContinueMillis'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAnalytics_startSession(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_startSession'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->startSession();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "startSession",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_startSession'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAnalytics_stopSession(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_stopSession'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->stopSession();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "stopSession",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_stopSession'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAnalytics_logTimedEventEnd(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAnalytics* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAnalytics",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAnalytics*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAnalytics_logTimedEventEnd'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->logTimedEventEnd(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "logTimedEventEnd",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAnalytics_logTimedEventEnd'.",&tolua_err);
#endif

    return 0;
}
static int lua_anysdk_ProtocolAnalytics_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolAnalytics)");
    return 0;
}

int lua_register_anysdk_ProtocolAnalytics(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolAnalytics");
    tolua_cclass(tolua_S,"ProtocolAnalytics","ccanysdk.ProtocolAnalytics","ccanysdk.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolAnalytics");
        tolua_function(tolua_S,"logTimedEventBegin",lua_anysdk_ProtocolAnalytics_logTimedEventBegin);
        tolua_function(tolua_S,"logError",lua_anysdk_ProtocolAnalytics_logError);
        tolua_function(tolua_S,"setCaptureUncaughtException",lua_anysdk_ProtocolAnalytics_setCaptureUncaughtException);
        tolua_function(tolua_S,"setSessionContinueMillis",lua_anysdk_ProtocolAnalytics_setSessionContinueMillis);
        tolua_function(tolua_S,"startSession",lua_anysdk_ProtocolAnalytics_startSession);
        tolua_function(tolua_S,"stopSession",lua_anysdk_ProtocolAnalytics_stopSession);
        tolua_function(tolua_S,"logTimedEventEnd",lua_anysdk_ProtocolAnalytics_logTimedEventEnd);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolAnalytics).name();
    g_luaType[typeName] = "ccanysdk.ProtocolAnalytics";
    g_typeCast["ProtocolAnalytics"] = "ccanysdk.ProtocolAnalytics";
    return 1;
}

int lua_anysdk_ProtocolAds_showAds(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAds_showAds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        anysdk::framework::AdsType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->showAds(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "showAds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAds_showAds'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAds_hideAds(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAds_hideAds'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        anysdk::framework::AdsType arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->hideAds(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "hideAds",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAds_hideAds'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAds_queryPoints(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAds_queryPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        double ret = cobj->queryPoints();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "queryPoints",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAds_queryPoints'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAds_spendPoints(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAds_spendPoints'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        if(!ok)
            return 0;
        cobj->spendPoints(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "spendPoints",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAds_spendPoints'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolAds_isSupportFunction(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolAds* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolAds",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolAds*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolAds_isSupportFunction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->isSupportFunction(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isSupportFunction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolAds_isSupportFunction'.",&tolua_err);
#endif

    return 0;
}
static int lua_anysdk_ProtocolAds_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolAds)");
    return 0;
}

int lua_register_anysdk_ProtocolAds(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolAds");
    tolua_cclass(tolua_S,"ProtocolAds","ccanysdk.ProtocolAds","ccanysdk.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolAds");
        tolua_function(tolua_S,"showAds",lua_anysdk_ProtocolAds_showAds);
        tolua_function(tolua_S,"hideAds",lua_anysdk_ProtocolAds_hideAds);
        tolua_function(tolua_S,"queryPoints",lua_anysdk_ProtocolAds_queryPoints);
        tolua_function(tolua_S,"spendPoints",lua_anysdk_ProtocolAds_spendPoints);
        tolua_function(tolua_S,"isSupportFunction",lua_anysdk_ProtocolAds_isSupportFunction);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolAds).name();
    g_luaType[typeName] = "ccanysdk.ProtocolAds";
    g_typeCast["ProtocolAds"] = "ccanysdk.ProtocolAds";
    return 1;
}

int lua_anysdk_ProtocolSocial_showLeaderboard(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolSocial_showLeaderboard'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        const char* arg0;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cobj->showLeaderboard(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "showLeaderboard",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolSocial_showLeaderboard'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolSocial_signOut(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolSocial_signOut'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->signOut();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "signOut",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolSocial_signOut'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolSocial_showAchievements(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolSocial_showAchievements'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->showAchievements();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "showAchievements",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolSocial_showAchievements'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolSocial_signIn(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolSocial_signIn'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->signIn();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "signIn",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolSocial_signIn'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolSocial_submitScore(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolSocial* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolSocial",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolSocial*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolSocial_submitScore'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        const char* arg0;
        long arg1;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        ok &= luaval_to_long(tolua_S, 3, &arg1);
        if(!ok)
            return 0;
        cobj->submitScore(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "submitScore",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolSocial_submitScore'.",&tolua_err);
#endif

    return 0;
}
static int lua_anysdk_ProtocolSocial_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolSocial)");
    return 0;
}

int lua_register_anysdk_ProtocolSocial(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolSocial");
    tolua_cclass(tolua_S,"ProtocolSocial","ccanysdk.ProtocolSocial","ccanysdk.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolSocial");
        tolua_function(tolua_S,"showLeaderboard",lua_anysdk_ProtocolSocial_showLeaderboard);
        tolua_function(tolua_S,"signOut",lua_anysdk_ProtocolSocial_signOut);
        tolua_function(tolua_S,"showAchievements",lua_anysdk_ProtocolSocial_showAchievements);
        tolua_function(tolua_S,"signIn",lua_anysdk_ProtocolSocial_signIn);
        tolua_function(tolua_S,"submitScore",lua_anysdk_ProtocolSocial_submitScore);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolSocial).name();
    g_luaType[typeName] = "ccanysdk.ProtocolSocial";
    g_typeCast["ProtocolSocial"] = "ccanysdk.ProtocolSocial";
    return 1;
}

int lua_anysdk_ProtocolUser_isLogined(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolUser_isLogined'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->isLogined();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isLogined",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolUser_isLogined'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolUser_getUserID(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolUser_getUserID'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getUserID();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getUserID",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolUser_getUserID'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolUser_isSupportFunction(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolUser_isSupportFunction'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        bool ret = cobj->isSupportFunction(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "isSupportFunction",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolUser_isSupportFunction'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolUser_login(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolUser* cobj = nullptr;
    bool ok  = true;
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif
    cobj = (anysdk::framework::ProtocolUser*)tolua_tousertype(tolua_S,1,0);
#if COCOS2D_DEBUG >= 1
    if (!cobj)
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolUser_login'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0);

            if (!ok) { break; }
            cobj->login(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->login();
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "login",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolUser_login'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolUser_getPluginId(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolUser* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolUser",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolUser*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolUser_getPluginId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getPluginId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPluginId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolUser_getPluginId'.",&tolua_err);
#endif

    return 0;
}
static int lua_anysdk_ProtocolUser_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolUser)");
    return 0;
}

int lua_register_anysdk_ProtocolUser(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolUser");
    tolua_cclass(tolua_S,"ProtocolUser","ccanysdk.ProtocolUser","ccanysdk.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolUser");
        tolua_function(tolua_S,"isLogined",lua_anysdk_ProtocolUser_isLogined);
        tolua_function(tolua_S,"getUserID",lua_anysdk_ProtocolUser_getUserID);
        tolua_function(tolua_S,"isSupportFunction",lua_anysdk_ProtocolUser_isSupportFunction);
        tolua_function(tolua_S,"login",lua_anysdk_ProtocolUser_login);
        tolua_function(tolua_S,"getPluginId",lua_anysdk_ProtocolUser_getPluginId);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolUser).name();
    g_luaType[typeName] = "ccanysdk.ProtocolUser";
    g_typeCast["ProtocolUser"] = "ccanysdk.ProtocolUser";
    return 1;
}

int lua_anysdk_ProtocolPush_startPush(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolPush* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolPush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolPush*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolPush_startPush'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->startPush();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "startPush",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolPush_startPush'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolPush_closePush(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolPush* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolPush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolPush*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolPush_closePush'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->closePush();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "closePush",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolPush_closePush'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolPush_delAlias(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolPush* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolPush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolPush*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolPush_delAlias'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->delAlias(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "delAlias",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolPush_delAlias'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_ProtocolPush_setAlias(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::ProtocolPush* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolPush",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::ProtocolPush*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_ProtocolPush_setAlias'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        std::string arg0;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->setAlias(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAlias",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_ProtocolPush_setAlias'.",&tolua_err);
#endif

    return 0;
}
static int lua_anysdk_ProtocolPush_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ProtocolPush)");
    return 0;
}

int lua_register_anysdk_ProtocolPush(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolPush");
    tolua_cclass(tolua_S,"ProtocolPush","ccanysdk.ProtocolPush","ccanysdk.PluginProtocol",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolPush");
        tolua_function(tolua_S,"startPush",lua_anysdk_ProtocolPush_startPush);
        tolua_function(tolua_S,"closePush",lua_anysdk_ProtocolPush_closePush);
        tolua_function(tolua_S,"delAlias",lua_anysdk_ProtocolPush_delAlias);
        tolua_function(tolua_S,"setAlias",lua_anysdk_ProtocolPush_setAlias);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolPush).name();
    g_luaType[typeName] = "ccanysdk.ProtocolPush";
    g_typeCast["ProtocolPush"] = "ccanysdk.ProtocolPush";
    return 1;
}

int lua_anysdk_AgentManager_getSocialPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getSocialPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolSocial* ret = cobj->getSocialPlugin();
        object_to_luaval<anysdk::framework::ProtocolSocial>(tolua_S, "ccanysdk.ProtocolSocial",(anysdk::framework::ProtocolSocial*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSocialPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getSocialPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_unloadALLPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_unloadALLPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->unloadALLPlugin();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unloadALLPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_unloadALLPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_loadALLPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_loadALLPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->loadALLPlugin();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "loadALLPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_loadALLPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_getUserPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getUserPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolUser* ret = cobj->getUserPlugin();
        object_to_luaval<anysdk::framework::ProtocolUser>(tolua_S, "ccanysdk.ProtocolUser",(anysdk::framework::ProtocolUser*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getUserPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getUserPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_init(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4) 
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0);

        ok &= luaval_to_std_string(tolua_S, 3,&arg1);

        ok &= luaval_to_std_string(tolua_S, 4,&arg2);

        ok &= luaval_to_std_string(tolua_S, 5,&arg3);
        if(!ok)
            return 0;
        cobj->init(arg0, arg1, arg2, arg3);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "init",argc, 4);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_init'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_getAdsPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getAdsPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolAds* ret = cobj->getAdsPlugin();
        object_to_luaval<anysdk::framework::ProtocolAds>(tolua_S, "ccanysdk.ProtocolAds",(anysdk::framework::ProtocolAds*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAdsPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getAdsPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_getPushPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getPushPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolPush* ret = cobj->getPushPlugin();
        object_to_luaval<anysdk::framework::ProtocolPush>(tolua_S, "ccanysdk.ProtocolPush",(anysdk::framework::ProtocolPush*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getPushPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getPushPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_getSharePlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getSharePlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolShare* ret = cobj->getSharePlugin();
        object_to_luaval<anysdk::framework::ProtocolShare>(tolua_S, "ccanysdk.ProtocolShare",(anysdk::framework::ProtocolShare*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getSharePlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getSharePlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_getAnalyticsPlugin(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getAnalyticsPlugin'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        anysdk::framework::ProtocolAnalytics* ret = cobj->getAnalyticsPlugin();
        object_to_luaval<anysdk::framework::ProtocolAnalytics>(tolua_S, "ccanysdk.ProtocolAnalytics",(anysdk::framework::ProtocolAnalytics*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getAnalyticsPlugin",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getAnalyticsPlugin'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_getChannelId(lua_State* tolua_S)
{
    int argc = 0;
    anysdk::framework::AgentManager* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (anysdk::framework::AgentManager*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_anysdk_AgentManager_getChannelId'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        std::string ret = cobj->getChannelId();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getChannelId",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getChannelId'.",&tolua_err);
#endif

    return 0;
}
int lua_anysdk_AgentManager_end(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::AgentManager::end();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "end",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_end'.",&tolua_err);
#endif
    return 0;
}
int lua_anysdk_AgentManager_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        anysdk::framework::AgentManager* ret = anysdk::framework::AgentManager::getInstance();
        object_to_luaval<anysdk::framework::AgentManager>(tolua_S, "ccanysdk.AgentManager",(anysdk::framework::AgentManager*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_anysdk_AgentManager_getInstance'.",&tolua_err);
#endif
    return 0;
}
static int lua_anysdk_AgentManager_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (AgentManager)");
    return 0;
}

int lua_register_anysdk_AgentManager(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.AgentManager");
    tolua_cclass(tolua_S,"AgentManager","ccanysdk.AgentManager","",nullptr);

    tolua_beginmodule(tolua_S,"AgentManager");
        tolua_function(tolua_S,"getSocialPlugin",lua_anysdk_AgentManager_getSocialPlugin);
        tolua_function(tolua_S,"unloadALLPlugin",lua_anysdk_AgentManager_unloadALLPlugin);
        tolua_function(tolua_S,"loadALLPlugin",lua_anysdk_AgentManager_loadALLPlugin);
        tolua_function(tolua_S,"getUserPlugin",lua_anysdk_AgentManager_getUserPlugin);
        tolua_function(tolua_S,"init",lua_anysdk_AgentManager_init);
        tolua_function(tolua_S,"getAdsPlugin",lua_anysdk_AgentManager_getAdsPlugin);
        tolua_function(tolua_S,"getPushPlugin",lua_anysdk_AgentManager_getPushPlugin);
        tolua_function(tolua_S,"getSharePlugin",lua_anysdk_AgentManager_getSharePlugin);
        tolua_function(tolua_S,"getAnalyticsPlugin",lua_anysdk_AgentManager_getAnalyticsPlugin);
        tolua_function(tolua_S,"getChannelId",lua_anysdk_AgentManager_getChannelId);
        tolua_function(tolua_S,"end", lua_anysdk_AgentManager_end);
        tolua_function(tolua_S,"getInstance", lua_anysdk_AgentManager_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::AgentManager).name();
    g_luaType[typeName] = "ccanysdk.AgentManager";
    g_typeCast["AgentManager"] = "ccanysdk.AgentManager";
    return 1;
}

int lua_register_anysdk_ProtocolShare(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ccanysdk.ProtocolShare");
    tolua_cclass(tolua_S,"ProtocolShare","ccanysdk.ProtocolShare","",nullptr);

    tolua_beginmodule(tolua_S,"ProtocolShare");
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(anysdk::framework::ProtocolShare).name();
    g_luaType[typeName] = "ccanysdk.ProtocolShare";
    g_typeCast["ProtocolShare"] = "ccanysdk.ProtocolShare";
    return 1;
}

TOLUA_API int register_all_anysdk(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"anysdk",0);
	tolua_beginmodule(tolua_S,"anysdk");

	lua_register_anysdk_PluginProtocol(tolua_S);
	lua_register_anysdk_ProtocolUser(tolua_S);
	lua_register_anysdk_PluginFactory(tolua_S);
	lua_register_anysdk_ProtocolIAP(tolua_S);
	lua_register_anysdk_AgentManager(tolua_S);
	lua_register_anysdk_ProtocolSocial(tolua_S);
	lua_register_anysdk_ProtocolAnalytics(tolua_S);
	lua_register_anysdk_ProtocolAds(tolua_S);
	lua_register_anysdk_PluginManager(tolua_S);
	lua_register_anysdk_ProtocolPush(tolua_S);
    lua_register_anysdk_ProtocolShare(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

