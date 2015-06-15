
#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "CCLuaBridge.h"

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

/**@~english
 * Build a bridge between ObjectC and Lua script.
 * This mechanism make Lua and ObjectC call each other easily.
 * @~chinese 
 * 构建ObjectC和Lua脚本之间的桥梁。
 * 这种机制使Lua脚本和ObjectC之间能够容易地互相调用。
 */
class LuaObjcBridge : public LuaBridge
{
public:
    /**@~english
     * Bind callObjcStaticMethod of LuaObjcBridge to Lua.
     * In current mechanism,we could call LuaObjcBridge.callStaticMethod(className, methodName, args) in Lua directly.
     * Meanwhile the callObjcStaticMethod of LuaObjcBridge binding function is wrapped in the luaoc.lua
     *
     * @~chinese 
     * 绑定LuaObjcBridge的callObjcStaticMethod到Lua中。
     * 当前的机制下,我们可以在Lua脚本中直接调用LuaObjcBridge.callStaticMethod(methodName className,args)。
     * 同时,callObjcStaticMethod绑定在luaoc.lua还进行了一层封装。
     * 
     * @param L @~english the current lua_State
     * @~chinese 当前lua_State
     * @js NA
     * @lua NA
     */
    static void luaopen_luaoc(lua_State *L);
    
protected:
    static int callObjcStaticMethod(lua_State *L);
    
    static void pushValue(lua_State *L, void *val);
};
NS_CC_END

// end group
/// @}
#endif // __LUA_OBJC_BRIDGE_H_
