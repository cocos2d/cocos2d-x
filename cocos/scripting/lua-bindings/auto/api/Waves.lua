
--------------------------------
-- @module Waves
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- brief Set the amplitude rate of the effect.<br>
-- param amplitudeRate The value of amplitude rate will be set.
-- @function [parent=#Waves] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return Waves#Waves self (return value: cc.Waves)
        
--------------------------------
-- brief Initializes the action with amplitude, horizontal sin, vertical sin, grid size, waves count and duration.<br>
-- param duration Specify the duration of the Waves action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param waves Specify the waves count of the Waves action.<br>
-- param amplitude Specify the amplitude of the Waves action.<br>
-- param horizontal Specify whether waves on horizontal.<br>
-- param vertical Specify whether waves on vertical.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#Waves] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int waves
-- @param #float amplitude
-- @param #bool horizontal
-- @param #bool vertical
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get the amplitude of the effect.<br>
-- return Return the amplitude of the effect.
-- @function [parent=#Waves] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Get the amplitude rate of the effect.<br>
-- return Return the amplitude rate of the effect.
-- @function [parent=#Waves] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Set the amplitude to the effect.<br>
-- param amplitude The value of amplitude will be set.
-- @function [parent=#Waves] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return Waves#Waves self (return value: cc.Waves)
        
--------------------------------
-- brief Create the action with amplitude, horizontal sin, vertical sin, grid size, waves count and duration.<br>
-- param duration Specify the duration of the Waves action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param waves Specify the waves count of the Waves action.<br>
-- param amplitude Specify the amplitude of the Waves action.<br>
-- param horizontal Specify whether waves on horizontal.<br>
-- param vertical Specify whether waves on vertical.<br>
-- return If the creation success, return a pointer of Waves action; otherwise, return nil.
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
-- 
-- @function [parent=#Waves] update 
-- @param self
-- @param #float time
-- @return Waves#Waves self (return value: cc.Waves)
        
--------------------------------
-- 
-- @function [parent=#Waves] Waves 
-- @param self
-- @return Waves#Waves self (return value: cc.Waves)
        
return nil
