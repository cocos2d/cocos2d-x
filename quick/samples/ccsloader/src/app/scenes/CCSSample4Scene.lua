
local CCSSample4Scene = class("CCSSample4Scene", function()
    return display.newScene("CCSSample4Scene")
end)

function CCSSample4Scene:ctor()
	app:createTitle(self, "CCS Sample4")
	app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/DemoShop/")
	app:loadCCSJsonFile(self, "DemoShop.ExportJson")
	local shopView = cc.uiloader:seekNodeByTag(self, 66)
	shopView:onScroll(function(event)
		print("CCSSample4Scene shop scroll")
		-- dump(event, "event:")
	end)

	local rankView = cc.uiloader:seekNodeByName(self, "ranking_ScrollView")
	rankView:onScroll(function(event)
		print("CCSSample4Scene rank scroll")
		-- dump(event, "event:")
	end)

	local buttonView = cc.uiloader:seekNodeByTag(self, 13)
	buttonView:onButtonClicked(function(event)
		if not rankView:isItemInViewRect(buttonView) then
			print("CCSSample4Scene button not in view rect")
			return
		end

		print("CCSSample4Scene button click")
		-- dump(event, "event:")
	end)
end

return CCSSample4Scene
