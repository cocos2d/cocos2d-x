
--------------------------------
-- @module Event
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Checks whether the event has been stopped.<br>
-- return True if the event has been stopped.
-- @function [parent=#Event] isStopped 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the event type.<br>
-- return The event type.
-- @function [parent=#Event] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Gets current target of the event.<br>
-- return The target with which the event associates.<br>
-- note It onlys be available when the event listener is associated with node.<br>
-- It returns 0 when the listener is associated with fixed priority.
-- @function [parent=#Event] getCurrentTarget 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  Stops propagation for current event.
-- @function [parent=#Event] stopPropagation 
-- @param self
-- @return Event#Event self (return value: cc.Event)
        
return nil
