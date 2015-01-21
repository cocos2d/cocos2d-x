
--------------------------------
-- @module Ripple3D
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Ripple3D] setAmplitudeRate 
-- @param self
-- @param #float fAmplitudeRate
-- @return Ripple3D#Ripple3D self (return value: cc.Ripple3D)
        
--------------------------------
-- 
-- @function [parent=#Ripple3D] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Ripple3D] setAmplitude 
-- @param self
-- @param #float fAmplitude
-- @return Ripple3D#Ripple3D self (return value: cc.Ripple3D)
        
--------------------------------
-- 
-- @function [parent=#Ripple3D] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  set center position 
-- @function [parent=#Ripple3D] setPosition 
-- @param self
-- @param #vec2_table position
-- @return Ripple3D#Ripple3D self (return value: cc.Ripple3D)
        
--------------------------------
--  get center position 
-- @function [parent=#Ripple3D] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  creates the action with radius, number of waves, amplitude, a grid size and duration 
-- @function [parent=#Ripple3D] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #vec2_table position
-- @param #float radius
-- @param #unsigned int waves
-- @param #float amplitude
-- @return Ripple3D#Ripple3D ret (return value: cc.Ripple3D)
        
--------------------------------
-- 
-- @function [parent=#Ripple3D] clone 
-- @param self
-- @return Ripple3D#Ripple3D ret (return value: cc.Ripple3D)
        
--------------------------------
-- param time in seconds
-- @function [parent=#Ripple3D] update 
-- @param self
-- @param #float time
-- @return Ripple3D#Ripple3D self (return value: cc.Ripple3D)
        
return nil
