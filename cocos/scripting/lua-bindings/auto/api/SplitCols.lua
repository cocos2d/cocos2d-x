
--------------------------------
-- @module SplitCols
-- @extend TiledGrid3DAction
-- @parent_module cc

--------------------------------
-- creates the action with the number of columns to split and the duration <br>
-- param duration in seconds
-- @function [parent=#SplitCols] create 
-- @param self
-- @param #float duration
-- @param #unsigned int cols
-- @return SplitCols#SplitCols ret (return value: cc.SplitCols)
        
--------------------------------
-- 
-- @function [parent=#SplitCols] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return SplitCols#SplitCols self (return value: cc.SplitCols)
        
--------------------------------
-- 
-- @function [parent=#SplitCols] clone 
-- @param self
-- @return SplitCols#SplitCols ret (return value: cc.SplitCols)
        
--------------------------------
-- param time in seconds
-- @function [parent=#SplitCols] update 
-- @param self
-- @param #float time
-- @return SplitCols#SplitCols self (return value: cc.SplitCols)
        
return nil
