
--------------------------------
-- @module TransitionFadeTR
-- @extend TransitionScene,TransitionEaseScene
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#TransitionFadeTR] easeActionWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
--  Returns the action that will be performed with size.<br>
-- param size A given size.<br>
-- return The action that will be performed.
-- @function [parent=#TransitionFadeTR] actionWithSize 
-- @param self
-- @param #size_table size
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
--  Creates a transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionFadeTR object.
-- @function [parent=#TransitionFadeTR] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionFadeTR#TransitionFadeTR ret (return value: cc.TransitionFadeTR)
        
--------------------------------
-- 
-- @function [parent=#TransitionFadeTR] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return TransitionFadeTR#TransitionFadeTR self (return value: cc.TransitionFadeTR)
        
return nil
