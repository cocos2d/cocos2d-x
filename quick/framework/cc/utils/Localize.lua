
local Localize = {}

Localize.strings = {}

function Localize.loadStrings(strings)
    Localize.strings = strings
end

function Localize.query(key, default)
    if not default then default = key end
    local lang = device.language
    if not Localize.strings[lang] or not Localize.strings[lang][key] then return default end
    return Localize.strings[lang][key]
end

function Localize.filename(filenameOrigin)
    local fi = io.pathinfo(filenameOrigin)
    return fi.dirname .. fi.basename .. "_" .. device.language .. fi.extname
end

cc = cc or {}
cc.utils = cc.utils or {}
cc.utils.Localize = Localize

return Localize
