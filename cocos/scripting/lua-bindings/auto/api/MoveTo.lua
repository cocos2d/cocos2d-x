
--------------------------------
-- @module MoveTo
-- @extend MoveBy
-- @parent_module cc

--------------------------------
-- @overload self, float, vec3_table         
-- @overload self, float, vec2_table         
-- @function [parent=#MoveTo] initWithDuration
-- @param self
-- @param #float duration
-- @param #vec2_table position
-- @return bool#bool ret (return value: bool)

--------------------------------
-- @overload self, float, vec3_table         
-- @overload self, float, vec2_table         
-- @function [parent=#MoveTo] create
-- @param self
-- @param #float duration
-- @param #vec2_table position
-- @return MoveTo#MoveTo ret (return value: cc.MoveTo)

--------------------------------
-- 
-- @function [parent=#MoveTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return MoveTo#MoveTo self (return value: cc.MoveTo)
        
--------------------------------
-- 
-- @function [parent=#MoveTo] clone 
-- @param self
-- @return MoveTo#MoveTo ret (return value: cc.MoveTo)
        
--------------------------------
-- 
-- @function [parent=#MoveTo] reverse 
-- @param self
-- @return MoveTo#MoveTo ret (return value: cc.MoveTo)
        
--------------------------------
-- 
-- @function [parent=#MoveTo] MoveTo 
-- @param self
-- @return MoveTo#MoveTo self (return value: cc.MoveTo)
        
return nil
