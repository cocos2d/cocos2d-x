
local ProviderBase = import(".ProviderBase")
local ProviderAndroid = class("ProviderAndroid", ProviderBase)

local SDK_CLASS_NAME = "com.quick2dx.sdk.PunchBoxSDK"


function ProviderAndroid:start()
    local ok, ret = luaj.callStaticMethod(SDK_CLASS_NAME, "start", {tostring(self.options_.appId)})
    if not ok then
        printError("cc.ad.ProviderAndroid:ctor() - init SDK failed.")
        return false
    end

    luaj.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {handler(self, self.callback_)})
    return true
end

function ProviderAndroid:stop()
    luaj.callStaticMethod(SDK_CLASS_NAME, "stop")
end

function ProviderAndroid:show(adType, options)
    if type(options) ~= "table" then options = {} end
    local id = options.id or ""
    local position = options.position or "default"
    luaj.callStaticMethod(SDK_CLASS_NAME, "show", {adType, id, position})
end

function ProviderAndroid:remove()
    luaj.callStaticMethod(SDK_CLASS_NAME, "remove")
end

return ProviderAndroid
