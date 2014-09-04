
--------------------------------
-- @module ControlPotentiometer
-- @extend Control
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setPreviousLocation 
-- @param self
-- @param #vec2_table var
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setValue 
-- @param self
-- @param #float value
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] getProgressTimer 
-- @param self
-- @return ProgressTimer#ProgressTimer ret (return value: cc.ProgressTimer)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] getMaximumValue 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Returns the angle in degree between line1 and line2. 
-- @function [parent=#ControlPotentiometer] angleInDegreesBetweenLineFromPoint_toPoint_toLineFromPoint_toPoint 
-- @param self
-- @param #vec2_table beginLineA
-- @param #vec2_table endLineA
-- @param #vec2_table beginLineB
-- @param #vec2_table endLineB
-- @return float#float ret (return value: float)
        
--------------------------------
--  Factorize the event dispath into these methods. 
-- @function [parent=#ControlPotentiometer] potentiometerBegan 
-- @param self
-- @param #vec2_table location
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setMaximumValue 
-- @param self
-- @param #float maximumValue
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] getMinimumValue 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setThumbSprite 
-- @param self
-- @param #cc.Sprite var
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] getValue 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] getPreviousLocation 
-- @param self
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
--  Returns the distance between the point1 and point2. 
-- @function [parent=#ControlPotentiometer] distanceBetweenPointAndPoint 
-- @param self
-- @param #vec2_table point1
-- @param #vec2_table point2
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] potentiometerEnded 
-- @param self
-- @param #vec2_table location
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setProgressTimer 
-- @param self
-- @param #cc.ProgressTimer var
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setMinimumValue 
-- @param self
-- @param #float minimumValue
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] getThumbSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- Initializes a potentiometer with a track sprite and a progress bar.<br>
-- param trackSprite   Sprite, that is used as a background.<br>
-- param progressTimer ProgressTimer, that is used as a progress bar.
-- @function [parent=#ControlPotentiometer] initWithTrackSprite_ProgressTimer_ThumbSprite 
-- @param self
-- @param #cc.Sprite trackSprite
-- @param #cc.ProgressTimer progressTimer
-- @param #cc.Sprite thumbSprite
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] potentiometerMoved 
-- @param self
-- @param #vec2_table location
        
--------------------------------
-- Creates potentiometer with a track filename and a progress filename.
-- @function [parent=#ControlPotentiometer] create 
-- @param self
-- @param #char backgroundFile
-- @param #char progressFile
-- @param #char thumbFile
-- @return ControlPotentiometer#ControlPotentiometer ret (return value: cc.ControlPotentiometer)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] isTouchInside 
-- @param self
-- @param #cc.Touch touch
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] setEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] onTouchMoved 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] onTouchEnded 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#ControlPotentiometer] onTouchBegan 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- js ctor
-- @function [parent=#ControlPotentiometer] ControlPotentiometer 
-- @param self
        
return nil
