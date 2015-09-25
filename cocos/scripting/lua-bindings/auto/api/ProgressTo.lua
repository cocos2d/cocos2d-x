
--------------------------------
-- @module ProgressTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- brief Initializes with a duration and destination percentage. <br>
-- param duration Specify the duration of the ProgressTo action. It's a value in seconds.<br>
-- param percent Specify the destination percentage.<br>
-- return If the creation success, return true; otherwise, return false.
-- @function [parent=#ProgressTo] initWithDuration 
-- @param self
-- @param #float duration
-- @param #float percent
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief Create and initializes with a duration and a destination percentage.<br>
-- param duration Specify the duration of the ProgressTo action. It's a value in seconds.<br>
-- param percent Specify the destination percentage.<br>
-- return If the creation success, return a pointer of ProgressTo action; otherwise, return nil.
-- @function [parent=#ProgressTo] create 
-- @param self
-- @param #float duration
-- @param #float percent
-- @return ProgressTo#ProgressTo ret (return value: cc.ProgressTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return ProgressTo#ProgressTo self (return value: cc.ProgressTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressTo] clone 
-- @param self
-- @return ProgressTo#ProgressTo ret (return value: cc.ProgressTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressTo] reverse 
-- @param self
-- @return ProgressTo#ProgressTo ret (return value: cc.ProgressTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressTo] update 
-- @param self
-- @param #float time
-- @return ProgressTo#ProgressTo self (return value: cc.ProgressTo)
        
--------------------------------
-- 
-- @function [parent=#ProgressTo] ProgressTo 
-- @param self
-- @return ProgressTo#ProgressTo self (return value: cc.ProgressTo)
        
return nil
