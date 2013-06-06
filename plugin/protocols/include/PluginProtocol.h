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

#include "PluginParam.h"
#include <vector>

namespace cocos2d { namespace plugin {

/**
	The super class for all plugins.
*/
class PluginFactory;
class PluginProtocol
{
public:
    virtual ~PluginProtocol();

    /**
    @brief plug-in info methods(name, version, SDK version)
    */
    inline const char* getPluginName() { return m_pPluginName.c_str(); }
    const char* getPluginVersion();
    const char* getSDKVersion();

    /**
    @brief switch debug plug-in on/off
    */
    void setDebugMode(bool bDebug);

    /**
     * @brief methods for reflections
     */
    void callFuncWithParam(const char* funcName, PluginParam* param, ...);
    void callFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    const char* callStringFuncWithParam(const char* funcName, PluginParam* param, ...);
    const char* callStringFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    int callIntFuncWithParam(const char* funcName, PluginParam* param, ...);
    int callIntFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    bool callBoolFuncWithParam(const char* funcName, PluginParam* param, ...);
    bool callBoolFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

    float callFloatFuncWithParam(const char* funcName, PluginParam* param, ...);
    float callFloatFuncWithParam(const char* funcName, std::vector<PluginParam*> params);

protected:
    PluginProtocol() {}

private:
    friend class PluginFactory;
    inline void setPluginName(const char* name) {
    	m_pPluginName = name;
    }
    std::string m_pPluginName;
};

}} //namespace cocos2d { namespace plugin {

#endif /* __CCX_IPLUGIN_H__ */
