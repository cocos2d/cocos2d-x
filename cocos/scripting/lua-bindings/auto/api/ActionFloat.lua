
--------------------------------
-- @module ActionFloat
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ActionFloat] initWithDuration 
-- @param self
-- @param #float duration
-- @param #float from
-- @param #float to
-- @param #function callback
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates FloatAction with specified duration, from value, to value and callback to report back<br>
-- results<br>
-- param duration of the action<br>
-- param from value to start from<br>
-- param to value to be at the end of the action<br>
-- param callback to report back result<br>
-- return An autoreleased ActionFloat object
-- @function [parent=#ActionFloat] create 
-- @param self
-- @param #float duration
-- @param #float from
-- @param #float to
-- @param #function callback
-- @return ActionFloat#ActionFloat ret (return value: cc.ActionFloat)
        
--------------------------------
-- Overridden ActionInterval methods
-- @function [parent=#ActionFloat] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionFloat#ActionFloat self (return value: cc.ActionFloat)
        
--------------------------------
-- 
-- @function [parent=#ActionFloat] clone 
-- @param self
-- @return ActionFloat#ActionFloat ret (return value: cc.ActionFloat)
        
--------------------------------
-- 
-- @function [parent=#ActionFloat] update 
-- @param self
-- @param #float delta
-- @return ActionFloat#ActionFloat self (return value: cc.ActionFloat)
        
--------------------------------
-- 
-- @function [parent=#ActionFloat] reverse 
-- @param self
-- @return ActionFloat#ActionFloat ret (return value: cc.ActionFloat)
        
--------------------------------
-- 
-- @function [parent=#ActionFloat] ActionFloat 
-- @param self
-- @return ActionFloat#ActionFloat self (return value: cc.ActionFloat)
        
return nil
