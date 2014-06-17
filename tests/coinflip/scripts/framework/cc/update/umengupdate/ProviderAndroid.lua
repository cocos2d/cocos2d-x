
local ProviderBase = import(".ProviderBase")
local ProviderAndroid = class("ProviderAndroid", ProviderBase)

local SDK_CLASS_NAME = "com.quick2dx.sdk.UmengUpdateSDK"

function ProviderAndroid:init()
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "init")
    if not ok then
        printError("cc.update.ProviderAndroid:init() - call init failed.")
        return false
    end

    return true
end

function ProviderAndroid:addListener()
    luaj.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {handler(self, self.callback_)})
end

function ProviderAndroid:removeListener()
    luaj.callStaticMethod(SDK_CLASS_NAME, "removeScriptListener")
end

function ProviderAndroid:update()
	local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "update")
    if not ok then
        printError("cc.update.ProviderAndroid:update() - call update failed.")
        return false
    end

    return true
end

function ProviderAndroid:forceUpdate()
	local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "forceUpdate")
    if not ok then
        printError("cc.update.ProviderAndroid:forceUpdate() - call forceUpdate failed.")
        return false
    end

    return true
end

function ProviderAndroid:silentUpdate()
	local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "silentUpdate")
    if not ok then
        printError("cc.update.ProviderAndroid:silentUpdate() - call silentUpdate failed.")
        return false
    end

    return true
end

return ProviderAndroid
