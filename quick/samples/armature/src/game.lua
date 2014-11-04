
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")

    game.armatureSceneIdx = 1
    game.test()
end

function game.exit()
    os.exit()
end

function game.test()
    local newScene = require("scenes.ArmatureTestScene").new(game.armatureSceneIdx)
    display.replaceScene(newScene)
end

function game.nextTest()
	if game.armatureSceneIdx >= game.numArmatureScenes then
		game.armatureSceneIdx = 1
	else
		game.armatureSceneIdx = game.armatureSceneIdx + 1
	end
	game.test()
end

function game.prevTest()
	if game.armatureSceneIdx < 2 then
		game.armatureSceneIdx = game.numArmatureScenes
	else
		game.armatureSceneIdx = game.armatureSceneIdx - 1
	end
	game.test()
end

