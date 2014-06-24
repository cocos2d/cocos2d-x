
-- for CCLuaEngine
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: "..tostring(errorMessage).."\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

require("game")
game.startup()
