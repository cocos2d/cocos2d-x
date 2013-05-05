/****************************************************************************
Copyright (c) 2012-2013 cocos2d-x.org

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
#include "PluginManager.h"
#include <map>
#include <string>
namespace cocos2d { namespace plugin {

typedef struct tagPluginInfo
{
    PluginCreator pfnCreator;
    PluginProtocol* pInstance;
}PluginInfo;

typedef std::map<std::string, PluginInfo> PluginCreatorMap;
typedef std::pair<std::string, PluginInfo> PluginCreatorPair;

static PluginCreatorMap* s_pCreatorMap = NULL;
static PluginManager* s_pPluginManager = NULL;

PluginManager::PluginManager(void)
{
}

PluginManager::~PluginManager()
{
    PluginCreatorMap::iterator it = s_pCreatorMap->begin();
    for (;it != s_pCreatorMap->end();++it)
    {
        if (it->second.pInstance != NULL) {
            delete it->second.pInstance;
            it->second.pInstance = NULL;
        }
    }
}

PluginManager* PluginManager::getInstance()
{
    if (s_pPluginManager == NULL)
    {
        s_pPluginManager = new PluginManager();
    }
    return s_pPluginManager;
}

void PluginManager::end()
{
    if (s_pPluginManager != NULL)
    {
        delete s_pPluginManager;
        s_pPluginManager = NULL;
    }
}

PluginProtocol* PluginManager::loadPlugin(const char* name)
{
    PluginProtocol* pRet = NULL;
    do {
        if (name == NULL || strlen(name) == 0) break;
        PluginCreatorMap::iterator it = s_pCreatorMap->find(name);
        if (it != s_pCreatorMap->end())
        {
            if (it->second.pInstance == NULL) {
                it->second.pInstance = it->second.pfnCreator();
            }
            else {
                // LOGD("The plugin has been loaded, return the loaded instance directly.");
            }
            pRet = it->second.pInstance;
        }
    } while (false);
    return pRet;
}

void PluginManager::unloadPlugin(const char* name)
{
    do {
        if (name == NULL || strlen(name) == 0) break;
        PluginCreatorMap::iterator it = s_pCreatorMap->find(name);
        if (it != s_pCreatorMap->end())
        {
            if (it->second.pInstance != NULL) {
                delete it->second.pInstance;
                it->second.pInstance = NULL;
            }
        }
    } while (false);
}

bool PluginManager::registerPlugin(const char* name, PluginCreator pfnCreator)
{
    if (s_pCreatorMap == NULL) {
        static PluginCreatorMap s_CreatorMap;
        s_pCreatorMap = &s_CreatorMap;
    }
    PluginInfo info;
    info.pfnCreator = pfnCreator;
    info.pInstance = NULL;
    s_pCreatorMap->insert(PluginCreatorPair(name, info));
    return true;
}

}} //namespace cocos2d { namespace plugin {
