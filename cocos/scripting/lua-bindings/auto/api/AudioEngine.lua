
--------------------------------
-- @module AudioEngine
-- @parent_module ccexp

--------------------------------
-- 
-- @function [parent=#AudioEngine] lazyInit 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Sets the current playback position of an audio instance.<br>
-- param audioID an audioID returned by the play2d function<br>
-- return 
-- @function [parent=#AudioEngine] setCurrentTime 
-- @param self
-- @param #int audioID
-- @param #float time
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Gets the volume value of an audio instance.<br>
-- param audioID an audioID returned by the play2d function<br>
-- return volume value (range from 0.0 to 1.0)
-- @function [parent=#AudioEngine] getVolume 
-- @param self
-- @param #int audioID
-- @return float#float ret (return value: float)
        
--------------------------------
--  Uncache the audio data from internal buffer.<br>
-- AudioEngine cache audio data on ios platform<br>
-- warning This can lead to stop related audio first.<br>
-- param filePath The path of an audio file
-- @function [parent=#AudioEngine] uncache 
-- @param self
-- @param #string filePath
        
--------------------------------
--  Resume all suspended audio instances 
-- @function [parent=#AudioEngine] resumeAll 
-- @param self
        
--------------------------------
--  Stop all audio instances 
-- @function [parent=#AudioEngine] stopAll 
-- @param self
        
--------------------------------
--  Pause an audio instance.<br>
-- param audioID an audioID returned by the play2d function
-- @function [parent=#AudioEngine] pause 
-- @param self
-- @param #int audioID
        
--------------------------------
-- Release related objects<br>
-- warning It must be called before the application exit
-- @function [parent=#AudioEngine] end 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#AudioEngine] getMaxAudioInstance 
-- @param self
-- @return int#int ret (return value: int)
        
--------------------------------
--  Gets the current playback position of an audio instance.<br>
-- param audioID an audioID returned by the play2d function<br>
-- return the current playback position of an audio instance
-- @function [parent=#AudioEngine] getCurrentTime 
-- @param self
-- @param #int audioID
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#AudioEngine] setMaxAudioInstance 
-- @param self
-- @param #int maxInstances
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Checks whether an audio instance is loop.<br>
-- param audioID an audioID returned by the play2d function<br>
-- return Whether or not an audio instance is loop.
-- @function [parent=#AudioEngine] isLoop 
-- @param self
-- @param #int audioID
-- @return bool#bool ret (return value: bool)
        
--------------------------------
--  Pause all playing audio instances 
-- @function [parent=#AudioEngine] pauseAll 
-- @param self
        
--------------------------------
--  Uncache all audio data from internal buffer.<br>
-- warning All audio will be stopped first.<br>
-- param
-- @function [parent=#AudioEngine] uncacheAll 
-- @param self
        
--------------------------------
--  Sets volume for an audio instance.<br>
-- param audioID an audioID returned by the play2d function<br>
-- param volume volume value (range from 0.0 to 1.0)
-- @function [parent=#AudioEngine] setVolume 
-- @param self
-- @param #int audioID
-- @param #float volume
        
--------------------------------
--  Play 2d sound<br>
-- param filePath The path of an audio file<br>
-- param loop Whether audio instance loop or not<br>
-- param volume volume value (range from 0.0 to 1.0)<br>
-- param profile a profile for audio instance<br>
-- return an audio ID. It allows you to dynamically change the behavior of an audio instance on the fly.
-- @function [parent=#AudioEngine] play2d 
-- @param self
-- @param #string filePath
-- @param #bool loop
-- @param #float volume
-- @param #cc.experimental::AudioProfile profile
-- @return int#int ret (return value: int)
        
--------------------------------
--  Returns the state of an audio instance.<br>
-- param audioID an audioID returned by the play2d function<br>
-- return the status of an audio instance
-- @function [parent=#AudioEngine] getState 
-- @param self
-- @param #int audioID
-- @return int#int ret (return value: int)
        
--------------------------------
--  Resume an audio instance.<br>
-- param audioID an audioID returned by the play2d function
-- @function [parent=#AudioEngine] resume 
-- @param self
-- @param #int audioID
        
--------------------------------
--  Stop an audio instance.<br>
-- param audioID an audioID returned by the play2d function
-- @function [parent=#AudioEngine] stop 
-- @param self
-- @param #int audioID
        
--------------------------------
--  Gets the duration of an audio instance.<br>
-- param audioID an audioID returned by the play2d function<br>
-- return the duration of an audio instance
-- @function [parent=#AudioEngine] getDuration 
-- @param self
-- @param #int audioID
-- @return float#float ret (return value: float)
        
--------------------------------
--  Sets whether an audio instance loop or not. <br>
-- param audioID an audioID returned by the play2d function<br>
-- param loop Whether audio instance loop or not
-- @function [parent=#AudioEngine] setLoop 
-- @param self
-- @param #int audioID
-- @param #bool loop
        
--------------------------------
--   Gets the default profile of audio instances<br>
-- return the default profile of audio instances
-- @function [parent=#AudioEngine] getDefaultProfile 
-- @param self
-- @return experimental::AudioProfile#experimental::AudioProfile ret (return value: cc.experimental::AudioProfile)
        
--------------------------------
-- @overload self, string         
-- @overload self, int         
-- @function [parent=#AudioEngine] getProfile
-- @param self
-- @param #int audioID
-- @return experimental::AudioProfile#experimental::AudioProfile ret (retunr value: cc.experimental::AudioProfile)

return nil
