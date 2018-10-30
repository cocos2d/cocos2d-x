/****************************************************************************
 Copyright (c) 2011-2012 cocos2d-x.org
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
#include "scripting/lua-bindings/manual/Cocos2dxLuaLoader.h"
#include <string>
#include <algorithm>

#include "scripting/lua-bindings/manual/CCLuaStack.h"
#include "scripting/lua-bindings/manual/CCLuaEngine.h"
#include "platform/CCFileUtils.h"

using namespace cocos2d;

extern "C"
{
    int cocos2dx_lua_loader(lua_State *L)
    {
        static const std::string BYTECODE_FILE_EXT    = ".luac";
        static const std::string NOT_BYTECODE_FILE_EXT = ".lua";

        std::string filename(luaL_checkstring(L, 1));
        size_t pos = filename.rfind(BYTECODE_FILE_EXT);
        if (pos != std::string::npos && pos == filename.length() - BYTECODE_FILE_EXT.length())
            filename = filename.substr(0, pos);
        else
        {
            pos = filename.rfind(NOT_BYTECODE_FILE_EXT);
            if (pos != std::string::npos && pos == filename.length() - NOT_BYTECODE_FILE_EXT.length())
                filename = filename.substr(0, pos);
        }

        pos = filename.find_first_of(".");
        while (pos != std::string::npos)
        {
            filename.replace(pos, 1, "/");
            pos = filename.find_first_of(".");
        }

        // search file in package.path
        Data chunk;
        std::string chunkName;
        FileUtils* utils = FileUtils::getInstance();

        lua_getglobal(L, "package");
        lua_getfield(L, -1, "path");
        std::string searchpath(lua_tostring(L, -1));
        lua_pop(L, 1);
        size_t begin = 0;
        size_t next = searchpath.find_first_of(";", 0);

        do
        {
            if (next == std::string::npos)
                next = searchpath.length();
            std::string prefix = searchpath.substr(begin, next-begin);
            if (prefix[0] == '.' && prefix[1] == '/')
                prefix = prefix.substr(2);

            pos = prefix.rfind(BYTECODE_FILE_EXT);
            if (pos != std::string::npos && pos == prefix.length() - BYTECODE_FILE_EXT.length())
            {
                prefix = prefix.substr(0, pos);
            }
            else
            {
                pos = prefix.rfind(NOT_BYTECODE_FILE_EXT);
                if (pos != std::string::npos && pos == prefix.length() - NOT_BYTECODE_FILE_EXT.length())
                    prefix = prefix.substr(0, pos);
            }
            pos = prefix.find_first_of("?", 0);
            while (pos != std::string::npos)
            {
                prefix.replace(pos, 1, filename);
                pos = prefix.find_first_of("?", pos + filename.length() + 1);
            }
            chunkName = prefix + BYTECODE_FILE_EXT;
            if (utils->isFileExist(chunkName) && !utils->isDirectoryExist(chunkName))
            {
                chunk = utils->getDataFromFile(chunkName);
                break;
            }
            else
            {
                chunkName = prefix + NOT_BYTECODE_FILE_EXT;
                if (utils->isFileExist(chunkName) && !utils->isDirectoryExist(chunkName))
                {
                    chunk = utils->getDataFromFile(chunkName);
                    break;
                }
                else
                {
                    chunkName = prefix;
                    if (utils->isFileExist(chunkName) && !utils->isDirectoryExist(chunkName))
                    {
                        chunk = utils->getDataFromFile(chunkName);
                        break;
                    }
                }
            }

            begin = next + 1;
            next = searchpath.find_first_of(";", begin);
        } while (begin < searchpath.length());
        if (chunk.getSize() > 0)
        {
            LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
            stack->luaLoadBuffer(L, reinterpret_cast<const char*>(chunk.getBytes()),
                                 static_cast<int>(chunk.getSize()), chunkName.c_str());
        }
        else
        {
            CCLOG("can not get file data of %s", chunkName.c_str());
            return 0;
        }

        return 1;
    }
}
