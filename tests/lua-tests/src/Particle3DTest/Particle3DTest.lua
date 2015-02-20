local PARTICLE_SYSTEM_TAG = 0x0001

local function baseInit(self)
    -- body
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self._angle = 0

    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_MAC  or targetPlatform == cc.PLATFORM_OS_IPHONE  or targetPlatform == cc.PLATFORM_OS_IPAD  then
        cc.FileUtils:getInstance():addSearchPath("Particle3D/materials")
        cc.FileUtils:getInstance():addSearchPath("Particle3D/scripts")
    else
        cc.FileUtils:getInstance():addSearchPath("res/Particle3D/materials")
        cc.FileUtils:getInstance():addSearchPath("res/Particle3D/scripts")
    end

    local size = cc.Director:getInstance():getWinSize()
    self._camera = cc.Camera:createPerspective(30.0, size.width / size.height, 1.0, 1000.0)
    self._camera:setPosition3D(cc.vec3(0.0, 0.0, 100.0))
    self._camera:lookAt(cc.vec3(0.0, 0.0, 0.0), cc.vec3(0.0, 1.0, 0.0))
    self._camera:setCameraFlag(cc.CameraFlag.USER1)
    self:addChild(self._camera)

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(function (touches, event)

    end,cc.Handler.EVENT_TOUCHES_BEGAN)

    listener:registerScriptHandler(function (touches, event)
        if #touches ~= 0 then
            local touch = touches[1]
            local delta = touch:getDelta()
        
            self._angle = self._angle - delta.x * math.pi / 180
            self._camera:setPosition3D(cc.vec3(100.0 *  math.sin(math.deg(self._angle)), 0.0, 100.0 * math.cos(math.deg(self._angle))))
            self._camera:lookAt(cc.vec3(0.0, 0.0, 0.0), cc.vec3(0.0, 1.0, 0.0)) 
        end
    end,cc.Handler.EVENT_TOUCHES_MOVED)

    listener:registerScriptHandler(function (touches, event)
        
    end,cc.Handler.EVENT_TOUCHES_ENDED)

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    local ttfConfig = {}
    ttfConfig.fontFilePath = "fonts/tahoma.ttf"
    ttfConfig.fontSize = 10
    self._particleLab = cc.Label:createWithTTF(ttfConfig,"Particle Count: 0",cc.TEXT_ALIGNMENT_LEFT)
    self._particleLab:setPosition(cc.p(0.0, size.height / 6.0))
    self._particleLab:setAnchorPoint(cc.p(0.0, 0.0))
    self:addChild(self._particleLab)

    self:scheduleUpdateWithPriorityLua(function(dt)
        local ps = self:getChildByTag(PARTICLE_SYSTEM_TAG)
        if nil ~= ps then
            local count = 0
            local children = ps:getChildren()
            for i= 1, #children do
                local child = children[i]
                if nil ~= child then
                    --UNDO
                    count = count + #(child:getParticlePool():getActiveParticleList())
                end
            end

            local str = string.format("Particle Count: %d", count)
            self._particleLab:setString(str)
        end
    end, 0)

    self:registerScriptHandler(function (event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end)
end

-- Particle3DLineStreakDemo
local Particle3DLineStreakDemo = class("Particle3DLineStreakDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DLineStreakDemo:ctor()
    -- body
    self:init()
end

function Particle3DLineStreakDemo:init()
    baseInit(self)
end

function Particle3DLineStreakDemo:title()
    return "Particle3D Test"
end

function Particle3DLineStreakDemo:subtitle()
    return "LineStreak"
end

function Particle3DLineStreakDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("lineStreak.pu", "pu_mediapack_01.material")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:setScale(5.0)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DLineStreakDemo:onExit()
    self:unscheduleUpdate()
end


-- Particle3DBlackHoleDemo
local Particle3DBlackHoleDemo = class("Particle3DBlackHoleDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DBlackHoleDemo:ctor()
    -- body
    self:init()
end

function Particle3DBlackHoleDemo:init()
    baseInit(self)
end

function Particle3DBlackHoleDemo:title()
    return "Particle3D Test"
end

function Particle3DBlackHoleDemo:subtitle()
    return "BlackHole"
end

function Particle3DBlackHoleDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("blackHole.pu", "pu_mediapack_01.material")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:setPosition(-25.0, 0.0)
    local moveby = cc.MoveBy:create(2.0, cc.p(50.0, 0.0))
    local moveby1 = cc.MoveBy:create(2.0, cc.p(-50.0, 0.0))
    rootps:runAction(cc.RepeatForever:create(cc.Sequence:create(moveby, moveby1)))
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DBlackHoleDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DHypnoDemo
local Particle3DHypnoDemo = class("Particle3DHypnoDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DHypnoDemo:ctor()
    -- body
    self:init()
end

function Particle3DHypnoDemo:init()
    baseInit(self)
end

function Particle3DHypnoDemo:title()
    return "Particle3D Test"
end

function Particle3DHypnoDemo:subtitle()
    return "Hypno"
end

function Particle3DHypnoDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("hypno.pu", "pu_mediapack_01.material")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DHypnoDemo:onExit()
    self:unscheduleUpdate()
end


-- Particle3DAdvancedLodSystemDemo
local Particle3DAdvancedLodSystemDemo = class("Particle3DAdvancedLodSystemDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DAdvancedLodSystemDemo:ctor()
    -- body
    self:init()
end

function Particle3DAdvancedLodSystemDemo:init()
    baseInit(self)
end

function Particle3DAdvancedLodSystemDemo:title()
    return "Particle3D Test"
end

function Particle3DAdvancedLodSystemDemo:subtitle()
    return "AdvancedSystem"
end

function Particle3DAdvancedLodSystemDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("advancedLodSystem.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    local scale = cc.ScaleBy:create(1.0, 2.0, 2.0, 2.0)
    local rotate = cc.RotateBy:create(1.0, cc.vec3(0.0, 0.0, 100.0))
    rootps:runAction(cc.RepeatForever:create(cc.Sequence:create(rotate)))
    rootps:runAction(cc.RepeatForever:create(cc.Sequence:create(scale, scale:reverse())))
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DAdvancedLodSystemDemo:onExit()
    self:unscheduleUpdate()
end


-- Particle3DTimeShiftDemo
local Particle3DTimeShiftDemo = class("Particle3DTimeShiftDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DTimeShiftDemo:ctor()
    -- body
    self:init()
end

function Particle3DTimeShiftDemo:init()
    baseInit(self)
end

function Particle3DTimeShiftDemo:title()
    return "Particle3D Test"
end

function Particle3DTimeShiftDemo:subtitle()
    return "TimeShift"
end

function Particle3DTimeShiftDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("timeShift.pu", "pu_mediapack_01.material")
    rootps:setScale(2.0)
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DTimeShiftDemo:onExit()
    self:unscheduleUpdate()
end


-- Particle3DUVAnimDemo
local Particle3DUVAnimDemo = class("Particle3DUVAnimDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DUVAnimDemo:ctor()
    -- body
    self:init()
end

function Particle3DUVAnimDemo:init()
    baseInit(self)
end

function Particle3DUVAnimDemo:title()
    return "Particle3D Test"
end

function Particle3DUVAnimDemo:subtitle()
    return "UVAnim"
end

function Particle3DUVAnimDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("UVAnimation.pu", "pu_mediapack_01.material")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DUVAnimDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DFirePlaceDemo
local Particle3DFirePlaceDemo = class("Particle3DFirePlaceDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DFirePlaceDemo:ctor()
    -- body
    self:init()
end

function Particle3DFirePlaceDemo:init()
    baseInit(self)
end

function Particle3DFirePlaceDemo:title()
    return "Particle3D Test"
end

function Particle3DFirePlaceDemo:subtitle()
    return "Fire"
end

function Particle3DFirePlaceDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("mp_torch.pu", "pu_mediapack_01.material")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:setScale(5.0)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DFirePlaceDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DElectricBeamSystemDemo
local Particle3DElectricBeamSystemDemo = class("Particle3DElectricBeamSystemDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DElectricBeamSystemDemo:ctor()
    -- body
    self:init()
end

function Particle3DElectricBeamSystemDemo:init()
    baseInit(self)
end

function Particle3DElectricBeamSystemDemo:title()
    return "Particle3D Test"
end

function Particle3DElectricBeamSystemDemo:subtitle()
    return "ElectricBeamSystem"
end

function Particle3DElectricBeamSystemDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("electricBeamSystem.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DElectricBeamSystemDemo:onExit()
    self:unscheduleUpdate()
end


-- Particle3DExplosionBlueDemo
local Particle3DExplosionBlueDemo = class("Particle3DExplosionBlueDemo", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DExplosionBlueDemo:ctor()
    -- body
    self:init()
end

function Particle3DExplosionBlueDemo:init()
    baseInit(self)
end

function Particle3DExplosionBlueDemo:title()
    return "Particle3D Test"
end

function Particle3DExplosionBlueDemo:subtitle()
    return "ExplosionBlue"
end

function Particle3DExplosionBlueDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("mp_explosion_04_blue.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:setScale(0.25)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DExplosionBlueDemo:onExit()
    self:unscheduleUpdate()
end

function Particle3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Particle3DLineStreakDemo.create,
        Particle3DBlackHoleDemo.create,
        Particle3DHypnoDemo.create,
        Particle3DAdvancedLodSystemDemo.create,
        Particle3DTimeShiftDemo.create,
        Particle3DUVAnimDemo.create,
        Particle3DFirePlaceDemo.create,
        Particle3DElectricBeamSystemDemo.create,
        Particle3DExplosionBlueDemo.create,
    }

    scene:addChild(Particle3DLineStreakDemo.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
