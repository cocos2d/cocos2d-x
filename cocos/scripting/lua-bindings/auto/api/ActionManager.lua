
--------------------------------
-- @module ActionManager
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Gets an action given its tag an a target.<br>
-- param tag       The action's tag.<br>
-- param target    A certain target.<br>
-- return  The Action the with the given tag.
-- @function [parent=#ActionManager] getActionByTag 
-- @param self
-- @param #int tag
-- @param #cc.Node target
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
--  Removes an action given its tag and the target.<br>
-- param tag       The action's tag.<br>
-- param target    A certain target.
-- @function [parent=#ActionManager] removeActionByTag 
-- @param self
-- @param #int tag
-- @param #cc.Node target
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Removes all actions matching at least one bit in flags and the target.<br>
-- param flags     The flag field to match the actions' flags based on bitwise AND.<br>
-- param target    A certain target.<br>
-- js NA
-- @function [parent=#ActionManager] removeActionsByFlags 
-- @param self
-- @param #unsigned int flags
-- @param #cc.Node target
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Removes all actions from all the targets.
-- @function [parent=#ActionManager] removeAllActions 
-- @param self
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Adds an action with a target. <br>
-- If the target is already present, then the action will be added to the existing target.<br>
-- If the target is not present, a new instance of this target will be created either paused or not, and the action will be added to the newly created target.<br>
-- When the target is paused, the queued actions won't be 'ticked'.<br>
-- param action    A certain action.<br>
-- param target    The target which need to be added an action.<br>
-- param paused    Is the target paused or not.
-- @function [parent=#ActionManager] addAction 
-- @param self
-- @param #cc.Action action
-- @param #cc.Node target
-- @param #bool paused
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Resumes the target. All queued actions will be resumed.<br>
-- param target    A certain target.
-- @function [parent=#ActionManager] resumeTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Main loop of ActionManager.<br>
-- param dt    In seconds.
-- @function [parent=#ActionManager] update 
-- @param self
-- @param #float dt
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Pauses the target: all running actions and newly added actions will be paused.<br>
-- param target    A certain target.
-- @function [parent=#ActionManager] pauseTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Returns the numbers of actions that are running in a certain target. <br>
-- Composable actions are counted as 1 action. Example:<br>
-- - If you are running 1 Sequence of 7 actions, it will return 1.<br>
-- - If you are running 7 Sequences of 2 actions, it will return 7.<br>
-- param target    A certain target.<br>
-- return  The numbers of actions that are running in a certain target.<br>
-- js NA
-- @function [parent=#ActionManager] getNumberOfRunningActionsInTarget 
-- @param self
-- @param #cc.Node target
-- @return long#long ret (return value: long)
        
--------------------------------
--  Removes all actions from a certain target.<br>
-- All the actions that belongs to the target will be removed.<br>
-- param target    A certain target.
-- @function [parent=#ActionManager] removeAllActionsFromTarget 
-- @param self
-- @param #cc.Node target
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Resume a set of targets (convenience function to reverse a pauseAllRunningActions call).<br>
-- param targetsToResume   A set of targets need to be resumed.
-- @function [parent=#ActionManager] resumeTargets 
-- @param self
-- @param #array_table targetsToResume
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Removes an action given an action reference.<br>
-- param action    A certain target.
-- @function [parent=#ActionManager] removeAction 
-- @param self
-- @param #cc.Action action
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Removes all actions given its tag and the target.<br>
-- param tag       The actions' tag.<br>
-- param target    A certain target.<br>
-- js NA
-- @function [parent=#ActionManager] removeAllActionsByTag 
-- @param self
-- @param #int tag
-- @param #cc.Node target
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
--------------------------------
--  Pauses all running actions, returning a list of targets whose actions were paused.<br>
-- return  A list of targets whose actions were paused.
-- @function [parent=#ActionManager] pauseAllRunningActions 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- js ctor
-- @function [parent=#ActionManager] ActionManager 
-- @param self
-- @return ActionManager#ActionManager self (return value: cc.ActionManager)
        
return nil
