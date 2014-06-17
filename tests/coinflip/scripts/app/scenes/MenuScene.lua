
local AdBar = import("..views.AdBar")
local BubbleButton = import("..views.BubbleButton")

local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
    self.bg = display.newSprite("#MenuSceneBg.png", display.cx, display.cy)
    self:addChild(self.bg)

    self.adBar = AdBar.new()
    self:addChild(self.adBar)

    cc.ui.UIPushButton.new("#MenuSceneMoreGamesButton.png")
        :onButtonClicked(function(event)
            app:enterMoreGamesScene()
        end)
        :align(display.CENTER, display.left + 150, display.bottom + 300)
        :addTo(self)

    cc.ui.UIPushButton.new("#MenuSceneStartButton.png")
        :onButtonClicked(function(event)
            app:enterChooseLevelScene()
        end)
        :align(display.CENTER, display.right - 150, display.bottom + 300)
        :addTo(self)

    -- create menu
    -- self.moreGamesButton = BubbleButton.new({
    --     image = "#MenuSceneMoreGamesButton.png",
    --     x = display.left + 150,
    --     y = display.bottom + 300,
    --     sound = GAME_SFX.tapButton,
    --     prepare = function()
    --         self.menu:setEnabled(false)
    --     end,
    --     listener = function()
    --         app:enterMoreGamesScene()
    --     end,
    -- })

    -- self.startButton = BubbleButton.new({
    --     image = "#MenuSceneStartButton.png",
    --     x = display.right - 150,
    --     y = display.bottom + 300,
    --     sound = GAME_SFX.tapButton,
    --     prepare = function()
    --         self.menu:setEnabled(false)
    --     end,
    --     listener = function()
    --         app:enterChooseLevelScene()
    --     end,
    -- })

    -- self.menu = ui.newMenu({self.moreGamesButton, self.startButton})
    -- self:addChild(self.menu)
end

function MenuScene:onEnter()
end

return MenuScene
