
--------------------------------
-- @module TintBy
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  initializes the action with duration and color 
-- @function [parent=#TintBy] initWithDuration 
-- @param self
-- @param #float duration
-- @param #short deltaRed
-- @param #short deltaGreen
-- @param #short deltaBlue
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates an action with duration and color.<br>
-- param duration Duration time, in seconds.<br>
-- param deltaRed Delta red color.<br>
-- param deltaGreen Delta green color.<br>
-- param deltaBlue Delta blue color.<br>
-- return An autoreleased TintBy object.
-- @function [parent=#TintBy] create 
-- @param self
-- @param #float duration
-- @param #short deltaRed
-- @param #short deltaGreen
-- @param #short deltaBlue
-- @return TintBy#TintBy ret (return value: cc.TintBy)
        
--------------------------------
-- 
-- @function [parent=#TintBy] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return TintBy#TintBy self (return value: cc.TintBy)
        
--------------------------------
-- 
-- @function [parent=#TintBy] clone 
-- @param self
-- @return TintBy#TintBy ret (return value: cc.TintBy)
        
--------------------------------
-- 
-- @function [parent=#TintBy] reverse 
-- @param self
-- @return TintBy#TintBy ret (return value: cc.TintBy)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#TintBy] update 
-- @param self
-- @param #float time
-- @return TintBy#TintBy self (return value: cc.TintBy)
        
--------------------------------
-- 
-- @function [parent=#TintBy] TintBy 
-- @param self
-- @return TintBy#TintBy self (return value: cc.TintBy)
        
return nil
