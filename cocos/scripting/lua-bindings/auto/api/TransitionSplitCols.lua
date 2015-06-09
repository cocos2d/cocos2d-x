
--------------------------------
-- @module TransitionSplitCols
-- @extend TransitionScene,TransitionEaseScene
-- @parent_module cc

--------------------------------
--  Returns the action that will be performed.<br>
-- return The action that will be performed.
-- @function [parent=#TransitionSplitCols] action 
-- @param self
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
-- 
-- @function [parent=#TransitionSplitCols] easeActionWithAction 
-- @param self
-- @param #cc.ActionInterval action
-- @return ActionInterval#ActionInterval ret (return value: cc.ActionInterval)
        
--------------------------------
--  Creates a transition with duration and incoming scene.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- return A autoreleased TransitionSplitCols object.
-- @function [parent=#TransitionSplitCols] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @return TransitionSplitCols#TransitionSplitCols ret (return value: cc.TransitionSplitCols)
        
--------------------------------
-- 
-- @function [parent=#TransitionSplitCols] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
-- @return TransitionSplitCols#TransitionSplitCols self (return value: cc.TransitionSplitCols)
        
--------------------------------
-- 
-- @function [parent=#TransitionSplitCols] TransitionSplitCols 
-- @param self
-- @return TransitionSplitCols#TransitionSplitCols self (return value: cc.TransitionSplitCols)
        
return nil
