
--------------------------------
-- @module ProtocolShare
-- @extend PluginProtocol
-- @parent_module plugin

--------------------------------
-- brief share result callback
-- @function [parent=#ProtocolShare] onShareResult 
-- @param self
-- @param #int ret
-- @param #char msg
        
--------------------------------
-- brief config the share developer info<br>
-- param devInfo This parameter is the info of developer,<br>
-- different plugin have different format<br>
-- warning Must invoke this interface before other interfaces.<br>
-- And invoked only once.
-- @function [parent=#ProtocolShare] configDeveloperInfo 
-- @param self
-- @param #map_table devInfo
        
return nil
