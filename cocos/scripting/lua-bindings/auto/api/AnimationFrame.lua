
--------------------------------
-- @module AnimationFrame
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Set the SpriteFrame.<br>
-- param frame A SpriteFrame will be used.
-- @function [parent=#AnimationFrame] setSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame frame
-- @return AnimationFrame#AnimationFrame self (return value: cc.AnimationFrame)
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#AnimationFrame] getUserInfo
-- @param self
-- @return map_table#map_table ret (return value: map_table)

--------------------------------
--  Sets the units of time the frame takes.<br>
-- param delayUnits The units of time the frame takes.
-- @function [parent=#AnimationFrame] setDelayUnits 
-- @param self
-- @param #float delayUnits
-- @return AnimationFrame#AnimationFrame self (return value: cc.AnimationFrame)
        
--------------------------------
-- 
-- @function [parent=#AnimationFrame] clone 
-- @param self
-- @return AnimationFrame#AnimationFrame ret (return value: cc.AnimationFrame)
        
--------------------------------
--  Return a SpriteFrameName to be used.<br>
-- return a SpriteFrameName to be used.
-- @function [parent=#AnimationFrame] getSpriteFrame 
-- @param self
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
--  Gets the units of time the frame takes.<br>
-- return The units of time the frame takes.
-- @function [parent=#AnimationFrame] getDelayUnits 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets user information.<br>
-- param userInfo A dictionary as UserInfo.
-- @function [parent=#AnimationFrame] setUserInfo 
-- @param self
-- @param #map_table userInfo
-- @return AnimationFrame#AnimationFrame self (return value: cc.AnimationFrame)
        
--------------------------------
--  initializes the animation frame with a spriteframe, number of delay units and a notification user info 
-- @function [parent=#AnimationFrame] initWithSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #float delayUnits
-- @param #map_table userInfo
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Creates the animation frame with a spriteframe, number of delay units and a notification user info.<br>
-- param spriteFrame The animation frame with a spriteframe.<br>
-- param delayUnits Number of delay units.<br>
-- param userInfo A notification user info.<br>
-- since 3.0
-- @function [parent=#AnimationFrame] create 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #float delayUnits
-- @param #map_table userInfo
-- @return AnimationFrame#AnimationFrame ret (return value: cc.AnimationFrame)
        
--------------------------------
-- js ctor
-- @function [parent=#AnimationFrame] AnimationFrame 
-- @param self
-- @return AnimationFrame#AnimationFrame self (return value: cc.AnimationFrame)
        
return nil
