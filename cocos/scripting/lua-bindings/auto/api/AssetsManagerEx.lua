
--------------------------------
-- @module AssetsManagerEx
-- @extend Ref
-- @parent_module cc

--------------------------------
--  @brief Gets the current update state.
-- @function [parent=#AssetsManagerEx] getState 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  @brief  Check out if there is a new version of manifest.<br>
-- You may use this method before updating, then let user determine whether<br>
-- he wants to update resources.
-- @function [parent=#AssetsManagerEx] checkUpdate 
-- @param self
-- @return AssetsManagerEx#AssetsManagerEx self (return value: cc.AssetsManagerEx)
        
--------------------------------
--  @brief Gets storage path.
-- @function [parent=#AssetsManagerEx] getStoragePath 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  @brief Update with the current local manifest.
-- @function [parent=#AssetsManagerEx] update 
-- @param self
-- @return AssetsManagerEx#AssetsManagerEx self (return value: cc.AssetsManagerEx)
        
--------------------------------
--  @brief Function for retrieve the local manifest object
-- @function [parent=#AssetsManagerEx] getLocalManifest 
-- @param self
-- @return Manifest#Manifest ret (return value: cc.Manifest)
        
--------------------------------
--  @brief Function for retrieve the remote manifest object
-- @function [parent=#AssetsManagerEx] getRemoteManifest 
-- @param self
-- @return Manifest#Manifest ret (return value: cc.Manifest)
        
--------------------------------
--  @brief Reupdate all failed assets under the current AssetsManagerEx context
-- @function [parent=#AssetsManagerEx] downloadFailedAssets 
-- @param self
-- @return AssetsManagerEx#AssetsManagerEx self (return value: cc.AssetsManagerEx)
        
--------------------------------
--  @brief Create function for creating a new AssetsManagerEx<br>
-- param manifestUrl   The url for the local manifest file<br>
-- param storagePath   The storage path for downloaded assetes<br>
-- warning   The cached manifest in your storage path have higher priority and will be searched first,<br>
-- only if it doesn't exist, AssetsManagerEx will use the given manifestUrl.
-- @function [parent=#AssetsManagerEx] create 
-- @param self
-- @param #string manifestUrl
-- @param #string storagePath
-- @return AssetsManagerEx#AssetsManagerEx ret (return value: cc.AssetsManagerEx)
        
return nil
