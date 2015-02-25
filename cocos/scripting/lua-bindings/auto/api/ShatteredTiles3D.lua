
--------------------------------
-- @module ShatteredTiles3D
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- initializes the action with a range, whether or not to shatter Z vertices, a grid size and duration 
-- @function [parent=#ShatteredTiles3D] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #int range
-- @param #bool shatterZ
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- creates the action with a range, whether of not to shatter Z vertices, a grid size and duration <br>
-- param duration in seconds
-- @function [parent=#ShatteredTiles3D] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #int range
-- @param #bool shatterZ
-- @return ShatteredTiles3D#ShatteredTiles3D ret (return value: cc.ShatteredTiles3D)
        
--------------------------------
-- 
-- @function [parent=#ShatteredTiles3D] clone 
-- @param self
-- @return ShatteredTiles3D#ShatteredTiles3D ret (return value: cc.ShatteredTiles3D)
        
--------------------------------
-- param time in seconds
-- @function [parent=#ShatteredTiles3D] update 
-- @param self
-- @param #float time
-- @return ShatteredTiles3D#ShatteredTiles3D self (return value: cc.ShatteredTiles3D)
        
--------------------------------
-- 
-- @function [parent=#ShatteredTiles3D] ShatteredTiles3D 
-- @param self
-- @return ShatteredTiles3D#ShatteredTiles3D self (return value: cc.ShatteredTiles3D)
        
return nil
