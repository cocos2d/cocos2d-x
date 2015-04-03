
--------------------------------
-- @module RotateTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- @overload self, float, float         
-- @overload self, float, float, float         
-- @overload self, float, vec3_table         
-- @function [parent=#RotateTo] create
-- @param self
-- @param #float duration
-- @param #float dstAngleX
-- @param #float dstAngleY
-- @return RotateTo#RotateTo ret (return value: cc.RotateTo)

--------------------------------
-- 
-- @function [parent=#RotateTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return RotateTo#RotateTo self (return value: cc.RotateTo)
        
--------------------------------
-- 
-- @function [parent=#RotateTo] clone 
-- @param self
-- @return RotateTo#RotateTo ret (return value: cc.RotateTo)
        
--------------------------------
-- 
-- @function [parent=#RotateTo] reverse 
-- @param self
-- @return RotateTo#RotateTo ret (return value: cc.RotateTo)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#RotateTo] update 
-- @param self
-- @param #float time
-- @return RotateTo#RotateTo self (return value: cc.RotateTo)
        
return nil
