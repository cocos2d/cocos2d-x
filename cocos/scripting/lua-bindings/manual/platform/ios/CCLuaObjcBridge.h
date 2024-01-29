/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
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


#ifndef __LUA_OBJC_BRIDGE_H_
#define __LUA_OBJC_BRIDGE_H_

#include "scripting/lua-bindings/manual/CCLuaBridge.h"

/**
 * @addtogroup lua
 * @{
 */

NS_CC_BEGIN

/**
 * Build a bridge between ObjectC and Lua script.
 * This mechanism make Lua and ObjectC call each other easily.
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
