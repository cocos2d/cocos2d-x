-- usage: (use instead of ant)
-- tolua++ "-L" "basic.lua" "-o" "../../scripting/lua/cocos2dx_support/LuaCocos2d.cpp" "Cocos2d.pkg"

_is_functions = _is_functions or {}
_to_functions = _to_functions or {}
_push_functions = _push_functions or {}

local CCObjectTypes = {
    "CCArmature",
    "CCArmatureAnimation",
    "CCSkin",
    "CCBone",
    "CCArmatureDataManager",
    "CCBatchNode",
    "CCTween",
    "CCBaseData",
    "CCDisplayManager",
    "Layout",
    "Widget",
    "Layer",
    "Button",
    "CheckBox",
    "ImageView",
    "Label",
    "LabelAtlas",
    "LoadingBar",
    "Slider",
    "TextField",
    "ScrollView",
    "PageView",
    "ListView",
    "LayoutParameter",
    "LinearLayoutParameter",
    "CCComController",
    "CCComAudio",
    "CCComAttribute",
    "CCComRender",
    "ActionManager",
    "GUIReader",
    "RootWidget",
    "ActionObject",
}

-- register CCObject types
for i = 1, #CCObjectTypes do
    _push_functions[CCObjectTypes[i]] = "toluafix_pushusertype_ccobject"
end

-- register LUA_FUNCTION, LUA_TABLE, LUA_HANDLE type
_to_functions["LUA_FUNCTION"] = "toluafix_ref_function"
_is_functions["LUA_FUNCTION"] = "toluafix_isfunction"
_to_functions["LUA_TABLE"] = "toluafix_totable"
_is_functions["LUA_TABLE"] = "toluafix_istable"

local toWrite = {}
local currentString = ''
local out
local WRITE, OUTPUT = write, output

function output(s)
    out = _OUTPUT
    output = OUTPUT -- restore
    output(s)
end

function write(a)
    if out == _OUTPUT then
        currentString = currentString .. a
        if string.sub(currentString,-1) == '\n'  then
            toWrite[#toWrite+1] = currentString
            currentString = ''
        end
    else
        WRITE(a)
    end
end

function post_output_hook(package)
    local result = table.concat(toWrite)
    local indexTest = 0
    local function replace(pattern, replacement)
        local k = 0
        local nxt, currentString = 1, ''
        repeat
            local s, e = string.find(result, pattern, nxt, true)
            if e then
                currentString = currentString .. string.sub(result, nxt, s-1) .. replacement
                nxt = e + 1
                k = k + 1
            end
        until not e
        result = currentString..string.sub(result, nxt)
        if k == 0 then print('Pattern not replaced', pattern) end
    end

    replace([[#ifndef __cplusplus
#include "stdlib.h"
#endif
#include "string.h"

#include "tolua++.h"]],
      [[/****************************************************************************
 Copyright (c) 2011 cocos2d-x.org

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

extern "C" {
#include "tolua_fix.h"
}

#include <map>
#include <string>
#include "cocos2d.h"
#include "CCLuaEngine.h"
#include "SimpleAudioEngine.h"
#include "cocos-ext.h"

using namespace cocos2d;
using namespace cocos2d::gui;
using namespace cocos2d::extension;
using namespace CocosDenshion;]])

      replace([[/* Exported function */
TOLUA_API int  tolua_CocoStudio_open (lua_State* tolua_S);]], [[]])

      replace([[(tolua_isvaluenil(tolua_S,2,&tolua_err) || !tolua_isusertype(tolua_S,2,"CCTextAlignment",0,&tolua_err))]],[[!tolua_isnumber(tolua_S,2,0,&tolua_err)]])

      replace([[CCTextAlignment alignment = *((CCTextAlignment*)  tolua_tousertype(tolua_S,2,0));]],[[CCTextAlignment alignment = ((CCTextAlignment) (int)  tolua_tonumber(tolua_S,2,0));]])

      replace([[toluafix_pushusertype_ccobject(tolua_S,(void*)tolua_ret]],
        [[int nID = (tolua_ret) ? (int)tolua_ret->m_uID : -1;
    int* pLuaID = (tolua_ret) ? &tolua_ret->m_nLuaID : NULL;
    toluafix_pushusertype_ccobject(tolua_S, nID, pLuaID, (void*)tolua_ret]])

      replace('\t', '    ')

      replace([[static int tolua_collect_CCPoint (lua_State* tolua_S)
{
 CCPoint* self = (CCPoint*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_UIRelativeAlign (lua_State* tolua_S)
{
 UIRelativeAlign* self = (UIRelativeAlign*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_CCRect (lua_State* tolua_S)
{
 CCRect* self = (CCRect*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_DisplayType (lua_State* tolua_S)
{
 DisplayType* self = (DisplayType*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_CCSize (lua_State* tolua_S)
{
 CCSize* self = (CCSize*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_ccColor4B (lua_State* tolua_S)
{
 ccColor4B* self = (ccColor4B*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_CCAffineTransform (lua_State* tolua_S)
{
 CCAffineTransform* self = (CCAffineTransform*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    replace([[static int tolua_collect_ccBlendFunc (lua_State* tolua_S)
{
 ccBlendFunc* self = (ccBlendFunc*) tolua_tousertype(tolua_S,1,0);
    Mtolua_delete(self);
    return 0;
}]],[[]])

    WRITE(result)
end
