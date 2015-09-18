--------------------------------
-- BillBoardTest
--------------------------------
local BillBoardTest = class("BillBoardTest", function ()
    return cc.Layer:create()
end)

function BillBoardTest:ctor()
    self._camera = nil
    self._layerBillBorad = nil
    self._billboards = {}
    self:init()
end

function BillBoardTest:title()
    return "Testing BillBoard"
end

function BillBoardTest:subtitle()
    return ""
end

function BillBoardTest:addNewBillBoradWithCoords(p)
    local imgs = {"Images/Icon.png", "Images/r2.png"}
    for i= 1, 10 do
        local billborad = cc.BillBoard:create(imgs[math.ceil(math.random() + 0.5)])
        billborad:setScale(0.5)
        billborad:setPosition3D(cc.vec3(p.x, p.y,  -150.0 + 30 * i))
        billborad:setOpacity(math.random() * 128 + 128)
        self._layerBillBorad:addChild(billborad)
        table.insert(self._billboards, billborad)
    end
end

function BillBoardTest:addNewAniBillBoradWithCoords(p)
    for i = 1, 10 do
        local billboradAni = cc.BillBoard:create("Images/grossini.png")
        billboradAni:setScale(0.5)
        billboradAni:setPosition3D(cc.vec3(p.x, p.y,  -150.0 + 30 * (i - 1)))
        self._layerBillBorad:addChild(billboradAni)

        local animation = cc.Animation:create()
        for i=1,14 do
            local szName = string.format("Images/grossini_dance_%02d.png", i)
            animation:addSpriteFrameWithFile(szName)      
        end

        --should last 2.8 seconds. And there are 14 frames.
        animation:setDelayPerUnit(2.8 / 14.0)
        animation:setRestoreOriginalFrame(true)

        local action = cc.Animate:create(animation)
        billboradAni:runAction(cc.RepeatForever:create(action))
        billboradAni:setOpacity( math.random() * 128 + 128)
        table.insert(self._billboards, billboradAni)
    end
end

function BillBoardTest:init()
    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function(touches, event)
        if #touches == 1 then
            local touch = touches[1]
            local location = touch:getLocation()
            local previousLocation = touch:getPreviousLocation()
            local newPos = cc.pSub(previousLocation, location)
    
            local cameraDir = {}
            local cameraRightDir = {}
            local transformMat = self._camera:getNodeToWorldTransform()

            cameraDir.x = -transformMat[9]
            cameraDir.y = -transformMat[10]
            cameraDir.z = -transformMat[11]
            cameraDir = cc.vec3normalize(cameraDir)
            cameraDir.y = 0
            transformMat = self._camera:getNodeToWorldTransform()
            cameraRightDir.x = transformMat[1]
            cameraRightDir.y = transformMat[2]
            cameraRightDir.z = transformMat[3]
            cameraRightDir = cc.vec3normalize(cameraRightDir)
            cameraRightDir.y=0

            local cameraPos=  self._camera:getPosition3D()
            cameraPos = cc.vec3(cameraPos.x + cameraDir.x * newPos.y * 0.5, cameraPos.y + cameraDir.y * newPos.y * 0.5, cameraPos.z + cameraDir.z * newPos.y * 0.5)
            cameraPos = cc.vec3(cameraPos.x + cameraRightDir.x * newPos.x * 0.5, cameraPos.y + cameraRightDir.y * newPos.x * 0.5, cameraPos.z + cameraRightDir.z * newPos.x * 0.5)
            self._camera:setPosition3D(cameraPos)
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local layer3D = cc.Layer:create()
    self:addChild(layer3D,0)
    self._layerBillBorad = layer3D

    local s = cc.Director:getInstance():getWinSize()
    if self._camera == nil then
        self._camera = cc.Camera:createPerspective(60, s.width/s.height, 1, 500)
        self._camera:setCameraFlag(cc.CameraFlag.USER1)
        self._layerBillBorad:addChild(self._camera)
    end

    local imgs = {"Images/Icon.png", "Images/r2.png"}

    for i= 1, 4 do
        local layer = cc.Layer:create()
        local billboard = cc.BillBoard:create(imgs[math.ceil((math.random() + 0.5))])
        billboard:setScale(0.5)
        billboard:setPosition3D(cc.vec3(0.0, 0.0,  math.random(-1, 1) * 150.0))
        billboard:setOpacity(math.random() * 128 + 128)
        table.insert(self._billboards, billboard)
        layer:addChild(billboard)
        self._layerBillBorad:addChild(layer)
        layer:runAction( cc.RepeatForever:create( cc.RotateBy:create( math.random() * 10, cc.vec3(0.0, 45.0, 0.0) ) ) )
    end

    local billboard = cc.BillBoard:create("Images/Icon.png")
    billboard:setScale(0.2)
    billboard:setPosition3D(cc.vec3(0.0, 30.0, 0.0))

    local billboard2 = cc.BillBoard:create("Images/r2.png")
    billboard2:setPosition3D(cc.vec3(0.0, 0.0, 100.0))
    billboard:addChild(billboard2)
    table.insert(self._billboards, billboard)
    table.insert(self._billboards, billboard2)

    local sprite3d = cc.Sprite3D:create("Sprite3DTest/orc.c3t")
    sprite3d:setScale(2.0)
    sprite3d:addChild(billboard)
    sprite3d:runAction( cc.RepeatForever:create( cc.RotateBy:create( 10.0, cc.vec3(0.0, 360.0, 0.0) ) ) )
    self._layerBillBorad:addChild(sprite3d)

    self:addNewBillBoradWithCoords(cc.vec3(20,5,0))
    self:addNewBillBoradWithCoords(cc.vec3(60,5,0))
    self:addNewBillBoradWithCoords(cc.vec3(100,5,0))
    self:addNewBillBoradWithCoords(cc.vec3(140,5,0))
    self:addNewBillBoradWithCoords(cc.vec3(180,5,0))
    self:addNewAniBillBoradWithCoords(cc.vec3(-20,0,0))
    self:addNewAniBillBoradWithCoords(cc.vec3(-60,0,0))
    self:addNewAniBillBoradWithCoords(cc.vec3(-100,0,0))
    self:addNewAniBillBoradWithCoords(cc.vec3(-140,0,0))
    self:addNewAniBillBoradWithCoords(cc.vec3(-180,0,0))

    self._camera:setPosition(cc.vec3(0, 130, 230))
    self._camera:lookAt(cc.vec3(0, 0, 100), cc.vec3(0, 1, 0))

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 16

    local label1 = cc.Label:createWithTTF(ttfConfig,"rotate+")
    local menuItem1 = cc.MenuItemLabel:create(label1)
    menuItem1:registerScriptTapHandler(function (tag, sender )
        local  rotation3D= self._camera:getRotation3D()
        rotation3D.y = rotation3D.y + 10
        self._camera:setRotation3D(rotation3D)
    end)
    local label2 = cc.Label:createWithTTF(ttfConfig,"rotate-")
    local menuItem2 = cc.MenuItemLabel:create(label2)
    menuItem2:registerScriptTapHandler(function (tag, sender )
        local  rotation3D= self._camera:getRotation3D()
        rotation3D.y = rotation3D.y - 10
        self._camera:setRotation3D(rotation3D)
    end)

    local menu = cc.Menu:create(menuItem1,menuItem2)
    menu:setPosition(cc.p(0, 0))
    menuItem1:setPosition( cc.p( s.width-80, VisibleRect:top().y-160) )
    menuItem2:setPosition( cc.p( s.width-80, VisibleRect:top().y-190) )
    self:addChild(menu, 0)
    self._layerBillBorad:setCameraMask(2)

    label1 = cc.Label:createWithTTF(ttfConfig,"Point Oriented")
    menuItem1 = cc.MenuItemLabel:create(label1)
    menuItem1:registerScriptTapHandler(function (tag, sender )
        for i,billboard in ipairs(self._billboards) do
            billboard:setMode(cc.BillBoard_Mode.VIEW_POINT_ORIENTED)
        end
    end)
    label2 = cc.Label:createWithTTF(ttfConfig,"Plane Oriented")
    menuItem2 = cc.MenuItemLabel:create(label2)
    menuItem2:registerScriptTapHandler(function (tag, sender )
        for i,billboard in ipairs(self._billboards) do
            billboard:setMode(cc.BillBoard_Mode.VIEW_PLANE_ORIENTED)
        end
    end)
    menuItem1:setPosition( cc.p( s.width-80, VisibleRect:top().y-100) )
    menuItem2:setPosition( cc.p( s.width-80, VisibleRect:top().y-130) )
    menu = cc.Menu:create(menuItem1,menuItem2)
    menu:setPosition(cc.p(0,0))
    self:addChild(menu, 10)

    for i,billboard in ipairs(self._billboards) do
        billboard:setMode(cc.BillBoard_Mode.VIEW_POINT_ORIENTED)
    end
end



function BillBoardTestMain()
    cclog("BillBoardTestMain")
    local scene = cc.Scene:create()
    scene:addChild(BillBoardTest.new())
    scene:addChild(CreateBackMenuItem())

    return scene
end
