
local CURRENT_MODULE_NAME = ...

local UmengFeedback = class("UmengFeedback")

function UmengFeedback.getInstance(interface)
    local providerClass
	if device.platform == "android" then
        providerClass = import(".umengfeedback.ProviderAndroid", CURRENT_MODULE_NAME)
    elseif device.platform == "ios" then
    	providerClass = import(".umengfeedback.ProviderIOS", CURRENT_MODULE_NAME)
    else
        printError("share.UmengFeedback.getInstance() - not supported platform %s", device.platform)
        return nil
    end

    local provider = providerClass.new(interface)

    return provider
end

return UmengFeedback
