
--------------------------------
-- @module Touch
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Returns the previous touch location in screen coordinates. <br>
-- return The previous touch location in screen coordinates.
-- @function [parent=#Touch] getPreviousLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the current touch location in OpenGL coordinates.<br>
-- return The current touch location in OpenGL coordinates.
-- @function [parent=#Touch] getLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the delta of 2 current touches locations in screen coordinates.<br>
-- return The delta of 2 current touches locations in screen coordinates.
-- @function [parent=#Touch] getDelta 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the start touch location in screen coordinates.<br>
-- return The start touch location in screen coordinates.
-- @function [parent=#Touch] getStartLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the start touch location in OpenGL coordinates.<br>
-- return The start touch location in OpenGL coordinates.
-- @function [parent=#Touch] getStartLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get touch id.<br>
-- js getId<br>
-- lua getId<br>
-- return The id of touch.
-- @function [parent=#Touch] getID 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Set the touch infomation. It always used to monitor touch event.<br>
-- param id A given id<br>
-- param x A given x coordinate.<br>
-- param y A given y coordinate.
-- @function [parent=#Touch] setTouchInfo 
-- @param self
-- @param #int id
-- @param #float x
-- @param #float y
-- @return Touch#Touch self (return value: cc.Touch)
        
--------------------------------
--  Returns the current touch location in screen coordinates.<br>
-- return The current touch location in screen coordinates.
-- @function [parent=#Touch] getLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the previous touch location in OpenGL coordinates.<br>
-- return The previous touch location in OpenGL coordinates.
-- @function [parent=#Touch] getPreviousLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Constructor.<br>
-- js ctor
-- @function [parent=#Touch] Touch 
-- @param self
-- @return Touch#Touch self (return value: cc.Touch)
        
return nil
