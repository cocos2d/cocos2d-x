/****************************************************************************
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
#ifndef COCOS_SCRIPTING_LUA_BINDINGS_MANUAL_LUA_COCOS2DX_COCOSBUILDER_H
#define COCOS_SCRIPTING_LUA_BINDINGS_MANUAL_LUA_COCOS2DX_COCOSBUILDER_H

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

TOLUA_API int register_all_cocos2dx_cocosbuilder_manual(lua_State* tolua_S);

/**
 * Call this function can import the lua bindings for the cocosbuilder module.
 * After registering, we could call the related cocosbuilder code conveniently in the lua.eg,.cc.CCBProxy:create().
 * If you don't want to use the cocosbuilder module in the lua, you only don't call this registering function.
 * If you don't register the cocosbuilder module, the package size would become smaller .
 * The current mechanism,this registering function is called in the lua_module_register.h
 *
 * @lua NA
 * @js NA
 */
TOLUA_API int register_cocosbuilder_module(lua_State* tolua_S);

#endif // #ifndef COCOS_SCRIPTING_LUA_BINDINGS_MANUAL_LUA_COCOS2DX_COCOSBUILDER_H
