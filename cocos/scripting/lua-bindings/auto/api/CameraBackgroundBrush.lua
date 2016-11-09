
--------------------------------
-- @module CameraBackgroundBrush
-- @extend Ref
-- @parent_module cc

--------------------------------
-- get brush type<br>
-- return BrushType
-- @function [parent=#CameraBackgroundBrush] getBrushType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- draw the background
-- @function [parent=#CameraBackgroundBrush] drawBackground 
-- @param self
-- @param #cc.Camera 
-- @return CameraBackgroundBrush#CameraBackgroundBrush self (return value: cc.CameraBackgroundBrush)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundBrush] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundBrush] isValid 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Creates a Skybox brush with 6 textures.<br>
-- param positive_x texture for the right side of the texture cube face.<br>
-- param negative_x texture for the up side of the texture cube face.<br>
-- param positive_y texture for the top side of the texture cube face<br>
-- param negative_y texture for the bottom side of the texture cube face<br>
-- param positive_z texture for the forward side of the texture cube face.<br>
-- param negative_z texture for the rear side of the texture cube face.<br>
-- return  A new brush inited with given parameters.
-- @function [parent=#CameraBackgroundBrush] createSkyboxBrush 
-- @param self
-- @param #string positive_x
-- @param #string negative_x
-- @param #string positive_y
-- @param #string negative_y
-- @param #string positive_z
-- @param #string negative_z
-- @return CameraBackgroundSkyBoxBrush#CameraBackgroundSkyBoxBrush ret (return value: cc.CameraBackgroundSkyBoxBrush)
        
--------------------------------
-- Creates a color brush<br>
-- param color Color of brush<br>
-- param depth Depth used to clear depth buffer<br>
-- return Created brush
-- @function [parent=#CameraBackgroundBrush] createColorBrush 
-- @param self
-- @param #color4f_table color
-- @param #float depth
-- @return CameraBackgroundColorBrush#CameraBackgroundColorBrush ret (return value: cc.CameraBackgroundColorBrush)
        
--------------------------------
-- Creates a none brush, it does nothing when clear the background<br>
-- return Created brush.
-- @function [parent=#CameraBackgroundBrush] createNoneBrush 
-- @param self
-- @return CameraBackgroundBrush#CameraBackgroundBrush ret (return value: cc.CameraBackgroundBrush)
        
--------------------------------
-- Creates a depth brush, which clears depth buffer with a given depth.<br>
-- param depth Depth used to clear depth buffer<br>
-- return Created brush
-- @function [parent=#CameraBackgroundBrush] createDepthBrush 
-- @param self
-- @return CameraBackgroundDepthBrush#CameraBackgroundDepthBrush ret (return value: cc.CameraBackgroundDepthBrush)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundBrush] CameraBackgroundBrush 
-- @param self
-- @return CameraBackgroundBrush#CameraBackgroundBrush self (return value: cc.CameraBackgroundBrush)
        
return nil
