
local MainScene = class("MainScene", function()
    return display.newPhysicsScene("MainScene")
    -- return display.newScene("MainScene")
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
    cc.ui.UILabel.new({text = "TAP SCREEN", size = 32, color = display.COLOR_WHITE})
        :align(display.CENTER, display.cx, display.cy)
        :addTo(self)

    -- create physics world
    self.world = self:getPhysicsWorld()
    self.world:setGravity(cc.p(0, GRAVITY))

    local leftWallSprite = display.newSprite("#Wall.png")
    leftWallSprite:setScaleY(display.height / WALL_THICKNESS)
    leftWallSprite:setPosition(display.left + WALL_THICKNESS / 2, display.cy + WALL_THICKNESS)
    self:addChild(leftWallSprite)

    local rightWallSprite = display.newSprite("#Wall.png")
    rightWallSprite:setScaleY(display.height / WALL_THICKNESS)
    rightWallSprite:setPosition(display.right - WALL_THICKNESS / 2, display.cy + WALL_THICKNESS)
    self:addChild(rightWallSprite)

    local bottomWallSprite = display.newSprite("#Wall.png")
    bottomWallSprite:setScaleX(display.width / WALL_THICKNESS)
    bottomWallSprite:setPosition(display.cx, display.bottom + WALL_THICKNESS / 2)
    self:addChild(bottomWallSprite)

    local wallBox = display.newNode()
    wallBox:setAnchorPoint(cc.p(0.5, 0.5))
    wallBox:setPhysicsBody(
        cc.PhysicsBody:createEdgeBox(cc.size(display.width - WALL_THICKNESS*2, display.height - WALL_THICKNESS)))
    wallBox:setPosition(display.cx, display.height/2 + WALL_THICKNESS/2)
    self:addChild(wallBox)

    -- add debug node
    -- self:getPhysicsWorld():setDebugDrawMask(
    --     true and cc.PhysicsWorld.DEBUGDRAW_ALL or cc.PhysicsWorld.DEBUGDRAW_NONE)
end

function MainScene:createCoin(x, y)
    -- add sprite to scene
    local coinSprite = display.newSprite("#Coin.png")
    self:addChild(coinSprite)
    local coinBody = cc.PhysicsBody:createCircle(COIN_RADIUS,
        cc.PhysicsMaterial(COIN_RADIUS, COIN_FRICTION, COIN_ELASTICITY))
    coinBody:setMass(COIN_MASS)
    coinSprite:setPhysicsBody(coinBody)
    coinSprite:setPosition(x, y)
end

function MainScene:onTouch(event, x, y)
    if event == "began" then
        self:createCoin(x, y)
    end
end

function MainScene:onEnter()
    self.layer:setTouchEnabled(true)
    self:addNodeEventListener(cc.NODE_ENTER_FRAME_EVENT, handler(self, self.onEnterFrame))
    self:scheduleUpdate()
end

function MainScene:onEnterFrame(dt)
    -- body
end

return MainScene
