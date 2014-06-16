
function __G__TRACKBACK__(errorMessage)
    print("----------------------------------------")
    print("LUA ERROR: " .. tostring(errorMessage) .. "\n")
    print(debug.traceback("", 2))
    print("----------------------------------------")
end

require("DeprecatedEnum.lua")
require("DeprecatedClass.lua")
require("Deprecated.lua")

require("app.MyApp").new():run()
