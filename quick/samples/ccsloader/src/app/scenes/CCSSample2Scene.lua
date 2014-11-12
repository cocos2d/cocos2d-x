
local CCSSample2Scene = class("CCSSample2Scene", function()
    return display.newScene("CCSSample2Scene")
end)

function CCSSample2Scene:ctor()
	app:createTitle(self, "CCS Sample2")
	app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/DemoLogin/")
	app:loadCCSJsonFile(self, "DemoLogin.ExportJson")

	-- register function on node
	-- path为传入除要结点node名字外的路径
	local ccsNode = self:getChildByTag(101)
	local loginNode = cc.uiloader:seekNodeByPath(ccsNode, "Panel/login_Button")
	loginNode:onButtonClicked(function(event)
		print("CCSSample2Scene login button clicked")
		-- dump(event, "login button:")
	end)

	local editBox = cc.uiloader:seekNodeByNameFast(ccsNode, "name_TextField")
	editBox:addEventListener(function(editbox, eventType)
		print("CCSSample2Scene editbox input")
	end)
end

return CCSSample2Scene
