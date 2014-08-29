
--------------------------------
-- @module ComAudio
-- @extend Component
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#ComAudio] stopAllEffects 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ComAudio] getEffectsVolume 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] stopEffect 
-- @param self
-- @param #unsigned int nSoundId
        
--------------------------------
-- 
-- @function [parent=#ComAudio] getBackgroundMusicVolume 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] willPlayBackgroundMusic 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setBackgroundMusicVolume 
-- @param self
-- @param #float volume
        
--------------------------------
-- 
-- @function [parent=#ComAudio] end 
-- @param self
        
--------------------------------
-- @overload self         
-- @overload self, bool         
-- @function [parent=#ComAudio] stopBackgroundMusic
-- @param self
-- @param #bool bReleaseData

--------------------------------
-- 
-- @function [parent=#ComAudio] pauseBackgroundMusic 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ComAudio] isBackgroundMusicPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] isLoop 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] resumeAllEffects 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ComAudio] pauseAllEffects 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ComAudio] preloadBackgroundMusic 
-- @param self
-- @param #char pszFilePath
        
--------------------------------
-- @overload self, char         
-- @overload self, char, bool         
-- @overload self         
-- @function [parent=#ComAudio] playBackgroundMusic
-- @param self
-- @param #char pszFilePath
-- @param #bool bLoop

--------------------------------
-- @overload self, char         
-- @overload self, char, bool         
-- @overload self         
-- @function [parent=#ComAudio] playEffect
-- @param self
-- @param #char pszFilePath
-- @param #bool bLoop
-- @return unsigned int#unsigned int ret (retunr value: unsigned int)

--------------------------------
-- 
-- @function [parent=#ComAudio] preloadEffect 
-- @param self
-- @param #char pszFilePath
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setLoop 
-- @param self
-- @param #bool bLoop
        
--------------------------------
-- 
-- @function [parent=#ComAudio] unloadEffect 
-- @param self
-- @param #char pszFilePath
        
--------------------------------
-- 
-- @function [parent=#ComAudio] rewindBackgroundMusic 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ComAudio] pauseEffect 
-- @param self
-- @param #unsigned int nSoundId
        
--------------------------------
-- 
-- @function [parent=#ComAudio] resumeBackgroundMusic 
-- @param self
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setFile 
-- @param self
-- @param #char pszFilePath
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setEffectsVolume 
-- @param self
-- @param #float volume
        
--------------------------------
-- 
-- @function [parent=#ComAudio] getFile 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] resumeEffect 
-- @param self
-- @param #unsigned int nSoundId
        
--------------------------------
-- 
-- @function [parent=#ComAudio] create 
-- @param self
-- @return ComAudio#ComAudio ret (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setEnabled 
-- @param self
-- @param #bool b
        
--------------------------------
-- 
-- @function [parent=#ComAudio] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] serialize 
-- @param self
-- @param #void r
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
