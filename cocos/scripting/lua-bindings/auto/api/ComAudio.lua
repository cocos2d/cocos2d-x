
--------------------------------
-- @module ComAudio
-- @extend Component

--------------------------------
-- @function [parent=#ComAudio] stopAllEffects 
-- @param self
        
--------------------------------
-- @function [parent=#ComAudio] getEffectsVolume 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ComAudio] stopEffect 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#ComAudio] getBackgroundMusicVolume 
-- @param self
-- @return float#float ret (return value: float)
        
--------------------------------
-- @function [parent=#ComAudio] willPlayBackgroundMusic 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ComAudio] setBackgroundMusicVolume 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ComAudio] end 
-- @param self
        
--------------------------------
-- overload function: stopBackgroundMusic()
--          
-- overload function: stopBackgroundMusic(bool)
--          
-- @function [parent=#ComAudio] stopBackgroundMusic
-- @param self
-- @param #bool bool

--------------------------------
-- @function [parent=#ComAudio] pauseBackgroundMusic 
-- @param self
        
--------------------------------
-- @function [parent=#ComAudio] isBackgroundMusicPlaying 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ComAudio] isLoop 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ComAudio] resumeAllEffects 
-- @param self
        
--------------------------------
-- @function [parent=#ComAudio] pauseAllEffects 
-- @param self
        
--------------------------------
-- @function [parent=#ComAudio] preloadBackgroundMusic 
-- @param self
-- @param #char char
        
--------------------------------
-- overload function: playBackgroundMusic(char)
--          
-- overload function: playBackgroundMusic(char, bool)
--          
-- overload function: playBackgroundMusic()
--          
-- @function [parent=#ComAudio] playBackgroundMusic
-- @param self
-- @param #char char
-- @param #bool bool

--------------------------------
-- overload function: playEffect(char)
--          
-- overload function: playEffect(char, bool)
--          
-- overload function: playEffect()
--          
-- @function [parent=#ComAudio] playEffect
-- @param self
-- @param #char char
-- @param #bool bool
-- @return unsigned int#unsigned int ret (retunr value: unsigned int)

--------------------------------
-- @function [parent=#ComAudio] preloadEffect 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#ComAudio] setLoop 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ComAudio] unloadEffect 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#ComAudio] rewindBackgroundMusic 
-- @param self
        
--------------------------------
-- @function [parent=#ComAudio] pauseEffect 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#ComAudio] resumeBackgroundMusic 
-- @param self
        
--------------------------------
-- @function [parent=#ComAudio] setFile 
-- @param self
-- @param #char char
        
--------------------------------
-- @function [parent=#ComAudio] setEffectsVolume 
-- @param self
-- @param #float float
        
--------------------------------
-- @function [parent=#ComAudio] getFile 
-- @param self
-- @return char#char ret (return value: char)
        
--------------------------------
-- @function [parent=#ComAudio] resumeEffect 
-- @param self
-- @param #unsigned int int
        
--------------------------------
-- @function [parent=#ComAudio] create 
-- @param self
-- @return ComAudio#ComAudio ret (return value: ccs.ComAudio)
        
--------------------------------
-- @function [parent=#ComAudio] createInstance 
-- @param self
-- @return Ref#Ref ret (return value: cc.Ref)
        
--------------------------------
-- @function [parent=#ComAudio] setEnabled 
-- @param self
-- @param #bool bool
        
--------------------------------
-- @function [parent=#ComAudio] isEnabled 
-- @param self
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ComAudio] serialize 
-- @param self
-- @param #void void
-- @return bool#bool ret (return value: bool)
        
--------------------------------
-- @function [parent=#ComAudio] init 
-- @param self
-- @return bool#bool ret (return value: bool)
        
return nil
