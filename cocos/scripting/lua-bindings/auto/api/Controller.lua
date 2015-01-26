
--------------------------------
-- @module Controller
-- @parent_module cc

--------------------------------
--  Activate receives key event from external key. e.g. back,menu.<br>
-- Controller receives only standard key which contained within enum Key by default.<br>
-- warning The API only work on the android platform for support diversified game controller.<br>
-- param externalKeyCode  external key code<br>
-- param receive  true if external key event on this controller should be receive, false otherwise.
-- @function [parent=#Controller] receiveExternalKeyEvent 
-- @param self
-- @param #int externalKeyCode
-- @param #bool receive
-- @return Controller#Controller self (return value: cc.Controller)
        
--------------------------------
-- 
-- @function [parent=#Controller] getDeviceName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#Controller] isConnected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Controller] getDeviceId 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Changes the tag that is used to identify the controller easily.<br>
-- param tag   A integer that identifies the controller.
-- @function [parent=#Controller] setTag 
-- @param self
-- @param #int tag
-- @return Controller#Controller self (return value: cc.Controller)
        
--------------------------------
-- Returns a tag that is used to identify the controller easily.<br>
-- return An integer that identifies the controller.
-- @function [parent=#Controller] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  To start discovering new controllers<br>
-- warning The API only work on the IOS platform.Empty implementation on Android
-- @function [parent=#Controller] startDiscoveryController 
-- @param self
-- @return Controller#Controller self (return value: cc.Controller)
        
--------------------------------
--  End the discovery process<br>
-- warning The API only work on the IOS platform.Empty implementation on Android
-- @function [parent=#Controller] stopDiscoveryController 
-- @param self
-- @return Controller#Controller self (return value: cc.Controller)
        
--------------------------------
--  Gets a controller with its tag<br>
-- param tag   An identifier to find the controller.
-- @function [parent=#Controller] getControllerByTag 
-- @param self
-- @param #int tag
-- @return Controller#Controller ret (return value: cc.Controller)
        
return nil
