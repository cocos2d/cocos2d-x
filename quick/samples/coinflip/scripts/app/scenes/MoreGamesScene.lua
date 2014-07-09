
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
    -- local backButton = ui.newImageMenuItem({
    --     image = "#BackButton.png",
    --     imageSelected = "#BackButtonSelected.png",
    --     x = display.right - 100,
    --     y = display.bottom + 120,
    --     sound = GAME_SFX.backButton,
    --     listener = function()
    --         app:enterMenuScene()
    --     end
    -- })

    -- local menu = ui.newMenu({backButton})
    -- self:addChild(menu)
end

return MoreGamesScene
