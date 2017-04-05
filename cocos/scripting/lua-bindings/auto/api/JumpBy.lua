
--------------------------------
-- @module JumpBy
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- initializes the action<br>
-- param duration in seconds
-- @function [parent=#JumpBy] initWithDuration 
-- @param self
-- @param #float duration
-- @param #vec2_table position
-- @param #float height
-- @param #int jumps
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates the action.<br>
-- param duration Duration time, in seconds.<br>
-- param position The jumping distance.<br>
-- param height The jumping height.<br>
-- param jumps The jumping times.<br>
-- return An autoreleased JumpBy object.
-- @function [parent=#JumpBy] create 
-- @param self
-- @param #float duration
-- @param #vec2_table position
-- @param #float height
-- @param #int jumps
-- @return JumpBy#JumpBy ret (return value: cc.JumpBy)
        
--------------------------------
-- 
-- @function [parent=#JumpBy] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return JumpBy#JumpBy self (return value: cc.JumpBy)
        
--------------------------------
-- 
-- @function [parent=#JumpBy] clone 
-- @param self
-- @return JumpBy#JumpBy ret (return value: cc.JumpBy)
        
--------------------------------
-- 
-- @function [parent=#JumpBy] reverse 
-- @param self
-- @return JumpBy#JumpBy ret (return value: cc.JumpBy)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#JumpBy] update 
-- @param self
-- @param #float time
-- @return JumpBy#JumpBy self (return value: cc.JumpBy)
        
--------------------------------
-- 
-- @function [parent=#JumpBy] JumpBy 
-- @param self
-- @return JumpBy#JumpBy self (return value: cc.JumpBy)
        
return nil
