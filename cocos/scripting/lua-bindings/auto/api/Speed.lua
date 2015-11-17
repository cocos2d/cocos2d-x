
--------------------------------
-- @module Speed
-- @extend Action
-- @parent_module cc

--------------------------------
--  Replace the interior action.<br>
-- param action The new action, it will replace the running action.
-- @function [parent=#Speed] setInnerAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return Speed#Speed self (return value: cc.Speed)
        
--------------------------------
--  Return the speed.<br>
-- return The action speed.
-- @function [parent=#Speed] getSpeed 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Alter the speed of the inner function in runtime. <br>
-- param speed Alter the speed of the inner function in runtime.
-- @function [parent=#Speed] setSpeed 
-- @param self
-- @param #float speed
-- @return Speed#Speed self (return value: cc.Speed)
        
--------------------------------
--  Initializes the action. 
-- @function [parent=#Speed] initWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float speed
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Return the interior action.<br>
-- return The interior action.
-- @function [parent=#Speed] getInnerAction 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
--  Create the action and set the speed.<br>
-- param action An action.<br>
-- param speed The action speed.
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
-- @return Speed#Speed self (return value: cc.Speed)
        
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
-- @return Speed#Speed self (return value: cc.Speed)
        
--------------------------------
-- param dt in seconds.
-- @function [parent=#Speed] step 
-- @param self
-- @param #float dt
-- @return Speed#Speed self (return value: cc.Speed)
        
--------------------------------
--  Return true if the action has finished.<br>
-- return Is true if the action has finished.
-- @function [parent=#Speed] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Speed] Speed 
-- @param self
-- @return Speed#Speed self (return value: cc.Speed)
        
return nil
