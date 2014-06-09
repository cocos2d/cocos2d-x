/****************************************************************************
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
#include "Cocos2dxLuaLoader.h"
#include <string>
#include <algorithm>

#include "CCLuaStack.h"

using namespace cocos2d;

extern "C"
{
    int cocos2dx_lua_loader(lua_State *L)
    {
        static const std::string SUFFIX_LUA = ".lua";

        std::string filename(luaL_checkstring(L, 1));
        lua_getglobal(L, kCCLuaDebuggerGlobalKey);
        if (lua_toboolean(L, -1))
        {
            return luaL_loadfile(L, filename.c_str()) == 0 ? 1 : 0;
        }
        lua_pop(L, 1);

        size_t pos = filename.rfind(SUFFIX_LUA);
        if (pos == filename.length() - SUFFIX_LUA.length())
        {
            filename = filename.substr(0, pos);
        }

        pos = filename.find_first_of(".");
        while (pos != std::string::npos)
        {
            filename.replace(pos, 1, "/");
            pos = filename.find_first_of(".");
        }
        filename.append(".lua");

        // search file in package.path
        unsigned char* chunk = NULL;
        ssize_t chunkSize = 0;
        std::string chunkName;
        CCFileUtils* utils = CCFileUtils::sharedFileUtils();

        lua_getglobal(L, "package");
        lua_getfield(L, -1, "path");
        std::string searchpath(lua_tostring(L, -1));
        lua_pop(L, 1);
        size_t begin = 0;
        size_t next = searchpath.find_first_of(";", 0);

        do
        {
            if (next == std::string::npos) next = searchpath.length();
            std::string prefix = searchpath.substr(begin, next);
            if (prefix[0] == '.' && prefix[1] == '/')
            {
                prefix = prefix.substr(2);
            }

            pos = prefix.find("?.lua");
            chunkName = prefix.substr(0, pos).append(filename);
            chunkName = utils->fullPathForFilename(chunkName.c_str());
            if (utils->isFileExist(chunkName))
            {
                chunk = utils->getFileData(chunkName.c_str(), "rb", &chunkSize);
                break;
            }

            begin = next + 1;
            next = searchpath.find_first_of(";", begin);
        } while (begin < (int)searchpath.length());

        if (chunk)
        {
            LuaStack::lua_loadbuffer(L, (char*)chunk, (int)chunkSize, chunkName.c_str());
            delete []chunk;
        }
        else
        {
            return 0;
        }

        return 1;
    }
}
