-- jit off
local currPlatform = cc.Application:getInstance():getTargetPlatform()
cc.PLATFORM_OS_OHOS = 12
if (cc.PLATFORM_OS_OHOS == currPlatform) then
    -- jit off
    local jit = require("jit")
    jit.off()
end

cc.FileUtils:getInstance():setPopupNotify(false)

require "config"
require "cocos.init"

local function main()
    require("app.MyApp"):create():run()
end

local status, msg = xpcall(main, __G__TRACKBACK__)
if not status then
    print(msg)
end
