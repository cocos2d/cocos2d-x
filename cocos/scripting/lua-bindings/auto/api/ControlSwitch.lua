
--------------------------------
-- @module ControlSwitch
-- @extend Control
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#ControlSwitch] setEnabled 
-- @param self
-- @param #bool enabled
-- @return ControlSwitch#ControlSwitch self (return value: cc.ControlSwitch)
        
--------------------------------
-- @overload self, bool         
-- @overload self, bool, bool         
-- @function [parent=#ControlSwitch] setOn
-- @param self
-- @param #bool isOn
-- @param #bool animated
-- @return ControlSwitch#ControlSwitch self (return value: cc.ControlSwitch)

--------------------------------
-- 
-- @function [parent=#ControlSwitch] isOn 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite, cc.Label, cc.Label         
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite         
-- @function [parent=#ControlSwitch] initWithMaskSprite
-- @param self
-- @param #cc.Sprite maskSprite
-- @param #cc.Sprite onSprite
-- @param #cc.Sprite offSprite
-- @param #cc.Sprite thumbSprite
-- @param #cc.Label onLabel
-- @param #cc.Label offLabel
-- @return bool#bool ret (return value: bool)

--------------------------------
-- 
-- @function [parent=#ControlSwitch] hasMoved 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ControlSwitch] locationFromTouch 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite         
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite, cc.Label, cc.Label         
-- @function [parent=#ControlSwitch] create
-- @param self
-- @param #cc.Sprite maskSprite
-- @param #cc.Sprite onSprite
-- @param #cc.Sprite offSprite
-- @param #cc.Sprite thumbSprite
-- @param #cc.Label onLabel
-- @param #cc.Label offLabel
-- @return ControlSwitch#ControlSwitch ret (return value: cc.ControlSwitch)

--------------------------------
-- 
-- @function [parent=#ControlSwitch] onTouchMoved 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return ControlSwitch#ControlSwitch self (return value: cc.ControlSwitch)
        
--------------------------------
-- 
-- @function [parent=#ControlSwitch] onTouchEnded 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return ControlSwitch#ControlSwitch self (return value: cc.ControlSwitch)
        
--------------------------------
-- 
-- @function [parent=#ControlSwitch] onTouchCancelled 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return ControlSwitch#ControlSwitch self (return value: cc.ControlSwitch)
        
--------------------------------
-- 
-- @function [parent=#ControlSwitch] onTouchBegan 
-- @param self
-- @param #cc.Touch pTouch
-- @param #cc.Event pEvent
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- js ctor
-- @function [parent=#ControlSwitch] ControlSwitch 
-- @param self
-- @return ControlSwitch#ControlSwitch self (return value: cc.ControlSwitch)
        
return nil
