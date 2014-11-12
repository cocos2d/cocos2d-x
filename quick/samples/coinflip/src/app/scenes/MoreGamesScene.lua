
local AdBar = import("..views.AdBar")

local MoreGamesScene = class("MoreGamesScene", function()
    return display.newScene("MoreGamesScene")
end)

function MoreGamesScene:ctor()
    self.bg = display.newSprite("#MenuSceneBg.png", display.cx, display.cy)
    self:addChild(self.bg)

    self.adBar = AdBar.new()
    self:addChild(self.adBar)

    cc.ui.UIPushButton.new("#BackButton.png")
        :align(display.CENTER, display.right - 100, display.bottom + 120)
        :onButtonClicked(function()
            app:enterMenuScene()
        end)
        :addTo(self)
end

return MoreGamesScene
