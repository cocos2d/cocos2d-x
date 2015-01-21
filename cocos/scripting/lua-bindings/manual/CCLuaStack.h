/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
 Copyright (c) 2013-2014 Chukong Technologies Inc.
 
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

#include "cocos2d.h"
#include "CCLuaValue.h"

#define LUASTACK_USED_FOR_QUICK_COCOS2DX

NS_CC_BEGIN

class LuaStack : public Ref
{
public:
    static LuaStack *create(void);
    static LuaStack *attach(lua_State *L);
    
    virtual ~LuaStack();
    
    /**
     @brief Method used to get a pointer to the lua_State that the script module is attached to.
     @return A pointer to the lua_State that the script module is attached to.
     */
    lua_State* getLuaState(void) {
        return _state;
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
     @brief reload script code contained in the given string.
     @param moduleFileName String object holding the filename of the script file that is to be executed
     @return 0 if the string is excuted correctly.
     @return other if the string is excuted wrongly.
     */
    virtual int reload(const char* moduleFileName);
    
    /**
     @brief Remove Object from lua state
     @param object The object to be removed.
     */
    virtual void removeScriptObjectByObject(Ref* object);
    
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
    virtual void pushLong(long longValue);
    virtual void pushBoolean(bool boolValue);
    virtual void pushString(const char* stringValue);
    virtual void pushString(const char* stringValue, int length);
    virtual void pushNil(void);
    virtual void pushObject(Ref* objectValue, const char* typeName);
    virtual void pushLuaValue(const LuaValue& value);
    virtual void pushLuaValueDict(const LuaValueDict& dict);
    virtual void pushLuaValueArray(const LuaValueArray& array);    
    virtual bool pushFunctionByHandler(int nHandler);
    virtual int executeFunction(int numArgs);
    
    virtual int executeFunctionByHandler(int nHandler, int numArgs);
    virtual int executeFunctionReturnArray(int handler,int numArgs,int numResults,__Array& resultArray);
    virtual int executeFunction(int handler, int numArgs, int numResults, const std::function<void(lua_State*,int)>& func);

	virtual bool handleAssert(const char *msg, const char *cond, const char *file, int line);
    
    virtual void setXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);
    virtual void cleanupXXTEAKeyAndSign();
    
    virtual const char *getXXTEAKey(int *len);
    virtual const char *getXXTEASign(int *len);
    
    int luaLoadBuffer(lua_State *L, const char *chunk, int chunkSize, const char *chunkName);
    int loadChunksFromZIP(const char *zipFilePath);
    int luaLoadChunksFromZIP(lua_State *L);
    
protected:
    LuaStack(void)
    : _state(nullptr)
    , _callFromLua(0)
    , _xxteaEnabled(false)
    , _xxteaKey(nullptr)
    , _xxteaKeyLen(0)
    , _xxteaSign(nullptr)
    , _xxteaSignLen(0)
    {
    }
    
    bool init(void);
    bool initWithLuaState(lua_State *L);
    
    lua_State *_state;
    int _callFromLua;
    bool  _xxteaEnabled;
    char* _xxteaKey;
    int   _xxteaKeyLen;
    char* _xxteaSign;
    int   _xxteaSignLen;
};

NS_CC_END

#endif // __CC_LUA_STACK_H_
