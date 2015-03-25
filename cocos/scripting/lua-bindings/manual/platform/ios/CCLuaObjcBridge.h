
#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "CCLuaBridge.h"

NS_CC_BEGIN

/**
 * Build a bridge between ObjectC and Lua script.
 * This mechanism make Lua and ObjectC call each other easily.
 * 
 * @js NA
 */
class LuaObjcBridge : public LuaBridge
{
public:
    /**
     * Bind callObjcStaticMethod of LuaObjcBridge to Lua.
     * In current mechanism,we could call LuaObjcBridge.callStaticMethod(className, methodName, args) in Lua directly.
     * Meanwhile the callObjcStaticMethod of LuaObjcBridge binding function is wrapped in the luaoc.lua
     *
     * @param L the current lua_State
     * @lua NA
     */
    static void luaopen_luaoc(lua_State *L);
    
protected:
    static int callObjcStaticMethod(lua_State *L);
    
    static void pushValue(lua_State *L, void *val);
};
NS_CC_END

#endif // __LUA_OBJC_BRIDGE_H_
