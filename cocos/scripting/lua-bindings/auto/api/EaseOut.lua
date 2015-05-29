
--------------------------------
-- @module EaseOut
-- @extend EaseRateAction
-- @parent_module cc

--------------------------------
-- brief Create the action with the inner action and the rate parameter.<br>
-- param action The pointer of the inner action.<br>
-- param rate The value of the rate parameter.<br>
-- return A pointer of EaseOut action. If creation failed, return nil.
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
-- 
-- @function [parent=#EaseOut] update 
-- @param self
-- @param #float time
-- @return EaseOut#EaseOut self (return value: cc.EaseOut)
        
--------------------------------
-- 
-- @function [parent=#EaseOut] reverse 
-- @param self
-- @return EaseOut#EaseOut ret (return value: cc.EaseOut)
        
--------------------------------
-- 
-- @function [parent=#EaseOut] EaseOut 
-- @param self
-- @return EaseOut#EaseOut self (return value: cc.EaseOut)
        
return nil
