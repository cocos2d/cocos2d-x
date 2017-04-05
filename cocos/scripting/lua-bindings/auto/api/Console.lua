
--------------------------------
-- @module Console
-- @extend Ref
-- @parent_module cc

--------------------------------
-- @overload self, cc.Console::Command, cc.Console::Command         
-- @overload self, string, cc.Console::Command         
-- @function [parent=#Console] addSubCommand
-- @param self
-- @param #string cmdName
-- @param #cc.Console::Command subCmd
-- @return Console#Console self (return value: cc.Console)

--------------------------------
--  starts listening to specified TCP port 
-- @function [parent=#Console] listenOnTCP 
-- @param self
-- @param #int port
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  log something in the console 
-- @function [parent=#Console] log 
-- @param self
-- @param #char buf
-- @return Console#Console self (return value: cc.Console)
        
--------------------------------
-- @overload self, cc.Console::Command, string         
-- @overload self, string, string         
-- @function [parent=#Console] getSubCommand
-- @param self
-- @param #string cmdName
-- @param #string subCmdName
-- @return Console::Command#Console::Command ret (return value: cc.Console::Command)

--------------------------------
--  delete custom command 
-- @function [parent=#Console] delCommand 
-- @param self
-- @param #string cmdName
-- @return Console#Console self (return value: cc.Console)
        
--------------------------------
--  stops the Console. 'stop' will be called at destruction time as well 
-- @function [parent=#Console] stop 
-- @param self
-- @return Console#Console self (return value: cc.Console)
        
--------------------------------
--  get custom command 
-- @function [parent=#Console] getCommand 
-- @param self
-- @param #string cmdName
-- @return Console::Command#Console::Command ret (return value: cc.Console::Command)
        
--------------------------------
--  starts listening to specified file descriptor 
-- @function [parent=#Console] listenOnFileDescriptor 
-- @param self
-- @param #int fd
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- set bind address<br>
-- address : 127.0.0.1
-- @function [parent=#Console] setBindAddress 
-- @param self
-- @param #string address
-- @return Console#Console self (return value: cc.Console)
        
--------------------------------
-- @overload self, cc.Console::Command, string         
-- @overload self, string, string         
-- @function [parent=#Console] delSubCommand
-- @param self
-- @param #string cmdName
-- @param #string subCmdName
-- @return Console#Console self (return value: cc.Console)

--------------------------------
--  Checks whether the server for console is bound with ipv6 address 
-- @function [parent=#Console] isIpv6Server 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
