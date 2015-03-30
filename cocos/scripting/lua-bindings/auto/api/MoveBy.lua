
--------------------------------
-- @module MoveBy
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- @overload self, float, vec3_table         
-- @overload self, float, vec2_table         
-- @function [parent=#MoveBy] create
-- @param self
-- @param #float duration
-- @param #vec2_table deltaPosition
-- @return MoveBy#MoveBy ret (return value: cc.MoveBy)

--------------------------------
-- 
-- @function [parent=#MoveBy] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return MoveBy#MoveBy self (return value: cc.MoveBy)
        
--------------------------------
-- 
-- @function [parent=#MoveBy] clone 
-- @param self
-- @return MoveBy#MoveBy ret (return value: cc.MoveBy)
        
--------------------------------
-- 
-- @function [parent=#MoveBy] reverse 
-- @param self
-- @return MoveBy#MoveBy ret (return value: cc.MoveBy)
        
--------------------------------
-- param time in seconds
-- @function [parent=#MoveBy] update 
-- @param self
-- @param #float time
-- @return MoveBy#MoveBy self (return value: cc.MoveBy)
        
return nil
