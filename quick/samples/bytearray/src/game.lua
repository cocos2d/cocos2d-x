require("config")
require("framework.init")

-- define global module
game = {}

function game.startup()
    game.showDemoScene()
end

function game.exit()
    --cc.Director:getInstance():endToLua()
    os.exit()
end

function game.showDemoScene()
    display.replaceScene(require("MainScene").new(), "fade", 0.6, display.COLOR_WHITE)
end
