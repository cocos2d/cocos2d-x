
--------------------------------
-- @module VideoPlayer
-- @extend Widget
-- @parent_module ccexp

--------------------------------
-- 
-- @function [parent=#VideoPlayer] getFileName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] getURL 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] play 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] pause 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] setKeepAspectRatioEnabled 
-- @param self
-- @param #bool enable
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] resume 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] stop 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] setFullScreenEnabled 
-- @param self
-- @param #bool enabled
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] setFileName 
-- @param self
-- @param #string videoPath
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] setURL 
-- @param self
-- @param #string _videoURL
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] isKeepAspectRatioEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] onPlayEvent 
-- @param self
-- @param #int event
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] isFullScreenEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] isPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] seekTo 
-- @param self
-- @param #float sec
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] create 
-- @param self
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer ret (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] draw 
-- @param self
-- @param #cc.Renderer renderer
-- @param #mat4_table transform
-- @param #unsigned int flags
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] setVisible 
-- @param self
-- @param #bool visible
        
return nil
