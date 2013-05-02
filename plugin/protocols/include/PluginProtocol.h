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
#ifndef __CCX_IPLUGIN_H__
#define __CCX_IPLUGIN_H__

#include "RegisterPlugin.h"

namespace cocos2d { namespace plugin {

/**
	The super class for all plugins.
*/

class PluginProtocol
{
public:
    virtual ~PluginProtocol() {}
    virtual bool init() { return true; }
    void setUserData(void* userData) { m_pUserData = userData; }
    void* getUserData() { return m_pUserData; }

    /**
    @brief plug-in info methods(name, version, SDK version)
    */
    virtual const char* getPluginName() = 0;
    virtual const char* getPluginVersion() = 0;

    /**
    @brief switch debug plug-in on/off
    */
    virtual void setDebugMode(bool bDebug) {}

protected:
    PluginProtocol() {}
    void* m_pUserData;
};

}} //namespace cocos2d { namespace plugin {

#endif /* __CCX_IPLUGIN_H__ */
