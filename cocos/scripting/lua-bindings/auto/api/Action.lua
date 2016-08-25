
--------------------------------
-- @module Action
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Called before the action start. It will also set the target. <br>
-- param target A certain target.
-- @function [parent=#Action] startWithTarget 
-- @param self
-- @param #cc.Node target
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
-- Set the original target, since target can be nil.<br>
-- Is the target that were used to run the action. Unless you are doing something complex, like ActionManager, you should NOT call this method.<br>
-- The target is 'assigned', it is not 'retained'.<br>
-- since v0.8.2<br>
-- param originalTarget Is 'assigned', it is not 'retained'.
-- @function [parent=#Action] setOriginalTarget 
-- @param self
-- @param #cc.Node originalTarget
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Returns a clone of action.<br>
-- return A clone action.
-- @function [parent=#Action] clone 
-- @param self
-- @return Action#Action ret (return value: cc.Action)
        
--------------------------------
--  Return a original Target. <br>
-- return A original Target.
-- @function [parent=#Action] getOriginalTarget 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
-- Called after the action has finished. It will set the 'target' to nil.<br>
-- IMPORTANT: You should never call "Action::stop()" manually. Instead, use: "target->stopAction(action);".
-- @function [parent=#Action] stop 
-- @param self
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
-- Called once per frame. time a value between 0 and 1.<br>
-- For example:<br>
-- - 0 Means that the action just started.<br>
-- - 0.5 Means that the action is in the middle.<br>
-- - 1 Means that the action is over.<br>
-- param time A value between 0 and 1.
-- @function [parent=#Action] update 
-- @param self
-- @param #float time
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Return certain target.<br>
-- return A certain target.
-- @function [parent=#Action] getTarget 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  Returns a flag field that is used to group the actions easily.<br>
-- return A tag.
-- @function [parent=#Action] getFlags 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
--  Called every frame with it's delta time, dt in seconds. DON'T override unless you know what you are doing. <br>
-- param dt In seconds.
-- @function [parent=#Action] step 
-- @param self
-- @param #float dt
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Changes the tag that is used to identify the action easily. <br>
-- param tag Used to identify the action easily.
-- @function [parent=#Action] setTag 
-- @param self
-- @param #int tag
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Changes the flag field that is used to group the actions easily.<br>
-- param flags Used to group the actions easily.
-- @function [parent=#Action] setFlags 
-- @param self
-- @param #unsigned int flags
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Returns a tag that is used to identify the action easily. <br>
-- return A tag.
-- @function [parent=#Action] getTag 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  The action will modify the target properties. <br>
-- param target A certain target.
-- @function [parent=#Action] setTarget 
-- @param self
-- @param #cc.Node target
-- @return Action#Action self (return value: cc.Action)
        
--------------------------------
--  Return true if the action has finished. <br>
-- return Is true if the action has finished.
-- @function [parent=#Action] isDone 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Returns a new action that performs the exact reverse of the action. <br>
-- return A new action that performs the exact reverse of the action.<br>
-- js NA
-- @function [parent=#Action] reverse 
-- @param self
-- @return Action#Action ret (return value: cc.Action)
        
return nil
