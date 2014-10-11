
--------------------------------
-- @module Console
-- @extend Ref
-- @parent_module cc

--------------------------------
--  stops the Console. 'stop' will be called at destruction time as well 
-- @function [parent=#Console] stop 
-- @param self
        
--------------------------------
--  starts listening to specifed TCP port 
-- @function [parent=#Console] listenOnTCP 
-- @param self
-- @param #int port
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  starts listening to specifed file descriptor 
-- @function [parent=#Console] listenOnFileDescriptor 
-- @param self
-- @param #int fd
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  log something in the console 
-- @function [parent=#Console] log 
-- @param self
-- @param #char buf
        
return nil
