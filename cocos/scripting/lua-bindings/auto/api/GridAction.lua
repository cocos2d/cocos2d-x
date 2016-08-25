
--------------------------------
-- @module GridAction
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- brief Get the pointer of GridBase.<br>
-- return The pointer of GridBase.
-- @function [parent=#GridAction] getGrid 
-- @param self
-- @return GridBase#GridBase ret (return value: cc.GridBase)
        
--------------------------------
-- brief Initializes the action with size and duration.<br>
-- param duration The duration of the GridAction. It's a value in seconds.<br>
-- param gridSize The size of the GridAction should be.<br>
-- return Return true when the initialization success, otherwise return false.
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
