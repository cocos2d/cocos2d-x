
--------------------------------
-- @module Control
-- @extend Layer
-- @parent_module cc

--------------------------------
--  Tells whether the control is enabled. 
-- @function [parent=#Control] setEnabled 
-- @param self
-- @param #bool bEnabled
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- 
-- @function [parent=#Control] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- 
-- @function [parent=#Control] getState 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Control] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- Sends action messages for the given control events.<br>
-- param controlEvents A bitmask whose set flags specify the control events for<br>
-- which action messages are sent. See "CCControlEvent" for bitmask constants.
-- @function [parent=#Control] sendActionsForControlEvents 
-- @param self
-- @param #int controlEvents
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
--  A Boolean value that determines the control selected state. 
-- @function [parent=#Control] setSelected 
-- @param self
-- @param #bool bSelected
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- 
-- @function [parent=#Control] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Control] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- Updates the control layout using its current internal state.
-- @function [parent=#Control] needsLayout 
-- @param self
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- 
-- @function [parent=#Control] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Control] hasVisibleParents 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Control] isSelected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Returns a boolean value that indicates whether a touch is inside the bounds<br>
-- of the receiver. The given touch must be relative to the world.<br>
-- param touch A Touch object that represents a touch.<br>
-- return Whether a touch is inside the receiver's rect.
-- @function [parent=#Control] isTouchInside 
-- @param self
-- @param #cc.Touch touch
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  A Boolean value that determines whether the control is highlighted. 
-- @function [parent=#Control] setHighlighted 
-- @param self
-- @param #bool bHighlighted
-- @return Control#Control self (return value: cc.Control)
        
--------------------------------
-- Returns a point corresponding to the touh location converted into the<br>
-- control space coordinates.<br>
-- param touch A Touch object that represents a touch.
-- @function [parent=#Control] getTouchLocation 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#Control] isHighlighted 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Creates a Control object 
-- @function [parent=#Control] create 
-- @param self
-- @return Control#Control ret (return value: cc.Control)
        
--------------------------------
-- 
-- @function [parent=#Control] isOpacityModifyRGB 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Control] setOpacityModifyRGB 
-- @param self
-- @param #bool bOpacityModifyRGB
-- @return Control#Control self (return value: cc.Control)
        
return nil
