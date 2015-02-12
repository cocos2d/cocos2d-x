
--------------------------------
-- @module EaseElastic
-- @extend ActionEase
-- @parent_module cc

--------------------------------
--  set period of the wave in radians. 
-- @function [parent=#EaseElastic] setPeriod 
-- @param self
-- @param #float fPeriod
-- @return EaseElastic#EaseElastic self (return value: cc.EaseElastic)
        
--------------------------------
--  Initializes the action with the inner action and the period in radians (default is 0.3) 
-- @function [parent=#EaseElastic] initWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float period
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  get period of the wave in radians. default is 0.3 
-- @function [parent=#EaseElastic] getPeriod 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#EaseElastic] clone 
-- @param self
-- @return EaseElastic#EaseElastic ret (return value: cc.EaseElastic)
        
--------------------------------
-- 
-- @function [parent=#EaseElastic] reverse 
-- @param self
-- @return EaseElastic#EaseElastic ret (return value: cc.EaseElastic)
        
return nil
