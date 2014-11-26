
local net = require("framework.cc.net.init")
local TimerTestScene = game.createSceneClass("TimerTestScene")

function TimerTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "Timer"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function TimerTestScene:TimerTest()
    if self.timer_ then
        return
    end

	local Timer = require("framework.cc.utils.Timer")
    local appTimer = Timer.new()

    -- 响应 CITYHALL_UPGRADE_TIMER 事件
    local function onCityHallUpgradeTimer(event)
        if event.countdown > 0 then
            -- 倒计时还未结束，更新用户界面上显示的时间
            print("timer counting")
        else
            -- 倒计时已经结束，更新用户界面显示升级后的城防大厅
            print("timer over")
        end
    end

    -- 注册事件
    appTimer:addEventListener("CITYHALL_UPGRADE_TIMER", onCityHallUpgradeTimer)
    -- 城防大厅升级需要 3600 秒，每 30 秒更新一次界面显示
    appTimer:addCountdown("CITYHALL_UPGRADE_TIMER", 600, 10)

    appTimer:start()

    self.timer_ = appTimer
end

function TimerTestScene:onExit()
    if self.timer_ then
        self.timer_:stop()
    end
end

return TimerTestScene
