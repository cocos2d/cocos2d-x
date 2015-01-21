
--------------------------------
-- @module Action
-- @extend Ref
-- @parent_module cc

--------------------------------
--  called before the action start. It will also set the target.
-- @function [parent=#Action] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Set the original target, since target can be nil.<br>
-- Is the target that were used to run the action. Unless you are doing something complex, like ActionManager, you should NOT call this method.<br>
-- The target is 'assigned', it is not 'retained'.<br>
-- since v0.8.2
-- @function [parent=#Action] setOriginalTarget 
-- @param self
-- @param #cc.Node originalTarget
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  returns a clone of action 
-- @function [parent=#Action] clone 
-- @param self
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
-- 
-- @function [parent=#Action] getOriginalTarget 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- called after the action has finished. It will set the 'target' to nil.<br>
-- IMPORTANT: You should never call "[action stop]" manually. Instead, use: "target->stopAction(action);"
-- @function [parent=#Action] stop 
-- @param self
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
-- called once per frame. time a value between 0 and 1<br>
-- For example: <br>
-- - 0 means that the action just started<br>
-- - 0.5 means that the action is in the middle<br>
-- - 1 means that the action is over
-- @function [parent=#Action] update 
-- @param self
-- @param #float time
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
-- 
-- @function [parent=#Action] getTarget 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  called every frame with it's delta time, dt in seconds. DON'T override unless you know what you are doing.
-- @function [parent=#Action] step 
-- @param self
-- @param #float dt
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
-- 
-- @function [parent=#Action] setTag 
-- @param self
-- @param #int tag
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
-- 
-- @function [parent=#Action] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  The action will modify the target properties. 
-- @function [parent=#Action] setTarget 
-- @param self
-- @param #cc.Node target
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  return true if the action has finished
-- @function [parent=#Action] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  returns a new action that performs the exactly the reverse action 
-- @function [parent=#Action] reverse 
-- @param self
-- @return Action#Action ret (return value: cc.Action)
        
return nil
