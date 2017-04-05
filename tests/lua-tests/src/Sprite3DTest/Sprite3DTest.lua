require "cocos.3d.3dConstants"

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
Sprite3DWithSkinTest._animateQuality = cc.Animate3DQuality.QUALITY_HIGH
Sprite3DWithSkinTest._sprites = {}

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
    table.insert(Sprite3DWithSkinTest._sprites, sprite)

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
        animate:setTag(110)
        animate:setQuality(Sprite3DWithSkinTest._animateQuality)
        local repeatAction = cc.RepeatForever:create(animate)
        repeatAction:setTag(110)
        sprite:runAction(repeatAction)
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
    Sprite3DWithSkinTest._sprites = {}
    Sprite3DWithSkinTest.addNewSpriteWithCoords(layer, size.width / 2, size.height / 2)
    
    cc.MenuItemFont:setFontName("fonts/arial.ttf")
    cc.MenuItemFont:setFontSize(15)
    local menuItem =  cc.MenuItemFont:create("High Quality")
    Sprite3DWithSkinTest._animateQuality = cc.Animate3DQuality.QUALITY_HIGH
    menuItem:registerScriptTapHandler(function(tag, sender)
        Sprite3DWithSkinTest._animateQuality  = Sprite3DWithSkinTest._animateQuality  + 1

        if Sprite3DWithSkinTest._animateQuality > cc.Animate3DQuality.QUALITY_HIGH then
            Sprite3DWithSkinTest._animateQuality = cc.Animate3DQuality.QUALITY_NONE
        end

        if Sprite3DWithSkinTest._animateQuality == cc.Animate3DQuality.QUALITY_NONE then
            menuItem:setString("None Quality")
        elseif Sprite3DWithSkinTest._animateQuality == cc.Animate3DQuality.QUALITY_LOW then
            menuItem:setString("Low Quality")
        elseif Sprite3DWithSkinTest._animateQuality == cc.Animate3DQuality.QUALITY_HIGH then
            menuItem:setString("High Quality")
        end

        for i,spriteIter in ipairs(Sprite3DWithSkinTest._sprites) do
            local repAction = spriteIter:getActionByTag(110)
            local animate3D = repAction:getInnerAction()
            animate3D:setQuality(Sprite3DWithSkinTest._animateQuality)
        end
    end)
    local menu = cc.Menu:create(menuItem)
    menu:setPosition(cc.p(0.0, 0.0))
    menuItem:setPosition(VisibleRect:left().x + 50, VisibleRect:top().y -70)
    layer:addChild(menu, 1)

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
        local winSize = cc.Director:getInstance():getWinSize()
        self._sprite:stopActionByTag(100)
        local inverse = cc.MoveTo:create(4.0, cc.p(winSize.width - self._sprite:getPositionX(), winSize.height / 2.0))
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
----Sprite3DWithOBBPerfromanceTest
----------------------------------------
local Sprite3DWithOBBPerfromanceTest = class("Sprite3DWithOBBPerfromanceTest",function()
    return cc.Layer:create()
end)

function Sprite3DWithOBBPerfromanceTest:ctor()
    self._obb = {}
    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function (touches, event)
        for i,touch in ipairs(touches) do
            local location = touch:getLocationInView()
            if nil ~= self._obb and #self._obb > 0 then
                self._intersetList = {}
                local ray = cc.Ray:new()
                self:calculateRayByLocationInView(ray, location)

                for idx,value in ipairs(self._obb) do
                    if ray:intersects(value) then
                        table.insert(self._intersetList, idx)
                        return
                    end
                end
            end
        end
    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function (touches, event)
        
    end,cc.Handler.EVENT_TOUCHES_ENDED)

    listener:registerScriptHandler(function (touches, event)
        for i,touch in ipairs(touches) do
            local location = touch:getLocation()

            for idx,value in ipairs(self._obb) do
                for lstIdx,lstValue in ipairs(self._intersetList) do
                    if idx == lstValue then
                        self._obb[idx]._center = cc.vec3(location.x,location.y,0)
                    end
                end
            end
        end
    end,cc.Handler.EVENT_TOUCHES_MOVED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local s = cc.Director:getInstance():getWinSize()
    self:initDrawBox()

    self:addNewSpriteWithCoords(cc.p(s.width/2, s.height/2))

    cc.MenuItemFont:setFontName("fonts/arial.ttf")
    cc.MenuItemFont:setFontSize(65)

    local decrease =  cc.MenuItemFont:create(" - ")
    decrease:registerScriptTapHandler(function(tag, sender)
        self:delOBBWithCount(10)
    end)
    decrease:setColor(cc.c3b(0, 200, 20))

    local increase =  cc.MenuItemFont:create(" + ")
    increase:registerScriptTapHandler(function(tag, sender)
        self:addOBBWithCount(10)
    end)
    increase:setColor(cc.c3b(0, 200, 20))

    local menu = cc.Menu:create(decrease, increase)
    menu:alignItemsHorizontally()
    menu:setPosition(cc.p(s.width/2, s.height - 90))
    self:addChild(menu, 1)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/Marker Felt.ttf"
    ttfConfig.fontSize = 30
    self._labelCubeCount = cc.Label:createWithTTF(ttfConfig,"0 cubes")
    self._labelCubeCount:setColor(cc.c3b(0,200,20))
    self._labelCubeCount:setPosition(cc.p(s.width/2, s.height-90))
    self:addChild(self._labelCubeCount)

    self:addOBBWithCount(10)
    self:scheduleUpdateWithPriorityLua(function(dt)
        self._labelCubeCount:setString(string.format("%u cubes", #self._obb))
        if nil ~= self._drawDebug then
            self._drawDebug:clear()
            local mat = self._sprite:getNodeToWorldTransform()

            self._obbt._xAxis = cc.vec3(mat[1], mat[2], mat[3])
            self._obbt._xAxis = cc.vec3normalize(self._obbt._xAxis)

            self._obbt._yAxis = cc.vec3(mat[5], mat[6], mat[7])
            self._obbt._yAxis = cc.vec3normalize(self._obbt._yAxis)

            self._obbt._zAxis = cc.vec3(-mat[9], -mat[10], -mat[11])
            self._obbt._zAxis = cc.vec3normalize(self._obbt._zAxis)

            self._obbt._center = self._sprite:getPosition3D()

            local corners = {}
            for i=1,8 do
                corners[i] = {}
            end
            corners = self._obbt:getCorners(corners)
            self._drawDebug:drawCube(corners, cc.c4f(0, 0, 1, 1))
        end

        if #self._obb > 0 then
            self._drawOBB:clear()

            for i= 1, #self._obb do
                local corners = {}
                for i=1,8 do
                    corners[i] = {}
                end

                corners = self._obb[i]:getCorners(corners)
                if self._obbt:intersects(self._obb[i]) then
                    self._drawOBB:drawCube(corners, cc.c4f(1, 0, 0, 1))
                else
                    self._drawOBB:drawCube(corners, cc.c4f(0, 1, 0, 1))
                end

            end
        end
    end, 0)
end

function Sprite3DWithOBBPerfromanceTest:addOBBWithCount( value )
    for i=1,value do
        local randompos = cc.p(math.random() * cc.Director:getInstance():getWinSize().width, math.random() * cc.Director:getInstance():getWinSize().height)
        local extents = cc.vec3(10, 10, 10)
        local aabb = cc.AABB:new({x = -10, y = -10, z = -10}, extents)
        local obb = cc.OBB:new(aabb)
        obb._center = cc.vec3(randompos.x,randompos.y,0)
        table.insert(self._obb, obb)
    end
end

function Sprite3DWithOBBPerfromanceTest:delOBBWithCount( value )
    if #self._obb >= 10 then
        for i= 1, 10 do
            table.remove(self._obb)
        end
        self._drawOBB:clear()
    end
end

function Sprite3DWithOBBPerfromanceTest:initDrawBox()
    self._drawOBB = cc.DrawNode3D:create()
    self:addChild(self._drawOBB )
end

function Sprite3DWithOBBPerfromanceTest:unproject( viewProjection, viewport, src, dst)
    assert(viewport.width ~= 0.0 and viewport.height ~= 0)
    local screen = cc.vec4(src.x / viewport.width, (viewport.height - src.y) / viewport.height, src.z, 1.0)
    screen.x = screen.x * 2.0 - 1.0
    screen.y = screen.y * 2.0 - 1.0
    screen.z = screen.z * 2.0 - 1.0
    local inversed = cc.mat4.new(viewProjection:getInversed())
    screen = inversed:transformVector(screen)
    if screen.w ~= 0.0 then
        screen.x = screen.x / screen.w
        screen.y = screen.y / screen.w
        screen.z = screen.z / screen.w
    end

    dst.x = screen.x
    dst.y = screen.y
    dst.z = screen.z
    return viewport, src, dst
end

function Sprite3DWithOBBPerfromanceTest:calculateRayByLocationInView(ray, location)
    local dir = cc.Director:getInstance()
    local view = dir:getWinSize()
    local mat = cc.mat4.new(dir:getMatrix(cc.MATRIX_STACK_TYPE.PROJECTION))
    local src = cc.vec3(location.x, location.y, -1)
    local nearPoint = {}
    view, src, nearPoint = self:unproject(mat, view, src, nearPoint)
    src = cc.vec3(location.x, location.y, 1)
    local farPoint = {}
    view, src, farPoint = self:unproject(mat, view, src, farPoint)
    local direction = {}
    direction.x = farPoint.x - nearPoint.x
    direction.y = farPoint.y - nearPoint.y
    direction.z = farPoint.z - nearPoint.z
    direction   = cc.vec3normalize(direction)
    
    ray._origin    = nearPoint
    ray._direction = direction
end

function Sprite3DWithOBBPerfromanceTest:addNewSpriteWithCoords(vec2)
    local fileName = "Sprite3DTest/tortoise.c3b"
    local sprite = cc.Sprite3D:create(fileName)
    sprite:setScale(0.1)
    local s = cc.Director:getInstance():getWinSize()
    sprite:setPosition(cc.p(s.width * 4.0 / 5.0, s.height / 2.0))
    self:addChild(sprite)
    self._sprite = sprite
    local animation = cc.Animation3D:create(fileName)
    if  nil ~= animation then
        local animate = cc.Animate3D:create(animation, 0.0, 1.933)
        sprite:runAction(cc.RepeatForever:create(animate))
    end
    
    self._moveAction = cc.MoveTo:create(4.0, cc.p(s.width / 5.0, s.height / 2.0))
    self._moveAction:retain()
    local function reachEndCallBack()
    local s = cc.Director:getInstance():getWinSize()
        self._sprite:stopActionByTag(100)
        local inverse = cc.MoveTo:create(4.0, cc.p(s.width - self._sprite:getPositionX(), s.height / 2.0))
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
 
    local aabb = self._sprite:getAABB()
    self._obbt = cc.OBB:new(aabb)
    
    self._drawDebug = cc.DrawNode3D:create()
    self:addChild(self._drawDebug)
end

function Sprite3DWithOBBPerfromanceTest.create()
    local layer = Sprite3DWithOBBPerfromanceTest.new()
    Helper.initWithLayer(layer)
    Helper.titleLabel:setString("OBB Collision Perfromance Test")
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


----------------------------------------
----AsyncLoadSprite3DTest
----------------------------------------
local AsyncLoadSprite3DTest = class("AsyncLoadSprite3DTest", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function AsyncLoadSprite3DTest:ctor()
    -- body
    self:init()
end

function AsyncLoadSprite3DTest:init()
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function AsyncLoadSprite3DTest:title()
    return "Testing Sprite3D:createAsync"
end

function AsyncLoadSprite3DTest:subtitle()
    return ""
end

function AsyncLoadSprite3DTest:onEnter()

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 15

    local paths = {"Sprite3DTest/boss.obj", "Sprite3DTest/girl.c3b", "Sprite3DTest/orc.c3b", "Sprite3DTest/ReskinGirl.c3b", "Sprite3DTest/axe.c3b"}

    local label1 = cc.Label:createWithTTF(ttfConfig,"AsyncLoad Sprite3D")
    local item1 = cc.MenuItemLabel:create(label1)

    function menuCallback_asyncLoadSprite(tag, sender)
        --Note that you must stop the tasks before leaving the scene.
        cc.AsyncTaskPool:getInstance():stopTasks(cc.AsyncTaskPool.TaskType.TASK_IO)
    
        local node = self:getChildByTag(101)
        --remove all loaded sprite
        node:removeAllChildren()
    
        --remove cache data
        cc.Sprite3DCache:getInstance():removeAllSprite3DData()

        local function callback(sprite, index)
            local node = self:getChildByTag(101)
            local s = cc.Director:getInstance():getWinSize()
            local width = s.width / (#paths)
            local point = cc.p(width * (0.5 + index), s.height / 2.0)
            sprite:setPosition(point)
            node:addChild(sprite)
        end

        cc.Sprite3D:createAsync(paths[1], function(sprite)
            callback(sprite, 0)
        end)

        cc.Sprite3D:createAsync(paths[2], function(sprite)
            callback(sprite, 1)
        end)

        cc.Sprite3D:createAsync(paths[3], function(sprite)
            callback(sprite, 2)
        end)

        cc.Sprite3D:createAsync(paths[4], function(sprite)
            callback(sprite, 3)
        end)

        cc.Sprite3D:createAsync(paths[5], function(sprite)
            callback(sprite, 4)
        end)
    end
    item1:registerScriptTapHandler(menuCallback_asyncLoadSprite)
    
    local s = cc.Director:getInstance():getWinSize()
    item1:setPosition( s.width * 0.5, s.height * 0.8)
    
    local menu = cc.Menu:create(item1)
    menu:setPosition(cc.p(0,0))
    self:addChild(menu, 10)
    
    local node = cc.Node:create()
    node:setTag(101)
    self:addChild(node)
    
    menuCallback_asyncLoadSprite()
end

function AsyncLoadSprite3DTest:onExit()
end

----------------------------------------
----Sprite3DCubeTexture
----------------------------------------
local Sprite3DCubeMapTest = class("Sprite3DCubeMapTest", function ()
    local layer = cc.Layer:create()
    return layer
end)

function Sprite3DCubeMapTest:ctor()
    -- body
    self:init()
    self._textureCube = nil
    self._skyBox = nil
    self._teapot = nil
end

function Sprite3DCubeMapTest:init()
    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Sprite3DCubeMapTest:title()
    return "CubeMap & Skybox Test"
end

function Sprite3DCubeMapTest:subtitle()
    return ""
end

function Sprite3DCubeMapTest:onEnter()
    local s = cc.Director:getInstance():getWinSize()
    self:addNewSpriteWithCoords(cc.p(s.width / 2, s.height / 2))
    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())
end

function Sprite3DCubeMapTest:onExit()
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_ANDROID  or targetPlatform == cc.PLATFORM_OS_WINRT  or targetPlatform == cc.PLATFORM_OS_WP8  then
        cc.Director:getInstance():getEventDispatcher():removeEventListener(self._backToForegroundListener)
    end
end

function Sprite3DCubeMapTest:addNewSpriteWithCoords(pos)
    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local camera = cc.Camera:createPerspective(60, visibleSize.width / visibleSize.height, 10, 1000)
    camera:setPosition3D(cc.vec3(0.0, 0.0, 50.0))
    camera:setCameraFlag(cc.CameraFlag.USER1)
    --create a teapot
    self._teapot = cc.Sprite3D:create("Sprite3DTest/teapot.c3b")

    local shader = cc.GLProgram:createWithFilenames("Sprite3DTest/cube_map.vert", "Sprite3DTest/cube_map.frag")
    local state  = cc.GLProgramState:create(shader)

    self._textureCube = cc.TextureCube:create("Sprite3DTest/skybox/left.jpg", "Sprite3DTest/skybox/right.jpg",
        "Sprite3DTest/skybox/top.jpg", "Sprite3DTest/skybox/bottom.jpg",
        "Sprite3DTest/skybox/front.jpg", "Sprite3DTest/skybox/back.jpg")

    --set texture parameters
    local tRepeatParams = { magFilter=gl.LINEAR , minFilter=gl.LINEAR , wrapS=gl.MIRRORED_REPEAT  , wrapT=gl.MIRRORED_REPEAT }
    self._textureCube:setTexParameters(tRepeatParams)

    --pass the texture sampler to our custom shader
    state:setUniformTexture("u_cubeTex", self._textureCube)

    self._teapot:setGLProgramState(state)
    self._teapot:setPosition3D(cc.vec3(0, -5, 0))
    self._teapot:setRotation3D(cc.vec3(-90, 180, 0))

    local rotate_action = cc.RotateBy:create(1.5, cc.vec3(0, 30, 0))
    self._teapot:runAction(cc.RepeatForever:create(rotate_action))

    --pass mesh's attribute to shader

    local attributeNames = 
    {
        "a_position",
        "a_color",
        "a_texCoord",
        "a_texCoord1",
        "a_texCoord2",
        "a_texCoord3",
        "a_normal",
        "a_blendWeight",
        "a_blendIndex",
    }

    local offset = 0
    local attributeCount = self._teapot:getMesh():getMeshVertexAttribCount()
    for i = 1, attributeCount do
        local meshattribute = self._teapot:getMesh():getMeshVertexAttribute(i - 1)
        state:setVertexAttribPointer(attributeNames[meshattribute.vertexAttrib+1],
            meshattribute.size,
            meshattribute.type,
            false,
            self._teapot:getMesh():getVertexSizeInBytes(),
            offset)
        offset = offset + meshattribute.attribSizeBytes
    end

    self:addChild(self._teapot)

    --config skybox
    self._skyBox = cc.Skybox:create()

    self._skyBox:setTexture(self._textureCube)
    self:addChild(self._skyBox)

    self:addChild(camera)
    self:setCameraMask(2)

    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_ANDROID  or targetPlatform == cc.PLATFORM_OS_WINRT  or targetPlatform == cc.PLATFORM_OS_WP8  then
        self._backToForegroundListener = cc.EventListenerCustom:create("event_renderer_recreated", function (eventCustom)
                
            local state = self._teapot:getGLProgramState()
            local glProgram = state:getGLProgram()
            glProgramreset()
            glProgram:initWithFilenames("Sprite3DTest/cube_map.vert", "Sprite3DTest/cube_map.frag")
            glProgram:link()
            glProgram:updateUniforms()

            self._textureCube:reloadTexture()

            local tRepeatParams = { magFilter=gl.NEAREST , minFilter=gl.NEAREST , wrapS=gl.MIRRORED_REPEAT  , wrapT=gl.MIRRORED_REPEAT }
            self._textureCube:setTexParameters(tRepeatParams)
            state:setUniformTexture("u_cubeTex", self._textureCube)

            self._skyBox:reload()
            self._skyBox:setTexture(self._textureCube)
        end)
        cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(self._backToForegroundListener, -1)
    end
end

----------------------------------------
----Sprite3DNormalMappingTest
----------------------------------------
local Sprite3DNormalMappingTest = class("Sprite3DNormalMappingTest", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Sprite3DNormalMappingTest:ctor()
    -- body
    self:init()
end

function Sprite3DNormalMappingTest:init()
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Sprite3DNormalMappingTest:title()
    return "Testing Normal Mapping"
end

function Sprite3DNormalMappingTest:subtitle()
    return ""
end

function Sprite3DNormalMappingTest:onEnter()

    local sprite3d = cc.Sprite3D:create("Sprite3DTest/sphere.c3b")
    sprite3d:setScale(2.0)
    sprite3d:setPosition(cc.p(-30,0))
    sprite3d:setRotation3D(cc.vec3(90.0, 0.0, 0.0))
    sprite3d:setTexture("Sprite3DTest/brickwork-texture.jpg")
    sprite3d:setCameraMask(2)
    self:addChild(sprite3d)

    local sprite3dBumped = cc.Sprite3D:create("Sprite3DTest/sphere_bumped.c3b")
    sprite3dBumped:setScale(20.0)
    sprite3dBumped:setPosition(cc.p(30,0))
    sprite3dBumped:setRotation3D(cc.vec3(90.0, 0.0, 0.0))
    sprite3dBumped:setCameraMask(2)
    self:addChild(sprite3dBumped)

    local radius = 100.0
    local angle = 0.0
    local reverseDir = false
    local light = cc.PointLight:create(cc.vec3(0.0, 0.0, 0.0), cc.c3b(255, 255, 255), 1000.0)
    local function lightUpdate()
        light:setPosition3D(cc.vec3(radius * math.cos(angle), 0.0, radius * math.sin(angle)))
        if reverseDir == true then
            angle = angle - 0.01
            if angle < 0.0 then
                reverseDir = false
            end
        else
            angle = angle + 0.01
            if 3.14159 < angle then
                reverseDir = true
            end
        end
    end

    local seq = cc.Sequence:create(cc.CallFunc:create(lightUpdate))
    light:runAction(cc.RepeatForever:create(seq))
    self:addChild(light)

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    local camera = cc.Camera:createPerspective(60, visibleSize.width / visibleSize.height, 10, 1000)
    camera:setPosition3D(cc.vec3(0.0, 0.0, 100.0))
    camera:lookAt(cc.vec3(0.0, 0.0, 0.0))
    camera:setCameraFlag(cc.CameraFlag.USER1)
    self:addChild(camera)

end

function Sprite3DNormalMappingTest:onExit()
end

----------------------------------------
----Sprite3DMaterialTest
----------------------------------------
local Sprite3DMaterialTest = class("Sprite3DMaterialTest", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Sprite3DMaterialTest:ctor()
    -- body
    self:init()
end

function Sprite3DMaterialTest:init()
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

function Sprite3DMaterialTest:title()
    return "Testing Sprite3DMaterial"
end

function Sprite3DMaterialTest:subtitle()
    return ""
end

function Sprite3DMaterialTest:onEnter()

    local material = cc.Sprite3DMaterial:createWithFilename("Sprite3DTest/outline.material")
    local sprite = cc.Sprite3D:create("Sprite3DTest/sphere_bumped.c3b")
        :setScale(20.0)
        :setPosition(cc.p(0,0))
        :setRotation3D(cc.vec3(90.0, 0.0, 0.0))
        :setCameraMask(2)
        :setMaterial(material)
    self:addChild(sprite)


    local camera = cc.Camera:create()
        :setPosition3D(cc.vec3(0.0, 0.0, 100.0))
        :lookAt(cc.vec3(0.0, 0.0, 0.0))
        :setCameraFlag(cc.CameraFlag.USER1)
    self:addChild(camera)
end

function Sprite3DMaterialTest:onExit()
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
        Sprite3DWithOBBPerfromanceTest.create,
        Sprite3DMirrorTest.create,
        AsyncLoadSprite3DTest.create,
        Sprite3DCubeMapTest.create,
        Sprite3DNormalMappingTest.create,
        Sprite3DMaterialTest.create,
    }
    Helper.index = 1

    scene:addChild(Sprite3DBasicTest.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
