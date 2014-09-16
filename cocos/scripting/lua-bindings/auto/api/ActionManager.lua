
--------------------------------
-- @module ActionManager
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Gets an action given its tag an a target<br>
-- return the Action the with the given tag
-- @function [parent=#ActionManager] getActionByTag 
-- @param self
-- @param #int tag
-- @param #cc.Node target
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
--  Removes an action given its tag and the target 
-- @function [parent=#ActionManager] removeActionByTag 
-- @param self
-- @param #int tag
-- @param #cc.Node target
        
--------------------------------
--  Removes all actions from all the targets.
-- @function [parent=#ActionManager] removeAllActions 
-- @param self
        
--------------------------------
--  Adds an action with a target. <br>
-- If the target is already present, then the action will be added to the existing target.<br>
-- If the target is not present, a new instance of this target will be created either paused or not, and the action will be added to the newly created target.<br>
-- When the target is paused, the queued actions won't be 'ticked'.
-- @function [parent=#ActionManager] addAction 
-- @param self
-- @param #cc.Action action
-- @param #cc.Node target
-- @param #bool paused
        
--------------------------------
--  Resumes the target. All queued actions will be resumed.
-- @function [parent=#ActionManager] resumeTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- 
-- @function [parent=#ActionManager] update 
-- @param self
-- @param #float dt
        
--------------------------------
--  Pauses the target: all running actions and newly added actions will be paused.
-- @function [parent=#ActionManager] pauseTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
--  Returns the numbers of actions that are running in a certain target. <br>
-- Composable actions are counted as 1 action. Example:<br>
-- - If you are running 1 Sequence of 7 actions, it will return 1.<br>
-- - If you are running 7 Sequences of 2 actions, it will return 7.
-- @function [parent=#ActionManager] getNumberOfRunningActionsInTarget 
-- @param self
-- @param #cc.Node target
-- @return long#long ret (return value: long)
        
--------------------------------
--  Removes all actions from a certain target.<br>
-- All the actions that belongs to the target will be removed.
-- @function [parent=#ActionManager] removeAllActionsFromTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
--  Resume a set of targets (convenience function to reverse a pauseAllRunningActions call)
-- @function [parent=#ActionManager] resumeTargets 
-- @param self
-- @param #array_table targetsToResume
        
--------------------------------
--  Removes an action given an action reference.
-- @function [parent=#ActionManager] removeAction 
-- @param self
-- @param #cc.Action action
        
--------------------------------
--  Removes all actions given its tag and the target 
-- @function [parent=#ActionManager] removeAllActionsByTag 
-- @param self
-- @param #int tag
-- @param #cc.Node target
        
--------------------------------
--  Pauses all running actions, returning a list of targets whose actions were paused.
-- @function [parent=#ActionManager] pauseAllRunningActions 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- js ctor
-- @function [parent=#ActionManager] ActionManager 
-- @param self
        
return nil
