
--------------------------------
-- @module CameraBackgroundColorBrush
-- @extend CameraBackgroundDepthBrush
-- @parent_module cc

--------------------------------
-- Set clear color<br>
-- param color Color used to clear the color buffer
-- @function [parent=#CameraBackgroundColorBrush] setColor 
-- @param self
-- @param #color4f_table color
-- @return CameraBackgroundColorBrush#CameraBackgroundColorBrush self (return value: cc.CameraBackgroundColorBrush)
        
--------------------------------
-- Create a color brush<br>
-- param color Color used to clear the color buffer<br>
-- param depth Depth used to clear the depth buffer<br>
-- return Created brush
-- @function [parent=#CameraBackgroundColorBrush] create 
-- @param self
-- @param #color4f_table color
-- @param #float depth
-- @return CameraBackgroundColorBrush#CameraBackgroundColorBrush ret (return value: cc.CameraBackgroundColorBrush)
        
--------------------------------
-- Get brush type. Should be BrushType::COLOR<br>
-- return brush type
-- @function [parent=#CameraBackgroundColorBrush] getBrushType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundColorBrush] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundColorBrush] CameraBackgroundColorBrush 
-- @param self
-- @return CameraBackgroundColorBrush#CameraBackgroundColorBrush self (return value: cc.CameraBackgroundColorBrush)
        
return nil
