
--------------------------------
-- @module TransitionSlideInT
-- @extend TransitionSlideInL
-- @parent_module cc

--------------------------------
--  Creates a transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionSlideInT object.
-- @function [parent=#TransitionSlideInT] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionSlideInT#TransitionSlideInT ret (return value: cc.TransitionSlideInT)
        
--------------------------------
--  returns the action that will be performed by the incoming and outgoing scene 
-- @function [parent=#TransitionSlideInT] action 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
return nil
