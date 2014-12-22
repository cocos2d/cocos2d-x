/*
** Lua binding: anysdk
** Generated automatically by tolua++-1.0.92 on Wed Jul  2 14:12:17 2014.
*/

/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/
// extern "C" {
#include "tolua_fix.h"
// }

#include <map>
#include <string>
#include "AgentManager.h"
#include "PluginManager.h"
#include "PluginFactory.h"
#include "AgentManager.h"
#include "PluginProtocol.h"
#include "ProtocolPush.h"
#include "PluginFactory.h"     
#include "ProtocolAds.h"     
#include "ProtocolShare.h"
#include "PluginManager.h"
#include "ProtocolAnalytics.h" 
#include "ProtocolSocial.h"
#include "PluginParam.h"      
#include "ProtocolIAP.h"     
#include "ProtocolUser.h"

#include "CCLuaEngine.h"

#include "anysdk_manual_bindings.h"
#include "cocos2d.h"

// #define ON_VERSION_2 1

#ifndef ON_VERSION_2
    #include "LuaBasicConversions.h"
#endif

/* Exported function */
TOLUA_API int  tolua_anysdk_manual_open (lua_State* tolua_S);

using namespace anysdk::framework;
USING_NS_CC;

// extern const char* cocos2dVersion();


/* method: share of class  setDebugMode */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolShare_setDebugMode
static int tolua_anysdk_ProtocolShare_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols share\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolShare",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolShare* self = (ProtocolShare*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: share of class  ProtocolShare */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolShare_share00
static int tolua_anysdk_ProtocolShare_share00(lua_State* tolua_S)
{
	CCLog("in function protocols share\n");
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
	if (
	 !tolua_isusertype(tolua_S,1,"ProtocolShare",0,&tolua_err) ||
	 !tolua_istable(tolua_S,2,0,&tolua_err)
	)
		goto tolua_lerror;
	else
#endif
	{
		ProtocolShare* self = (ProtocolShare*)  tolua_tousertype(tolua_S,1,0);
	#ifndef TOLUA_RELEASE
		if (!self) tolua_error(tolua_S,"invalid 'self' in function 'share'", NULL);
	#endif
		{
			TShareInfo strmap;
			lua_pushnil(tolua_S);
			while ( 0 != lua_next(tolua_S, 2 ) )                             /* L: lotable ..... key value */
            {
                if (!lua_isstring(tolua_S, -2))
                {
                    lua_pop(tolua_S, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                    continue;
                }
                if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
                {
                    lua_pop(tolua_S, 1);
                    continue;
                }
                std::string key = "";
                key = tolua_tocppstring(tolua_S, -2, NULL);
                std::string value = "";
                value = tolua_tocppstring(tolua_S, -1, NULL);
                CCLog("key: %s, value: %s.", key.c_str(), value.c_str());
                strmap.insert( StringMap::value_type(key, value) );
                lua_pop(tolua_S, 1);                                          /* L: lotable ..... key */
            }
            self->share(strmap);
		}
	}
	return 0;
#ifndef TOLUA_RELEASE
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'share'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

const char* version = cocos2dVersion();
char VERSION_X = version[10];

class ProtocolShareActionListener : public ShareResultListener
{
public:
    ProtocolShareActionListener():_handler(0)
    {
    }
    ~ProtocolShareActionListener()
    {
      // if (VERSION_X == '2')
      // {
      //     #define ON_VERSION_2 TRUE
      // }

      #ifdef ON_VERSION_2
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #else
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #endif
    }

    virtual void onShareResult(ShareResultCode ret, const char* msg)
    {
      #ifdef ON_VERSION_2
        CCLog("on action result: %d, msg: %s.", ret, msg);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #else
        CCLOG("on share result result: %d, msg: %s.", ret, msg);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #endif
    }

    static ProtocolShareActionListener* _instance;
    static ProtocolShareActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolShareActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    void setHandler(LUA_FUNCTION handler)
    {
        _handler = handler;
        CCLOG("_handler: %d.", (int)_handler);
    }
private:
    LUA_FUNCTION _handler;
};
ProtocolShareActionListener* ProtocolShareActionListener::_instance = NULL;

/* method: setResultListener of class  ProtocolShare */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolShare_setResultListener
static int tolua_anysdk_ProtocolShare_setResultListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolShare",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolShare* self = (ProtocolShare*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResultListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
#ifndef TOLUA_RELEASE
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));

        if (ProtocolShareActionListener::_instance != NULL)
        {
            return 0;
        }
        CCLog("will set push action listener:");
        ProtocolShareActionListener* listener = ProtocolShareActionListener::getInstance();
        listener->setHandler(handler);
        self->setResultListener(listener);

        CCLog("set listener end");

        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResultListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  ProtocolShare */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolShare_removeListener
static int tolua_anysdk_ProtocolShare_removeListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolShare",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolShare* self = (ProtocolShare*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
        if (ProtocolShareActionListener::_instance != NULL)
        {
            ProtocolShareActionListener::purge();
        }
        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolsShare(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolShare");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "share", tolua_anysdk_ProtocolShare_share00);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolShare_setDebugMode);
		    tolua_function(tolua_S,"setResultListener",tolua_anysdk_ProtocolShare_setResultListener);
		    tolua_function(tolua_S,"removeListener",tolua_anysdk_ProtocolShare_removeListener);
    }
    lua_pop(tolua_S, 1);
}

/* method: create of class  PluginParam */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginParam_create
static int tolua_anysdk_PluginParam_create(lua_State* tolua_S)
{
	CCLog("in function PluginParam create\n");
#ifndef TOLUA_RELEASE
	tolua_Error tolua_err;
#endif
	{
		int argc = lua_gettop(tolua_S)-1;
		CCLog("argc: %d.", argc);
		PluginParam* param = NULL;
		if (argc == 0){
			param = new PluginParam();
		}
		else if(argc == 1){
			if( tolua_isboolean(tolua_S,2,0,&tolua_err) )
			{
				bool temp = ((bool)  tolua_toboolean(tolua_S,2,true));
				param = new PluginParam(temp);
			}
      else if( lua_type(tolua_S, 2) == LUA_TNUMBER ) 
			{
				double arg1 = (double)tolua_tonumber(tolua_S, 2, 0);
	            float argf = (float)arg1;
	            int argi = (int)arg1;
	            float temp = argf - (float)argi;

	            if ( temp > 0.000001){
	                param = new PluginParam((float)argf);
	            }
	            else{
	                param = new PluginParam((int)argi);
	            }
			}
			else if(tolua_isstring(tolua_S, 2, 0, &tolua_err))
	        {
	            std::string arg1 = (std::string)tolua_tostring(tolua_S, 2, 0);
	            const char* temp = arg1.c_str();
	            param = new PluginParam(temp);
	        }
	        else if (tolua_istable(tolua_S, 2, 0, &tolua_err))
	        {
	        	CCLOG("is table");
	            StringMap strmap;
	            lua_pushnil(tolua_S);                                            /* first key L: lotable ..... nil */
	            while ( 0 != lua_next(tolua_S, 2 ) )                             /* L: lotable ..... key value */
	            {
	                if (!lua_isstring(tolua_S, -2))
	                {
	                    lua_pop(tolua_S, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
	                    continue;
	                }
	                if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
	                {
	                    lua_pop(tolua_S, 1);
	                    continue;
	                }
	                std::string key = "";
	                key = tolua_tocppstring(tolua_S, -2, NULL);;
	                std::string value = "";
	                value = tolua_tocppstring(tolua_S, -1, NULL);
	                strmap.insert( StringMap::value_type(key, value) );
	                CCLog("key: %s, value: %s.", key.c_str(), value.c_str());
	                lua_pop(tolua_S, 1);                                          /* L: lotable ..... key */
	            }
	            param = new PluginParam(strmap);
	            CCLOG("end");
	        }
		}
		tolua_pushusertype(tolua_S,(void*)param,"PluginParam");
	}
	return 1;
#ifndef TOLUA_RELEASE
	tolua_lerror:
	tolua_error(tolua_S,"#ferror in function 'create'.",&tolua_err);
	return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getMapValue of class  PluginParam */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginParam_getMapValue
static int tolua_anysdk_PluginParam_getMapValue(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginParam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginParam* self = (PluginParam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getMapValue'", NULL);
#endif
  {
  	typedef std::map<std::string, PluginParam*> StringMap;
    StringMap strmap = self->getMapValue();
    StringMap::iterator iter;
    lua_newtable(tolua_S);
    if (NULL != tolua_S)
    {
        for ( iter = strmap.begin(); iter != strmap.end(); ++iter)
        {
            std::string key = iter->first;
            PluginParam* value = iter->second;
            lua_pushstring(tolua_S, key.c_str());
            tolua_pushusertype(tolua_S,(void*)value,"PluginParam");
            lua_rawset(tolua_S, -3);
        }
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getMapValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: getStrMapValue of class  PluginParam */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginParam_getStrMapValue
static int tolua_anysdk_PluginParam_getStrMapValue(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginParam",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginParam* self = (PluginParam*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getStrMapValue'", NULL);
#endif
  {
	typedef std::map<std::string, std::string> StringMap;
    StringMap strmap = self->getStrMapValue();
    StringMap::iterator iter;
    lua_newtable(tolua_S);
    if (NULL != tolua_S)
    {
        for ( iter = strmap.begin(); iter != strmap.end(); ++iter)
        {
            std::string key = iter->first;
            std::string value = iter->second;
            lua_pushstring(tolua_S, key.c_str());
            lua_pushstring(tolua_S, value.c_str());
            lua_rawset(tolua_S, -3);
        }
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getStrMapValue'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendPluginParam(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "PluginParam");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "create", tolua_anysdk_PluginParam_create);
        tolua_function(tolua_S, "getMapValue", tolua_anysdk_PluginParam_getMapValue);
        tolua_function(tolua_S, "getStrMapValue", tolua_anysdk_PluginParam_getStrMapValue);
    }
    lua_pop(tolua_S, 1);
}

/* method: getIAPPlugin of class  PluginParam */
#ifndef TOLUA_DISABLE_tolua_anysdk_AgentManager_getIAPPlugin
static int tolua_anysdk_AgentManager_getIAPPlugin(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"AgentManager",0,&tolua_err) ||
     !tolua_isnoobj(tolua_S,2,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  AgentManager* self = (AgentManager*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'getIAPPlugin'", NULL);
#endif
  {
  	typedef std::map<std::string, ProtocolIAP*> StringMap;
    StringMap *strmap = self->getIAPPlugin();
    StringMap::iterator iter;
    lua_newtable(tolua_S);
    if (NULL != tolua_S)
    {
        for ( iter = strmap->begin(); iter != strmap->end(); ++iter)
        {
            std::string key = iter->first;
            ProtocolIAP* value = iter->second;
            lua_pushstring(tolua_S, key.c_str());
            tolua_pushusertype(tolua_S,(void*)value,"ProtocolIAP");
            lua_rawset(tolua_S, -3);
        }
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'getIAPPlugin'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendAgentManager(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "AgentManager");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "getIAPPlugin", tolua_anysdk_AgentManager_getIAPPlugin);
    }
    lua_pop(tolua_S, 1);
}

/* method: callFuncWithParam of class  PluginProtocol */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginProtocol_callFuncWithParam
static int tolua_anysdk_PluginProtocol_callFuncWithParam(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginProtocol",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginProtocol* self = (PluginProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'callFuncWithParam'", NULL);
#endif
  {
  	int argc = lua_gettop(tolua_S)-1;
  	CCLog("argc: %d.", argc);
    if(argc == 0){
      CCLog("error param number in callFuncWithParam.");
      return 0;
  	}
    else if (argc == 1)
    {
      std::string arg1 = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* temp = arg1.c_str();
      self->callFuncWithParam(temp, NULL);
      return 0;
    }
    else
    {
      std::string temp = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* arg1 = temp.c_str();
      std::vector<PluginParam*> params;
      if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
      {
        CCLog("is not usertable");

        for (int i = 2; i <= argc; ++i)
        {
            PluginParam* param = (PluginParam*)tolua_tousertype(tolua_S,i+1,0);
            CCLog("param:%s.", param->getStringValue());
            params.push_back(param);
        }
      }
      else
      {
        size_t len = lua_objlen(tolua_S, 3);
        CCLog("is usertable: %d.", len);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 3);
            
            if (lua_isnil(tolua_S, -1) || !lua_isuserdata(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }

            PluginParam* param = static_cast<PluginParam*>(tolua_tousertype(tolua_S, -1, NULL) );
            if (NULL != param)
            {
                CCLog("param: %d", param->getIntValue());
                params.push_back(param);
            }
            else{
                CCLog("param is null");
            }
            lua_pop(tolua_S, 1);
        }
      }
      self->callFuncWithParam(arg1, params);
      return 0;
    }
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'callFuncWithParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: callStringFuncWithParam of class  PluginProtocol */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginProtocol_callStringFuncWithParam
static int tolua_anysdk_PluginProtocol_callStringFuncWithParam(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginProtocol",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginProtocol* self = (PluginProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'callStringFuncWithParam'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if(argc == 0){
      CCLog("error param number in callStringFuncWithParam.");
      return 0;
    }
    else if (argc == 1)
    {
      std::string arg1 = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* temp = arg1.c_str();
      self->callStringFuncWithParam(temp, NULL);
      return 0;
    }
    else
    {
      std::string temp = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* arg1 = temp.c_str();
      std::vector<PluginParam*> params;
      if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
      {
        CCLog("is not usertable");

        for (int i = 2; i <= argc; ++i)
        {
            PluginParam* param = (PluginParam*)tolua_tousertype(tolua_S,i+1,0);
            CCLog("param:%s.", param->getStringValue());
            params.push_back(param);
        }
      }
      else
      {
        size_t len = lua_objlen(tolua_S, 3);
        CCLog("is usertable: %d.", len);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 3);
            
            if (lua_isnil(tolua_S, -1) || !lua_isuserdata(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }

            PluginParam* param = static_cast<PluginParam*>(tolua_tousertype(tolua_S, -1, NULL) );
            if (NULL != param)
            {
                CCLog("param: %d", param->getIntValue());
                params.push_back(param);
            }
            else{
                CCLog("param is null");
            }
            lua_pop(tolua_S, 1);
        }
      }
      self->callStringFuncWithParam(arg1, params);
      return 0;
    }
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'callStringFuncWithParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: callIntFuncWithParam of class  PluginProtocol */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginProtocol_callIntFuncWithParam
static int tolua_anysdk_PluginProtocol_callIntFuncWithParam(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginProtocol",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginProtocol* self = (PluginProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'callIntFuncWithParam'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if(argc == 0){
      CCLog("error param number in callIntFuncWithParam.");
      return 0;
    }
    else if (argc == 1)
    {
      std::string arg1 = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* temp = arg1.c_str();
      self->callIntFuncWithParam(temp, NULL);
      return 0;
    }
    else
    {
      std::string temp = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* arg1 = temp.c_str();
      std::vector<PluginParam*> params;
      if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
      {
        CCLog("is not usertable");

        for (int i = 2; i <= argc; ++i)
        {
            PluginParam* param = (PluginParam*)tolua_tousertype(tolua_S,i+1,0);
            CCLog("param:%s.", param->getStringValue());
            params.push_back(param);
        }
      }
      else
      {
        size_t len = lua_objlen(tolua_S, 3);
        CCLog("is usertable: %d.", len);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 3);
            
            if (lua_isnil(tolua_S, -1) || !lua_isuserdata(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }

            PluginParam* param = static_cast<PluginParam*>(tolua_tousertype(tolua_S, -1, NULL) );
            if (NULL != param)
            {
                CCLog("param: %d", param->getIntValue());
                params.push_back(param);
            }
            else{
                CCLog("param is null");
            }
            lua_pop(tolua_S, 1);
        }
      }
      self->callIntFuncWithParam(arg1, params);
      return 0;
    }
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'callIntFuncWithParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: callBoolFuncWithParam of class  PluginProtocol */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginProtocol_callBoolFuncWithParam
static int tolua_anysdk_PluginProtocol_callBoolFuncWithParam(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginProtocol",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginProtocol* self = (PluginProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'callBoolFuncWithParam'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if(argc == 0){
      CCLog("error param number in callBoolFuncWithParam.");
      return 0;
    }
    else if (argc == 1)
    {
      std::string arg1 = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* temp = arg1.c_str();
      self->callBoolFuncWithParam(temp, NULL);
      return 0;
    }
    else
    {
      std::string temp = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* arg1 = temp.c_str();
      std::vector<PluginParam*> params;
      if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
      {
        CCLog("is not usertable");

        for (int i = 2; i <= argc; ++i)
        {
            PluginParam* param = (PluginParam*)tolua_tousertype(tolua_S,i+1,0);
            CCLog("param:%s.", param->getStringValue());
            params.push_back(param);
        }
      }
      else
      {
        size_t len = lua_objlen(tolua_S, 3);
        CCLog("is usertable: %d.", len);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 3);
            
            if (lua_isnil(tolua_S, -1) || !lua_isuserdata(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }

            PluginParam* param = static_cast<PluginParam*>(tolua_tousertype(tolua_S, -1, NULL) );
            if (NULL != param)
            {
                CCLog("param: %d", param->getIntValue());
                params.push_back(param);
            }
            else{
                CCLog("param is null");
            }
            lua_pop(tolua_S, 1);
        }
      }
      self->callBoolFuncWithParam(arg1, params);
      return 0;
    }
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'callBoolFuncWithParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: callFloatFuncWithParam of class  PluginProtocol */
#ifndef TOLUA_DISABLE_tolua_anysdk_PluginProtocol_callFloatFuncWithParam
static int tolua_anysdk_PluginProtocol_callFloatFuncWithParam(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"PluginProtocol",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  PluginProtocol* self = (PluginProtocol*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'callFloatFuncWithParam'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if(argc == 0){
      CCLog("error param number in callFloatFuncWithParam.");
      return 0;
    }
    else if (argc == 1)
    {
      std::string arg1 = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* temp = arg1.c_str();
      self->callFloatFuncWithParam(temp, NULL);
      return 0;
    }
    else
    {
      std::string temp = (std::string)tolua_tostring(tolua_S, 2, 0);
      const char* arg1 = temp.c_str();
      std::vector<PluginParam*> params;
      if (!tolua_istable(tolua_S, 3, 0, &tolua_err))
      {
        CCLog("is not usertable");

        for (int i = 2; i <= argc; ++i)
        {
            PluginParam* param = (PluginParam*)tolua_tousertype(tolua_S,i+1,0);
            CCLog("param:%s.", param->getStringValue());
            params.push_back(param);
        }
      }
      else
      {
        size_t len = lua_objlen(tolua_S, 3);
        CCLog("is usertable: %d.", len);
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 3);
            
            if (lua_isnil(tolua_S, -1) || !lua_isuserdata(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }

            PluginParam* param = static_cast<PluginParam*>(tolua_tousertype(tolua_S, -1, NULL) );
            if (NULL != param)
            {
                CCLog("param: %d", param->getIntValue());
                params.push_back(param);
            }
            else{
                CCLog("param is null");
            }
            lua_pop(tolua_S, 1);
        }
      }
      self->callFloatFuncWithParam(arg1, params);
      return 0;
    }
  }
 }
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'callFloatFuncWithParam'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendPluginProtocol(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "PluginProtocol");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "callFuncWithParam", tolua_anysdk_PluginProtocol_callFuncWithParam);
        tolua_function(tolua_S, "callStringFuncWithParam", tolua_anysdk_PluginProtocol_callStringFuncWithParam);
        tolua_function(tolua_S, "callIntFuncWithParam", tolua_anysdk_PluginProtocol_callIntFuncWithParam);
        tolua_function(tolua_S, "callBoolFuncWithParam", tolua_anysdk_PluginProtocol_callBoolFuncWithParam);
        tolua_function(tolua_S, "callFloatFuncWithParam", tolua_anysdk_PluginProtocol_callFloatFuncWithParam);
    }
    lua_pop(tolua_S, 1);
}

/* method: setDebugMode of class  ProtocolAnalytics */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolAnalytics_setDebugMode
static int tolua_anysdk_ProtocolAnalytics_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols analytics\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolAnalytics",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolAnalytics* self = (ProtocolAnalytics*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: logEvent of class  ProtocolAnalytics */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolAnalytics_logEvent
static int tolua_anysdk_ProtocolAnalytics_logEvent(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolAnalytics",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolAnalytics* self = (ProtocolAnalytics*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'logEvent'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    if (argc == 0)
    {
      CCLog("error params count of function logEvent.");
      return 0;
    }
    std::string temp = (std::string)tolua_tostring(tolua_S, 2, 0);
    const char* arg1 = temp.c_str();
      CCLog("logevent, argc: %d, arg1: %s", argc, arg1);
    if (argc == 1)
    {
      self->logEvent(arg1, NULL);
      return 0;
    }
    if (argc == 2)
    {
      LogEventParamMap strmap;
      lua_pushnil(tolua_S);
      while ( 0 != lua_next(tolua_S, 3 ) )                             /* L: lotable ..... key value */
      {
          if (!lua_isstring(tolua_S, -2))
          {
              lua_pop(tolua_S, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
              continue;
          }
          if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
          {
              lua_pop(tolua_S, 1);
              continue;
          }
          std::string key = "";
          key = tolua_tocppstring(tolua_S, -2, NULL);
          std::string value = "";
          value = tolua_tocppstring(tolua_S, -1, NULL);
          CCLog("key: %s, value: %s.", key.c_str(), value.c_str());
          strmap.insert( LogEventParamMap::value_type(key, value) );
          lua_pop(tolua_S, 1);                                          /* L: lotable ..... key */
      }
      self->logEvent(arg1, &strmap);
    }
  }
}
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'logEvent'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolAnalytics(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolAnalytics");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "logEvent", tolua_anysdk_ProtocolAnalytics_logEvent);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolAnalytics_setDebugMode);
    }
    lua_pop(tolua_S, 1);
}

/* method: setDebugMode of class  ProtocolIAP */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolIAP_setDebugMode
static int tolua_anysdk_ProtocolIAP_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols iap\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolIAP",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolIAP* self = (ProtocolIAP*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: payForProduct of class  ProtocolIAP */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolIAP_payForProduct
static int tolua_anysdk_ProtocolIAP_payForProduct(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolIAP",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolIAP* self = (ProtocolIAP*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'payForProduct'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("pay argc: %d.", argc);
    if (argc == 1)
    { 
      TProductInfo strmap;
      lua_pushnil(tolua_S);
      while ( 0 != lua_next(tolua_S, 2 ) )                             /* L: lotable ..... key value */
      {
          if (!lua_isstring(tolua_S, -2))
          {
              lua_pop(tolua_S, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
              continue;
          }
          if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
          {
              lua_pop(tolua_S, 1);
              continue;
          }
          std::string key = "";
          key = tolua_tocppstring(tolua_S, -2, NULL);
          std::string value = "";
          value = tolua_tocppstring(tolua_S, -1, NULL);
          CCLog("key: %s, value: %s.", key.c_str(), value.c_str());
          strmap.insert( StringMap::value_type(key, value) );
          lua_pop(tolua_S, 1);                                          /* L: lotable ..... key */
      }
      self->payForProduct(strmap);
      return 0;
    }
    CCLog("error params count of function payForProduct.");
  }
}
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'payForProduct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

class ProtocolIAPActionListener : public PayResultListener
{
public:
    ProtocolIAPActionListener():_handler(0)
    {
    }
    ~ProtocolIAPActionListener()
    {
      #ifdef ON_VERSION_2
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #else
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #endif
    }

    virtual void onPayResult(PayResultCode ret, const char* msg, TProductInfo info)
    {
      #ifdef ON_VERSION_2
        CCLog("on action result: %d, msg: %s.", ret, msg);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushstring(tolua_S, (const char *)msg);
        lua_newtable(tolua_S);
        TProductInfo::iterator iter= info.begin();
        if (NULL != tolua_S)
        {
            for (; iter != info.end(); ++iter)
            {
                std::string key = iter->first;
                std::string value = iter->second;
                lua_pushstring(tolua_S, key.c_str());
                lua_pushstring(tolua_S, value.c_str());
                lua_rawset(tolua_S, -3);
            }
        }
        stack->executeFunctionByHandler(_handler, 3);
        stack->clean();
      #else
        CCLOG("on pay result: %d, msg: %s.", ret, msg);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)ret);
        tolua_pushstring(tolua_S, (const char *)msg);
        lua_newtable(tolua_S);
        if (nullptr != tolua_S)
        {
            for (auto iter = info.begin(); iter != info.end(); ++iter)
            {
                std::string key = iter->first;
                std::string value = iter->second;
                lua_pushstring(tolua_S, key.c_str());
                lua_pushstring(tolua_S, value.c_str());
                lua_rawset(tolua_S, -3);
            }
        }
        stack->executeFunctionByHandler(_handler, 3);
        stack->clean();
      #endif
    }

    static ProtocolIAPActionListener* _instance;
    static ProtocolIAPActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolIAPActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    void setHandler(LUA_FUNCTION handler)
    {
        _handler = handler;
        CCLOG("_handler: %d.", (int)_handler);
    }
private:
    LUA_FUNCTION _handler;
};
ProtocolIAPActionListener* ProtocolIAPActionListener::_instance = NULL;

/* method: setResultListener of class  ProtocolIAP */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolIAP_setResultListener
static int tolua_anysdk_ProtocolIAP_setResultListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolIAP",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolIAP* self = (ProtocolIAP*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setResultListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
#ifndef TOLUA_RELEASE
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));

        if (ProtocolIAPActionListener::_instance != NULL)
        {
            return 0;
        }
        CCLog("will set iap pay listener:");
        ProtocolIAPActionListener* listener = ProtocolIAPActionListener::getInstance();
        listener->setHandler(handler);
        self->setResultListener(listener);

        CCLog("set listener end");

        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setResultListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  ProtocolIAP */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolIAP_removeListener
static int tolua_anysdk_ProtocolIAP_removeListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolIAP",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolIAP* self = (ProtocolIAP*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
        if (ProtocolIAPActionListener::_instance != NULL)
        {
            ProtocolIAPActionListener::purge();
        }
        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolIAP(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolIAP");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "payForProduct", tolua_anysdk_ProtocolIAP_payForProduct);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolIAP_setDebugMode);
        tolua_function(tolua_S, "setResultListener", tolua_anysdk_ProtocolIAP_setResultListener);
        tolua_function(tolua_S, "removeListener", tolua_anysdk_ProtocolIAP_removeListener);
    }
    lua_pop(tolua_S, 1);
}

/* method: setTags of class  ProtocolPush */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolPush_setTags
static int tolua_anysdk_ProtocolPush_setTags(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolPush",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolPush* self = (ProtocolPush*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setTags'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
      if( tolua_istable(tolua_S, 2, 0, &tolua_err) )
      {
        size_t len = lua_objlen(tolua_S, 2);
        CCLog("is usertable, len: %d.", len);
        std::list<std::string> tags;
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 2);
            
            if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }
            std::string param = (std::string)tolua_tostring(tolua_S, -1, 0);
            if (param.length())
            {
                CCLog("param: %s", param.c_str());
                tags.push_back(param);
            }
            lua_pop(tolua_S, 1);
        }
        self->setTags(tags);
        return 0;
      }
      CCLog("error param type.");
      return 0;
    }
    CCLog("error params count of function setTags.");
  }
}
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'payForProduct'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDebugMode of class  ProtocolPush */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolPush_setDebugMode
static int tolua_anysdk_ProtocolPush_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols push\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolPush",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolPush* self = (ProtocolPush*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: delTags of class  ProtocolPush */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolPush_delTags
static int tolua_anysdk_ProtocolPush_delTags(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolPush",0,&tolua_err) 
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolPush* self = (ProtocolPush*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'delTags'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
      if( tolua_istable(tolua_S, 2, 0, &tolua_err) )
      {
        size_t len = lua_objlen(tolua_S, 2);
        CCLog("is usertable, len: %d.", len);
        std::list<std::string> tags;
        for (int i = 0; i < len; i++)
        {
            lua_pushnumber(tolua_S, i + 1);
            lua_gettable(tolua_S, 2);
            
            if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
            {
                lua_pop(tolua_S, 1);
                continue;
            }

            std::string param = (std::string)tolua_tostring(tolua_S, -1, 0);
            if (param.length())
            {
                CCLog("param: %s", param.c_str());
                tags.push_back(param);
            }
            lua_pop(tolua_S, 1);
        }
        self->delTags(tags);
        return 0;
      }
      CCLog("error param type.");
      return 0;
    }
    CCLog("error params count of function delTags.");
  }
}
 return 0;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'delTags'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

class ProtocolPushActionListener : public PushActionListener
{
public:
    ProtocolPushActionListener():_handler(0)
    {
    }
    ~ProtocolPushActionListener()
    {
      #ifdef ON_VERSION_2
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #else
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #endif
    }

    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
    {
      #ifdef ON_VERSION_2
        CCLog("on action result: %d, msg: %s.", code, msg);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushusertype(tolua_S,(void*)pPlugin,"ProtocolPush");
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 3);
        stack->clean();
      #else
        CCLOG("on pay result: %d, msg: %s.", code, msg);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        object_to_luaval<ProtocolPush>(tolua_S, "anysdk.ProtocolPush",(ProtocolPush*)pPlugin);
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 3);
        stack->clean();
      #endif
    }

    static ProtocolPushActionListener* _instance;
    static ProtocolPushActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolPushActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    void setHandler(LUA_FUNCTION handler)
    {
        _handler = handler;
        CCLOG("_handler: %d.", (int)_handler);
    }
private:
    LUA_FUNCTION _handler;
};
ProtocolPushActionListener* ProtocolPushActionListener::_instance = NULL;

/* method: setActionListener of class  ProtocolPush */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolPush_setActionListener
static int tolua_anysdk_ProtocolPush_setActionListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolPush",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolPush* self = (ProtocolPush*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
#ifndef TOLUA_RELEASE
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));

        if (ProtocolPushActionListener::_instance != NULL)
        {
            return 0;
        }
        CCLog("will set push action listener:");
        ProtocolPushActionListener* listener = ProtocolPushActionListener::getInstance();
        listener->setHandler(handler);
        self->setActionListener(listener);

        CCLog("set listener end");

        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  ProtocolPush */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolPush_removeListener
static int tolua_anysdk_ProtocolPush_removeListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolPush",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolPush* self = (ProtocolPush*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
        if (ProtocolPushActionListener::_instance != NULL)
        {
            ProtocolPushActionListener::purge();
        }
        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolPush(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolPush");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setTags", tolua_anysdk_ProtocolPush_setTags);
        tolua_function(tolua_S, "delTags", tolua_anysdk_ProtocolPush_delTags);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolPush_setDebugMode);
        tolua_function(tolua_S, "setActionListener", tolua_anysdk_ProtocolPush_setActionListener);
        tolua_function(tolua_S, "removeListener", tolua_anysdk_ProtocolPush_removeListener);
    }
    lua_pop(tolua_S, 1);
}

/* method: unlockAchievement of class  ProtocolSocial */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolSocial_unlockAchievement
static int tolua_anysdk_ProtocolSocial_unlockAchievement(lua_State* tolua_S)
{
  CCLog("in function protocols unlockAchievement\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolSocial",0,&tolua_err) ||
   !tolua_istable(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolSocial* self = (ProtocolSocial*)  tolua_tousertype(tolua_S,1,0);
  #ifndef TOLUA_RELEASE
    if (!self) tolua_error(tolua_S,"invalid 'self' in function 'unlockAchievement'", NULL);
  #endif
    {
      TAchievementInfo strmap;
      lua_pushnil(tolua_S);
      while ( 0 != lua_next(tolua_S, 2 ) )                             /* L: lotable ..... key value */
            {
                if (!lua_isstring(tolua_S, -2))
                {
                    lua_pop(tolua_S, 1);                                      /* removes 'value'; keep 'key' for next iteration*/
                    continue;
                }
                if (lua_isnil(tolua_S, -1) || !lua_isstring(tolua_S, -1))
                {
                    lua_pop(tolua_S, 1);
                    continue;
                }
                std::string key = "";
                key = tolua_tocppstring(tolua_S, -2, NULL);
                std::string value = "";
                value = tolua_tocppstring(tolua_S, -1, NULL);
                CCLog("key: %s, value: %s.", key.c_str(), value.c_str());
                strmap.insert( StringMap::value_type(key, value) );
                lua_pop(tolua_S, 1);                                          /* L: lotable ..... key */
            }
            self->unlockAchievement(strmap);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'unlockAchievement'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

class ProtocolSocialActionListener : public SocialListener
{
public:
    ProtocolSocialActionListener():_handler(0)
    {
    }
    ~ProtocolSocialActionListener()
    {
      #ifdef ON_VERSION_2
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #else
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #endif
    }

    virtual void onSocialResult(SocialRetCode code, const char* msg)
    {
      #ifdef ON_VERSION_2
        CCLog("on action result: %d, msg: %s.", code, msg);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #else
        CCLOG("on social result: %d, msg: %s.", code, msg);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #endif
    }

    static ProtocolSocialActionListener* _instance;
    static ProtocolSocialActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolSocialActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    void setHandler(LUA_FUNCTION handler)
    {
        _handler = handler;
        CCLOG("_handler: %d.", (int)_handler);
    }
private:
    LUA_FUNCTION _handler;
};
ProtocolSocialActionListener* ProtocolSocialActionListener::_instance = NULL;

/* method: setDebugMode of class  ProtocolSocial */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolSocial_setDebugMode
static int tolua_anysdk_ProtocolSocial_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols social\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolSocial",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolSocial* self = (ProtocolSocial*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setListener of class  ProtocolSocial */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolSocial_setListener
static int tolua_anysdk_ProtocolSocial_setListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolSocial",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolSocial* self = (ProtocolSocial*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
#ifndef TOLUA_RELEASE
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));

        if (ProtocolSocialActionListener::_instance != NULL)
        {
            return 0;
        }
        CCLog("will set ads listener:");
        ProtocolSocialActionListener* listener = ProtocolSocialActionListener::getInstance();
        listener->setHandler(handler);
        self->setListener(listener);

        CCLog("set listener end");

        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  ProtocolSocial */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolSocial_removeListener
static int tolua_anysdk_ProtocolSocial_removeListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolSocial",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolSocial* self = (ProtocolSocial*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
        if (ProtocolSocialActionListener::_instance != NULL)
        {
            ProtocolSocialActionListener::purge();
        }
        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolSocial(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolSocial");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "unlockAchievement", tolua_anysdk_ProtocolSocial_unlockAchievement);
        tolua_function(tolua_S, "setListener", tolua_anysdk_ProtocolSocial_setListener);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolSocial_setDebugMode);
        tolua_function(tolua_S, "removeListener", tolua_anysdk_ProtocolSocial_removeListener);
    }
    lua_pop(tolua_S, 1);
}

class ProtocolUserActionListener : public UserActionListener
{
public:
    ProtocolUserActionListener():_handler(0)
    {
    }
    ~ProtocolUserActionListener()
    {
      #ifdef ON_VERSION_2
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #else
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #endif
    }

    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
    {
      #ifdef ON_VERSION_2
        CCLog("on action result: %d, msg: %s.", code, msg);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushusertype(tolua_S,(void*)pPlugin,"ProtocolUser");
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 3);
        stack->clean();
      #else
        CCLOG("on action result: %d, msg: %s.", code, msg);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        object_to_luaval<ProtocolUser>(tolua_S, "anysdk.ProtocolUser",(ProtocolUser*)pPlugin);
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 3);
        stack->clean();
      #endif
    }

    static ProtocolUserActionListener* _instance;
    static ProtocolUserActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolUserActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    void setHandler(LUA_FUNCTION handler)
    {
        _handler = handler;
        CCLOG("_handler: %d.", (int)_handler);
    }
private:
    LUA_FUNCTION _handler;
};
ProtocolUserActionListener* ProtocolUserActionListener::_instance = NULL;

/* method: setDebugMode of class  ProtocolUser */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolUser_setDebugMode
static int tolua_anysdk_ProtocolUser_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols user\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolUser",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolUser* self = (ProtocolUser*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setActionListener of class  ProtocolUser */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolUser_setActionListener
static int tolua_anysdk_ProtocolUser_setActionListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolUser",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolUser* self = (ProtocolUser*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setActionListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
#ifndef TOLUA_RELEASE
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));

        if (ProtocolUserActionListener::_instance != NULL)
        {
            return 0;
        }
        CCLog("will set ads listener:");
        ProtocolUserActionListener* listener = ProtocolUserActionListener::getInstance();
        listener->setHandler(handler);
        self->setActionListener(listener);

        CCLog("set listener end");

        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setActionListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: removeListener of class  ProtocolUser */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolUser_removeListener
static int tolua_anysdk_ProtocolUser_removeListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolUser",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolUser* self = (ProtocolUser*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
        if (ProtocolUserActionListener::_instance != NULL)
        {
            ProtocolUserActionListener::purge();
        }
        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolUser(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolUser");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setActionListener", tolua_anysdk_ProtocolUser_setActionListener);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolUser_setDebugMode);
        tolua_function(tolua_S, "removeListener", tolua_anysdk_ProtocolUser_removeListener);
    }
    lua_pop(tolua_S, 1);
}

class ProtocolAdsListener : public AdsListener
{
public:
    ProtocolAdsListener():_handler(0)
    {
    }
    ~ProtocolAdsListener()
    {
      #ifdef ON_VERSION_2
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #else
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        stack->removeScriptHandler(_handler);
      #endif
    }

    virtual void onAdsResult(AdsResultCode code, const char* msg)
    {
      #ifdef ON_VERSION_2
        CCLOG("on ads result: %d, msg: %s.", code, msg);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #else
        CCLOG("on ads result: %d, msg: %s.", code, msg);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        tolua_pushnumber(tolua_S, (lua_Number)code);
        tolua_pushstring(tolua_S, (const char *)msg);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #endif
    }
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points)
    {
      #ifdef ON_VERSION_2
        CCLOG("onPlayerGetPoints. points: %d.", points);
        CCLuaStack* stack = CCLuaEngine::defaultEngine()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        // object_to_luaval<ProtocolAds>(tolua_S, "anysdk.ProtocolAds",(ProtocolAds*)pAdsPlugin);
        tolua_pushusertype(tolua_S,(void*)pAdsPlugin,"ProtocolAds");
        tolua_pushnumber(tolua_S, (lua_Number)points);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #else
        CCLOG("onPlayerGetPoints. points: %d.", points);
        LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
        lua_State* tolua_S    = stack->getLuaState();
        object_to_luaval<ProtocolAds>(tolua_S, "anysdk.ProtocolAds",(ProtocolAds*)pAdsPlugin);
        tolua_pushnumber(tolua_S, (lua_Number)points);
        stack->executeFunctionByHandler(_handler, 2);
        stack->clean();
      #endif
    }

    static ProtocolAdsListener* _instance;
    static ProtocolAdsListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolAdsListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }

    void setHandler(LUA_FUNCTION handler)
    {
        _handler = handler;
        CCLOG("_handler: %d.", (int)_handler);
    }
private:
    LUA_FUNCTION _handler;
};
ProtocolAdsListener* ProtocolAdsListener::_instance = NULL;

/* method: setAdsListener of class  ProtocolAds */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolAds_setAdsListener
static int tolua_anysdk_ProtocolAds_setAdsListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolAds",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolAds* self = (ProtocolAds*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setAdsListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
#ifndef TOLUA_RELEASE
        if (!toluafix_isfunction(tolua_S,2,"LUA_FUNCTION",0,&tolua_err) )
        {
            goto tolua_lerror;
        }
#endif
        LUA_FUNCTION handler = (  toluafix_ref_function(tolua_S,2,0));

        if (ProtocolAdsListener::_instance != NULL)
        {
            return 0;
        }
        CCLog("will set ads listener:");
        ProtocolAdsListener* listener = ProtocolAdsListener::getInstance();
        listener->setHandler(handler);
        self->setAdsListener(listener);

        CCLog("set listener end");

        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'setAdsListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

/* method: setDebugMode of class  ProtocolAds */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolAds_setDebugMode
static int tolua_anysdk_ProtocolAds_setDebugMode(lua_State* tolua_S)
{
  CCLog("in function protocols ads\n");
#ifndef TOLUA_RELEASE
  tolua_Error tolua_err;
  if (
   !tolua_isusertype(tolua_S,1,"ProtocolAds",0,&tolua_err) ||
   !tolua_isboolean(tolua_S,2,0,&tolua_err)
  )
    goto tolua_lerror;
  else
#endif
  {
    ProtocolAds* self = (ProtocolAds*)  tolua_tousertype(tolua_S,1,0);
  bool bDebug = ((bool)  tolua_toboolean(tolua_S,2,0));
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'setDebugMode'", NULL);
#endif
    {
      self->setDebugMode(bDebug);
    }
  }
  return 0;
#ifndef TOLUA_RELEASE
  tolua_lerror:
  tolua_error(tolua_S,"#ferror in function 'setDebugMode'.",&tolua_err);
  return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE


/* method: removeListener of class  ProtocolAds */
#ifndef TOLUA_DISABLE_tolua_anysdk_ProtocolAds_removeListener
static int tolua_anysdk_ProtocolAds_removeListener(lua_State* tolua_S)
{
#ifndef TOLUA_RELEASE
 tolua_Error tolua_err;
 if (
     !tolua_isusertype(tolua_S,1,"ProtocolAds",0,&tolua_err)
 )
  goto tolua_lerror;
 else
#endif
 {
  ProtocolAds* self = (ProtocolAds*)  tolua_tousertype(tolua_S,1,0);
#ifndef TOLUA_RELEASE
  if (!self) tolua_error(tolua_S,"invalid 'self' in function 'removeListener'", NULL);
#endif
  {
    int argc = lua_gettop(tolua_S)-1;
    CCLog("argc: %d.", argc);
    if (argc == 1)
    {
        if (ProtocolAdsListener::_instance != NULL)
        {
            ProtocolAdsListener::purge();
        }
        return 0;
    }
  }
 }
 return 1;
#ifndef TOLUA_RELEASE
 tolua_lerror:
 tolua_error(tolua_S,"#ferror in function 'removeListener'.",&tolua_err);
 return 0;
#endif
}
#endif //#ifndef TOLUA_DISABLE

static void extendProtocolAds(lua_State* tolua_S)
{
    lua_pushstring(tolua_S, "ProtocolAds");
    lua_rawget(tolua_S, LUA_REGISTRYINDEX);
    if (lua_istable(tolua_S,-1))
    {
        tolua_function(tolua_S, "setAdsListener", tolua_anysdk_ProtocolAds_setAdsListener);
        tolua_function(tolua_S, "removeListener", tolua_anysdk_ProtocolAds_removeListener);
        tolua_function(tolua_S, "setDebugMode", tolua_anysdk_ProtocolAds_setDebugMode);
    }
    lua_pop(tolua_S, 1);
}

/* Open function */
TOLUA_API int tolua_anysdk_manual_open (lua_State* tolua_S)
{
	extendProtocolsShare(tolua_S);
	extendPluginParam(tolua_S);
	extendAgentManager(tolua_S);
  extendPluginProtocol(tolua_S);
  extendProtocolAnalytics(tolua_S);
  extendProtocolIAP(tolua_S);
  extendProtocolAds(tolua_S);
  extendProtocolPush(tolua_S);
  extendProtocolSocial(tolua_S);
  extendProtocolUser(tolua_S);
	return 0;
}

#if defined(LUA_VERSION_NUM) && LUA_VERSION_NUM >= 501
 TOLUA_API int luaopen_anysdk_manual (lua_State* tolua_S) {
 return tolua_anysdk_manual_open(tolua_S);
};
#endif
