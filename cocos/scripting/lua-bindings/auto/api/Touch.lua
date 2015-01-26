
--------------------------------
-- @module Touch
-- @extend Ref
-- @parent_module cc

--------------------------------
--  returns the previous touch location in screen coordinates 
-- @function [parent=#Touch] getPreviousLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the current touch location in OpenGL coordinates 
-- @function [parent=#Touch] getLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the delta of 2 current touches locations in screen coordinates 
-- @function [parent=#Touch] getDelta 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the start touch location in screen coordinates 
-- @function [parent=#Touch] getStartLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the start touch location in OpenGL coordinates 
-- @function [parent=#Touch] getStartLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- js getId<br>
-- lua getId
-- @function [parent=#Touch] getID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Touch] setTouchInfo 
-- @param self
-- @param #int id
-- @param #float x
-- @param #float y
-- @return Touch#Touch self (return value: cc.Touch)
        
--------------------------------
--  returns the current touch location in screen coordinates 
-- @function [parent=#Touch] getLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the previous touch location in OpenGL coordinates 
-- @function [parent=#Touch] getPreviousLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#Touch] Touch 
-- @param self
-- @return Touch#Touch self (return value: cc.Touch)
        
return nil
