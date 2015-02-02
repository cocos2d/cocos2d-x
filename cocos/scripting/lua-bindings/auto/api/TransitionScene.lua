
--------------------------------
-- @module TransitionScene
-- @extend Scene
-- @parent_module cc

--------------------------------
--  called after the transition finishes 
-- @function [parent=#TransitionScene] finish 
-- @param self
-- @return TransitionScene#TransitionScene self (return value: cc.TransitionScene)
        
--------------------------------
--  used by some transitions to hide the outer scene 
-- @function [parent=#TransitionScene] hideOutShowIn 
-- @param self
-- @return TransitionScene#TransitionScene self (return value: cc.TransitionScene)
        
--------------------------------
--  creates a base transition with duration and incoming scene 
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
