
local CCSReader1Scene = class("CCSReader1Scene", function()
    return display.newScene("CCSReader1Scene")
end)

function CCSReader1Scene:ctor()
	app:createTitle(self, "CCS Reader1")
	app:createNextButton(self)

	ccs.GUIReader:getInstance():widgetFromJsonFile("DemoHead_UI/DemoHead_UI.ExportJson")
		:addTo(self)
end

return CCSReader1Scene
