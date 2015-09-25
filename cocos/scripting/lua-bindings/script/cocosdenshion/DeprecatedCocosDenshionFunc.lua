if nil == cc.SimpleAudioEngine then
    return
end
--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--functions of SimpleAudioEngine will be deprecated begin
local SimpleAudioEngineDeprecated = { }
function SimpleAudioEngineDeprecated.sharedEngine()
    deprecatedTip("SimpleAudioEngine:sharedEngine","SimpleAudioEngine:getInstance")
    return cc.SimpleAudioEngine:getInstance()
end
SimpleAudioEngine.sharedEngine = SimpleAudioEngineDeprecated.sharedEngine

function SimpleAudioEngineDeprecated.playBackgroundMusic(self,...)
    deprecatedTip("SimpleAudioEngine:playBackgroundMusic","SimpleAudioEngine:playMusic")
    return self:playMusic(...)
end
SimpleAudioEngine.playBackgroundMusic = SimpleAudioEngineDeprecated.playBackgroundMusic
--functions of SimpleAudioEngine will be deprecated end
