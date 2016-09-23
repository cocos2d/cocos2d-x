
--------------------------------
-- @module ProgressTimer
-- @extend Node
-- @parent_module cc

--------------------------------
--  Initializes a progress timer with the sprite as the shape the timer goes through 
-- @function [parent=#ProgressTimer] initWithSprite 
-- @param self
-- @param #cc.Sprite sp
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Return the Reverse direction.<br>
-- return If the direction is Anti-clockwise,it will return true.
-- @function [parent=#ProgressTimer] isReverseDirection 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- This allows the bar type to move the component at a specific rate.<br>
-- Set the component to 0 to make sure it stays at 100%.<br>
-- For example you want a left to right bar but not have the height stay 100%.<br>
-- Set the rate to be Vec2(0,1); and set the midpoint to = Vec2(0,.5f).<br>
-- param barChangeRate A Vec2.
-- @function [parent=#ProgressTimer] setBarChangeRate 
-- @param self
-- @param #vec2_table barChangeRate
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
--  Percentages are from 0 to 100.<br>
-- return Percentages.
-- @function [parent=#ProgressTimer] getPercentage 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Set the sprite as the shape. <br>
-- param sprite The sprite as the shape.
-- @function [parent=#ProgressTimer] setSprite 
-- @param self
-- @param #cc.Sprite sprite
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
--  Change the percentage to change progress. <br>
-- return A Type
-- @function [parent=#ProgressTimer] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  The image to show the progress percentage, retain. <br>
-- return A sprite.
-- @function [parent=#ProgressTimer] getSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- Midpoint is used to modify the progress start position.<br>
-- If you're using radials type then the midpoint changes the center point.<br>
-- If you're using bar type then the midpoint changes the bar growth.<br>
-- it expands from the center but clamps to the sprites edge so:<br>
-- you want a left to right then set the midpoint all the way to Vec2(0,y).<br>
-- you want a right to left then set the midpoint all the way to Vec2(1,y).<br>
-- you want a bottom to top then set the midpoint all the way to Vec2(x,0).<br>
-- you want a top to bottom then set the midpoint all the way to Vec2(x,1).<br>
-- param point A Vec2 point.
-- @function [parent=#ProgressTimer] setMidpoint 
-- @param self
-- @param #vec2_table point
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
--  Returns the BarChangeRate.<br>
-- return A barChangeRate.
-- @function [parent=#ProgressTimer] getBarChangeRate 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Set the Reverse direction.<br>
-- param value If value is false it will clockwise,if is true it will Anti-clockwise.
-- @function [parent=#ProgressTimer] setReverseDirection 
-- @param self
-- @param #bool value
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
--  Returns the Midpoint. <br>
-- return A Vec2.
-- @function [parent=#ProgressTimer] getMidpoint 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Set the initial percentage values. <br>
-- param percentage The initial percentage values.
-- @function [parent=#ProgressTimer] setPercentage 
-- @param self
-- @param #float percentage
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
--  Set the ProgressTimer type. <br>
-- param type Is an Type.
-- @function [parent=#ProgressTimer] setType 
-- @param self
-- @param #int type
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
--  Creates a progress timer with the sprite as the shape the timer goes through.<br>
-- param sp The sprite as the shape the timer goes through.<br>
-- return A ProgressTimer.
-- @function [parent=#ProgressTimer] create 
-- @param self
-- @param #cc.Sprite sp
-- @return ProgressTimer#ProgressTimer ret (return value: cc.ProgressTimer)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setAnchorPoint 
-- @param self
-- @param #vec2_table anchorPoint
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] setColor 
-- @param self
-- @param #color3b_table color
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
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
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
--------------------------------
-- 
-- @function [parent=#ProgressTimer] getOpacity 
-- @param self
-- @return unsigned char#unsigned char ret (return value: unsigned char)
        
--------------------------------
-- js ctor
-- @function [parent=#ProgressTimer] ProgressTimer 
-- @param self
-- @return ProgressTimer#ProgressTimer self (return value: cc.ProgressTimer)
        
return nil
