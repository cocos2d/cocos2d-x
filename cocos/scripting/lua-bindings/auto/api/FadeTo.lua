
--------------------------------
-- @module FadeTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- initializes the action with duration and opacity <br>
-- param duration in seconds
-- @function [parent=#FadeTo] initWithDuration 
-- @param self
-- @param #float duration
-- @param #unsigned char opacity
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates an action with duration and opacity.<br>
-- param duration Duration time, in seconds.<br>
-- param opacity A certain opacity, the range is from 0 to 255.<br>
-- return An autoreleased FadeTo object.
-- @function [parent=#FadeTo] create 
-- @param self
-- @param #float duration
-- @param #unsigned char opacity
-- @return FadeTo#FadeTo ret (return value: cc.FadeTo)
        
--------------------------------
-- 
-- @function [parent=#FadeTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return FadeTo#FadeTo self (return value: cc.FadeTo)
        
--------------------------------
-- 
-- @function [parent=#FadeTo] clone 
-- @param self
-- @return FadeTo#FadeTo ret (return value: cc.FadeTo)
        
--------------------------------
-- 
-- @function [parent=#FadeTo] reverse 
-- @param self
-- @return FadeTo#FadeTo ret (return value: cc.FadeTo)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#FadeTo] update 
-- @param self
-- @param #float time
-- @return FadeTo#FadeTo self (return value: cc.FadeTo)
        
--------------------------------
-- 
-- @function [parent=#FadeTo] FadeTo 
-- @param self
-- @return FadeTo#FadeTo self (return value: cc.FadeTo)
        
return nil
