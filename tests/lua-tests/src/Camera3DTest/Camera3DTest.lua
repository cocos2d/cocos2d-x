--------------------------------
-- Camera3DTest
--------------------------------
local State = 
{
    None = 0,
    Idle = 0x01,
    Move = 0x02,
    Rotate = 0x04,
    Speak = 0x08,
    MeleeAttack = 0x10,
    RemoteAttack = 0x20,
    Attack = 0x40,
}

local CameraType = 
{
    FreeCamera = 0,
    FirstCamera = 1,
    ThirdCamera = 2,
}

local scheduler = cc.Director:getInstance():getScheduler()

local Camera3DTestDemo = class("Camera3DTestDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Camera3DTestDemo:ctor()
    -- body
    self._title = ""
    self._layer3D = nil
    self._sprite3D = nil
    self._targetPos = {x = 0, y = 0, z = 0}
    self._cameraType = 0
    self._incRot = nil
    self._decRot = nil
    self._curState = 0
    self._camera = nil
    self._moveAction = nil
    self.schedulerEntry = 0
    self:init()
end

function Camera3DTestDemo:addNewSpriteWithCoords(vec3, filename, playAnimation, scale, bindCamera)

    local sprite = cc.Sprite3D:create(filename)
    self._layer3D:addChild(sprite)
    local globalZOrder = sprite:getGlobalZOrder()
    sprite:setPosition3D(cc.vec3( vec3.x, vec3.y, vec3.z))
    sprite:setGlobalZOrder(globalZOrder)
    if nil ~= playAnimation then
        local animation = cc.Animation3D:create(filename,"Take 001")
        if nil ~= animation then
            local animate = cc.Animate3D:create(animation)
            sprite:runAction(cc.RepeatForever:create(animate))
        end
    end
    if bindCamera then
        self._sprite3D = sprite
    end
    sprite:setScale(scale)
end

function Camera3DTestDemo:scaleCameraCallback(sender, value)
    
end

function Camera3DTestDemo:rotateCameraCallback( sender,value)
    -- body
end

function Camera3DTestDemo:SwitchViewCallback(sender, value)
    if self._cameraType == value then
        return
    end

    self._cameraType = value

    if self._cameraType == CameraType.FreeCamera then
        local pos3D = self._sprite3D:getPosition3D()
        self._camera:setPosition3D(cc.vec3add(cc.vec3(0, 130, 130), pos3D))
        self._camera:lookAt(self._sprite3D:getPosition3D(), cc.vec3(0,1,0))
        self._incRot:setEnabled(true)
        self._decRot:setEnabled(true)

    elseif self._cameraType == CameraType.FirstCamera then
        local newFaceDir = {}
        local transform = self._sprite3D:getWorldToNodeTransform()
        newFaceDir.x = -transform[9]
        newFaceDir.y = -transform[10]
        newFaceDir.z = -transform[11]
        newFaceDir = cc.vec3normalize(newFaceDir)
        local pos3D = self._sprite3D:getPosition3D()
        self._camera:lookAt(cc.vec3add(pos3D, cc.vec3mul(newFaceDir, 50)), cc.vec3(0, 1, 0))
        self._incRot:setEnabled(true)
        self._decRot:setEnabled(true)
    elseif self._cameraType == CameraType.ThirdCamera then
        local pos3D = self._sprite3D:getPosition3D()
        self._camera:setPosition3D(cc.vec3(pos3D.x, pos3D.y + 130, pos3D.z + 130))
        self._camera:lookAt(self._sprite3D:getPosition3D(), cc.vec3(0, 1, 0))
        self._incRot:setEnabled(false)
        self._decRot:setEnabled(false)
    end

end

function Camera3DTestDemo:update(ft)
    -- body
end

function Camera3DTestDemo:title()
    return "Testing Camera"
end

function Camera3DTestDemo:subtitle()
    return ""
end

function Camera3DTestDemo:updateState( dt )
    if self._sprite3D ~= nil then
        local curPos =  self._sprite3D:getPosition3D()
        local curFaceDir = {}
        local matTransform = self._sprite3D:getNodeToWorldTransform()
        curFaceDir.x = matTransform[9]
        curFaceDir.y = matTransform[10]
        curFaceDir.z = matTransform[11]
        curFaceDir = cc.vec3normalize(curFaceDir)

        local newFaceDir = {x = self._targetPos.x - curPos.x, y = self._targetPos.y - curPos.y, z = self._targetPos.z - curPos.z}
        newFaceDir.y = 0.0 
        newFaceDir = cc.vec3normalize(newFaceDir)
        local cosAngle = math.abs(curFaceDir.x * newFaceDir.x + curFaceDir.y * newFaceDir.y + curFaceDir.z * newFaceDir.z - 1) 
        local distanceX = self._targetPos.x - curPos.x
        local distanceY = self._targetPos.y - curPos.y
        local distanceZ = self._targetPos.z - curPos.z
        local dist      = distanceX * distanceX + distanceY * distanceY + distanceZ *  distanceZ
        if dist <= 4.0 then
            if cosAngle <= 0.01 then
                self._curState = State.Idle
            else
                self._curState = State.Rotate
            end
        else
            if cosAngle > 0.01 then
                self._curState = bit._or(State.Rotate,State.Move)
            else
                self._curState = State.Move
            end
        end
    end
end

function Camera3DTestDemo:isState(state, dstState)
    return bit._and(state, dstState) == dstState
end

function Camera3DTestDemo:move3D(dt)
    if self._sprite3D ~= nil then
        local curPos = self._sprite3D:getPosition3D()
        local newFaceDir = {x = self._targetPos.x - curPos.x, y = self._targetPos.y - curPos.y, z = self._targetPos.z - curPos.z }
        newFaceDir.y = 0.0
        newFaceDir = cc.vec3normalize(newFaceDir)
        local offset = { x = newFaceDir.x * 25.0 * dt, y = newFaceDir.y * 25.0 * dt, z = newFaceDir.z * 25.0 * dt  }
        curPos = { x = curPos.x + offset.x, y = curPos.y + offset.y, z = curPos.z + offset.z}
        self._sprite3D:setPosition3D(curPos)
        offset.x = offset.x
        offset.z = offset.z
        if self._cameraType == CameraType.ThirdCamera then
            local cameraPos = self._camera:getPosition3D()
            cameraPos.x = cameraPos.x + offset.x
            cameraPos.z = cameraPos.z + offset.z
            self._camera:setPosition3D(cameraPos)
        end
    end
end

function Camera3DTestDemo:onEnter()
    self._sprite3D = nil
    local s = cc.Director:getInstance():getWinSize()
    local listener = cc.EventListenerTouchAllAtOnce:create()

    listener:registerScriptHandler(function(touches, event)
        
    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function(touches, event)
        if #touches == 1 then
            local touch = touches[1]
            local location = touch:getLocation()
            local newPos  = cc.p(touch:getPreviousLocation().x - location.x, touch:getPreviousLocation().y - location.y)
            if self._cameraType == CameraType.FreeCamera or self._cameraType == CameraType.FirstCamera then
                local cameraRightDir
                local transformMat = self._camera:getNodeToWorldTransform()
                local cameraDir = { x = -transformMat[9], y = -transformMat[10], z = -transformMat[11] }
                cameraDir = cc.vec3normalize(cameraDir)
                cameraDir.y = 0

                transformMat = self._camera:getNodeToWorldTransform()
                local cameraRightDir = { x = transformMat[1], y = transformMat[2], z = transformMat[3]}
                cameraRightDir = cc.vec3normalize(cameraRightDir)
                cameraRightDir.y = 0

                local cameraPos = self._camera:getPosition3D()
                cameraPos = {x = cameraPos.x + cameraDir.x * newPos.y * 0.1, y = cameraPos.y + cameraDir.y * newPos.y * 0.1, z = cameraPos.z + cameraDir.z * newPos.y * 0.1}
                cameraPos = {x = cameraPos.x + cameraRightDir.x * newPos.x * 0.1, y = cameraPos.y + cameraRightDir.y * newPos.x * 0.1, z = cameraPos.z + cameraRightDir.z * newPos.x * 0.1}
                self._camera:setPosition3D(cameraPos)

                if nil ~= self._sprite3D and self._cameraType == CameraType.FirstCamera then
                    self._sprite3D:setPosition3D(cc.vec3(self._camera:getPositionX(), 0, self._camera:getPositionZ()))
                    self._targetPos = self._sprite3D:getPosition3D()
                end
            end
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)

    listener:registerScriptHandler(function(touches, event)
        for i,v in ipairs(touches) do
            local touch = v
            local location = touch:getLocationInView()
            if self._camera ~= nil and self._sprite3D ~= nil and self._cameraType == CameraType.ThirdCamera then
                local nearP = cc.vec3(location.x, location.y, -1.0)
                local farP  = cc.vec3(location.x, location.y, 1.0)

                nearP = self._camera:unproject(nearP)
                farP  = self._camera:unproject(farP)
                local dir = cc.vec3sub(farP, nearP)
                local dist=0.0
                local ndd = dir.x * 0 + dir.y * 1 + dir.z * 0
                if ndd == 0 then
                    dist=0.0
                end

                local ndo = nearP.x * 0 + nearP.y * 1 + nearP.z * 0
                dist= (0 - ndo) / ndd
                local p =   cc.vec3add(nearP, cc.vec3mul(dir, dist))
                self._targetPos = p
            end
        end
    end, cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local layer3D = cc.Layer:create()
    self:addChild(layer3D,0)
    self._layer3D = layer3D
    self._curState = State.None
    self:addNewSpriteWithCoords(cc.vec3(0, 0, 0), "Sprite3DTest/girl.c3b", true, 0.2, true)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 20

    local label1 = cc.Label:createWithTTF(ttfConfig,"zoom out")
    local menuItem1 = cc.MenuItemLabel:create(label1)
    menuItem1:registerScriptTapHandler(function (tag, sender ) -- zoom out
        if nil ~= self._camera and self._cameraType ~= CameraType.FirstCamera then
            local cameraPos = self._camera:getPosition3D()
            local cameraPosNormalize = cc.vec3normalize(cameraPos)
            cameraPos = {x = cameraPos.x + cameraPosNormalize.x * 5, y = cameraPos.y + cameraPosNormalize.y * 5, z = cameraPos.z + cameraPosNormalize.z * 5}
            self._camera:setPosition3D(cameraPos)
        end
    end)
    self._zoomout = menuItem1

    local label2 = cc.Label:createWithTTF(ttfConfig,"zoom in")
    local menuItem2 = cc.MenuItemLabel:create(label2)
    menuItem2:registerScriptTapHandler(function (tag, sender ) -- zoom in
        if nil ~= self._camera and self._cameraType ~= CameraType.FirstCamera then
            local cameraPos = self._camera:getPosition3D()
            local cameraPosNormalize = cc.vec3normalize(cameraPos)
            cameraPos = {x = cameraPos.x - cameraPosNormalize.x * 5, y = cameraPos.y - cameraPosNormalize.y * 5, z = cameraPos.z - cameraPosNormalize.z * 5}
            self._camera:setPosition3D(cameraPos)
        end
    end)
    self._zoomin = menuItem2

    local label3 = cc.Label:createWithTTF(ttfConfig,"rotate+")
    local menuItem3 = cc.MenuItemLabel:create(label3)
    menuItem3:registerScriptTapHandler(function (tag, sender ) -- rotate +
        if self._cameraType == CameraType.FreeCamera or self._cameraType == CameraType.FirstCamera then
            local  rotation3D = self._camera:getRotation3D()
            rotation3D.y = rotation3D.y + 10
            self._camera:setRotation3D(rotation3D)
        end
    end)
    self._incRot = menuItem3

    local label4 = cc.Label:createWithTTF(ttfConfig,"rotate-")
    local menuItem4 = cc.MenuItemLabel:create(label4)
    menuItem4:registerScriptTapHandler(function (tag, sender ) -- rotate -
        if self._cameraType == CameraType.FreeCamera or self._cameraType == CameraType.FirstCamera then
            local  rotation3D = self._camera:getRotation3D()
            rotation3D.y = rotation3D.y - 10
            self._camera:setRotation3D(rotation3D)
        end
    end)
    self._decRot = menuItem4

    local label5 = cc.Label:createWithTTF(ttfConfig,"free")
    local menuItem5 = cc.MenuItemLabel:create(label5)
    menuItem5:registerScriptTapHandler(function (tag, sender ) -- free
        if self._cameraType == CameraType.FreeCamera then
            return
        end

        self._cameraType = CameraType.FreeCamera
        local pos3D = self._sprite3D:getPosition3D()
        self._camera:setPosition3D(cc.vec3(pos3D.x, pos3D.y + 130, pos3D.z + 130))
        self._camera:lookAt(self._sprite3D:getPosition3D(), cc.vec3(0,1,0))
        self._incRot:setEnabled(true)
        self._decRot:setEnabled(true)
    end)

    local label6 = cc.Label:createWithTTF(ttfConfig,"third person")
    local menuItem6 = cc.MenuItemLabel:create(label6)
    menuItem6:registerScriptTapHandler(function (tag, sender ) -- third person
        if self._cameraType == CameraType.ThirdCamera then
            return
        end

        self._cameraType = CameraType.ThirdCamera

        local pos3D = self._sprite3D:getPosition3D()
        self._camera:setPosition3D(cc.vec3(pos3D.x, pos3D.y + 130, pos3D.z + 130))
        self._camera:lookAt(self._sprite3D:getPosition3D(), cc.vec3(0,1,0))
        self._incRot:setEnabled(false)
        self._decRot:setEnabled(false)
        self._zoomin:setEnabled(true)
        self._zoomout:setEnabled(true)
    end)

    local label7 = cc.Label:createWithTTF(ttfConfig,"first person")
    local menuItem7 = cc.MenuItemLabel:create(label7)
    menuItem7:registerScriptTapHandler(function (tag, sender ) -- first person
        if self._cameraType == CameraType.FirstCamera then
            return
        end

        self._cameraType = CameraType.FirstCamera

        local transformMat = self._sprite3D:getWorldToNodeTransform()
        local newFaceDir = cc.vec3normalize({x = -transformMat[9],y = -transformMat[10], z = -transformMat[11]})
        local pos3D = self._sprite3D:getPosition3D()
        self._camera:setPosition3D(cc.vec3(pos3D.x, pos3D.y + 35, pos3D.z))
        pos3D = self._sprite3D:getPosition3D()
        self._camera:lookAt(cc.vec3add(pos3D, cc.vec3mul(newFaceDir, 50)), cc.vec3(0,1,0))
        self._incRot:setEnabled(true)
        self._decRot:setEnabled(true)
        self._zoomin:setEnabled(false)
        self._zoomout:setEnabled(false)
    end)

    local menu = cc.Menu:create(menuItem1,menuItem2,menuItem3,menuItem4,menuItem5,menuItem6,menuItem7)
    menu:setPosition(cc.p(0, 0))
    menuItem1:setPosition(s.width-50, VisibleRect:top().y-50 )
    menuItem2:setPosition(s.width-50, VisibleRect:top().y-100)
    menuItem3:setPosition(s.width-50, VisibleRect:top().y-150)
    menuItem4:setPosition(s.width-50, VisibleRect:top().y-200)
    menuItem5:setPosition(VisibleRect:left().x+100, VisibleRect:top().y-50)
    menuItem6:setPosition(VisibleRect:left().x+100, VisibleRect:top().y -100)
    menuItem7:setPosition(VisibleRect:left().x+100, VisibleRect:top().y -150)
    self:addChild(menu, 0)

    scheduler:unscheduleScriptEntry(self.schedulerEntry)
    self.schedulerEntry = scheduler:scheduleScriptFunc(function(dt)
        if nil ~= self._sprite3D then
            if self._cameraType == CameraType.ThirdCamera then
                self:updateState(dt)
                if self:isState(self._curState, State.Move) then
                    self:move3D(dt)
                    if self:isState(self._curState, State.Rotate) then
                        local curPos = self._sprite3D:getPosition3D()
                        local newFaceDir = {x = self._targetPos.x - curPos.x, y = self._targetPos.y - curPos.y, z = self._targetPos.z - curPos.z }
                        newFaceDir.y = 0
                        newFaceDir = cc.vec3normalize(newFaceDir)

                        local matTransform = self._sprite3D:getNodeToWorldTransform()
                        local up = {x = matTransform[5], y = matTransform[6] ,z = matTransform[7] }
                        up = cc.vec3normalize(up)
                        local right = {x = -newFaceDir.y * up.z + newFaceDir.z * up.y, y = -newFaceDir.z * up.x + newFaceDir.x * up.z, z = -newFaceDir.x * up.y + newFaceDir.y * up.x}
                        right = cc.vec3normalize(right)

                        local pos = cc.vec3(0, 0, 0)
                        local mat = {}
                        mat[1] = right.x
                        mat[2] = right.y
                        mat[3] = right.z
                        mat[4] = 0.0
    
                        mat[5] = up.x
                        mat[6] = up.y
                        mat[7] = up.z
                        mat[8] = 0.0
    
                        mat[9]  = newFaceDir.x
                        mat[10] = newFaceDir.y
                        mat[11] = newFaceDir.z
                        mat[12] = 0.0
    
                        mat[13] = pos.x
                        mat[14] = pos.y
                        mat[15] = pos.z
                        mat[16] = 1.0
                        self._sprite3D:setAdditionalTransform(mat)
                    end
                end
            end
        end
    end, 0.0, false)

    if self._camera == nil then
        self._camera = cc.Camera:createPerspective(60, s.width / s.height, 1, 1000)
        self._camera:setCameraFlag(cc.CameraFlag.USER1)
        self._layer3D:addChild(self._camera)
    end

    self:SwitchViewCallback(self, CameraType.ThirdCamera)

    local line = cc.DrawNode3D:create()
    --draw x
    for i = -20 ,20 do
        line:drawLine(cc.vec3(-100, 0, 5 * i), cc.vec3(100, 0, 5 * i), cc.c4f(1, 0, 0, 0))
    end

    --draw z
    for i = -20, 20 do
        line:drawLine(cc.vec3(5 * i, 0, -100), cc.vec3(5 * i, 0, 100), cc.c4f(0, 0, 1, 1))
    end

    --draw y
    line:drawLine(cc.vec3(0, -50, 0), cc.vec3(0,0,0), cc.c4f(0, 0.5, 0, 1))
    line:drawLine(cc.vec3(0, 0, 0), cc.vec3(0,50,0), cc.c4f(0, 1, 0, 1))
    self._layer3D:addChild(line)

    self._layer3D:setCameraMask(2)
end

function Camera3DTestDemo:onExit()
    if self._camera ~= nil then
        self._camera = nil
    end

    scheduler:unscheduleScriptEntry(self.schedulerEntry)

end

function Camera3DTestDemo:init()
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

local CameraRotationTest = class("CameraRotationTest", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function CameraRotationTest:ctor()
    -- body
    self:init()
end

function CameraRotationTest:init()
    -- body
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

function CameraRotationTest:onEnter()
    local s = cc.Director:getInstance():getWinSize()
    
    camControlNode = cc.Node:create()
    camControlNode:setNormalizedPosition(cc.p(0.5, 0.5))
    self:addChild(camControlNode)

    camNode = cc.Node:create()
    camNode:setPositionZ(cc.Camera:getDefaultCamera():getPosition3D().z)
    camControlNode:addChild(camNode)

    local sp3d = cc.Sprite3D:create()
    sp3d:setPosition(s.width/2, s.height/2)
    self:addChild(sp3d)
    
    local lship = cc.Label:create()
    lship:setString("Ship")
    lship:setPosition(0, 20)
    sp3d:addChild(lship)
    
    --Billboards
    --Yellow is at the back
    bill1 = cc.BillBoard:create("Images/Icon.png")
    bill1:setPosition3D(cc.vec3(s.width/2 + 50, s.height/2 + 10, -10))
    bill1:setColor(cc.c3b(255, 255,   0))
    bill1:setScale(0.6)
    self:addChild(bill1)
    
    l1 = cc.Label:create()
    l1:setPosition(cc.p(0,-10))
    l1:setString("Billboard1")
    l1:setColor(cc.c3b(255, 255, 255))
    l1:setScale(3)
    bill1:addChild(l1)

    local p1 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
    p1:setPosition(30,80)
    bill1:addChild(p1)
    
    bill2 = cc.BillBoard:create("Images/Icon.png")
    bill2:setPosition3D(cc.vec3(s.width/2 - 50, s.height/2 - 10, 10))
    bill2:setScale(0.6)
    self:addChild(bill2)
    
    l2 = cc.Label:create()
    l2:setString("Billboard2")
    l2:setPosition(cc.p(0,-10))
    l2:setColor(cc.c3b(255, 255, 255))
    l2:setScale(3)
    bill2:addChild(l2)
    
    local p2 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
    p2:setPosition(30,80)
    bill2:addChild(p2)

    --3D models
    local model = cc.Sprite3D:create("Sprite3DTest/boss1.obj")
    model:setScale(4)
    model:setTexture("Sprite3DTest/boss.png")
    model:setPosition3D(cc.vec3(s.width/2, s.height/2, 0))
    self:addChild(model)

    --Listener
    lis = cc.EventListenerTouchOneByOne:create()
    lis:registerScriptHandler(function (touch, event)
        return true
    end,cc.Handler.EVENT_TOUCH_BEGAN )

    lis:registerScriptHandler(function (touch, event)
        local dx = touch:getDelta().x
        local rot = camControlNode:getRotation3D()
        rot.y = rot.y + dx
        camControlNode:setRotation3D(rot)

        local worldPos = cc.vec3(0.0, 0.0, 0.0)
        local decompose = cc.mat4.new(camNode:getNodeToWorldTransform()):decompose(nil, nil, worldPos)
        worldPos = decompose.translation
        cc.Camera:getDefaultCamera():setPosition3D(worldPos)
        cc.Camera:getDefaultCamera():lookAt(camControlNode:getPosition3D())
    end, cc.Handler.EVENT_TOUCH_MOVED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(lis, self)
end

function CameraRotationTest:onExit()

end

function CameraRotationTest:title()
    return "Camera Rotation Test"
end

function CameraRotationTest:subtitle()
    return "Slide to rotate"
end

local FogTestDemo = class("FogTestDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function FogTestDemo:ctor()
    -- body
    self:init()
end

function FogTestDemo:init()
    -- body
    self._layer3D = nil
    self._cameraType = CameraType.FreeCamera
    self._camera = nil
    self._shader = nil
    self._state  = nil

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

function FogTestDemo:setEventListener()
    local listener = cc.EventListenerTouchAllAtOnce:create()

    listener:registerScriptHandler(function(touches, event)
        if #touches == 1 then
            local touch = touches[1]
            local prelocation = touch:getPreviousLocationInView()
            local location = touch:getLocationInView()
            local newPos = cc.p(prelocation.x - location.x, prelocation.y - location.y)
            if self._cameraType == CameraType.FreeCamera then

                local transformMat = self._camera:getNodeToWorldTransform()
                local cameraDir = { x = -transformMat[9], y = -transformMat[10], z = -transformMat[11] }
                cameraDir = cc.vec3normalize(cameraDir)
                cameraDir.y = 0

                transformMat = self._camera:getNodeToWorldTransform()
                local cameraRightDir = { x = transformMat[1], y = transformMat[2], z = transformMat[3]}
                cameraRightDir = cc.vec3normalize(cameraRightDir)
                cameraRightDir.y = 0

                local cameraPos = self._camera:getPosition3D()
                cameraPos = {x = cameraPos.x - cameraDir.x * newPos.y * 0.1, y = cameraPos.y - cameraDir.y * newPos.y * 0.1, z = cameraPos.z - cameraDir.z * newPos.y * 0.1}
                cameraPos = {x = cameraPos.x + cameraRightDir.x * newPos.x * 0.1, y = cameraPos.y + cameraRightDir.y * newPos.x * 0.1, z = cameraPos.z + cameraRightDir.z * newPos.x * 0.1}
                self._camera:setPosition3D(cameraPos)

            end
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function FogTestDemo:createMenu()
    -- body
    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/arial.ttf"
    ttfConfig.fontSize = 20

    local label1 = cc.Label:createWithTTF(ttfConfig,"Linear ")
    local menuItem1 = cc.MenuItemLabel:create(label1)
    menuItem1:registerScriptTapHandler(function (tag, sender )
        self._state:setUniformVec4("u_fogColor", cc.vec4(0.5,0.5,0.5,1.0))
        self._state:setUniformFloat("u_fogStart",10)
        self._state:setUniformFloat("u_fogEnd",60)
        self._state:setUniformInt("u_fogEquation" ,0)

        self._sprite3D1:setGLProgramState(self._state)
        self._sprite3D2:setGLProgramState(self._state)
    end)

    local label2 = cc.Label:createWithTTF(ttfConfig,"Exp")
    local menuItem2 = cc.MenuItemLabel:create(label2)
    menuItem2:registerScriptTapHandler(function (tag, sender )
        self._state:setUniformVec4("u_fogColor", cc.vec4(0.5,0.5,0.5,1.0))
        self._state:setUniformFloat("u_fogDensity",0.03)
        self._state:setUniformInt("u_fogEquation" ,1)

        self._sprite3D1:setGLProgramState(self._state)
        self._sprite3D2:setGLProgramState(self._state)
    end)
    local label3 = cc.Label:createWithTTF(ttfConfig,"Exp2")
    local menuItem3 = cc.MenuItemLabel:create(label3)
    menuItem3:registerScriptTapHandler(function (tag, sender )
        self._state:setUniformVec4("u_fogColor", cc.vec4(0.5,0.5,0.5,1.0))
        self._state:setUniformFloat("u_fogDensity",0.03)
        self._state:setUniformInt("u_fogEquation" ,2)

        self._sprite3D1:setGLProgramState(self._state)
        self._sprite3D2:setGLProgramState(self._state)
    end)
    local menu = cc.Menu:create(menuItem1, menuItem2, menuItem3)
    
    menu:setPosition(cc.p(0.0, 0.0))
    
    menuItem1:setPosition(VisibleRect:left().x + 60, VisibleRect:top().y - 50)
    menuItem2:setPosition(VisibleRect:left().x + 60, VisibleRect:top().y - 100)
    menuItem3:setPosition(VisibleRect:left().x + 60, VisibleRect:top().y - 150)
    self:addChild(menu, 0)
end

function FogTestDemo:createLayer3D()
    -- body
    local s = cc.Director:getInstance():getWinSize()

    local layer3D = cc.Layer:create()
    self:addChild(layer3D,0)
    self._layer3D = layer3D

    self._shader = cc.GLProgram:createWithFilenames("Sprite3DTest/fog.vert","Sprite3DTest/fog.frag")
    self._state  = cc.GLProgramState:create(self._shader)

    self._sprite3D1 = cc.Sprite3D:create("Sprite3DTest/teapot.c3b")
    self._sprite3D2 = cc.Sprite3D:create("Sprite3DTest/teapot.c3b")

    self._sprite3D1:setGLProgramState(self._state)
    self._sprite3D2:setGLProgramState(self._state)

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
    local attributeCount = self._sprite3D1:getMesh():getMeshVertexAttribCount()
    for i = 1, attributeCount do
        local meshattribute = self._sprite3D1:getMesh():getMeshVertexAttribute(i - 1)
        self._state:setVertexAttribPointer(attributeNames[meshattribute.vertexAttrib + 1],
            meshattribute.size, 
            meshattribute.type,
            false,
            self._sprite3D1:getMesh():getVertexSizeInBytes(),
            offset)
        offset = offset + meshattribute.attribSizeBytes
    end

    local offset1 = 0
    local attributeCount1 = self._sprite3D2:getMesh():getMeshVertexAttribCount()
    for i = 1,  attributeCount1 do
        local meshattribute = self._sprite3D2:getMesh():getMeshVertexAttribute(i - 1)
        self._state:setVertexAttribPointer(attributeNames[meshattribute.vertexAttrib + 1],
            meshattribute.size, 
            meshattribute.type,
            false,
            self._sprite3D2:getMesh():getVertexSizeInBytes(),
            offset1)
        offset1 = offset1 + meshattribute.attribSizeBytes
    end

    self._state:setUniformVec4("u_fogColor", cc.vec4(0.5,0.5,0.5,1.0))
    self._state:setUniformFloat("u_fogStart",10)
    self._state:setUniformFloat("u_fogEnd",60)
    self._state:setUniformInt("u_fogEquation" ,0)

    self._layer3D:addChild(self._sprite3D1)
    self._sprite3D1:setPosition3D( cc.vec3( 0, 0,0 ) )
    self._sprite3D1:setScale(2.0)
    self._sprite3D1:setRotation3D(cc.vec3(-90,180,0))

    self._layer3D:addChild(self._sprite3D2)
    self._sprite3D2:setPosition3D( cc.vec3( 0, 0,-20 ) )
    self._sprite3D2:setScale(2.0)
    self._sprite3D2:setRotation3D(cc.vec3(-90,180,0))

    if self._camera == nil then
        self._camera = cc.Camera:createPerspective(60, s.width/s.height, 1, 1000)
        self._camera:setCameraFlag(cc.CameraFlag.USER1)
        self._camera:setPosition3D(cc.vec3(0, 30, 40))
        self._camera:lookAt(cc.vec3(0,0,0), cc.vec3(0, 1, 0))

        self._layer3D:addChild(self._camera)
    end

    self._layer3D:setCameraMask(2)

    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_ANDROID  or targetPlatform == cc.PLATFORM_OS_WINRT  or targetPlatform == cc.PLATFORM_OS_WP8  then
        self._backToForegroundListener = cc.EventListenerCustom:create("event_renderer_recreated", function (eventCustom)
            -- body
            cc.Director:getInstance():setClearColor(cc.c4f(0.5,0.5,0.5,1))
            local glProgram = self._state:getGLProgram()
            glProgram:reset()
            glProgram:initWithFilenames("Sprite3DTest/fog.vert","Sprite3DTest/fog.frag")
            glProgram:link()
            glProgram:updateUniforms()
            
            self._state:setUniformVec4("u_fogColor", cc.vec4(0.5,0.5,0.5,1.0))
            self._state:setUniformFloat("u_fogStart",10)
            self._state:setUniformFloat("u_fogEnd",60)
            self._state:setUniformInt("u_fogEquation" ,0)
        end)
        cc.Director:getInstance():getEventDispatcher():addEventListenerWithFixedPriority(self._backToForegroundListener, -1)
    end
end

function FogTestDemo:onEnter()
    cc.Director:getInstance():setClearColor(cc.c4f(0.5,0.5,0.5,1))
    self:setEventListener()
    self:createMenu()
    self:createLayer3D()
end

function FogTestDemo:onExit()
    cc.Director:getInstance():setClearColor(cc.c4f(0,0,0,1))
    if nil ~= self._camera then
        self._camera = nil
    end
    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_ANDROID  or targetPlatform == cc.PLATFORM_OS_WINRT  or targetPlatform == cc.PLATFORM_OS_WP8  then
        cc.Director:getInstance():getEventDispatcher():removeEventListener(self._backToForegroundListener)
    end
end

function FogTestDemo:title()
    return "Fog Test Demo"
end

function FogTestDemo:subtitle()
    return ""
end

local OperateCamType = 
{
    MoveCamera = 0,
    RotateCamera = 1,
}

local CameraArcBallDemo = class("CameraArcBallDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function CameraArcBallDemo:ctor()
    -- body
    self:init()
end

function CameraArcBallDemo:init()
    self._layer3D = nil
    self._cameraType = CameraType.FreeCamera
    self._camera = nil
    self._drawGrid = nil
    self._sprite3D1 = nil
    self._sprite3D2 = nil
    self._radius    = 1.0
    self._distanceZ = 50.0
    self._operate   = OperateCamType.RotateCamera
    self._center    = cc.vec3(0, 0, 0)
    self._target    = 0

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

function CameraArcBallDemo:projectToSphere(r, x, y)
    local d, t, z
    d = math.sqrt(x*x + y*y)
    --inside sphere
    if d < r * 0.70710678118654752440 then
        z = math.sqrt(r*r - d*d)                      
    else--on hyperbola
        t = r / 1.41421356237309504880
        z = t*t / d
    end
    return z
end

function CameraArcBallDemo:calculateArcBall(axis, angle, p1x, p1y, p2x, p2y)
    local rotation_matrix = cc.mat4.createRotation(self._rotationQuat)
    --rotation y
    local uv = mat4_transformVector(rotation_matrix , 0.0, 1.0, 0.0, 0.0)
    --rotation x
    local sv = mat4_transformVector(rotation_matrix, 1.0, 0.0, 0.0, 0.0)
    --rotation z 
    local lv = mat4_transformVector(rotation_matrix, 0.0, 0.0, -1.0, 0.0)
    --start point screen transform to 3d
    local projectZ1 = self:projectToSphere(self._radius, p1x, p1y)
    local p1 = cc.vec3sub(cc.vec3add(cc.vec3mul(sv, p1x), cc.vec3mul(uv, p1y)), cc.vec3mul(lv, projectZ1))
    --end point screen transform to 3d
    local projectZ2 = self:projectToSphere(self._radius, p2x, p2y)
    local p2 = cc.vec3sub(cc.vec3add(cc.vec3mul(sv, p2x), cc.vec3mul(uv, p2y)), cc.vec3mul(lv, projectZ2))
    --calculate rotation axis
    axis = vec3_cross(p2, p1, axis)
    axis = cc.vec3normalize(axis)

    local pdiff = cc.vec3sub(p2, p1)
    local t = math.sqrt(cc.vec3dot(pdiff, pdiff)) / (2.0 * self._radius)
    --clamp -1 to 1
    if t > 1.0 then
        t = 1.0
    end

    if t < -1.0 then
        t = -1.0
    end
    --rotation angle
    angle = math.asin(t)          

    return axis, angle
end
function CameraArcBallDemo:setEventListener()
    local listener = cc.EventListenerTouchAllAtOnce:create()

    listener:registerScriptHandler(function(touchs, event)
        if #touchs ~= 0 then
            if self._operate == OperateCamType.RotateCamera then
                local visibleSize = cc.Director:getInstance():getVisibleSize()
                local prelocation = touchs[1]:getPreviousLocationInView()
                local location = touchs[1]:getLocationInView()
                location.x = 2.0 * (location.x) / (visibleSize.width) - 1.0
                location.y = 2.0 * (visibleSize.height - location.y) / (visibleSize.height) - 1.0
                prelocation.x = 2.0 * (prelocation.x) / (visibleSize.width) - 1.0
                prelocation.y = 2.0 * (visibleSize.height - prelocation.y) / (visibleSize.height) - 1.0
    
                local axes = cc.vec3(0,0,0)
                local angle = 0.0
                --calculate  rotation quaternion parameters
                axes , angle = self:calculateArcBall(axes, angle, prelocation.x, prelocation.y, location.x, location.y) 
                
                --get rotation quaternion 
                local halfAngle = angle * 0.5
                local sinHalfAngle = math.sin(math.deg(halfAngle))

                local normal = axes
                normal = cc.vec3normalize(normal)
                local quat = cc.quaternion(normal.x * sinHalfAngle, normal.y * sinHalfAngle, normal.z * sinHalfAngle, math.cos(math.deg(halfAngle)))
                local x = quat.w * self._rotationQuat.x + quat.x * self._rotationQuat.w + quat.y * self._rotationQuat.z - quat.z * self._rotationQuat.y
                local y = quat.w * self._rotationQuat.y - quat.x * self._rotationQuat.z + quat.y * self._rotationQuat.w + quat.z * self._rotationQuat.x
                local z = quat.w * self._rotationQuat.z + quat.x * self._rotationQuat.y - quat.y * self._rotationQuat.x + quat.z * self._rotationQuat.w
                local w = quat.w * self._rotationQuat.w - quat.x * self._rotationQuat.x - quat.y * self._rotationQuat.y - quat.z * self._rotationQuat.z
                self._rotationQuat = cc.quaternion(x, y, z, w)
    
                self:updateCameraTransform()
                   
            elseif self._operate == OperateCamType.MoveCamera then
                local previousLocation = touchs[1]:getPreviousLocation()
                local location         = touchs[1]:getLocation()
                local newPos = cc.p(previousLocation.x - location.x, previousLocation.y - location.y)
                self._distanceZ = self._distanceZ - newPos.y * 0.1

                self:updateCameraTransform()
            end
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
end

function CameraArcBallDemo:createLayer3D()
    local s = cc.Director:getInstance():getWinSize()

    cc.MenuItemFont:setFontName("fonts/arial.ttf")
    cc.MenuItemFont:setFontSize(20)
    
    local menuItem1 = cc.MenuItemFont:create("Switch Operation")
    menuItem1:setColor(cc.c3b(0,200,20))
    menuItem1:registerScriptTapHandler(function (tag, sender )
        if self._operate == OperateCamType.MoveCamera then
            self._operate = OperateCamType.RotateCamera
        elseif self._operate == OperateCamType.RotateCamera then
            self._operate = OperateCamType.MoveCamera
        end
    end)
    local menuItem2 = cc.MenuItemFont:create("Switch Target")
    menuItem2:setColor(cc.c3b(0,200,20))
    menuItem2:registerScriptTapHandler(function (tag, sender )
        if self._target == 0 then
            self._target = 1
            self._center = self._sprite3D2:getPosition3D()
            self:updateCameraTransform()
        elseif self._target == 1 then
            self._target = 0
            self._center = self._sprite3D1:getPosition3D()
            self:updateCameraTransform()
        end
    end)
    local menu = cc.Menu:create(menuItem1,menuItem2)
    menu:setPosition(cc.p(0.0, 0.0))
    menuItem1:setPosition(VisibleRect:left().x + 80, VisibleRect:top().y -70)
    menuItem2:setPosition(VisibleRect:left().x + 80, VisibleRect:top().y -100)
    self:addChild(menu, 1)

    local layer3D = cc.Layer:create()
    self:addChild(layer3D,0)
    self._layer3D = layer3D

    if self._camera == nil then
        self._camera = cc.Camera:createPerspective(60, s.width/s.height, 1, 1000)
        self._camera:setCameraFlag(cc.CameraFlag.USER1)
        self._camera:setPosition3D(cc.vec3(0, 10, 50))
        self._camera:lookAt(cc.vec3(0, 0, 0), cc.vec3(0, 1, 0))
        self._layer3D:addChild(self._camera)
    end

    self._sprite3D1 = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    self._sprite3D1:setScale(0.5)
    self._sprite3D1:setRotation3D(cc.vec3(0,180,0))
    self._sprite3D1:setPosition3D(cc.vec3(0,0,0))
    self._layer3D:addChild(self._sprite3D1)

    self._sprite3D2 = cc.Sprite3D:create("Sprite3DTest/boss.c3b")
    self._sprite3D2:setScale(0.6)
    self._sprite3D2:setRotation3D(cc.vec3(-90,0,0))
    self._sprite3D2:setPosition3D(cc.vec3(20,0,0))
    self._layer3D:addChild(self._sprite3D2)

    self._drawGrid = cc.DrawNode3D:create()
    --draw x
    for j = -20, 20 do
        self._drawGrid:drawLine(cc.vec3(-100, 0, 5*j), cc.vec3(100, 0, 5*j),cc.c4f(1, 0, 0, 1))
    end

    --draw z
    for j = -20, 20 do
        self._drawGrid:drawLine(cc.vec3(5*j, 0, -100), cc.vec3(5*j, 0, 100),cc.c4f(0,0,1,1))
    end

    --draw y
    self._drawGrid:drawLine(cc.vec3(0, 0, 0), cc.vec3(0,50,0), cc.c4f(0,1,0,1))

    self._layer3D:addChild(self._drawGrid)

    self._layer3D:setCameraMask(2)
    self:updateCameraTransform()
end

function CameraArcBallDemo:updateCameraTransform()
    -- body
    local trans = cc.mat4.createTranslation(cc.vec3(0.0, 10.0, self._distanceZ))
    local rot = cc.mat4.new(cc.mat4.createRotation(self._rotationQuat))
    local center = cc.mat4.new(cc.mat4.createTranslation(self._center))
    local result = cc.mat4.new(center:multiply(rot)):multiply(trans)

    self._camera:setNodeToParentTransform(result)
end

function CameraArcBallDemo:onEnter()
    self._rotationQuat = cc.quaternion(0.0, 0.0, 0.0, 1.0)
    self:setEventListener()
    self:createLayer3D()
end

function CameraArcBallDemo:onExit()
    if self._camera ~= nil then
        self._camera = nil
    end
end

function CameraArcBallDemo:title()
    return "Camera ArcBall Moving"
end

function CameraArcBallDemo:subtitle()
    return ""
end

function Camera3DTestMain()
    cclog("Camera3DTestMain")
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Camera3DTestDemo.create,
        CameraRotationTest.create,
        FogTestDemo.create,
        CameraArcBallDemo.create,
    }
    scene:addChild(Helper.createFunctionTable[1]())
    scene:addChild(CreateBackMenuItem())
    

    return scene
end
