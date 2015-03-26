
--------------------------------
-- @module SimpleAudioEngine
-- @parent_module cc

--------------------------------
-- Preload background music.<br>
-- param filePath The path of the background music file.<br>
-- js NA<br>
-- lua preloadMusic
-- @function [parent=#SimpleAudioEngine] preloadBackgroundMusic 
-- @param self
-- @param #char filePath
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Stop playing background music.<br>
-- param releaseData If release the background music data or not.As default value is false.<br>
-- js stopMusic<br>
-- lua stopMusic
-- @function [parent=#SimpleAudioEngine] stopBackgroundMusic 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Stop all playing sound effects.
-- @function [parent=#SimpleAudioEngine] stopAllEffects 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- The volume of the background music within the range of 0.0 as the minimum and 1.0 as the maximum.<br>
-- js getMusicVolume<br>
-- lua getMusicVolume
-- @function [parent=#SimpleAudioEngine] getBackgroundMusicVolume 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Resume playing background music.<br>
-- js resumeMusic<br>
-- lua resumeMusic
-- @function [parent=#SimpleAudioEngine] resumeBackgroundMusic 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Set the volume of background music.<br>
-- param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.<br>
-- js setMusicVolume<br>
-- lua setMusicVolume
-- @function [parent=#SimpleAudioEngine] setBackgroundMusicVolume 
-- @param self
-- @param #float volume
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Preload a compressed audio file.<br>
-- The compressed audio will be decoded to wave, then written into an internal buffer in SimpleAudioEngine.<br>
-- param filePath The path of the effect file.<br>
-- js NA
-- @function [parent=#SimpleAudioEngine] preloadEffect 
-- @param self
-- @param #char filePath
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Indicates whether the background music is playing.<br>
-- return <i>true</i> if the background music is playing, otherwise <i>false</i>.<br>
-- js isMusicPlaying<br>
-- lua isMusicPlaying
-- @function [parent=#SimpleAudioEngine] isBackgroundMusicPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- The volume of the effects within the range of 0.0 as the minimum and 1.0 as the maximum.
-- @function [parent=#SimpleAudioEngine] getEffectsVolume 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- Indicates whether any background music can be played or not.<br>
-- return <i>true</i> if background music can be played, otherwise <i>false</i>.<br>
-- js willPlayMusic<br>
-- lua willPlayMusic
-- @function [parent=#SimpleAudioEngine] willPlayBackgroundMusic 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- Pause playing sound effect.<br>
-- param soundId The return value of function playEffect.
-- @function [parent=#SimpleAudioEngine] pauseEffect 
-- @param self
-- @param #unsigned int soundId
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Play sound effect with a file path, pitch, pan and gain.<br>
-- param filePath The path of the effect file.<br>
-- param loop Determines whether to loop the effect playing or not. The default value is false.<br>
-- param pitch Frequency, normal value is 1.0. Will also change effect play time.<br>
-- param pan   Stereo effect, in the range of [-1..1] where -1 enables only left channel.<br>
-- param gain  Volume, in the range of [0..1]. The normal value is 1.<br>
-- return The sound id.<br>
-- note Full support is under development, now there are limitations:<br>
-- - no pitch effect on Samsung Galaxy S2 with OpenSL backend enabled;<br>
-- - no pitch/pan/gain on win32.
-- @function [parent=#SimpleAudioEngine] playEffect 
-- @param self
-- @param #char filePath
-- @param #bool loop
-- @param #float pitch
-- @param #float pan
-- @param #float gain
-- @return unsigned int#unsigned int ret (return value: unsigned int)
        
--------------------------------
-- Rewind playing background music.<br>
-- js rewindMusic<br>
-- lua rewindMusic
-- @function [parent=#SimpleAudioEngine] rewindBackgroundMusic 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Play background music.<br>
-- param filePath The path of the background music file,or the FileName of T_SoundResInfo.<br>
-- param loop Whether the background music loop or not.<br>
-- js playMusic<br>
-- lua playMusic
-- @function [parent=#SimpleAudioEngine] playBackgroundMusic 
-- @param self
-- @param #char filePath
-- @param #bool loop
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Resume all playing sound effect.
-- @function [parent=#SimpleAudioEngine] resumeAllEffects 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Set the volume of sound effects.<br>
-- param volume must be within the range of 0.0 as the minimum and 1.0 as the maximum.
-- @function [parent=#SimpleAudioEngine] setEffectsVolume 
-- @param self
-- @param #float volume
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Stop playing sound effect.<br>
-- param soundId The return value of function playEffect.
-- @function [parent=#SimpleAudioEngine] stopEffect 
-- @param self
-- @param #unsigned int soundId
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Pause playing background music.<br>
-- js pauseMusic<br>
-- lua pauseMusic
-- @function [parent=#SimpleAudioEngine] pauseBackgroundMusic 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Pause all playing sound effect.
-- @function [parent=#SimpleAudioEngine] pauseAllEffects 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Unload the preloaded effect from internal buffer.<br>
-- param filePath The path of the effect file.
-- @function [parent=#SimpleAudioEngine] unloadEffect 
-- @param self
-- @param #char filePath
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Resume playing sound effect.<br>
-- param soundId The return value of function playEffect.
-- @function [parent=#SimpleAudioEngine] resumeEffect 
-- @param self
-- @param #unsigned int soundId
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Release the shared Engine object.<br>
-- warning It must be called before the application exit, or it will lead to memory leaks.
-- @function [parent=#SimpleAudioEngine] end 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine self (return value: cc.SimpleAudioEngine)
        
--------------------------------
-- Returns a shared instance of the SimpleAudioEngine.<br>
-- js NA
-- @function [parent=#SimpleAudioEngine] getInstance 
-- @param self
-- @return SimpleAudioEngine#SimpleAudioEngine ret (return value: cc.SimpleAudioEngine)
        
return nil
