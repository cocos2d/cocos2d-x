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
using namespace cocos2d::network;

static int get_field_int(lua_State *L, const char *field, int def)
{
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    if(lua_isnil(L, -1))
    {
        //luaL_error(L, "get_field_int: field '%s' no exists.", field);
        return def;
    }
    return lua_toint(L, -1);
}

static std::string get_field_string(lua_State *L, const char *field, const char *def)
{
    lua_pushstring(L, field);
    lua_gettable(L, -2);
    if(lua_isnil(L, -1))
    {
        //luaL_error(L, "get_field_string: field '%s' no exists.", field);
        return def;
    }
    return std::string(lua_tostring(L, -1));
}

static int set_field_string(lua_State *L, const char *field, const char *value)
{
    lua_pushstring(L, field);
    lua_pushstring(L, value);
    lua_settable(L, -3);
}

static Downloader *checkDownloader (lua_State *L) {
    void *ud = luaL_checkudata(L, 1, "cc.Downloader.meta");
    luaL_argcheck(L, ud != NULL, 1, "`Downloader' expected");
    return (Downloader *)ud;
}

static void newTaskTable(lua_State *L, std::shared_ptr<const DownloaderTask> &task)
{
    lua_newtable(L);
    set_field_string(L, "identifier", task->identifier.c_str());
    set_field_string(L, "requestURL", task->requestURL.c_str());
    set_field_string(L, "storagePath", task->storagePath.c_str());
}


static int lua_downloader_new(lua_State *L)
{
    Downloader *downloader = nullptr;
    int argc = lua_gettop(L) - 1;
    if(argc >= 1) { 
        //parse DownloaderHints
        if(!lua_istable(L, -1)) {
            luaL_error(L, "cc.Downloader.new: first argument should be table if set");
            return 0;
        }
        DownloaderHints hints;
        hints.countOfMaxProcessingTasks = get_field_int(L, "countOfMaxProcessingTasks", 6);
        hints.timeoutInSeconds = get_field_int(L, "timeoutInSeconds", 45);
        hints.tempFileNameSuffix = get_field_string(L, "tempFileNameSuffix", ".tmp");
        
        auto ptr = lua_newuserdata(L, sizeof(Downloader));
        downloader = new (ptr) Downloader(hints);
    }
    else
    {
        auto ptr = lua_newuserdata(L, sizeof(Downloader));
        downloader = new (ptr) Downloader();
    }

    luaL_getmetatable(L, "cc.Downloader.meta");
    lua_setmetatable(L, -2);

    return 1;
}


static int lua_downloader_createDownloadDataTask(lua_State *L)
{
    Downloader *d = checkDownloader(L);
    int argc = lua_gettop(L) - 1;
    std::string url = "";
    std::string identifier = "";
    
    if(argc == 0 ) 
    {
        luaL_error(L, "cc.Downloader.createDownloadDataTask argument number not required");
        return 0;
    }

    if(argc >= 1) url = lua_tostring(L, 2);
    if(arg >= 2) identifier = lua_tostring(L, 3);
    auto tsk = d->createDownloadDataTask(url, identifier);

    newTaskTable(L, tsk);
    return 1;
}

static int lua_downloader_createDownloadFileTask(lua_State *L)
{
    Downloader *d = checkDownloader(L);
    int argc = lua_gettop(L) - 1;
    std::string url = "";
    std::string storagePath = "";
    std::string identifier = "";
    
    if(argc < 2 ) 
    {
        luaL_error(L, "cc.Downloader.lua_downloader_createDownloadFileTask argument not enough!");
        return 0;
    }

    url = lua_tostring(L, 2);
    storagePath = lua_tostring(L, 3);
    if(arg > 2) identifier = lua_tostring(L, 4);

    auto tsk = d->lua_downloader_createDownloadFileTask(url, storagePath, identifier);

    newTaskTable(L, tsk);
    return 1;
}
static int lua_downloader_setOnFileTaskSuccess(lua_State *L)
{
    
}
static int lua_downloader_setOnTaskProgress(lua_State *L)
{
    
}
static int lua_downloader_setOnTaskError(lua_State *L)
{
    
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
