
local ProviderBase = class("ProviderBase")

local events = import("..events")

function ProviderBase:ctor(interface)
    self.interface_ = interface
end

function ProviderBase:doCommand(args)
    if args.command == "showFeedBack" then
        self:showFeedBack(args.args.appKey)
    elseif args.command == "checkReplies" then
        self:checkReplies(args.args.appKey)
    else
        printError("cc.share.umengfeedback.ProviderBase:doCommand() - invaild command:" .. args.command)
    end
end

return ProviderBase
