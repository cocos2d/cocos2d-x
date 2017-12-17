
--------------------------------
-- @module AssetsManager
-- @extend Node
-- @parent_module cc

--------------------------------
-- 
-- @function [parent=#AssetsManager] setStoragePath 
-- @param self
-- @param #char storagePath
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] setPackageUrl 
-- @param self
-- @param #char packageUrl
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] checkUpdate 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] getStoragePath 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] update 
-- @param self
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
--------------------------------
--  @brief Sets connection time out in seconds
-- @function [parent=#AssetsManager] setConnectionTimeout 
-- @param self
-- @param #unsigned int timeout
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] setVersionFileUrl 
-- @param self
-- @param #char versionFileUrl
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] getPackageUrl 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
--  @brief Gets connection time out in seconds
-- @function [parent=#AssetsManager] getConnectionTimeout 
-- @param self
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] getVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] getVersionFileUrl 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] deleteVersion 
-- @param self
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] create 
-- @param self
-- @param #char packageUrl
-- @param #char versionFileUrl
-- @param #char storagePath
-- @param #function errorCallback
-- @param #function progressCallback
-- @param #function successCallback
-- @return AssetsManager#AssetsManager ret (return value: cc.AssetsManager)
        
--------------------------------
-- 
-- @function [parent=#AssetsManager] AssetsManager 
-- @param self
-- @return AssetsManager#AssetsManager self (return value: cc.AssetsManager)
        
return nil
