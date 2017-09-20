
--------------------------------
-- @module Timer
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#Timer] setupTimerWithInterval 
-- @param self
-- @param #float seconds
-- @param #unsigned int repeat
-- @param #float delay
-- @return Timer#Timer self (return value: cc.Timer)
        
--------------------------------
--  triggers the timer 
-- @function [parent=#Timer] update 
-- @param self
-- @param #float dt
-- @return Timer#Timer self (return value: cc.Timer)
        
--------------------------------
-- 
-- @function [parent=#Timer] isAborted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Timer] isExhausted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
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
        
--------------------------------
-- 
-- @function [parent=#Timer] setAborted 
-- @param self
-- @return Timer#Timer self (return value: cc.Timer)
        
return nil
