
--------------------------------
-- @module ControlStepper
-- @extend Control
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ControlStepper] setMinusSprite 
-- @param self
-- @param #cc.Sprite var
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getMinusLabel 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setWraps 
-- @param self
-- @param #bool wraps
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] isContinuous 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getMinusSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
--  Update the layout of the stepper with the given touch location. 
-- @function [parent=#ControlStepper] updateLayoutUsingTouchLocation 
-- @param self
-- @param #vec2_table location
        
--------------------------------
--  Set the numeric value of the stepper. If send is true, the Control::EventType::VALUE_CHANGED is sent. 
-- @function [parent=#ControlStepper] setValueWithSendingEvent 
-- @param self
-- @param #double value
-- @param #bool send
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getPlusLabel 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
--  Stop the autorepeat. 
-- @function [parent=#ControlStepper] stopAutorepeat 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMinimumValue 
-- @param self
-- @param #double minimumValue
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getPlusSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setPlusSprite 
-- @param self
-- @param #cc.Sprite var
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMinusLabel 
-- @param self
-- @param #cc.Label var
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setValue 
-- @param self
-- @param #double value
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setStepValue 
-- @param self
-- @param #double stepValue
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMaximumValue 
-- @param self
-- @param #double maximumValue
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] update 
-- @param self
-- @param #float dt
        
--------------------------------
--  Start the autorepeat increment/decrement. 
-- @function [parent=#ControlStepper] startAutorepeat 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] initWithMinusSpriteAndPlusSprite 
-- @param self
-- @param #cc.Sprite minusSprite
-- @param #cc.Sprite plusSprite
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getValue 
-- @param self
-- @return double#double ret (return value: double)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setPlusLabel 
-- @param self
-- @param #cc.Label var
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] create 
-- @param self
-- @param #cc.Sprite minusSprite
-- @param #cc.Sprite plusSprite
-- @return ControlStepper#ControlStepper ret (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] onTouchMoved 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] onTouchEnded 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] onTouchBegan 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- js ctor
-- @function [parent=#ControlStepper] ControlStepper 
-- @param self
        
return nil
