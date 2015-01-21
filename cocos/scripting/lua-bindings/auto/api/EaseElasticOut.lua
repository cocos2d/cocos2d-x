
--------------------------------
-- @module EaseElasticOut
-- @extend EaseElastic
-- @parent_module cc

--------------------------------
-- @overload self, cc.ActionInterval         
-- @overload self, cc.ActionInterval, float         
-- @function [parent=#EaseElasticOut] create
-- @param self
-- @param #cc.ActionInterval action
-- @param #float period
-- @return EaseElasticOut#EaseElasticOut ret (return value: cc.EaseElasticOut)

--------------------------------
-- 
-- @function [parent=#EaseElasticOut] clone 
-- @param self
-- @return EaseElasticOut#EaseElasticOut ret (return value: cc.EaseElasticOut)
        
--------------------------------
-- param time in seconds
-- @function [parent=#EaseElasticOut] update 
-- @param self
-- @param #float time
-- @return EaseElasticOut#EaseElasticOut self (return value: cc.EaseElasticOut)
        
--------------------------------
-- 
-- @function [parent=#EaseElasticOut] reverse 
-- @param self
-- @return EaseElastic#EaseElastic ret (return value: cc.EaseElastic)
        
return nil
