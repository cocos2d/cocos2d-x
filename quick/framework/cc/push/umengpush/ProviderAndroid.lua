
local ProviderBase = import(".ProviderBase")
local ProviderAndroid = class("ProviderAndroid", ProviderBase)

local SDK_CLASS_NAME = "com.quick2dx.sdk.UmengPushSDK"

function ProviderAndroid:addListener()
	luaj.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {handler(self, self.callback_)})
end

function ProviderAndroid:removeListener()
	luaj.callStaticMethod(SDK_CLASS_NAME, "removeScriptListener")
end

function ProviderAndroid:startPush()
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "startPush")
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call startPush failed.")
        return false
    end

    return true
end

function ProviderAndroid:stopPush()
	local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "stopPush")
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call stopPush failed.")
        return false
    end

    return true
end

function ProviderAndroid:setAlias(alias, aliasType)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "setAlias", {alias, aliasType})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call setAlias failed.")
        return false
    end

    return true
end

function ProviderAndroid:delAlias(alias, aliasType)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "delAlias", {alias, aliasType})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

function ProviderAndroid:setTags(tags)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "setTags", {table.concat(tags, ",")})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

function ProviderAndroid:delTags(tags)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "delTags", {table.concat(tags, ",")})
    if not ok then
        printError("cc.push.ProviderAndroid:ctor() - call delAlias failed.")
        return false
    end

    return true
end

return ProviderAndroid
