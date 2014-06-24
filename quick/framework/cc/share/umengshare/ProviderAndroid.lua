
local ProviderBase = import(".ProviderBase")
local ProviderAndroid = class("ProviderAndroid", ProviderBase)

local SDK_CLASS_NAME = "com.quick2dx.sdk.UmengShareSDK"


function ProviderAndroid:addListener()
	luaj.callStaticMethod(SDK_CLASS_NAME, "addScriptListener", {handler(self, self.callback_)})
end

function ProviderAndroid:removeListener()
	luaj.callStaticMethod(SDK_CLASS_NAME, "removeScriptListener")
end

function ProviderAndroid:setAppWebSite(shareMedia, webSite)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "setAppWebSite", {shareMedia, webSite})
    if not ok then
        printError("cc.share.ProviderAndroid:setAppWebSite() - call setAppWebSite failed.")
        return false
    end

    return true
end

function ProviderAndroid:addPlatform(shareMedia)
    local strMedia
    if type(shareMedia) == "table" then
        strMedia = table.concat(shareMedia, ",")
    elseif type(shareMedia) == "string" then
        strMedia = shareMedia
    else
        printError("cc.share.ProviderAndroid:addPlatform - invalild args shareMedia")
        return
    end

    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "addPlatform", {strMedia})
    if not ok then
        printError("cc.share.ProviderAndroid:addPlatform() - call addPlatform failed.")
        return false
    end

    return true
end

function ProviderAndroid:removePlatform(shareMedia)
    local strMedia
    if type(shareMedia) == "table" then
        strMedia = table.concat(shareMedia, ",")
    elseif type(shareMedia) == "string" then
        strMedia = shareMedia
    else
        printError("cc.share.ProviderAndroid:removePlatform - invalild args shareMedia")
        return
    end

	local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "removePlatform", {strMedia})
    if not ok then
        printError("cc.share.ProviderAndroid:removePlatform() - call removePlatform failed.")
        return false
    end

    return true
end

function ProviderAndroid:reorderPlatform(shareMedia)
    local strMedia
    if type(shareMedia) == "table" then
        strMedia = table.concat(shareMedia, ",")
    elseif type(shareMedia) == "string" then
        strMedia = shareMedia
    else
        printError("cc.share.ProviderAndroid:reorderPlatform - invalild args shareMedia")
        return
    end

    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "reorderPlatform", {strMedia})
    if not ok then
        printError("cc.share.ProviderAndroid:reorderPlatform() - call reorderPlatform failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareText(text)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "shareText", {text})
    if not ok then
        printError("cc.push.ProviderAndroid:shareText() - call shareText failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareImg(text, img)
    local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "shareImg", {text, img})
    if not ok then
        printError("cc.push.ProviderAndroid:shareImg() - call shareImg failed.")
        return false
    end

    return true
end

function ProviderAndroid:shareMusic(text, music, musicImg, title, author)
    printInfo("cc.share.ProviderAndroid not support shareMusic")
    -- local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "shareMusic", {text, music, musicImg, title, author})
    -- if not ok then
    --     printError("cc.push.ProviderAndroid:shareMusic() - call shareMusic failed.")
    --     return false
    -- end

    -- return true
end

function ProviderAndroid:shareVideo(text, video, videoImg, title)
    printInfo("cc.share.ProviderAndroid not support shareVideo")
    -- local ok = luaj.callStaticMethod(SDK_CLASS_NAME, "shareVideo", {text, video, videoImg, title})
    -- if not ok then
    --     printError("cc.push.ProviderAndroid:shareVideo() - call shareVideo failed.")
    --     return false
    -- end

    -- return true
end

return ProviderAndroid
