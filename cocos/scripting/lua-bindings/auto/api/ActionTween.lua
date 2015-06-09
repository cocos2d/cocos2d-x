
--------------------------------
-- @module ActionTween
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- brief Initializes the action with the property name (key), and the from and to parameters.<br>
-- param duration The duration of the ActionTween. It's a value in seconds.<br>
-- param key The key of property which should be updated.<br>
-- param from The value of the specified property when the action begin.<br>
-- param to The value of the specified property when the action end.<br>
-- return If the initialization success, return true; otherwise, return false.
-- @function [parent=#ActionTween] initWithDuration 
-- @param self
-- @param #float duration
-- @param #string key
-- @param #float from
-- @param #float to
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create and initializes the action with the property name (key), and the from and to parameters.<br>
-- param duration The duration of the ActionTween. It's a value in seconds.<br>
-- param key The key of property which should be updated.<br>
-- param from The value of the specified property when the action begin.<br>
-- param to The value of the specified property when the action end.<br>
-- return If the creation success, return a pointer of ActionTween; otherwise, return nil.
-- @function [parent=#ActionTween] create 
-- @param self
-- @param #float duration
-- @param #string key
-- @param #float from
-- @param #float to
-- @return ActionTween#ActionTween ret (return value: cc.ActionTween)
        
--------------------------------
-- 
-- @function [parent=#ActionTween] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionTween#ActionTween self (return value: cc.ActionTween)
        
--------------------------------
-- 
-- @function [parent=#ActionTween] clone 
-- @param self
-- @return ActionTween#ActionTween ret (return value: cc.ActionTween)
        
--------------------------------
-- 
-- @function [parent=#ActionTween] update 
-- @param self
-- @param #float dt
-- @return ActionTween#ActionTween self (return value: cc.ActionTween)
        
--------------------------------
-- 
-- @function [parent=#ActionTween] reverse 
-- @param self
-- @return ActionTween#ActionTween ret (return value: cc.ActionTween)
        
return nil
