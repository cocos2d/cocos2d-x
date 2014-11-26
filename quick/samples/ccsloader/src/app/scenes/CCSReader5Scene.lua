
local CCSReader5Scene = class("CCSReader5Scene", function()
    return display.newScene("CCSReader5Scene")
end)

function CCSReader5Scene:ctor()
	app:createTitle(self, "CCS Reader5")
	app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/GameFightScene/")
	ccs.SceneReader:getInstance()
		:createNodeWithSceneFile("publish/FightScene.json")
		:addTo(self)
end

return CCSReader5Scene
