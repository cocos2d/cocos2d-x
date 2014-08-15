/****************************************************************************
 Copyright (c) 2014 cocos2d-x.org
 
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

#include "base/CCModuleManager.h"
#include <unordered_map>
#include "base/CCConsole.h"

using namespace std;

//RegisterJPEG *temp = new RegisterJPEG();

NS_CC_BEGIN

void ModuleManager::registerModule(const string &moduleName, void* module)
{
    auto &moduleMap = createMap();
    if (moduleMap.find(moduleName) != moduleMap.end())
    {
        CCLOG("module: %s exists", moduleName.c_str());
        return;
    }
    
    moduleMap[moduleName] = module;
}

void ModuleManager::unRegisterModule(const string &moduleName)
{
    auto &moduleMap = createMap();
    moduleMap.erase(moduleName);
}

void* ModuleManager::getModule(const string &moduleName)
{
    auto &moduleMap = createMap();
    auto result = moduleMap.find(moduleName);
    if (result != moduleMap.end())
    {
        return result->second;
    }
    else
        return nullptr;
}

unordered_map<std::string, void*>& ModuleManager::createMap()
{
    static unordered_map<string, void*> map;
    return map;
}

NS_CC_END
