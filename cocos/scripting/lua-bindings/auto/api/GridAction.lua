
--------------------------------
-- @module GridAction
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  returns the grid 
-- @function [parent=#GridAction] getGrid 
-- @param self
-- @return GridBase#GridBase ret (return value: cc.GridBase)
        
--------------------------------
-- initializes the action with size and duration<br>
-- param duration in seconds
-- @function [parent=#GridAction] initWithDuration 
-- @param self
-- @param #float duration
-- @param #size_table gridSize
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#GridAction] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return GridAction#GridAction self (return value: cc.GridAction)
        
--------------------------------
-- 
-- @function [parent=#GridAction] clone 
-- @param self
-- @return GridAction#GridAction ret (return value: cc.GridAction)
        
--------------------------------
-- 
-- @function [parent=#GridAction] reverse 
-- @param self
-- @return GridAction#GridAction ret (return value: cc.GridAction)
        
return nil
