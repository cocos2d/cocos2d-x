
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
--  Init an action with the specified action and forced target 
-- @function [parent=#TargetedAction] initWithTarget 
-- @param self
-- @param #cc.Node target
-- @param #cc.FiniteTimeAction action
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the target that the action will be forced to run with.<br>
-- param forcedTarget The target that the action will be forced to run with.
-- @function [parent=#TargetedAction] setForcedTarget 
-- @param self
-- @param #cc.Node forcedTarget
-- @return TargetedAction#TargetedAction self (return value: cc.TargetedAction)
        
--------------------------------
--  Create an action with the specified action and forced target.<br>
-- param target The target needs to override.<br>
-- param action The action needs to override.<br>
-- return An autoreleased TargetedAction object.
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
-- @return TargetedAction#TargetedAction self (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] reverse 
-- @param self
-- @return TargetedAction#TargetedAction ret (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] clone 
-- @param self
-- @return TargetedAction#TargetedAction ret (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] stop 
-- @param self
-- @return TargetedAction#TargetedAction self (return value: cc.TargetedAction)
        
--------------------------------
-- param time In seconds.
-- @function [parent=#TargetedAction] update 
-- @param self
-- @param #float time
-- @return TargetedAction#TargetedAction self (return value: cc.TargetedAction)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#TargetedAction] TargetedAction 
-- @param self
-- @return TargetedAction#TargetedAction self (return value: cc.TargetedAction)
        
return nil
