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

定义所有已经废弃的 API

]]

-- debug
echoLog = DEPRECATED(printLog, "echoLog", "printLog")
echoError = DEPRECATED(printError, "echoError", "printError")
echoInfo = DEPRECATED(printInfo, "echoInfo", "printInfo")

-- functions
tonum = DEPRECATED(checknumber, "tonum", "checknumber")
toint = DEPRECATED(checkint, "toint", "checkint")
tobool = DEPRECATED(checkbool, "tobool", "checkbool")
totable = DEPRECATED(checktable, "totable", "checktable")

table.insertTo = DEPRECATED(table.insertto, "table.insertTo", "table.insertto")
table.indexOf = DEPRECATED(table.indexof, "table.indexOf", "table.indexof")
table.keyOfItem = DEPRECATED(table.keyof, "table.keyOfItem", "table.keyof")
table.removeItem = DEPRECATED(table.removebyvalue, "table.removeItem", "table.removebyvalue")

string.htmlspecialcharsDecode = DEPRECATED(string.restorehtmlspecialchars, "string.htmlspecialcharsDecode", "string.restorehtmlspecialchars")
string.formatNumberThousands = DEPRECATED(string.formatnumberthousands, "string.formatNumberThousands", "string.formatnumberthousands")

-- audio
audio.getBackgroundMusicVolume = DEPRECATED(audio.getMusicVolume, "audio.getBackgroundMusicVolume", "audio.getMusicVolume")
audio.setBackgroundMusicVolume = DEPRECATED(audio.setMusicVolume, "audio.setBackgroundMusicVolume", "audio.setMusicVolume")
audio.getEffectsVolume = DEPRECATED(audio.getSoundsVolume, "audio.getEffectsVolume", "audio.getSoundsVolume")
audio.setEffectsVolume = DEPRECATED(audio.setSoundsVolume, "audio.setEffectsVolume", "audio.setSoundsVolume")
audio.preloadBackgroundMusic = DEPRECATED(audio.preloadMusic, "audio.preloadBackgroundMusic", "audio.preloadMusic")
audio.playBackgroundMusic = DEPRECATED(audio.playMusic, "audio.playBackgroundMusic", "audio.playMusic")
audio.stopBackgroundMusic = DEPRECATED(audio.stopMusic, "audio.stopBackgroundMusic", "audio.stopMusic")
audio.pauseBackgroundMusic = DEPRECATED(audio.pauseMusic, "audio.pauseBackgroundMusic", "audio.pauseMusic")
audio.resumeBackgroundMusic = DEPRECATED(audio.resumeMusic, "audio.resumeBackgroundMusic", "audio.resumeMusic")
audio.rewindBackgroundMusic = DEPRECATED(audio.rewindMusic, "audio.rewindBackgroundMusic", "audio.rewindMusic")
audio.willPlayBackgroundMusic = DEPRECATED(audio.willPlayMusic, "audio.willPlayBackgroundMusic", "audio.willPlayMusic")
audio.isBackgroundMusicPlaying = DEPRECATED(audio.isMusicPlaying, "audio.isBackgroundMusicPlaying", "audio.isMusicPlaying")
audio.playEffect = DEPRECATED(audio.playSound, "audio.playEffect", "audio.playSound")
audio.pauseEffect = DEPRECATED(audio.pauseSound, "audio.pauseEffect", "audio.pauseSound")
audio.pauseAllEffects = DEPRECATED(audio.pauseAllSounds, "audio.pauseAllEffects", "audio.pauseAllSounds")
audio.resumeEffect = DEPRECATED(audio.resumeSound, "audio.resumeEffect", "audio.resumeSound")
audio.resumeAllEffects = DEPRECATED(audio.resumeAllSounds, "audio.resumeAllEffects", "audio.resumeAllSounds")
audio.stopEffect = DEPRECATED(audio.stopSound, "audio.stopEffect", "audio.stopSound")
audio.stopAllEffects = DEPRECATED(audio.stopAllSounds, "audio.stopAllEffects", "audio.stopAllSounds")
audio.preloadEffect = DEPRECATED(audio.preloadSound, "audio.preloadEffect", "audio.preloadSound")
audio.unloadEffect = DEPRECATED(audio.unloadSound, "audio.unloadEffect", "audio.unloadSound")

-- constants
kCCMenuHandlerPriority = 0

----
CCPointArray = {}

local CCPointArray_mt = {
	__index = CCPointArray,
}

function CCPointArray:add( point )
	self[#self+1] = point
end

function CCPointArray:create( capacity )
	local a = {}
	for i=1,capacity do
		a[i] = cc.p(0, 0)
	end
	setmetatable(a, CCPointArray_mt)
	return a
end

