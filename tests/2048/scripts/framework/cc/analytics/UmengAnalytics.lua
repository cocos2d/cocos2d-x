
local CURRENT_MODULE_NAME = ...

local UmengAnalytics = class("UmengAnalytics")

function UmengAnalytics.getInstance(interface)
    local providerClass

	if device.platform == "android" or device.platform == "ios" then
        providerClass = import(".umenganalytics.Provider", CURRENT_MODULE_NAME)
    else
        printError("push.UmengAnalytics.getInstance() - not supported platform %s", device.platform)
        return nil
    end

    local provider = providerClass.new(interface)

    return provider
end

return UmengAnalytics
