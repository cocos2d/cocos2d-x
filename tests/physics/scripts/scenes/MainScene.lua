
local MainScene = class("MainScene", function()
    return display.newPhysicsScene("MainScene")
end)

local GRAVITY         = -200
local COIN_MASS       = 100
local COIN_RADIUS     = 46
local COIN_FRICTION   = 0.8
local COIN_ELASTICITY = 0.8
local WALL_THICKNESS  = 64
local WALL_FRICTION   = 1.0
local WALL_ELASTICITY = 0.5

function MainScene:ctor()
    -- create touch layer
    self.layer = display.newLayer()
    self.layer:addNodeEventListener(cc.NODE_TOUCH_EVENT, function(event)
        return self:onTouch(event.name, event.x, event.y)
    end)
    self:addChild(self.layer)

    -- create label
    self:addChild(ui.newTTFLabel({
        text = "TAP SCREEN",
        size = 32,
        x = display.cx,
        y = display.cy,
        align = ui.TEXT_ALIGN_CENTER
    }))

    -- create physics world
    self.world = self:getPhysicsWorld()
    self.world:setGravity(0, GRAVITY)

    -- add static body
    local leftWallSprite = display.newSprite("#Wall.png")
    leftWallSprite:setScaleY(display.height / WALL_THICKNESS)
    self:addChild(leftWallSprite)
    local leftWallBody = self.world:createBoxBody(0, WALL_THICKNESS, display.height)
    leftWallBody:setFriction(WALL_FRICTION)
    leftWallBody:setElasticity(WALL_ELASTICITY)
    leftWallBody:bind(leftWallSprite)
    leftWallBody:setPosition(display.left + WALL_THICKNESS / 2, display.cy + WALL_THICKNESS)

    local rightWallSprite = display.newSprite("#Wall.png")
    rightWallSprite:setScaleY(display.height / WALL_THICKNESS)
    self:addChild(rightWallSprite)
    local rightWallBody = self.world:createBoxBody(0, WALL_THICKNESS, display.height)
    rightWallBody:setFriction(WALL_FRICTION)
    rightWallBody:setElasticity(WALL_ELASTICITY)
    rightWallBody:bind(rightWallSprite)
    rightWallBody:setPosition(display.right - WALL_THICKNESS / 2, display.cy + WALL_THICKNESS)

    local bottomWallSprite = display.newSprite("#Wall.png")
    bottomWallSprite:setScaleX(display.width / WALL_THICKNESS)
    self:addChild(bottomWallSprite)
    local bottomWallBody = self.world:createBoxBody(0, display.width, WALL_THICKNESS)
    bottomWallBody:setFriction(WALL_FRICTION)
    bottomWallBody:setElasticity(WALL_ELASTICITY)
    bottomWallBody:bind(bottomWallSprite)
    bottomWallBody:setPosition(display.cx, display.bottom + WALL_THICKNESS / 2)

    -- add debug node
    self.worldDebug = self.world:createDebugNode()
    self:addChild(self.worldDebug)
end

function MainScene:createCoin(x, y)
    -- add sprite to scene
    local coinSprite = display.newSprite("#Coin.png")
    self:addChild(coinSprite)

    -- create body
    local coinBody = self.world:createCircleBody(COIN_MASS, COIN_RADIUS)
    coinBody:setFriction(COIN_FRICTION)
    coinBody:setElasticity(COIN_ELASTICITY)
    -- binding sprite to body
    coinBody:bind(coinSprite)
    -- set body position
    coinBody:setPosition(x, y)
end

function MainScene:onTouch(event, x, y)
    if event == "began" then
        self:createCoin(x, y)
    end
end

function MainScene:onEnter()
    self.layer:setTouchEnabled(true)
    -- make world running
    self.world:start()
end

return MainScene
