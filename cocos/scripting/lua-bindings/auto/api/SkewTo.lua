
--------------------------------
-- @module SkewTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- param t In seconds.
-- @function [parent=#SkewTo] initWithDuration 
-- @param self
-- @param #float t
-- @param #float sx
-- @param #float sy
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates the action.<br>
-- param t Duration time, in seconds.<br>
-- param sx Skew x angle.<br>
-- param sy Skew y angle.<br>
-- return An autoreleased SkewTo object.
-- @function [parent=#SkewTo] create 
-- @param self
-- @param #float t
-- @param #float sx
-- @param #float sy
-- @return SkewTo#SkewTo ret (return value: cc.SkewTo)
        
--------------------------------
-- 
-- @function [parent=#SkewTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return SkewTo#SkewTo self (return value: cc.SkewTo)
        
--------------------------------
-- 
-- @function [parent=#SkewTo] clone 
-- @param self
-- @return SkewTo#SkewTo ret (return value: cc.SkewTo)
        
--------------------------------
-- 
-- @function [parent=#SkewTo] reverse 
-- @param self
-- @return SkewTo#SkewTo ret (return value: cc.SkewTo)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#SkewTo] update 
-- @param self
-- @param #float time
-- @return SkewTo#SkewTo self (return value: cc.SkewTo)
        
--------------------------------
-- 
-- @function [parent=#SkewTo] SkewTo 
-- @param self
-- @return SkewTo#SkewTo self (return value: cc.SkewTo)
        
return nil
