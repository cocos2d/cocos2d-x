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

#include "CCLuaEngine.h"
#include "tolua++.h"

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
#include "tolua_fix.h"
}

#include "cocos2d.h"
#include "LuaCocos2d.h"
#include "CCArray.h"
#include "CCScheduler.h"

#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "Cocos2dxLuaLoader.h"
#endif

NS_CC_BEGIN

CCLuaEngine::~CCLuaEngine()
{
    lua_close(m_state);
}

bool CCLuaEngine::init(void)
{
    m_state = lua_open();
    luaL_openlibs(m_state);
    tolua_Cocos2d_open(m_state);
    tolua_prepare_ccobject_table(m_state);
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
    addLuaLoader(loader_Android);
#endif
    return true;
}

CCLuaEngine* CCLuaEngine::engine()
{
    CCLuaEngine* pEngine = new CCLuaEngine();
    pEngine->init();
    pEngine->autorelease();
    return pEngine;
}

void CCLuaEngine::removeCCObjectByID(int nLuaID)
{
    tolua_remove_ccobject_by_refid(m_state, nLuaID);
}

void CCLuaEngine::removeLuaHandler(int nHandler)
{
    tolua_remove_function_by_refid(m_state, nHandler);
}

void CCLuaEngine::addSearchPath(const char* path)
{
    lua_getglobal(m_state, "package");                              /* stack: package */
    lua_getfield(m_state, -1, "path");            /* get package.path, stack: package path */
    const char* cur_path =  lua_tostring(m_state, -1);
    lua_pop(m_state, 1);                                            /* stack: package */
    lua_pushfstring(m_state, "%s;%s/?.lua", cur_path, path);        /* stack: package newpath */
    lua_setfield(m_state, -2, "path");      /* package.path = newpath, stack: package */
    lua_pop(m_state, 1);                                            /* stack: - */
}

int CCLuaEngine::executeString(const char *codes)
{
	int nRet =	luaL_dostring(m_state, codes);
	lua_gc(m_state, LUA_GCCOLLECT, 0);

    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return nRet;
    }
    return 0;
}

int CCLuaEngine::executeScriptFile(const char* filename)
{
    int nRet = luaL_dofile(m_state, filename);
//    lua_gc(m_state, LUA_GCCOLLECT, 0);

    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return nRet;
    }
    return 0;
}

int	CCLuaEngine::executeGlobalFunction(const char* functionName)
{
    lua_getglobal(m_state, functionName);  /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", functionName);
        lua_pop(m_state, 1);
        return 0;
    }

    int error = lua_pcall(m_state, 0, 1, 0);         /* call function, stack: ret */
//    lua_gc(m_state, LUA_GCCOLLECT, 0);

    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));
        lua_pop(m_state, 1); // clean error message
        return 0;
    }

    // get return value
    if (!lua_isnumber(m_state, -1))
    {
        lua_pop(m_state, 1);
        return 0;
    }

    int ret = lua_tointeger(m_state, -1);
    lua_pop(m_state, 1);                                            /* stack: - */
    return ret;
}

int CCLuaEngine::executeFunctionByHandler(int nHandler, int numArgs)
{
    if (pushFunctionByHandler(nHandler))
    {
        if (numArgs > 0)
        {
            lua_insert(m_state, -(numArgs + 1));                        /* stack: ... func arg1 arg2 ... */
        }

        int error = 0;
        // try
        // {
            error = lua_pcall(m_state, numArgs, 1, 0);                  /* stack: ... ret */
        // }
        // catch (exception& e)
        // {
        //     CCLOG("[LUA ERROR] lua_pcall(%d) catch C++ exception: %s", nHandler, e.what());
        //     lua_settop(m_state, 0);
        //     return 0;
        // }
        // catch (...)
        // {
        //     CCLOG("[LUA ERROR] lua_pcall(%d) catch C++ unknown exception.", nHandler);
        //     lua_settop(m_state, 0);
        //     return 0;
        // }
        if (error)
        {
            CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));        /* stack: ... error */
            lua_pop(m_state, 1); // remove error message from stack
            return 0;
        }

        // get return value
        int ret = 0;
        if (lua_isnumber(m_state, -1))
        {
            ret = lua_tointeger(m_state, -1);
        }
        else if (lua_isboolean(m_state, -1))
        {
            ret = lua_toboolean(m_state, -1);
        }

        lua_pop(m_state, 1); // remove return value from stack
        return ret;
    }
    else
    {
        lua_pop(m_state, numArgs); // remove args from stack
        return 0;
    }
}

int CCLuaEngine::executeFunctionWithIntegerData(int nHandler, int data)
{
    lua_pushinteger(m_state, data);
    return executeFunctionByHandler(nHandler, 1);
}

int CCLuaEngine::executeFunctionWithFloatData(int nHandler, float data)
{
    lua_pushnumber(m_state, data);
    return executeFunctionByHandler(nHandler, 1);
}

int CCLuaEngine::executeFunctionWithBooleanData(int nHandler, bool data)
{
    lua_pushboolean(m_state, data);
    return executeFunctionByHandler(nHandler, 1);
}

int CCLuaEngine::executeFunctionWithCCObject(int nHandler, CCObject* pObject, const char* typeName)
{
    tolua_pushusertype_ccobject(m_state, pObject->m_uID, &pObject->m_nLuaID, pObject, typeName);
    return executeFunctionByHandler(nHandler, 1);
}

int CCLuaEngine::pushIntegerToLuaStack(int data)
{
    lua_pushinteger(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushFloatToLuaStack(int data)
{
    lua_pushnumber(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushBooleanToLuaStack(int data)
{
    lua_pushboolean(m_state, data);
    return lua_gettop(m_state);
}

int CCLuaEngine::pushCCObjectToLuaStack(CCObject* pObject, const char* typeName)
{
    tolua_pushusertype_ccobject(m_state, pObject->m_uID, &pObject->m_nLuaID, pObject, typeName);
    return lua_gettop(m_state);
}

// functions for excute touch event
int CCLuaEngine::executeTouchEvent(int nHandler, int eventType, CCTouch *pTouch)
{
    CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView());
    lua_pushinteger(m_state, eventType);
    lua_pushnumber(m_state, pt.x);
    lua_pushnumber(m_state, pt.y);
    return executeFunctionByHandler(nHandler, 3);
}

int CCLuaEngine::executeTouchesEvent(int nHandler, int eventType, CCSet *pTouches)
{
    lua_pushinteger(m_state, eventType);
    lua_newtable(m_state);

    CCDirector* pDirector = CCDirector::sharedDirector();
    CCSetIterator it = pTouches->begin();
    CCTouch* pTouch;
    int n = 1;
    while (it != pTouches->end())
    {
        pTouch = (CCTouch*)*it;
        CCPoint pt = pDirector->convertToGL(pTouch->locationInView());
        lua_pushnumber(m_state, pt.x);
        lua_rawseti(m_state, -2, n++);
        lua_pushnumber(m_state, pt.y);
        lua_rawseti(m_state, -2, n++);
        ++it;
    }

    return executeFunctionByHandler(nHandler, 2);
}

int CCLuaEngine::executeSchedule(int nHandler, ccTime dt)
{
    return executeFunctionWithFloatData(nHandler, dt);
}

void CCLuaEngine::addLuaLoader(lua_CFunction func)
{
    if (!func) return;

    // stack content after the invoking of the function
    // get loader table
    lua_getglobal(m_state, "package");                     // package
    lua_getfield(m_state, -1, "loaders");                  // package, loaders

    // insert loader into index 2
    lua_pushcfunction(m_state, func);                      // package, loaders, func
    for (int i = lua_objlen(m_state, -2) + 1; i > 2; --i)
    {
        lua_rawgeti(m_state, -2, i - 1);                   // package, loaders, func, function
                                                           // we call lua_rawgeti, so the loader table now is at -3
        lua_rawseti(m_state, -3, i);                       // package, loaders, func
    }
    lua_rawseti(m_state, -2, 2);                           // package, loaders

    // set loaders into package
    lua_setfield(m_state, -2, "loaders");                  // package

    lua_pop(m_state, 1);
}

bool CCLuaEngine::pushFunctionByHandler(int nHandler)
{
    lua_rawgeti(m_state, LUA_REGISTRYINDEX, nHandler);  /* stack: ... func */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", nHandler);
        lua_pop(m_state, 1);
        return false;
    }
    return true;
}

NS_CC_END
