
-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    CCLuaLog("----------------------------------------")
    CCLuaLog("LUA ERROR: "..tostring(errorMessage).."\n")
    CCLuaLog(debug.traceback("", 2))
    CCLuaLog("----------------------------------------")
end

cc.FileUtils:getInstance():addSearchPath("res/")

xpcall(function()
    require("config")
    require("cocos.init")
    require("framework.init")
    require("utils")

    display.addSpriteFrames("SheetMapBattle.plist", "SheetMapBattle.png")
    display.addSpriteFrames("SheetEditor.plist", "SheetEditor.png")

    display.replaceScene(require("editor.EditorScene").new())
end, __G__TRACKBACK__)
