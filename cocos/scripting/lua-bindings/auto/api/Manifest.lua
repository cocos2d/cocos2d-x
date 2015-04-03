
--------------------------------
-- @module Manifest
-- @extend Ref
-- @parent_module cc

--------------------------------
--  @brief Gets remote manifest file url.
-- @function [parent=#Manifest] getManifestFileUrl 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  @brief Check whether the version informations have been fully loaded
-- @function [parent=#Manifest] isVersionLoaded 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  @brief Check whether the manifest have been fully loaded
-- @function [parent=#Manifest] isLoaded 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  @brief Gets remote package url.
-- @function [parent=#Manifest] getPackageUrl 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  @brief Gets manifest version.
-- @function [parent=#Manifest] getVersion 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  @brief Gets remote version file url.
-- @function [parent=#Manifest] getVersionFileUrl 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
--  @brief Get the search paths list related to the Manifest.
-- @function [parent=#Manifest] getSearchPaths 
-- @param self
-- @return array_table#array_table ret (return value: array_table)
        
return nil
