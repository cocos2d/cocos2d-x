
--------------------------------
-- @module CameraBackgroundSkyBoxBrush
-- @extend CameraBackgroundBrush
-- @parent_module cc

--------------------------------
-- init Skybox.
-- @function [parent=#CameraBackgroundSkyBoxBrush] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Set skybox texutre <br>
-- param texture Skybox texture
-- @function [parent=#CameraBackgroundSkyBoxBrush] setTexture 
-- @param self
-- @param #cc.TextureCube texture
-- @return CameraBackgroundSkyBoxBrush#CameraBackgroundSkyBoxBrush self (return value: cc.CameraBackgroundSkyBoxBrush)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundSkyBoxBrush] initBuffer 
-- @param self
-- @return CameraBackgroundSkyBoxBrush#CameraBackgroundSkyBoxBrush self (return value: cc.CameraBackgroundSkyBoxBrush)
        
--------------------------------
-- @overload self         
-- @overload self, string, string, string, string, string, string         
-- @function [parent=#CameraBackgroundSkyBoxBrush] create
-- @param self
-- @param #string positive_x
-- @param #string negative_x
-- @param #string positive_y
-- @param #string negative_y
-- @param #string positive_z
-- @param #string negative_z
-- @return CameraBackgroundSkyBoxBrush#CameraBackgroundSkyBoxBrush ret (return value: cc.CameraBackgroundSkyBoxBrush)

--------------------------------
-- Get brush type. Should be BrushType::SKYBOX<br>
-- return brush type
-- @function [parent=#CameraBackgroundSkyBoxBrush] getBrushType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- Draw background
-- @function [parent=#CameraBackgroundSkyBoxBrush] drawBackground 
-- @param self
-- @param #cc.Camera camera
-- @return CameraBackgroundSkyBoxBrush#CameraBackgroundSkyBoxBrush self (return value: cc.CameraBackgroundSkyBoxBrush)
        
--------------------------------
-- 
-- @function [parent=#CameraBackgroundSkyBoxBrush] CameraBackgroundSkyBoxBrush 
-- @param self
-- @return CameraBackgroundSkyBoxBrush#CameraBackgroundSkyBoxBrush self (return value: cc.CameraBackgroundSkyBoxBrush)
        
return nil
