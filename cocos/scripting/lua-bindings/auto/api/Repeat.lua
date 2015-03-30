
--------------------------------
-- @module Repeat
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  Sets the inner action.<br>
-- param action The inner action.
-- @function [parent=#Repeat] setInnerAction 
-- @param self
-- @param #cc.FiniteTimeAction action
-- @return Repeat#Repeat self (return value: cc.Repeat)
        
--------------------------------
--  Gets the inner action.<br>
-- return The inner action.
-- @function [parent=#Repeat] getInnerAction 
-- @param self
-- @return FiniteTimeAction#FiniteTimeAction ret (return value: cc.FiniteTimeAction)
        
--------------------------------
--  Creates a Repeat action. Times is an unsigned integer between 1 and pow(2,30).<br>
-- param action The action needs to repeat.<br>
-- param times The repeat times.<br>
-- return An autoreleased Repeat object.
-- @function [parent=#Repeat] create 
-- @param self
-- @param #cc.FiniteTimeAction action
-- @param #unsigned int times
-- @return Repeat#Repeat ret (return value: cc.Repeat)
        
--------------------------------
-- 
-- @function [parent=#Repeat] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Repeat#Repeat self (return value: cc.Repeat)
        
--------------------------------
-- 
-- @function [parent=#Repeat] reverse 
-- @param self
-- @return Repeat#Repeat ret (return value: cc.Repeat)
        
--------------------------------
-- 
-- @function [parent=#Repeat] clone 
-- @param self
-- @return Repeat#Repeat ret (return value: cc.Repeat)
        
--------------------------------
-- 
-- @function [parent=#Repeat] stop 
-- @param self
-- @return Repeat#Repeat self (return value: cc.Repeat)
        
--------------------------------
-- param dt In seconds.
-- @function [parent=#Repeat] update 
-- @param self
-- @param #float dt
-- @return Repeat#Repeat self (return value: cc.Repeat)
        
--------------------------------
-- 
-- @function [parent=#Repeat] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
