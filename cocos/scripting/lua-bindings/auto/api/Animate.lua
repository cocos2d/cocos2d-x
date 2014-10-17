
--------------------------------
-- @module Animate
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#Animate] getAnimation
-- @param self
-- @return Animation#Animation ret (return value: cc.Animation)

--------------------------------
--  sets the Animation object to be animated 
-- @function [parent=#Animate] setAnimation 
-- @param self
-- @param #cc.Animation animation
        
--------------------------------
--  creates the action with an Animation and will restore the original frame when the animation is over 
-- @function [parent=#Animate] create 
-- @param self
-- @param #cc.Animation animation
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- 
-- @function [parent=#Animate] startWithTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- 
-- @function [parent=#Animate] clone 
-- @param self
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- 
-- @function [parent=#Animate] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#Animate] reverse 
-- @param self
-- @return Animate#Animate ret (return value: cc.Animate)
        
--------------------------------
-- 
-- @function [parent=#Animate] update 
-- @param self
-- @param #float t
        
return nil
