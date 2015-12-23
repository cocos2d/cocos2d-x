
local SceneIdx  = -1
local MAX_LAYER = 42

local emitter = nil
local background = nil

local labelAtlas = nil
local titleLabel = nil
local subtitleLabel = nil
local baseLayer_entry = nil

local s = cc.Director:getInstance():getWinSize()

local function backAction()
	SceneIdx = SceneIdx - 1
    if SceneIdx < 0 then
        SceneIdx = SceneIdx + MAX_LAYER
    end

    return CreateParticleLayer()
end

local function restartAction()
	return CreateParticleLayer()
end

local function nextAction()
	SceneIdx = SceneIdx + 1
    SceneIdx = math.mod(SceneIdx, MAX_LAYER)

    return CreateParticleLayer()
end

local function backCallback(sender)
	local scene = cc.Scene:create()

	scene:addChild(backAction())
	scene:addChild(CreateBackMenuItem())

	cc.Director:getInstance():replaceScene(scene)
end

local function restartCallback(sender)
	local scene = cc.Scene:create()

	scene:addChild(restartAction())
	scene:addChild(CreateBackMenuItem())

	cc.Director:getInstance():replaceScene(scene)
end

local function nextCallback(sender)
	local scene = cc.Scene:create()

	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	cc.Director:getInstance():replaceScene(scene)
end

local function toggleCallback(sender)
	if emitter ~= nil then
        if emitter:getPositionType() == cc.POSITION_TYPE_GROUPED then
            emitter:setPositionType(cc.POSITION_TYPE_FREE)
        elseif emitter:getPositionType() == cc.POSITION_TYPE_FREE then
            emitter:setPositionType(cc.POSITION_TYPE_RELATIVE)
        elseif emitter:getPositionType() == cc.POSITION_TYPE_RELATIVE then
            emitter:setPositionType(cc.POSITION_TYPE_GROUPED)
		end
    end
end

local function setEmitterPosition()
    if emitter ~= nil then
		emitter:setPosition(s.width / 2, s.height / 2)
	end
end

local function update(dt)
	if emitter ~= nil then
		local str = "" .. emitter:getParticleCount()
--  	labelAtlas:setString("" .. str)
    end
end

local function baseLayer_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		baseLayer_entry = scheduler:scheduleScriptFunc(update, 0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(baseLayer_entry)
	end
end

local function getBaseLayer()
	local layer = cc.LayerColor:create(cc.c4b(127,127,127,255))

    emitter = nil

    titleLabel = cc.Label:createWithTTF("", s_arialPath, 28)
    layer:addChild(titleLabel, 100, 1000)
    titleLabel:setAnchorPoint(cc.p(0.5, 0.5))
    titleLabel:setPosition(s.width / 2, s.height - 50)

    subtitleLabel = cc.Label:createWithTTF("", s_arialPath, 16)
    layer:addChild(subtitleLabel, 100)
    subtitleLabel:setAnchorPoint(cc.p(0.5, 0.5))
    subtitleLabel:setPosition(s.width / 2, s.height - 80)


    local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
	local item4 = cc.MenuItemToggle:create(cc.MenuItemFont:create("Free Movement"))
	item4:addSubItem(cc.MenuItemFont:create("Relative Movement"))
	item4:addSubItem(cc.MenuItemFont:create("Grouped Movement"))
	item1:registerScriptTapHandler(backCallback)
	item2:registerScriptTapHandler(restartCallback)
	item3:registerScriptTapHandler(nextCallback)
	item4:registerScriptTapHandler(toggleCallback)

    local menu = cc.Menu:create()
	menu:addChild(item1)
	menu:addChild(item2)
	menu:addChild(item3)
	menu:addChild(item4)

    menu:setPosition(cc.p(0, 0))
    item1:setPosition(cc.p(s.width/2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(cc.p(s.width/2, item2:getContentSize().height / 2))
    item3:setPosition(cc.p(s.width/2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
	item4:setPosition(cc.p(0, 100))
    item4:setAnchorPoint(cc.p(0, 0))

    layer:addChild(menu, 100)

    labelAtlas = cc.LabelAtlas:_create("0000", "fps_images.png", 12, 32, string.byte('.'))
    layer:addChild(labelAtlas, 100)
    labelAtlas:setPosition(cc.p(s.width - 66, 50))

    -- moving background
    background = cc.Sprite:create(s_back3)
    layer:addChild(background, 5)
    background:setPosition(cc.p(s.width / 2, s.height - 180))

    local move = cc.MoveBy:create(4, cc.p(300, 0))
    local move_back = move:reverse()
    local seq = cc.Sequence:create(move, move_back)
    background:runAction(cc.RepeatForever:create(seq))

    local function onTouchesEnded(touches, event)
        local location = touches[1]:getLocation()
        local pos = cc.p(0, 0)
        if background ~= nil then
            pos = background:convertToWorldSpace(cc.p(0, 0))
        end

        if emitter ~= nil then
            local newPos = cc.pSub(location, pos)
            emitter:setPosition(newPos.x, newPos.y)
        end
    end

    local function onTouchesBegan(touches, event)
         onTouchesEnded(touches, event);
    end

    local function onTouchesMoved(touches, event)
         onTouchesEnded(touches, event);
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesBegan,cc.Handler.EVENT_TOUCHES_BEGAN )
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
    listener:registerScriptHandler(onTouchesEnded,cc.Handler.EVENT_TOUCHES_ENDED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

	layer:registerScriptHandler(baseLayer_onEnterOrExit)

	return layer
end

---------------------------------
--  ParticleReorder
---------------------------------
local ParticleReorder_Order = nil
local ParticleReorder_entry = nil
local ParticleReorder_layer = nil

local function reorderParticles(dt)
	update(dt)

	for i = 0, 1 do
        local parent = ParticleReorder_layer:getChildByTag(1000 + i)
        local child1 = parent:getChildByTag(1)
        local child2 = parent:getChildByTag(2)
        local child3 = parent:getChildByTag(3)

        if math.mod(ParticleReorder_Order, 3) == 0 then
            parent:reorderChild(child1, 1)
            parent:reorderChild(child2, 2)
            parent:reorderChild(child3, 3)

        elseif math.mod(ParticleReorder_Order, 3) == 1 then
            parent:reorderChild(child1, 3)
            parent:reorderChild(child2, 1)
            parent:reorderChild(child3, 2)

        elseif math.mod(ParticleReorder_Order, 3) == 2 then
            parent:reorderChild(child1, 2)
            parent:reorderChild(child2, 3)
            parent:reorderChild(child3, 1)
		end
    end

    ParticleReorder_Order = ParticleReorder_Order + 1
end

local function ParticleReorder_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		ParticleReorder_entry = scheduler:scheduleScriptFunc(reorderParticles, 1.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(ParticleReorder_entry)
	end
end

local function ParticleReorder()
	ParticleReorder_layer = getBaseLayer()

	ParticleReorder_Order = 0
    ParticleReorder_layer:setColor(cc.c3b(0, 0, 0))
    ParticleReorder_layer:removeChild(background, true)
    background = nil

    local ignore = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
    local parent1 = cc.Node:create()
    local parent2 = cc.ParticleBatchNode:createWithTexture(ignore:getTexture())
    ignore:unscheduleUpdate()

    for i = 0, 1 do
		local parent = nil
        if i == 0 then
			parent = parent1
		else
			parent = parent2
		end

        local emitter1 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
        emitter1:setStartColor(cc.c4f(1,0,0,1))
        emitter1:setBlendAdditive(false)
        local emitter2 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
        emitter2:setStartColor(cc.c4f(0,1,0,1))
        emitter2:setBlendAdditive(false)
        local emitter3 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
        emitter3:setStartColor(cc.c4f(0,0,1,1))
        emitter3:setBlendAdditive(false)

		local neg = nil
		if i == 0 then
			neg = 1
		else
			neg = -1
		end

        emitter1:setPosition(cc.p( s.width / 2 - 30, s.height / 2 + 60 * neg))
        emitter2:setPosition(cc.p( s.width / 2, s.height / 2 + 60 * neg))
        emitter3:setPosition(cc.p( s.width / 2 + 30, s.height / 2 + 60 * neg))

        parent:addChild(emitter1, 0, 1)
        parent:addChild(emitter2, 0, 2)
        parent:addChild(emitter3, 0, 3)

        ParticleReorder_layer:addChild(parent, 10, 1000 + i)
    end

	ParticleReorder_layer:registerScriptHandler(ParticleReorder_onEnterOrExit)

	titleLabel:setString("Reordering particles")
	subtitleLabel:setString("Reordering particles with and without batches batches")
	return ParticleReorder_layer
end

---------------------------------
--  ParticleBatchHybrid
---------------------------------
local ParticleBatchHybrid_entry = nil
local ParticleBatchHybrid_parent1 = nil
local ParticleBatchHybrid_parent2 = nil

local function switchRender(dt)
	update(dt)

    if nil ~= emitter then
    	local cond = (emitter:getBatchNode() ~= nil)
    	emitter:removeFromParent(false)
    	local str = "Particle: Using new parent: "
    	local newParent = nil
    	if cond == true then
    		newParent = ParticleBatchHybrid_parent2
    		str = str .. "Node"
    	else
    		newParent = ParticleBatchHybrid_parent1
    		str = str .. "ParticleBatchNode"
    	end
    	newParent:addChild(emitter)
	    cclog(str)
	end
end

local function ParticleBatchHybrid_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		ParticleBatchHybrid_entry = scheduler:scheduleScriptFunc(switchRender, 2.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(ParticleBatchHybrid_entry)
		if nil ~= emitter then
		    emitter:release()
		    emitter = nil
		end
	end
end

local function ParticleBatchHybrid()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    emitter = cc.ParticleSystemQuad:create("Particles/LavaFlow.plist")
	emitter:retain()
    local batch = cc.ParticleBatchNode:createWithTexture(emitter:getTexture())
    batch:addChild(emitter)
    layer:addChild(batch, 10)

	local node = cc.Node:create()
	layer:addChild(node)
	ParticleBatchHybrid_parent1 = batch
	ParticleBatchHybrid_parent2 = node

	layer:registerScriptHandler(ParticleBatchHybrid_onEnterOrExit)

	titleLabel:setString("Particle Batch")
	subtitleLabel:setString("Hybrid: batched and non batched every 2 seconds")
	return layer
end

---------------------------------
--  ParticleBatchMultipleEmitters
---------------------------------
local function ParticleBatchMultipleEmitters()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    local emitter1 = cc.ParticleSystemQuad:create("Particles/LavaFlow.plist")
    emitter1:setStartColor(cc.c4f(1,0,0,1))
    local emitter2 = cc.ParticleSystemQuad:create("Particles/LavaFlow.plist")
    emitter2:setStartColor(cc.c4f(0,1,0,1))
    local emitter3 = cc.ParticleSystemQuad:create("Particles/LavaFlow.plist")
    emitter3:setStartColor(cc.c4f(0,0,1,1))

    emitter1:setPosition(cc.p(s.width / 1.25, s.height / 1.25))
    emitter2:setPosition(cc.p(s.width / 2, s.height / 2))
    emitter3:setPosition(cc.p(s.width / 4, s.height / 4))

    local batch = cc.ParticleBatchNode:createWithTexture(emitter1:getTexture())

    batch:addChild(emitter1, 0)
    batch:addChild(emitter2, 0)
    batch:addChild(emitter3, 0)

    layer:addChild(batch, 10)

	titleLabel:setString("Particle Batch")
	subtitleLabel:setString("Multiple emitters. One Batch")
	return layer
end

---------------------------------
--  DemoFlower
---------------------------------
local function DemoFlower()
	local layer = getBaseLayer()

	emitter = cc.ParticleFlower:create()
	-- emitter:retain()
    background:addChild(emitter, 10)
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_stars1))

    setEmitterPosition()

	titleLabel:setString("ParticleFlower")
	return layer
end

---------------------------------
--  DemoGalaxy
---------------------------------
local function DemoGalaxy()
	local layer = getBaseLayer()

	emitter = cc.ParticleGalaxy:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    setEmitterPosition()

	titleLabel:setString("ParticleGalaxy")
	return layer
end

---------------------------------
--  DemoFirework
---------------------------------
local function DemoFirework()
	local layer = getBaseLayer()

	emitter = cc.ParticleFireworks:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_stars1))

    setEmitterPosition()

	titleLabel:setString("ParticleFireworks")
	return layer
end

---------------------------------
--  DemoSpiral
---------------------------------
local function DemoSpiral()
	local layer = getBaseLayer()

	emitter = cc.ParticleSpiral:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    setEmitterPosition()

	titleLabel:setString("ParticleSpiral")
	return layer
end

---------------------------------
--  DemoSun
---------------------------------
local function DemoSun()
	local layer = getBaseLayer()

	emitter = cc.ParticleSun:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    setEmitterPosition()

	titleLabel:setString("ParticleSun")
	return layer
end

---------------------------------
--  DemoMeteor
---------------------------------
local function DemoMeteor()
	local layer = getBaseLayer()

	emitter = cc.ParticleMeteor:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    setEmitterPosition()

	titleLabel:setString("ParticleMeteor")
	return layer
end

---------------------------------
--  DemoFire
---------------------------------
local function DemoFire()
	local layer = getBaseLayer()

	emitter = cc.ParticleFire:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))
    local pos_x, pos_y = emitter:getPosition()
    emitter:setPosition(pos_x, 100)

	titleLabel:setString("ParticleFire")
	return layer
end

---------------------------------
--  DemoSmoke
---------------------------------
local function DemoSmoke()
	local layer = getBaseLayer()

	emitter = cc.ParticleSmoke:create()
    -- emitter:retain()
    background:addChild(emitter, 10)
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))
    local pos_x, pos_y = emitter:getPosition()
    emitter:setPosition(pos_x, 100)

    setEmitterPosition()

	titleLabel:setString("ParticleSmoke")
	return layer
end

---------------------------------
--  DemoExplosion
---------------------------------
local function DemoExplosion()
	local layer = getBaseLayer()

	emitter = cc.ParticleExplosion:create()
    -- emitter:retain()
    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_stars1))

    emitter:setAutoRemoveOnFinish(true)

    setEmitterPosition()

	titleLabel:setString("ParticleExplosion")
	return layer
end

---------------------------------
--  DemoSnow
---------------------------------
local function DemoSnow()
	local layer = getBaseLayer()

	emitter = cc.ParticleSnow:create()
    -- emitter:retain()
    background:addChild(emitter, 10)
    local pos_x, pos_y = emitter:getPosition()
    emitter:setPosition(pos_x, pos_y - 110)
    emitter:setLife(3)
    emitter:setLifeVar(1)

    -- gravity
    emitter:setGravity(cc.p(0, -10))

    -- speed of particles
    emitter:setSpeed(130)
    emitter:setSpeedVar(30)

    local startColor = emitter:getStartColor()
    startColor.r = 0.9
    startColor.g = 0.9
    startColor.b = 0.9
    emitter:setStartColor(startColor)

    local startColorVar = emitter:getStartColorVar()
    startColorVar.b = 0.1
    emitter:setStartColorVar(startColorVar)

    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_snow))

    setEmitterPosition()

	titleLabel:setString("ParticleSnow")
	return layer
end

---------------------------------
--  DemoRain
---------------------------------
local function DemoRain()
	local layer = getBaseLayer()

	emitter = cc.ParticleRain:create()
    -- emitter:retain()
    background:addChild(emitter, 10)
    local pos_x, pos_y = emitter:getPosition()
    emitter:setPosition(pos_x, pos_y - 100)
    emitter:setLife(4)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    setEmitterPosition()

	titleLabel:setString("ParticleRain")
	return layer
end

---------------------------------
--  DemoBigFlower
---------------------------------
local function DemoBigFlower()
	local layer = getBaseLayer()

	emitter = cc.ParticleSystemQuad:createWithTotalParticles(50)

    background:addChild(emitter, 10)
    ----emitter:release()    -- win32 :  use this line or remove this line and use autorelease()
    emitter:setTexture( cc.Director:getInstance():getTextureCache():addImage(s_stars1) )
    emitter:setDuration(-1)

    -- gravity
    emitter:setGravity(cc.p(0, 0))

    -- angle
    emitter:setAngle(90)
    emitter:setAngleVar(360)

    -- speed of particles
    emitter:setSpeed(160)
    emitter:setSpeedVar(20)

    -- radial
    emitter:setRadialAccel(-120)
    emitter:setRadialAccelVar(0)

    -- tagential
    emitter:setTangentialAccel(30)
    emitter:setTangentialAccelVar(0)

    -- emitter position
    emitter:setPosition(160, 240)
    emitter:setPosVar(cc.p(0, 0))

    -- life of particles
    emitter:setLife(4)
    emitter:setLifeVar(1)

    -- spin of particles
    emitter:setStartSpin(0)
    emitter:setStartSizeVar(0)
    emitter:setEndSpin(0)
    emitter:setEndSpinVar(0)

    -- color of particles
    emitter:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setStartColorVar(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
    emitter:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

    -- size, in pixels
    emitter:setStartSize(80.0)
    emitter:setStartSizeVar(40.0)
    emitter:setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE )

    -- emits per second
    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    -- additive
    emitter:setBlendAdditive(true)

    setEmitterPosition()

	titleLabel:setString("ParticleBigFlower")
	return layer
end

---------------------------------
--  DemoRotFlower
---------------------------------
local function DemoRotFlower()
	local layer = getBaseLayer()

	emitter = cc.ParticleSystemQuad:createWithTotalParticles(300)

    background:addChild(emitter, 10)
    ----emitter:release()    -- win32 : Remove this line
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_stars2))

    -- duration
    emitter:setDuration(-1)

    -- gravity
    emitter:setGravity(cc.p(0, 0))

    -- angle
    emitter:setAngle(90)
    emitter:setAngleVar(360)

    -- speed of particles
    emitter:setSpeed(160)
    emitter:setSpeedVar(20)

    -- radial
    emitter:setRadialAccel(-120)
    emitter:setRadialAccelVar(0)

    -- tagential
    emitter:setTangentialAccel(30)
    emitter:setTangentialAccelVar(0)

    -- emitter position
    emitter:setPosition(160, 240)
    emitter:setPosVar(cc.p(0, 0))

    -- life of particles
    emitter:setLife(3)
    emitter:setLifeVar(1)

    -- spin of particles
    emitter:setStartSpin(0)
    emitter:setStartSpinVar(0)
    emitter:setEndSpin(0)
    emitter:setEndSpinVar(2000)

    -- color of particles
	emitter:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setStartColorVar(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
    emitter:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

    -- size, in pixels
    emitter:setStartSize(30.0)
    emitter:setStartSizeVar(0)
    emitter:setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE )

    -- emits per second
    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    -- additive
    emitter:setBlendAdditive(false)

    setEmitterPosition()

	titleLabel:setString("ParticleRotFlower")
	return layer
end

---------------------------------
--  DemoModernArt
---------------------------------
local function DemoModernArt()
	local layer = getBaseLayer()

	emitter = cc.ParticleSystemQuad:createWithTotalParticles(1000)

    background:addChild(emitter, 10)
    ----emitter:release()

    -- duration
    emitter:setDuration(-1)

    -- gravity
    emitter:setGravity(cc.p(0,0))

    -- angle
    emitter:setAngle(0)
    emitter:setAngleVar(360)

    -- radial
    emitter:setRadialAccel(70)
    emitter:setRadialAccelVar(10)

    -- tagential
    emitter:setTangentialAccel(80)
    emitter:setTangentialAccelVar(0)

    -- speed of particles
    emitter:setSpeed(50)
    emitter:setSpeedVar(10)

    -- emitter position
    emitter:setPosition(s.width / 2, s.height / 2)
    emitter:setPosVar(cc.p(0, 0))

    -- life of particles
    emitter:setLife(2.0)
    emitter:setLifeVar(0.3)

    -- emits per frame
    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    -- color of particles
	emitter:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setStartColorVar(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
    emitter:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

    -- size, in pixels
    emitter:setStartSize(1.0)
    emitter:setStartSizeVar(1.0)
    emitter:setEndSize(32.0)
    emitter:setEndSizeVar(8.0)

    -- texture
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    -- additive
    emitter:setBlendAdditive(false)

    setEmitterPosition()

	titleLabel:setString("Varying size")
	return layer
end

---------------------------------
--  DemoRing
---------------------------------
local function DemoRing()
	local layer = getBaseLayer()

	emitter = cc.ParticleFlower:create()
    -- emitter:retain()

    background:addChild(emitter, 10)

    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_stars1))
    emitter:setLifeVar(0)
    emitter:setLife(10)
    emitter:setSpeed(100)
    emitter:setSpeedVar(0)
    emitter:setEmissionRate(10000)

    setEmitterPosition()

	titleLabel:setString("Ring Demo")
	return layer
end

---------------------------------
--  ParallaxParticle
---------------------------------
local function ParallaxParticle()
	local layer = getBaseLayer()

	background:getParent():removeChild(background, true)
    background = nil

    local p = cc.ParallaxNode:create()
    layer:addChild(p, 5)

    local p1 = cc.Sprite:create(s_back3)
    local p2 = cc.Sprite:create(s_back3)

    p:addChild(p1, 1, cc.p(0.5, 1), cc.p(0, 250))
    p:addChild(p2, 2, cc.p(1.5, 1), cc.p(0, 50))

    emitter = cc.ParticleFlower:create()
    -- emitter:retain()
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    p1:addChild(emitter, 10)
    emitter:setPosition(250, 200)

    local par = cc.ParticleSun:create()
    p2:addChild(par, 10)
    par:setTexture(cc.Director:getInstance():getTextureCache():addImage(s_fire))

    local move = cc.MoveBy:create(4, cc.p(300,0))
    local move_back = move:reverse()
    local seq = cc.Sequence:create(move, move_back)
    p:runAction(cc.RepeatForever:create(seq))

	titleLabel:setString("Parallax + Particles")
	return layer
end

---------------------------------
--  DemoParticleFromFile
---------------------------------
local function DemoParticleFromFile(name)
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    local filename = "Particles/" .. name .. ".plist"
    emitter = cc.ParticleSystemQuad:create(filename)
    layer:addChild(emitter, 10)

    setEmitterPosition()

	titleLabel:setString(name)
	return layer
end

---------------------------------
--  RadiusMode1
---------------------------------
local function RadiusMode1()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    emitter = cc.ParticleSystemQuad:createWithTotalParticles(200)
    layer:addChild(emitter, 10)
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage("Images/stars-grayscale.png"))

    -- duration
    emitter:setDuration(cc.PARTICLE_DURATION_INFINITY)

    -- radius mode
    emitter:setEmitterMode(cc.PARTICLE_MODE_RADIUS)

    -- radius mode: start and end radius in pixels
    emitter:setStartRadius(0)
    emitter:setStartRadiusVar(0)
    emitter:setEndRadius(160)
    emitter:setEndRadiusVar(0)

    -- radius mode: degrees per second
    emitter:setRotatePerSecond(180)
    emitter:setRotatePerSecondVar(0)


    -- angle
    emitter:setAngle(90)
    emitter:setAngleVar(0)

    -- emitter position
    emitter:setPosition(s.width / 2, s.height / 2)
    emitter:setPosVar(cc.p(0, 0))

    -- life of particles
    emitter:setLife(5)
    emitter:setLifeVar(0)

    -- spin of particles
    emitter:setStartSpin(0)
    emitter:setStartSpinVar(0)
    emitter:setEndSpin(0)
    emitter:setEndSpinVar(0)

    -- color of particles
    emitter:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setStartColorVar(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
    emitter:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

    -- size, in pixels
    emitter:setStartSize(32)
    emitter:setStartSizeVar(0)
    emitter:setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE )

    -- emits per second
    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    -- additive
    emitter:setBlendAdditive(false)

	titleLabel:setString("Radius Mode: Spiral")
	return layer
end

---------------------------------
--  RadiusMode2
---------------------------------
local function RadiusMode2()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    emitter = cc.ParticleSystemQuad:createWithTotalParticles(200)
    layer:addChild(emitter, 10)
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage("Images/stars-grayscale.png"))

    -- duration
    emitter:setDuration(cc.PARTICLE_DURATION_INFINITY )

    -- radius mode
    emitter:setEmitterMode(cc.PARTICLE_MODE_RADIUS)

    -- radius mode: start and end radius in pixels
    emitter:setStartRadius(100)
    emitter:setStartRadiusVar(0)
    emitter:setEndRadius(cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS)
    emitter:setEndRadiusVar(0)

    -- radius mode: degrees per second
    emitter:setRotatePerSecond(45)
    emitter:setRotatePerSecondVar(0)

    -- angle
    emitter:setAngle(90)
    emitter:setAngleVar(0)

    -- emitter position
    emitter:setPosition(s.width / 2, s.height / 2)
    emitter:setPosVar(cc.p(0, 0))

    -- life of particles
    emitter:setLife(4)
    emitter:setLifeVar(0)

    -- spin of particles
    emitter:setStartSpin(0)
    emitter:setStartSpinVar(0)
    emitter:setEndSpin(0)
    emitter:setEndSpinVar(0)

    -- color of particles
    emitter:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setStartColorVar(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
    emitter:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

    -- size, in pixels
    emitter:setStartSize(32)
    emitter:setStartSizeVar(0)
    emitter:setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE)

    -- emits per second
    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    -- additive
    emitter:setBlendAdditive(false)

	titleLabel:setString("Radius Mode: Semi Circle")
	return layer
end

---------------------------------
--  Issue704
---------------------------------
local function Issue704()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    emitter = cc.ParticleSystemQuad:createWithTotalParticles(100)
    layer:addChild(emitter, 10)
    emitter:setTexture(cc.Director:getInstance():getTextureCache():addImage("Images/fire.png"))

    -- duration
    emitter:setDuration(cc.PARTICLE_DURATION_INFINITY)

    -- radius mode
    emitter:setEmitterMode(cc.PARTICLE_MODE_RADIUS)

    -- radius mode: start and end radius in pixels
    emitter:setStartRadius(50)
    emitter:setStartRadiusVar(0)
    emitter:setEndRadius(cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS )
    emitter:setEndRadiusVar(0)

    -- radius mode: degrees per second
    emitter:setRotatePerSecond(0)
    emitter:setRotatePerSecondVar(0)


    -- angle
    emitter:setAngle(90)
    emitter:setAngleVar(0)

    -- emitter position
    emitter:setPosition(s.width / 2, s.height / 2)
    emitter:setPosVar(cc.p(0, 0))

    -- life of particles
    emitter:setLife(5)
    emitter:setLifeVar(0)

    -- spin of particles
    emitter:setStartSpin(0)
    emitter:setStartSpinVar(0)
    emitter:setEndSpin(0)
    emitter:setEndSpinVar(0)

    -- color of particles
    emitter:setStartColor(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setStartColorVar(cc.c4f(0.5, 0.5, 0.5, 1.0))
    emitter:setEndColor(cc.c4f(0.1, 0.1, 0.1, 0.2))
    emitter:setEndColorVar(cc.c4f(0.1, 0.1, 0.1, 0.2))

    -- size, in pixels
    emitter:setStartSize(16)
    emitter:setStartSizeVar(0)
    emitter:setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE)

    -- emits per second
    emitter:setEmissionRate(emitter:getTotalParticles() / emitter:getLife())

    -- additive
    emitter:setBlendAdditive(false)

    local rot = cc.RotateBy:create(16, 360)
    emitter:runAction(cc.RepeatForever:create(rot))

	titleLabel:setString("Issue 704. Free + Rot")
	subtitleLabel:setString("Emitted particles should not rotate")
	return layer
end

---------------------------------
--  Issue870
---------------------------------
local Issue870_index = nil
local Issue870_entry = nil

local function updateQuads(dt)
	update(dt)

	Issue870_index = math.mod(Issue870_index + 1, 4)
    local rect = cc.rect(Issue870_index * 32, 0, 32, 32)
    emitter:setTextureWithRect(emitter:getTexture(), rect)
end

local function Issue870_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		Issue870_entry = scheduler:scheduleScriptFunc(updateQuads, 2.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Issue870_entry)
	end
end

local function Issue870()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    local system = cc.ParticleSystemQuad:create("Particles/SpinningPeas.plist")
    system:setTextureWithRect(cc.Director:getInstance():getTextureCache():addImage("Images/particles.png"), cc.rect(0,0,32,32))
    layer:addChild(system, 10)
    emitter = system

    Issue870_index = 0
	layer:registerScriptHandler(Issue870_onEnterOrExit)

	titleLabel:setString("Issue 870. SubRect")
	subtitleLabel:setString("Every 2 seconds the particle should change")
	return layer
end

---------------------------------
--  MultipleParticleSystems
---------------------------------
local function MultipleParticleSystems()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    cc.Director:getInstance():getTextureCache():addImage("Images/particles.png")

    for i = 0, 4 do
        local particleSystem = cc.ParticleSystemQuad:create("Particles/SpinningPeas.plist")
        particleSystem:setPosition(i * 50, i * 50)
        particleSystem:setPositionType(cc.POSITION_TYPE_GROUPED )
        layer:addChild(particleSystem)
    end

    emitter = nil

	titleLabel:setString("Multiple particle systems")
	subtitleLabel:setString("v1.1 test: FPS should be lower than next test")
	return layer
end

---------------------------------
--  MultipleParticleSystemsBatched
---------------------------------
local function MultipleParticleSystemsBatched()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    local batchNode = cc.ParticleBatchNode:createWithTexture(nil, 3000)
    layer:addChild(batchNode, 1, 2)

    for i = 0, 4 do
        local particleSystem = cc.ParticleSystemQuad:create("Particles/SpinningPeas.plist")
        particleSystem:setPositionType(cc.POSITION_TYPE_GROUPED )
        particleSystem:setPosition(i * 50, i * 50)
        batchNode:setTexture(particleSystem:getTexture())
        batchNode:addChild(particleSystem)
    end

    emitter = nil

	titleLabel:setString("Multiple particle systems batched")
	subtitleLabel:setString("v1.1 test: should perform better than previous test")
	return layer
end

---------------------------------
--  AddAndDeleteParticleSystems
---------------------------------
local AddAndDeleteParticleSystems_entry = nil
local AddAndDeleteParticleSystems_batchNode = nil

local function removeSystem(dt)
	update(dt)

	local ChildrenCount = table.getn(AddAndDeleteParticleSystems_batchNode:getChildren())
    if ChildrenCount > 0 then
        cclog("remove random system")
        local rand = math.mod(math.random(1, 999999), ChildrenCount - 1)
        AddAndDeleteParticleSystems_batchNode:removeChild(AddAndDeleteParticleSystems_batchNode:getChildren()[(rand)], true)

		--add new
        local particleSystem = cc.ParticleSystemQuad:create("Particles/Spiral.plist")
        particleSystem:setPositionType(cc.POSITION_TYPE_GROUPED )
        particleSystem:setTotalParticles(200)

        particleSystem:setPosition(math.mod(math.random(1, 999999), 300) ,math.mod(math.random(1, 999999), 400))

        cclog("add a new system")
		local randZ = math.floor(math.random() * 100)
        AddAndDeleteParticleSystems_batchNode:addChild(particleSystem, randZ, -1)
    end
end

local function AddAndDeleteParticleSystems_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		AddAndDeleteParticleSystems_entry = scheduler:scheduleScriptFunc(removeSystem, 2.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(AddAndDeleteParticleSystems_entry)
	end
end

local function AddAndDeleteParticleSystems()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    --adds the texture inside the plist to the texture cache
    AddAndDeleteParticleSystems_batchNode = cc.ParticleBatchNode:createWithTexture(nil, 16000)

    layer:addChild(AddAndDeleteParticleSystems_batchNode, 1, 2)

    for i = 0, 5 do
        local particleSystem = cc.ParticleSystemQuad:create("Particles/Spiral.plist")
        AddAndDeleteParticleSystems_batchNode:setTexture(particleSystem:getTexture())

        particleSystem:setPositionType(cc.POSITION_TYPE_GROUPED )
        particleSystem:setTotalParticles(200)

        particleSystem:setPosition(i * 15 + 100, i * 15 + 100)

        local randZ = math.floor(math.random() * 100)
        AddAndDeleteParticleSystems_batchNode:addChild(particleSystem, randZ, -1)
	end

    layer:registerScriptHandler(AddAndDeleteParticleSystems_onEnterOrExit)
    emitter = nil

	titleLabel:setString("Add and remove Particle System")
	subtitleLabel:setString("v1.1 test: every 2 sec 1 system disappear, 1 appears")
	return layer
end

---------------------------------
--  ReorderParticleSystems *
--    problem
---------------------------------
local ReorderParticleSystems_entry = nil
local ReorderParticleSystems_batchNode = nil

local function reorderSystem(dt)
	update(dt)

    local childArray = ReorderParticleSystems_batchNode:getChildren()
    local random     = math.random(1,table.getn(childArray))
	local child = childArray[random]
	-- problem: there's no getLocalZOrder() for cc.Object
	-- ReorderParticleSystems_batchNode:reorderChild(child, child:getLocalZOrder() - 1)
	ReorderParticleSystems_batchNode:reorderChild(child, math.random(0, 99999))
end

local function ReorderParticleSystems_onEnterOrExit(tag)
	local scheduler = cc.Director:getInstance():getScheduler()
	if tag == "enter" then
		ReorderParticleSystems_entry = scheduler:scheduleScriptFunc(reorderSystem, 2.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(ReorderParticleSystems_entry)
	end
end

local function ReorderParticleSystems()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background ,true)
    background = nil

    ReorderParticleSystems_batchNode = cc.ParticleBatchNode:create("Images/stars-grayscale.png", 3000)

    layer:addChild(ReorderParticleSystems_batchNode, 1, 2)

    for i = 0, 2 do
        local particleSystem = cc.ParticleSystemQuad:createWithTotalParticles(200)
        particleSystem:setTexture(ReorderParticleSystems_batchNode:getTexture())

        -- duration
        particleSystem:setDuration(cc.PARTICLE_DURATION_INFINITY)

        -- radius mode
        particleSystem:setEmitterMode(cc.PARTICLE_MODE_RADIUS)

        -- radius mode: 100 pixels from center
        particleSystem:setStartRadius(100)
        particleSystem:setStartRadiusVar(0)
        particleSystem:setEndRadius(cc.PARTICLE_START_RADIUS_EQUAL_TO_END_RADIUS )
        particleSystem:setEndRadiusVar(0)    -- not used when start == end

        -- radius mode: degrees per second
        -- 45 * 4 seconds of life = 180 degrees
        particleSystem:setRotatePerSecond(45)
        particleSystem:setRotatePerSecondVar(0)


        -- angle
        particleSystem:setAngle(90)
        particleSystem:setAngleVar(0)

        -- emitter position
        particleSystem:setPosVar(cc.p(0, 0))

        -- life of particles
        particleSystem:setLife(4)
        particleSystem:setLifeVar(0)

        -- spin of particles
        particleSystem:setStartSpin(0)
        particleSystem:setStartSpinVar(0)
        particleSystem:setEndSpin(0)
        particleSystem:setEndSpinVar(0)

        -- color of particles
		local startColor = cc.c4f(0, 0, 0, 1)
		if i == 0 then startColor.r = 1
		elseif i == 1 then startColor.g = 1
		elseif i == 2 then startColor.b = 1
		end

        particleSystem:setStartColor(startColor)
        particleSystem:setStartColorVar(cc.c4f(0, 0, 0, 0))

		local endColor = startColor
        particleSystem:setEndColor(endColor)
        particleSystem:setEndColorVar(cc.c4f(0, 0, 0, 0))

        -- size, in pixels
        particleSystem:setStartSize(32)
        particleSystem:setStartSizeVar(0)
        particleSystem:setEndSize(cc.PARTICLE_START_SIZE_EQUAL_TO_END_SIZE)

        -- emits per second
        particleSystem:setEmissionRate(particleSystem:getTotalParticles() / particleSystem:getLife())

        -- additive
        particleSystem:setPosition(i * 10 + 120, 200)

        ReorderParticleSystems_batchNode:addChild(particleSystem)
        particleSystem:setPositionType(cc.POSITION_TYPE_FREE )

        --particleSystem:release()
    end

    layer:registerScriptHandler(ReorderParticleSystems_onEnterOrExit)
    emitter = nil

	titleLabel:setString("reorder systems")
	subtitleLabel:setString("changes every 2 seconds")
	return layer
end

---------------------------------
--  PremultipliedAlphaTest
---------------------------------
local function PremultipliedAlphaTest()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 255))
    layer:removeChild(background, true)
    background = nil

    emitter = cc.ParticleSystemQuad:create("Particles/BoilingFoam.plist")

    emitter:setBlendFunc(cc.blendFunc(gl.ONE, gl.ONE_MINUS_SRC_ALPHA))

    --assert(emitter:getOpacityModifyRGB(), "Particle texture does not have premultiplied alpha, test is useless")

    emitter:setStartColor(cc.c4f(1, 1, 1, 1))
    emitter:setEndColor(cc.c4f(1, 1, 1, 0))
    emitter:setStartColorVar(cc.c4f(0, 0, 0, 0))
    emitter:setEndColorVar(cc.c4f(0, 0, 0, 0))

    layer:addChild(emitter, 10)

	titleLabel:setString("premultiplied alpha")
	subtitleLabel:setString("no black halo, particles should fade out")
	return layer
end

---------------------------------
--  PremultipliedAlphaTest2
---------------------------------
local function PremultipliedAlphaTest2()
	local layer = getBaseLayer()

	layer:setColor(cc.c3b(0, 0, 0))
    layer:removeChild(background, true)
    background = nil

    emitter = cc.ParticleSystemQuad:create("Particles/TestPremultipliedAlpha.plist")
    layer:addChild(emitter ,10)

	titleLabel:setString("premultiplied alpha 2")
	subtitleLabel:setString("Arrows should be faded")
	return layer
end

---------------------------------
--  Particle Test
---------------------------------
function CreateParticleLayer()
	if SceneIdx == 0 then return ParticleReorder()
	elseif SceneIdx == 1  then return ParticleBatchHybrid()
	elseif SceneIdx == 2  then return ParticleBatchMultipleEmitters()
	elseif SceneIdx == 3  then return DemoFlower()
	elseif SceneIdx == 4  then return DemoGalaxy()
	elseif SceneIdx == 5  then return DemoFirework()
	elseif SceneIdx == 6  then return DemoSpiral()
	elseif SceneIdx == 7  then return DemoSun()
	elseif SceneIdx == 8  then return DemoMeteor()
	elseif SceneIdx == 9  then return DemoFire()
	elseif SceneIdx == 10 then return DemoSmoke()
	elseif SceneIdx == 11 then return DemoExplosion()
	elseif SceneIdx == 12 then return DemoSnow()
	elseif SceneIdx == 13 then return DemoRain()
	elseif SceneIdx == 14 then return DemoBigFlower()
	elseif SceneIdx == 15 then return DemoRotFlower()
	elseif SceneIdx == 16 then return DemoModernArt()
	elseif SceneIdx == 17 then return DemoRing()
	elseif SceneIdx == 18 then return ParallaxParticle()
	elseif SceneIdx == 19 then return DemoParticleFromFile("BoilingFoam")
	elseif SceneIdx == 20 then return DemoParticleFromFile("BurstPipe")
	elseif SceneIdx == 21 then return DemoParticleFromFile("Comet")
	elseif SceneIdx == 22 then return DemoParticleFromFile("debian")
	elseif SceneIdx == 23 then return DemoParticleFromFile("ExplodingRing")
	elseif SceneIdx == 24 then return DemoParticleFromFile("LavaFlow")
	elseif SceneIdx == 25 then return DemoParticleFromFile("SpinningPeas")
	elseif SceneIdx == 26 then return DemoParticleFromFile("SpookyPeas")
	elseif SceneIdx == 27 then return DemoParticleFromFile("Upsidedown")
	elseif SceneIdx == 28 then return DemoParticleFromFile("Flower")
	elseif SceneIdx == 29 then return DemoParticleFromFile("Spiral")
	elseif SceneIdx == 30 then return DemoParticleFromFile("Galaxy")
	elseif SceneIdx == 31 then return DemoParticleFromFile("Phoenix")
    elseif SceneIdx == 32 then return DemoParticleFromFile("lines")
	elseif SceneIdx == 33 then return RadiusMode1()
	elseif SceneIdx == 34 then return RadiusMode2()
	elseif SceneIdx == 35 then return Issue704()
	elseif SceneIdx == 36 then return Issue870()
	--elseif SceneIdx == 36 then return Issue1201()
	-- v1.1 tests
	elseif SceneIdx == 37 then return MultipleParticleSystems()
	elseif SceneIdx == 38 then return MultipleParticleSystemsBatched()
	elseif SceneIdx == 39 then return AddAndDeleteParticleSystems()
	elseif SceneIdx == 40 then return ReorderParticleSystems()
	elseif SceneIdx == 41 then return PremultipliedAlphaTest()
	elseif SceneIdx == 42 then return PremultipliedAlphaTest2()
	end
end

function ParticleTest()
	cclog("ParticleTest")
	local scene = cc.Scene:create()

	SceneIdx = -1
	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	return scene
end
