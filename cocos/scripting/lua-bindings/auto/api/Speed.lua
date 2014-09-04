
--------------------------------
-- @module Speed
-- @extend Action
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Speed] setInnerAction 
-- @param self
-- @param #cc.ActionInterval action
        
--------------------------------
--  alter the speed of the inner function in runtime 
-- @function [parent=#Speed] setSpeed 
-- @param self
-- @param #float speed
        
--------------------------------
-- 
-- @function [parent=#Speed] getInnerAction 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#Speed] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  create the action 
-- @function [parent=#Speed] create 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float speed
-- @return Speed#Speed ret (return value: cc.Speed)
        
--------------------------------
-- 
-- @function [parent=#Speed] startWithTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- 
-- @function [parent=#Speed] reverse 
-- @param self
-- @return Speed#Speed ret (return value: cc.Speed)
        
--------------------------------
-- 
-- @function [parent=#Speed] clone 
-- @param self
-- @return Speed#Speed ret (return value: cc.Speed)
        
--------------------------------
-- 
-- @function [parent=#Speed] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Speed] step 
-- @param self
-- @param #float dt
        
--------------------------------
-- 
-- @function [parent=#Speed] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
