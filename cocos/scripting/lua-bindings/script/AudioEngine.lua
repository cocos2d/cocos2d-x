--Encapsulate SimpleAudioEngine to AudioEngine,Play music and sound effects. 
local M = {}
local audioEngineInstance = cc.SimpleAudioEngine:getInstance()

function M.stopAllEffects()
    audioEngineInstance:stopAllEffects()
end

function M.getMusicVolume()
    return audioEngineInstance:getMusicVolume()
end

function M.isMusicPlaying()
    return audioEngineInstance:isMusicPlaying()
end

function M.getEffectsVolume()
    return audioEngineInstance:getEffectsVolume()
end

function M.setMusicVolume(volume)
    audioEngineInstance:setMusicVolume(volume)
end

function M.stopEffect(handle)
    audioEngineInstance:stopEffect(handle)
end

function M.stopMusic(isReleaseData)
    local releaseDataValue = false
    if nil ~= isReleaseData then
        releaseDataValue = isReleaseData
    end
    audioEngineInstance:stopMusic(releaseDataValue)
end

function M.playMusic(filename, isLoop)
    local loopValue = false
    if nil ~= isLoop then
        loopValue = isLoop
    end
    audioEngineInstance:playMusic(filename, loopValue)
end

function M.pauseAllEffects()
    audioEngineInstance:pauseAllEffects()
end

function M.preloadMusic(filename)
    audioEngineInstance:preloadMusic(filename)
end

function M.resumeMusic()
    audioEngineInstance:resumeMusic()
end

function M.playEffect(filename, isLoop)
    local loopValue = false
    if nil ~= isLoop then
        loopValue = isLoop
    end
    return audioEngineInstance:playEffect(filename, loopValue)
end

function M.rewindMusic()
    audioEngineInstance:rewindMusic()
end

function M.willPlayMusic()
    return audioEngineInstance:willPlayMusic()
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
    audioEngineInstance:pauseMusic()
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


