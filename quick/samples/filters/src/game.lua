require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    cc.FileUtils:getInstance():addSearchPath("res/")

    game.enterMainScene()
end

function game.exit()
    --CCDirector:sharedDirector():endToLua()
    os.exit()
end

function game.enterMainScene()
    display.replaceScene(require("MainScene").new(), "fade", 0.6, display.COLOR_WHITE)
end
