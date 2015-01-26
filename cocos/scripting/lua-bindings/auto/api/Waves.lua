
--------------------------------
-- @module Waves
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Waves] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Waves] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return Waves#Waves self (return value: cc.Waves)
        
--------------------------------
-- 
-- @function [parent=#Waves] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return Waves#Waves self (return value: cc.Waves)
        
--------------------------------
-- 
-- @function [parent=#Waves] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  initializes the action with amplitude, horizontal sin, vertical sin, a grid and duration 
-- @function [parent=#Waves] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int waves
-- @param #float amplitude
-- @param #bool horizontal
-- @param #bool vertical
-- @return Waves#Waves ret (return value: cc.Waves)
        
--------------------------------
-- 
-- @function [parent=#Waves] clone 
-- @param self
-- @return Waves#Waves ret (return value: cc.Waves)
        
--------------------------------
-- param time in seconds
-- @function [parent=#Waves] update 
-- @param self
-- @param #float time
-- @return Waves#Waves self (return value: cc.Waves)
        
return nil
