
--------------------------------
-- @module EventController
-- @extend Event
-- @parent_module cc

--------------------------------
-- @function [parent=#EventController] getControllerEventType 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @function [parent=#EventController] setConnectStatus 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#EventController] isConnected 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#EventController] setKeyCode 
-- @param self
-- @param #int int
        
--------------------------------
-- @function [parent=#EventController] getController 
-- @param self
-- @return Controller#Controller ret (return value: cc.Controller)
        
--------------------------------
-- @function [parent=#EventController] getKeyCode 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- @overload self, int, cc.Controller, bool         
-- @overload self, int, cc.Controller, int         
-- @function [parent=#EventController] EventController
-- @param self
-- @param #int controllereventtype
-- @param #cc.Controller controller
-- @param #int int

return nil
