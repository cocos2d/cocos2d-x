
--------------------------------
-- @module TargetedAction
-- @extend ActionInterval
-- @parent_module cc

--------------------------------
-- @overload self         
-- @overload self         
-- @function [parent=#TargetedAction] getForcedTarget
-- @param self
-- @return Node#Node ret (return value: cc.Node)

--------------------------------
--  Sets the target that the action will be forced to run with 
-- @function [parent=#TargetedAction] setForcedTarget 
-- @param self
-- @param #cc.Node forcedTarget
        
--------------------------------
--  Create an action with the specified action and forced target 
-- @function [parent=#TargetedAction] create 
-- @param self
-- @param #cc.Node target
-- @param #cc.FiniteTimeAction action
-- @return TargetedAction#TargetedAction ret (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] startWithTarget 
-- @param self
-- @param #cc.Node target
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] clone 
-- @param self
-- @return TargetedAction#TargetedAction ret (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] reverse 
-- @param self
-- @return TargetedAction#TargetedAction ret (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] update 
-- @param self
-- @param #float time
        
return nil
