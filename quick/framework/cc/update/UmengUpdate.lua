
local CURRENT_MODULE_NAME = ...

local UmengUpdate = class("UmengUpdate")

function UmengUpdate.getInstance(interface)
	local providerClass
	if device.platform == "android" then
		providerClass = import(".umengupdate.ProviderAndroid", CURRENT_MODULE_NAME)
	else
		printError("cc.update.UmengUpdate.getInstance() - not supportPlatformn %s", device.platform)
		return nil
	end

	local provider = providerClass.new(interface)
	provider:init()
	provider:addListener()

    return provider
end

return UmengUpdate
