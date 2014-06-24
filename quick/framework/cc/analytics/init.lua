
local CURRENT_MODULE_NAME = ...

local providers = {
    "UmengAnalytics"
}

for _, packageName in ipairs(providers) do
    local className = "analytics." .. packageName
    if not cc.Registry.exists(className) then
        cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), className)
    end
end

local analytics = class("cc.analytics")

local DEFAULT_PROVIDER_OBJECT_NAME = "analytics.default"

function analytics:ctor()
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.providers_ = {}
end

function analytics:start(name)
    if not self.providers_[name] then
        local providerFactoryClass = cc.Registry.newObject(name)
        local provider = providerFactoryClass.getInstance(self)
        if not provider then
            printError("cc.analytics:start() - create analytics provider failed")
            return
        end

        self.providers_[name] = provider
        if not self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] then
            self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] = provider
        end
    end
end

function analytics:stop(name)
    local provider = self:getProvider(name)
    if provider then
        provider:removeListener()
        self.providers_[name or DEFAULT_PROVIDER_OBJECT_NAME] = nil
    end
end

--[[
args {
    command = "要执行的命令",
    providerName = "模块名字",
    args = "执行命令的参数"
}
]]
function analytics:doCommand(args)
    local provider = self:getProvider(args.providerName)
    if provider then
        return provider:doCommand(args)
    end
end


function analytics:getProvider(name)
    name = name or DEFAULT_PROVIDER_OBJECT_NAME
    if self.providers_[name] then
        return self.providers_[name]
    end
    printError("cc.analytics:getProvider() - provider %s not exists", name)
end

return analytics
