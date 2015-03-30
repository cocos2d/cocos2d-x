
--------------------------------
-- @module EventListener
-- @extend Ref
-- @parent_module cc

--------------------------------
--  Enables or disables the listener.<br>
-- note Only listeners with `enabled` state will be able to receive events.<br>
-- When an listener was initialized, it's enabled by default.<br>
-- An event listener can receive events when it is enabled and is not paused.<br>
-- paused state is always false when it is a fixed priority listener.<br>
-- param enabled True if enables the listener.
-- @function [parent=#EventListener] setEnabled 
-- @param self
-- @param #bool enabled
-- @return EventListener#EventListener self (return value: cc.EventListener)
        
--------------------------------
--  Clones the listener, its subclasses have to override this method.
-- @function [parent=#EventListener] clone 
-- @param self
-- @return EventListener#EventListener ret (return value: cc.EventListener)
        
--------------------------------
--  Checks whether the listener is enabled.<br>
-- return True if the listenrt is enabled.
-- @function [parent=#EventListener] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Checks whether the listener is available.<br>
-- return True if the listener is available.
-- @function [parent=#EventListener] checkAvailable 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
