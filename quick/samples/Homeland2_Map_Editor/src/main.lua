
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

package.path = package.path .. ";src/"
cc.FileUtils:getInstance():setPopupNotify(false)
cc.FileUtils:getInstance():addSearchPath("res/")

require("config")
require("cocos.init")
require("framework.init")
require("utils")

display.addSpriteFrames("SheetMapBattle.plist", "SheetMapBattle.png")
display.addSpriteFrames("SheetEditor.plist", "SheetEditor.png")

display.replaceScene(require("editor.EditorScene").new())
