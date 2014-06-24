
local CURRENT_MODULE_NAME = ...

local providers = {
    "PunchBox",
}
for _, packageName in ipairs(providers) do
    local className = "ad." .. packageName
    if not cc.Registry.exists(className) then
        cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), className)
    end
end

local ad = class("cc.ad")

local DEFAULT_PROVIDER_OBJECT_NAME = "ad.default"

function ad:ctor()
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.events = import(".events", CURRENT_MODULE_NAME)
    self.errors = import(".errors", CURRENT_MODULE_NAME)
    self.providers_ = {}
end

function ad:start(options, name)
    if not self.providers_[name] then
        local providerFactoryClass = cc.Registry.newObject(name)
        local provider = providerFactoryClass.getInstance(self, options)
        if not provider then
            printError("cc.ad:start() - create ad provider failed")
            return
        end

        self.providers_[name] = provider
        if not self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] then
            self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] = provider
        end
    end
end

function ad:getProvider(name)
    name = name or DEFAULT_PROVIDER_OBJECT_NAME
    if self.providers_[name] then
        return self.providers_[name]
    end
    printError("cc.ad:getProvider() - provider %s not exists", name)
end

function ad:stop(name)
    local provider = self:getProvider(name)
    if provider then
        provider:stop()
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
function ad:doCommand(args)
    local provider = self:getProvider(name)
    if provider then
        provider:doCommand(args)
    end
end

function ad:remove(name)
    local provider = self:getProvider(name)
    if provider then
        provider:remove()
    end
end

return ad
