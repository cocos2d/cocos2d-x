/****************************************************************************
 Copyright (c) 2013-2015 Chukong Technologies Inc.
 
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
#ifndef __COCOS_SCRIPTING_LUA_BINDING_MANUAL_COCOSTUDIO_LUA_STUDIO_CONVERSIONS_H__
#define __COCOS_SCRIPTING_LUA_BINDING_MANUAL_COCOSTUDIO_LUA_STUDIO_CONVERSIONS_H__

extern "C" {
#include "lua.h"
#include "tolua++.h"
}

#include "tolua_fix.h"

namespace cocostudio
{
    namespace timeline
    {
        struct AnimationInfo;
    }
}

/**@~english
 * Get a cocostudio::timeline::AnimationInfo object value from the given acceptable index of stack.
 * If the value at the given acceptable index of stack is a table it returns true, otherwise returns false.
 * If the table has the `name`, `startIndex` and `endIndex` keys and the corresponding values are not nil, this function would assign the values to the corresponding members of outValue. Otherwise, the value of members of outValue would be 0.
 *
 * @~chinese 
 * 从给定Lua栈索引上获取一个cocostudio::timeline::AnimationInfo对象。
 * 如果给定Lua栈索引上是一个table，返回true，否则返回false。
 * 如果table有`name`, `startIndex`和`endIndex`键并且对应的值不为nil,那么这些值会赋值给PhysicsMaterial对象对应的成员变量。否则,对应的成员变值设置为默认值。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param lo @~english the given acceptable index of stack.
 * @~chinese Lua栈索引。
 * @param outValue @~english the pointer to a cocostudio::timeline::AnimationInfo object which stores the values from the Lua table.
 * @~chinese 指向cocostudio::timeline::AnimationInfo对象的指针，用于储存从Lua中获取的值。
 * @param funcName @~english the name of calling function, it is used for error output in the debug model.
 * @~chinese 调用函数名字，调试模式下错误信息的输出会用到这个函数名字。
 * @return @~english Return true if the value at the given acceptable index of stack is a table, otherwise return false.
 * @~chinese 如果给定Lua栈索引上是一个table，返回true，否则返回false。
 */
extern bool luaval_to_animationInfo(lua_State* L, int lo, cocostudio::timeline::AnimationInfo* outValue , const char* funcName = "");

/**@~english
 * Push a table converted from a cocostudio::timeline::AnimationInfo into the Lua stack.
 * The format of table as follows: {name=stringValue, startIndex=numberValue1, endIndex=numberValue2}.
 *
 * @~chinese 
 * 将一个cocos2d::AffineTransform对象转换成Lua table,然后将其压入Lua栈中。
 * table的格式如下:{ name=stringValue, startIndex=numberValue1, endIndex=numberValue2}。
 * 
 * @param L @~english the current lua_State.
 * @~chinese 当前lua_State。
 * @param inValue @~english a cocos2d::AffineTransform object.
 * @~chinese cocostudio::timeline::AnimationInfo对象。
 */
extern void animationInfo_to_luaval(lua_State* L,const cocostudio::timeline::AnimationInfo& inValue);


#endif //__COCOS_SCRIPTING_LUA_BINDING_MANUAL_COCOSTUDIO_LUA_STUDIO_CONVERSIONS_H__
