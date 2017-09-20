
--------------------------------
-- @module ActionInstant
-- @extend FiniteTimeAction
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ActionInstant] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionInstant#ActionInstant self (return value: cc.ActionInstant)
        
--------------------------------
-- 
-- @function [parent=#ActionInstant] reverse 
-- @param self
-- @return ActionInstant#ActionInstant ret (return value: cc.ActionInstant)
        
--------------------------------
-- 
-- @function [parent=#ActionInstant] clone 
-- @param self
-- @return ActionInstant#ActionInstant ret (return value: cc.ActionInstant)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#ActionInstant] update 
-- @param self
-- @param #float time
-- @return ActionInstant#ActionInstant self (return value: cc.ActionInstant)
        
--------------------------------
-- param dt In seconds.
-- @function [parent=#ActionInstant] step 
-- @param self
-- @param #float dt
-- @return ActionInstant#ActionInstant self (return value: cc.ActionInstant)
        
--------------------------------
-- 
-- @function [parent=#ActionInstant] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
