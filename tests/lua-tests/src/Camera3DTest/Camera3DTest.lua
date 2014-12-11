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
    return cc.Layer:create()
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
        self._camera:setPosition3D(cc.vec3(0 + pos3D.x, 130 + pos3D.y, 130 + pos3D.z))
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
        self._camera:lookAt(cc.vec3(pos3D.x + newFaceDir.x * 50, pos3D.y + newFaceDir.y * 50, pos3D.z + newFaceDir.z * 50), cc.vec3(0, 1, 0))
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
                
                local size = cc.Director:getInstance():getWinSize()
                nearP = self._camera:unproject(size, nearP, nearP)
                farP  = self._camera:unproject(size, farP, farP)
                local dir = cc.vec3(farP.x - nearP.x, farP.y - nearP.y, farP.z - nearP.z)
                local dist=0.0
                local ndd = dir.x * 0 + dir.y * 1 + dir.z * 0
                if ndd == 0 then
                    dist=0.0
                end

                local ndo = nearP.x * 0 + nearP.y * 1 + nearP.z * 0
                dist= (0 - ndo) / ndd
                local p =   cc.vec3(nearP.x + dist * dir.x, nearP.y + dist * dir.y, nearP.z + dist * dir.z)
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
        self._camera:lookAt(cc.vec3(pos3D.x + newFaceDir.x * 50, pos3D.y + newFaceDir.y * 50 , pos3D.z + newFaceDir.z * 50), cc.vec3(0,1,0))
        self._incRot:setEnabled(true)
        self._decRot:setEnabled(true)
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
    self:registerScriptHandler(function (event)
    if event == "enter" then
        self:onEnter()
    elseif event == "exit" then
        self:onExit()
    end
    end)
end

function Camera3DTestMain()
    cclog("Camera3DTestMain")
    local scene = cc.Scene:create()
    scene:addChild(Camera3DTestDemo.new())
    scene:addChild(CreateBackMenuItem())
    

    return scene
end
