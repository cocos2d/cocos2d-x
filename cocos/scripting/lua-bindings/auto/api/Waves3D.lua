
--------------------------------
-- @module Waves3D
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
--  returns the amplitude rate 
-- @function [parent=#Waves3D] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  sets the amplitude to the effect 
-- @function [parent=#Waves3D] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
--------------------------------
--  sets the ampliture rate 
-- @function [parent=#Waves3D] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
--------------------------------
--  returns the amplitude of the effect 
-- @function [parent=#Waves3D] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  creates an action with duration, grid size, waves and amplitude 
-- @function [parent=#Waves3D] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int waves
-- @param #float amplitude
-- @return Waves3D#Waves3D ret (return value: cc.Waves3D)
        
--------------------------------
-- 
-- @function [parent=#Waves3D] clone 
-- @param self
-- @return Waves3D#Waves3D ret (return value: cc.Waves3D)
        
--------------------------------
-- param time in seconds
-- @function [parent=#Waves3D] update 
-- @param self
-- @param #float time
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
return nil
