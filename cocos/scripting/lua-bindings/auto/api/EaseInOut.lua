
--------------------------------
-- @module EaseInOut
-- @extend EaseRateAction
-- @parent_module cc

--------------------------------
-- brief Create the action with the inner action and the rate parameter.<br>
-- param action The pointer of the inner action.<br>
-- param rate The value of the rate parameter.<br>
-- return A pointer of EaseInOut action. If creation failed, return nil.
-- @function [parent=#EaseInOut] create 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float rate
-- @return EaseInOut#EaseInOut ret (return value: cc.EaseInOut)
        
--------------------------------
-- 
-- @function [parent=#EaseInOut] clone 
-- @param self
-- @return EaseInOut#EaseInOut ret (return value: cc.EaseInOut)
        
--------------------------------
-- 
-- @function [parent=#EaseInOut] update 
-- @param self
-- @param #float time
-- @return EaseInOut#EaseInOut self (return value: cc.EaseInOut)
        
--------------------------------
-- 
-- @function [parent=#EaseInOut] reverse 
-- @param self
-- @return EaseInOut#EaseInOut ret (return value: cc.EaseInOut)
        
return nil
