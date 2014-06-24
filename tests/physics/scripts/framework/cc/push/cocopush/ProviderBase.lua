
local ProviderBase = class("ProviderBase")

local events = import("..events")

function ProviderBase:ctor(interface)
    self.interface_ = interface
end

function ProviderBase:callback_(event)
    local infos = string.split(event, "|")
    local evt = {
    provider = "push.CocoPush",
    type = infos[1],
    code = infos[2] }
    if infos[3] then
        evt.sucTags = string.split(infos[3], ",")
    end
    if infos[4] then
        evt.failTags = string.split(infos[4], ",")
    end
    
    evt.name = events.LISTENER
    self.interface_:dispatchEvent(evt)

end

function ProviderBase:doCommand(args)
    if args.command == "startPush" then
        self:startPush()
    elseif args.command == "stopPush" then
        self:stopPush()
    elseif args.command == "setAlias" then
        self:setAlias(args.args)
    elseif args.command == "delAlias" then
        self:delAlias(args.args)
    elseif args.command == "setTags" then
        if type(args.args) ~= "table" then
            printError("cc.push.cocopush.ProviderBase:doCommand() - args must be table")
            return 
        end
        self:setTags(args.args)
    elseif args.command == "delTags" then
        if type(args.args) ~= "table" then
            printError("cc.push.cocopush.ProviderBase:doCommand() - args must be table")
            return 
        end
        self:delTags(args.args)
    else
        printError("cc.push.cocopush.ProviderBase:doCommand() - invaild command:" .. args.command)
    end
end

return ProviderBase