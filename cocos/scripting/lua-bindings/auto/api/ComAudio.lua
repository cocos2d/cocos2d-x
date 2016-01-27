
--------------------------------
-- @module ComAudio
-- @extend Component,PlayableProtocol
-- @parent_module ccs

--------------------------------
-- 
-- @function [parent=#ComAudio] stopAllEffects 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
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
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
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
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] end 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- / @{/ @name implement Playable Protocol
-- @function [parent=#ComAudio] start 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- @overload self         
-- @overload self, bool         
-- @function [parent=#ComAudio] stopBackgroundMusic
-- @param self
-- @param #bool bReleaseData
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)

--------------------------------
-- 
-- @function [parent=#ComAudio] pauseBackgroundMusic 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
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
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] pauseAllEffects 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] preloadBackgroundMusic 
-- @param self
-- @param #char pszFilePath
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- @overload self, char         
-- @overload self, char, bool         
-- @overload self         
-- @function [parent=#ComAudio] playBackgroundMusic
-- @param self
-- @param #char pszFilePath
-- @param #bool bLoop
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)

--------------------------------
-- 
-- @function [parent=#ComAudio] stop 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- @overload self, char         
-- @overload self, char, bool         
-- @overload self         
-- @function [parent=#ComAudio] playEffect
-- @param self
-- @param #char pszFilePath
-- @param #bool bLoop
-- @return unsigned int#unsigned int ret (return value: unsigned int)

--------------------------------
-- 
-- @function [parent=#ComAudio] preloadEffect 
-- @param self
-- @param #char pszFilePath
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setLoop 
-- @param self
-- @param #bool bLoop
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] unloadEffect 
-- @param self
-- @param #char pszFilePath
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] rewindBackgroundMusic 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] pauseEffect 
-- @param self
-- @param #unsigned int nSoundId
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] resumeBackgroundMusic 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setFile 
-- @param self
-- @param #char pszFilePath
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
--------------------------------
-- 
-- @function [parent=#ComAudio] setEffectsVolume 
-- @param self
-- @param #float volume
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
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
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
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
-- js NA<br>
-- lua NA
-- @function [parent=#ComAudio] onRemove 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
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
        
--------------------------------
-- js NA<br>
-- lua NA
-- @function [parent=#ComAudio] onAdd 
-- @param self
-- @return ComAudio#ComAudio self (return value: ccs.ComAudio)
        
return nil
