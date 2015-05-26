require "cocos.3d.3dConstants"

----------------------------------------
----TerrainSimple
----------------------------------------
local TerrainSimple = class("TerrainSimple", function ()
    local layer = cc.Layer:create()

    return layer
end)

function TerrainSimple:ctor()
    -- body
    self:init()
end

function TerrainSimple:init()


    local visibleSize = cc.Director:getInstance():getVisibleSize()

    --use custom camera
    self._camera = cc.Camera:createPerspective(60, visibleSize.width/visibleSize.height, 0.1, 800)
    self._camera:setCameraFlag(cc.CameraFlag.USER1)
    self._camera:setPosition3D(cc.vec3(-1, 1.6, 4))
    self:addChild(self._camera)

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local detailMapR = { _detailMapSrc = "TerrainTest/dirt.jpg", _detailMapSize = 35}
    local detailMapG = { _detailMapSrc = "TerrainTest/Grass2.jpg", _detailMapSize = 35}
    local detailMapB = { _detailMapSrc = "TerrainTest/road.jpg", _detailMapSize = 35}
    local detailMapA = { _detailMapSrc = "TerrainTest/GreenSkin.jpg", _detailMapSize = 35}
    local terrainData = { _heightMapSrc = "TerrainTest/heightmap16.jpg", _alphaMapSrc = "TerrainTest/alphamap.png" , _detailMaps = {detailMapR, detailMapG, detailMapB, detailMapA}, _detailMapAmount = 4 }

    self._terrain = cc.Terrain:create(terrainData,cc.Terrain.CrackFixedType.SKIRT)
    self._terrain:setLODDistance(3.2, 6.4, 9.6)
    self._terrain:setMaxDetailMapAmount(4)
    self:addChild(self._terrain)
    self._terrain:setCameraMask(2)
    self._terrain:setDrawWire(false)

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function (touches, event)
        local delta = cc.Director:getInstance():getDeltaTime()
        local touch = touches[1]
        local location = touch:getLocation()
        local previousLocation = touch:getPreviousLocation()
        local newPos = {x=previousLocation.x - location.x, y=previousLocation.y - location.y}

        local matTransform = self:getNodeToWorldTransform()

        local cameraDir = {x = -matTransform[9], y = -matTransform[10], z = -matTransform[11]}
        cameraDir = cc.vec3normalize(cameraDir)
        cameraDir.y = 0

        local cameraRightDir = {x = matTransform[1], y = matTransform[2], z = matTransform[3]}
        cameraRightDir = cc.vec3normalize(cameraRightDir)
        cameraRightDir.y = 0

        local cameraPos = self._camera:getPosition3D()
        cameraPos = { x = cameraPos.x + cameraDir.x * newPos.y * 0.5 * delta, y = cameraPos.y + cameraDir.y * newPos.y * 0.5 * delta, z = cameraPos.z + cameraDir.z * newPos.y * 0.5 * delta }
        cameraPos = { x = cameraPos.x + cameraRightDir.x * newPos.x * 0.5 * delta, y = cameraPos.y + cameraRightDir.y * newPos.x * 0.5 * delta, z = cameraPos.z + cameraRightDir.z * newPos.x * 0.5 * delta }
        self._camera:setPosition3D(cameraPos)

    end,cc.Handler.EVENT_TOUCHES_MOVED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    --add Particle3D for test blend
    local rootps = cc.PUParticleSystem3D:create("Particle3D/scripts/mp_torch.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, 0)
end

function TerrainSimple:title()
    return "Terrain with skirt"
end

function TerrainSimple:subtitle()
    return "Drag to walkThru"
end

----------------------------------------
----TerrainWalkThru
----------------------------------------

local PLAER_STATE =
{
    LEFT     = 0,
    RIGHT    = 1,
    IDLE     = 2,
    FORWARD  = 3, 
    BACKWARD = 4,
}

local PLAYER_HEIGHT = 0

local camera_offset = cc.vec3(0, 45, 60)

local Player = class("Player", function(file, cam, terrain)
    local sprite = cc.Sprite3D:create(file)
    if nil ~= sprite then
        sprite._headingAngle = 0
        sprite._playerState = PLAER_STATE.IDLE
        sprite._cam = cam
        sprite._terrain = terrain
    end
    return sprite
end)

function Player:ctor()
    -- body
    self:init()      
end

function Player:init()
    self._headingAxis = cc.vec3(0.0, 0.0, 0.0)
    self:scheduleUpdateWithPriorityLua(function(dt)
        local curPos = self:getPosition3D()
        if self._playerState == PLAER_STATE.IDLE then

        elseif self._playerState == PLAER_STATE.FORWARD then
            local newFaceDir = cc.vec3( self._targetPos.x - curPos.x, self._targetPos.y - curPos.y, self._targetPos.z - curPos.z)
            newFaceDir.y = 0.0
            newFaceDir = cc.vec3normalize(newFaceDir)
            local offset = cc.vec3(newFaceDir.x * 25.0 * dt, newFaceDir.y * 25.0 * dt, newFaceDir.z * 25.0 * dt)
            curPos = cc.vec3(curPos.x + offset.x, curPos.y + offset.y, curPos.z + offset.z)
            self:setPosition3D(curPos)
        elseif self._playerState ==  PLAER_STATE.BACKWARD then
            
            local transform   = self:getNodeToWorldTransform()
            local forward_vec = cc.vec3(-transform[9], -transform[10], -transform[11])
            forward_vec = cc.vec3normalize(forward_vec)
            self:setPosition3D(cc.vec3(curPos.x - forward_vec.x * 15 * dt, curPos.y - forward_vec.y * 15 * dt, curPos.z - forward_vec.z * 15 *dt))
        elseif self._playerState == PLAER_STATE.LEFT then
            player:setRotation3D(cc.vec3(curPos.x, curPos.y + 25 * dt, curPos.z))
        elseif self._playerState == PLAER_STATE.RIGHT then
            player:setRotation3D(cc.vec3(curPos.x, curPos.y - 25 * dt, curPos.z))
        end

        local normal = cc.vec3(0.0, 0.0, 0.0)
        local player_h, normal = self._terrain:getHeight(self:getPositionX(), self:getPositionZ(), normal)
        self:setPositionY(player_h + PLAYER_HEIGHT)

        --need to scriptfile
        local q2 = cc.quaternion_createFromAxisAngle(cc.vec3(0, 1, 0), -math.pi)
        local headingQ = cc.quaternion_createFromAxisAngle(self._headingAxis, self._headingAngle)
        local x = headingQ.w * q2.x + headingQ.x * q2.w + headingQ.y * q2.z - headingQ.z * q2.y
        local y = headingQ.w * q2.y - headingQ.x * q2.z + headingQ.y * q2.w + headingQ.z * q2.x
        local z = headingQ.w * q2.z + headingQ.x * q2.y - headingQ.y * q2.x + headingQ.z * q2.w
        local w = headingQ.w * q2.w - headingQ.x * q2.x - headingQ.y * q2.y - headingQ.z * q2.z
        headingQ = cc.quaternion(x, y, z, w)
        self:setRotationQuat(headingQ)

        local vec_offset = cc.vec4(camera_offset.x, camera_offset.y, camera_offset.z, 1)
        local transform  = self:getNodeToWorldTransform()
        local dst = cc.vec4(0.0, 0.0, 0.0, 0.0)
        vec_offset = mat4_transformVector(transform, vec_offset, dst)
        local playerPos = self:getPosition3D()
        self._cam:setPosition3D(cc.vec3(playerPos.x + camera_offset.x, playerPos.y + camera_offset.y, playerPos.z + camera_offset.z))
        self:updateState()
    end, 0)

    self:registerScriptHandler(function (event)
        -- body
        if "exit" == event then
            self:unscheduleUpdate()
        end
    end)
end

function Player:updateState()
    if self._playerState == PLAER_STATE.FORWARD then
        local player_pos = cc.p(self:getPositionX(),self:getPositionZ())
        local targetPos = cc.p(self._targetPos.x, self._targetPos.z)
        local dist = cc.pGetDistance(player_pos, targetPos)
        if dist < 1 then
            self._playerState = PLAER_STATE.IDLE
        end
    end
end

local TerrainWalkThru = class("TerrainWalkThru", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function TerrainWalkThru:ctor()
    -- body
    self:init()
end

function TerrainWalkThru:init()
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local listener = cc.EventListenerTouchAllAtOnce:create()

    listener:registerScriptHandler(function (touches, event)

    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function (touches, event)

        local touch = touches[1]
        local location = touch:getLocationInView()
        if self._camera ~= nil then
            if self._player ~= nil then
                local nearP = cc.vec3(location.x, location.y, 0.0)
                local farP  = cc.vec3(location.x, location.y, 1.0)

                local size = cc.Director:getInstance():getWinSize()
                nearP = self._camera:unproject(size, nearP, nearP)
                farP  = self._camera:unproject(size, farP, farP)
                local dir = cc.vec3(farP.x - nearP.x, farP.y - nearP.y, farP.z - nearP.z)
                dir = cc.vec3normalize(dir)

                local rayStep = cc.vec3(15 * dir.x, 15 * dir.y, 15 * dir.z)
                local rayPos =  nearP
                local rayStartPosition = nearP
                local lastRayPosition  = rayPos
                rayPos = cc.vec3(rayPos.x + rayStep.x, rayPos.y + rayStep.y, rayPos.z + rayStep.z)
                -- Linear search - Loop until find a point inside and outside the terrain Vector3 
                local height = self._terrain:getHeight(rayPos.x, rayPos.z)

                while rayPos.y > height do
                    lastRayPosition = rayPos 
                    rayPos = cc.vec3(rayPos.x + rayStep.x, rayPos.y + rayStep.y, rayPos.z + rayStep.z)
                    height = self._terrain:getHeight(rayPos.x,rayPos.z) 
                end

                local startPosition = lastRayPosition
                local endPosition   = rayPos

                for i = 1, 32 do
                    -- Binary search pass 
                    local middlePoint = cc.vec3(0.5 * (startPosition.x + endPosition.x), 0.5 * (startPosition.y + endPosition.y), 0.5 * (startPosition.z + endPosition.z))
                    if (middlePoint.y < height) then
                        endPosition = middlePoint 
                    else 
                        startPosition = middlePoint
                    end
                end

                local collisionPoint = cc.vec3(0.5 * (startPosition.x + endPosition.x), 0.5 * (startPosition.y + endPosition.y), 0.5 * (startPosition.z + endPosition.z))
                local playerPos = self._player:getPosition3D()
                dir = cc.vec3(collisionPoint.x - playerPos.x, collisionPoint.y - playerPos.y, collisionPoint.z - playerPos.z)
                dir.y = 0
                dir = cc.vec3normalize(dir)
                self._player._headingAngle =  -1 * math.acos(-dir.z)

                self._player._headingAxis = vec3_cross(dir, cc.vec3(0, 0, -1), self._player._headingAxis)
                self._player._targetPos = collisionPoint
                -- self._player:forward()
                self._player._playerState = PLAER_STATE.FORWARD
            end
        end
    end,cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local visibleSize = cc.Director:getInstance():getVisibleSize()
    self._camera = cc.Camera:createPerspective(60, visibleSize.width/visibleSize.height, 0.1, 200)
    self._camera:setCameraFlag(cc.CameraFlag.USER1)
    self:addChild(self._camera)

    local detailMapR = { _detailMapSrc = "TerrainTest/dirt.jpg", _detailMapSize = 35}
    local detailMapG = { _detailMapSrc = "TerrainTest/Grass2.jpg", _detailMapSize = 10}
    local detailMapB = { _detailMapSrc = "TerrainTest/road.jpg", _detailMapSize = 35}
    local detailMapA = { _detailMapSrc = "TerrainTest/GreenSkin.jpg", _detailMapSize = 20}
    local terrainData = { _heightMapSrc = "TerrainTest/heightmap16.jpg", _alphaMapSrc = "TerrainTest/alphamap.png" , _detailMaps = {detailMapR, detailMapG, detailMapB, detailMapA}, _detailMapAmount = 4, _mapHeight = 40.0, _mapScale = 2.0 }

    self._terrain = cc.Terrain:create(terrainData,cc.Terrain.CrackFixedType.SKIRT)
    self._terrain:setMaxDetailMapAmount(4)
    self._terrain:setCameraMask(2)
    self._terrain:setDrawWire(false)

    self._terrain:setSkirtHeightRatio(3)
    self._terrain:setLODDistance(64,128,192)

    self._player = Player:create("Sprite3DTest/girl.c3b", self._camera, self._terrain)
    self._player:setCameraMask(2)
    self._player:setScale(0.08)
    self._player:setPositionY(self._terrain:getHeight(self._player:getPositionX(), self._player:getPositionZ()) + PLAYER_HEIGHT)

    --add Particle3D for test blend
    local rootps = cc.PUParticleSystem3D:create("Particle3D/scripts/mp_torch.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:setScale(30.0)
    rootps:startParticleSystem()
    self._player:addChild(rootps)

    --add BillBoard for test blend
    local billboard = cc.BillBoard:create("Images/btn-play-normal.png")
    billboard:setPosition3D(cc.vec3(0,180,0))
    billboard:setCameraMask(cc.CameraFlag.USER1)
    self._player:addChild(billboard)

    local animation = cc.Animation3D:create("Sprite3DTest/girl.c3b","Take 001")
    if nil ~= animation then
        local animate = cc.Animate3D:create(animation)
        self._player:runAction(cc.RepeatForever:create(animate))
    end

    local playerPos = self._player:getPosition3D()
    self._camera:setPosition3D(cc.vec3(playerPos.x + camera_offset.x, playerPos.y + camera_offset.y, playerPos.z + camera_offset.z))
    self._camera:setRotation3D(cc.vec3(-45,0,0))

    self:addChild(self._player)
    self:addChild(self._terrain)
end

function TerrainWalkThru:title()
    return "Player walk around in terrain"
end

function TerrainWalkThru:subtitle()
    return "touch to move"
end

function TerrainTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable =
    {
        TerrainSimple.create,
        TerrainWalkThru.create,
    }

    scene:addChild(TerrainSimple.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end