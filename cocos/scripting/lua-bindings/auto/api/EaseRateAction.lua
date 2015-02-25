
--------------------------------
-- @module EaseRateAction
-- @extend ActionEase
-- @parent_module cc

--------------------------------
--  set rate value for the actions 
-- @function [parent=#EaseRateAction] setRate 
-- @param self
-- @param #float rate
-- @return EaseRateAction#EaseRateAction self (return value: cc.EaseRateAction)
        
--------------------------------
--  Initializes the action with the inner action and the rate parameter 
-- @function [parent=#EaseRateAction] initWithAction 
-- @param self
-- @param #cc.ActionInterval pAction
-- @param #float fRate
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  get rate value for the actions 
-- @function [parent=#EaseRateAction] getRate 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#EaseRateAction] clone 
-- @param self
-- @return EaseRateAction#EaseRateAction ret (return value: cc.EaseRateAction)
        
--------------------------------
-- 
-- @function [parent=#EaseRateAction] reverse 
-- @param self
-- @return EaseRateAction#EaseRateAction ret (return value: cc.EaseRateAction)
        
return nil
