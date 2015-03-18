
--------------------------------
-- @module ShatteredTiles3D
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- brief Create the action with a range, whether of not to shatter Z vertices, grid size and duration.<br>
-- param duration Specify the duration of the ShatteredTiles3D action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param range Specify the range of the shatter effect.<br>
-- param shatterZ Specify whether shatter on the z axis.<br>
-- return If the creation success, return a pointer of ShatteredTiles3D action; otherwise, return nil.
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
-- 
-- @function [parent=#ShatteredTiles3D] update 
-- @param self
-- @param #float time
-- @return ShatteredTiles3D#ShatteredTiles3D self (return value: cc.ShatteredTiles3D)
        
return nil
