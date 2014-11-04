
local MenuScene = class("MenuScene", function()
    return display.newScene("MenuScene")
end)

function MenuScene:ctor()
	app:createTitle(self, "CCS Sample1")
	-- app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/Test_1/")
	app:loadCCSJsonFile(self, "Test_1.Exportjson")
	-- display.addSpriteFrames("ui/ui_main/ui_main.plist", "ui/ui_main/ui_main.png")
	-- local sp = display.newSprite("#shouye_userinfo.png")
	-- sp:setPosition(300, 400)
	-- self:addChild(sp)
end

function MenuScene:onEnter()
end

return MenuScene
