
local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    local items = {
        "framework.helper",
        "framework.native",
        "framework.display",
        "framework.crypto",
        "framework.network",
        "framework.luabinding",
        "framework.event",
        "framework.interface",
        "framework.socketTcp",
        "framework.timer",
        "framework.gamestate",
        "framework.transition",
        "framework.nvgdrawnode",
        "framework.clone"
    }

    self:addChild(game.createMenu(items, handler(self, self.openTest)))

    -- local layer = display.newLayer()
    -- self:addChild(layer)

    -- layer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
    --     -- event.name 是触摸事件的状态：began, moved, ended, cancelled
    --     -- event.x, event.y 是触摸点当前位置
    --     -- event.prevX, event.prevY 是触摸点之前的位置
    --     local label = string.format("sprite: %s x,y: %0.2f, %0.2f", event.name, event.x, event.y)
    --     print(label)
    --     -- self.sprite.label:setString(label)

    --     -- 返回 true 表示要响应该触摸事件，并继续接收该触摸事件的状态变化
    --     return true
    -- end)
end

function MainScene:openTest(name)
    display.replaceScene(require("tests." .. name .. "Test").new(), "random", 1)
end

function MainScene:onEnter()
end

return MainScene
