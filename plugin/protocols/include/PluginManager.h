#ifndef __CCX_PLUGINMANAGER_H__
#define __CCX_PLUGINMANAGER_H__

#include "PluginProtocol.h"
#include "RegisterPlugin.h"

namespace cocos2d { namespace plugin {

class PluginManager
{
public:
	virtual ~PluginManager();
	/** Get singleton of PluginManager */
    static PluginManager* getInstance();
    /** Destory the instance of PluginManager */
    static void end();
    
    /** load the plugin by name */
    PluginProtocol* loadPlugin(const char* name);
    /** unload the plugin by name */
    void unloadPlugin(const char* name);
private:
	friend class RegisterPlugin;
	bool registerPlugin(const char* name, PluginCreator pfnCreator);
    PluginManager(void);
};

}} //namespace cocos2d { namespace plugin {

#endif /* __CCX_PLUGINMANAGER_H__ */
