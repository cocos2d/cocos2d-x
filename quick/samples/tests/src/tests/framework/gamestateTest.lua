

local gameState = require("framework.cc.utils.GameState")
local GameStateTestScene = game.createSceneClass("GameStateTestScene")

function GameStateTestScene:ctor()
    cc.FileUtils:getInstance():addSearchPath("src/")

    self:prepare({
        description = "Please run server listen on 127.0.0.1:8080"
    })

    local items = {
        "Load",
        "Save"
    }
    self:addChild(game.createMenu(items, handler(self, self.runTest)))

    self:init()
end

function GameStateTestScene:init()
	local stateListener = function(event)
		if event.errorCode then
			print("ERROR, load:" .. event.errorCode)
			return
		end

		if "load" == event.name then
			local str = crypto.decryptXXTEA(event.values.data, "scertKey")
            local gameData = json.decode(str)
            dump(gameData, "gameData:")
		elseif "save" == event.name then
			local str = json.encode(event.values)
            if str then
                str = crypto.encryptXXTEA(str, "scertKey")
                returnValue = {data = str}
            else
            	print("ERROR, encode fail")
                return
            end

			return {data = str}
		end
	end

	gameState.init(stateListener, "gameState.dat", "keyHTL")
end

function GameStateTestScene:LoadTest()
	gameState.load()
end

function GameStateTestScene:SaveTest()
	local data = {
		appName = "这是游戏名",
		description = "这是一个Quick制作的游戏",
		gate = 2, --已玩到第二关
		topScore = 15862, --玩家达到的最高分值
	}

	gameState.save(data)
end

return GameStateTestScene
