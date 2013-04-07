#include "RegisterPlugin.h"
#include "PluginManager.h"

namespace cocos2d { namespace plugin {

RegisterPlugin::RegisterPlugin(const char* name, PluginCreator pfnCreator)
{
    PluginManager::getInstance()->registerPlugin(name, pfnCreator);
}

}} //namespace cocos2d { namespace plugin {
