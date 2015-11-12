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
#ifndef __LUA_OPENGL_H__
#define __LUA_OPENGL_H__

#ifdef __cplusplus
extern "C" {
#endif
#include "tolua++.h"
#ifdef __cplusplus
}
#endif

#include "2d/CCNode.h"
#include "renderer/CCCustomCommand.h"

/**
 * @addtogroup lua
 * @{
 */

/**@~english
 * The GLNode is wrapped to call the callback function about draw in the Lua.
 * @~chinese 
 * 封装GLNode是为了更友好地回调Lua层的draw函数。
 */
class GLNode:public cocos2d::Node
{
public:
    /**@~english
     * Destructor of GLNode.
     *
     * @~chinese
     * GLNode的析构函数。
     * 
     * @lua NA
     * @js NA
     */
    virtual ~GLNode(){}
    
    // @cond
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4& transform, uint32_t flags) override;
    // @endcond
protected:
    cocos2d::CustomCommand _renderCmd;
    void onDraw(const cocos2d::Mat4 &transform, uint32_t flags);
};

/// @cond
TOLUA_API int tolua_opengl_open(lua_State* tolua_S);
TOLUA_API int register_glnode_manual(lua_State* tolua_S);
/// @endcond

// end group
/// @}
#endif //__LUA_OPENGL_H__
