
--------------------------------
-- @module Lens3D
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Lens3D] setPosition 
-- @param self
-- @param #vec2_table position
        
--------------------------------
--  Set whether lens is concave 
-- @function [parent=#Lens3D] setConcave 
-- @param self
-- @param #bool concave
        
--------------------------------
--  Set lens center position 
-- @function [parent=#Lens3D] setLensEffect 
-- @param self
-- @param #float lensEffect
        
--------------------------------
-- 
-- @function [parent=#Lens3D] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get lens center position 
-- @function [parent=#Lens3D] getLensEffect 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  creates the action with center position, radius, a grid size and duration 
-- @function [parent=#Lens3D] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #vec2_table position
-- @param #float radius
-- @return Lens3D#Lens3D ret (return value: cc.Lens3D)
        
--------------------------------
-- 
-- @function [parent=#Lens3D] clone 
-- @param self
-- @return Lens3D#Lens3D ret (return value: cc.Lens3D)
        
--------------------------------
-- 
-- @function [parent=#Lens3D] update 
-- @param self
-- @param #float time
        
return nil
