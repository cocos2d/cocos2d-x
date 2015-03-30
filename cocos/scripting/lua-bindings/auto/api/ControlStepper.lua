
--------------------------------
-- @module ControlStepper
-- @extend Control
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ControlStepper] getMinusSprite 
-- @param self
-- @return Sprite#Sprite ret (return value: cc.Sprite)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setValue 
-- @param self
-- @param #double value
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setStepValue 
-- @param self
-- @param #double stepValue
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] initWithMinusSpriteAndPlusSprite 
-- @param self
-- @param #cc.Sprite minusSprite
-- @param #cc.Sprite plusSprite
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Set the numeric value of the stepper. If send is true, the Control::EventType::VALUE_CHANGED is sent. 
-- @function [parent=#ControlStepper] setValueWithSendingEvent 
-- @param self
-- @param #double value
-- @param #bool send
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMaximumValue 
-- @param self
-- @param #double maximumValue
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getMinusLabel 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getPlusLabel 
-- @param self
-- @return Label#Label ret (return value: cc.Label)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setWraps 
-- @param self
-- @param #bool wraps
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMinusLabel 
-- @param self
-- @param #cc.Label var
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
--  Start the autorepeat increment/decrement. 
-- @function [parent=#ControlStepper] startAutorepeat 
-- @param self
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
--  Update the layout of the stepper with the given touch location. 
-- @function [parent=#ControlStepper] updateLayoutUsingTouchLocation 
-- @param self
-- @param #vec2_table location
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] isContinuous 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Stop the autorepeat. 
-- @function [parent=#ControlStepper] stopAutorepeat 
-- @param self
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMinimumValue 
-- @param self
-- @param #double minimumValue
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setPlusLabel 
-- @param self
-- @param #cc.Label var
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] getValue 
-- @param self
-- @return double#double ret (return value: double)
        
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
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] setMinusSprite 
-- @param self
-- @param #cc.Sprite var
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
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
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] onTouchEnded 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
--------------------------------
-- 
-- @function [parent=#ControlStepper] update 
-- @param self
-- @param #float dt
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
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
-- @return ControlStepper#ControlStepper self (return value: cc.ControlStepper)
        
return nil
