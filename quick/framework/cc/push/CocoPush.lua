

local CURRENT_MODULE_NAME = ...

local CocoPush = class("CocoPush")

function CocoPush.getInstance(interface)
    local providerClass

	if device.platform == "android" then
        providerClass = import(".cocopush.ProviderAndroid", CURRENT_MODULE_NAME)
    else
        printError("push.CocoPush.getInstance() - not supported platform %s", device.platform)
        return nil
    end

    local provider = providerClass.new(interface)
    provider:addListener()

    return provider
end

return CocoPush
