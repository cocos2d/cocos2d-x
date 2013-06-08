--Encapsulate SimpleAudioEngine to AudioEngine,Play music and sound effects. 
AudioEngine = AudioEngine or {}

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


AudioEngine.stopAllEffects = stopAllEffects
AudioEngine.getMusicVolume = getMusicVolume
AudioEngine.isMusicPlaying = isMusicPlaying
AudioEngine.getEffectsVolume  = getEffectsVolume
AudioEngine.setMusicVolume = setMusicVolume
AudioEngine.stopEffect     = stopEffect
AudioEngine.stopMusic     = stopMusic
AudioEngine.playMusic     = playMusic
AudioEngine.pauseAllEffects = pauseAllEffects
AudioEngine.preloadMusic = preloadMusic
AudioEngine.resumeMusic = resumeMusic
AudioEngine.playEffect = playEffect
AudioEngine.rewindMusic = rewindMusic
AudioEngine.willPlayMusic  = willPlayMusic
AudioEngine.unloadEffect  = unloadEffect
AudioEngine.preloadEffect = preloadEffect
AudioEngine.setEffectsVolume = setEffectsVolume
AudioEngine.pauseEffect = pauseEffect
AudioEngine.resumeAllEffects = resumeAllEffects
AudioEngine.pauseMusic = pauseMusic
AudioEngine.resumeEffect = resumeEffect


