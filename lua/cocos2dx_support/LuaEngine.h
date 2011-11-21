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
#ifndef __LUA_ENGINE_H__
#define __LUA_ENGINE_H__

extern "C" {
#include "lua.h"
}

#include "tolua++.h"
#include "tolua_fix.h"

#include "CCObject.h"
#include "CCTouch.h"
#include "CCSet.h"
#include "CCNode.h"

#include <map>

using namespace cocos2d;

class LuaEngine
{
public:
    ~LuaEngine();
    
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    lua_State* getLuaState(void) const {
        return m_state;
    }

    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    void removeCCObject(CCObject *object);
    
    void removeFunctionByRefId(int refid);

    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    void addSearchPath(const char* path);

    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    bool executeScriptFile(const char* filename);
    
    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param function_name String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    int executeGlobalFunction(const char* function_name);

    /**
     @brief Execute a function by ref id
     @param The function ref id
     @return The integer value returned from the script function.
     */
    int executeFunctionByRefId(int functionRefId);

    int retainRefID(int refID);
    int releaseRefID(int refID);

    // functions for excute touch event
    bool executeTouchEvent(const char *pszFuncName, cocos2d::CCTouch *pTouch);
    bool executeTouchesEvent(const char *pszFuncName, cocos2d::CCSet *pTouches);

    // functions for CCCallFuncX
    bool executeCallFunc(const char *pszFuncName);
    bool executeCallFuncN(const char *pszFuncName, cocos2d::CCNode *pNode);
    bool executeCallFuncND(const char *pszFuncName, cocos2d::CCNode *pNode, void *pData);
    bool executeCallFunc0(const char *pszFuncName, cocos2d::CCObject *pObject);

    // excute a script function without params
    int executeFuction(const char *pszFuncName);

    // execute a schedule function
    bool executeSchedule(int refid, cocos2d::ccTime dt);
    
    static LuaEngine* sharedEngine();
    static void purgeSharedEngine();

private:
    LuaEngine();
    
    static LuaEngine* s_engine;
    lua_State* m_state;
    std::map<int, int> m_refIDMap;
};

#endif // __LUA_ENGINE_H__
