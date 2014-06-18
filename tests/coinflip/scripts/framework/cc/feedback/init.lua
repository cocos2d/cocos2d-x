
local CURRENT_MODULE_NAME = ...

local providers = {
    "UmengFeedback"
}

for _, packageName in ipairs(providers) do
    local className = "feedback." .. packageName
    if not cc.Registry.exists(className) then
        cc.Registry.add(import("." .. packageName, CURRENT_MODULE_NAME), className)
    end
end

local feedback = class("cc.feedback")

local DEFAULT_PROVIDER_OBJECT_NAME = "feedback.default"

function feedback:ctor()
    cc(self):addComponent("components.behavior.EventProtocol"):exportMethods()
    self.events = import(".events", CURRENT_MODULE_NAME)
    self.providers_ = {}
end

function feedback:start(name)
    if not self.providers_[name] then
        local providerFactoryClass = cc.Registry.newObject(name)
        local provider = providerFactoryClass.getInstance(self)
        if not provider then
            printError("cc.feedback:start() - create feedback provider failed")
            return
        end

        self.providers_[name] = provider
        if not self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] then
            self.providers_[DEFAULT_PROVIDER_OBJECT_NAME] = provider
        end
    end
end

function feedback:stop(name)
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
function feedback:doCommand(args)
    local provider = self:getProvider(name)
    if provider then
        provider:doCommand(args)
    end
end

function feedback:getProvider(name)
    name = name or DEFAULT_PROVIDER_OBJECT_NAME
    if self.providers_[name] then
        return self.providers_[name]
    end
    printError("cc.feedback:getProvider() - provider %s not exists", name)
end

return feedback
