local size = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()
local attributeNames = 
{
    "a_position",
    "a_color",
    "a_texCoord",
    "a_texCoord1",
    "a_texCoord2",
    "a_texCoord3",
    "a_texCoord4",
    "a_texCoord5",
    "a_texCoord6",
    "a_texCoord7",
    "a_normal",
    "a_blendWeight",
    "a_blendIndex",
}

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

function Sprite3DHitTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D Touch in 2D")
    Helper.subtitleLabel:setString("Tap Sprite3D and Drag")

    local sprite1 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite1:setScale(4.0)
    sprite1:setTexture("Sprite3DTest/boss.png")
    sprite1:setPosition( cc.p(size.width/2, size.height/2) )
    sprite1:runAction(cc.RepeatForever:create(cc.RotateBy:create(3, 360)))
    layer:addChild(sprite1)

    local sprite2 = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    sprite2:setScale(4.0)
    sprite2:setTexture("Sprite3DTest/boss.png")
    sprite2:setPosition( cc.p(size.width/2, size.height/2) )
    sprite2:setAnchorPoint(cc.p(0.5, 0.5))
    sprite2:runAction(cc.RepeatForever:create(cc.RotateBy:create(3, -360)))
    layer:addChild(sprite2)

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(function (touch, event)
        local target = event:getCurrentTarget()
        local rect   = target:getBoundingBox()
        if cc.rectContainsPoint(rect, touch:getLocation()) then
            print(string.format("sprite3d began... x = %f, y = %f", touch:getLocation().x, touch:getLocation().y))
            target:setOpacity(100)
            return true
        end

        return false
    end,cc.Handler.EVENT_TOUCH_BEGAN )

    listener:registerScriptHandler(function (touch, event)
        local target = event:getCurrentTarget()
        local x,y = target:getPosition()
        target:setPosition(cc.p(x + touch:getDelta().x, y + touch:getDelta().y))
    end, cc.Handler.EVENT_TOUCH_MOVED)

    listener:registerScriptHandler(function (touch, event)
        local target = event:getCurrentTarget()
        print("sprite3d onTouchEnd")
        target:setOpacity(255)
    end, cc.Handler.EVENT_TOUCH_ENDED)

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, sprite1)
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener:clone(), sprite2)

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
----AttachmentTest
----------------------------------------
local AttachmentTest = {}
AttachmentTest.__index = AttachmentTest

function AttachmentTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Testing Sprite3D Attachment")
    Helper.subtitleLabel:setString("touch to switch weapon")

    local _sprite = nil
    local _hasWeapon = nil

    local function addNewSpriteWithCoords(pos)
        local fileName = "Sprite3DTest/orc.c3b"
        local sprite = cc.Sprite3D:create(fileName)
        sprite:setScale(5)
        sprite:setRotation3D({x = 0, y =180, z = 0})
        layer:addChild(sprite)
        sprite:setPosition( cc.p( pos.x, pos.y) )
    
        --test attach
        local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
        sprite:getAttachNode("Bip001 R Hand"):addChild(sp)
    
        local animation = cc.Animation3D:create(fileName)
        if nil ~=animation then
            local animate = cc.Animate3D:create(animation)
            sprite:runAction(cc.RepeatForever:create(animate))
        end 

        _sprite = sprite
        _hasWeapon = true
    end

    addNewSpriteWithCoords(cc.p(size.width / 2, size.height / 2))

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function (touches, event)
        if _hasWeapon then
            _sprite:removeAllAttachNode()
        else
            local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
            _sprite:getAttachNode("Bip001 R Hand"):addChild(sp)
        end

        _hasWeapon = not _hasWeapon
    end,cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

    return layer
end

----------------------------------------
----Sprite3DReskinTest
----------------------------------------
local Sprite3DReskinTest = {}
Sprite3DReskinTest.__index = Sprite3DReskinTest

function Sprite3DReskinTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, Sprite3DReskinTest)
    return target
end

function Sprite3DReskinTest:init()
    self._girlPants = {}
    self._usePantsId = 0
    self._girlUpperBody = {}
    self._useUpBodyId = 0
    self._girlShoes = {}
    self._useShoesId = 0
    self._girlHair   = {}
    self._useHairId  = 0
    self._sprite     = nil 

    self:addNewSpriteWithCoords(cc.p(size.width / 2, size.height / 2))

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function (touches, event)
        
    end,cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 20

    local label1 = cc.Label:createWithTTF(ttfConfig,"Hair")
    local item1  = cc.MenuItemLabel:create(label1)
    item1:registerScriptTapHandler(function (tag, sender ) -- swithHair
        self._useHairId = self._useHairId + 1
        if self._useHairId > 1 then
            self._useHairId = 0
        end

        if self._useHairId >= 0 and self._sprite ~= nil then
            for i=1,2 do
                local subMesh = self._sprite:getMeshByName(self._girlHair[i])
                if nil ~= subMesh then
                    if (i - 1) == self._useHairId then
                        subMesh:setVisible(true)
                    else
                        subMesh:setVisible(false)
                    end
                end
            end
        end
    end)
    local label2 = cc.Label:createWithTTF(ttfConfig,"Glasses")
    local item2 = cc.MenuItemLabel:create(label2)
    item2:registerScriptTapHandler(function (tag, sender ) -- switchGlasses
        local subMesh = self._sprite:getMeshByName("Girl_Glasses01")
        if nil ~= subMesh then
            if subMesh:isVisible() then
                subMesh:setVisible(false)
            else
                subMesh:setVisible(true)
            end
        end
    end)

    local label3 = cc.Label:createWithTTF(ttfConfig,"Coat")
    local item3 = cc.MenuItemLabel:create(label3)
    item3:registerScriptTapHandler(function (tag, sender ) -- switchCoat
        self._useUpBodyId = self._useUpBodyId + 1
        if self._useUpBodyId > 1 then
            self._useUpBodyId = 0
        end
        if self._useUpBodyId >= 0  and nil ~= self._sprite then
            for i=1,2 do
                local subMesh = self._sprite:getMeshByName(self._girlUpperBody[i])
                if nil ~=subMesh then
                    if (i - 1) == self._useUpBodyId then
                        subMesh:setVisible(true)
                    else
                        subMesh:setVisible(false)
                    end
                end
            end
        end
    end)

    local label4 = cc.Label:createWithTTF(ttfConfig,"Pants")
    local item4 = cc.MenuItemLabel:create(label4)
    item4:registerScriptTapHandler(function (tag, sender ) -- switchPants

        self._usePantsId = self._usePantsId + 1
        if self._usePantsId > 1 then
            self._usePantsId = 0
        end

        if self._usePantsId >= 0  and nil ~= self._sprite then
            for i=1,2 do
                local subMesh = self._sprite:getMeshByName(self._girlPants[i])
                if nil ~= subMesh then
                    if (i - 1) == self._usePantsId then
                        subMesh:setVisible(true)
                    else
                        subMesh:setVisible(false)
                    end
                end
            end
        end
    end)

    local label5 = cc.Label:createWithTTF(ttfConfig,"Shoes")
    local item5 = cc.MenuItemLabel:create(label5)
    item5:registerScriptTapHandler(function (tag, sender ) -- switchShoes

        self._useShoesId = self._useShoesId + 1
        if self._useShoesId > 1 then
            self._useShoesId = 0
        end

        if self._useShoesId >= 0  and nil ~= self._sprite then
            for i=1,2 do
                local subMesh = self._sprite:getMeshByName(self._girlShoes[i])
                if nil ~= subMesh then
                    if (i - 1) == self._useShoesId then
                        subMesh:setVisible(true)
                    else
                        subMesh:setVisible(false)
                    end
                end
            end
        end
    end)

    item1:setPosition( cc.p(VisibleRect:left().x+50, VisibleRect:bottom().y+item1:getContentSize().height*4 ) )
    item2:setPosition( cc.p(VisibleRect:left().x+50, VisibleRect:bottom().y+item1:getContentSize().height *5 ) )
    item3:setPosition( cc.p(VisibleRect:left().x+50, VisibleRect:bottom().y+item1:getContentSize().height*6 ) )
    item4:setPosition( cc.p(VisibleRect:left().x+50, VisibleRect:bottom().y+item1:getContentSize().height *7 ) )
    item5:setPosition( cc.p(VisibleRect:left().x+50, VisibleRect:bottom().y+item1:getContentSize().height *8 ) )
    local menu = cc.Menu:create(item1,item2,item3,item4,item5)
    menu:setPosition(cc.p(0,0))
    self:addChild(menu, 10)
end


function Sprite3DReskinTest:addNewSpriteWithCoords(pos)
    self._girlPants = {"Girl_LowerBody01", "Girl_LowerBody02"}
    self._girlUpperBody = {"Girl_UpperBody01", "Girl_UpperBody02"}
    self._girlShoes  = {"Girl_Shoes01", "Girl_Shoes02"}
    self._girlHair  = {"Girl_Hair01", "Girl_Hair02"}
    self._usePantsId = 0
    self._useUpBodyId = 0
    self._useShoesId   =0
    self._useHairId = 0

    local fileName = "Sprite3DTest/ReskinGirl.c3b"
    local sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(4)
    sprite:setRotation3D({x = 0, y =0 ,z = 0})
    local girlPants = sprite:getMeshByName(self._girlPants[2])
    if nil ~= girlPants then
        girlPants:setVisible(false)
    end

    local girlShoes = sprite:getMeshByName(self._girlShoes[2])
    if nil ~= girlShoes then
        girlShoes:setVisible(false)
    end

    local girlHair = sprite:getMeshByName(self._girlHair[2])
    if nil ~= girlHair then
        girlHair:setVisible(false)
    end

    local girlUpBody = sprite:getMeshByName( self._girlUpperBody[2])
    if nil ~=girlUpBody then
        girlUpBody:setVisible(false)
    end

    self:addChild(sprite)
    sprite:setPosition( cc.p( pos.x, pos.y-60) )
    local animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        sprite:runAction(cc.RepeatForever:create(animate))
    end
    self._sprite = sprite
end

function Sprite3DReskinTest.create()
    local layer =  Sprite3DReskinTest.extend(cc.Layer:create())

    if nil ~= layer then
        Helper.initWithLayer(layer)
        Helper.titleLabel:setString("Testing Sprite3D Reskin")
        layer:init()
    end

    return layer
end

----------------------------------------
----Sprite3DMirrorTest
----------------------------------------
local Sprite3DMirrorTest = {}
Sprite3DMirrorTest.__index = Sprite3DMirrorTest

function Sprite3DMirrorTest.create()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("Sprite3D Mirror Test")

    local fileName = "Sprite3DTest/orc.c3b"
    local sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(5.0)
    sprite:setRotation3D({x = 0, y = 180, z = 0})
    sprite:setPosition( cc.p(size.width/2 - 80, size.height/2) )
    layer:addChild(sprite)

    local sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
    sprite:getAttachNode("Bip001 R Hand"):addChild(sp)

    local animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        
        sprite:runAction(cc.RepeatForever:create(animate))
    end

    --create mirror Sprite3D
    sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(5)
    sprite:setScaleX(-5)
    sprite:setCullFace(gl.FRONT)
    sprite:setRotation3D({x = 0, y = 180,z = 0})
    layer:addChild(sprite)
    sprite:setPosition( cc.p( size.width/2 + 80, size.height/2))

    --test attach
    sp = cc.Sprite3D:create("Sprite3DTest/axe.c3b")
    sprite:getAttachNode("Bip001 R Hand"):addChild(sp)
    
    animation = cc.Animation3D:create(fileName)
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        
        sprite:runAction(cc.RepeatForever:create(animate))
    end

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
