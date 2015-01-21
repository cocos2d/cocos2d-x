
--------------------------------
-- @module ProgressFromTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- Creates and initializes the action with a duration, a "from" percentage and a "to" percentage <br>
-- param duration in seconds
-- @function [parent=#ProgressFromTo] create 
-- @param self
-- @param #float duration
-- @param #float fromPercentage
-- @param #float toPercentage
-- @return ProgressFromTo#ProgressFromTo ret (return value: cc.ProgressFromTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressFromTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ProgressFromTo#ProgressFromTo self (return value: cc.ProgressFromTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressFromTo] clone 
-- @param self
-- @return ProgressFromTo#ProgressFromTo ret (return value: cc.ProgressFromTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressFromTo] reverse 
-- @param self
-- @return ProgressFromTo#ProgressFromTo ret (return value: cc.ProgressFromTo)
        
--------------------------------
-- param time in seconds
-- @function [parent=#ProgressFromTo] update 
-- @param self
-- @param #float time
-- @return ProgressFromTo#ProgressFromTo self (return value: cc.ProgressFromTo)
        
return nil
