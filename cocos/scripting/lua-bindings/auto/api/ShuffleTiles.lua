
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
-- brief Create the action with grid size, random seed and duration.<br>
-- param duration Specify the duration of the ShuffleTiles action. It's a value in seconds.<br>
-- param gridSize Specify the size of the grid.<br>
-- param seed Specify the random seed.<br>
-- return If the creation success, return a pointer of ShuffleTiles action; otherwise, return nil.
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
-- @return ShuffleTiles#ShuffleTiles self (return value: cc.ShuffleTiles)
        
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
-- @return ShuffleTiles#ShuffleTiles self (return value: cc.ShuffleTiles)
        
return nil
