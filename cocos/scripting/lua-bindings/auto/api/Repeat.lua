
--------------------------------
-- @module Repeat
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Repeat] setInnerAction 
-- @param self
-- @param #cc.FiniteTimeAction action
-- @return Repeat#Repeat self (return value: cc.Repeat)
        
--------------------------------
-- 
-- @function [parent=#Repeat] getInnerAction 
-- @param self
-- @return FiniteTimeAction#FiniteTimeAction ret (return value: cc.FiniteTimeAction)
        
--------------------------------
--  creates a Repeat action. Times is an unsigned integer between 1 and pow(2,30) 
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
-- param dt in seconds
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
