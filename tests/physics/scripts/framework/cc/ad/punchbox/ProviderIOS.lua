
local ProviderBase = import(".ProviderBase")
local ProviderIOS = class("ProviderIOS", ProviderBase)

local SDK_CLASS_NAME = "PunchBoxAdSDK"

function ProviderIOS:start()
    local ok, ret = luaoc.callStaticMethod(SDK_CLASS_NAME, "start", {appId = tostring(self.options_.appId)})
    if not ok then
        printError("cc.ad.ProviderIOS:ctor() - init SDK failed.")
        return false
    end

    luaoc.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {listener = handler(self, self.callback_)})
    return true
end

function ProviderIOS:stop()
    luaoc.callStaticMethod(SDK_CLASS_NAME, "stop")
end

function ProviderIOS:show(command, options)
    if type(options) ~= "table" then options = {} end
    local id = options.id or ""
    local position = options.position or "default"
    luaoc.callStaticMethod(SDK_CLASS_NAME, "show", {command = command, id = id, position = position})
end

function ProviderIOS:remove()
    luaoc.callStaticMethod(SDK_CLASS_NAME, "remove")
end

return ProviderIOS
