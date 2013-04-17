#ifndef __CXX_IPLUGIN_H__
#define __CXX_IPLUGIN_H__

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

#endif /* __CXX_IPLUGIN_H__ */
