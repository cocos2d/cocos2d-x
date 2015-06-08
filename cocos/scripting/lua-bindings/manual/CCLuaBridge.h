/****************************************************************************
 Copyright (c) 2013 Chukong Technologies Inc.
 
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

#ifndef __LUA_BRIDGE_H_
#define __LUA_BRIDGE_H_

#include <string>
#include <map>
#include "CCLuaEngine.h"

extern "C" {
#include "lua.h"
}

using namespace std;
/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN
/** @~english LuaBridge Error enum, with inline docs.  @~chinese LuaBridge的错误枚举*/
typedef enum {
    kLuaBridgeErrorOk                   = 0,  /** &lt; value 0 */
    kLuaBridgeErrorInvalidParameters    = -1, /** &lt; value -1 */
    kLuaBridgeErrorClassNotFound        = -2, /** &lt; value -2 */
    kLuaBridgeErrorMethodNotFound       = -3, /** &lt; value -3 */
    kLuaBridgeErrorExceptionOccurred    = -4, /** &lt; value -4 */
    kLuaBridgeErrorMethodSignature      = -5, /** &lt; value -5 */
    kLuaBridgeErrorJavaVMError          = -6, /** &lt; value -6 */
} LuaBridgeError;

#define LUA_BRIDGE_REGISTRY_FUNCTION    "lua_bridge_function_id"        // table[function] = id
#define LUA_BRIDGE_REGISTRY_RETAIN      "lua_bridge_function_id_retain" // table[id] = retain count

/**@~english
 * Build bridge between ObjC and Lua.
 * It makes Lua and ObjC can call each other conveniently.
 *
 * @~chinese 
 * 构建ObjC和Lua之间的桥梁。
 * 它使Lua和ObjC间可以方便地互相调用。
 * 
 * @lua NA
 * @js NA
 */
class LuaBridge
{
public:
    /**@~english
     * Get the LuaStack of LuaEngine.
     *
     * @~chinese 
     * 获取LuaEngine的LuaStack对象。
     * 
     * @return @~english the LuaStack object.
     * @~chinese LuaStack对象。
     */
    static LuaStack *getStack(void);
    /**@~english
     * Push the function pointer corresponding to functionId on the top of lua stack by searching the `lua_bridge_function_id` table.
     * If it don't find the function pointer corresponding to functionId, it will reset stack top index to the index before searching.
     *
     * @~chinese 
     * 通过查找“lua_bridge_function_id” table将functionId对应的函数指针压入到Lua栈顶。
     * 如果没有找到functionId对应的函数指针,它将重置Lua栈顶索引为查找前的Lua栈柄索引。
     *
     * @param functionId @~english the value used to search the `lua_bridge_function_id` table.
     * @~chinese 用于查找“lua_bridge_function_id”表的函数引用id。

     * @return @~english Return 0 if the `lua_bridge_function_id` table or the function pointer corresponding to functionId don't exist, otherwise return -1.
     * @~chinese 如果给定的`lua_bridge_function_id` table不存在或者对应functionId的函数指针不存在，返回0，否则，返回-1。
     */
    static int pushLuaFunctionById(int functionId);
    
    /**@~english
     * The retain count would be increase by 1 corresponding to functionId in the `lua_bridge_function_id_retain` table if it could be found.
     * If `lua_bridge_function_id_retain` table is not existed or the type of lua_bridge_function_id_retain[functionId] isn't LUA_TNUMBER, It would return 0.
     * The top index of Lua stack the same as before calling this function.
     *
     * @~chinese 
     * 如果在对应的'lua_bridge_function_id_retain'表中可以找到functionId的引用计数值，那么对应的引用计数值加1。
     * 如果`lua_bridge_function_id_retain`不存在或者lua_bridge_function_id_retain[functionId]对应的值的类型不是LUA_TNUMBER，它将返回0，否则返回更新后的引用计数。
     * Lua栈顶索引调用前后一致。
     * 
     * @param functionId @~english the value used to search the `lua_bridge_function_id_retain` table.
     * @~chinese 用于查找“lua_bridge_function_id_retain” table的函数引用id。
     * @return @~english the retain count or 0.
     * @~chinese 引用计数或0。
     */
    static int retainLuaFunctionById(int functionId);
    
    /**@~english
     *
     * The retain count woulde be reduced by 1 corresponding to functionId in the `lua_bridge_function_id_retain` table if it could be found.
     * If `lua_bridge_function_id` table or `lua_bridge_function_id_retain` aren't existed or the type of lua_bridge_function_id_retain[functionId] isn't LUA_TNUMBER , it would return 0.
     * If the vaule of retain count is 0 after reducing, it would update the `lua_bridge_function_id_retain` table and `lua_bridge_function_id_retain` table to remove the  reference corresponding to this functionId
     *
     * @~chinese 
     * 
     * 如果在对应的'lua_bridge_function_id_retain'表中可以找到functionId的引用计数值，那么对应的引用计数值减1。
     * 如果`lua_bridge_function_id`或者`lua_bridge_function_id_retain`不存在或者lua_bridge_function_id_retain[functionId]对应的值的类型不是LUA_TNUMBER，它将返回0。
     * 同时，如果引用计数更新为0,它将删除这个functionId对应在“lua_bridge_function_id_retain” table和“lua_bridge_function_id_retain” table中的值，返回0，否则返回引用计数。
     * 
     * @param functionId @~english the value used to search the `lua_bridge_function_id` table and `lua_bridge_function_id` table.
     * @~chinese 用于查找“lua_bridge_function_id” table和“lua_bridge_function_id” table中的函数引用id。
     * @return @~english the retain count or 0.
     * @~chinese 引用计数值或0。
     */
    static int releaseLuaFunctionById(int functionId);
    
protected:
    static int retainLuaFunction(lua_State *L, int functionIndex, int *retainCountReturn);

    static lua_State *s_luaState;
    static int        s_newFunctionId;
};

NS_CC_END

// end group
/// @}

#endif // __LUA_BRIDGE_H_
