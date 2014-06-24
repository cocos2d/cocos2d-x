
local ProviderBase = import(".ProviderBase")
local ProviderIOS = class("ProviderIOS", ProviderBase)

local SDK_CLASS_NAME = "UmengFeedBackSDK"

function ProviderIOS:showFeedBack(appKey)
	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "showFeedback", {appKey = appKey})
	if not ok then
        printError("cc.feedback.ProviderIOS:showFeedBack() - call showFeedback failed.")
    end
end

function ProviderIOS:checkReplies(appKey)
	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "checkReplies", {appKey = appKey})
	if not ok then
        printError("cc.feedback.ProviderIOS:checkReplies() - call checkReplies failed.")
    end
end

return ProviderIOS
