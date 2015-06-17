
--------------------------------
-- @module WavesTiles3D
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- brief Set the ampliture rate of the effect.<br>
-- param amplitudeRate The value of amplitude rate will be set.
-- @function [parent=#WavesTiles3D] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return WavesTiles3D#WavesTiles3D self (return value: cc.WavesTiles3D)
        
--------------------------------
-- brief Initializes an action with duration, grid size, waves count and amplitude.<br>
-- param duration Specify the duration of the WavesTiles3D action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param waves Specify the waves count of the WavesTiles3D action.<br>
-- param amplitude Specify the amplitude of the WavesTiles3D action.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#WavesTiles3D] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int waves
-- @param #float amplitude
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get the amplitude of the effect.<br>
-- return Return the amplitude of the effect.
-- @function [parent=#WavesTiles3D] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Get the amplitude rate of the effect.<br>
-- return Return the amplitude rate of the effect.
-- @function [parent=#WavesTiles3D] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- brief Set the amplitude to the effect.<br>
-- param amplitude The value of amplitude will be set.
-- @function [parent=#WavesTiles3D] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return WavesTiles3D#WavesTiles3D self (return value: cc.WavesTiles3D)
        
--------------------------------
-- brief Create the action with a number of waves, the waves amplitude, the grid size and the duration.<br>
-- param duration Specify the duration of the WavesTiles3D action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param waves Specify the waves count of the WavesTiles3D action.<br>
-- param amplitude Specify the amplitude of the WavesTiles3D action.<br>
-- return If the creation success, return a pointer of WavesTiles3D action; otherwise, return nil.
-- @function [parent=#WavesTiles3D] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int waves
-- @param #float amplitude
-- @return WavesTiles3D#WavesTiles3D ret (return value: cc.WavesTiles3D)
        
--------------------------------
-- 
-- @function [parent=#WavesTiles3D] clone 
-- @param self
-- @return WavesTiles3D#WavesTiles3D ret (return value: cc.WavesTiles3D)
        
--------------------------------
-- 
-- @function [parent=#WavesTiles3D] update 
-- @param self
-- @param #float time
-- @return WavesTiles3D#WavesTiles3D self (return value: cc.WavesTiles3D)
        
--------------------------------
-- 
-- @function [parent=#WavesTiles3D] WavesTiles3D 
-- @param self
-- @return WavesTiles3D#WavesTiles3D self (return value: cc.WavesTiles3D)
        
return nil
