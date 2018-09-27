/****************************************************************************
 Copyright (c) 2013-2016 Chukong Technologies Inc.
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
#include "scripting/lua-bindings/manual/network/lua_downloader.h"
#include "scripting/lua-bindings/manual/tolua_fix.h"
#include "scripting/lua-bindings/manual/CCLuaStack.h"
#include "scripting/lua-bindings/manual/CCLuaValue.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "scripting/lua-bindings/manual/cocos2d/LuaScriptHandlerMgr.h"

#include "network/CCDownloader.h"

#include <unordered_map>
#include <string>
#include <sstream>

using namespace cocos2d;


static int lua_downloader_new(lua_State *L)
{
    Downloader *downloader = nullptr;
    int argc = lua_gettop(L) - 1;
    if(argc == 1) { 
        //parse DownloaderHints
        if(lua_is)
    }
}

static const struct luaL_reg downloaderStaticFns[] = {
    {"new", lua_downloader_new},
    {nullptr, nullptr}
};

static const struct luaL_reg downloaderMemberFns[] = {
    {"createDownloadDataTask", lua_downloader_createDownloadDataTask},
    {"createDownloadFileTask", lua_downloader_createDownloadFileTask},
    {"setOnFileTaskSuccess",lua_downloader_setOnFileTaskSuccess},
    {"setOnTaskProgress",lua_downloader_setOnTaskProgress},
    {"setOnTaskError",lua_downloader_setOnTaskError},
    {nullptr, nullptr}
};

TOLUA_API int register_downloader(lua_State* L)
{
    luaL_newmetatable(L, "cc.Downloader.meta");
    lua_pushstring(L, "__index");
    lua_pushvalue(L, -2);  /* pushes the metatable */
    lua_settable(L, -3);  /* metatable.__index = metatable */

    luaL_openlib(L, nullptr, downloaderMemberFns, 0);
    luaL_openlib(L, "cc.Downloader", downloaderStaticFns, 0);
    return 1;
}
