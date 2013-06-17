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
#include "PluginFactory.h"

namespace cocos2d { namespace plugin {

static PluginManager* s_pPluginManager = NULL;

PluginManager::PluginManager(void)
{
}

PluginManager::~PluginManager()
{
	std::map<std::string, PluginProtocol*>::iterator it = m_pluginsMap.begin();
    for (;it != m_pluginsMap.end();++it)
    {
        if (it->second != NULL) {
            delete it->second;
            it->second = NULL;
        }
    }
    m_pluginsMap.clear();
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

    PluginFactory::purgeFactory();
}

PluginProtocol* PluginManager::loadPlugin(const char* name)
{
    PluginProtocol* pRet = NULL;
    do {
        if (name == NULL || strlen(name) == 0) break;
        std::map<std::string, PluginProtocol*>::iterator it = m_pluginsMap.find(name);
        if (it != m_pluginsMap.end())
        {
            if (it->second == NULL) {
                it->second = PluginFactory::getInstance()->createPlugin(name);
            }
            pRet = it->second;
        } else
        {
        	pRet = PluginFactory::getInstance()->createPlugin(name);
        	m_pluginsMap[name] = pRet;
        }
    } while (false);

    return pRet;
}

void PluginManager::unloadPlugin(const char* name)
{
    do {
        if (name == NULL || strlen(name) == 0) break;
        std::map<std::string, PluginProtocol*>::iterator it = m_pluginsMap.find(name);
		if (it != m_pluginsMap.end())
        {
            if (it->second != NULL) {
                delete it->second;
                it->second = NULL;
            }
        }
    } while (false);
}

}} //namespace cocos2d { namespace plugin {
