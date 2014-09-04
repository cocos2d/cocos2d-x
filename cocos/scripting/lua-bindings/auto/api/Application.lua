
--------------------------------
-- @module Application
-- @parent_module cc

--------------------------------
-- brief Get target platform
-- @function [parent=#Application] getTargetPlatform 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief Get current language iso 639-1 code<br>
-- return Current language iso 639-1 code
-- @function [parent=#Application] getCurrentLanguageCode 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- brief Get current language config<br>
-- return Current language config
-- @function [parent=#Application] getCurrentLanguage 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
-- brief    Callback by Director to limit FPS.<br>
-- param interval The time, expressed in seconds, between current frame and next.
-- @function [parent=#Application] setAnimationInterval 
-- @param self
-- @param #double interval
        
--------------------------------
-- brief    Get current application instance.<br>
-- return Current application instance pointer.
-- @function [parent=#Application] getInstance 
-- @param self
-- @return Application#Application ret (return value: cc.Application)
        
return nil
