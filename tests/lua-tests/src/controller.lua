local currPlatform = cc.Application:getInstance():getTargetPlatform()
cc.PLATFORM_OS_OHOS = 12
if (cc.PLATFORM_OS_OHOS == currPlatform) then
    -- jit off
    local jit = require("jit")
    jit.off()
end
-- avoid memory leak
collectgarbage("setpause", 100) 
collectgarbage("setstepmul", 5000)
	
require "src/mainMenu"
----------------


-- run
local scene = cc.Scene:create()
scene:addChild(CreateTestMenu())
cc.Director:getInstance():runWithScene(scene)
