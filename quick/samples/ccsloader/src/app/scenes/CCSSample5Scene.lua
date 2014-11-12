
local CCSSample5Scene = class("CCSSample5Scene", function()
    return display.newScene("CCSSample5Scene")
end)

function CCSSample5Scene:ctor()
	app:createTitle(self, "CCS Sample5")
	app:createNextButton(self)
	
	cc.FileUtils:getInstance():addSearchPath("res/GameFightScene/")
	app:loadCCSJsonFile(self, "publish/FightScene.json")

	-- "hero" 是结点名称
	-- 1 是 "hero"这个结点下的第一个组件
	local hero = cc.uiloader:seekComponents(self, "hero", 1)
	hero:getAnimation():play("attack")
end


return CCSSample5Scene
