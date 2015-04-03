
--------------------------------
-- @module VideoPlayer
-- @extend Widget
-- @parent_module ccexp

--------------------------------
-- brief Get the local video filie name.<br>
-- return The video file name.
-- @function [parent=#VideoPlayer] getFileName 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- brief Get the URL of remoting video source.<br>
-- return A remoting URL address.
-- @function [parent=#VideoPlayer] getURL 
-- @param self
-- @return string#string ret (return value: string)
        
--------------------------------
-- Starts playback.
-- @function [parent=#VideoPlayer] play 
-- @param self
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Pauses playback.
-- @function [parent=#VideoPlayer] pause 
-- @param self
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Causes the video player to keep aspect ratio or no when displaying the video.<br>
-- param enable    Specify true to keep aspect ratio or false to scale the video until <br>
-- both dimensions fit the visible bounds of the view exactly.
-- @function [parent=#VideoPlayer] setKeepAspectRatioEnabled 
-- @param self
-- @param #bool enable
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Resumes playback.
-- @function [parent=#VideoPlayer] resume 
-- @param self
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Stops playback.
-- @function [parent=#VideoPlayer] stop 
-- @param self
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Causes the video player to enter or exit full-screen mode.<br>
-- param fullscreen    Specify true to enter full-screen mode or false to exit full-screen mode.
-- @function [parent=#VideoPlayer] setFullScreenEnabled 
-- @param self
-- @param #bool fullscreen
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Sets a file path as a video source for VideoPlayer.
-- @function [parent=#VideoPlayer] setFileName 
-- @param self
-- @param #string videoPath
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Sets a URL as a video source for VideoPlayer.
-- @function [parent=#VideoPlayer] setURL 
-- @param self
-- @param #string _videoURL
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Indicates whether the video player keep aspect ratio when displaying the video.
-- @function [parent=#VideoPlayer] isKeepAspectRatioEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- brief A function which will be called when video is playing.<br>
-- param event @see VideoPlayer::EventType.
-- @function [parent=#VideoPlayer] onPlayEvent 
-- @param self
-- @param #int event
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- Indicates whether the video player is in full-screen mode.<br>
-- return True if the video player is in full-screen mode, false otherwise.
-- @function [parent=#VideoPlayer] isFullScreenEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Checks whether the VideoPlayer is playing.<br>
-- return True if currently playing, false otherwise.
-- @function [parent=#VideoPlayer] isPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Seeks to specified time position.<br>
-- param sec   The offset in seconds from the start to seek to.
-- @function [parent=#VideoPlayer] seekTo 
-- @param self
-- @param #float sec
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
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
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
--------------------------------
-- 
-- @function [parent=#VideoPlayer] setVisible 
-- @param self
-- @param #bool visible
-- @return experimental::ui::VideoPlayer#experimental::ui::VideoPlayer self (return value: cc.experimental::ui::VideoPlayer)
        
return nil
