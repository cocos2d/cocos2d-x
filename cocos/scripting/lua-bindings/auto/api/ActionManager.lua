
--------------------------------
-- @module ActionManager
-- @extend Ref

--------------------------------
-- @function [parent=#ActionManager] getActionByTag 
-- @param self
-- @param #int int
-- @param #cc.Node node
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- @function [parent=#ActionManager] removeActionByTag 
-- @param self
-- @param #int int
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ActionManager] removeAllActions 
-- @param self
        
--------------------------------
-- @function [parent=#ActionManager] addAction 
-- @param self
-- @param #cc.Action action
-- @param #cc.Node node
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ActionManager] resumeTarget 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ActionManager] update 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ActionManager] getNumberOfRunningActionsInTarget 
-- @param self
-- @param #cc.Node node
-- @return long#long ret (return value: long)
        
--------------------------------
-- @function [parent=#ActionManager] removeAllActionsFromTarget 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ActionManager] resumeTargets 
-- @param self
-- @param #array_table array
        
--------------------------------
-- @function [parent=#ActionManager] removeAction 
-- @param self
-- @param #cc.Action action
        
--------------------------------
-- @function [parent=#ActionManager] pauseTarget 
-- @param self
-- @param #cc.Node node
        
--------------------------------
-- @function [parent=#ActionManager] pauseAllRunningActions 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
--------------------------------
-- @function [parent=#ActionManager] ActionManager 
-- @param self
        
return nil
