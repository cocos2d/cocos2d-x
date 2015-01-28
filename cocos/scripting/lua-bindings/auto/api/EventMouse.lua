
--------------------------------
-- @module EventMouse
-- @extend Event
-- @parent_module cc

--------------------------------
--  returns the previous touch location in screen coordinates 
-- @function [parent=#EventMouse] getPreviousLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the current touch location in OpenGL coordinates 
-- @function [parent=#EventMouse] getLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] getMouseButton 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  returns the previous touch location in OpenGL coordinates 
-- @function [parent=#EventMouse] getPreviousLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the delta of 2 current touches locations in screen coordinates 
-- @function [parent=#EventMouse] getDelta 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Set mouse scroll data 
-- @function [parent=#EventMouse] setScrollData 
-- @param self
-- @param #float scrollX
-- @param #float scrollY
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
--------------------------------
--  returns the start touch location in screen coordinates 
-- @function [parent=#EventMouse] getStartLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  returns the start touch location in OpenGL coordinates 
-- @function [parent=#EventMouse] getStartLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] setMouseButton 
-- @param self
-- @param #int button
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
--------------------------------
--  returns the current touch location in screen coordinates 
-- @function [parent=#EventMouse] getLocationInView 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] getScrollY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] getScrollX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] getCursorX 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] getCursorY 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] setCursorPosition 
-- @param self
-- @param #float x
-- @param #float y
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
--------------------------------
-- 
-- @function [parent=#EventMouse] EventMouse 
-- @param self
-- @param #int mouseEventCode
-- @return EventMouse#EventMouse self (return value: cc.EventMouse)
        
return nil
