
--------------------------------
-- @module ProgressTimer
-- @extend Node
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ProgressTimer] isReverseDirection 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- This allows the bar type to move the component at a specific rate<br>
-- Set the component to 0 to make sure it stays at 100%.<br>
-- For example you want a left to right bar but not have the height stay 100%<br>
-- Set the rate to be Vec2(0,1); and set the midpoint to = Vec2(0,.5f);
-- @function [parent=#ProgressTimer] setBarChangeRate 
-- @param self
-- @param #vec2_table barChangeRate
        
--------------------------------
--  Percentages are from 0 to 100 
-- @function [parent=#ProgressTimer] getPercentage 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setSprite 
-- @param self
-- @param #cc.Sprite sprite
        
--------------------------------
--  Change the percentage to change progress. 
-- @function [parent=#ProgressTimer] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  The image to show the progress percentage, retain 
-- @function [parent=#ProgressTimer] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- Midpoint is used to modify the progress start position.<br>
-- If you're using radials type then the midpoint changes the center point<br>
-- If you're using bar type the the midpoint changes the bar growth<br>
-- it expands from the center but clamps to the sprites edge so:<br>
-- you want a left to right then set the midpoint all the way to Vec2(0,y)<br>
-- you want a right to left then set the midpoint all the way to Vec2(1,y)<br>
-- you want a bottom to top then set the midpoint all the way to Vec2(x,0)<br>
-- you want a top to bottom then set the midpoint all the way to Vec2(x,1)
-- @function [parent=#ProgressTimer] setMidpoint 
-- @param self
-- @param #vec2_table point
        
--------------------------------
--  Returns the BarChangeRate 
-- @function [parent=#ProgressTimer] getBarChangeRate 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @overload self, bool         
-- @overload self, bool         
-- @function [parent=#ProgressTimer] setReverseDirection
-- @param self
-- @param #bool reverse

--------------------------------
--  Returns the Midpoint 
-- @function [parent=#ProgressTimer] getMidpoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setPercentage 
-- @param self
-- @param #float percentage
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setType 
-- @param self
-- @param #int type
        
--------------------------------
--  Creates a progress timer with the sprite as the shape the timer goes through 
-- @function [parent=#ProgressTimer] create 
-- @param self
-- @param #cc.Sprite sp
-- @return ProgressTimer#ProgressTimer ret (return value: cc.ProgressTimer)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setAnchorPoint 
-- @param self
-- @param #vec2_table anchorPoint
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setColor 
-- @param self
-- @param #color3b_table color
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] getColor 
-- @param self
-- @return color3b_table#color3b_table ret (return value: color3b_table)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setOpacity 
-- @param self
-- @param #unsigned char opacity
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
return nil
