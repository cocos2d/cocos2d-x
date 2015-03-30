
--------------------------------
-- @module TransitionScene
-- @extend Scene
-- @parent_module cc

--------------------------------
--  Called after the transition finishes.
-- @function [parent=#TransitionScene] finish 
-- @param self
-- @return TransitionScene#TransitionScene self (return value: cc.TransitionScene)
        
--------------------------------
--  Used by some transitions to hide the outer scene.
-- @function [parent=#TransitionScene] hideOutShowIn 
-- @param self
-- @return TransitionScene#TransitionScene self (return value: cc.TransitionScene)
        
--------------------------------
--  Creates a base transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionScene object.
-- @function [parent=#TransitionScene] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionScene#TransitionScene ret (return value: cc.TransitionScene)
        
--------------------------------
-- 
-- @function [parent=#TransitionScene] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return TransitionScene#TransitionScene self (return value: cc.TransitionScene)
        
--------------------------------
-- 
-- @function [parent=#TransitionScene] cleanup 
-- @param self
-- @return TransitionScene#TransitionScene self (return value: cc.TransitionScene)
        
return nil
