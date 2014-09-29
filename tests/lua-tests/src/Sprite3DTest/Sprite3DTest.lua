require "OpenglConstants"

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
----Sprite3DHitTest
----------------------------------------

local Sprite3DHitTest = {}
Sprite3DHitTest.__index = Sprite3DHitTest

function Sprite3DHitTest.addNewSpriteWithCoords(parent,x,y)
    local sprite1 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite1:setScale(4.0)
    sprite1:setTexture("Sprite3DTest/boss.png")
    sprite1:setPosition(cc.p(x, y))
    sprite1:runAction(cc.RepeatForever:create(cc.RotateBy:create(3, 360)))
    parent:addChild(sprite1)

    local sprite2 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite2:setScale(4.0)
    sprite2:setTexture("Sprite3DTest/boss.png")
    sprite2:setPosition(cc.p(x, y))
    sprite2:setAnchorPoint(cc.p(0.5, 0.5))
    sprite2:runAction(cc.RepeatForever:create(cc.RotateBy:create(3, -360)))
    parent:addChild(sprite2)

    local function onTouchBegan(touch, event)
        local target = event:getCurrentTarget()
        local rect = target:getBoundingBox()
        if cc.rectContainsPoint(rect, touch:getLocation()) then
            target:setOpacity(100)
            return true
        end	
        return false
    end

    local function onTouchMoved(touch, event)
        local target = event:getCurrentTarget()
        target:setPosition(cc.p(target:getPositionX() + touch:getDelta().x, target:getPositionY() + touch:getDelta().y))
    end

    local function onTouchEnded(touch, event)
        local target = event:getCurrentTarget()
        target:setOpacity(255)
    end

    local listener1 = cc.EventListenerTouchOneByOne:create()
    listener1:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    listener1:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
    listener1:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)

    local listener2 = cc.EventListenerTouchOneByOne:create()
    listener2:registerScriptHandler(onTouchBegan, cc.Handler.EVENT_TOUCH_BEGAN)
    listener2:registerScriptHandler(onTouchMoved, cc.Handler.EVENT_TOUCH_MOVED)
    listener2:registerScriptHandler(onTouchEnded, cc.Handler.EVENT_TOUCH_ENDED)
    local eventDispatcher = parent:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener1, sprite1)
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener2, sprite2)
end

function Sprite3DHitTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D Touch in 2D")
    Helper.subtitleLabel:setString("Tap Sprite3D and Drag")

    Sprite3DHitTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
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

    local animation = cc.Animation3D:create("Sprite3DTest/orc.c3b")
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        local inverse = false
        if math.random() == 0 then
            inverse = true
        end

        local rand2 = math.random()
        local speed = 1.0

        if rand2 < 1/3 then
            speed = animate:getSpeed() + math.random()  
        elseif rand2 < 2/3 then
            speed = animate:getSpeed() - 0.5 *  math.random()
        end

        if inverse then
            animate:setSpeed(-speed)
        else
            animate:setSpeed(speed)
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

    local animation = cc.Animation3D:create(fileName)
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

----------------------------------------
----Sprite3DEffectTest
----------------------------------------

local Sprite3DEffectTest = {}
Sprite3DEffectTest.__index = Sprite3DEffectTest

function Sprite3DEffectTest.onTouchesEnd(touches, event)
    for i = 1,table.getn(touches) do
        local location = touches[i]:getLocation()
        Sprite3DEffectTest.addNewSpriteWithCoords(Helper.currentLayer, location.x, location.y )
    end
end

function Sprite3DEffectTest.addNewSpriteWithCoords(parent,x,y)
    local sprite = cc.EffectSprite3D:createFromObjFileAndTexture("Sprite3DTest/boss1.obj", "Sprite3DTest/boss.png")
    local effect = cc.Effect3DOutline:create()
    sprite:addEffect(effect, -1)
    effect:setOutlineColor({x = 1, y = 0, z = 0})
    effect:setOutlineWidth(0.01)

    local effect2 = cc.Effect3DOutline:create()
    sprite:addEffect(effect2, -2)
    effect2:setOutlineColor({x = 1, y = 1, z = 0})
    effect2:setOutlineWidth(0.02)

    sprite:setScale(6.0)
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

function Sprite3DEffectTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D")
    Helper.subtitleLabel:setString("Sprite3d with effects")

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(Sprite3DEffectTest.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    Sprite3DEffectTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end

----------------------------------------
----AttachmentTest
----------------------------------------
local _ATsprite = nil
local _AThasWeapon = false
local AttachmentTest = {}
AttachmentTest.__index = AttachmentTest

function AttachmentTest.addNewSpriteWithCoords(parent,x,y)
    local fileName = "Sprite3DTest/orc.c3b"
    local sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(5.0)
    sprite:setRotation3D({x = 0, y = 180, z = 0})
    sprite:setPosition(cc.p(x, y))
    local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
    local attachNode = sprite:getAttachNode("Bip001 R Hand")
    attachNode:addChild(sp)
    local animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        sprite:runAction(cc.RepeatForever:create(animate))
    end
    parent:addChild(sprite)

    _ATsprite = sprite;
    _AThasWeapon = true;
end

function AttachmentTest.onTouchesEnd(touches, event)
    if _AThasWeapon == true then
        _ATsprite:removeAllAttachNode()
    else
        local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
        local attachNode = _ATsprite:getAttachNode("Bip001 R Hand")
        attachNode:addChild(sp)
    end

    _AThasWeapon = not _AThasWeapon
end

function AttachmentTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D Attachment")
    Helper.subtitleLabel:setString("touch to switch weapon")

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(AttachmentTest.onTouchesEnd,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    AttachmentTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end

----------------------------------------
----Sprite3DReskinTest
----------------------------------------
local _SRTgirlPants = {"Girl_LowerBody01", "Girl_LowerBody02"}
local _SRTgirlUpperBody = {"Girl_UpperBody01", "Girl_UpperBody02"}
local _SRTgirlShoes = {"Girl_Shoes01", "Girl_Shoes02"}
local _SRTgirlHair = {"Girl_Hair01", "Girl_Hair02"}
local _SRTusePantsId = 1
local _SRTuseUpperBodyId = 1
local _SRTuseShoesId = 1
local _SRTuseHairId = 1
local _SRTsprite = nil
local Sprite3DReskinTest = {}
Sprite3DReskinTest.__index = Sprite3DReskinTest

function Sprite3DReskinTest.addNewSpriteWithCoords(parent,x,y)
    local fileName = "Sprite3DTest/ReskinGirl.c3b"
    local sprite = cc.Sprite3D:create(fileName)

    local girlPants = sprite:getMeshByName(_SRTgirlPants[2]);
    if nil ~= girlPants then
        girlPants:setVisible(false)
    end
    local girlUpBody = sprite:getMeshByName(_SRTgirlUpperBody[2]);
    if nil ~= girlUpBody then
        girlUpBody:setVisible(false)
    end
    local girlShoes = sprite:getMeshByName(_SRTgirlShoes[2]);
    if nil ~= girlShoes then
        girlShoes:setVisible(false)
    end
    local girlHair = sprite:getMeshByName(_SRTgirlHair[2]);
    if nil ~= girlHair then
        girlHair:setVisible(false)
    end

    parent:addChild(sprite)
    sprite:setScale(4.0)
    sprite:setPosition(cc.p(x, y - 60.0))
    local animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        sprite:runAction(cc.RepeatForever:create(animate))
    end

    _SRTsprite = sprite;
end

function Sprite3DReskinTest.createMenu(parent)

    local function SwitchPants()
        _SRTusePantsId = _SRTusePantsId + 1
        if _SRTusePantsId > 2 then
            _SRTusePantsId = 1
        end
        for i = 1, 2 do
            local mesh = _SRTsprite:getMeshByName(_SRTgirlPants[i])
            if i == _SRTusePantsId then
                mesh:setVisible(true)
            else
                mesh:setVisible(false)
            end
        end
    end

    local function SwitchUpperBody()
        _SRTuseUpperBodyId = _SRTuseUpperBodyId + 1
        if _SRTuseUpperBodyId > 2 then
            _SRTuseUpperBodyId = 1
        end
        for i = 1, 2 do
            local mesh = _SRTsprite:getMeshByName(_SRTgirlUpperBody[i])
            if i == _SRTuseUpperBodyId then
                mesh:setVisible(true)
            else
                mesh:setVisible(false)
            end
        end
    end

    local function SwitchShoes()
        _SRTuseShoesId = _SRTuseShoesId + 1
        if _SRTuseShoesId > 2 then
            _SRTuseShoesId = 1
        end
        for i = 1, 2 do
            local mesh = _SRTsprite:getMeshByName(_SRTgirlShoes[i])
            if i == _SRTuseShoesId then
                mesh:setVisible(true)
            else
                mesh:setVisible(false)
            end
        end
    end

    local function SwitchHair()
        _SRTuseHairId = _SRTuseHairId + 1
        if _SRTuseHairId > 2 then
            _SRTuseHairId = 1
        end
        for i = 1, 2 do
            local mesh = _SRTsprite:getMeshByName(_SRTgirlHair[i])
            if i == _SRTuseHairId then
                mesh:setVisible(true)
            else
                mesh:setVisible(false)
            end
        end
    end

    local function SwitchClasses()
        local mesh = _SRTsprite:getMeshByName("Girl_Glasses01")
        mesh:setVisible(not mesh:isVisible())
    end

    local label1 = cc.MenuItemLabel:create(cc.Label:createWithTTF("Hair","fonts/arial.ttf",20))
    local contSize = label1:getContentSize()
    label1:setPosition(cc.p(50.0, contSize.height * 4.0))
    label1:registerScriptTapHandler(SwitchHair)

    local label2 = cc.MenuItemLabel:create(cc.Label:createWithTTF("Glasses","fonts/arial.ttf",20))
    label2:setPosition(cc.p(50.0, contSize.height * 5.0))
    label2:registerScriptTapHandler(SwitchClasses)

    local label3 = cc.MenuItemLabel:create(cc.Label:createWithTTF("Coat","fonts/arial.ttf",20))
    label3:setPosition(cc.p(50.0, contSize.height * 6.0))
    label3:registerScriptTapHandler(SwitchUpperBody)

    local label4 = cc.MenuItemLabel:create(cc.Label:createWithTTF("Pants","fonts/arial.ttf",20))
    label4:setPosition(cc.p(50.0, contSize.height * 7.0))
    label4:registerScriptTapHandler(SwitchPants)

    local label5 = cc.MenuItemLabel:create(cc.Label:createWithTTF("Shoes","fonts/arial.ttf",20))
    label5:setPosition(cc.p(50.0, contSize.height * 8.0))
    label5:registerScriptTapHandler(SwitchShoes)

    local menu = cc.Menu:create(label1, label2, label3, label4, label5)
    menu:setPosition(cc.p(0.0, 0.0))
    parent:addChild(menu)
end

function Sprite3DReskinTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D Reskin")
    Helper.subtitleLabel:setString("")

    Sprite3DReskinTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    Sprite3DReskinTest.createMenu(layer)
    return layer
end


----------------------------------------
----Sprite3DMirrorTest
----------------------------------------
local Sprite3DMirrorTest = {}
Sprite3DMirrorTest.__index = Sprite3DMirrorTest

function Sprite3DMirrorTest.addNewSpriteWithCoords(parent,x,y)
    local fileName = "Sprite3DTest/orc.c3b"
    local sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(5.0)
    sprite:setRotation3D({x = 0, y = 180, z = 0})
    sprite:setPosition(cc.p(x - 80.0, y))
    local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
    local attachNode = sprite:getAttachNode("Bip001 R Hand")
    attachNode:addChild(sp)
    local animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        sprite:runAction(cc.RepeatForever:create(animate))
    end
    parent:addChild(sprite)

    sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(5.0)
    sprite:setScaleX(-5.0)
    sprite:setRotation3D({x = 0, y = 180, z = 0})
    sprite:setPosition(cc.p(x + 80.0, y))
    sprite:setCullFace(gl.FRONT)
    sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
    attachNode = sprite:getAttachNode("Bip001 R Hand")
    attachNode:addChild(sp)
    animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        sprite:runAction(cc.RepeatForever:create(animate))
    end
    parent:addChild(sprite)

end

function Sprite3DMirrorTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Sprite3D Mirror Test")
    Helper.subtitleLabel:setString("")

    Sprite3DMirrorTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    return layer
end

function Sprite3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Sprite3DBasicTest.create,
        Sprite3DHitTest.create,
        Sprite3DWithSkinTest.create,
        Animate3DTest.create,
        AttachmentTest.create,
        Sprite3DReskinTest.create,
        Sprite3DMirrorTest.create,
    }

    scene:addChild(Sprite3DBasicTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
