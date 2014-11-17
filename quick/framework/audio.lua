--[[

Copyright (c) 2011-2014 chukong-inc.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

]]

--------------------------------
-- @module audio

--[[--

播放音乐、音效

]]

local audio = {}

local sharedEngine = cc.SimpleAudioEngine:getInstance()


--------------------------------
-- 返回音乐的音量值
-- @function [parent=#audio] getMusicVolume
-- @return number#number ret (return value: number)  返回值在 0.0 到 1.0 之间，0.0 表示完全静音，1.0 表示 100% 音量

function audio.getMusicVolume()
    local volume = sharedEngine:getMusicVolume()
    if DEBUG > 1 then
        printInfo("audio.getMusicVolume() - volume: %0.1f", volume)
    end
    return volume
end

--------------------------------
-- 设置音乐的音量
-- @function [parent=#audio] setMusicVolume
-- @param number volume 音量在 0.0 到 1.0 之间, 0.0 表示完全静音，1.0 表示 100% 音量

function audio.setMusicVolume(volume)
    volume = checknumber(volume)
    if DEBUG > 1 then
        printInfo("audio.setMusicVolume() - volume: %0.1f", volume)
    end
    sharedEngine:setMusicVolume(volume)
end

--------------------------------
-- 返回音效的音量值
-- @function [parent=#audio] getSoundsVolume
-- @return number#number ret (return value: number)  返回值在 0.0 到 1.0 之间, 0.0 表示完全静音，1.0 表示 100% 音量

function audio.getSoundsVolume()
    local volume = sharedEngine:getEffectsVolume()
    if DEBUG > 1 then
        printInfo("audio.getSoundsVolume() - volume: %0.1f", volume)
    end
    return volume
end

--------------------------------
-- 设置音效的音量
-- @function [parent=#audio] setSoundsVolume
-- @param number volume 音量在 0.0 到 1.0 之间, 0.0 表示完全静音，1.0 表示 100% 音量

function audio.setSoundsVolume(volume)
    volume = checknumber(volume)
    if DEBUG > 1 then
        printInfo("audio.setSoundsVolume() - volume: %0.1f", volume)
    end
    sharedEngine:setEffectsVolume(volume)
end

--------------------------------
-- 预载入一个音乐文件
-- @function [parent=#audio] preloadMusic
-- @param string filename 音乐文件名

function audio.preloadMusic(filename)
    if not filename then
        printError("audio.preloadMusic() - invalid filename")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.preloadMusic() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadMusic(filename)
end

--------------------------------
-- 播放音乐
-- @function [parent=#audio] playMusic
-- @param string filename 音乐文件名
-- @param boolean isLoop 是否循环播放，默认为 true

function audio.playMusic(filename, isLoop)
    if not filename then
        printError("audio.playMusic() - invalid filename")
        return
    end
    if type(isLoop) ~= "boolean" then isLoop = true end

    audio.stopMusic()
    if DEBUG > 1 then
        printInfo("audio.playMusic() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    sharedEngine:playMusic(filename, isLoop)
end

--------------------------------
-- 停止播放音乐
-- @function [parent=#audio] stopMusic
-- @param boolean isReleaseData 是否释放音乐数据，默认为 true

function audio.stopMusic(isReleaseData)
    isReleaseData = checkbool(isReleaseData)
    if DEBUG > 1 then
        printInfo("audio.stopMusic() - isReleaseData: %s", tostring(isReleaseData))
    end
    sharedEngine:stopMusic(isReleaseData)
end

--------------------------------
-- 暂停音乐的播放
-- @function [parent=#audio] pauseMusic
function audio.pauseMusic()
    if DEBUG > 1 then
        printInfo("audio.pauseMusic()")
    end
    sharedEngine:pauseMusic()
end

--------------------------------
-- 恢复暂停的音乐
-- @function [parent=#audio] resumeMusic
function audio.resumeMusic()
    if DEBUG > 1 then
        printInfo("audio.resumeMusic()")
    end
    sharedEngine:resumeMusic()
end

--------------------------------
-- 从头开始重新播放当前音乐
-- @function [parent=#audio] rewindMusic
function audio.rewindMusic()
    if DEBUG > 1 then
        printInfo("audio.rewindMusic()")
    end
    sharedEngine:rewindMusic()
end

--------------------------------
-- 检查是否可以开始播放音乐
-- 如果可以则返回 true。
-- 如果尚未载入音乐，或者载入的音乐格式不被设备所支持，该方法将返回 false。
-- @function [parent=#audio] willPlayMusic
-- @return boolean#boolean ret (return value: bool) 

function audio.willPlayMusic()
    local ret = sharedEngine:willPlayMusic()
    if DEBUG > 1 then
        printInfo("audio.willPlayMusic() - ret: %s", tostring(ret))
    end
    return ret
end

--------------------------------
-- 检查当前是否正在播放音乐
-- @function [parent=#audio] isMusicPlaying
-- @return boolean#boolean ret (return value: bool) 

function audio.isMusicPlaying()
    local ret = sharedEngine:isMusicPlaying()
    if DEBUG > 1 then
        printInfo("audio.isMusicPlaying() - ret: %s", tostring(ret))
    end
    return ret
end

--------------------------------
-- 播放音效，并返回音效句柄
-- 如果音效尚未载入，则会载入后开始播放。
-- 该方法返回的音效句柄用于 audio.stopSound()、audio.pauseSound() 等方法。
-- @function [parent=#audio] playSound
-- @param string filename 音效文件名
-- @param boolean isLoop 是否重复播放，默认为 false
-- @return integer#integer ret (return value: int)  音效句柄

function audio.playSound(filename, isLoop)
    if not filename then
        printError("audio.playSound() - invalid filename")
        return
    end
    if type(isLoop) ~= "boolean" then isLoop = false end
    if DEBUG > 1 then
        printInfo("audio.playSound() - filename: %s, isLoop: %s", tostring(filename), tostring(isLoop))
    end
    return sharedEngine:playEffect(filename, isLoop)
end

--------------------------------
-- 暂停指定的音效
-- @function [parent=#audio] pauseSound
-- @param integer 音效句柄

function audio.pauseSound(handle)
    if not handle then
        printError("audio.pauseSound() - invalid handle")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.pauseSound() - handle: %s", tostring(handle))
    end
    sharedEngine:pauseEffect(handle)
end

--------------------------------
-- 暂停所有音效
-- @function [parent=#audio] pauseAllSounds

function audio.pauseAllSounds()
    if DEBUG > 1 then
        printInfo("audio.pauseAllSounds()")
    end
    sharedEngine:pauseAllEffects()
end

--------------------------------
-- 恢复暂停的音效
-- @function [parent=#audio] resumeSound
-- @param integer 音效句柄

function audio.resumeSound(handle)
    if not handle then
        printError("audio.resumeSound() - invalid handle")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.resumeSound() - handle: %s", tostring(handle))
    end
    sharedEngine:resumeEffect(handle)
end

--------------------------------
-- 恢复所有的音效
-- @function [parent=#audio] resumeAllSounds

function audio.resumeAllSounds()
    if DEBUG > 1 then
        printInfo("audio.resumeAllSounds()")
    end
    sharedEngine:resumeAllEffects()
end

--------------------------------
-- 停止指定的音效
-- @function [parent=#audio] stopSound
-- @param integer 音效句柄

function audio.stopSound(handle)
    if not handle then
        printError("audio.stopSound() - invalid handle")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.stopSound() - handle: %s", tostring(handle))
    end
    sharedEngine:stopEffect(handle)
end

--------------------------------
-- 停止所有音效
-- @function [parent=#audio] stopAllSounds

function audio.stopAllSounds()
    if DEBUG > 1 then
        printInfo("audio.stopAllSounds()")
    end
    sharedEngine:stopAllEffects()
end

--------------------------------
-- 预载入一个音效文件
-- @function [parent=#audio] preloadSound
-- @param string 音效文件名

function audio.preloadSound(filename)
    if not filename then
        printError("audio.preloadSound() - invalid filename")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.preloadSound() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadEffect(filename)
end

--------------------------------
-- 从内存卸载一个音效
-- @function [parent=#audio] unloadSound
-- @param string 音效文件名

function audio.unloadSound(filename)
    if not filename then
        printError("audio.unloadSound() - invalid filename")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.unloadSound() - filename: %s", tostring(filename))
    end
    sharedEngine:unloadEffect(filename)
end

return audio
