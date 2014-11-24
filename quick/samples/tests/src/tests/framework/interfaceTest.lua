
local InterfaceTestScene = game.createSceneClass("EventTestScene")

function InterfaceTestScene:ctor()
    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "register",
        "modebase"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function InterfaceTestScene:registerTest()
	local register = require("framework.cc.Registry")

	local eventProtocol = register.newObject("components.behavior.EventProtocol")
	if not eventProtocol then
		printError("ERROR some thing wrong please check Register")
	end
	register.setObject(eventProtocol, "cryptoTest1")
	if not register.isObjectExists("cryptoTest1") then
		printError("ERROR some thing wrong please check Register")
	end
	register.getObject("cryptoTest1")
	register.removeObject("cryptoTest1")
	if register.isObjectExists("cryptoTest1") then
		printError("ERROR some thing wrong please check Register")
	end

	if not register.exists("components.behavior.EventProtocol") then
		printError("ERROR some thing wrong please check Register")
	end

end

function InterfaceTestScene:modebaseTest()
	local mvcBase = require("framework.cc.mvc.ModelBase")
end

return InterfaceTestScene
