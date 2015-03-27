
--------------------------------
-- @module JumpTo
-- @extend JumpBy
-- @parent_module cc

--------------------------------
-- Creates the action.<br>
-- param duration Duration time, in seconds.<br>
-- param position The jumping destination position.<br>
-- param height The jumping height.<br>
-- param jumps The jumping times.<br>
-- return An autoreleased JumpTo object.
-- @function [parent=#JumpTo] create 
-- @param self
-- @param #float duration
-- @param #vec2_table position
-- @param #float height
-- @param #int jumps
-- @return JumpTo#JumpTo ret (return value: cc.JumpTo)
        
--------------------------------
-- 
-- @function [parent=#JumpTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return JumpTo#JumpTo self (return value: cc.JumpTo)
        
--------------------------------
-- 
-- @function [parent=#JumpTo] clone 
-- @param self
-- @return JumpTo#JumpTo ret (return value: cc.JumpTo)
        
--------------------------------
-- 
-- @function [parent=#JumpTo] reverse 
-- @param self
-- @return JumpTo#JumpTo ret (return value: cc.JumpTo)
        
return nil
