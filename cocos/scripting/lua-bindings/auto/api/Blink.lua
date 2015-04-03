
--------------------------------
-- @module Blink
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- Creates the action.<br>
-- param duration Duration time, in seconds.<br>
-- param blinks Blink times.<br>
-- return An autoreleased Blink object.
-- @function [parent=#Blink] create 
-- @param self
-- @param #float duration
-- @param #int blinks
-- @return Blink#Blink ret (return value: cc.Blink)
        
--------------------------------
-- 
-- @function [parent=#Blink] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Blink#Blink self (return value: cc.Blink)
        
--------------------------------
-- 
-- @function [parent=#Blink] clone 
-- @param self
-- @return Blink#Blink ret (return value: cc.Blink)
        
--------------------------------
-- 
-- @function [parent=#Blink] stop 
-- @param self
-- @return Blink#Blink self (return value: cc.Blink)
        
--------------------------------
-- 
-- @function [parent=#Blink] reverse 
-- @param self
-- @return Blink#Blink ret (return value: cc.Blink)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#Blink] update 
-- @param self
-- @param #float time
-- @return Blink#Blink self (return value: cc.Blink)
        
return nil
