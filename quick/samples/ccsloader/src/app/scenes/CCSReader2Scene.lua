
local CCSReader2Scene = class("CCSReader2Scene", function()
    return display.newScene("CCSReader2Scene")
end)

function CCSReader2Scene:ctor()
	app:createTitle(self, "CCS Reader2")
	app:createNextButton(self)

	local widget = ccs.GUIReader:getInstance():widgetFromJsonFile("DemoLogin/DemoLogin.ExportJson")
		:addTo(self)

	local editBox = widget:getChildByName("name_TextField")
	editBox:addEventListener(function(editbox, eventType)
		print("CCSSample2Scene editbox input")
	end)
end

return CCSReader2Scene
