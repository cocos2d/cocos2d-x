
--------------------------------
-- @module TransitionScene
-- @extend Scene
-- @parent_module cc

--------------------------------
--  called after the transition finishes 
-- @function [parent=#TransitionScene] finish 
-- @param self
        
--------------------------------
--  used by some transitions to hide the outer scene 
-- @function [parent=#TransitionScene] hideOutShowIn 
-- @param self
        
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
        
--------------------------------
-- 
-- @function [parent=#TransitionScene] cleanup 
-- @param self
        
return nil
