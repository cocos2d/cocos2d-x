
--------------------------------
-- @module ShuffleTiles
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ShuffleTiles] getDelta 
-- @param self
-- @param #size_table pos
-- @return size_table#size_table ret (return value: size_table)
        
--------------------------------
--  creates the action with a random seed, the grid size and the duration 
-- @function [parent=#ShuffleTiles] create 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @param #unsigned int seed
-- @return ShuffleTiles#ShuffleTiles ret (return value: cc.ShuffleTiles)
        
--------------------------------
-- 
-- @function [parent=#ShuffleTiles] startWithTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- 
-- @function [parent=#ShuffleTiles] clone 
-- @param self
-- @return ShuffleTiles#ShuffleTiles ret (return value: cc.ShuffleTiles)
        
--------------------------------
-- 
-- @function [parent=#ShuffleTiles] update 
-- @param self
-- @param #float time
        
return nil
