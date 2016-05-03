
--------------------------------
-- @module ProtocolAds
-- @extend PluginProtocol
-- @parent_module plugin

--------------------------------
-- brief show adview<br>
-- param info The information of adview will be shown<br>
-- Pay attention to the subclass definition<br>
-- param pos The position where the adview be shown.
-- @function [parent=#ProtocolAds] showAds 
-- @param self
-- @param #map_table info
-- @param #int pos
        
--------------------------------
-- brief Hide the adview<br>
-- param info The information of adview will be hided
-- @function [parent=#ProtocolAds] hideAds 
-- @param self
-- @param #map_table info
        
--------------------------------
-- brief Query the points of player
-- @function [parent=#ProtocolAds] queryPoints 
-- @param self
        
--------------------------------
-- brief Spend the points.<br>
-- Use this method to notify server spend points.<br>
-- param points Need spend number of points
-- @function [parent=#ProtocolAds] spendPoints 
-- @param self
-- @param #int points
        
--------------------------------
-- brief config the application info<br>
-- param devInfo This parameter is the info of aplication,<br>
-- different plugin have different format<br>
-- warning Must invoke this interface before other interfaces.<br>
-- And invoked only once.
-- @function [parent=#ProtocolAds] configDeveloperInfo 
-- @param self
-- @param #map_table devInfo
        
return nil
