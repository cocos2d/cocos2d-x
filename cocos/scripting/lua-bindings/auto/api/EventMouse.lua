
--------------------------------
-- @module EventMouse
-- @extend Event
-- @parent_module cc

--------------------------------
--  Returns the previous touch location in screen coordinates.<br>
-- return The previous touch location in screen coordinates.<br>
-- js NA
-- @function [parent=#EventMouse] getPreviousLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the current touch location in OpenGL coordinates.<br>
-- return The current touch location in OpenGL coordinates.
-- @function [parent=#EventMouse] getLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get mouse button.<br>
-- return The mouse button.<br>
-- js getButton
-- @function [parent=#EventMouse] getMouseButton 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Returns the previous touch location in OpenGL coordinates.<br>
-- return The previous touch location in OpenGL coordinates.<br>
-- js NA
-- @function [parent=#EventMouse] getPreviousLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the delta of 2 current touches locations in screen coordinates.<br>
-- return The delta of 2 current touches locations in screen coordinates.
-- @function [parent=#EventMouse] getDelta 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Set mouse scroll data.<br>
-- param scrollX The scroll data of x axis.<br>
-- param scrollY The scroll data of y axis.
-- @function [parent=#EventMouse] setScrollData 
-- @param self
-- @param #float scrollX
-- @param #float scrollY
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
--------------------------------
--  Returns the start touch location in screen coordinates.<br>
-- return The start touch location in screen coordinates.<br>
-- js NA
-- @function [parent=#EventMouse] getStartLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the start touch location in OpenGL coordinates.<br>
-- return The start touch location in OpenGL coordinates.<br>
-- js NA
-- @function [parent=#EventMouse] getStartLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Set mouse button.<br>
-- param button a given mouse button.<br>
-- js setButton
-- @function [parent=#EventMouse] setMouseButton 
-- @param self
-- @param #int button
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
--------------------------------
--  Returns the current touch location in screen coordinates.<br>
-- return The current touch location in screen coordinates.
-- @function [parent=#EventMouse] getLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Get mouse scroll data of y axis.<br>
-- return The scroll data of y axis.
-- @function [parent=#EventMouse] getScrollY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get mouse scroll data of x axis.<br>
-- return The scroll data of x axis.
-- @function [parent=#EventMouse] getScrollX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get the cursor position of x axis.<br>
-- return The x coordinate of cursor position.<br>
-- js getLocationX
-- @function [parent=#EventMouse] getCursorX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Get the cursor position of y axis.<br>
-- return The y coordinate of cursor position.<br>
-- js getLocationY
-- @function [parent=#EventMouse] getCursorY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the cursor position.<br>
-- param x The x coordinate of cursor position.<br>
-- param y The y coordinate of cursor position.<br>
-- js setLocation
-- @function [parent=#EventMouse] setCursorPosition 
-- @param self
-- @param #float x
-- @param #float y
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
--------------------------------
--  Constructor.<br>
-- param mouseEventCode A given mouse event type.<br>
-- js ctor
-- @function [parent=#EventMouse] EventMouse 
-- @param self
-- @param #int mouseEventCode
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
return nil
