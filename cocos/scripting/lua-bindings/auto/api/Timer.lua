
--------------------------------
-- @module Timer
-- @extend Ref
-- @parent_module cc

--------------------------------
--  get interval in seconds 
-- @function [parent=#Timer] getInterval 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#Timer] setupTimerWithInterval 
-- @param self
-- @param #float seconds
-- @param #unsigned int repeat
-- @param #float delay
-- @return Timer#Timer self (return value: cc.Timer)
        
--------------------------------
--  set interval in seconds 
-- @function [parent=#Timer] setInterval 
-- @param self
-- @param #float interval
-- @return Timer#Timer self (return value: cc.Timer)
        
--------------------------------
--  triggers the timer 
-- @function [parent=#Timer] update 
-- @param self
-- @param #float dt
-- @return Timer#Timer self (return value: cc.Timer)
        
--------------------------------
-- 
-- @function [parent=#Timer] trigger 
-- @param self
-- @param #float dt
-- @return Timer#Timer self (return value: cc.Timer)
        
--------------------------------
-- 
-- @function [parent=#Timer] cancel 
-- @param self
-- @return Timer#Timer self (return value: cc.Timer)
        
return nil
