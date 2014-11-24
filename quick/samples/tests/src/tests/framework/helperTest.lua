
local HelperTestScene = game.createSceneClass("HelperTestScene")

function HelperTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "Please check console output"
    })

    local items = {
        "getFileData",
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))
end

function HelperTestScene:getFileDataTest()
    print(cc.HelperFunc:getFileData("config.lua"))
end

return HelperTestScene
