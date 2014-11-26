
local CCSReader4Scene = class("CCSReader4Scene", function()
    return display.newScene("CCSReader4Scene")
end)

function CCSReader4Scene:ctor()
	app:createTitle(self, "CCS Reader4")
	app:createNextButton(self)

	ccs.GUIReader:getInstance():widgetFromJsonFile("DemoShop/DemoShop.ExportJson")
		:addTo(self)
end

return CCSReader4Scene
