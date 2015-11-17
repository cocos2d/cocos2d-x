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

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

/**
 * LuaStack is used to manager the operation on the lua_State,eg., push data onto the lua_State, execute the function depended on the lua_State.
 * In the current mechanism, there is only one lua_State in one LuaStack object.
 *
 * @lua NA
 * @js NA
 */
class LuaStack : public Ref
{
public:
    /**
     * Create a LuaStack object, it will new a lua_State.
     */
    static LuaStack *create(void);
    /**
     * Create a LuaStack object with the existed lua_State.
     */
    static LuaStack *attach(lua_State *L);
    
    /** Destructor. */
    virtual ~LuaStack();
    
    /**
     * Method used to get a pointer to the lua_State that the script module is attached to.
     *
     * @return A pointer to the lua_State that the script module is attached to.
     */
    lua_State* getLuaState(void) {
        return _state;
    }
    
    /**
     * Add a path to find lua files in.
     *
     * @param path to be added to the Lua search path.
     */
    virtual void addSearchPath(const char* path);
    
    /**
     * Add lua loader.
     * 
     * @param func a function pointer point to the loader function.
     */
    virtual void addLuaLoader(lua_CFunction func);
    
    /**
     * Reload script code corresponding to moduleFileName.
     * If value of package["loaded"][moduleFileName] is existed, it would set the value nil.Then,it calls executeString function.
     *
     * @param moduleFileName String object holding the filename of the script file that is to be executed.
     * @return 0 if the string is executed correctly or other if the string is executed wrongly.
     */
    virtual int reload(const char* moduleFileName);
    
    /**
     * Remove the related reference about the Ref object stored in the Lua table by set the value of corresponding key nil:
     * The related Lua tables are toluafix_refid_ptr_mapping,toluafix_refid_type_mapping,tolua_value_root and object_Metatable["tolua_ubox"] or tolua_ubox.
     * Meanwhile set the corresponding userdata nullptr and remove the all the lua function reference corresponding to this object.
     *
     * In current mechanism, this function is called in the destructor of Ref object, developer don't call this functions.
     *
     * @param object the key object to remove script object.
     */
    virtual void removeScriptObjectByObject(Ref* object);
    
    /**
     * Remove Lua function reference by nHandler by setting toluafix_refid_function_mapping[nHandle] nil.
     *
     * @param nHandler the function reference index to find the corresponding Lua function pointer.
     */
    virtual void removeScriptHandler(int nHandler);
    
    /**
     * Reallocate Lua function reference index to the Lua function pointer to add reference.
     *
     * @param nHandler the function reference index to find the corresponding Lua function pointer.
     */
    virtual int reallocateScriptHandler(int nHandler);
    
    /**
     * Execute script code contained in the given string.
     *
     * @param codes holding the valid script code that should be executed.
     * @return 0 if the string is executed correctly, other if the string is executed wrongly.
     */
    virtual int executeString(const char* codes);
    
    /**
     * Execute a script file.
     *
     * @param filename String object holding the filename of the script file that is to be executed.
     * @return the return values by calling executeFunction.
     */
    virtual int executeScriptFile(const char* filename);

    /**
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer.
     *
     * @param functionName String object holding the name of the function, in the global script environment, that is to be executed.
     * @return The integer value returned from the script function.
     */
    virtual int executeGlobalFunction(const char* functionName);
    
    /**
     * Set the stack top index 0.
     */
    virtual void clean(void);
    
    /**
     * Pushes a integer number with value intValue onto the stack.
     * 
     * @param intValue a integer number.
     */
    virtual void pushInt(int intValue);
    
    /**
     * Pushes a float number with value floatValue onto the stack.
     *
     * @param floatValue a float number.
     */
    virtual void pushFloat(float floatValue);
    
    /**
     * Pushes a long number with value longValue onto the stack.
     * 
     * @param longValue a long number.
     */
    virtual void pushLong(long longValue);
    
    /**
     * Pushes a bool value with boolValue onto the stack.
     * 
     * @param boolValue a bool value.
     */
    virtual void pushBoolean(bool boolValue);
    
    /**
     * Pushes the zero-terminated string pointed to by stringValue onto the stack.
     *
     * @param stringValue a pointer point to a zero-terminated string stringValue.
     */
    virtual void pushString(const char* stringValue);
    
    /**
     * Pushes the string pointed to by stringValue with size length onto the stack.
     *
     * @param stringValue a pointer point to the string stringValue.
     * @param length the size.
     */
    virtual void pushString(const char* stringValue, int length);
    
    /**
     * Pushes a nil value onto the stack.
     */
    virtual void pushNil(void);
    
    /**
     * Pushes a Ref object onto the stack.
     *
     * @see toluafix_pushusertype_ccobject.
     */
    virtual void pushObject(Ref* objectValue, const char* typeName);
    
    /**
     * According to the type of LuaValue, it would called the other push function in the internal.
     *   type                           function
     * LuaValueTypeInt                   pushInt
     * LuaValueTypeFloat                 pushFloat
     * LuaValueTypeBoolean               pushBoolean
     * LuaValueTypeString                pushString
     * LuaValueTypeDict                  pushLuaValueDict
     * LuaValueTypeArray                 pushLuaValueArray
     * LuaValueTypeObject                pushObject
     * 
     * @param value a LuaValue object.
     */
    virtual void pushLuaValue(const LuaValue& value);
    
    /**
     * Pushes a lua table onto the stack.
     * The key of table is the key of LuaValueDict which is std::map.
     * The value of table is according to the type of LuaValue of LuaValueDict by calling pushLuaValue,@see pushLuaValue.
     *
     * @param dict a LuaValueDict object.
     */
    virtual void pushLuaValueDict(const LuaValueDict& dict);
    
    /**
     * Pushes a lua array table onto the stack.
     * The index of array table is begin at 1.
     * The value of array table is according to the type of LuaValue of LuaValueDict by calling pushLuaValue,@see pushLuaValue.
     */
    virtual void pushLuaValueArray(const LuaValueArray& array);
    
    /**
     * Get the lua function pointer from toluafix_refid_function_mapping table by giving nHanlder.
     * If the lua function pointer corresponding to the nHanlder isn't found, it would push nil on the top index of stack, then it would output the error log in the debug model.
     *
     * @return true if get the no-null function pointer otherwise false.
     */
    virtual bool pushFunctionByHandler(int nHandler);
    
    /**
     * Execute the lua function on the -(numArgs + 1) index on the stack by the numArgs variables passed.
     *
     * @param numArgs the number of variables.
     * @return 0 if it happen the error or it hasn't return value, otherwise it return the value by calling the lua function.
     */
    virtual int executeFunction(int numArgs);
    
    /**
     * Execute the lua function corresponding to the nHandler by the numArgs variables passed.
     *
     * @param nHandler the index count corresponding to the lua function.
     * @param numArgs the number of variables.
     * @return the return value is the same as executeFunction,please @see executeFunction.
     */
    virtual int executeFunctionByHandler(int nHandler, int numArgs);
    
    /**
     * Execute the lua function corresponding to the handler by the numArgs variables passed.
     * By calling this function, the number of return value is numResults(may be > 1).
     * All the return values are stored in the resultArray.
     *
     * @param handler the index count corresponding to the lua function.
     * @param numArgs the number of variables.
     * @param numResults the number of return value.
     * @param resultArray a array used to store the return value.
     * @return 0 if it happen error or it hasn't return value, otherwise return 1.
     */
    virtual int executeFunctionReturnArray(int handler,int numArgs,int numResults,__Array& resultArray);
    
    /**
     * Execute the lua function corresponding to the handler by the numArgs variables passed.
     * By calling this function, the number of return value is numResults(may be > 1).
     * All the return values are used in the callback func.
     *
     * @param handler the index count corresponding to the lua function.
     * @param numArgs the number of variables.
     * @param numResults the number of return value.
     * @param func callback function which is called if the numResults > 0.
     * @return 0 if it happen error or it hasn't return value, otherwise return 1.
     */
    virtual int executeFunction(int handler, int numArgs, int numResults, const std::function<void(lua_State*,int)>& func);
    
    /**
     * Handle the assert message.
     *
     * @return return true if current _callFromLua of LuaStack is not equal to 0 otherwise return false.
     */
    virtual bool handleAssert(const char *msg);
    
    /**
     * Set the key and sign for xxtea encryption algorithm.
     *
     * @param key a string pointer
     * @param keyLen the length of key
     * @param sign a string sign
     * @param signLen the length of sign
     */
    virtual void setXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);
    
    /**
     * free the key and sign for xxtea encryption algorithm.
     */
    virtual void cleanupXXTEAKeyAndSign();
    
    /**
     * Loads a buffer as a Lua chunk.This function uses lua_load to load the Lua chunk in the buffer pointed to by chunk with size chunkSize.
     * If it supports xxtea encryption algorithm, the chunk and the chunkSize would be processed by calling xxtea_decrypt to the real buffer and buffer size.
     *
     * @param L the current lua_State.
     * @param chunk the buffer pointer.
     * @param chunkSize the size of buffer.
     * @param chunkName the name of chunk pointer.
     * @return 0, LUA_ERRSYNTAX or LUA_ERRMEM:.
     */
    int luaLoadBuffer(lua_State *L, const char *chunk, int chunkSize, const char *chunkName);
    
    /**
     * Load the Lua chunks from the zip file
     * 
     * @param zipFilePath file path to zip file.
     * @return 1 if load successfully otherwise 0.
     */
    int loadChunksFromZIP(const char *zipFilePath);
    
    /**
     * Load the Lua chunks from current lua_State.
     *
     * @param L the current lua_State.
     * @return 1 if load successfully otherwise 0.
     */
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

// end group
/// @}
#endif // __CC_LUA_STACK_H_
