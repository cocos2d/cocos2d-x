
--------------------------------
-- @module BezierBy
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- initializes the action with a duration and a bezier configuration<br>
-- param t in seconds
-- @function [parent=#BezierBy] initWithDuration 
-- @param self
-- @param #float t
-- @param #cc._ccBezierConfig c
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#BezierBy] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return BezierBy#BezierBy self (return value: cc.BezierBy)
        
--------------------------------
-- 
-- @function [parent=#BezierBy] clone 
-- @param self
-- @return BezierBy#BezierBy ret (return value: cc.BezierBy)
        
--------------------------------
-- 
-- @function [parent=#BezierBy] reverse 
-- @param self
-- @return BezierBy#BezierBy ret (return value: cc.BezierBy)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#BezierBy] update 
-- @param self
-- @param #float time
-- @return BezierBy#BezierBy self (return value: cc.BezierBy)
        
--------------------------------
-- 
-- @function [parent=#BezierBy] BezierBy 
-- @param self
-- @return BezierBy#BezierBy self (return value: cc.BezierBy)
        
return nil
