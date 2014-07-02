
#include "lua_anysdk_manual.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "LuaScriptHandlerMgr.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

using namespace cocostudio;

void stdmap_string_key_iap_to_luaval(lua_State* L, const std::Map<std::string, anysdk::framework::ProtocolIAP*>* v)
{
    lua_newtable(L);
    
    if(nullptr == L)
        return;
    
    for (auto iter = v.begin(); iter != v.end(); ++iter)
    {
        std::string key = iter->first;
        anysdk::framework::ProtocolIAP* obj = iter->second;
        if (nullptr != obj)
        {
            std::string name = typeid(*obj).name();
            auto typeIter = g_luaType.find(name);
            if (g_luaType.end() != typeIter)
            {
                lua_pushstring(L, key);
                object_to_luaval<anysdk::framework::ProtocolIAP>(tolua_S,
                	"ccanysdk.ProtocolIAP",(anysdk::framework::ProtocolIAP*)ret);
                lua_rawset(L, -3);
            }
        }
    }
}

bool luaval_to_stdmap_string_key_string(lua_State* L, int lo, std::Map<std::string, std::string>* ret)
{
    if(nullptr == L || nullptr == ret || lua_gettop(L) < lo)
        return false;
    
    tolua_Error tolua_err;
    bool ok = true;
    if (!tolua_istable(L, lo, 0, &tolua_err))
    {
#if COCOS2D_DEBUG >=1
        luaval_to_native_err(L,"#ferror:",&tolua_err);
#endif
        ok = false;
    }
    
    if (ok)
    {
        std::string stringKey = "";
        std::string stringVal = "";
        lua_pushnil(L);                                             /* first key L: lotable ..... nil */
        while ( 0 != lua_next(L, lo ) )                             /* L: lotable ..... key value */
        {
            if (!lua_isstring(L, -2))
            {
                lua_pop(L, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                continue;
            }
            
            if (!lua_isstring(L, -1))
            {
                lua_pop(L, 1);
                continue;
            }
            
            luaval_to_std_string(L, -2, &stringKey);
            luaval_to_std_string(L, -1, &stringVal);
            ret->insert(stringKey, stringVal);
                
            lua_pop(L, 1);                                          /* L: lotable ..... key */
        }
    }
    
    return ok;
}

static int tolua_anysdk_AgentManager_getIAPPlugin(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    AgentManager* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"ccanysdk.AgentManager",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<AgentManager*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_anysdk_AgentManager_getIAPPlugin'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (0 == argc)
    {
    	std::map<std::string , ProtocolIAP*>* iaps = self->getIAPPlugin()
    	stdmap_string_key_iap_to_luaval(tolua_S, iaps);

        return 1;
    }
    
    CCLOG("'getIAPPlugin' function of AgentManager has wrong number of arguments: %d, was expecting %d\n", argc, 0);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getIAPPlugin'.",&tolua_err);
    return 0;
#endif
}

static void extendAgentManager(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ccanysdk.AgentManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"getIAPPlugin");
        lua_pushcfunction(tolua_S,tolua_anysdk_AgentManager_getIAPPlugin);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

static int tolua_anysdk_ProtocolIAP_payForProduct(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    ProtocolIAP* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ProtocolIAP*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_anysdk_ProtocolIAP_payForProduct'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
    	std::map<std::string, std::string> productInfo;
    	luaval_to_stdmap_string_key_string(tolua_S, 2, &productInfo);
    	self->payForProduct(productInfo);

        return 0;
    }
    
    CCLOG("'payForProduct' function of ProtocolIAP has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getIAPPlugin'.",&tolua_err);
    return 0;
#endif
}

static int tolua_anysdk_ProtocolIAP_setResultListener(lua_State* tolua_S)
{
    if (NULL == tolua_S)
        return 0;
    
    int argc = 0;
    ProtocolIAP* self = nullptr;
    
#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
	if (!tolua_isusertype(tolua_S,1,"ccanysdk.ProtocolIAP",0,&tolua_err)) goto tolua_lerror;
#endif
    
    self = static_cast<ProtocolIAP*>(tolua_tousertype(tolua_S,1,0));
    
#if COCOS2D_DEBUG >= 1
	if (nullptr == self) {
		tolua_error(tolua_S,"invalid 'self' in function 'tolua_anysdk_ProtocolIAP_setResultListener'\n", NULL);
		return 0;
	}
#endif
    
    argc = lua_gettop(tolua_S) - 1;
    
    if (1 == argc)
    {
    	int nFunction = 0;
    	luaval_to_int32(tolua_S, 2, &nFunction);

    	PayResultListenerLua *listener = new PayResultListenerLua()
    	listener->m_luaFunction = nFunction;
    	self->setResultListener(listener);

        return 0;
    }
    
    CCLOG("'setResultListener' function of ProtocolIAP has wrong number of arguments: %d, was expecting %d\n", argc, 1);
    return 0;
    
#if COCOS2D_DEBUG >= 1
tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'getIAPPlugin'.",&tolua_err);
    return 0;
#endif
}

static void extendProtocolIAP(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ccanysdk.ProtocolIAP");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        lua_pushstring(tolua_S,"payForProduct");
        lua_pushcfunction(tolua_S,tolua_anysdk_ProtocolIAP_payForProduct);
        lua_rawset(tolua_S,-3);
        lua_pushstring(tolua_S,"setResultListener");
        lua_pushcfunction(tolua_S,tolua_anysdk_ProtocolIAP_setResultListener);
        lua_rawset(tolua_S,-3);
    }
    lua_pop(tolua_S, 1);
}

int register_all_anysdk_manual(lua_State* L)
{
    if (nullptr == L)
        return 0;

    extendAgentManager(L);
    extendProtocolIAP(L);
    extendUser(L);
    extendSocial(L);
    extendAnalytics(L);
    extendAds(L);
    extendPush(L);
    
    return 0;
}
