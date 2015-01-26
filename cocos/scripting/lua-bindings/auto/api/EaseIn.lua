
--------------------------------
-- @module EaseIn
-- @extend EaseRateAction
-- @parent_module cc

--------------------------------
--  Creates the action with the inner action and the rate parameter 
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
-- param time in seconds
-- @function [parent=#EaseIn] update 
-- @param self
-- @param #float time
-- @return EaseIn#EaseIn self (return value: cc.EaseIn)
        
--------------------------------
-- 
-- @function [parent=#EaseIn] reverse 
-- @param self
-- @return EaseIn#EaseIn ret (return value: cc.EaseIn)
        
return nil
