/** @file PluginFactory.h
 */
#ifndef __CCX_PLUGINMANAGER_H__
#define __CCX_PLUGINMANAGER_H__

#include "PluginProtocol.h"
#include "PluginFactory.h"
#include <map>
#include <string>

namespace anysdk { namespace framework {

/**   
 *  @class  PluginManager  
 */
class PluginManager
{
public:
	virtual ~PluginManager();
    /**
     @brief Get singleton of PluginManager
     */
    static PluginManager* getInstance();
    /**
     @brief Destory the instance of PluginManager
     */
    static void end();
    
    /**
     @brief load the plugin by name and type
     @param the name of plugin
     @param the type of plugin
     */
    PluginProtocol* loadPlugin(const char* name, int pluginType);
    /**
     @brief unload the plugin by name and type
     @param the name of plugin
     @param the type of plugin
     */
    void unloadPlugin(const char* name, int pluginType = 0);


private:
    PluginManager(void);
    std::map<std::string, PluginProtocol*> _pluginsMap;
//    bool _isDebug;
};

}} //namespace anysdk { namespace framework {

#endif /* __CCX_PLUGINMANAGER_H__ */
