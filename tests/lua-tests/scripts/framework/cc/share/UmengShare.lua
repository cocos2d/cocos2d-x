
local CURRENT_MODULE_NAME = ...

local UmengShare = class("UmengShare")

function UmengShare.getInstance(interface)
    local providerClass
	if device.platform == "android" then
        providerClass = import(".umengshare.ProviderAndroid", CURRENT_MODULE_NAME)
    elseif device.platform == "ios" then
    	providerClass = import(".umengshare.ProviderIOS", CURRENT_MODULE_NAME)
    else
        printError("share.UmengShare.getInstance() - not supported platform %s", device.platform)
        return nil
    end

    local provider = providerClass.new(interface)
    provider:addListener()

    return provider
end

return UmengShare
