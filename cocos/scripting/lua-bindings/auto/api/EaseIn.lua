
--------------------------------
-- @module EaseIn
-- @extend EaseRateAction
-- @parent_module cc

--------------------------------
-- brief Create the action with the inner action and the rate parameter.<br>
-- param action The pointer of the inner action.<br>
-- param rate The value of the rate parameter.<br>
-- return A pointer of EaseIn action. If creation failed, return nil.
-- @function [parent=#EaseIn] create 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float rate
-- @return EaseIn#EaseIn ret (return value: cc.EaseIn)
        
--------------------------------
-- 
-- @function [parent=#EaseIn] clone 
-- @param self
-- @return EaseIn#EaseIn ret (return value: cc.EaseIn)
        
--------------------------------
-- 
-- @function [parent=#EaseIn] update 
-- @param self
-- @param #float time
-- @return EaseIn#EaseIn self (return value: cc.EaseIn)
        
--------------------------------
-- 
-- @function [parent=#EaseIn] reverse 
-- @param self
-- @return EaseIn#EaseIn ret (return value: cc.EaseIn)
        
--------------------------------
-- 
-- @function [parent=#EaseIn] EaseIn 
-- @param self
-- @return EaseIn#EaseIn self (return value: cc.EaseIn)
        
return nil
