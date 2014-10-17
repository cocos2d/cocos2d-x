
--------------------------------
-- @module AnimationFrame
-- @extend Ref
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#AnimationFrame] setSpriteFrame 
-- @param self
-- @param #cc.SpriteFrame frame
        
--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#AnimationFrame] getUserInfo
-- @param self
-- @return map_table#map_table ret (return value: map_table)

--------------------------------
--  Sets the units of time the frame takes 
-- @function [parent=#AnimationFrame] setDelayUnits 
-- @param self
-- @param #float delayUnits
        
--------------------------------
-- 
-- @function [parent=#AnimationFrame] clone 
-- @param self
-- @return AnimationFrame#AnimationFrame ret (return value: cc.AnimationFrame)
        
--------------------------------
-- 
-- @function [parent=#AnimationFrame] getSpriteFrame 
-- @param self
-- @return SpriteFrame#SpriteFrame ret (return value: cc.SpriteFrame)
        
--------------------------------
--  Gets the units of time the frame takes 
-- @function [parent=#AnimationFrame] getDelayUnits 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets user infomation 
-- @function [parent=#AnimationFrame] setUserInfo 
-- @param self
-- @param #map_table userInfo
        
--------------------------------
-- Creates the animation frame with a spriteframe, number of delay units and a notification user info<br>
-- since 3.0
-- @function [parent=#AnimationFrame] create 
-- @param self
-- @param #cc.SpriteFrame spriteFrame
-- @param #float delayUnits
-- @param #map_table userInfo
-- @return AnimationFrame#AnimationFrame ret (return value: cc.AnimationFrame)
        
return nil
