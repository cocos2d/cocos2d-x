
#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "CCLuaBridge.h"

NS_CC_BEGIN

class CCLuaObjcBridge : public CCLuaBridge
{
public:
    static void luaopen_luaoc(lua_State *L);
    
protected:
    static int callObjcStaticMethod(lua_State *L);
    
    static void pushValue(lua_State *L, void *val);
    
    // added by guorui.chen
    static void* checkArray(lua_State *L);
    static void* checkDictionary(lua_State *L);
    static void* copyToObjc(lua_State *L);
};

NS_CC_END

#endif // __LUA_OBJC_BRIDGE_H_
