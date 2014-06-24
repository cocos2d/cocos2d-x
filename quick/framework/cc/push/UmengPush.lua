
local CURRENT_MODULE_NAME = ...

local UmengPush = class("UmengPush")

function UmengPush.getInstance(interface)
    local providerClass

	if device.platform == "android" then
        providerClass = import(".umengpush.ProviderAndroid", CURRENT_MODULE_NAME)
    else
        printError("push.UmengPush.getInstance() - not supported platform %s", device.platform)
        return nil
    end

    local provider = providerClass.new(interface)
    provider:addListener()

    return provider
end

return UmengPush
