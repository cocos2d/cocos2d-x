
--------------------------------
-- @module Console
-- @extend Ref
-- @parent_module cc

--------------------------------
--  starts listening to specifed TCP port 
-- @function [parent=#Console] listenOnTCP 
-- @param self
-- @param #int port
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  log something in the console 
-- @function [parent=#Console] log 
-- @param self
-- @param #char buf
        
--------------------------------
-- set bind address<br>
-- address : 127.0.0.1
-- @function [parent=#Console] setBindAddress 
-- @param self
-- @param #string address
        
--------------------------------
--  stops the Console. 'stop' will be called at destruction time as well 
-- @function [parent=#Console] stop 
-- @param self
        
--------------------------------
--  starts listening to specifed file descriptor 
-- @function [parent=#Console] listenOnFileDescriptor 
-- @param self
-- @param #int fd
-- @return bool#bool ret (return value: bool)
        
return nil
