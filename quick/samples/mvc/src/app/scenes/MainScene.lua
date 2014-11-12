
local PlayDuelController = import("..controllers.PlayDuelController")

local MainScene = class("MainScene", function()
    return display.newScene("MainScene")
end)

function MainScene:ctor()
    display.newColorLayer(cc.c4b(255, 255, 255, 255)):addTo(self)

    -- add controller
    self:addChild(PlayDuelController.new())

    cc.ui.UIPushButton.new("Button01.png", {scale9 = true})
        :setButtonSize(200, 80)
        :setButtonLabel(cc.ui.UILabel.new({text = "REFRESH"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.1)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function()
            app:enterScene("MainScene", nil, "flipy")
        end)
        :pos(display.cx, display.bottom + 100)
        :addTo(self)
end

function MainScene:onEnter()
end

function MainScene:onExit()
end

return MainScene
