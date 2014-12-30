
function tolua.cloneTable(src)
	if type(src)~="table" then
		return nil
	end

	local dest = {}
    for k, v in pairs(src) do
        dest[k] = v
    end

    local mt = getmetatable(src)
    if mt then
	    setmetatable(dest, mt)
    end

    return dest
end

if CCPoint then
	tolua.default_gc_classes__ = {
        -- "CCAtlasNode",
        -- "ccBezierConfig",
        -- "ccBlendFunc",
        -- "CCBool",
        -- "CCCamera",
        "ccColor3B",
        "ccColor4B",
        "ccColor4F",
        -- "CCDouble",
        -- "CCFloat",
        -- "ccFontDefinition",
        -- "CCImage",
        -- "CCInteger",
        -- "CCLabelBMFont",
        -- "CCLabelTTF",
        -- "CCParticleSystemQuad",
		"CCPoint",
        "CCRect",
        -- "CCScrollView",
		"CCSize",
        -- "CCTableView",
        -- "ccTexParams",
        -- "CCTileMapAtlas",
        -- "CCTMXLayer",
        -- "CCTMXLayerInfo",
        -- "CCTMXMapInfo",
        -- "CCTMXTilesetInfo",
        -- "cc_timeval",
        -- "HSV",
        -- "RGBA",
	}
else
	tolua.default_gc_classes__ = {
	}
end

function tolua.fullgc(classes)
    collectgarbage("collect")

	if classes == nil then
		classes = tolua.default_gc_classes__
	elseif type(classes) == "string" then
		classes = {classes}
	elseif type(classes) ~= "table" then
		classes = tolua.default_gc_classes__
	end

    local o = tolua.getregval("tolua_gc")
    local t = tolua.cloneTable(o)
    if t then
	    tolua.setregval("tolua_gc", t)
    end

    for i,v in ipairs(classes) do
    	o =  tolua.getubox(v)
    	t = tolua.cloneTable(o)
    	if o then
    		tolua.setubox(v, t)
    	end
    end

    o = nil
    t = nil

    collectgarbage("collect")
end