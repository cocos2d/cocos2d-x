
local ProviderBase = import(".ProviderBase")
local ProviderAndroid = class("ProviderAndroid", ProviderBase)

local SDK_CLASS_NAME = "com.quick2dx.sdk.UmengFeedbackSDK"


function ProviderAndroid:showFeedBack()
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "showFeedback")
    if not ok then
        printError("cc.share.ProviderAndroid:showFeedBack() - call showFeedBack failed.")
        return false
    end

    return true
end

function ProviderAndroid:checkReplies()
    printInfo("cc.feedback.ProviderAndroid:checkReplies() - not support")
end

return ProviderAndroid
