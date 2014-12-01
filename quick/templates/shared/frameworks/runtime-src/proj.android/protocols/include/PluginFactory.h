/** @file PluginFactory.h
 */
#ifndef __CCX_PLUGIN_FACTORY_H__
#define __CCX_PLUGIN_FACTORY_H__

namespace anysdk { namespace framework {
/** @brief Plugin_type enum, with inline docs */
typedef enum {
	kPluginAds = 1,/**< enum value kPluginAds. */
	kPluginAnalytics,/**< enum value kPluginAnalytics. */
	kPluginIAP,/**< enum value kPluginIAP. */
	kPluginShare,/**< enum value kPluginShare. */
	kPluginUser,/**< enum value kPluginUser. */
	kPluginSocial,/**< enum value kPluginSocial. */
	kPluginPush,/**< enum value kPluginPush. */
}Plugin_type;

class PluginProtocol;
class PluginManager;
/**   
 *  @class  PluginFactory  
 */
class PluginFactory
{
public:
	virtual ~PluginFactory();
    /**
     @brief Get singleton of PluginFactory
     */
    static PluginFactory* getInstance();

    /**
     @brief Destory the instance of PluginFactory
     */
    static void purgeFactory();

private:
    friend class PluginManager;
    PluginFactory(void);

    /**
     @brief create the plugin by name and type
     @param the name of plugin
     @param the type of plugin
     */
    PluginProtocol* createPlugin(const char* name, int pluginType);
};

}} //namespace anysdk { namespace framework {

#endif /* __CCX_PLUGIN_FACTORY_H__ */
