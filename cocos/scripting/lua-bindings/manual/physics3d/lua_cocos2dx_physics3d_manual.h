/****************************************************************************
 Copyright (c) 2014 Chukong Technologies Inc.

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
#ifndef COCOS_SCRIPTING_LUA_BINDINGS_MANUAL_PHYSICS3D_LUA_COCOS2DX_PHYSICS3D_MANUAL_H__
#define COCOS_SCRIPTING_LUA_BINDINGS_MANUAL_PHYSICS3D_LUA_COCOS2DX_PHYSICS3D_MANUAL_H__

#if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif


/**
 * @addtogroup lua
 * @{
 */

/**@~english
 * Call this function can import the lua bindings for the physics3d module.
 * After registering, we could call the related physics3d code conveniently in the lua.eg,cc.Physics3DShape:createBox(cc.vec3(0.5, 0.5, 0.5)).
 * If you don't want to use the physics3d module in the lua, you only don't call this registering function.
 * If you don't register the physics3d module, the package size would become smaller .
 * The current mechanism,this function is called in the lua_module_register.h and the register function's effect is limited by the marco values of CC_USE_3D_PHYSICS and CC_ENABLE_BULLET_INTEGRATION
 * @~chinese 
 * 调用这个函数可以将physics3d模块绑定到Lua层。
 * 调用这个注册函数后，我们可以方便地在Lua层调用physics3d的相关代码，例如：cc.Physics3DShape:createBox(cc.vec3(0.5, 0.5, 0.5))。
 * 如果你不想使用physics3d模块，那么你就无需调用这个注册函数。这种情况下，最终包的大小也会变得更小一些。
 * 目前的机制,在lua_module_register.h调用这个函数，并且这个函数的调用还受CC_USE_3D_PHYSICS以及CC_ENABLE_BULLET_INTEGRATION这两个宏的限制。
 */

TOLUA_API int  register_physics3d_module(lua_State* L);

// end group
/// @}

#endif // #if CC_USE_3D_PHYSICS && CC_ENABLE_BULLET_INTEGRATION
#endif // #ifndef COCOS_SCRIPTING_LUA_BINDINGS_MANUAL_PHYSICS3D_LUA_COCOS2DX_PHYSICS3D_MANUAL_H__
