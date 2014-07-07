local size = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

----------------------------------------
----Sprite3DBasicTest
----------------------------------------

local Sprite3DBasicTest = {}
Sprite3DBasicTest.__index = Sprite3DBasicTest

function Sprite3DBasicTest.onTouchesEnd(touches, event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        Sprite3DBasicTest.addNewSpriteWithCoords(Helper.currentLayer, location.x, location.y )
    end
end

function Sprite3DBasicTest.addNewSpriteWithCoords(parent,x,y)
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite:setScale(3.0)
    sprite:setTexture("Sprite3DTest/boss.png")

    parent:addChild(sprite)
    sprite:setPosition(cc.p(x,y))

    local random = math.random()
    local action = nil
    if random < 0.2 then
        action = cc.ScaleBy:create(3,2)
    elseif random < 0.4 then
        action = cc.RotateBy:create(3, 360)
    elseif random < 0.6 then
        action = cc.Blink:create(1, 3)
    elseif random < 0.8 then
        action = cc.TintBy:create(2, 0, -255, -255)
    else
        action  = cc.FadeOut:create(2)
    end

    local action_back = action:reverse()
    local seq = cc.Sequence:create(action, action_back)

    sprite:runAction(cc.RepeatForever:create(seq))
end

function Sprite3DBasicTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D")
    Helper.subtitleLabel:setString("Tap screen to add more sprites")

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(Sprite3DBasicTest.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    Sprite3DBasicTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end

----------------------------------------
----Sprite3DWithSkinTest
----------------------------------------
local Sprite3DWithSkinTest = {}
Sprite3DWithSkinTest.__index = Sprite3DWithSkinTest

function Sprite3DWithSkinTest.onTouchesEnd(touches, event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        Sprite3DWithSkinTest.addNewSpriteWithCoords(Helper.currentLayer, location.x, location.y )
    end
end

function Sprite3DWithSkinTest.addNewSpriteWithCoords(parent,x,y)
    local sprite = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    sprite:setScale(3)
    sprite:setRotation3D({x = 0, y = 180, z = 0})
    sprite:setPosition(cc.p(x, y))
    parent:addChild(sprite)

    local animation = cc.Animation3D:getOrCreate("Sprite3DTest/orc.c3b")
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        if math.random() < (1/3) then
            animate:setPlayBack(true)
        end

        local rand2 = math.random()
        if rand2 < 1/3 then
            animate:setSpeed(animate:getSpeed() + math.random())    
        elseif rand2 < 2/3 then
            animate:setSpeed(animate:getSpeed() - 0.5 *  math.random())
        end

        sprite:runAction(cc.RepeatForever:create(animate))
    end
end

function Sprite3DWithSkinTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D for animation from c3t")
    Helper.subtitleLabel:setString("Tap screen to add more sprite3D")

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(Sprite3DWithSkinTest.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    Sprite3DWithSkinTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end


----------------------------------------
----Animate3DTest
----------------------------------------
local State = 
{
    SWIMMING = 0,
    SWIMMING_TO_HURT = 1,
    HURT = 2,
    HURT_TO_SWIMMING = 3,
}

local Animate3DTest = {}
Animate3DTest.__index = Animate3DTest

function Animate3DTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, Animate3DTest)
    return target
end



function Animate3DTest:onEnter()

    self._hurt = nil
    self._swim = nil
    self._sprite = nil
    self._moveAction = nil
    self._transTime = 0.1
    self._elapseTransTime = 0.0

    local function renewCallBack()
        self._sprite:stopActionByTag(101)
        self._state = State.HURT_TO_SWIMMING
    end
    local function onTouchesEnd(touches, event )
        for i = 1,table.getn(touches) do
            local location = touches[i]:getLocation()
            if self._sprite ~= nil then
                local len = cc.pGetLength(cc.pSub(cc.p(self._sprite:getPosition()), location))
                if len < 40 then
                    if self._state == State.SWIMMING then
                        self._sprite:runAction(self._hurt)
                        local delay = cc.DelayTime:create(self._hurt:getDuration() - 0.1)
                        local seq = cc.Sequence:create(delay, cc.CallFunc:create(renewCallBack))
                        seq:setTag(101)
                        self._sprite:runAction(seq)
                        self._state = State.SWIMMING_TO_HURT
                    end
                    return
                end
            end
        end  
    end

    self:addSprite3D()

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local function update(dt)
        if self._state == State.HURT_TO_SWIMMING then
            self._elapseTransTime = self._elapseTransTime + dt
            local t = self._elapseTransTime / self._transTime
            
            if t >= 1.0 then
                t = 1.0
                self._sprite:stopAction(self._hurt)
                self._state = State.SWIMMING
            end
            self._swim:setWeight(t)
            self._hurt:setWeight(1.0 - t)
        elseif self._state == State.SWIMMING_TO_HURT then
            self._elapseTransTime = self._elapseTransTime + dt
            local t = self._elapseTransTime / self._transTime
            if t >= 1.0 then
                t = 1.0
                self._state = State.HURT
            end
            self._swim:setWeight(1.0 - t)
            self._hurt:setWeight(t)
        end
    end

    self:scheduleUpdateWithPriorityLua(update,0)
end

function Animate3DTest:onExit()
    self._moveAction:release()
    self._hurt:release()
    self._swim:release()
    self:unscheduleUpdate()
end

function Animate3DTest:addSprite3D()
    -- body
    local fileName = "Sprite3DTest/tortoise.c3b"
    local sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(0.1)
    local winSize = cc.Director:getInstance():getWinSize()
    sprite:setPosition(cc.p(winSize.width * 4.0 / 5.0, winSize.height / 2.0))
    self:addChild(sprite)

    self._sprite = sprite

    local animation = cc.Animation3D:getOrCreate(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation, 0.0, 1.933)
        sprite:runAction(cc.RepeatForever:create(animate))
        self._swim = animate
        self._swim:retain()
        self._hurt = cc.Animate3D:create(animation, 1.933, 2.8)
        self._hurt:retain()
        self._state = State.SWIMMING
    end

    self._moveAction = cc.MoveTo:create(4.0, cc.p(winSize.width / 5.0, winSize.height / 2.0))
    self._moveAction:retain()

    local function reachEndCallBack()
        self._sprite:stopActionByTag(100)
        local inverse = self._moveAction:reverse()
        inverse:retain()
        self._moveAction:release()
        self._moveAction = inverse
        local rot = cc.RotateBy:create(1.0, { x = 0.0, y = 180.0, z = 0.0})
        local seq = cc.Sequence:create(rot, self._moveAction, cc.CallFunc:create(reachEndCallBack))
        seq:setTag(100)
        self._sprite:runAction(seq)
    end

    local seq = cc.Sequence:create(self._moveAction, cc.CallFunc:create(reachEndCallBack))
    seq:setTag(100)
    sprite:runAction(seq)
end

function Animate3DTest.create()
    local layer =  Animate3DTest.extend(cc.Layer:create())

    if nil ~= layer then
        Helper.initWithLayer(layer)
        Helper.titleLabel:setString("Testing Animate3D")
        Helper.subtitleLabel:setString("Touch to beat the tortoise")

        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end


function Sprite3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Sprite3DBasicTest.create,
        Sprite3DWithSkinTest.create,
        Animate3DTest.create,
    }

    scene:addChild(Sprite3DBasicTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
