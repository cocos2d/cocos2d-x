
--------------------------------
-- @module WavesTiles3D
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
--  waves amplitude rate 
-- @function [parent=#WavesTiles3D] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#WavesTiles3D] setAmplitude 
-- @param self
-- @param #float amplitude
        
--------------------------------
-- 
-- @function [parent=#WavesTiles3D] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
        
--------------------------------
--  waves amplitude 
-- @function [parent=#WavesTiles3D] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  creates the action with a number of waves, the waves amplitude, the grid size and the duration 
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
        
return nil
