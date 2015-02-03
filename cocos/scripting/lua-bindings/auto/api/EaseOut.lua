
--------------------------------
-- @module EaseOut
-- @extend EaseRateAction
-- @parent_module cc

--------------------------------
--  Creates the action with the inner action and the rate parameter 
-- @function [parent=#EaseOut] create 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float rate
-- @return EaseOut#EaseOut ret (return value: cc.EaseOut)
        
--------------------------------
-- 
-- @function [parent=#EaseOut] clone 
-- @param self
-- @return EaseOut#EaseOut ret (return value: cc.EaseOut)
        
--------------------------------
-- param time in seconds
-- @function [parent=#EaseOut] update 
-- @param self
-- @param #float time
-- @return EaseOut#EaseOut self (return value: cc.EaseOut)
        
--------------------------------
-- 
-- @function [parent=#EaseOut] reverse 
-- @param self
-- @return EaseOut#EaseOut ret (return value: cc.EaseOut)
        
return nil
