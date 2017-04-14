
local START_POS_X = -0.5
local START_POS_Y = -2.5
local START_POS_Z = -0.5

local ARRAY_SIZE_X = 4
local ARRAY_SIZE_Y = 3
local ARRAY_SIZE_Z = 4
----------------------------------------
----Physics3DTestDemo
----------------------------------------
local Physics3DTestDemo = class("Physics3DTestDemo", function ()
    -- body
    local layer = cc.Layer:create()
    return layer
end)

function Physics3DTestDemo:ctor()

    Helper.initWithLayer(self)
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    local function onNodeEvent(event)
        if "enter" == event then
            self:onEnter()
        elseif "exit" == event then
            self:onExit()
        end
    end

    self:registerScriptHandler(onNodeEvent)
end

function Physics3DTestDemo:title()
    return "Physics3D Test"
end

function Physics3DTestDemo:subtitle()
    return ""
end

function Physics3DTestDemo:shootBox(des)
    local rbDes = {}
    local cameraPosition = self._camera:getPosition3D()
    local linearVec = cc.vec3normalize(cc.vec3sub(des, cameraPosition))
    linearVec = cc.vec3mul(linearVec, 100)

    rbDes.originalTransform = cc.mat4.translate(cc.mat4.createIdentity(), self._camera:getPosition3D())
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(0.5, 0.5, 0.5))

    local sprite = cc.PhysicsSprite3D:create("Sprite3DTest/box.c3t", rbDes)
    sprite:setTexture("Images/Icon.png")

    local rigidBody = sprite:getPhysicsObj()
    rigidBody:setLinearFactor(cc.vec3(1.0, 1.0, 1.0))
    rigidBody:setLinearVelocity(linearVec)
    rigidBody:setAngularVelocity(cc.vec3(0.0, 0.0, 0.0))
    rigidBody:setCcdMotionThreshold(0.5)
    rigidBody:setCcdSweptSphereRadius(0.4)

    self:addChild(sprite)
    sprite:setPosition3D(self._camera:getPosition3D())
    sprite:setScale(0.5)
    sprite:syncNodeToPhysics()
    
    --optimize, only sync node to physics
    sprite:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE) --sync node to physics
    
    sprite:setCameraMask(cc.CameraFlag.USER1) 
end

function Physics3DTestDemo:onEnter()
    local scene = cc.Director:getInstance():getRunningScene()
    if nil ~= scene then
        self._physicsScene = scene
        local physics3DWorld = scene:getPhysics3DWorld()
        physics3DWorld:setDebugDrawEnable(false)

        local size = cc.Director:getInstance():getWinSize()
        self._camera = cc.Camera:createPerspective(30.0, size.width / size.height, 1.0, 1000.0)
        self._camera:setPosition3D(cc.vec3(0.0, 50.0, 100.0))
        self._camera:lookAt(cc.vec3(0.0, 0.0, 0.0), cc.vec3(0.0, 1.0, 0.0))
        self._camera:setCameraFlag(cc.CameraFlag.USER1)
        self:addChild(self._camera)

        if Helper.index ~= 2 then
            local listener = cc.EventListenerTouchAllAtOnce:create()
            listener:registerScriptHandler(function(touches, event)
                self._needShootBox = true
            end,cc.Handler.EVENT_TOUCHES_BEGAN)

            listener:registerScriptHandler(function(touches, event)

                if #touches > 0 and self._camera ~= nil then
                    local touch = touches[1]
                    local delta = touch:getDelta()

                    self._angle = self._angle - delta.x * math.pi / 180.0
                    self._camera:setPosition3D(cc.vec3(100.0 * math.sin(self._angle), 50.0, 100.0 * math.cos(self._angle)))
                    self._camera:lookAt(cc.vec3(0.0, 0.0, 0.0), cc.vec3(0.0, 1.0, 0.0))
    
                    if (delta.x * delta.x + delta.y * delta.y) > 16 then
                        self._needShootBox = false
                    end
                end
            end, cc.Handler.EVENT_TOUCHES_MOVED)

            listener:registerScriptHandler(function(touches, event)
                if self._needShootBox == false then
                    return
                end

                if #touches > 0 then
                    local location = touches[1]:getLocationInView()
                    local nearP = cc.vec3(location.x, location.y, -1.0)
                    local farP = cc.vec3(location.x, location.y, 1.0)
                    nearP = self._camera:unproject(nearP)
                    farP  = self._camera:unproject(farP)
    
                    local dir = cc.vec3sub(farP, nearP)
                    local cameraPosition = self._camera:getPosition3D()
                    self:shootBox(cc.vec3add(cameraPosition, cc.vec3mul(dir, 10)))
                end
            end, cc.Handler.EVENT_TOUCHES_ENDED)

            local eventDispatcher = self:getEventDispatcher()
            eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)
        end
        
        local ttfConfig = {}
        ttfConfig.fontFilePath = "fonts/arial.ttf"
        ttfConfig.fontSize = 10
        local label = cc.Label:createWithTTF(ttfConfig,"DebugDraw OFF")
        local menuItem = cc.MenuItemLabel:create(label)
        menuItem:registerScriptTapHandler(function (tag, sender)
            if physics3DWorld:isDebugDrawEnabled() then
                physics3DWorld:setDebugDrawEnable(false)
                label:setString("DebugDraw OFF")
            else
                physics3DWorld:setDebugDrawEnable(true)
                label:setString("DebugDraw ON")
            end
        end)

        local menu = cc.Menu:create(menuItem)
        menu:setPosition(cc.p(0.0,0.0))
        menuItem:setAnchorPoint(cc.p(0.0, 1.0))
        menuItem:setPosition(cc.p(VisibleRect:left().x, VisibleRect:top().y-50))
        self:addChild(menu)

        self._angle = 0.0

        self:extend()
    end
end

function Physics3DTestDemo:onExit()

end

function Physics3DTestDemo:extend()
    
end

----------------------------------------
----BasicPhysics3DDemo
----------------------------------------
local BasicPhysics3DDemo = class("BasicPhysics3DDemo", Physics3DTestDemo)

function BasicPhysics3DDemo:subtitle()
    return "Basic Physics3D"
end

function BasicPhysics3DDemo:extend()
    local rbDes = {}
    rbDes.mass = 0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(60.0, 1.0, 60.0))

    local floor = cc.PhysicsSprite3D:create("Sprite3DTest/box.c3t", rbDes)
    floor:setTexture("Sprite3DTest/plane.png")
    floor:setScaleX(60)
    floor:setScaleZ(60)
    self:addChild(floor)
    floor:setCameraMask(cc.CameraFlag.USER1)
    floor:syncNodeToPhysics()
    floor:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.NONE)

    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(0.8, 0.8, 0.8))

    local start_x = START_POS_X - ARRAY_SIZE_X/2
    local start_y = START_POS_Y
    local start_z = START_POS_Z - ARRAY_SIZE_Z/2

    for k = 1, ARRAY_SIZE_Y do
        for i = 1, ARRAY_SIZE_X do
            for j = 1, ARRAY_SIZE_Z do
                local x = 1.0 * (i - 1) + start_x
                local y = 5.0+1.0 * (k - 1) + start_y
                local z = 1.0 * (j - 1) + start_z
                
                local sprite = cc.PhysicsSprite3D:create("Sprite3DTest/box.c3t", rbDes)
                sprite:setTexture("Images/CyanSquare.png")
                sprite:setPosition3D(cc.vec3(x, y, z))
                sprite:syncNodeToPhysics()
                sprite:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE)
                sprite:setCameraMask(cc.CameraFlag.USER1)
                sprite:setScale(0.8)
                self:addChild(sprite)
            end
        end
    end

    self._physicsScene:setPhysics3DDebugCamera(self._camera)
end

----------------------------------------
----Physics3DConstraintDemo
----------------------------------------
local Physics3DConstraintDemo = class("Physics3DConstraintDemo", Physics3DTestDemo)

function Physics3DConstraintDemo:subtitle()
    return "Physics3D Constraint"
end

function Physics3DConstraintDemo:extend()

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function(touches, event)
        if nil ~= self._camera then
            local touch = touches[1]
            local location = touch:getLocationInView()
            local nearP = cc.vec3(location.x, location.y, 0.0) 
            local farP  = cc.vec3(location.x, location.y, 1.0)
        
            local size = cc.Director:getInstance():getWinSize()
            nearP = self._camera:unproject(size, nearP, nearP)
            farP  = self._camera:unproject(size, farP, farP)

            local physicsWorld = self._physicsScene:getPhysics3DWorld()
            local hitResult = {}
            local ret = false
            ret, hitResult = physicsWorld:rayCast(nearP, farP, hitResult)
            if true == ret and nil ~= hitResult.hitObj and hitResult.hitObj:getObjType() == cc.Physics3DObject.PhysicsObjType.RIGID_BODY then
                local mat = cc.mat4.getInversed(hitResult.hitObj:getWorldTransform())
                local position = cc.mat4.transformVector(mat, cc.vec4(hitResult.hitPosition.x, hitResult.hitPosition.y, hitResult.hitPosition.z, 1.0))

                self._constraint = cc.Physics3DPointToPointConstraint:create(hitResult.hitObj, position)
                physicsWorld:addPhysics3DConstraint(self._constraint, true)
                self._pickingDistance = math.sqrt(math.pow(hitResult.hitPosition.x - nearP.x, 2) + math.pow(hitResult.hitPosition.y - nearP.y, 2) + math.pow(hitResult.hitPosition.z - nearP.z, 2))
                return
            end
        end
        self._needShootBox = false
    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function(touches, event)

        if self._constraint ~= nil then
            local touch = touches[1]
            local location = touch:getLocationInView()
            local nearP = cc.vec3(location.x, location.y, 0.0)
            local farP  = cc.vec3(location.x, location.y, 1.0) 

            local size = cc.Director:getInstance():getWinSize()
            nearP = self._camera:unproject(size, nearP, nearP)
            farP  = self._camera:unproject(size, farP, farP)
            local dir = cc.vec3normalize(cc.vec3sub(farP, nearP))
            self._constraint:setPivotPointInB(cc.vec3add(nearP, cc.vec3mul(dir, self._pickingDistance)))
            return
        end

        if #touches > 0 and self._camera ~= nil then
            local touch = touches[1]
            local delta = touch:getDelta()

            self._angle = self._angle - delta.x * math.pi / 180.0
            self._camera:setPosition3D(cc.vec3(100.0 * math.sin(self._angle), 50.0, 100.0 * math.cos(self._angle)))
            self._camera:lookAt(cc.vec3(0.0, 0.0, 0.0), cc.vec3(0.0, 1.0, 0.0))

            if (delta.x * delta.x + delta.y * delta.y) > 16 then
                self._needShootBox = false
            end
        end
    end, cc.Handler.EVENT_TOUCHES_MOVED)

    listener:registerScriptHandler(function(touches, event)

        if self._constraint ~= nil then
            self._physicsScene:getPhysics3DWorld():removePhysics3DConstraint(self._constraint)
            self._constraint = nil
            return
        end

        if self._needShootBox == false then
            return
        end

        if #touches > 0 then
            local location = touches[1]:getLocationInView()
            local nearP = cc.vec3(location.x, location.y, -1.0)
            local farP = cc.vec3(location.x, location.y, 1.0)
            nearP = self._camera:unproject(nearP)
            farP  = self._camera:unproject(farP)

            local dir = cc.vec3sub(farP, nearP)
            local cameraPosition = self._camera:getPosition3D()
            self:shootBox(cc.vec3add(cameraPosition, cc.vec3mul(dir, 10)))
        end
    end, cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local rbDes = {}
    rbDes.disableSleep = true
    --create box
    local sprite = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    rbDes.mass = 10.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(5.0, 5.0, 5.0))
    local rigidBody = cc.Physics3DRigidBody:create(rbDes)

    local quat = cc.quaternion_createFromAxisAngle(cc.vec3(0, 1, 0), math.pi)
    local component = cc.Physics3DComponent:create(rigidBody, cc.vec3(0.0, -3.0, 0.0), quat)

    sprite:addComponent(component)
    self:addChild(sprite)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    sprite:setScale(0.4)
    sprite:setPosition3D(cc.vec3(-20.0, 5.0, 0.0))
    --sync node position to physics
    component:syncNodeToPhysics()
    --physics controlled, we will not set position for it, so we can skip sync node position to physics
    component:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE)

    self._physicsScene:setPhysics3DDebugCamera(self._camera)

    local physicsWorld = self._physicsScene:getPhysics3DWorld()
    --create point to point constraint
    local constraint = cc.Physics3DPointToPointConstraint:create(rigidBody, cc.vec3(2.5, 2.5, 2.5))
    physicsWorld:addPhysics3DConstraint(constraint)

    --create hinge constraint
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(8.0, 8.0, 1.0))
    rigidBody = cc.Physics3DRigidBody:create(rbDes)
    component = cc.Physics3DComponent:create(rigidBody)
    sprite = cc.Sprite3D:create("Sprite3DTest/box.c3t")
    sprite:setTexture("Sprite3DTest/plane.png")
    sprite:setScaleX(8.0)
    sprite:setScaleY(8.0)
    sprite:setPosition3D(cc.vec3(5.0, 0.0, 0.0))
    sprite:addComponent(component)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)
    component:syncNodeToPhysics()
    rigidBody:setAngularVelocity(cc.vec3(0,3,0))
    constraint = cc.Physics3DHingeConstraint:create(rigidBody, cc.vec3(4.0, 4.0, 0.5), cc.vec3(0.0, 1.0, 0.0))
    physicsWorld:addPhysics3DConstraint(constraint)

    --create slider constraint
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(3.0, 2.0, 3.0))
    rigidBody = cc.Physics3DRigidBody:create(rbDes)
    component = cc.Physics3DComponent:create(rigidBody)
    sprite = cc.Sprite3D:create("Sprite3DTest/box.c3t")
    sprite:setTexture("Sprite3DTest/plane.png")
    sprite:setScaleX(3.0)
    sprite:setScaleZ(3.0)
    sprite:setPosition3D(cc.vec3(30.0, 15.0, 0.0))
    sprite:addComponent(component)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)
    component:syncNodeToPhysics()
    rigidBody:setLinearVelocity(cc.vec3(0,3,0))

    rbDes.mass = 0.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(3.0, 3.0, 3.0))
    local rigidBodyB = cc.Physics3DRigidBody:create(rbDes)
    component = cc.Physics3DComponent:create(rigidBodyB)
    sprite = cc.Sprite3D:create("Sprite3DTest/box.c3t")
    sprite:setTexture("Sprite3DTest/plane.png")
    sprite:setScale(3.0)
    sprite:setPosition3D(cc.vec3(30.0, 5.0, 0.0))
    sprite:addComponent(component)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)
    component:syncNodeToPhysics()

    local frameInA = cc.mat4.createRotationZ(cc.mat4.createIdentity(), math.pi / 2)
    local frameInB = {}
    for i=1,16 do
        frameInB[i] = frameInA[i]
    end
    frameInA[14] = -5.0
    frameInB[14] = 5.0
    constraint = cc.Physics3DSliderConstraint:create(rigidBody, rigidBodyB, frameInA, frameInB, false)
    physicsWorld:addPhysics3DConstraint(constraint)
    constraint:setLowerLinLimit(-5.0)
    constraint:setUpperLinLimit(5.0)

    --create ConeTwist constraint
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(3.0, 3.0, 3.0))
    rigidBody = cc.Physics3DRigidBody:create(rbDes)
    component = cc.Physics3DComponent:create(rigidBody)
    sprite = cc.Sprite3D:create("Sprite3DTest/box.c3t")
    sprite:setTexture("Sprite3DTest/plane.png")
    sprite:setScale(3.0)
    sprite:setPosition3D(cc.vec3(-10.0, 5.0, 0.0))
    sprite:addComponent(component)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)
    component:syncNodeToPhysics()

    frameInA = cc.mat4.createRotationZ(frameInA, math.pi / 2)
    frameInA[13] = 0.0
    frameInA[14] = -10.0
    frameInA[15] = 0.0
    constraint = cc.Physics3DConeTwistConstraint:create(rigidBody, frameInA)
    physicsWorld:addPhysics3DConstraint(constraint, true)
    constraint:setLimit(math.pi / 180 * 10, math.pi / 180 * 10, math.pi / 180 * 40)

    --reate 6 dof constraint
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(3.0, 3.0, 3.0))
    rigidBody = cc.Physics3DRigidBody:create(rbDes)
    component = cc.Physics3DComponent:create(rigidBody)
    sprite = cc.Sprite3D:create("Sprite3DTest/box.c3t")
    sprite:setTexture("Sprite3DTest/plane.png")
    sprite:setScale(3.0)
    sprite:setPosition3D(cc.vec3(30.0, -5.0, 0.0))
    sprite:addComponent(component)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)
    component:syncNodeToPhysics()
    frameInA = cc.mat4.setIdentity(frameInA)
    constraint = cc.Physics3D6DofConstraint:create(rigidBody, frameInA, false)
    physicsWorld:addPhysics3DConstraint(constraint)
    constraint:setAngularLowerLimit(cc.vec3(0,0,0))
    constraint:setAngularUpperLimit(cc.vec3(0,0,0))
    constraint:setLinearLowerLimit(cc.vec3(-10,0,0))
    constraint:setLinearUpperLimit(cc.vec3(10,0,0))
end

----------------------------------------
----Physics3DKinematicDemo
----------------------------------------
local Physics3DKinematicDemo = class("Physics3DKinematicDemo", Physics3DTestDemo)

function Physics3DKinematicDemo:subtitle()
    return "Physics3D Kinematic"
end

function Physics3DKinematicDemo:extend()
    local rbDes = {}
    rbDes.mass = 0.0
    rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(60.0, 1.0, 60.0))
    local floor = cc.PhysicsSprite3D:create("Sprite3DTest/box.c3t", rbDes)
    floor:setTexture("Sprite3DTest/plane.png")
    floor:setScaleX(60)
    floor:setScaleZ(60)
    floor:setPosition3D(cc.vec3(0.0, -1.0, 0.0))
    self:addChild(floor)
    floor:setCameraMask(cc.CameraFlag.USER1)
    floor:syncNodeToPhysics()
    --static object sync is not needed
    floor:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.NONE)

    for i=1, 3 do

        rbDes.mass = 0.0 --kinematic objects. zero mass so that it can not be affected by other dynamic objects
        rbDes.shape = cc.Physics3DShape:createBox(cc.vec3(2.0, 2.0, 2.0))
        
        local sprite = cc.PhysicsSprite3D:create("Sprite3DTest/box.c3t", rbDes)
        sprite:setTexture("Images/CyanSquare.png")
        sprite:setCameraMask(cc.CameraFlag.USER1)
        local rigidBody = sprite:getPhysicsObj()
        rigidBody:setKinematic(true)
        
        self:addChild(sprite)

        sprite:setScale(2.0)
        sprite:setPosition3D(cc.vec3(-15.0, 0.0, 15.0 - 15.0 * (i - 1) ))
        local moveby = cc.MoveBy:create(2.0 + (i - 1), cc.vec3(30.0, 0.0, 0.0))
        sprite:runAction(cc.RepeatForever:create(cc.Sequence:create(moveby, moveby:reverse())))
    end

    --create Dynamic
    --create several spheres
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createSphere(0.5)
    local start_x = START_POS_X - ARRAY_SIZE_X/2
    local start_y = START_POS_Y + 5.0
    local start_z = START_POS_Z - ARRAY_SIZE_Z/2

    for k = 1,ARRAY_SIZE_Y do
        for i = 1,ARRAY_SIZE_X do
            for j = 1,ARRAY_SIZE_Z do
                local x = 1.0 * (i - 1) + start_x
                local y = 5.0 + 1.0 * (k - 1) + start_y
                local z = 1.0 * (j - 1) + start_z
                if rbDes.originalTransform == nil then
                    rbDes.originalTransform = cc.mat4.createIdentity()
                else
                    rbDes.originalTransform = cc.mat4.setIdentity(rbDes.originalTransform)
                end

                rbDes.originalTransform = cc.mat4.translate(rbDes.originalTransform, cc.vec3(x, y, z))

                local sprite = cc.PhysicsSprite3D:create("Sprite3DTest/sphere.c3b", rbDes)
                sprite:setTexture("Sprite3DTest/plane.png")
                sprite:setCameraMask(cc.CameraFlag.USER1)
                sprite:setScale(1.00 / sprite:getContentSize().width)
                self:addChild(sprite)
                sprite:setPosition3D(cc.vec3(x, y, z))
                sprite:syncNodeToPhysics()
                sprite:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE)
            end
        end
    end

    self._physicsScene:setPhysics3DDebugCamera(self._camera)
end

----------------------------------------
----Physics3DCollisionCallbackDemo
----------------------------------------
local Physics3DCollisionCallbackDemo = class("Physics3DCollisionCallbackDemo", Physics3DTestDemo)

function Physics3DCollisionCallbackDemo:subtitle()
    return "Physics3D CollisionCallback"
end

function Physics3DCollisionCallbackDemo:extend()
    local rbDes = {}

    local scale = 2.0
    local trianglesList = cc.Bundle3D:getTrianglesList("Sprite3DTest/boss.c3b")
    for i = 1, #trianglesList do
        trianglesList[i] = {x = trianglesList[i].x * scale, y = trianglesList[i].y * scale, z = trianglesList[i].z * scale}
    end

    rbDes.mass = 0.0
    rbDes.shape = cc.Physics3DShape:createMesh(trianglesList, math.floor(#trianglesList / 3))
    local rigidBody = cc.Physics3DRigidBody:create(rbDes)
    local component = cc.Physics3DComponent:create(rigidBody)
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss.c3b")
    sprite:addComponent(component)
    sprite:setRotation3D(cc.vec3(-90.0, 0.0, 0.0))
    sprite:setScale(scale)
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)

    rigidBody:setCollisionCallback(function (collisionInfo)
        if nil ~= collisionInfo.collisionPointList and #collisionInfo.collisionPointList > 0 then
            if collisionInfo.objA:getMask() ~= 0 then
                local ps = cc.PUParticleSystem3D:create("Particle3D/scripts/mp_hit_04.pu")
                ps:setPosition3D(collisionInfo.collisionPointList[1].worldPositionOnB)
                ps:setScale(0.05)
                ps:startParticleSystem()
                ps:setCameraMask(2)
                self:addChild(ps)
                ps:runAction(cc.Sequence:create(cc.DelayTime:create(1.0), cc.CallFunc:create(function()
                    ps:removeFromParent()
                end)))
                collisionInfo.objA:setMask(0)
            end
        end
    end)

    self._physicsScene:setPhysics3DDebugCamera(self._camera)
end

----------------------------------------
----Physics3DTerrainDemo
----------------------------------------
local Physics3DTerrainDemo = class("Physics3DTerrainDemo", Physics3DTestDemo)

function Physics3DTerrainDemo:subtitle()
    return "Physics3D Terrain"
end

function Physics3DTerrainDemo:extend()
    
    local detailMapR = { _detailMapSrc = "TerrainTest/dirt.jpg", _detailMapSize = 35}
    local detailMapG = { _detailMapSrc = "TerrainTest/Grass2.jpg", _detailMapSize = 10}
    local detailMapB = { _detailMapSrc = "TerrainTest/road.jpg", _detailMapSize = 35}
    local detailMapA = { _detailMapSrc = "TerrainTest/GreenSkin.jpg", _detailMapSize = 20}
    local terrainData = { _heightMapSrc = "TerrainTest/heightmap129.jpg", _alphaMapSrc = "TerrainTest/alphamap.png" , _detailMaps = {detailMapR, detailMapG, detailMapB, detailMapA}, _detailMapAmount = 4, _mapHeight = 20.0, _mapScale = 1.0, _chunkSize = cc.size(32,32)}

    local terrain = cc.Terrain:create(terrainData,cc.Terrain.CrackFixedType.SKIRT)
    terrain:setMaxDetailMapAmount(4)
    terrain:setCameraMask(2)
    terrain:setDrawWire(false)
    
    terrain:setSkirtHeightRatio(3)
    terrain:setLODDistance(64,128,192)
    terrain:setCameraMask(cc.CameraFlag.USER1)

    --create terrain
    local rbDes = {}
    rbDes.mass = 0.0
    local heidata = terrain:getHeightData()
    local size = terrain:getTerrainSize()
    rbDes.shape = cc.Physics3DShape:createHeightfield(size.width, size.height, heidata, 1.0, terrain:getMinHeight(), terrain:getMaxHeight(), true, false, true)
    local rigidBody = cc.Physics3DRigidBody:create(rbDes)
    local component = cc.Physics3DComponent:create(rigidBody)
    terrain:addComponent(component)
    self:addChild(terrain)
    component:syncNodeToPhysics()
    component:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.NONE)

    --create several spheres
    rbDes.mass = 1.0
    rbDes.shape = cc.Physics3DShape:createSphere(0.5)
    local start_x = START_POS_X - ARRAY_SIZE_X/2 + 5.0
    local start_y = START_POS_Y + 20.0
    local start_z = START_POS_Z - ARRAY_SIZE_Z/2

    for k = 1, ARRAY_SIZE_Y do
        for i = 1, ARRAY_SIZE_X do
            for j = 1, ARRAY_SIZE_Z do
                local x = 1.0 * (i - 1) + start_x
                local y = 5.0+1.0 * (k - 1) + start_y
                local z = 1.0 * (j - 1) + start_z
                
                local sprite = cc.PhysicsSprite3D:create("Sprite3DTest/sphere.c3b", rbDes)
                sprite:setTexture("Sprite3DTest/plane.png")
                sprite:setCameraMask(cc.CameraFlag.USER1)
                sprite:setScale(1.0 / sprite:getContentSize().width)
                sprite:setPosition3D(cc.vec3(x, y, z))
                self:addChild(sprite)
                sprite:syncNodeToPhysics()
                sprite:setSyncFlag(cc.Physics3DComponent.PhysicsSyncFlag.PHYSICS_TO_NODE)
            end
        end
    end

    --create mesh
    local trianglesList = cc.Bundle3D:getTrianglesList("Sprite3DTest/boss.c3b")
    
    rbDes.mass = 0.0
    rbDes.shape = cc.Physics3DShape:createMesh(trianglesList, math.floor(#trianglesList / 3))
    local rigidBody = cc.Physics3DRigidBody:create(rbDes)
    local component = cc.Physics3DComponent:create(rigidBody)
    local sprite = cc.Sprite3D:create("Sprite3DTest/boss.c3b")
    sprite:addComponent(component)
    sprite:setRotation3D(cc.vec3(-90.0, 0.0, 0.0))
    sprite:setPosition3D(cc.vec3(0.0, 15.0, 0.0))
    sprite:setCameraMask(2)
    self:addChild(sprite)

    local shapeList = {}
    local bodyshape  = cc.Physics3DShape:createBox(cc.vec3(2.0, 4.0, 2.0))
    local localTrans = cc.mat4.createTranslation(0.0, 2.0, 0.0)
    table.insert(shapeList, {bodyshape, localTrans})

    local headshape = cc.Physics3DShape:createSphere(1.5)
    localTrans = cc.mat4.createTranslation(0.6, 5.0, -1.5)
    table.insert(shapeList, {headshape, localTrans})

    local lhandshape = cc.Physics3DShape:createBox(cc.vec3(1.0, 3.0, 1.0))
    localTrans = cc.mat4.createRotation(cc.vec3(1.0, 0.0, 0.0), 15.0 * math.pi / 180)
    localTrans[13] = -1.5
    localTrans[14] = 2.5
    localTrans[15] = -2.5
    table.insert(shapeList, {lhandshape, localTrans})

    local rhandshape = cc.Physics3DShape:createBox(cc.vec3(1.0, 3.0, 1.0))
    localTrans = cc.mat4.createRotation(cc.vec3(1.0, 0.0, 0.0), -15.0 * math.pi / 180)
    localTrans[13] = 2.0
    localTrans[14] = 2.5
    localTrans[15] = 1.0
    table.insert(shapeList, {rhandshape, localTrans})

    rbDes.mass = 10.0
    rbDes.shape = cc.Physics3DShape:createCompoundShape(shapeList)
    rigidBody = cc.Physics3DRigidBody:create(rbDes)
    component = cc.Physics3DComponent:create(rigidBody)
    local sprite = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    sprite:addComponent(component)
    sprite:setRotation3D(cc.vec3(0.0, 180.0, 0.0))
    sprite:setPosition3D(cc.vec3(-5.0, 20.0, 0.0))
    sprite:setScale(0.4)
    sprite:setCameraMask(2)
    self:addChild(sprite)

    self._physicsScene:setPhysics3DDebugCamera(self._camera)
end

function Physics3DTest()

    Helper.usePhysics = true
    
    local scene = cc.Scene:createWithPhysics()

    Helper.createFunctionTable = 
    {
        BasicPhysics3DDemo.create,
        Physics3DConstraintDemo.create,
        Physics3DKinematicDemo.create,
        Physics3DCollisionCallbackDemo.create,
        Physics3DTerrainDemo.create,
    }
    Helper.index = 1

    scene:addChild(BasicPhysics3DDemo.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end