
local ProviderBase = class("ProviderBase")
local errors = import("..errors")
local events = import("..events")

function ProviderBase:ctor(interface)
	self.interface_ = interface
end

function ProviderBase:callback_(event)
	local typeName, status, dlStatus, file = unpack(string.split(event, "|"))
	local evt = {}
	evt.type = typeName
	if status == "haveUpdate" then
		evt.code = errors.HAVE_UPDATE
	elseif status == "noUpdate" then
		evt.code = errors.NO_UPDATE
	elseif status == "noWifi" then
		evt.code = errors.NO_WIFI
	elseif status == "timeout" then
		evt.code = errors.TIME_OUT
	elseif status == "userUpdate" then
		evt.code = errors.USER_UPDATE
	elseif status == "userIgnore" then
		evt.code = errors.USER_IGNORE
	elseif status == "userLater" then
		evt.code = errors.USER_LATER
	elseif status == "start" then
		evt.code = errors.DOWNLOAD_START
	elseif status == "downloading" then
		evt.code = errors.DOWNLOADING
		evt.downloadProgress = tonumber(dlStatus)
	elseif status == "end" then
		evt.code = errors.DOWNLOAD_END
		if dlStatus == "fail" then
			evt.dlCode = errors.DOWNLOAD_FAIL
		elseif dlStatus == "sucess" then
			evt.dlCode = errors.DOWNLOAD_SUC
			evt.file = file
		elseif dlStatus == "needRestart" then
			evt.dlCode = errors.DOWNLOAD_NEED_RESTART
		end
	end
	evt.name = events.LISTENER
	self.interface_:dispatchEvent(evt)
end

function ProviderBase:doCommand(args)
	if args.command == "update" then
		self:update()
	elseif args.command == "forceUpdate" then
		self:forceUpdate()
	elseif args.command == "silentUpdate" then
		self:silentUpdate()
	end
end

return ProviderBase
