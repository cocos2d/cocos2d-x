
--------------------------------
-- @module Waves3D
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- brief Set the ampliture rate of the effect.<br>
-- param amplitudeRate The value of amplitude rate will be set.
-- @function [parent=#Waves3D] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
--------------------------------
-- brief Initializes an action with duration, grid size, waves and amplitude.<br>
-- param duration Specify the duration of the Waves3D action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param waves Specify the waves count of the Waves3D action.<br>
-- param amplitude Specify the amplitude of the Waves3D action.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#Waves3D] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int waves
-- @param #float amplitude
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get the amplitude of the effect.<br>
-- return Return the amplitude of the effect.
-- @function [parent=#Waves3D] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Get the amplitude rate of the effect.<br>
-- return Return the amplitude rate of the effect.
-- @function [parent=#Waves3D] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Set the amplitude to the effect.<br>
-- param amplitude The value of amplitude will be set.
-- @function [parent=#Waves3D] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
--------------------------------
-- brief Create an action with duration, grid size, waves and amplitude.<br>
-- param duration Specify the duration of the Waves3D action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param waves Specify the waves count of the Waves3D action.<br>
-- param amplitude Specify the amplitude of the Waves3D action.<br>
-- return If the creation sucess, return a pointer of Waves3D action; otherwise, return nil.
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
-- 
-- @function [parent=#Waves3D] update 
-- @param self
-- @param #float time
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
--------------------------------
-- 
-- @function [parent=#Waves3D] Waves3D 
-- @param self
-- @return Waves3D#Waves3D self (return value: cc.Waves3D)
        
return nil
