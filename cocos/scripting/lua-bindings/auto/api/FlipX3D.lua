
--------------------------------
-- @module FlipX3D
-- @extend Grid3DAction
-- @parent_module cc

--------------------------------
-- brief Initializes an action with duration and grid size.<br>
-- param gridSize Specify the grid size of the FlipX3D action.<br>
-- param duration Specify the duration of the FlipX3D action. It's a value in seconds.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#FlipX3D] initWithSize 
-- @param self
-- @param #size_table gridSize
-- @param #float duration
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Initializes an action with duration.<br>
-- param duration Specify the duration of the FlipX3D action. It's a value in seconds.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#FlipX3D] initWithDuration 
-- @param self
-- @param #float duration
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create the action with duration.<br>
-- param duration Specify the duration of the FilpX3D action. It's a value in seconds.<br>
-- return If the creation sucess, return a pointer of FilpX3D action; otherwise, return nil.
-- @function [parent=#FlipX3D] create 
-- @param self
-- @param #float duration
-- @return FlipX3D#FlipX3D ret (return value: cc.FlipX3D)
        
--------------------------------
-- 
-- @function [parent=#FlipX3D] clone 
-- @param self
-- @return FlipX3D#FlipX3D ret (return value: cc.FlipX3D)
        
--------------------------------
-- 
-- @function [parent=#FlipX3D] update 
-- @param self
-- @param #float time
-- @return FlipX3D#FlipX3D self (return value: cc.FlipX3D)
        
--------------------------------
-- 
-- @function [parent=#FlipX3D] FlipX3D 
-- @param self
-- @return FlipX3D#FlipX3D self (return value: cc.FlipX3D)
        
return nil
