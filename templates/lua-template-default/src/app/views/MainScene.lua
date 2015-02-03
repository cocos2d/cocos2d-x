
local MainScene = class("MainScene", cc.load("mvc").ViewBase)

function MainScene:onCreate()
    -- add background image
    display.newSprite("MainSceneBg.jpg")
        :move(display.center)
        :addTo(self)

    -- add play button
    local playButton = cc.MenuItemImage:create("PlayButton.png", "PlayButton.png")
        :onClicked(function()
            self:getApp():enterScene("PlayScene")
        end)
    cc.Menu:create(playButton)
        :move(display.cx, display.cy - 200)
        :addTo(self)
end

return MainScene
