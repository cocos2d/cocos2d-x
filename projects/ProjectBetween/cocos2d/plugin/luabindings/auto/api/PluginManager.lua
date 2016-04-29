
--------------------------------
-- @module PluginManager
-- @parent_module plugin

--------------------------------
--  unload the plugin by name 
-- @function [parent=#PluginManager] unloadPlugin 
-- @param self
-- @param #char name
        
--------------------------------
--  load the plugin by name 
-- @function [parent=#PluginManager] loadPlugin 
-- @param self
-- @param #char name
-- @return plugin::PluginProtocol#plugin::PluginProtocol ret (return value: cc.plugin::PluginProtocol)
        
--------------------------------
--  Destory the instance of PluginManager 
-- @function [parent=#PluginManager] end 
-- @param self
        
--------------------------------
--  Get singleton of PluginManager 
-- @function [parent=#PluginManager] getInstance 
-- @param self
-- @return plugin::PluginManager#plugin::PluginManager ret (return value: cc.plugin::PluginManager)
        
return nil
