
--------------------------------
-- @module ActionMoveFrame
-- @extend ActionFrame
-- @parent_module ccs

--------------------------------
-- Changes the move action position.<br>
-- param the move action position.
-- @function [parent=#ActionMoveFrame] setPosition 
-- @param self
-- @param #vec2_table pos
-- @return ActionMoveFrame#ActionMoveFrame self (return value: ccs.ActionMoveFrame)
        
--------------------------------
-- Gets the ActionInterval of ActionFrame.<br>
-- parame duration   the duration time of ActionFrame<br>
-- return ActionInterval
-- @function [parent=#ActionMoveFrame] getAction 
-- @param self
-- @param #float duration
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- Gets the move action position.<br>
-- return the move action position.
-- @function [parent=#ActionMoveFrame] getPosition 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- Default constructor
-- @function [parent=#ActionMoveFrame] ActionMoveFrame 
-- @param self
-- @return ActionMoveFrame#ActionMoveFrame self (return value: ccs.ActionMoveFrame)
        
return nil
