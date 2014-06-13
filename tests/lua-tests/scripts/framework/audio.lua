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

--[[--

播放音乐、音效

]]

local audio = {}

local sharedEngine = SimpleAudioEngine:sharedEngine()

--[[--

返回音乐的音量值

@return number 返回值在 0.0 到 1.0 之间，0.0 表示完全静音，1.0 表示 100% 音量

]]
function audio.getMusicVolume()
    local volume = sharedEngine:getBackgroundMusicVolume()
    if DEBUG > 1 then
        printInfo("audio.getMusicVolume() - volume: %0.1f", volume)
    end
    return volume
end


--[[--

设置音乐的音量

@param number volume 音量在 0.0 到 1.0 之间, 0.0 表示完全静音，1.0 表示 100% 音量

]]
function audio.setMusicVolume(volume)
    volume = checknumber(volume)
    if DEBUG > 1 then
        printInfo("audio.setMusicVolume() - volume: %0.1f", volume)
    end
    sharedEngine:setBackgroundMusicVolume(volume)
end

--[[--

返回音效的音量值

@return number 返回值在 0.0 到 1.0 之间, 0.0 表示完全静音，1.0 表示 100% 音量

]]
function audio.getSoundsVolume()
    local volume = sharedEngine:getEffectsVolume()
    if DEBUG > 1 then
        printInfo("audio.getSoundsVolume() - volume: %0.1f", volume)
    end
    return volume
end

--[[--

设置音效的音量

@param number volume 音量在 0.0 到 1.0 之间, 0.0 表示完全静音，1.0 表示 100% 音量

]]
function audio.setSoundsVolume(volume)
    volume = checknumber(volume)
    if DEBUG > 1 then
        printInfo("audio.setSoundsVolume() - volume: %0.1f", volume)
    end
    sharedEngine:setEffectsVolume(volume)
end

--[[--

预载入一个音乐文件

在播放音乐前预先载入，可以在需要播放音乐时无延迟立即播放。
不过限于硬件设备和操作系统的限制，通常只能预载入一个音乐文件。

@param string filename 音乐文件名

]]
function audio.preloadMusic(filename)
    if not filename then
        printError("audio.preloadMusic() - invalid filename")
        return
    end
    if DEBUG > 1 then
        printInfo("audio.preloadMusic() - filename: %s", tostring(filename))
    end
    sharedEngine:preloadBackgroundMusic(filename)
end

--[[--

播放音乐

如果音乐文件尚未载入，则会首先载入音乐文件，然后开始播放。

注意：即便音乐音量为 0.0，audio.playMusic() 仍然会进行播放操作。
如果希望停止音乐来降低 CPU 占用，应该使用 audio.stopMusic() 接口完全停止音乐播放。

@param string filename 音乐文件名
@param boolean isLoop 是否循环播放，默认为 true

]]
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
    sharedEngine:playBackgroundMusic(filename, isLoop)
end

--[[--

停止播放音乐

@param boolean isReleaseData 是否释放音乐数据，默认为 true

]]
function audio.stopMusic(isReleaseData)
    isReleaseData = checkbool(isReleaseData)
    if DEBUG > 1 then
        printInfo("audio.stopMusic() - isReleaseData: %s", tostring(isReleaseData))
    end
    sharedEngine:stopBackgroundMusic(isReleaseData)
end

--[[--

暂停音乐的播放

]]
function audio.pauseMusic()
    if DEBUG > 1 then
        printInfo("audio.pauseMusic()")
    end
    sharedEngine:pauseBackgroundMusic()
end

--[[--

恢复暂停的音乐

]]
function audio.resumeMusic()
    if DEBUG > 1 then
        printInfo("audio.resumeMusic()")
    end
    sharedEngine:resumeBackgroundMusic()
end

--[[--

从头开始重新播放当前音乐

]]
function audio.rewindMusic()
    if DEBUG > 1 then
        printInfo("audio.rewindMusic()")
    end
    ending:rewindBackgroundMusic()
end

--[[--

检查是否可以开始播放音乐

如果可以则返回 true。

如果尚未载入音乐，或者载入的音乐格式不被设备所支持，该方法将返回 false。

@return boolean

]]
function audio.willPlayMusic()
    local ret = sharedEngine:willPlayBackgroundMusic()
    if DEBUG > 1 then
        printInfo("audio.willPlayMusic() - ret: %s", tostring(ret))
    end
    return ret
end

--[[--

检查当前是否正在播放音乐

如果有音乐正在播放则返回 true，否则返回 false

@return boolean

]]
function audio.isMusicPlaying()
    local ret = sharedEngine:isBackgroundMusicPlaying()
    if DEBUG > 1 then
        printInfo("audio.isMusicPlaying() - ret: %s", tostring(ret))
    end
    return ret
end

--[[--

播放音效，并返回音效句柄

如果音效尚未载入，则会载入后开始播放。

该方法返回的音效句柄用于 audio.stopSound()、audio.pauseSound() 等方法。

@param string filename 音效文件名
@param boolean isLoop 是否重复播放，默认为 false

@return integer 音效句柄

]]
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

--[[--

暂停指定的音效

@param integer 音效句柄

]]
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

--[[--

暂停所有音效

]]
function audio.pauseAllSounds()
    if DEBUG > 1 then
        printInfo("audio.pauseAllSounds()")
    end
    sharedEngine:pauseAllEffects()
end

--[[--

恢复暂停的音效

@param integer 音效句柄

]]
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

--[[--

恢复所有的音效

]]
function audio.resumeAllSounds()
    if DEBUG > 1 then
        printInfo("audio.resumeAllSounds()")
    end
    sharedEngine:resumeAllEffects()
end

--[[--

停止指定的音效

@param integer 音效句柄

]]
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

--[[--

停止所有音效

]]
function audio.stopAllSounds()
    if DEBUG > 1 then
        printInfo("audio.stopAllSounds()")
    end
    sharedEngine:stopAllEffects()
end

--[[--

预载入一个音效文件

可以在进入场景前，载入该场景需要的所有音效。这样就不会因为首次播放某个未载入的音效，而导致游戏暂停执行。

@param string 音效文件名

]]
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

--[[--

从内存卸载一个音效

退出场景时，可以卸载掉只有该场景使用的音效，从而节约内存。

@param string 音效文件名

]]
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
