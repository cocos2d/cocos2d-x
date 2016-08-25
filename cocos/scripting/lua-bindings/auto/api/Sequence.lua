
--------------------------------
-- @module Sequence
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Sequence] init 
-- @param self
-- @param #array_table arrayOfActions
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  initializes the action 
-- @function [parent=#Sequence] initWithTwoActions 
-- @param self
-- @param #cc.FiniteTimeAction pActionOne
-- @param #cc.FiniteTimeAction pActionTwo
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Sequence] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Sequence#Sequence self (return value: cc.Sequence)
        
--------------------------------
-- 
-- @function [parent=#Sequence] clone 
-- @param self
-- @return Sequence#Sequence ret (return value: cc.Sequence)
        
--------------------------------
-- 
-- @function [parent=#Sequence] stop 
-- @param self
-- @return Sequence#Sequence self (return value: cc.Sequence)
        
--------------------------------
-- 
-- @function [parent=#Sequence] reverse 
-- @param self
-- @return Sequence#Sequence ret (return value: cc.Sequence)
        
--------------------------------
-- param t In seconds.
-- @function [parent=#Sequence] update 
-- @param self
-- @param #float t
-- @return Sequence#Sequence self (return value: cc.Sequence)
        
--------------------------------
-- 
-- @function [parent=#Sequence] Sequence 
-- @param self
-- @return Sequence#Sequence self (return value: cc.Sequence)
        
return nil
