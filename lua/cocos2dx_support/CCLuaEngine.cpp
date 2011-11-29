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

#include "LuaEngine.h"
#include "tolua++.h"
#include "tolua_fix.h"

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
#include "lualoadexts.h"
}

#include "LuaCocos2d.h"
#include "LuaSimpleAudioEngine.h"
#include "LuaGameInterfaces.h"

using namespace cocos2d;


LuaEngine* LuaEngine::s_engine = NULL;

LuaEngine::LuaEngine()
{
    m_state = lua_open();
    luaL_openlibs(m_state);
    tolua_Cocos2d_open(m_state);
    tolua_SimpleAudioEngine_open(m_state);
    tolua_prepare_ccobject_table(m_state);
    tolua_LuaGameInterfaces_open(m_state);
    luax_loadexts(m_state);
}

LuaEngine::~LuaEngine()
{
    lua_close(m_state);
    s_engine = NULL;
}

LuaEngine* LuaEngine::sharedEngine()
{
    if (!s_engine)
    {
        s_engine = new LuaEngine();
    }
    return s_engine;
}

void LuaEngine::purgeSharedEngine()
{
    if (s_engine) delete s_engine;
}

// -------------------------------------------

void LuaEngine::removeCCObject(CCObject *object)
{
    tolua_remove_ccobject_by_refid(m_state, object->m_refID);
}

void LuaEngine::removeFunctionByRefId(int refid)
{
//    CCLOG("LuaEngine::removeFunctionByRefId() - refid: %d", refid);
    tolua_remove_function_by_refid(m_state, refid);
}

void LuaEngine::addSearchPath(const char* path)
{
    lua_getglobal(m_state, "package");                              /* stack: package */
    lua_getfield(m_state, -1, "path");            /* get package.path, stack: package path */
    const char* cur_path =  lua_tostring(m_state, -1);
    lua_pop(m_state, 1);                                            /* stack: package */
    lua_pushfstring(m_state, "%s;%s/?.lua", cur_path, path);        /* stack: package newpath */
    lua_setfield(m_state, -2, "path");      /* package.path = newpath, stack: package */
    lua_pop(m_state, 1);                                            /* stack: - */
}

bool LuaEngine::executeScriptFile(const char* filename)
{
    int nRet = luaL_dofile(m_state, filename);
    lua_gc(m_state, LUA_GCCOLLECT, 0);
    
    if (nRet != 0)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return false;
    }
    return true;
}

int	LuaEngine::executeGlobalFunction(const char* function_name)
{
    lua_getglobal(m_state, function_name);  /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", function_name);
        lua_pop(m_state, 1);
        return 0;
    }
    
    int error = lua_pcall(m_state, 0, 1, 0);         /* call function, stack: ret */
    lua_gc(m_state, LUA_GCCOLLECT, 0);
    
    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));
        lua_pop(m_state, 1); // clean error message
        return 0;
    }
    
    // get return value
    if (!lua_isnumber(m_state, -1))
    {
        CCLOG("[LUA ERROR] '%s' return value is not a number", function_name);
        lua_pop(m_state, 1);
        return 0;
    }

    int ret = lua_tointeger(m_state, -1);
    lua_pop(m_state, 1);                                            /* stack: - */
    return ret;
}

int LuaEngine::executeFunctionByRefId(int functionRefId)
{
    lua_rawgeti(m_state, LUA_REGISTRYINDEX, functionRefId);         /* stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", functionRefId);
        lua_pop(m_state, 1);
        return 0;
    }

    int error = lua_pcall(m_state, 0, 1, 0);                        /* stack: ret */
    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));
        lua_pop(m_state, 1); // clean error message
        return 0;
    }
    
    // get return value
    if (!lua_isnumber(m_state, -1))
    {
        CCLOG("[LUA ERROR] function '%d' return value is not a number", functionRefId);
        lua_pop(m_state, 1);
        return 0;
    }
    
    int ret = lua_tointeger(m_state, -1);
    lua_pop(m_state, 1);
    return ret;
}

int LuaEngine::retainRefID(int refID)
{
    int r = ++m_refIDMap[refID];
    return r;
}

int LuaEngine::releaseRefID(int refID)
{
    std::map<int, int>::iterator it = m_refIDMap.find(refID);
    if (it == m_refIDMap.end()) return 0;
    
    --(it->second);
    if (it->second <= 0)
    {
        m_refIDMap.erase(it);
        return 0;
    }
    return it->second;
}

// functions for excute touch event
bool LuaEngine::executeTouchEvent(const char *pszFuncName, CCTouch *pTouch)
{
    return false;
}

bool LuaEngine::executeTouchesEvent(const char *pszFuncName, CCSet *pTouches)
{
    return false;
}

// functions for CCCallFuncX
bool LuaEngine::executeCallFunc(const char *pszFuncName)
{
    return false;
}

bool LuaEngine::executeCallFuncN(const char *pszFuncName, CCNode *pNode)
{
    return false;
}

bool LuaEngine::executeCallFuncND(const char *pszFuncName, CCNode *pNode, void *pData)
{
    return false;
}

bool LuaEngine::executeCallFunc0(const char *pszFuncName, CCObject *pObject)
{
    return false;
}

bool LuaEngine::executeSchedule(int refid, ccTime dt)
{
    lua_rawgeti(m_state, LUA_REGISTRYINDEX, refid);                         /* stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid %d invalid", refid);
        lua_pop(m_state, 1);
        return false;
    }
    
    lua_pushnumber(m_state, dt);                                            /* stack: function time */
    int error = lua_pcall(m_state, 1, 0, 0);                                /* stack: [error] */
    if (error)
    {
        CCLOG("[LUA ERROR] function %d, %s", refid, lua_tostring(m_state, -1));
        lua_pop(m_state, 1);
        return false;
    }
    return true;
}
