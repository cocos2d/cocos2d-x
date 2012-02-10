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

#include "cocos2d.h"
#include "LuaCocos2d.h"
#include "CCArray.h"
#include "CCScheduler.h"

namespace cocos2d
{

CCSchedulerFuncEntry* CCSchedulerFuncEntry::entryWithFuncID(int uFuncID, ccTime fInterval, bool bPaused)
{
    CCSchedulerFuncEntry* pEntry = new CCSchedulerFuncEntry();
    pEntry->initWithuFuncID(uFuncID, fInterval, bPaused);
    pEntry->autorelease();
    return pEntry;
}

bool CCSchedulerFuncEntry::initWithuFuncID(int uFuncID, ccTime fInterval, bool bPaused)
{
    m_pTimer = new CCTimer();
    m_pTimer->initWithScriptFuncID(uFuncID, fInterval);
    m_pTimer->autorelease();
    m_pTimer->retain();
    m_uFuncID = uFuncID;
    m_bPaused = bPaused;
    LUALOG("[LUA] ADD function refID: %04d, add schedule entryID: %d", m_uFuncID, m_entryID);
    return true;
}

CCSchedulerFuncEntry::CCSchedulerFuncEntry(void)
: m_pTimer(NULL)
, m_uFuncID(0)
, m_bPaused(true)
, m_bMarkedForDeletion(false)
{
    static unsigned int uEntryCount = 0;
    m_uEntryID = ++uEntryCount;
}

CCSchedulerFuncEntry::~CCSchedulerFuncEntry(void)
{
    m_pTimer->release();
    CCLuaEngine::sharedEngine()->removeLuaFuncID(m_uFuncID);
    LUALOG("[LUA] DEL function refID: %04d, remove schedule entryID: %d", m_uFuncID, m_entryID);
}

// ----------------------------


CCLuaEngine* CCLuaEngine::s_engine = NULL;

CCLuaEngine::CCLuaEngine()
{
    m_state = lua_open();
    luaL_openlibs(m_state);
    tolua_Cocos2d_open(m_state);
    tolua_prepare_ccobject_table(m_state);
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

void CCLuaEngine::removeCCObjectByID(unsigned int uLuaID)
{
    tolua_remove_ccobject_by_refid(m_state, uLuaID);
}

void CCLuaEngine::removeLuaFuncID(int uFuncID)
{
    tolua_remove_function_by_refid(m_state, uFuncID);
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

int CCLuaEngine::executeFunctionByRefID(int uFuncID, int numArgs)
{
    lua_pushstring(m_state, TOLUA_REFID_FUNC_MAPPING);
    lua_rawget(m_state, LUA_REGISTRYINDEX);                         /* stack: ... refid_func */
    lua_pushinteger(m_state, uFuncID);                        /* stack: ... refid_func refid */
    lua_rawget(m_state, -2);                                        /* stack: ... refid_func func */
    
    if (!lua_isfunction(m_state, -1))
    {
        CCLOG("[LUA ERROR] function refid '%d' does not reference a Lua function", uFuncID);
        lua_pop(m_state, 2 + numArgs);
        return 0;
    }
    
    if (numArgs > 0)
    {
        // [a1] [a2] refid_func func
        //  -4   -3     -2       -1
        // [a1] [a2] refid_func func [a1]
        //  -5   -4     -3       -2   -1
        int lo = -2 - numArgs;
        for (int i = 0; i < numArgs; i++)
        {
            tolua_pushvalue(m_state, lo);                           /* stack: ... refid_func func (...) */
        }
    }
    
    int error = 0;
    try
    {
        error = lua_pcall(m_state, numArgs, 1, 0);                  /* stack: ... refid_func ret */
    }
    catch (exception& e)
    {
        CCLOG("[LUA ERROR] lua_pcall(%d) catch C++ exception: %s", uFuncID, e.what());
        lua_settop(m_state, 0);
        return 0;
    }
    catch (...)
    {
        CCLOG("[LUA ERROR] lua_pcall(%d) catch C++ unknown exception.", uFuncID);
        lua_settop(m_state, 0);
        return 0;
    }
    if (error)
    {
        CCLOG("[LUA ERROR] %s", lua_tostring(m_state, - 1));
        lua_pop(m_state, 2 + numArgs); // clean error message
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
    
    lua_pop(m_state, 2 + numArgs);
    return ret;
}

int CCLuaEngine::executeFunctionWithIntegerData(int uFuncID, int data)
{
    lua_pushinteger(m_state, data);
    return executeFunctionByRefID(uFuncID, 1);
}

int CCLuaEngine::executeFunctionWithFloatData(int uFuncID, float data)
{
    lua_pushnumber(m_state, data);
    return executeFunctionByRefID(uFuncID, 1);
}

int CCLuaEngine::executeFunctionWithBooleanData(int uFuncID, bool data)
{
    lua_pushboolean(m_state, data);
    return executeFunctionByRefID(uFuncID, 1);
}

// functions for excute touch event
int CCLuaEngine::executeTouchEvent(int uFuncID, int eventType, CCTouch *pTouch)
{
    CCPoint pt = CCDirector::sharedDirector()->convertToGL(pTouch->locationInView(pTouch->view()));
    lua_pushinteger(m_state, eventType);
    lua_pushnumber(m_state, pt.x);
    lua_pushnumber(m_state, pt.y);
    return executeFunctionByRefID(uFuncID, 3);
}

int CCLuaEngine::executeTouchesEvent(int uFuncID, int eventType, CCSet *pTouches)
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
        CCPoint pt = pDirector->convertToGL(pTouch->locationInView(pTouch->view()));
        lua_pushnumber(m_state, pt.x);
        lua_rawseti(m_state, -2, n++);
        lua_pushnumber(m_state, pt.y);
        lua_rawseti(m_state, -2, n++);
        ++it;
    }
    
    return executeFunctionByRefID(uFuncID, 2);
}

int CCLuaEngine::executeSchedule(int uFuncID, ccTime dt)
{
    return executeFunctionWithFloatData(uFuncID, dt);
}

} // namespace cocos2d
