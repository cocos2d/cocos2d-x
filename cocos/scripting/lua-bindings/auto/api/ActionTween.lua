
--------------------------------
-- @module ActionTween
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- creates an initializes the action with the property name (key), and the from and to parameters. <br>
-- param duration in seconds
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
-- param dt in seconds
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
