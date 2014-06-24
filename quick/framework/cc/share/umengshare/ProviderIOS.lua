
local ProviderBase = import(".ProviderBase")
local ProviderIOS = class("ProviderIOS", ProviderBase)

local SDK_CLASS_NAME = "UmengShareSDK"

function ProviderIOS:addListener()
    luaoc.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {listener = handler(self, self.callback_)})
end

function ProviderIOS:removeListener()
    luaoc.callStaticMethod(SDK_CLASS_NAME, "removeScriptListener")
end

function ProviderIOS:setAppWebSite()
	printInfo("cc.share.ProviderIOS not support setAppWebSite")
end

function ProviderIOS:addPlatform(shareMedia)
	local strMedia
	if type(shareMedia) == "table" then
		strMedia = table.concat(shareMedia, ",")
	elseif type(shareMedia) == "string" then
		strMedia = shareMedia
	else
		printError("cc.share.ProviderIOS:addPlatform - invalild args shareMedia")
		return
	end

	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "addPlatform", {shareMedias = strMedia})
	if not ok then
        printError("cc.share.ProviderIOS:addPlatform() - call addPlatform failed.")
    end
end

function ProviderIOS:removePlatform(shareMedia)
	local strMedia
	if type(shareMedia) == "table" then
		strMedia = table.concat(shareMedia, ",")
	elseif type(shareMedia) == "string" then
		strMedia = shareMedia
	else
		printError("cc.share.ProviderIOS:removePlatform - invalild args shareMedia")
		return
	end

	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "removePlatform", {shareMedias = strMedia})
	if not ok then
        printError("cc.share.ProviderIOS:removePlatform() - call removePlatform failed.")
    end
end

function ProviderIOS:reorderPlatform(shareMedia)
	local strMedia
	if type(shareMedia) == "table" then
		strMedia = table.concat(shareMedia, ",")
	elseif type(shareMedia) == "string" then
		strMedia = shareMedia
	else
		printError("cc.share.ProviderIOS:reorderPlatform - invalild args shareMedia")
		return
	end

	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "reorderPlatform", {shareMedias = strMedia})
	if not ok then
        printError("cc.share.ProviderIOS:reorderPlatform() - call reorderPlatform failed.")
    end
end

function ProviderIOS:shareText(text)
	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "share", {shareText = text})
	if not ok then
        printError("cc.share.ProviderIOS:shareText() - call shareText failed.")
    end
end

function ProviderIOS:shareImg(text, img)
	local ok = luaoc.callStaticMethod(SDK_CLASS_NAME, "share",
		{shareText = text, shareImage = img})
	if not ok then
        printError("cc.share.ProviderIOS:shareImg() - call shareImg failed.")
    end
end

function ProviderIOS:shareMusic()
	printInfo("cc.share.ProviderIOS not support shareMusic")
end

function ProviderIOS:shareVideo()
	printInfo("cc.share.ProviderIOS not support shareVideo")
end

return ProviderIOS
