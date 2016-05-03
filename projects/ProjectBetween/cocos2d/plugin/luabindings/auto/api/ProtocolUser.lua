
--------------------------------
-- @module ProtocolUser
-- @extend PluginProtocol
-- @parent_module plugin

--------------------------------
-- brief config the application info<br>
-- param devInfo This parameter is the info of aplication,<br>
-- different plugin have different format<br>
-- warning Must invoke this interface before other interfaces.<br>
-- And invoked only once.
-- @function [parent=#ProtocolUser] configDeveloperInfo 
-- @param self
-- @param #map_table devInfo
        
--------------------------------
-- 
-- @function [parent=#ProtocolUser] isLoggedIn 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get session ID<br>
-- return If user logined, return value is session ID;<br>
-- else return value is empty string.
-- @function [parent=#ProtocolUser] getSessionID 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief get Access Token
-- @function [parent=#ProtocolUser] getAccessToken 
-- @param self
-- @return string#string ret (return value: string)
        
return nil
