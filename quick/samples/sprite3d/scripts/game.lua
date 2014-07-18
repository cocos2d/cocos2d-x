
require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")
    display.addSpriteFrames(GAME_TEXTURE_DATA_FILENAME, GAME_TEXTURE_IMAGE_FILENAME)

    game.mainScene()
end

function game.exit()
    os.exit()
end

function game.mainScene()
    local BenchmarkScene = require("scenes.Sprite3DScene")
    display.replaceScene(BenchmarkScene.new())
end
