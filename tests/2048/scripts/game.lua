require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")

    game.enterMainScene()
end

function game.exit()
    os.exit()
end

function game.enterMainScene()
    game.mainScene = require("scenes.MainScene").new()
    display.replaceScene(game.mainScene, "fade", 0.6, display.COLOR_WHITE)
end
