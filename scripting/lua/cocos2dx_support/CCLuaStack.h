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

#ifndef __CC_LUA_STACK_H_
#define __CC_LUA_STACK_H_

extern "C" {
#include "lua.h"
}

#include "ccTypes.h"
#include "cocoa/CCObject.h"
#include "CCLuaValue.h"

NS_CC_BEGIN
/** Lua support for cocos2d-x
 *  @js NA
 *  @lua NA
 */
class CCLuaStack : public CCObject
{
public:
    static CCLuaStack *create(void);
    static CCLuaStack *attach(lua_State *L);
    
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    lua_State* getLuaState(void) {
        return m_state;
    }
    
    /**
     @brief Add a path to find lua files in
     @param path to be added to the Lua path
     */
    virtual void addSearchPath(const char* path);
    
    /**
     @brief Add lua loader, now it is used on android
     */
    virtual void addLuaLoader(lua_CFunction func);
    
    /**
     @brief Remove CCObject from lua state
     @param object to remove
     */
    virtual void removeScriptObjectByCCObject(CCObject* pObj);
    
    /**
     @brief Remove Lua function reference
     */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     @brief Remove Lua function reference
     */
    virtual int reallocateScriptHandler(int nHandler);
    
    /**
     @brief Execute script code contained in the given string.
     @param codes holding the valid script code that should be executed.
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int executeString(const char* codes);
    
    /**
     @brief Execute a script file.
     @param filename String object holding the filename of the script file that is to be executed
     */
    virtual int executeScriptFile(const char* filename);

    /**
     @brief Execute a scripted global function.
     @brief The function should not take any parameters and should return an integer.
     @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName);

    virtual void clean(void);
    virtual void pushInt(int intValue);
    virtual void pushFloat(float floatValue);
    virtual void pushBoolean(bool boolValue);
    virtual void pushString(const char* stringValue);
    virtual void pushString(const char* stringValue, int length);
    virtual void pushNil(void);
    virtual void pushCCObject(CCObject* objectValue, const char* typeName);
    virtual void pushCCLuaValue(const CCLuaValue& value);
    virtual void pushCCLuaValueDict(const CCLuaValueDict& dict);
    virtual void pushCCLuaValueArray(const CCLuaValueArray& array);    
    virtual bool pushFunctionByHandler(int nHandler);
    virtual int executeFunction(int numArgs);
    
    virtual int executeFunctionByHandler(int nHandler, int numArgs);
    
    virtual int executeFunctionReturnArray(int nHandler,int nNumArgs,int nNummResults,CCArray* pResultArray);
    
    virtual bool handleAssert(const char *msg);
    
    void setXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);
    void cleanupXXTEAKeyAndSign();
    int luaLoadBuffer(lua_State* L, const char* chunk, int chunkSize, const char* chunkName);
    
    
protected:
    CCLuaStack(void)
    : m_state(NULL)
    , m_callFromLua(0)
    , m_xxteaEnabled(false)
    , m_xxteaKey(NULL)
    , m_xxteaKeyLen(0)
    , m_xxteaSign(NULL)
    , m_xxteaSignLen(0)
    {
    }
    
    bool init(void);
    bool initWithLuaState(lua_State *L);
    
    lua_State *m_state;
    int m_callFromLua;
    bool  m_xxteaEnabled;
    char* m_xxteaKey;
    int   m_xxteaKeyLen;
    char* m_xxteaSign;
    int   m_xxteaSignLen;
};

NS_CC_END

#endif // __CC_LUA_STACK_H_
