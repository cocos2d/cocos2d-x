local size = cc.Director:getInstance():getWinSize()

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
    local sprite = cc.Sprite3D:create("Sprite3DTest/girl.c3t")
    sprite:setRotation3D({x = -90.0, y = 0.0, z = 0.0})
    sprite:setPosition(cc.p(x, y))
    parent:addChild(sprite)

    local animation = cc.Animation3D:getOrCreate("Sprite3DTest/girl.c3t")
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


function Sprite3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Sprite3DBasicTest.create,
        Sprite3DWithSkinTest.create,
    }

    scene:addChild(Sprite3DBasicTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
