
--------------------------------
-- @module Twirl
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- brief Set the amplitude rate of the effect.<br>
-- param amplitudeRate The value of amplitude rate will be set.
-- @function [parent=#Twirl] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
-- brief Initializes the action with center position, number of twirls, amplitude, a grid size and duration.<br>
-- param duration Specify the duration of the Twirl action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param position Specify the center position of the twirl action.<br>
-- param twirls Specify the twirls count of the Twirl action.<br>
-- param amplitude Specify the amplitude of the Twirl action.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#Twirl] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #vec2_table position
-- @param #unsigned int twirls
-- @param #float amplitude
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get the amplitude rate of the effect.<br>
-- return Return the amplitude rate of the effect.
-- @function [parent=#Twirl] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Set the amplitude to the effect.<br>
-- param amplitude The value of amplitude will be set.
-- @function [parent=#Twirl] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
-- brief Get the amplitude of the effect.<br>
-- return Return the amplitude of the effect.
-- @function [parent=#Twirl] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Set the center position of twirl action.<br>
-- param position The center position of twirl action will be set.
-- @function [parent=#Twirl] setPosition 
-- @param self
-- @param #vec2_table position
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
-- brief Get the center position of twirl action.<br>
-- return The center position of twirl action.
-- @function [parent=#Twirl] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- brief Create the action with center position, number of twirls, amplitude, a grid size and duration.<br>
-- param duration Specify the duration of the Twirl action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param position Specify the center position of the twirl action.<br>
-- param twirls Specify the twirls count of the Twirl action.<br>
-- param amplitude Specify the amplitude of the Twirl action.<br>
-- return If the creation success, return a pointer of Twirl action; otherwise, return nil.
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
-- 
-- @function [parent=#Twirl] update 
-- @param self
-- @param #float time
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
--------------------------------
-- 
-- @function [parent=#Twirl] Twirl 
-- @param self
-- @return Twirl#Twirl self (return value: cc.Twirl)
        
return nil
