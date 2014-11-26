
--------------------------------
-- @module Event
-- @extend Ref
-- @parent_module cc

--------------------------------
--  @brief Gets current target of the event<br>
-- return The target with which the event associates.<br>
-- note It onlys be available when the event listener is associated with node. <br>
-- It returns 0 when the listener is associated with fixed priority.
-- @function [parent=#Event] getCurrentTarget 
-- @param self
-- @return Node#Node ret (return value: cc.Node)
        
--------------------------------
--  Gets the event type 
-- @function [parent=#Event] getType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- 
-- @function [parent=#Event] getResult 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Checks whether the event has been stopped 
-- @function [parent=#Event] isStopped 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#Event] setResult 
-- @param self
-- @param #string result
        
--------------------------------
--  Stops propagation for current event 
-- @function [parent=#Event] stopPropagation 
-- @param self
        
return nil
