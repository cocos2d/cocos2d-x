if nil == cc.SimpleAudioEngine then
    return
end
-- This is the DeprecatedCocosDenshionClass

DeprecatedCocosDenshionClass = {} or DeprecatedCocosDenshionClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--SimpleAudioEngine class will be Deprecated,begin
function DeprecatedCocosDenshionClass.SimpleAudioEngine()
    deprecatedTip("SimpleAudioEngine","cc.SimpleAudioEngine")
    return cc.SimpleAudioEngine
end
_G["SimpleAudioEngine"] = DeprecatedCocosDenshionClass.SimpleAudioEngine()
--SimpleAudioEngine class will be Deprecated,end
