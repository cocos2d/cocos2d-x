
local CCSSample6Scene = class("CCSSample6Scene", function()
    return display.newScene("CCSSample6Scene")
end)

function CCSSample6Scene:ctor()
	app:createTitle(self, "CCS Sample6")
	app:createNextButton(self)
	
	cc.FileUtils:getInstance():addSearchPath("res/GameRPG/")
	app:loadCCSJsonFile(self, "publish/RPGGame.json")
end


return CCSSample6Scene
