
--------------------------------
-- @module Spawn
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  initializes the Spawn action with the 2 actions to spawn 
-- @function [parent=#Spawn] initWithTwoActions 
-- @param self
-- @param #cc.FiniteTimeAction action1
-- @param #cc.FiniteTimeAction action2
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Spawn] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Spawn#Spawn self (return value: cc.Spawn)
        
--------------------------------
-- 
-- @function [parent=#Spawn] clone 
-- @param self
-- @return Spawn#Spawn ret (return value: cc.Spawn)
        
--------------------------------
-- 
-- @function [parent=#Spawn] stop 
-- @param self
-- @return Spawn#Spawn self (return value: cc.Spawn)
        
--------------------------------
-- 
-- @function [parent=#Spawn] reverse 
-- @param self
-- @return Spawn#Spawn ret (return value: cc.Spawn)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#Spawn] update 
-- @param self
-- @param #float time
-- @return Spawn#Spawn self (return value: cc.Spawn)
        
--------------------------------
-- 
-- @function [parent=#Spawn] Spawn 
-- @param self
-- @return Spawn#Spawn self (return value: cc.Spawn)
        
return nil
