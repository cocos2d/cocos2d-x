
local CCSReader6Scene = class("CCSReader6Scene", function()
    return display.newScene("CCSReader6Scene")
end)

function CCSReader6Scene:ctor()
	app:createTitle(self, "CCS Reader6")
	app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/GameRPG/")
	ccs.SceneReader:getInstance()
		:createNodeWithSceneFile("publish/RPGGame.json")
		:addTo(self)
end

return CCSReader6Scene
