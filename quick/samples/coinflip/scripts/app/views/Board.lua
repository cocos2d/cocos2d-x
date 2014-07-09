
local Levels = import("..data.Levels")
local Coin   = import("..views.Coin")

local Board = class("Board", function()
    return display.newNode()
end)

local NODE_PADDING   = 100
local NODE_ZORDER    = 0

local COIN_ZORDER    = 1000

function Board:ctor(levelData)
    cc.GameObject.extend(self):addComponent("components.behavior.EventProtocol"):exportMethods()

    self.batch = display.newBatchNode(GAME_TEXTURE_IMAGE_FILENAME)
    self.batch:setPosition(display.cx, display.cy)
    self:addChild(self.batch)

    self.grid = clone(levelData.grid)
    self.rows = levelData.rows
    self.cols = levelData.cols
    self.coins = {}
    self.flipAnimationCount = 0

    local offsetX = -math.floor(NODE_PADDING * self.cols / 2) - NODE_PADDING / 2
    local offsetY = -math.floor(NODE_PADDING * self.rows / 2) - NODE_PADDING / 2
    -- create board, place all coins
    for row = 1, self.rows do
        local y = row * NODE_PADDING + offsetY
        for col = 1, self.cols do
            local x = col * NODE_PADDING + offsetX
            local nodeSprite = display.newSprite("#BoardNode.png", x, y)
            self.batch:addChild(nodeSprite, NODE_ZORDER)

            local node = self.grid[row][col]
            if node ~= Levels.NODE_IS_EMPTY then
                local coin = Coin.new(node)
                coin:setPosition(x, y)
                coin.row = row
                coin.col = col
                self.grid[row][col] = coin
                self.coins[#self.coins + 1] = coin
                self.batch:addChild(coin, COIN_ZORDER)
            end
        end
    end

    self:setNodeEventEnabled(true)
    self:setTouchEnabled(true)
    self:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)

end

function Board:checkLevelCompleted()
    local count = 0
    for _, coin in ipairs(self.coins) do
        if coin.isWhite then count = count + 1 end
    end
    if count == #self.coins then
        -- completed
        self:setTouchEnabled(false)
        self:dispatchEvent({name = "LEVEL_COMPLETED"})
    end
end

function Board:getCoin(row, col)
    if self.grid[row] then
        return self.grid[row][col]
    end
end

function Board:flipCoin(coin, includeNeighbour)
    if not coin or coin == Levels.NODE_IS_EMPTY then return end

    self.flipAnimationCount = self.flipAnimationCount + 1
    coin:flip(function()
        self.flipAnimationCount = self.flipAnimationCount - 1
        self.batch:reorderChild(coin, COIN_ZORDER)
        if self.flipAnimationCount == 0 then
            self:checkLevelCompleted()
        end
    end)
    if includeNeighbour then
        audio.playSound(GAME_SFX.flipCoin)
        self.batch:reorderChild(coin, COIN_ZORDER + 1)
        self:performWithDelay(function()
            self:flipCoin(self:getCoin(coin.row - 1, coin.col))
            self:flipCoin(self:getCoin(coin.row + 1, coin.col))
            self:flipCoin(self:getCoin(coin.row, coin.col - 1))
            self:flipCoin(self:getCoin(coin.row, coin.col + 1))
        end, 0.25)
    end
end

function Board:onTouch(event, x, y)
    if event ~= "began" or self.flipAnimationCount > 0 then return end

    local padding = NODE_PADDING / 2
    for _, coin in ipairs(self.coins) do
        local cx, cy = coin:getPosition()
        cx = cx + display.cx
        cy = cy + display.cy
        if x >= cx - padding
            and x <= cx + padding
            and y >= cy - padding
            and y <= cy + padding then
            self:flipCoin(coin, true)
            break
        end
    end
end

function Board:onEnter()
    self:setTouchEnabled(true)
end

function Board:onExit()
    self:removeAllEventListeners()
end

return Board
