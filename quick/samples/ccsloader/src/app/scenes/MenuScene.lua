
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	app:createTitle(self, "Select Loader")

	cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
		:setButtonSize(200, 60)
		:setButtonLabel(cc.ui.UILabel.new({text = "Use CCSLoader"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.2)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function(event)
            app:enterNextScene()
        end)
        :align(display.CENTER, display.cx, display.cy + 40)
        :addTo(self)

    cc.ui.UIPushButton.new("GreenButton.png", {scale9 = true})
    	:setButtonSize(200, 60)
		:setButtonLabel(cc.ui.UILabel.new({text = "Use CCSReader"}))
        :onButtonPressed(function(event)
            event.target:setScale(1.2)
        end)
        :onButtonRelease(function(event)
            event.target:setScale(1.0)
        end)
        :onButtonClicked(function(event)
        	app.currentSceneName_ = "CCSSample6Scene"
            app:enterNextScene(true)
        end)
        :align(display.CENTER, display.cx, display.cy - 40)
        :addTo(self)

end

function MenuScene:onEnter()
end

return MenuScene
