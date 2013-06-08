--Encapsulate SimpleAudioEngine to audioEngine,Play music and sound effects. 
audioEngine = audioEngine or {}

local sharedEngine = SimpleAudioEngine:sharedEngine()

local function stopAllEffects()
    sharedEngine:stopAllEffects()
end

local function getMusicVolume()
    return sharedEngine:getBackgroundMusicVolume()
end

local function isMusicPlaying()
    return sharedEngine:isBackgroundMusicPlaying()
end

local function getEffectsVolume()
    return sharedEngine:getEffectsVolume()
end

local function setMusicVolume(volume)
    sharedEngine:setBackgroundMusicVolume(volume)
end

local function stopEffect(handle)
    sharedEngine:stopEffect(handle)
end

local function stopMusic(isReleaseData)
    local releaseDataValue = false
    if nil ~= isReleaseData then
        releaseDataValue = isReleaseData
    end
    sharedEngine:stopBackgroundMusic(releaseDataValue)
end

local function playMusic(filename, isLoop)
    local loopValue = false
    if nil ~= isLoop then
        loopValue = isLoop
    end
    sharedEngine:playBackgroundMusic(filename, loopValue)
end

local function pauseAllEffects()
    sharedEngine:pauseAllEffects()
end

local function preloadMusic(filename)
    sharedEngine:preloadBackgroundMusic(filename)
end

local function resumeMusic()
    sharedEngine:resumeBackgroundMusic()
end

local function playEffect(filename, isLoop)
    local loopValue = false
    if nil ~= isLoop then
        loopValue = isLoop
    end
    return sharedEngine:playEffect(filename, loopValue)
end

local function rewindMusic()
    sharedEngine:rewindBackgroundMusic()
end

local function willPlayMusic()
    return sharedEngine:willPlayBackgroundMusic()
end

local function unloadEffect(filename)
    sharedEngine:unloadEffect(filename)
end

local function preloadEffect(filename)
    sharedEngine:preloadEffect(filename)
end

local function setEffectsVolume(volume)
    sharedEngine:setEffectsVolume(volume)
end

local function pauseEffect(handle)
    sharedEngine:pauseEffect(handle)
end

local function resumeAllEffects(handle)
    sharedEngine:resumeAllEffects()
end

local function pauseMusic()
    sharedEngine:pauseBackgroundMusic()
end

local function resumeEffect(handle)
    sharedEngine:resumeEffect(handle)
end


audioEngine.stopAllEffects = stopAllEffects
audioEngine.getMusicVolume = getMusicVolume
audioEngine.isMusicPlaying = isMusicPlaying
audioEngine.getEffectsVolume  = getEffectsVolume
audioEngine.setMusicVolume = setMusicVolume
audioEngine.stopEffect     = stopEffect
audioEngine.stopMusic     = stopMusic
audioEngine.playMusic     = playMusic
audioEngine.pauseAllEffects = pauseAllEffects
audioEngine.preloadMusic = preloadMusic
audioEngine.resumeMusic = resumeMusic
audioEngine.playEffect = playEffect
audioEngine.rewindMusic = rewindMusic
audioEngine.willPlayMusic  = willPlayMusic
audioEngine.unloadEffect  = unloadEffect
audioEngine.preloadEffect = preloadEffect
audioEngine.setEffectsVolume = setEffectsVolume
audioEngine.pauseEffect = pauseEffect
audioEngine.resumeAllEffects = resumeAllEffects
audioEngine.pauseMusic = pauseMusic
audioEngine.resumeEffect = resumeEffect


