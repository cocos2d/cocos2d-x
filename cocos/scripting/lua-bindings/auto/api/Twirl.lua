
--------------------------------
-- @module Twirl
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Twirl] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
-- 
-- @function [parent=#Twirl] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Twirl] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
-- 
-- @function [parent=#Twirl] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  set twirl center 
-- @function [parent=#Twirl] setPosition 
-- @param self
-- @param #vec2_table position
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
--  get twirl center 
-- @function [parent=#Twirl] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  creates the action with center position, number of twirls, amplitude, a grid size and duration 
-- @function [parent=#Twirl] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #vec2_table position
-- @param #unsigned int twirls
-- @param #float amplitude
-- @return Twirl#Twirl ret (return value: cc.Twirl)
        
--------------------------------
-- 
-- @function [parent=#Twirl] clone 
-- @param self
-- @return Twirl#Twirl ret (return value: cc.Twirl)
        
--------------------------------
-- param time in seconds
-- @function [parent=#Twirl] update 
-- @param self
-- @param #float time
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
return nil
