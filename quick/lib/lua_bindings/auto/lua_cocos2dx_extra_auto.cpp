#include "lua_cocos2dx_extra_auto.hpp"
#include "Native/CCNative.h"
#include "Crypto/CCCrypto.h"
#include "Network/CCNetwork.h"
#include "Network/CCHTTPRequest.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_extra_Native_openURL(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::extra::Native::openURL(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "openURL",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_openURL'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_showActivityIndicator(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::extra::Native::showActivityIndicator();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "showActivityIndicator",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_showActivityIndicator'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_hideActivityIndicator(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::extra::Native::hideActivityIndicator();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "hideActivityIndicator",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_hideActivityIndicator'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_getDeviceName(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        const std::string ret = cocos2d::extra::Native::getDeviceName();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getDeviceName",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_getDeviceName'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_vibrate(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::extra::Native::vibrate();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "vibrate",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_vibrate'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_getInputText(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        if(!ok)
            return 0;
        const std::string ret = cocos2d::extra::Native::getInputText(arg0, arg1, arg2);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInputText",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_getInputText'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_cancelAlert(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        cocos2d::extra::Native::cancelAlert();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "cancelAlert",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_cancelAlert'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_getOpenUDID(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        const std::string ret = cocos2d::extra::Native::getOpenUDID();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getOpenUDID",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_getOpenUDID'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Native_createAlert(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Native",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::extra::Native::createAlert(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createAlert",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Native_createAlert'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extra_Native_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Native)");
    return 0;
}

int lua_register_cocos2dx_extra_Native(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.extra::Native");
    tolua_cclass(tolua_S,"Native","cc.extra::Native","",nullptr);

    tolua_beginmodule(tolua_S,"Native");
        tolua_function(tolua_S,"openURL", lua_cocos2dx_extra_Native_openURL);
        tolua_function(tolua_S,"showActivityIndicator", lua_cocos2dx_extra_Native_showActivityIndicator);
        tolua_function(tolua_S,"hideActivityIndicator", lua_cocos2dx_extra_Native_hideActivityIndicator);
        tolua_function(tolua_S,"getDeviceName", lua_cocos2dx_extra_Native_getDeviceName);
        tolua_function(tolua_S,"vibrate", lua_cocos2dx_extra_Native_vibrate);
        tolua_function(tolua_S,"getInputText", lua_cocos2dx_extra_Native_getInputText);
        tolua_function(tolua_S,"cancelAlert", lua_cocos2dx_extra_Native_cancelAlert);
        tolua_function(tolua_S,"getOpenUDID", lua_cocos2dx_extra_Native_getOpenUDID);
        tolua_function(tolua_S,"createAlert", lua_cocos2dx_extra_Native_createAlert);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extra::Native).name();
    g_luaType[typeName] = "cc.extra::Native";
    g_typeCast["Native"] = "cc.extra::Native";
    return 1;
}

int lua_cocos2dx_extra_Crypto_MD5Lua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        bool arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_boolean(tolua_S, 3,&arg1);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::MD5Lua(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "MD5Lua",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_MD5Lua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_encodeBase64Lua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::encodeBase64Lua(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "encodeBase64Lua",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_encodeBase64Lua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_MD5FileLua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::MD5FileLua(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "MD5FileLua",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_MD5FileLua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_encryptAES256Lua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        const char* arg0;
        int arg1;
        const char* arg2;
        int arg3;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::encryptAES256Lua(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "encryptAES256Lua",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_encryptAES256Lua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_decodeBase64Lua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::decodeBase64Lua(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "decodeBase64Lua",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_decodeBase64Lua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_encryptXXTEALua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        const char* arg0;
        int arg1;
        const char* arg2;
        int arg3;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::encryptXXTEALua(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "encryptXXTEALua",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_encryptXXTEALua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_decryptAES256Lua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        const char* arg0;
        int arg1;
        const char* arg2;
        int arg3;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::decryptAES256Lua(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "decryptAES256Lua",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_decryptAES256Lua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_decodeBase64Len(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::decodeBase64Len(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "decodeBase64Len",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_decodeBase64Len'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_decryptXXTEALua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 4)
    {
        const char* arg0;
        int arg1;
        const char* arg2;
        int arg3;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::decryptXXTEALua(arg0, arg1, arg2, arg3);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "decryptXXTEALua",argc, 4);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_decryptXXTEALua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_MD5String(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        void* arg0;
        int arg1;
        #pragma warning NO CONVERSION TO NATIVE FOR void*;
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        const std::string ret = cocos2d::extra::Crypto::MD5String(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "MD5String",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_MD5String'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_getAES256KeyLength(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::getAES256KeyLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getAES256KeyLength",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_getAES256KeyLength'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Crypto_encodeBase64Len(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Crypto",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1);
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Crypto::encodeBase64Len(arg0, arg1);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "encodeBase64Len",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Crypto_encodeBase64Len'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extra_Crypto_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Crypto)");
    return 0;
}

int lua_register_cocos2dx_extra_Crypto(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.extra::Crypto");
    tolua_cclass(tolua_S,"Crypto","cc.extra::Crypto","",nullptr);

    tolua_beginmodule(tolua_S,"Crypto");
        tolua_function(tolua_S,"MD5Lua", lua_cocos2dx_extra_Crypto_MD5Lua);
        tolua_function(tolua_S,"encodeBase64Lua", lua_cocos2dx_extra_Crypto_encodeBase64Lua);
        tolua_function(tolua_S,"MD5FileLua", lua_cocos2dx_extra_Crypto_MD5FileLua);
        tolua_function(tolua_S,"encryptAES256Lua", lua_cocos2dx_extra_Crypto_encryptAES256Lua);
        tolua_function(tolua_S,"decodeBase64Lua", lua_cocos2dx_extra_Crypto_decodeBase64Lua);
        tolua_function(tolua_S,"encryptXXTEALua", lua_cocos2dx_extra_Crypto_encryptXXTEALua);
        tolua_function(tolua_S,"decryptAES256Lua", lua_cocos2dx_extra_Crypto_decryptAES256Lua);
        tolua_function(tolua_S,"decodeBase64Len", lua_cocos2dx_extra_Crypto_decodeBase64Len);
        tolua_function(tolua_S,"decryptXXTEALua", lua_cocos2dx_extra_Crypto_decryptXXTEALua);
        tolua_function(tolua_S,"MD5String", lua_cocos2dx_extra_Crypto_MD5String);
        tolua_function(tolua_S,"getAES256KeyLength", lua_cocos2dx_extra_Crypto_getAES256KeyLength);
        tolua_function(tolua_S,"encodeBase64Len", lua_cocos2dx_extra_Crypto_encodeBase64Len);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extra::Crypto).name();
    g_luaType[typeName] = "cc.extra::Crypto";
    g_typeCast["Crypto"] = "cc.extra::Crypto";
    return 1;
}

int lua_cocos2dx_extra_HTTPRequest_setCookieString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_setCookieString'", nullptr);
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
        cobj->setCookieString(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setCookieString",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_setCookieString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_setRequestUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_setRequestUrl'", nullptr);
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
        cobj->setRequestUrl(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setRequestUrl",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_setRequestUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_addFormContents(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_addFormContents'", nullptr);
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
        cobj->addFormContents(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addFormContents",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_addFormContents'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseStatusCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseStatusCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getResponseStatusCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseStatusCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseStatusCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_cancel(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_cancel'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cobj->cancel();
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "cancel",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_cancel'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseHeaders(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseHeaders'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::vector<std::string>& ret = cobj->getResponseHeaders();
        ccvector_std_string_to_luaval(tolua_S, ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseHeaders",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseHeaders'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseDataLength(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseDataLength'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getResponseDataLength();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseDataLength",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseDataLength'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseData'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        void* ret = cobj->getResponseData();
        #pragma warning NO CONVERSION FROM NATIVE FOR void*;
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseData",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string ret = cobj->getResponseString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_checkCURLState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_checkCURLState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->checkCURLState(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "checkCURLState",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_checkCURLState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_setAcceptEncoding(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_setAcceptEncoding'", nullptr);
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
        cobj->setAcceptEncoding(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setAcceptEncoding",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_setAcceptEncoding'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getDelegate(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getDelegate'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        cocos2d::extra::HTTPRequestDelegate* ret = cobj->getDelegate();
        object_to_luaval<cocos2d::extra::HTTPRequestDelegate>(tolua_S, "cc.extra::HTTPRequestDelegate",(cocos2d::extra::HTTPRequestDelegate*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getDelegate",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getDelegate'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_start(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_start'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        bool ret = cobj->start();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "start",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_start'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getErrorCode(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getErrorCode'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getErrorCode();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getErrorCode",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getErrorCode'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getState(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getState'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getState();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getState",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getState'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_saveResponseData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_saveResponseData'", nullptr);
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
        unsigned long ret = cobj->saveResponseData(arg0);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "saveResponseData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_saveResponseData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getCookieString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getCookieString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string ret = cobj->getCookieString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getCookieString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getCookieString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_update(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_update'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        double arg0;

        ok &= luaval_to_number(tolua_S, 2,&arg0);
        if(!ok)
            return 0;
        cobj->update(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "update",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_update'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseHeadersString(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseHeadersString'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string ret = cobj->getResponseHeadersString();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseHeadersString",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseHeadersString'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getErrorMessage(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getErrorMessage'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string ret = cobj->getErrorMessage();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getErrorMessage",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getErrorMessage'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getRequestUrl(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getRequestUrl'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        const std::string ret = cobj->getRequestUrl();
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getRequestUrl",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getRequestUrl'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_setTimeout(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_setTimeout'", nullptr);
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
        cobj->setTimeout(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setTimeout",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_setTimeout'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_addPOSTValue(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_addPOSTValue'", nullptr);
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
        cobj->addPOSTValue(arg0, arg1);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addPOSTValue",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_addPOSTValue'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_addRequestHeader(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_addRequestHeader'", nullptr);
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
        cobj->addRequestHeader(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addRequestHeader",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_addRequestHeader'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_setPOSTData(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_setPOSTData'", nullptr);
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
        cobj->setPOSTData(arg0);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "setPOSTData",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_setPOSTData'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_addFormFile(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_addFormFile'", nullptr);
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
        cobj->addFormFile(arg0, arg1);
        return 0;
    }
    if (argc == 3) 
    {
        const char* arg0;
        const char* arg1;
        const char* arg2;

        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();

        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();

        std::string arg2_tmp; ok &= luaval_to_std_string(tolua_S, 4, &arg2_tmp); arg2 = arg2_tmp.c_str();
        if(!ok)
            return 0;
        cobj->addFormFile(arg0, arg1, arg2);
        return 0;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "addFormFile",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_addFormFile'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_getResponseDataLua(lua_State* tolua_S)
{
    int argc = 0;
    cocos2d::extra::HTTPRequest* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (cocos2d::extra::HTTPRequest*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_extra_HTTPRequest_getResponseDataLua'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
            return 0;
        int ret = cobj->getResponseDataLua();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "getResponseDataLua",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_getResponseDataLua'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_extra_HTTPRequest_createWithUrlLua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::HTTPRequest",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        const char* arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::extra::HTTPRequest* ret = cocos2d::extra::HTTPRequest::createWithUrlLua(arg0, arg1);
        object_to_luaval<cocos2d::extra::HTTPRequest>(tolua_S, "cc.extra::HTTPRequest",(cocos2d::extra::HTTPRequest*)ret);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        const char* arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        if(!ok)
            return 0;
        cocos2d::extra::HTTPRequest* ret = cocos2d::extra::HTTPRequest::createWithUrlLua(arg0, arg1, arg2);
        object_to_luaval<cocos2d::extra::HTTPRequest>(tolua_S, "cc.extra::HTTPRequest",(cocos2d::extra::HTTPRequest*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createWithUrlLua",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_HTTPRequest_createWithUrlLua'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extra_HTTPRequest_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (HTTPRequest)");
    return 0;
}

int lua_register_cocos2dx_extra_HTTPRequest(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.extra::HTTPRequest");
    tolua_cclass(tolua_S,"HTTPRequest","cc.extra::HTTPRequest","cc.Ref",nullptr);

    tolua_beginmodule(tolua_S,"HTTPRequest");
        tolua_function(tolua_S,"setCookieString",lua_cocos2dx_extra_HTTPRequest_setCookieString);
        tolua_function(tolua_S,"setRequestUrl",lua_cocos2dx_extra_HTTPRequest_setRequestUrl);
        tolua_function(tolua_S,"addFormContents",lua_cocos2dx_extra_HTTPRequest_addFormContents);
        tolua_function(tolua_S,"getResponseStatusCode",lua_cocos2dx_extra_HTTPRequest_getResponseStatusCode);
        tolua_function(tolua_S,"cancel",lua_cocos2dx_extra_HTTPRequest_cancel);
        tolua_function(tolua_S,"getResponseHeaders",lua_cocos2dx_extra_HTTPRequest_getResponseHeaders);
        tolua_function(tolua_S,"getResponseDataLength",lua_cocos2dx_extra_HTTPRequest_getResponseDataLength);
        tolua_function(tolua_S,"getResponseData",lua_cocos2dx_extra_HTTPRequest_getResponseData);
        tolua_function(tolua_S,"getResponseString",lua_cocos2dx_extra_HTTPRequest_getResponseString);
        tolua_function(tolua_S,"checkCURLState",lua_cocos2dx_extra_HTTPRequest_checkCURLState);
        tolua_function(tolua_S,"setAcceptEncoding",lua_cocos2dx_extra_HTTPRequest_setAcceptEncoding);
        tolua_function(tolua_S,"getDelegate",lua_cocos2dx_extra_HTTPRequest_getDelegate);
        tolua_function(tolua_S,"start",lua_cocos2dx_extra_HTTPRequest_start);
        tolua_function(tolua_S,"getErrorCode",lua_cocos2dx_extra_HTTPRequest_getErrorCode);
        tolua_function(tolua_S,"getState",lua_cocos2dx_extra_HTTPRequest_getState);
        tolua_function(tolua_S,"saveResponseData",lua_cocos2dx_extra_HTTPRequest_saveResponseData);
        tolua_function(tolua_S,"getCookieString",lua_cocos2dx_extra_HTTPRequest_getCookieString);
        tolua_function(tolua_S,"update",lua_cocos2dx_extra_HTTPRequest_update);
        tolua_function(tolua_S,"getResponseHeadersString",lua_cocos2dx_extra_HTTPRequest_getResponseHeadersString);
        tolua_function(tolua_S,"getErrorMessage",lua_cocos2dx_extra_HTTPRequest_getErrorMessage);
        tolua_function(tolua_S,"getRequestUrl",lua_cocos2dx_extra_HTTPRequest_getRequestUrl);
        tolua_function(tolua_S,"setTimeout",lua_cocos2dx_extra_HTTPRequest_setTimeout);
        tolua_function(tolua_S,"addPOSTValue",lua_cocos2dx_extra_HTTPRequest_addPOSTValue);
        tolua_function(tolua_S,"addRequestHeader",lua_cocos2dx_extra_HTTPRequest_addRequestHeader);
        tolua_function(tolua_S,"setPOSTData",lua_cocos2dx_extra_HTTPRequest_setPOSTData);
        tolua_function(tolua_S,"addFormFile",lua_cocos2dx_extra_HTTPRequest_addFormFile);
        tolua_function(tolua_S,"getResponseDataLua",lua_cocos2dx_extra_HTTPRequest_getResponseDataLua);
        tolua_function(tolua_S,"createWithUrlLua", lua_cocos2dx_extra_HTTPRequest_createWithUrlLua);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extra::HTTPRequest).name();
    g_luaType[typeName] = "cc.extra::HTTPRequest";
    g_typeCast["HTTPRequest"] = "cc.extra::HTTPRequest";
    return 1;
}

int lua_cocos2dx_extra_Network_isInternetConnectionAvailable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        bool ret = cocos2d::extra::Network::isInternetConnectionAvailable();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "isInternetConnectionAvailable",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Network_isInternetConnectionAvailable'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Network_isHostNameReachable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        const char* arg0;
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        bool ret = cocos2d::extra::Network::isHostNameReachable(arg0);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "isHostNameReachable",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Network_isHostNameReachable'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Network_getInternetConnectionStatus(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        int ret = cocos2d::extra::Network::getInternetConnectionStatus();
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "getInternetConnectionStatus",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Network_getInternetConnectionStatus'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Network_createHTTPRequestLua(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        const char* arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        if(!ok)
            return 0;
        cocos2d::extra::HTTPRequest* ret = cocos2d::extra::Network::createHTTPRequestLua(arg0, arg1);
        object_to_luaval<cocos2d::extra::HTTPRequest>(tolua_S, "cc.extra::HTTPRequest",(cocos2d::extra::HTTPRequest*)ret);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        const char* arg1;
        int arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0);
        std::string arg1_tmp; ok &= luaval_to_std_string(tolua_S, 3, &arg1_tmp); arg1 = arg1_tmp.c_str();
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2);
        if(!ok)
            return 0;
        cocos2d::extra::HTTPRequest* ret = cocos2d::extra::Network::createHTTPRequestLua(arg0, arg1, arg2);
        object_to_luaval<cocos2d::extra::HTTPRequest>(tolua_S, "cc.extra::HTTPRequest",(cocos2d::extra::HTTPRequest*)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "createHTTPRequestLua",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Network_createHTTPRequestLua'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_extra_Network_isLocalWiFiAvailable(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"cc.extra::Network",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
            return 0;
        bool ret = cocos2d::extra::Network::isLocalWiFiAvailable();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d\n ", "isLocalWiFiAvailable",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_extra_Network_isLocalWiFiAvailable'.",&tolua_err);
#endif
    return 0;
}
static int lua_cocos2dx_extra_Network_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (Network)");
    return 0;
}

int lua_register_cocos2dx_extra_Network(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"cc.extra::Network");
    tolua_cclass(tolua_S,"Network","cc.extra::Network","",nullptr);

    tolua_beginmodule(tolua_S,"Network");
        tolua_function(tolua_S,"isInternetConnectionAvailable", lua_cocos2dx_extra_Network_isInternetConnectionAvailable);
        tolua_function(tolua_S,"isHostNameReachable", lua_cocos2dx_extra_Network_isHostNameReachable);
        tolua_function(tolua_S,"getInternetConnectionStatus", lua_cocos2dx_extra_Network_getInternetConnectionStatus);
        tolua_function(tolua_S,"createHTTPRequestLua", lua_cocos2dx_extra_Network_createHTTPRequestLua);
        tolua_function(tolua_S,"isLocalWiFiAvailable", lua_cocos2dx_extra_Network_isLocalWiFiAvailable);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(cocos2d::extra::Network).name();
    g_luaType[typeName] = "cc.extra::Network";
    g_typeCast["Network"] = "cc.extra::Network";
    return 1;
}
TOLUA_API int register_all_cocos2dx_extra(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_extra_HTTPRequest(tolua_S);
	lua_register_cocos2dx_extra_Network(tolua_S);
	lua_register_cocos2dx_extra_Crypto(tolua_S);
	lua_register_cocos2dx_extra_Native(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

