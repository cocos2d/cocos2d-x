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
#include "tolua_fix.h"

extern "C" {
#include "lualib.h"
#include "lauxlib.h"
#include "lualoadexts.h"
}

#include "LuaCocos2d.h"
#include "LuaSimpleAudioEngine.h"
#include "LuaGameInterfaces.h"
#include "CCArray.h"
#include "CCTimer.h"

namespace cocos2d
{

CCSchedulerFuncEntry* CCSchedulerFuncEntry::entryWithFunctionRefID(int functionRefID, ccTime fInterval, bool bPaused)
{
    CCSchedulerFuncEntry* entry = new CCSchedulerFuncEntry();
    entry->initWithFunctionRefID(functionRefID, fInterval, bPaused);
    entry->autorelease();
    return entry;
}

bool CCSchedulerFuncEntry::initWithFunctionRefID(int functionRefID, ccTime fInterval, bool bPaused)
{
    m_timer = new CCTimer();
    m_timer->initWithScriptFunc(functionRefID, fInterval);
    m_timer->autorelease();
    m_timer->retain();
    m_functionRefID = functionRefID;
    m_paused = bPaused;
    CCLOG("[LUA] ADD function refID: %04d, add schedule entryID: %d", m_functionRefID, m_entryID);
    return true;
}

CCSchedulerFuncEntry::CCSchedulerFuncEntry(void)
: m_timer(NULL)
, m_functionRefID(0)
, m_paused(true)
, m_isMarkDeleted(false)
{
    static int entryIDCount = 0;
    ++entryIDCount;
    m_entryID = entryIDCount;
}

CCSchedulerFuncEntry::~CCSchedulerFuncEntry(void)
{
    m_timer->release();
    CCLuaEngine::sharedEngine()->removeLuaFunctionRef(m_functionRefID);
    CCLOG("[LUA] DEL function refID: %04d, remove schedule entryID: %d", m_functionRefID, m_entryID);
}

// ----------------------------


CCLuaEngine* CCLuaEngine::s_engine = NULL;

CCLuaEngine::CCLuaEngine()
{
    m_state = lua_open();
    luaL_openlibs(m_state);
    tolua_Cocos2d_open(m_state);
    tolua_SimpleAudioEngine_open(m_state);
    tolua_prepare_ccobject_table(m_state);
    tolua_LuaGameInterfaces_open(m_state);
    luax_loadexts(m_state);
}

CCLuaEngine::~CCLuaEngine()
{
    lua_close(m_state);
    s_engine = NULL;
}

CCLuaEngine* CCLuaEngine::sharedEngine()
{
    if (!s_engine)
    {
        s_engine = new CCLuaEngine();
    }
    return s_engine;
}

void CCLuaEngine::purgeSharedEngine()
{
    if (s_engine) delete s_engine;
}

// -------------------------------------------

void CCLuaEngine::removeCCObject(CCObject *object)
{
    tolua_remove_ccobject_by_refid(m_state, object->m_refID);
}

void CCLuaEngine::removeLuaFunctionRef(int functionRefID)
{
    tolua_remove_function_by_refid(m_state, functionRefID);
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

int	CCLuaEngine::executeGlobalFunction(const char* function_name)
{
    lua_getglobal(m_state, function_name);  /* query function by name, stack: function */
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] name '%s' does not represent a Lua function", function_name);
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

int CCLuaEngine::executeFunctionByRefID(int functionRefId, int numArgs)
{
    lua_pushstring(m_state, TOLUA_REFID_FUNC_MAPPING);
    lua_rawget(m_state, LUA_REGISTRYINDEX);                         /* stack: refid_func */
    lua_pushinteger(m_state, functionRefId);                        /* stack: refid_func refid */
    lua_rawget(m_state, -2);                                        /* stack: refid_func func */
    
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", functionRefId);
        lua_pop(m_state, 1);
        return 0;
    }
    
    if (numArgs > 0)
    {
        int lo = -2 - numArgs;
        while (lo <= -3)
        {
            tolua_pushvalue(m_state, lo);                           /* stack: refid_func func (...) */
            ++lo;
        }
    }
    
    int error = lua_pcall(m_state, numArgs, 1, 0);                  /* stack: refid_func ret */
    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));
        lua_pop(m_state, 2); // clean error message
        return 0;
    }
    
    // get return value
    if (!lua_isnumber(m_state, -1))
    {
        lua_pop(m_state, 2);
        return 0;
    }
    
    int ret = lua_tointeger(m_state, -1);
    lua_pop(m_state, 2);
    return ret;
}

// functions for excute touch event
int CCLuaEngine::executeTouchEvent(int functionRefId, CCTouch *pTouch)
{
    return false;
}

int CCLuaEngine::executeTouchesEvent(int functionRefId, CCSet *pTouches)
{
    return false;
}

int CCLuaEngine::executeSchedule(int functionRefID, ccTime dt)
{
    lua_pushnumber(m_state, dt);
    int ret = executeFunctionByRefID(functionRefID, 1);
    lua_pop(m_state, 1);
    return ret;
}

} // namespace cocos2d
