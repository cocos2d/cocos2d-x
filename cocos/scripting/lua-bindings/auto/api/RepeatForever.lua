
--------------------------------
-- @module RepeatForever
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  Sets the inner action.<br>
-- param action The inner action.
-- @function [parent=#RepeatForever] setInnerAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return RepeatForever#RepeatForever self (return value: cc.RepeatForever)
        
--------------------------------
--  initializes the action 
-- @function [parent=#RepeatForever] initWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the inner action.<br>
-- return The inner action.
-- @function [parent=#RepeatForever] getInnerAction 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
--  Creates the action.<br>
-- param action The action need to repeat forever.<br>
-- return An autoreleased RepeatForever object.
-- @function [parent=#RepeatForever] create 
-- @param self
-- @param #cc.ActionInterval action
-- @return RepeatForever#RepeatForever ret (return value: cc.RepeatForever)
        
--------------------------------
-- 
-- @function [parent=#RepeatForever] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return RepeatForever#RepeatForever self (return value: cc.RepeatForever)
        
--------------------------------
-- 
-- @function [parent=#RepeatForever] clone 
-- @param self
-- @return RepeatForever#RepeatForever ret (return value: cc.RepeatForever)
        
--------------------------------
-- 
-- @function [parent=#RepeatForever] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#RepeatForever] reverse 
-- @param self
-- @return RepeatForever#RepeatForever ret (return value: cc.RepeatForever)
        
--------------------------------
-- param dt In seconds.
-- @function [parent=#RepeatForever] step 
-- @param self
-- @param #float dt
-- @return RepeatForever#RepeatForever self (return value: cc.RepeatForever)
        
--------------------------------
-- 
-- @function [parent=#RepeatForever] RepeatForever 
-- @param self
-- @return RepeatForever#RepeatForever self (return value: cc.RepeatForever)
        
return nil
