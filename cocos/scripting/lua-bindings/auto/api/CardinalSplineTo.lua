
--------------------------------
-- @module CardinalSplineTo
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
--  Return a PointArray.<br>
-- return A PointArray.
-- @function [parent=#CardinalSplineTo] getPoints 
-- @param self
-- @return point_table#point_table ret (return value: point_table)
        
--------------------------------
--  It will update the target position and change the _previousPosition to newPos<br>
-- param newPos The new position.
-- @function [parent=#CardinalSplineTo] updatePosition 
-- @param self
-- @param #vec2_table newPos
-- @return CardinalSplineTo#CardinalSplineTo self (return value: cc.CardinalSplineTo)
        
--------------------------------
-- Initializes the action with a duration and an array of points.<br>
-- param duration In seconds.<br>
-- param point An PointArray.<br>
-- param tension Goodness of fit.
-- @function [parent=#CardinalSplineTo] initWithDuration 
-- @param self
-- @param #float duration
-- @param #point_table points
-- @param #float tension
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#CardinalSplineTo] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return CardinalSplineTo#CardinalSplineTo self (return value: cc.CardinalSplineTo)
        
--------------------------------
-- 
-- @function [parent=#CardinalSplineTo] clone 
-- @param self
-- @return CardinalSplineTo#CardinalSplineTo ret (return value: cc.CardinalSplineTo)
        
--------------------------------
-- 
-- @function [parent=#CardinalSplineTo] reverse 
-- @param self
-- @return CardinalSplineTo#CardinalSplineTo ret (return value: cc.CardinalSplineTo)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#CardinalSplineTo] update 
-- @param self
-- @param #float time
-- @return CardinalSplineTo#CardinalSplineTo self (return value: cc.CardinalSplineTo)
        
--------------------------------
-- js ctor<br>
-- lua NA
-- @function [parent=#CardinalSplineTo] CardinalSplineTo 
-- @param self
-- @return CardinalSplineTo#CardinalSplineTo self (return value: cc.CardinalSplineTo)
        
return nil
