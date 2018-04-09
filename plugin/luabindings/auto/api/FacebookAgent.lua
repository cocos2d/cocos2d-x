
--------------------------------
-- @module FacebookAgent
-- @parent_module plugin

--------------------------------
-- brief Notifies the events system that the app has launched & logs an activatedApp event. 
-- @function [parent=#FacebookAgent] activateApp 
-- @param self
        
--------------------------------
-- brief get permissoin list
-- @function [parent=#FacebookAgent] getPermissionList 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief get UserID
-- @function [parent=#FacebookAgent] getUserID 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief log out
-- @function [parent=#FacebookAgent] logout 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#FacebookAgent] getSDKVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief Check whether the user logined or not
-- @function [parent=#FacebookAgent] isLoggedIn 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief get AccessToken
-- @function [parent=#FacebookAgent] getAccessToken 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  Destroy singleton of FacebookAgent 
-- @function [parent=#FacebookAgent] destroyInstance 
-- @param self
        
return nil
