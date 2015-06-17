
--------------------------------
-- @module TransitionSceneOriented
-- @extend TransitionScene
-- @parent_module cc

--------------------------------
--  initializes a transition with duration and incoming scene 
-- @function [parent=#TransitionSceneOriented] initWithDuration 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @param #int orientation
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Creates a transition with duration, incoming scene and orientation.<br>
-- param t Duration time, in seconds.<br>
-- param scene A given scene.<br>
-- param orientation A given orientation: LeftOver, RightOver, UpOver, DownOver.<br>
-- return A autoreleased TransitionSceneOriented object.
-- @function [parent=#TransitionSceneOriented] create 
-- @param self
-- @param #float t
-- @param #cc.Scene scene
-- @param #int orientation
-- @return TransitionSceneOriented#TransitionSceneOriented ret (return value: cc.TransitionSceneOriented)
        
--------------------------------
-- 
-- @function [parent=#TransitionSceneOriented] TransitionSceneOriented 
-- @param self
-- @return TransitionSceneOriented#TransitionSceneOriented self (return value: cc.TransitionSceneOriented)
        
return nil
