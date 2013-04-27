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
#ifndef __CCX_REGISTERPLUGIN_H__
#define __CCX_REGISTERPLUGIN_H__

namespace cocos2d { namespace plugin {

class PluginProtocol;

typedef PluginProtocol* (*PluginCreator)();

/**
	@brief RegisterPlugin class is only for associating plugin name with plugin creator.
	Plugin developers don't need to use this class directly.
	Using the macros 'PLUGIN_REGISTER_DECL' and 'PLUGIN_REGISTER_IMPL' instead.
*/
class RegisterPlugin
{
public:
    RegisterPlugin(const char* name, PluginCreator pfnCreator);
};

#define PLUGIN_REGISTER_DECL(type) \
    private: type() {} \
    		static RegisterPlugin s_registerPlugin; \
    public: static PluginProtocol* createPlugin(); \
            virtual const char* getPluginName() { return #type; };

#define PLUGIN_REGISTER_IMPL(type) \
RegisterPlugin type::s_registerPlugin(#type, type::createPlugin); \
PluginProtocol* type::createPlugin() { \
    type* pRet = new type(); \
    if (pRet) { \
        if (!pRet->init()) { \
            delete pRet; pRet = NULL; \
        } \
    } \
    return pRet; \
}

}} //namespace cocos2d { namespace plugin {

#endif /* __CCX_REGISTERPLUGIN_H__ */
