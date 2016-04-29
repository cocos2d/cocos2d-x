#include "lua_pluginx_manual_callback.h"
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolAds.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"
#include "lua_pluginx_basic_conversions.h"

using namespace std;
using namespace cocos2d::plugin;

static map<PluginProtocol*, LUA_FUNCTION> callbacks;

int lua_pluginx_protocols_PluginProtocol_setCallback(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::PluginProtocol* cobj = nullptr;
    
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_setCallback'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 1)
    {
        LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 2, 0);
        if(!callback)
            return 0;
        std::function<void (int, std::basic_string<char> &)> arg0 = [=](int ret, std::string& productInfo) {
            tolua_pushnumber(tolua_S, ret);
            tolua_pushstring(tolua_S, productInfo.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
        };
        if (dynamic_cast<ProtocolIAP*>(cobj)) {
            dynamic_cast<ProtocolIAP*>(cobj)->setCallback(arg0);
        } else if (dynamic_cast<ProtocolAds*>(cobj)) {
            dynamic_cast<ProtocolAds*>(cobj)->setCallback(arg0);
        } else if (dynamic_cast<ProtocolShare*>(cobj)) {
            dynamic_cast<ProtocolShare*>(cobj)->setCallback(arg0);
        } else if (dynamic_cast<ProtocolSocial*>(cobj)) {
            dynamic_cast<ProtocolSocial*>(cobj)->setCallback(arg0);
        } else if (dynamic_cast<ProtocolUser*>(cobj)) {
            dynamic_cast<ProtocolUser*>(cobj)->setCallback(arg0);
        } else {
            return 0;
        }
        if (callbacks.count(cobj) != 0) {
            LuaEngine::getInstance()->removeScriptHandler(callbacks[cobj]);
        }
        callbacks[cobj] = callback;
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCallback",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_setCallback'.",&tolua_err);
#endif
    
    return 0;
}

int lua_pluginx_protocols_PluginProtocol_getCallback(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_getCallback'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
        ok = LuaEngine::getInstance()->getLuaStack()->pushFunctionByHandler(callbacks[cobj]);
        if(!ok)
            return 0;
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCallback",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_getCallback'.",&tolua_err);
#endif
    
    return 0;
}

static void extendPluginProtocol(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.PluginProtocol");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setCallback", lua_pluginx_protocols_PluginProtocol_setCallback);
        tolua_function(tolua_S, "getCallback", lua_pluginx_protocols_PluginProtocol_getCallback);
    }
    lua_pop(tolua_S, 1);
}

int lua_pluginx_protocols_ProtocolIAP_payForProduct(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolIAP_payForProduct'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            TProductInfo arg0;
            ok &= pluginx::luaval_to_TProductInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 3, 0);
            cobj->payForProduct(arg0, [=](int ret, std::string& productInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, productInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            });
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            TProductInfo arg0;
            ok &= pluginx::luaval_to_TProductInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            cobj->payForProduct(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "payForProduct",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolIAP_payForProduct'.",&tolua_err);
#endif
    
    return 0;
}

static void extendProtocolIAP(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.ProtocolIAP");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "payForProduct", lua_pluginx_protocols_ProtocolIAP_payForProduct);
    }
    lua_pop(tolua_S, 1);
}

int lua_pluginx_protocols_ProtocolShare_share(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolShare_share'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            TShareInfo arg0;
            ok &= pluginx::luaval_to_TShareInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 3, 0);
            function<void(int, string&)> arg1 = [=](int ret, string& shareInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, shareInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            };
            cobj->share(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            TShareInfo arg0;
            ok &= pluginx::luaval_to_TShareInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            cobj->share(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "share",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolShare_share'.",&tolua_err);
#endif
    
    return 0;
}

static void extendProtocolShare(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.ProtocolShare");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "share", lua_pluginx_protocols_ProtocolShare_share);
    }
    lua_pop(tolua_S, 1);
}

int lua_pluginx_protocols_ProtocolSocial_submitScore(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolSocial_submitScore'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 3) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            
            if (!ok) { break; }
            long arg1;
            ok &= luaval_to_long(tolua_S, 3, &arg1);
            
            if (!ok) { break; }
            std::function<void (int, std::basic_string<char> &)> arg2;
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 4, 0);
            arg2 = [=](int ret, string& scoreInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, scoreInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            };
            
            if (!ok) { break; }
            cobj->submitScore(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            const char* arg0;
            std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
            
            if (!ok) { break; }
            long arg1;
            ok &= luaval_to_long(tolua_S, 3, &arg1);
            
            if (!ok) { break; }
            cobj->submitScore(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "submitScore",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolSocial_submitScore'.",&tolua_err);
#endif
    
    return 0;
}

int lua_pluginx_protocols_ProtocolSocial_unlockAchievement(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolSocial_unlockAchievement'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            cocos2d::plugin::TAchievementInfo arg0;
            ok &= pluginx::luaval_to_TAchievementInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            std::function<void (int, std::basic_string<char> &)> arg1;
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 3, 0);
            arg1 = [=](int ret, string& unlockInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, unlockInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            };
            
            if (!ok) { break; }
            cobj->unlockAchievement(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            cocos2d::plugin::TAchievementInfo arg0;
            ok &= pluginx::luaval_to_TAchievementInfo(tolua_S, 2, &arg0);
            
            if (!ok) { break; }
            cobj->unlockAchievement(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "unlockAchievement",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolSocial_unlockAchievement'.",&tolua_err);
#endif
    
    return 0;
}

static void extendProtocolSocial(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.ProtocolSocial");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "submitScore", lua_pluginx_protocols_ProtocolSocial_submitScore);
        tolua_function(tolua_S, "unlockAchievement", lua_pluginx_protocols_ProtocolSocial_unlockAchievement);
    }
    lua_pop(tolua_S, 1);
}

int lua_pluginx_protocols_ProtocolUser_login(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolUser_login'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::function<void (int, std::basic_string<char> &)> arg0;
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 2, 0);
            arg0 = [=](int ret, string& loginInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, loginInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            };
            
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
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolUser_login'.",&tolua_err);
#endif
    
    return 0;
}

int lua_pluginx_protocols_ProtocolUser_logout(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_ProtocolUser_logout'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            std::function<void (int, std::basic_string<char> &)> arg0;
            LUA_FUNCTION callback = toluafix_ref_function(tolua_S, 2, 0);
            arg0 = [=](int ret, string& logoutInfo) {
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, logoutInfo.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(callback, 2);
                LuaEngine::getInstance()->removeScriptHandler(callback);
            };
            
            if (!ok) { break; }
            cobj->logout(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 0) {
            cobj->logout();
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "logout",argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_ProtocolUser_logout'.",&tolua_err);
#endif
    
    return 0;
}

static void extendProtocolUser(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.ProtocolUser");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "login", lua_pluginx_protocols_ProtocolUser_login);
        tolua_function(tolua_S, "logout", lua_pluginx_protocols_ProtocolUser_logout);
    }
    lua_pop(tolua_S, 1);
}

int lua_pluginx_protocols_FacebookAgent_api(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_api'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 4)
    {
        std::string arg0;
        int arg1;
        cocos2d::plugin::FacebookAgent::FBInfo arg2;
        
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "plugin.FacebookAgent:api");
        
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "plugin.FacebookAgent:api");

        ok &= pluginx::luaval_to_FBInfo(tolua_S, 4, &arg2, "plugin.FacebookAgent:api");

        if(!ok)
            return 0;

#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,5,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 5, 0);

        cobj->api(arg0, arg1, arg2, [=](int ret, std::string& msg){
            tolua_pushnumber(tolua_S, ret);
            tolua_pushstring(tolua_S, msg.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        });

        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:api",argc, 4);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_api'.",&tolua_err);
#endif
    return 0;
}

int lua_pluginx_protocols_FacebookAgent_share(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_share'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::plugin::FacebookAgent::FBInfo arg0;

        ok &= pluginx::luaval_to_FBInfo(tolua_S, 2, &arg0, "plugin.FacebookAgent:share");
        if(!ok)
            return 0;

#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 3, 0);

        cobj->share(arg0, [=](int ret, std::string& msg){
            tolua_pushnumber(tolua_S, ret);
            tolua_pushstring(tolua_S, msg.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        });
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:share",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_share'.",&tolua_err);
#endif
    return 0;
}

int lua_pluginx_protocols_FacebookAgent_dialog(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_dialog'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::plugin::FacebookAgent::FBInfo arg0;

        ok &= pluginx::luaval_to_FBInfo(tolua_S, 2, &arg0, "plugin.FacebookAgent:dialog");
        if(!ok)
            return 0;
        auto iter = arg0.begin();
        for (; iter != arg0.end(); iter++)
        {
            CCLOG("key is %s, value is %s", iter->first.c_str(), iter->second.c_str());
        }

#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 3, 0);

        cobj->dialog(arg0, [=](int ret, std::string& msg){
            tolua_pushnumber(tolua_S, ret);
            tolua_pushstring(tolua_S, msg.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        });
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:dialog",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_dialog'.",&tolua_err);
#endif

    return 0;
}

int lua_pluginx_protocols_FacebookAgent_login(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::plugin::FacebookAgent* cobj = nullptr;
    bool ok = true;

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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_login'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 1) {
            if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err))
                ok = false;
            
            if (!ok) { break; }
            
            LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 2, 0);
            cobj->login([=](int ret, std::string& msg){
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, msg.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
                LuaEngine::getInstance()->removeScriptHandler(handler);
            });
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "plugin.FacebookAgent:login");
            
            if (!ok) { break; }
            if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
                ok = false;
            
            if (!ok) { break; }
            
            LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 3, 0);
            cobj->login(arg0, [=](int ret, std::string& msg){
                tolua_pushnumber(tolua_S, ret);
                tolua_pushstring(tolua_S, msg.c_str());
                LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
                LuaEngine::getInstance()->removeScriptHandler(handler);
            });
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:login",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_login'.",&tolua_err);
#endif

    return 0;
}

int lua_pluginx_protocols_FacebookAgent_appRequest(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_appRequest'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        cocos2d::plugin::FacebookAgent::FBInfo arg0;
        
        ok &= pluginx::luaval_to_FBInfo(tolua_S, 2, &arg0, "plugin.FacebookAgent:appRequest");
        if(!ok)
            return 0;
        
#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 3, 0);
        cobj->appRequest(arg0, [=](int ret, std::string& msg){
            tolua_pushnumber(tolua_S, ret);
            tolua_pushstring(tolua_S, msg.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        });
        
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:appRequest",argc, 2);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_appRequest'.",&tolua_err);
#endif
    
    return 0;
}

int lua_pluginx_protocols_FacebookAgent_logEvent(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_logEvent'", nullptr);
        return 0;
    }
#endif
    argc = lua_gettop(tolua_S)-1;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            cobj->logEvent(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 1) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            cobj->logEvent(arg0);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 2) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            cocos2d::plugin::FacebookAgent::FBInfo arg1;
            ok &= pluginx::luaval_to_FBInfo(tolua_S, 3, &arg1, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            cobj->logEvent(arg0, arg1);
            return 0;
        }
    }while(0);
    ok  = true;
    do{
        if (argc == 3) {
            std::string arg0;
            ok &= luaval_to_std_string(tolua_S, 2,&arg0, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            double arg1;
            ok &= luaval_to_number(tolua_S, 3,&arg1, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            cocos2d::plugin::FacebookAgent::FBInfo arg2;
            ok &= pluginx::luaval_to_FBInfo(tolua_S, 4, &arg2, "plugin.FacebookAgent:logEvent");
            
            if (!ok) { break; }
            cobj->logEvent(arg0, arg1, arg2);
            return 0;
        }
    }while(0);
    ok  = true;
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n",  "plugin.FacebookAgent:logEvent",argc, 3);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_logEvent'.",&tolua_err);
#endif
    
    return 0;
}

int lua_pluginx_protocols_FacebookAgent_webDialog(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_webDialog'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        cocos2d::plugin::FacebookAgent::FBInfo arg0;

        ok &= pluginx::luaval_to_FBInfo(tolua_S, 2, &arg0, "plugin.FacebookAgent:webDialog");
        if(!ok)
            return 0;
        
        auto iter = arg0.begin();
        for (; iter != arg0.end(); iter++)
        {
            CCLOG("key is %s, value is %s", iter->first.c_str(), iter->second.c_str());
        }

#if COCOS2D_DEBUG >= 1
        if (!toluafix_isfunction(tolua_S,3,"LUA_FUNCTION",0,&tolua_err))
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = toluafix_ref_function(tolua_S, 3, 0);

        cobj->webDialog(arg0, [=](int ret, std::string& msg){
            tolua_pushnumber(tolua_S, ret);
            tolua_pushstring(tolua_S, msg.c_str());
            LuaEngine::getInstance()->getLuaStack()->executeFunctionByHandler(handler, 2);
            LuaEngine::getInstance()->removeScriptHandler(handler);
        });
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:webDialog",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_webDialog'.",&tolua_err);
#endif

    return 0;
}

int lua_pluginx_protocols_FacebookAgent_logPurchase(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_logPurchase'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        float mount;
        std::string currency;
        cocos2d::plugin::FacebookAgent::FBInfo fbInfo;

#if COCOS2D_DEBUG >= 1
        if (!tolua_isnumber(tolua_S, 2, 0, &tolua_err) ||
            !tolua_isstring(tolua_S, 3, 0, &tolua_err))
        {
            goto tolua_lerror;
        }
#endif

        mount = lua_tonumber(tolua_S, 2);
        currency = tolua_tocppstring(tolua_S, 3, 0);

        ok &= pluginx::luaval_to_FBInfo(tolua_S, 4, &fbInfo, "plugin.FacebookAgent:logPurchase");
        if(!ok)
            return 0;

        cobj->logPurchase(mount, currency, fbInfo);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:logPurchase",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_logPurchase'.",&tolua_err);
#endif

    return 0;
}

int lua_pluginx_protocols_FacebookAgent_canPresentDialogWithParams(lua_State* tolua_S)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_FacebookAgent_canPresentDialogWithParams'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {

        cocos2d::plugin::FacebookAgent::FBInfo fbInfo;

        ok &= pluginx::luaval_to_FBInfo(tolua_S, 2, &fbInfo, "plugin.FacebookAgent:canPresentDialogWithParams");
        if(!ok)
            return 0;

        bool ret = cobj->canPresentDialogWithParams(fbInfo);

        tolua_pushboolean(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "plugin.FacebookAgent:canPresentDialogWithParams",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_canPresentDialogWithParams'.",&tolua_err);
#endif

    return 0;
}

int lua_pluginx_protocols_FacebookAgent_getInstance(lua_State* tolua_S)
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
            return 0;
        cocos2d::plugin::FacebookAgent* ret = cocos2d::plugin::FacebookAgent::getInstanceLua();
        object_to_luaval<cocos2d::plugin::FacebookAgent>(tolua_S, "plugin.FacebookAgent",(cocos2d::plugin::FacebookAgent*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "plugin.FacebookAgent:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_FacebookAgent_getInstance'.",&tolua_err);
#endif
    return 0;
}

static void extendFacebookAgent(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.FacebookAgent");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "api", lua_pluginx_protocols_FacebookAgent_api);
        tolua_function(tolua_S, "share", lua_pluginx_protocols_FacebookAgent_share);
        tolua_function(tolua_S, "dialog", lua_pluginx_protocols_FacebookAgent_dialog);
        tolua_function(tolua_S, "login", lua_pluginx_protocols_FacebookAgent_login);
        tolua_function(tolua_S, "appRequest", lua_pluginx_protocols_FacebookAgent_appRequest);
        tolua_function(tolua_S, "logEvent", lua_pluginx_protocols_FacebookAgent_logEvent);
        tolua_function(tolua_S, "webDialog", lua_pluginx_protocols_FacebookAgent_webDialog);
        tolua_function(tolua_S, "logPurchase", lua_pluginx_protocols_FacebookAgent_logPurchase);
        tolua_function(tolua_S, "canPresentDialogWithParams", lua_pluginx_protocols_FacebookAgent_canPresentDialogWithParams);
        tolua_function(tolua_S, "getInstance", lua_pluginx_protocols_FacebookAgent_getInstance);
    }
    lua_pop(tolua_S, 1);
}

int register_all_pluginx_manual_callback(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    extendPluginProtocol(tolua_S);
    extendProtocolIAP(tolua_S);
    extendProtocolShare(tolua_S);
    extendProtocolSocial(tolua_S);
    extendProtocolUser(tolua_S);
    extendFacebookAgent(tolua_S);
    return 0;
}
