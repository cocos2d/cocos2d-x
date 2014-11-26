
local CCSReader3Scene = class("CCSReader3Scene", function()
    return display.newScene("CCSReader3Scene")
end)

function CCSReader3Scene:ctor()
	app:createTitle(self, "CCS Reader3")
	app:createNextButton(self)

	local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("DemoMap/DemoMap.ExportJson")
		:addTo(self)

	local scrollView = widget:getChildByName("DragPanel")
	scrollView:setDirection(ccui.ScrollViewDir.both)
	scrollView:addEventListener(function(sender, eventType)
		print("CCSSample2Scene scroll")
	end)
end

return CCSReader3Scene
