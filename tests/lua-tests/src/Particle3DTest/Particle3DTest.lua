local PARTICLE_SYSTEM_TAG = 0x0001

local function baseInit(self)
    -- body
    Helper.titleLabel:setString(self:title())
    Helper.subtitleLabel:setString(self:subtitle())

    self._angle = 0

    local targetPlatform = cc.Application:getInstance():getTargetPlatform()
    if targetPlatform == cc.PLATFORM_OS_MAC  or targetPlatform == cc.PLATFORM_OS_IPHONE  or targetPlatform == cc.PLATFORM_OS_IPAD or targetPlatform == cc.PLATFORM_OS_TIZEN then
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
                if nil ~= child and nil ~= child.getAliveParticleCount then
                    count = count + child:getAliveParticleCount()
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
    local rootps = cc.PUParticleSystem3D:create("lineStreak.pu", "pu_example.material")
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
    local rootps = cc.PUParticleSystem3D:create("blackHole.pu", "pu_example.material")
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
    local rootps = cc.PUParticleSystem3D:create("hypno.pu", "pu_example.material")
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
    local rootps = cc.PUParticleSystem3D:create("timeShift.pu", "pu_example.material")
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
    local rootps = cc.PUParticleSystem3D:create("UVAnimation.pu", "pu_example.material")
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
    local rootps = cc.PUParticleSystem3D:create("mp_torch.pu", "pu_example.material")
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

-- Particle3DFlareShield
local Particle3DFlareShieldDemo = class("Particle3DFlareShield", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DFlareShieldDemo:ctor()
    -- body
    self:init()
end

function Particle3DFlareShieldDemo:init()
    baseInit(self)
end

function Particle3DFlareShieldDemo:title()
    return "Particle3D Test"
end

function Particle3DFlareShieldDemo:subtitle()
    return "FlareShield"
end

function Particle3DFlareShieldDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("flareShield.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DFlareShieldDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DLightningBoltDemo
local Particle3DLightningBoltDemo = class("Particle3DLightningBolt", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DLightningBoltDemo:ctor()
    -- body
    self:init()
end

function Particle3DLightningBoltDemo:init()
    baseInit(self)
end

function Particle3DLightningBoltDemo:title()
    return "Particle3D Test"
end

function Particle3DLightningBoltDemo:subtitle()
    return "LightningBolt"
end

function Particle3DLightningBoltDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("lightningBolt.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DLightningBoltDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DCanOfWormsDemo
local Particle3DCanOfWormsDemo = class("Particle3DCanOfWorms", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DCanOfWormsDemo:ctor()
    -- body
    self:init()
end

function Particle3DCanOfWormsDemo:init()
    baseInit(self)
end

function Particle3DCanOfWormsDemo:title()
    return "Particle3D Test"
end

function Particle3DCanOfWormsDemo:subtitle()
    return "CanOfWorms"
end

function Particle3DCanOfWormsDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("canOfWorms.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DCanOfWormsDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DRibbonTrailDemo
local Particle3DRibbonTrailDemo = class("Particle3DRibbonTrail", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DRibbonTrailDemo:ctor()
    -- body
    self:init()
end

function Particle3DRibbonTrailDemo:init()
    baseInit(self)
end

function Particle3DRibbonTrailDemo:title()
    return "Particle3D Test"
end

function Particle3DRibbonTrailDemo:subtitle()
    return "RibbonTrail"
end

function Particle3DRibbonTrailDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("ribbonTrailTest.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DRibbonTrailDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DWeaponTrailDemo
local Particle3DWeaponTrailDemo = class("Particle3DWeaponTrail", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DWeaponTrailDemo:ctor()
    -- body
    self:init()
end

function Particle3DWeaponTrailDemo:init()
    baseInit(self)
end

function Particle3DWeaponTrailDemo:title()
    return "Particle3D Test"
end

function Particle3DWeaponTrailDemo:subtitle()
    return "WeaponTrail"
end

function Particle3DWeaponTrailDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("weaponTrail.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DWeaponTrailDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DExplosionSystemDemo
local Particle3DExplosionSystemDemo = class("Particle3DExplosionSystem", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DExplosionSystemDemo:ctor()
    -- body
    self:init()
end

function Particle3DExplosionSystemDemo:init()
    baseInit(self)
end

function Particle3DExplosionSystemDemo:title()
    return "Particle3D Test"
end

function Particle3DExplosionSystemDemo:subtitle()
    return "ExplosionSystem"
end

function Particle3DExplosionSystemDemo:onEnter()
    local rootps = cc.PUParticleSystem3D:create("explosionSystem.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DExplosionSystemDemo:onExit()
    self:unscheduleUpdate()
end

-- Particle3DWithSprite3DDemo
local Particle3DWithSprite3DDemo = class("Particle3DWithSprite3D", function ()
    local layer = cc.Layer:create()
    Helper.initWithLayer(layer)
    return layer
end)

function Particle3DWithSprite3DDemo:ctor()
    -- body
    self:init()
end

function Particle3DWithSprite3DDemo:init()
    baseInit(self)
end

function Particle3DWithSprite3DDemo:title()
    return "Particle3D Test"
end

function Particle3DWithSprite3DDemo:subtitle()
    return "Particle3D With Sprite3D"
end

function Particle3DWithSprite3DDemo:onEnter()

    local sprite = cc.Sprite3D:create("Sprite3DTest/orc.c3b")
    sprite:setPosition3D(cc.vec3(-20, 0, 0))
    sprite:setRotation3D(cc.vec3(0, 180, 0))
    sprite:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(sprite)
    local animation = cc.Animation3D:create("Sprite3DTest/orc.c3b")
    local animate = cc.Animate3D:create(animation)
    sprite:runAction(cc.RepeatForever:create(animate))
    
    local billboard = cc.BillBoard:create("Images/Icon.png")
    billboard:setPosition3D(cc.vec3(20, 0, 0))
    billboard:setScale(0.2)
    billboard:setCameraMask(cc.CameraFlag.USER1)
    self:addChild(billboard)

    local rootps = cc.PUParticleSystem3D:create("lineStreak.pu")
    rootps:setCameraMask(cc.CameraFlag.USER1)
    rootps:startParticleSystem()
    self:addChild(rootps, 0, PARTICLE_SYSTEM_TAG)
end

function Particle3DWithSprite3DDemo:onExit()
    self:unscheduleUpdate()
end

function Particle3DTest()
    local scene = cc.Scene:create()

    Helper.createFunctionTable = 
    {
        Particle3DExplosionSystemDemo.create,
        Particle3DLineStreakDemo.create,
        Particle3DBlackHoleDemo.create,
        Particle3DHypnoDemo.create,
        Particle3DAdvancedLodSystemDemo.create,
        Particle3DTimeShiftDemo.create,
        Particle3DUVAnimDemo.create,
        Particle3DFirePlaceDemo.create,
        Particle3DElectricBeamSystemDemo.create,
        Particle3DFlareShieldDemo.create,
        Particle3DLightningBoltDemo.create,
        Particle3DCanOfWormsDemo.create,
        Particle3DRibbonTrailDemo.create,
        Particle3DWeaponTrailDemo.create,
        Particle3DWithSprite3DDemo.create,
    }

    scene:addChild(Particle3DExplosionSystemDemo.create())
    scene:addChild(CreateBackMenuItem())

    return scene
end
