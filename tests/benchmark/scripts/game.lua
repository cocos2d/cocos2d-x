
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")
    display.addSpriteFrames(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)

    game.benchmark()
end

function game.exit()
    os.exit()
end

function game.benchmark()
    local BenchmarkScene = require("scenes.BenchmarkScene")
    display.replaceScene(BenchmarkScene.new())
end
