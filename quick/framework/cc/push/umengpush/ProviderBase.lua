
local ProviderBase = class("ProviderBase")

local events = import("..events")

function ProviderBase:ctor(interface)
    self.interface_ = interface
end

function ProviderBase:callback_(event)
	printInfo("cc.push.umengush.ProviderBase:callback() - event:" .. event)

    local infos = string.split(event, "|")
    local evt = {
    	provider = "push.UmengPush",
    	command = infos[1]}

    if evt.command == "startPush" then
        evt.code = infos[2]
    elseif evt.command == "stopPush" then
        evt.code = infos[2]
    elseif evt.command == "setAlias" then
        evt.code = infos[2]
    elseif evt.command == "delAlias" then
        evt.code = infos[2]
    elseif evt.command == "setTags" then
        evt.code = infos[2]
    elseif evt.command == "delTags" then
        evt.code = infos[2]
    elseif evt.command == "customMsg" then
    	evt.text = infos[2]
    elseif evt.command == "notifyMsg" then
    	evt.text = infos[2]
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
        local val = string.split(args.args, ",")
        dump(val, "args")
        self:setAlias(val[1], val[2])
    elseif args.command == "delAlias" then
        local val = string.split(args.args, ",")
        self:delAlias(val[1], val[2])
    elseif args.command == "setTags" then
        if type(args.args) ~= "table" then
            printError("cc.push.umengpush.ProviderBase:doCommand() - args must be table")
            return 
        end
        self:setTags(args.args)
    elseif args.command == "delTags" then
        if type(args.args) ~= "table" then
            printError("cc.push.umengpush.ProviderBase:doCommand() - args must be table")
            return 
        end
        self:delTags(args.args)
    else
        printError("cc.push.umengpush.ProviderBase:doCommand() - invaild command:" .. args.command)
    end
end

return ProviderBase
