
--------------------------------
-- @module RotateBy
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- @overload self, float, float, float         
-- @overload self, float, float         
-- @overload self, float, vec3_table         
-- @function [parent=#RotateBy] create
-- @param self
-- @param #float duration
-- @param #float deltaAngleZ_X
-- @param #float deltaAngleZ_Y
-- @return RotateBy#RotateBy ret (return value: cc.RotateBy)

--------------------------------
-- 
-- @function [parent=#RotateBy] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return RotateBy#RotateBy self (return value: cc.RotateBy)
        
--------------------------------
-- 
-- @function [parent=#RotateBy] clone 
-- @param self
-- @return RotateBy#RotateBy ret (return value: cc.RotateBy)
        
--------------------------------
-- 
-- @function [parent=#RotateBy] reverse 
-- @param self
-- @return RotateBy#RotateBy ret (return value: cc.RotateBy)
        
--------------------------------
-- param time in seconds
-- @function [parent=#RotateBy] update 
-- @param self
-- @param #float time
-- @return RotateBy#RotateBy self (return value: cc.RotateBy)
        
return nil
