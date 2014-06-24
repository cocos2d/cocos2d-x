
local ProviderBase = class("ProviderBase")

local events = import("..events")

function ProviderBase:ctor(interface)
    self.interface_ = interface
end

function ProviderBase:callback_(event)
    local infos = string.split(event, "|")
    local evt = {
    provider = "share.UmengShare",
    type = infos[1],
    code = infos[2],
    shareSns = infos[3] }
    
    evt.name = events.LISTENER
    self.interface_:dispatchEvent(evt)

end

function ProviderBase:doCommand(args)
    if args.command == "setAppWebSite" then
        self:setAppWebSite(args.args.shareMedia, args.args.webSite)
    elseif args.command == "addPlatform" then
        self:addPlatform(args.args.shareMedia)
    elseif args.command == "removePlatform" then
        self:removePlatform(args.args.shareMedia)
    elseif args.command == "reorderPlatform" then
        self:reorderPlatform(args.args.shareMedia)
    elseif args.command == "shareText" then
        self:shareText(args.args.shareText)
    elseif args.command == "shareImg" then
        self:shareImg(args.args.shareText, args.args.shareImg)
    elseif args.command == "shareMusic" then
        self:shareMusic(args.args.shareText, args.args.shareMusic,
        		args.args.shareMusicImg, args.args.shareTitle, args.args.shareAuthor)
    elseif args.command == "shareVideo" then
    	self:shareMusic(args.args.shareText, args.args.shareVideo,
        		args.args.shareVideoImg, args.args.shareTitle)
    else
        printError("cc.share.umengshare.ProviderBase:doCommand() - invaild command:" .. args.command)
    end
end

return ProviderBase
