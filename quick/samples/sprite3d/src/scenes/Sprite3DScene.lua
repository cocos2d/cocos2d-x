
local Sprite3DScene = class("Sprite3DScene", function()
    return display.newScene("Sprite3DScene")
end)

local random = math.random

function Sprite3DScene:ctor()
    self.layer = display.newNode()
    self.layer:setContentSize(cc.size(display.width, display.height))
    self:addChild(self.layer)

    local button = display.newSprite("#AddCoinButton.png", display.right - 100, display.bottom + 270)
    self:addChild(button)
    self.addCoinButtonBoundingBox = button:getBoundingBox()

    local button = display.newSprite("#RemoveCoinButton.png", display.right - 100, display.bottom + 100)
    self:addChild(button)
    self.removeCoinButtonBoundingBox = button:getBoundingBox()

    cc.ui.UIPushButton.new({normal = "#ExitButton.png"})
        :onButtonClicked(function()
            game.exit()
        end)
        :pos(display.right - 100, display.top - 100)
        :addTo(self)

    self.label = cc.ui.UILabel.new({
        UILabelType = 1,
        text = "00000",
        font = "UIFont.fnt",
        x = display.cx,
        y = display.top - 40,
    })
    self:addChild(self.label)

    self.coins = {}
    self.state = "IDLE"


    self.left   = display.left
    self.right  = display.right
    self.top    = display.top
    self.bottom = display.bottom
end

function Sprite3DScene:onTouch(event, x, y)
    if event == "began" then
        local p = cc.p(x, y)
        if cc.rectContainsPoint(self.addCoinButtonBoundingBox, p) then
            self.state = "ADD"
        elseif cc.rectContainsPoint(self.removeCoinButtonBoundingBox, p) then
            self.state = "REMOVE"
        else
            self.state = "IDLE"
        end
        return true
    elseif event ~= "moved" then
        self.state = "IDLE"
    end
end

function Sprite3DScene:addCoin()
    local sprite = cc.Sprite3D:create("boss.obj")
    sprite:setScale(10.0)
    sprite:setTexture("boss.png")
    sprite:setPosition(random(self.left, self.right), random(self.bottom, self.top))
    sprite:setRotation3D({x = random(360), y = random(360), z = random(360)})
    self:addChild(sprite, -1)

    local randomValue = random(0, 100)
    local action = nil
    if randomValue < 10 then
        action = cc.ScaleBy:create(3,2)
    elseif randomValue < 40 then
        action = cc.RotateBy:create(3, 360)
    elseif randomValue < 60 then
        action = cc.Blink:create(1, 3)
    elseif randomValue < 80 then
        action = cc.TintBy:create(2, 0, -255, -255)
    else
        action  = cc.FadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = cc.Sequence:create(action, action_back)

    sprite:runAction(cc.RepeatForever:create(seq))

    self.coins[#self.coins + 1] = sprite
    self.coinsCount = #self.coins
    self.label:setString(string.format("%05d", self.coinsCount))
end

function Sprite3DScene:removeCoin()
    local coin = self.coins[self.coinsCount]
    coin:removeFromParent()
    table.remove(self.coins, self.coinsCount)
    self.coinsCount = self.coinsCount - 1
    self.label:setString(string.format("%05d", self.coinsCount))
end

function Sprite3DScene:onEnterFrame(dt)
    if self.state == "ADD" then
        self:addCoin()
    elseif self.state == "REMOVE" and self.coinsCount > 0 then
        self:removeCoin()
    end
end

function Sprite3DScene:onEnter()
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, function(dt) self:onEnterFrame(dt) end)
    self:scheduleUpdate()
    self.layer:setTouchEnabled(true)
    self.layer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
end

return Sprite3DScene
