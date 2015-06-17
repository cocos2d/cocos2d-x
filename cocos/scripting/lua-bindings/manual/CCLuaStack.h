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

/**@~english
 * LuaStack is used to manager the operation on the lua_State,eg., push data onto the lua_State, execute the function depended on the lua_State, and so on.
 * In the current mechanism, there is only one lua_State in one LuaStack object.
 *
 * @~chinese 
 * LuaStack用于管理lua_State操作,例如: 将数据压入到lua_State，执行lua_State上的函数等等。
 * 在当前的机制,在一个LuaStack对象中只有一个lua_State
 * 
 * @lua NA
 * @js NA
 */

class LuaStack : public Ref
{
public:
    /**@~english
     * Create a LuaStack object, it will new a lua_State.
     * @~chinese 
     * 创建一个LuaStack对象,它将新建一个lua_State。
     */

    static LuaStack *create(void);
    /**@~english
     * Create a LuaStack object with the existed lua_State.
     * @~chinese 
     * 根据存在的lua_State创建一个LuaStack对象。
     */

    static LuaStack *attach(lua_State *L);
    
    /** @~english Destructor.  @~chinese 析构函数。*/

    virtual ~LuaStack();
    
    /**@~english
     * Method used to get a pointer to the lua_State that the script module is attached to.
     *
     * @~chinese 
     * 获取脚本模块依赖的lua_State指针。
     * 
     * @return @~english A pointer to the lua_State that the script module is attached to.
     * @~chinese lua_State指针。
     */

    lua_State* getLuaState(void) {
        return _state;
    }
    
    /**@~english
     * Add a path to find lua files in.
     *
     * @~chinese 
     * 添加一条搜索Lua文件的路径。
     * 
     * @param path @~english to be added to the Lua search path.
     * @~chinese 新增的搜索路径。
     */

    virtual void addSearchPath(const char* path);
    
    /**@~english
     * Add lua loader.
     * 
     * @~chinese 
     * 添加Lua加载函数。
     * 
     * @param func @~english a function pointer point to the loader function.
     * @~chinese 加载函数的函数指针。
     */

    virtual void addLuaLoader(lua_CFunction func);
    
    /**@~english
     * Reload script code corresponding to moduleFileName.
     * If value of package["loaded"][moduleFileName] is existed, it would set the vaule nil.Then,it calls executeString function.
     *
     * @~chinese 
     * 重新加载对应模块名的脚本代码。
     * 如果package["loaded"][moduleFileName]的值存在,它将被设置值为nil，然后，再调用executeString函数。
     * 
     * @param moduleFileName @~english String object holding the filename of the script file that is to be reloaded.
     * @~chinese 需重新加载的脚本文件名。
     * @return @~english 0 if the string is excuted correctly or other if the string is excuted wrongly.
     * @~chinese 如果执行正确返回0，否则返回其它值。
     */

    virtual int reload(const char* moduleFileName);
    
    /**@~english
     * Remove the related reference about the Ref object stored in the Lua table by set the value of corresponding key nil:
     * The related Lua tables are toluafix_refid_ptr_mapping,toluafix_refid_type_mapping,tolua_value_root and object_Metatable["tolua_ubox"] or tolua_ubox.
     * Meanwhile set the corresponding userdata nullptr and remove the all the lua function reference corresponding to this object.
     *
     * In current mechanism, this function is called in the destructor of Ref object, developer don't call this functions.
     *
     * @~chinese 
     * 通过操作Lua table,移除Ref对象在Lua table中的引用。
     * 相关的Lua table包括toluafix_refid_ptr_mapping、toluafix_refid_type_mapping tolua_value_root和object_Metatable["tolua_ubox"]或tolua_ubox。
     * 同时，设置相应的userdata为nullptr以及移除去该对象相关的Lua函数的引用
     * 
     * 目前的机制下，开发者不需要直接调用这个函数，这个函数将会在LuaEngier的析构函数中自动被调用。
     * 
     * @param object @~english the key object to remove script object.
     * @~chinese 用于移除脚本对象引用的键值
     */

    virtual void removeScriptObjectByObject(Ref* object);
    
    /**@~english
     * Remove Lua function reference by nHandler by setting toluafix_refid_function_mapping[nHandle] nil.
     *
     * @~chinese 
     * 通过设置toluafix_refid_function_mapping[nHandle]=nil,移除Lua函数引用
     * 
     * @param nHandler @~english the function reference id to find the correspoinding Lua function pointer.
     * @~chinese Lua函数的引用id。
     */

    virtual void removeScriptHandler(int nHandler);
    
    /**@~english
     * Reallocate Lua function reference id to the Lua function pointer to add reference.
     *
     * @~chinese 
     * 重新分配Lua函数的引用id。
     * 
     * @param nHandler @~english the reference id to find the correspoinding Lua function pointer.
     * @~chinese Lua函数的引用id。
     */

    virtual int reallocateScriptHandler(int nHandler);
    
    /**@~english
     * Execute script code contained in the given string.
     *
     * @~chinese 
     * 执行给定字符串中包含的脚本代码。
     * 
     * @param codes @~english holding the valid script code that should be executed.
     * @~chinese 需被执行的脚本代码字符串。
     * @return @~english 0 if the string is excuted correctly,other if the string is excuted wrongly.
     * @~chinese 执行成功返回0，否则返回其它值。
     */

    virtual int executeString(const char* codes);
    
    /**@~english
     * Execute a script file.
     *
     * @~chinese 
     * 执行一个脚本文件。
     * 
     * @param filename @~english String object holding the filename of the script file that is to be executed.
     * @~chinese 脚本文件的文件名。
     * @return @~english the return values by calling executeFunction.
     * @~chinese 如果碰到错误或者执行结果没有返回值时返回0，否则返回1。
     */

    virtual int executeScriptFile(const char* filename);

    /**@~english
     * Execute a scripted global function.
     * The function should not take any parameters and should return an integer.
     *
     * @~chinese 
     * 执行全局的脚本函数。
     * 该全局函数不应该有任何参数,同时返回一个整数。
     * 
     * @param functionName @~english String object holding the name of the function, in the global script environment, that is to be executed.
     * @~chinese 全局脚本函数的字符串名称
     * @return @~english The integer value returned from the script function.
     * @~chinese 从脚本函数返回的整数值。
     */

    virtual int executeGlobalFunction(const char* functionName);
    
    /**@~english
     * Set the stack top index 0.
     * @~chinese 
     * 设置Lua栈顶索引为0。
     */

    virtual void clean(void);
    
    /**@~english
     * Pushes a integer number into the stack.
     * 
     * @~chinese 
     * 将一个整数值压入Lua栈。
     * 
     * @param intValue @~english a integer number.
     * @~chinese 整数值。
     */

    virtual void pushInt(int intValue);
    
    /**@~english
     * Pushes a float number into the stack.
     *
     * @~chinese 
     * 将一个浮点值压入Lua栈。
     * 
     * @param floatValue @~english a float number.
     * @~chinese 浮点值。
     */

    virtual void pushFloat(float floatValue);
    
    /**@~english
     * Pushes a long number into the stack.
     * 
     * @~chinese 
     * 将一个长整型数压入Lua栈。
     * 
     * @param longValue @~english a long number.
     * @~chinese 长整型值。
     */

    virtual void pushLong(long longValue);
    
    /**@~english
     * Pushes a bool value into the stack.
     * 
     * @~chinese 
     * 将一个布尔值压入Lua栈。
     * 
     * @param boolValue @~english a bool value.
     * @~chinese 布尔值
     */

    virtual void pushBoolean(bool boolValue);
    
    /**@~english
     * Pushes the zero-terminated string pointed into the stack.
     *
     * @~chinese 
     * 将一个以'\0'结束的字符串指针压入Lua栈。
     * 
     * @param stringValue @~english a pointer point to a zero-terminated string.
     * @~chinese 字符串指针。
     */

    virtual void pushString(const char* stringValue);
    
    /**@~english
     * Pushes the string pointed to stringValue with size length into the stack.
     *
     * @~chinese 
     * 将指向stringValue的字符串按指定length压入Lua栈。
     * 
     * @param stringValue @~english a pointer point to the string stringValue.
     * @~chinese 字符串指针。
     * @param length @~english the size.
     * @~chinese 需要压入的长度。
     */

    virtual void pushString(const char* stringValue, int length);
    
    /**@~english
     * Pushes a nil value into the stack.
     * @~chinese 
     * 压入一个nil到Lua栈。
     */

    virtual void pushNil(void);
    
    /**@~english
     * Pushes a Ref object into the stack,please refer to toluafix_pushusertype_ccobject for detail information
     *
     * @~chinese 
     * 将一个Ref对象压入到Lua栈，详细信息请查阅toluafix_pushusertype_ccobject
     * 
     * @see toluafix_pushusertype_ccobject.
     */

    virtual void pushObject(Ref* objectValue, const char* typeName);
    
    /**@~english
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
     * @~chinese 
     * 根据不同类型的LuaValue,它将会在函数内部调用其它相关的push函数
     *    类型                       函数
     * LuaValueTypeInt             pushInt
     * LuaValueTypeFloat           pushFloat
     * LuaValueTypeBoolean         pushBoolean
     * LuaValueTypeString          pushString
     * LuaValueTypeDict            pushLuaValueDict
     * LuaValueTypeArray           pushLuaValueArray
     * LuaValueTypeObject          pushObject
     * 
     * @param value @~english a LuaValue object.
     * @~chinese LuaValue对象。
     */

    virtual void pushLuaValue(const LuaValue& value);
    
    /**@~english
     * Pushes a Lua table into the stack.
     * The key of table is string.
     * The value of table is got by calling pushLuaValue,@see pushLuaValue.
     * @~chinese 
     * 将一个Lua table压入Lua栈。
     * 这个Lua table的key值为字符串，value值依赖LuaValue的类型通过调用pushLuaValue获得，@see pushLuaValue。
     * 
     * @param dict @~english a LuaValueDict object.
     * @~chinese LuaValueDict对象。
     */

    virtual void pushLuaValueDict(const LuaValueDict& dict);
    
    /**@~english
     * Pushes a Lua array table onto the stack.
     * The index of array table is begin at 1.
     * The value of array table is got by calling pushLuaValue,@see pushLuaValue.
     * @~chinese 
     * 将一个Lua数组table压入Lua栈。
     * 数组table的索引从1开始。
     * 这个Lua数组table中的值通过调用pushLuaValue获得，@see pushLuaValue。
     *
     * @param array @~english a LuaValueArray object.
     * @~chinese LuaValueArray
     */

    virtual void pushLuaValueArray(const LuaValueArray& array);
    
    /**@~english
     * Get the Lua function pointer from toluafix_refid_function_mapping table by giving nHanlder,then push it into the Lua stack.
     * If the Lua function pointer corresponding to the nHanlder isn't found, it would push nil on the top index of stack, then it would output the error log in the debug model.
     *
     * @~chinese 
     * 通过给定的nHandler查找toluafix_refid_function_mapping table获取对应的Lua函数指针，并将它压入Lua栈。
     * 如果无法找到nHanlder对应的Lua函数指针, 它会把压入一个nil值到栈顶，并且在在调试模式，它还会输出错误日志。
     * 
     * @return @~english true if get the no-null function pointer otherwise false.
     * @~chinese 否则真的如果没有null的函数指针错误。
     */

    virtual bool pushFunctionByHandler(int nHandler);
    
    /**@~english
     * Find and execute the Lua function on the -(numArgs + 1) index on the stack,the function has numArgs variables.
     *
     * @~chinese 
     * 通过numArgs值，获取Lua栈上-(numArgs + 1)索引处的Lua函数并执行
     * 
     * @param numArgs @~english the number of variables.
     * @~chinese 变量的数量。
     * @return @~english 0 if it happen the error or it hasn't return value, otherwise it return the value by calling the Lua function，integer type or boolean type.
     * @~chinese 如果发生错误或没有返回值返回0,否则返回被调用Lua函数的一个返回值，可以是整型值或是布尔值。
     */

    virtual int executeFunction(int numArgs);
    
    /**@~english
     * Find and execute the Lua function corresponding to the nHandler,the function has numArgs variables.
     *
     * @~chinese 
     * 查找并执行nHandler对应的Lua函数，这个函数有numArgs个参数。
     * 
     * @param nHandler @~english the reference id to the Lua function.
     * @~chinese Lua函数的引用id。
     * @param numArgs @~english the number of variables.
     * @~chinese 变量的数量。
     * @return @~english the return value is the same as executeFunction,please @see executeFunction.
     * @~chinese 返回值与executeFunction一样，@see executeFunction
     */

    virtual int executeFunctionByHandler(int nHandler, int numArgs);
    
    /**@~english
     * Find and execute the Lua function corresponding to the handler,the function has numArgs variables.
     * By calling this function, the number of return values is numResults(may be > 1).
     * All the return values are stored in the resultArray.
     *
     * @~chinese 
     * 查找并执行handler对应的Lua函数，这个函数有numArgs个参数。
     * 调用这个函数将会返回numResults个返回值(可能大于1)。
     * 所有的返回值将存在resultArray中。
     * 
     * @param handler @~english the reference id corresponding to the Lua function.
     * @~chinese 对应Lua函数的引用id
     * @param numArgs @~english the number of function parameters.
     * @~chinese 函数参数的数量。
     * @param numResults @~english the number of return values.
     * @~chinese 返回值的数量。
     * @param resultArray @~english a array used to store the return value.
     * @~chinese 一个用于存储返回值的数组。
     * @return @~english 0 if it happen error or it hasn't return value, otherwise return 1.
     * @~chinese 如果它发生错误或没有返回值返回0,否则返回1。
     */

    virtual int executeFunctionReturnArray(int handler,int numArgs,int numResults,__Array& resultArray);
    
    /**@~english
     * Find and execute the Lua function corresponding to the handler,the function has numArgs variables..
     * By calling this function, the number of return values is numResults(may be > 1).
     * All the return values are used in the callback func.
     *
     * @~chinese 
     * 查找并执行handler对应的Lua函数，这个函数有numArgs个参数。
     * 调用这个函数将会返回numResults个返回值(可能大于1)。
     * 所有的返回值将被用在回调函数func中。
     * 
     * @param handler @~english the reference id corresponding to the lua function.
     * @~chinese 对应Lua函数的引用id。
     * @param numArgs @~english the number of function parameters.
     * @~chinese 函数参数的数量。
     * @param numResults @~english the number of return values.
     * @~chinese 返回值的数量。
     * @param func @~english callback function which is called if the numResults > 0.
     * @~chinese 当numResults > 0时将被调用的回调函数。
     * @return @~english 0 if it happen error or it hasn't return value, otherwise return 1.
     * @~chinese 如果它发生错误或没有返回值返回0,否则返回1。
     */

    virtual int executeFunction(int handler, int numArgs, int numResults, const std::function<void(lua_State*,int)>& func);
    
    /**@~english
     * Handle the assert message.
     *
     * @~chinese 
     * 处理assert信息。
     * 
     * @param msg @~english the assert message string.
     * @~chinese assert信息字符串。
     * @return @~english return true if current _callFromLua is not equal to 0 otherwise return false.
     * @~chinese 如果当前_callFromLua不为0返回true，否则返回false。
     */

    virtual bool handleAssert(const char *msg);
    
    /**@~english
     * Set the key and sign for xxtea encryption algorithm.
     *
     * @~chinese 
     * 设置的xxtea加密算法的key和sign。
     * 
     * @param key @~english a string pointer point to key
     * @~chinese key字符串指针
     * @param keyLen @~english the length of key
     * @~chinese key的长度
     * @param sign @~english a string pointer point to sign
     * @~chinese sign字符串指针
     * @param signLen @~english the length of sign
     * @~chinese sign的长度
     */

    virtual void setXXTEAKeyAndSign(const char *key, int keyLen, const char *sign, int signLen);
    
    /**@~english
     * Cleanup the key and sign for xxtea encryption algorithm.
     * @~chinese 
     * 清除xxtea加密算法的key和sign。
     */

    virtual void cleanupXXTEAKeyAndSign();
    
    /**@~english
     * Loads a buffer as a Lua chunk.This function uses lua_load to load the Lua chunk in the buffer pointed to by chunk with size chunkSize.
     * if current stack enable the xxtea encryption algorithm and the the beginner of the chunk has the sign, the chunk should be decrypt first.
     *
     * @~chinese 
     * 加载一个Lua程序块。该函数使用lua_load通过一个指向程序块的指针加载一块大小为chunkSize的Lua程序块。
     * 如果当前支持xxtea算法，并且chunk的头部有sing签名，那么加载的程序块还需要进行解密操作。
     * 
     * @param L @~english the current lua_State.
     * @~chinese 当前lua_State。
     * @param chunk @~english the chunk pointer.
     * @~chinese 程序块指针。
     * @param chunkSize @~english the size of buffer.
     * @~chinese 程序块大小。
     * @param chunkName @~english the name of chunk pointer.
     * @~chinese 程序块的名称。
     * @return @~english 0, LUA_ERRSYNTAX or LUA_ERRMEM:.
     * @~chinese 0,LUA_ERRSYNTAX或LUA_ERRMEM:。
     */

    int luaLoadBuffer(lua_State *L, const char *chunk, int chunkSize, const char *chunkName);
    
    /**@~english
     * Load the Lua chunks from the zip file
     * 
     * @~chinese 
     * 从zip文件加载Lua程序块
     * 
     * @param zipFilePath @~english file path to zip file.
     * @~chinese zip文件的文件路径。
     * @return @~english 1 if load sucessfully otherwise 0.
     * @~chinese 加载成功返回1，否则返回0。
     */

    int loadChunksFromZIP(const char *zipFilePath);
    
    /**@~english
     * Load the Lua chunks from current lua_State.
     *
     * @~chinese 
     * 从当前的lua_State中加载Lua程序块。
     * 
     * @param L @~english the current lua_State.
     * @~chinese 当前的lua_State。
     * @return @~english 1 if load sucessfully otherwise 0.
     * @~chinese 加载成功返回1，否则返回0。
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
