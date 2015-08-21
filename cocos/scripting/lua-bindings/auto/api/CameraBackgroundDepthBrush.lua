
--------------------------------
-- @module CameraBackgroundDepthBrush
-- @extend CameraBackgroundBrush
-- @parent_module cc

--------------------------------
-- Set depth<br>
-- param depth Depth used to clear depth buffer
-- @function [parent=#CameraBackgroundDepthBrush] setDepth 
-- @param self
-- @param #float depth
-- @return CameraBackgroundDepthBrush#CameraBackgroundDepthBrush self (return value: cc.CameraBackgroundDepthBrush)
        
--------------------------------
-- Create a depth brush<br>
-- param depth Depth used to clear the depth buffer<br>
-- return Created brush
-- @function [parent=#CameraBackgroundDepthBrush] create 
-- @param self
-- @param #float depth
-- @return CameraBackgroundDepthBrush#CameraBackgroundDepthBrush ret (return value: cc.CameraBackgroundDepthBrush)
        
--------------------------------
-- Get brush type. Should be BrushType::DEPTH<br>
-- return brush type
-- @function [parent=#CameraBackgroundDepthBrush] getBrushType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Draw background
-- @function [parent=#CameraBackgroundDepthBrush] drawBackground 
-- @param self
-- @param #cc.Camera camera
-- @return CameraBackgroundDepthBrush#CameraBackgroundDepthBrush self (return value: cc.CameraBackgroundDepthBrush)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundDepthBrush] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundDepthBrush] CameraBackgroundDepthBrush 
-- @param self
-- @return CameraBackgroundDepthBrush#CameraBackgroundDepthBrush self (return value: cc.CameraBackgroundDepthBrush)
        
return nil
