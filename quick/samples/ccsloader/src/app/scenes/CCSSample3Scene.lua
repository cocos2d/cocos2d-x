
local CCSSample3Scene = class("CCSSample3Scene", function()
    return display.newScene("CCSSample3Scene")
end)

function CCSSample3Scene:ctor()
	app:createTitle(self, "CCS Sample3")
	app:createNextButton(self)

	cc.FileUtils:getInstance():addSearchPath("res/DemoMap/")
	app:loadCCSJsonFile(self, "DemoMap.ExportJson")

	local scrollView = cc.uiloader:seekNodeByName(self, "DragPanel")
	scrollView:onScroll(function(event)
		print("CCSSample3Scene scroll")
		-- dump(event, "event:")
	end)
end

return CCSSample3Scene
