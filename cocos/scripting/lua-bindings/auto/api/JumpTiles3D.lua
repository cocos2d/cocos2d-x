
--------------------------------
-- @module JumpTiles3D
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
--  amplitude rate 
-- @function [parent=#JumpTiles3D] getAmplitudeRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#JumpTiles3D] setAmplitude 
-- @param self
-- @param #float amplitude
-- @return JumpTiles3D#JumpTiles3D self (return value: cc.JumpTiles3D)
        
--------------------------------
-- 
-- @function [parent=#JumpTiles3D] setAmplitudeRate 
-- @param self
-- @param #float amplitudeRate
-- @return JumpTiles3D#JumpTiles3D self (return value: cc.JumpTiles3D)
        
--------------------------------
--  amplitude of the sin
-- @function [parent=#JumpTiles3D] getAmplitude 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- creates the action with the number of jumps, the sin amplitude, the grid size and the duration <br>
-- param duration in seconds
-- @function [parent=#JumpTiles3D] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int numberOfJumps
-- @param #float amplitude
-- @return JumpTiles3D#JumpTiles3D ret (return value: cc.JumpTiles3D)
        
--------------------------------
-- 
-- @function [parent=#JumpTiles3D] clone 
-- @param self
-- @return JumpTiles3D#JumpTiles3D ret (return value: cc.JumpTiles3D)
        
--------------------------------
-- param time in seconds
-- @function [parent=#JumpTiles3D] update 
-- @param self
-- @param #float time
-- @return JumpTiles3D#JumpTiles3D self (return value: cc.JumpTiles3D)
        
return nil
