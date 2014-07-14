
--------------------------------
-- @module EventController
-- @extend Event
-- @parent_module cc

--------------------------------
-- @function [parent=#EventController] getControllerEventType 
-- @param self
-- @return EventController::ControllerEventType#EventController::ControllerEventType ret (return value: cc.EventController::ControllerEventType)
        
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
-- overload function: EventController(cc.EventController::ControllerEventType, cc.Controller, bool)
--          
-- overload function: EventController(cc.EventController::ControllerEventType, cc.Controller, int)
--          
-- @function [parent=#EventController] EventController
-- @param self
-- @param #cc.EventController::ControllerEventType controllereventtype
-- @param #cc.Controller controller
-- @param #int int

return nil
