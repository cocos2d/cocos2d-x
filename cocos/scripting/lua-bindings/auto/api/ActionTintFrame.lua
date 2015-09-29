
--------------------------------
-- @module ActionTintFrame
-- @extend ActionFrame
-- @parent_module ccs

--------------------------------
-- Gets the tint action color.<br>
-- return the tint action color.
-- @function [parent=#ActionTintFrame] getColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- Gets the ActionInterval of ActionFrame.<br>
-- parame duration   the duration time of ActionFrame<br>
-- return ActionInterval
-- @function [parent=#ActionTintFrame] getAction 
-- @param self
-- @param #float duration
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- Changes the tint action color.<br>
-- param ccolor the tint action color
-- @function [parent=#ActionTintFrame] setColor 
-- @param self
-- @param #color3b_table ccolor
-- @return ActionTintFrame#ActionTintFrame self (return value: ccs.ActionTintFrame)
        
--------------------------------
-- Default constructor
-- @function [parent=#ActionTintFrame] ActionTintFrame 
-- @param self
-- @return ActionTintFrame#ActionTintFrame self (return value: ccs.ActionTintFrame)
        
return nil
