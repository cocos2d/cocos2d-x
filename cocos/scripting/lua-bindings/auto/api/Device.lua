
--------------------------------
-- @module Device
-- @parent_module cc

--------------------------------
-- To enable or disable accelerometer.
-- @function [parent=#Device] setAccelerometerEnabled 
-- @param self
-- @param #bool isEnabled
-- @return Device#Device self (return value: cc.Device)
        
--------------------------------
-- Controls whether the screen should remain on.<br>
-- param keepScreenOn One flag indicating that the screen should remain on.
-- @function [parent=#Device] setKeepScreenOn 
-- @param self
-- @param #bool keepScreenOn
-- @return Device#Device self (return value: cc.Device)
        
--------------------------------
-- Sets the interval of accelerometer.
-- @function [parent=#Device] setAccelerometerInterval 
-- @param self
-- @param #float interval
-- @return Device#Device self (return value: cc.Device)
        
--------------------------------
-- Gets the DPI of device<br>
-- return The DPI of device.
-- @function [parent=#Device] getDPI 
-- @param self
-- @return int#int ret (return value: int)
        
return nil
