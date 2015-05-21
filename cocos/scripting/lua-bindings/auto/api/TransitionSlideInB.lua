
--------------------------------
-- @module TransitionSlideInB
-- @extend TransitionSlideInL
-- @parent_module cc

--------------------------------
--  Creates a transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionSlideInB object.
-- @function [parent=#TransitionSlideInB] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionSlideInB#TransitionSlideInB ret (return value: cc.TransitionSlideInB)
        
--------------------------------
--  returns the action that will be performed by the incoming and outgoing scene 
-- @function [parent=#TransitionSlideInB] action 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#TransitionSlideInB] TransitionSlideInB 
-- @param self
-- @return TransitionSlideInB#TransitionSlideInB self (return value: cc.TransitionSlideInB)
        
return nil
