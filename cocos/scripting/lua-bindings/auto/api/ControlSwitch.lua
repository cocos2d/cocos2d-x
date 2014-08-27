
--------------------------------
-- @module ControlSwitch
-- @extend Control
-- @parent_module cc

--------------------------------
-- @function [parent=#ControlSwitch] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @overload self, bool         
-- @overload self, bool, bool         
-- @function [parent=#ControlSwitch] setOn
-- @param self
-- @param #bool bool
-- @param #bool bool

--------------------------------
-- @function [parent=#ControlSwitch] isOn 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite, cc.Label, cc.Label         
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite         
-- @function [parent=#ControlSwitch] initWithMaskSprite
-- @param self
-- @param #cc.Sprite sprite
-- @param #cc.Sprite sprite
-- @param #cc.Sprite sprite
-- @param #cc.Sprite sprite
-- @param #cc.Label label
-- @param #cc.Label label
-- @return bool#bool ret (retunr value: bool)

--------------------------------
-- @function [parent=#ControlSwitch] hasMoved 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlSwitch] locationFromTouch 
-- @param self
-- @param #cc.Touch touch
-- @return vec2_table#vec2_table ret (return value: vec2_table)
        
--------------------------------
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite         
-- @overload self, cc.Sprite, cc.Sprite, cc.Sprite, cc.Sprite, cc.Label, cc.Label         
-- @function [parent=#ControlSwitch] create
-- @param self
-- @param #cc.Sprite sprite
-- @param #cc.Sprite sprite
-- @param #cc.Sprite sprite
-- @param #cc.Sprite sprite
-- @param #cc.Label label
-- @param #cc.Label label
-- @return ControlSwitch#ControlSwitch ret (retunr value: cc.ControlSwitch)

--------------------------------
-- @function [parent=#ControlSwitch] onTouchMoved 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ControlSwitch] onTouchEnded 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ControlSwitch] onTouchCancelled 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
        
--------------------------------
-- @function [parent=#ControlSwitch] onTouchBegan 
-- @param self
-- @param #cc.Touch touch
-- @param #cc.Event event
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ControlSwitch] ControlSwitch 
-- @param self
        
return nil
