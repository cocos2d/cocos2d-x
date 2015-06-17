
--------------------------------
-- @module EaseElastic
-- @extend ActionEase
-- @parent_module cc

--------------------------------
-- brief Set period of the wave in radians.<br>
-- param fPeriod The value will be set.
-- @function [parent=#EaseElastic] setPeriod 
-- @param self
-- @param #float fPeriod
-- @return EaseElastic#EaseElastic self (return value: cc.EaseElastic)
        
--------------------------------
-- brief Initializes the action with the inner action and the period in radians.<br>
-- param action The pointer of the inner action.<br>
-- param period Period of the wave in radians. Default is 0.3.<br>
-- return Return true when the initialization success, otherwise return false.
-- @function [parent=#EaseElastic] initWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @param #float period
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Get period of the wave in radians. Default value is 0.3.<br>
-- return Return the period of the wave in radians.
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
