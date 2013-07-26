--Encapsulate SimpleAudioEngine to AudioEngine,Play music and sound effects. 
local M = {}
local audioEngineInstance = SimpleAudioEngine:getInstance()

function M.stopAllEffects()
    audioEngineInstance:stopAllEffects()
end

function M.getMusicVolume()
    return audioEngineInstance:getBackgroundMusicVolume()
end

function M.isMusicPlaying()
    return audioEngineInstance:isBackgroundMusicPlaying()
end

function M.getEffectsVolume()
    return audioEngineInstance:getEffectsVolume()
end

function M.setMusicVolume(volume)
    audioEngineInstance:setBackgroundMusicVolume(volume)
end

function M.stopEffect(handle)
    audioEngineInstance:stopEffect(handle)
end

function M.stopMusic(isReleaseData)
    local releaseDataValue = false
    if nil ~= isReleaseData then
        releaseDataValue = isReleaseData
    end
    audioEngineInstance:stopBackgroundMusic(releaseDataValue)
end

function M.playMusic(filename, isLoop)
    local loopValue = false
    if nil ~= isLoop then
        loopValue = isLoop
    end
    audioEngineInstance:playBackgroundMusic(filename, loopValue)
end

function M.pauseAllEffects()
    audioEngineInstance:pauseAllEffects()
end

function M.preloadMusic(filename)
    audioEngineInstance:preloadBackgroundMusic(filename)
end

function M.resumeMusic()
    audioEngineInstance:resumeBackgroundMusic()
end

function M.playEffect(filename, isLoop)
    local loopValue = false
    if nil ~= isLoop then
        loopValue = isLoop
    end
    return audioEngineInstance:playEffect(filename, loopValue)
end

function M.rewindMusic()
    audioEngineInstance:rewindBackgroundMusic()
end

function M.willPlayMusic()
    return audioEngineInstance:willPlayBackgroundMusic()
end

function M.unloadEffect(filename)
    audioEngineInstance:unloadEffect(filename)
end

function M.preloadEffect(filename)
    audioEngineInstance:preloadEffect(filename)
end

function M.setEffectsVolume(volume)
    audioEngineInstance:setEffectsVolume(volume)
end

function M.pauseEffect(handle)
    audioEngineInstance:pauseEffect(handle)
end

function M.resumeAllEffects(handle)
    audioEngineInstance:resumeAllEffects()
end

function M.pauseMusic()
    audioEngineInstance:pauseBackgroundMusic()
end

function M.resumeEffect(handle)
    audioEngineInstance:resumeEffect(handle)
end

local modename = "AudioEngine"
local proxy = {}
local mt    = {
    __index = M,
    __newindex =  function (t ,k ,v)
        print("attemp to update a read-only table")
    end
} 
setmetatable(proxy,mt)
_G[modename] = proxy
package.loaded[modename] = proxy


