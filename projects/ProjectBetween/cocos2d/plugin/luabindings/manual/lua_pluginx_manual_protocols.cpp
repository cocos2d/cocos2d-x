#include "lua_pluginx_manual_protocols.h"
#include "PluginProtocol.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"

using namespace std;
using namespace cocos2d::plugin;

int lua_pluginx_protocols_PluginProtocol_callFuncWithParam_base(lua_State* tolua_S, function<int(PluginProtocol*, const char*, vector<PluginParam*>&)> callback)
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
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_pluginx_protocols_PluginProtocol_callFuncWithParam'", nullptr);
        return 0;
    }
#endif
    
    argc = lua_gettop(tolua_S)-1;
    if (argc >= 1)
    {
        const char* arg0;
        std::vector<PluginParam*> arg1;
        
        std::string arg0_tmp; ok &= luaval_to_std_string(tolua_S, 2, &arg0_tmp); arg0 = arg0_tmp.c_str();
        if(!ok)
            return 0;
        
        for (int i = 3; i <= argc + 1; i++) {
            Value ret;
            luaval_to_ccvalue(tolua_S, i, &ret);
            switch (ret.getType()) {
                case cocos2d::Value::Type::INTEGER:
                    arg1.push_back(new PluginParam(ret.asInt()));
                    break;
                case cocos2d::Value::Type::FLOAT:
                    arg1.push_back(new PluginParam(ret.asFloat()));
                    break;
                case cocos2d::Value::Type::BOOLEAN:
                    arg1.push_back(new PluginParam(ret.asBool()));
                    break;
                case cocos2d::Value::Type::STRING:
                    arg1.push_back(new PluginParam(ret.asString().c_str()));
                    break;
                case cocos2d::Value::Type::MAP:
                {
                    auto vm = ret.asValueMap();
                    StringMap sm;
                    for (auto e : vm) {
                        sm[e.first] = e.second.asString();
                    }
                    arg1.push_back(new PluginParam(sm));
                    break;
                }
                default:
                    break;
            }
        }
        int ret = callback(cobj, arg0, arg1);
        for (auto e : arg1) {
            delete e;
        }
        return ret;
    }
    CCLOG("%s has wrong number of arguments: %d, was expecting %d \n", "callFuncWithParam",argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_pluginx_protocols_PluginProtocol_callFuncWithParam'.",&tolua_err);
#endif
    
    return 0;
}

int lua_pluginx_protocols_PluginProtocol_callFuncWithParam(lua_State* tolua_S)
{
    return lua_pluginx_protocols_PluginProtocol_callFuncWithParam_base(tolua_S, [](PluginProtocol* cobj, const char* arg0, vector<PluginParam*>& arg1) {
        cobj->callFuncWithParam(arg0, arg1);
        return 0;
    });
}

int lua_pluginx_protocols_PluginProtocol_callStringFuncWithParam(lua_State* tolua_S)
{
    return lua_pluginx_protocols_PluginProtocol_callFuncWithParam_base(tolua_S, [=](PluginProtocol* cobj, const char* arg0, vector<PluginParam*>& arg1) {
        string ret = cobj->callStringFuncWithParam(arg0, arg1);
        tolua_pushcppstring(tolua_S,ret);
        return 1;
    });
}

int lua_pluginx_protocols_PluginProtocol_callIntFuncWithParam(lua_State* tolua_S)
{
    return lua_pluginx_protocols_PluginProtocol_callFuncWithParam_base(tolua_S, [=](PluginProtocol* cobj, const char* arg0, vector<PluginParam*>& arg1) {
        int ret = cobj->callIntFuncWithParam(arg0, arg1);
        tolua_pushnumber(tolua_S, ret);
        return 1;
    });
}

int lua_pluginx_protocols_PluginProtocol_callFloatFuncWithParam(lua_State* tolua_S)
{
    return lua_pluginx_protocols_PluginProtocol_callFuncWithParam_base(tolua_S, [=](PluginProtocol* cobj, const char* arg0, vector<PluginParam*>& arg1) {
        float ret = cobj->callFloatFuncWithParam(arg0, arg1);
        tolua_pushnumber(tolua_S, ret);
        return 1;
    });
}

int lua_pluginx_protocols_PluginProtocol_callBoolFuncWithParam(lua_State* tolua_S)
{
    return lua_pluginx_protocols_PluginProtocol_callFuncWithParam_base(tolua_S, [=](PluginProtocol* cobj, const char* arg0, vector<PluginParam*>& arg1) {
        bool ret = cobj->callBoolFuncWithParam(arg0, arg1);
        tolua_pushboolean(tolua_S, ret);
        return 1;
    });
}

static void extendPluginProtoco(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "plugin.PluginProtocol");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "callFuncWithParam", lua_pluginx_protocols_PluginProtocol_callFuncWithParam);
        tolua_function(tolua_S, "callStringFuncWithParam", lua_pluginx_protocols_PluginProtocol_callStringFuncWithParam);
        tolua_function(tolua_S, "callIntFuncWithParam", lua_pluginx_protocols_PluginProtocol_callIntFuncWithParam);
        tolua_function(tolua_S, "callFloatFuncWithParam", lua_pluginx_protocols_PluginProtocol_callFloatFuncWithParam);
        tolua_function(tolua_S, "callBoolFuncWithParam", lua_pluginx_protocols_PluginProtocol_callBoolFuncWithParam);
    }
    lua_pop(tolua_S, 1);
}

int register_all_pluginx_manual_protocols(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    extendPluginProtoco(tolua_S);
    return 0;
}
