
--------------------------------
-- @module TransitionSlideInL
-- @extend TransitionScene,TransitionEaseScene
-- @parent_module cc

--------------------------------
--  Returns the action that will be performed by the incoming and outgoing scene.<br>
-- return The action that will be performed by the incoming and outgoing scene.
-- @function [parent=#TransitionSlideInL] action 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#TransitionSlideInL] easeActionWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
--  Creates a transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionSlideInL object.
-- @function [parent=#TransitionSlideInL] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionSlideInL#TransitionSlideInL ret (return value: cc.TransitionSlideInL)
        
return nil
