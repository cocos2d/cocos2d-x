-- This is the DeprecatedCocosBuilderClass

DeprecatedCocosBuilderClass = {} or DeprecatedCocosBuilderClass

--tip
local function deprecatedTip(old_name,new_name)
    print("\n********** \n"..old_name.." was deprecated please use ".. new_name .. " instead.\n**********")
end

--CCBReader class will be Deprecated,begin
function DeprecatedCocosBuilderClass.CCBReader()
    deprecatedTip("CCBReader","cc.BReader")
    return cc.BReader
end
_G["CCBReader"] = DeprecatedCocosBuilderClass.CCBReader()
--CCBReader class will be Deprecated,end

--CCBAnimationManager class will be Deprecated,begin
function DeprecatedCocosBuilderClass.CCBAnimationManager()
    deprecatedTip("CCBAnimationManager","cc.BAnimationManager")
    return cc.BAnimationManager
end
_G["CCBAnimationManager"] = DeprecatedCocosBuilderClass.CCBAnimationManager()
--CCBAnimationManager class will be Deprecated,end

--CCBProxy class will be Deprecated,begin
function DeprecatedCocosBuilderClass.CCBProxy()
    deprecatedTip("CCBProxy","cc.CCBProxy")
    return cc.CCBProxy
end
_G["CCBProxy"] = DeprecatedCocosBuilderClass.CCBProxy()
--CCBProxy class will be Deprecated,end
