
local CURRENT_MODULE_NAME = ...

local PunchBox = class("PunchBox")

function PunchBox.getInstance(interface, options)
    if type(options) ~= "table" or type(options.appId) ~= "string" then
        printError("ad.PunchBox.getInstance() - invalid options, miss appId")
        return nil
    end

    local providerClass
    if device.platform == "ios" then
        providerClass = import(".punchbox.ProviderIOS", CURRENT_MODULE_NAME)
    elseif device.platform == "android" then
        providerClass = import(".punchbox.ProviderAndroid", CURRENT_MODULE_NAME)
    else
        printError("ad.PunchBox.getInstance() - not supported platform %s", device.platform)
        return nil
    end

    local provider = providerClass.new(interface, options)
    if provider:start() then return provider end

    return nil -- create provider failed
end

return PunchBox
