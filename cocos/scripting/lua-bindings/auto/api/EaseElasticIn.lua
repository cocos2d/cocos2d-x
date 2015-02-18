
--------------------------------
-- @module EaseElasticIn
-- @extend EaseElastic
-- @parent_module cc

--------------------------------
-- @overload self, cc.ActionInterval         
-- @overload self, cc.ActionInterval, float         
-- @function [parent=#EaseElasticIn] create
-- @param self
-- @param #cc.ActionInterval action
-- @param #float period
-- @return EaseElasticIn#EaseElasticIn ret (return value: cc.EaseElasticIn)

--------------------------------
-- 
-- @function [parent=#EaseElasticIn] clone 
-- @param self
-- @return EaseElasticIn#EaseElasticIn ret (return value: cc.EaseElasticIn)
        
--------------------------------
-- param time in seconds
-- @function [parent=#EaseElasticIn] update 
-- @param self
-- @param #float time
-- @return EaseElasticIn#EaseElasticIn self (return value: cc.EaseElasticIn)
        
--------------------------------
-- 
-- @function [parent=#EaseElasticIn] reverse 
-- @param self
-- @return EaseElastic#EaseElastic ret (return value: cc.EaseElastic)
        
return nil
