local kTagSprite1 = 1
local kTagSprite2 = 2
local kTagSprite3 = 3
local kTagSlider  = 4

local s = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

local function getBaseLayer()
	local layer = cc.Layer:create()

	Helper.initWithLayer(layer)

    return layer
end

-----------------------------------
--  CameraCenterTest
-----------------------------------
local function CameraCenterTest()
	local layer = getBaseLayer()

    -- LEFT-TOP
    local sprite = cc.Sprite:create("Images/white-512x512.png")
    layer:addChild(sprite, 0)
    sprite:setPosition(cc.p(s.width / 5 * 1, s.height / 5 * 1))
    sprite:setColor(cc.c3b(255, 0, 0))
    sprite:setTextureRect(cc.rect(0, 0, 120, 50))
    local orbit = cc.OrbitCamera:create(10, 1, 0, 0, 360, 0, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))
	-- [sprite setAnchorPoint: cc.p(0,1))

    -- LEFT-BOTTOM
    sprite = cc.Sprite:create("Images/white-512x512.png")
    layer:addChild(sprite, 0, 40)
    sprite:setPosition(cc.p(s.width / 5 * 1, s.height / 5 * 4))
    sprite:setColor(cc.c3b(0, 0, 255))
    sprite:setTextureRect(cc.rect(0, 0, 120, 50))
    orbit = cc.OrbitCamera:create(10, 1, 0, 0, 360, 0, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))

    -- RIGHT-TOP
    sprite = cc.Sprite:create("Images/white-512x512.png")
    layer:addChild(sprite, 0)
    sprite:setPosition(cc.p(s.width / 5 * 4, s.height / 5 * 1))
    sprite:setColor(cc.c3b(255, 255, 0))
    sprite:setTextureRect(cc.rect(0, 0, 120, 50))
    orbit = cc.OrbitCamera:create(10, 1, 0, 0, 360, 0, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))

    -- RIGHT-BOTTOM
    sprite = cc.Sprite:create("Images/white-512x512.png")
    layer:addChild(sprite, 0, 40)
    sprite:setPosition(cc.p(s.width / 5 * 4, s.height / 5 * 4))
    sprite:setColor(cc.c3b(0, 255, 0))
    sprite:setTextureRect(cc.rect(0, 0, 120, 50))
    orbit = cc.OrbitCamera:create(10, 1, 0, 0, 360, 0, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))

    -- CENTER
    sprite = cc.Sprite:create("Images/white-512x512.png")
    layer:addChild(sprite, 0, 40)
    sprite:setPosition(cc.p(s.width / 2, s.height / 2))
    sprite:setColor(cc.c3b(255, 255, 255))
    sprite:setTextureRect(cc.rect(0, 0, 120, 50))
    orbit = cc.OrbitCamera:create(10, 1, 0, 0, 360, 0, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))

	Helper.titleLabel:setString("Camera Center test")
	Helper.subtitleLabel:setString("Sprites should rotate at the same speed")
	return layer
end

-----------------------------------
--  Test2
-----------------------------------
local function Test2()
	local layer = getBaseLayer()

	local sp1 = cc.Sprite:create(s_pPathSister1)
    local sp2 = cc.Sprite:create(s_pPathSister2)
    local sp3 = cc.Sprite:create(s_pPathSister1)
    local sp4 = cc.Sprite:create(s_pPathSister2)

    sp1:setPosition(cc.p(100, s.height /2))
    sp2:setPosition(cc.p(380, s.height /2))
    layer:addChild(sp1)
    layer:addChild(sp2)

    sp3:setScale(0.25)
    sp4:setScale(0.25)
    sp1:addChild(sp3)
    sp2:addChild(sp4)

    local a1 = cc.RotateBy:create(2, 360)
    local a2 = cc.ScaleBy:create(2, 2)

    local action1 = cc.RepeatForever:create(cc.Sequence:create(a1, a2, a2:reverse()))
    local action2 = cc.RepeatForever:create(cc.Sequence:create(a1:clone(), a2:clone(), a2:reverse()))

    sp2:setAnchorPoint(cc.p(0,0))

    sp1:runAction(action1)
    sp2:runAction(action2)

	Helper.titleLabel:setString("anchorPoint and children")
	return layer
end

-----------------------------------
--  Test4
-----------------------------------
local Test4_layer = nil
local Test4_delay2Entry = nil
local Test4_delay4Entry = nil

local function delay2(dt)
	node = Test4_layer:getChildByTag(2)
    local action1 = cc.RotateBy:create(1, 360)
    node:runAction(action1)
end

local function delay4(dt)
	scheduler:unscheduleScriptEntry(Test4_delay4Entry)
    Test4_layer:removeChildByTag(3, false)
end

local function Test4_onEnterOrExit(tag)
	if tag == "enter" then
		Test4_delay2Entry = scheduler:scheduleScriptFunc(delay2, 2.0, false)
		Test4_delay4Entry = scheduler:scheduleScriptFunc(delay4, 4.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Test4_delay2Entry)
		scheduler:unscheduleScriptEntry(Test4_delay4Entry)
	end
end

local function Test4()
	Test4_layer = getBaseLayer()

	local sp1 = cc.Sprite:create(s_pPathSister1)
    local sp2 = cc.Sprite:create(s_pPathSister2)
    sp1:setPosition(cc.p(100, 160))
    sp2:setPosition(cc.p(380, 160))

    Test4_layer:addChild(sp1, 0, 2)
    Test4_layer:addChild(sp2, 0, 3)

    Test4_layer:registerScriptHandler(Test4_onEnterOrExit)

	Helper.titleLabel:setString("tags")
	return Test4_layer
end

-----------------------------------
--  Test5
-----------------------------------
local Test5_entry = nil
local Test5_layer = nil

local function Test5_addAndRemove(dt)
	local sp1 = Test5_layer:getChildByTag(kTagSprite1)
    local sp2 = Test5_layer:getChildByTag(kTagSprite2)

    sp1:retain()
    sp2:retain()

    Test5_layer:removeChild(sp1, false)
    Test5_layer:removeChild(sp2, true)

    Test5_layer:addChild(sp1, 0, kTagSprite1)
    Test5_layer:addChild(sp2, 0, kTagSprite2)

    sp1:release()
    sp2:release()
end

local function Test5_onEnterOrExit(tag)
	if tag == "enter" then
		Test5_entry = scheduler:scheduleScriptFunc(Test5_addAndRemove, 2.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Test5_entry)
	end
end

local function Test5()
	Test5_layer = getBaseLayer()

	local sp1 = cc.Sprite:create(s_pPathSister1)
    local sp2 = cc.Sprite:create(s_pPathSister2)

    sp1:setPosition(cc.p(100, 160))
    sp2:setPosition(cc.p(380, 160))

    local rot = cc.RotateBy:create(2, 360)
    local rot_back = rot:reverse()
    local forever = cc.RepeatForever:create(cc.Sequence:create(rot, rot_back))

	local rot2 = cc.RotateBy:create(2, 360)
	local rot2_back = rot2:reverse()
	local forever2 = cc.RepeatForever:create(cc.Sequence:create(rot2, rot2_back))

	forever:setTag(101)
    forever2:setTag(102)

    Test5_layer:addChild(sp1, 0, kTagSprite1)
    Test5_layer:addChild(sp2, 0, kTagSprite2)

    sp1:runAction(forever)
    sp2:runAction(forever2)

    Test5_layer:registerScriptHandler(Test5_onEnterOrExit)

	Helper.titleLabel:setString("remove and cleanup")
	return Test5_layer
end

-----------------------------------
--  Test6
-----------------------------------
local Test6_entry = nil
local Test6_layer = nil

local function Test6_addAndRemove(dt)
	local sp1 = Test6_layer:getChildByTag(kTagSprite1)
    local sp2 = Test6_layer:getChildByTag(kTagSprite2)

    sp1:retain()
    sp2:retain()

    Test6_layer:removeChild(sp1, false)
    Test6_layer:removeChild(sp2, true)

    Test6_layer:addChild(sp1, 0, kTagSprite1)
    Test6_layer:addChild(sp2, 0, kTagSprite2)

    sp1:release()
    sp2:release()
end

local function Test6_onEnterOrExit(tag)
	if tag == "enter" then
		Test6_entry = scheduler:scheduleScriptFunc(Test6_addAndRemove, 2.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Test6_entry)
	end
end

local function Test6()
	Test6_layer = getBaseLayer()

	local sp1 = cc.Sprite:create(s_pPathSister1)
    local sp11 = cc.Sprite:create(s_pPathSister1)

    local sp2 = cc.Sprite:create(s_pPathSister2)
    local sp21 = cc.Sprite:create(s_pPathSister2)

    sp1:setPosition(cc.p(100, 160))
    sp2:setPosition(cc.p(380, 160))

    local rot = cc.RotateBy:create(2, 360)
    local rot_back = rot:reverse()
    local forever1 = cc.RepeatForever:create(cc.Sequence:create(rot, rot_back))
    local forever11 = forever1:clone()

    local forever2 = forever1:clone()
    local forever21 = forever1:clone()

    Test6_layer:addChild(sp1, 0, kTagSprite1)
    sp1:addChild(sp11)
    Test6_layer:addChild(sp2, 0, kTagSprite2)
    sp2:addChild(sp21)

    sp1:runAction(forever1)
    sp11:runAction(forever11)
    sp2:runAction(forever2)
    sp21:runAction(forever21)

	Test6_layer:registerScriptHandler(Test6_onEnterOrExit)

	Helper.titleLabel:setString("remove/cleanup with children")
	return Test6_layer
end

-----------------------------------
--  StressTest1
-----------------------------------
local StressTest1_entry = nil
local StressTest1_layer = nil

local function removeMe(node)
	local parent = StressTest1_layer:getParent()
	parent:removeChild(node, true)
    Helper.nextAction()
end

local function shouldNotCrash(dt)
	scheduler:unscheduleScriptEntry(StressTest1_entry)

    -- if the node has timers, it crashes
    local explosion = cc.ParticleSun:create()
    explosion:setTexture(cc.Director:getInstance():getTextureCache():addImage("Images/fire.png"))

    explosion:setPosition(s.width / 2, s.height / 2)

	StressTest1_layer:setAnchorPoint(cc.p(0, 0))
    local callFunc = cc.CallFunc:create(removeMe)
    StressTest1_layer:runAction(cc.Sequence:create(cc.RotateBy:create(2, 360), callFunc))

    StressTest1_layer:addChild(explosion)
end

local function StressTest1_onEnterOrExit(tag)
	if tag == "enter" then
		StressTest1_entry = scheduler:scheduleScriptFunc(shouldNotCrash, 1.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(StressTest1_entry)
	end
end

local function StressTest1()
	StressTest1_layer = getBaseLayer()

	sp1 = cc.Sprite:create(s_pPathSister1)
    StressTest1_layer:addChild(sp1, 0, kTagSprite1)

    sp1:setPosition(cc.p(s.width / 2, s.height / 2))

    StressTest1_layer:registerScriptHandler(StressTest1_onEnterOrExit)

	Helper.titleLabel:setString("stress test #1: no crashes")
	return StressTest1_layer
end

-----------------------------------
--  StressTest2
-----------------------------------
local StressTest2_entry = nil
local StressTest2_layer = nil

local function shouldNotLeak(dt)
	scheduler:unscheduleScriptEntry(StressTest2_entry)

    local sublayer = StressTest2_layer:getChildByTag(kTagSprite1)
    sublayer:removeAllChildren(true)
end

local function StressTest2_onEnterOrExit(tag)
	if tag == "enter" then
		StressTest2_entry = scheduler:scheduleScriptFunc(shouldNotLeak, 6.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(StressTest2_entry)
	end
end

local function StressTest2()
	StressTest2_layer = getBaseLayer()

	sublayer = cc.Layer:create()

    local sp1 = cc.Sprite:create(s_pPathSister1)
    sp1:setPosition(cc.p(80, s.height / 2))

    local move = cc.MoveBy:create(3, cc.p(350, 0))
    local move_ease_inout3 = cc.EaseInOut:create(cc.MoveBy:create(3, cc.p(350, 0)), 2.0)
    local move_ease_inout_back3 = move_ease_inout3:reverse()
    local seq3 = cc.Sequence:create(move_ease_inout3, move_ease_inout_back3)
    sp1:runAction(cc.RepeatForever:create(seq3))
    sublayer:addChild(sp1, 1)

    local fire = cc.ParticleFire:create()
    local fireTexture = cc.Director:getInstance():getTextureCache():addImage("Images/fire.png")
    fire:setTexture(fireTexture)
    fire:setPosition(80, s.height / 2 - 50)

    local copy_seq3 = seq3:clone()
    fire:runAction(cc.RepeatForever:create(copy_seq3))
    sublayer:addChild(fire, 2)

    StressTest2_layer:registerScriptHandler(StressTest2_onEnterOrExit)

    StressTest2_layer:addChild(sublayer, 0, kTagSprite1)

	Helper.titleLabel:setString("stress test #2: no leaks")
	return StressTest2_layer
end

-----------------------------------
--  NodeToWorld
-----------------------------------
local function NodeToWorld()
	local layer = getBaseLayer()

    -- This code tests that nodeToParent works OK:
    --  - It tests different anchor Points
    --  - It tests different children anchor points

    local back = cc.Sprite:create(s_back3)
    layer:addChild(back, -10)
    back:setAnchorPoint(cc.p(0, 0))
    local backSize = back:getContentSize()

    local item = cc.MenuItemImage:create(s_PlayNormal, s_PlaySelect)
    local menu = cc.Menu:create()
	menu:addChild(item)
    menu:alignItemsVertically()
    menu:setPosition(cc.p(backSize.width / 2, backSize.height / 2))
    back:addChild(menu)

    local rot = cc.RotateBy:create(5, 360)
    local fe = cc.RepeatForever:create(rot)
    item:runAction(fe)

    local move = cc.MoveBy:create(3, cc.p(200, 0))
    local move_back = move:reverse()
    local seq = cc.Sequence:create(move, move_back)
    local fe2 = cc.RepeatForever:create(seq)
    back:runAction(fe2)

	Helper.titleLabel:setString("nodeToParent transform")
	return layer
end

-----------------------------------
--  CameraOrbitTest
-----------------------------------
local function CameraOrbitTest_onEnterOrExit(tag)
	if tag == "enter" then
		cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION3_D)
        cc.Director:getInstance():getRenderer():setDepthTest(true)
        cc.Director:getInstance():getRenderer():setDepthWrite(true)
	elseif tag == "exit" then
		cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION_DEFAULT)
        cc.Director:getInstance():getRenderer():setDepthTest(false)
        cc.Director:getInstance():getRenderer():setDepthWrite(false)
	end
end

local function CameraOrbitTest()
	local layer = getBaseLayer()

	local p = cc.Sprite:create(s_back3)
    layer:addChild(p, 0)
    p:setPosition(cc.p(s.width / 2, s.height / 2))
    p:setOpacity(128)

    -- LEFT
    local s = p:getContentSize()
    local sprite = cc.Sprite:create(s_pPathGrossini)
    sprite:setScale(0.5)
    p:addChild(sprite, 0)
    sprite:setPosition(cc.p(s.width / 4 * 1, s.height / 2))
    local orbit = cc.OrbitCamera:create(2, 1, 0, 0, 360, 0, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))

    -- CENTER
    sprite = cc.Sprite:create(s_pPathGrossini)
    sprite:setScale(1.0)
    p:addChild(sprite, 0)
    sprite:setPosition(cc.p(s.width / 4 * 2, s.height / 2))
    orbit = cc.OrbitCamera:create(2, 1, 0, 0, 360, 45, 0)
    sprite:runAction(cc.RepeatForever:create(orbit))

    -- RIGHT
    sprite = cc.Sprite:create(s_pPathGrossini)
    sprite:setScale(2.0)
    p:addChild(sprite, 0)
    sprite:setPosition(cc.p(s.width / 4 * 3, s.height / 2))
    local ss = sprite:getContentSize()
    orbit = cc.OrbitCamera:create(2, 1, 0, 0, 360, 90, -45)
    sprite:runAction(cc.RepeatForever:create(orbit))

    -- PARENT
    orbit = cc.OrbitCamera:create(10, 1, 0, 0, 360, 0, 90)
    p:runAction(cc.RepeatForever:create(orbit))

    layer:setScale(1)
    layer:registerScriptHandler(CameraOrbitTest_onEnterOrExit)
	Helper.titleLabel:setString("Camera Orbit test")
	return layer
end

-----------------------------------
--  CameraZoomTest
-----------------------------------
local z = 0
local CameraZoomTest_layer = nil
local CameraZoomTest_entry = nil

local function CameraZoomTest_update(dt)
	z = z + dt * 100

    local sprite = CameraZoomTest_layer:getChildByTag(20)
    -- local cam = sprite:getCamera()
    -- cam:setEye(0, 0, z)

    sprite = CameraZoomTest_layer:getChildByTag(40)
    -- cam = sprite:getCamera()
    -- cam:setEye(0, 0, -z)
end

local function CameraZoomTest_onEnterOrExit(tag)
	if tag == "enter" then
		cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION3_D)
		CameraZoomTest_entry = scheduler:scheduleScriptFunc(CameraZoomTest_update, 0.0, false)
	elseif tag == "exit" then
		cc.Director:getInstance():setProjection(cc.DIRECTOR_PROJECTION_DEFAULT)
		scheduler:unscheduleScriptEntry(CameraZoomTest_entry)
	end
end

local function CameraZoomTest()
	CameraZoomTest_layer = getBaseLayer()

	z = 0

    -- LEFT
    local sprite = cc.Sprite:create(s_pPathGrossini)
    CameraZoomTest_layer:addChild(sprite, 0)
    sprite:setPosition(cc.p(s.width / 4 * 1, s.height / 2))
    -- local cam = sprite:getCamera()
    -- cam:setEye(0, 0, 415 / 2)
    -- cam:setCenter(0, 0, 0)

    -- CENTER
    sprite = cc.Sprite:create(s_pPathGrossini)
    CameraZoomTest_layer:addChild(sprite, 0, 40)
    sprite:setPosition(cc.p(s.width / 4 * 2, s.height / 2))

    -- RIGHT
    sprite = cc.Sprite:create(s_pPathGrossini)
    CameraZoomTest_layer:addChild(sprite, 0, 20)
    sprite:setPosition(cc.p(s.width / 4 * 3, s.height / 2))

	CameraZoomTest_layer:scheduleUpdateWithPriorityLua(CameraZoomTest_update, 0)
	CameraZoomTest_layer:registerScriptHandler(CameraZoomTest_onEnterOrExit)

	Helper.titleLabel:setString("Camera Zoom test")
	return CameraZoomTest_layer
end

-----------------------------------
--  ConvertToNode
-----------------------------------
local ConvertToNode_layer = nil

local function ConvertToNode()
	ConvertToNode_layer = getBaseLayer()

    local rotate = cc.RotateBy:create(10, 360)
    local action = cc.RepeatForever:create(rotate)
    for i = 0, 2 do
        local sprite = cc.Sprite:create("Images/grossini.png")
        sprite:setPosition(cc.p(s.width / 4 * (i + 1), s.height / 2))

        local point = cc.Sprite:create("Images/r1.png")
        point:setScale(0.25)
        point:setPosition(sprite:getPosition())
        ConvertToNode_layer:addChild(point, 10, 100 + i)

        if i == 0 then
			sprite:setAnchorPoint(cc.p(0, 0))
		elseif i == 1 then
            sprite:setAnchorPoint(cc.p(0.5, 0.5))
        elseif i == 2 then
            sprite:setAnchorPoint(cc.p(1,1))
		end

        point:setPosition(sprite:getPosition())

        local copy = action:clone()
        sprite:runAction(copy)
        ConvertToNode_layer:addChild(sprite, i)
    end

    local function onTouchesEnded(touches, event)
        local count = table.getn(touches)
        for i = 1, count do
            local location = touches[i]:getLocation()
            for j = 1,3 do
                local node = ConvertToNode_layer:getChildByTag(100 + i - 1)
                local p1, p2
                p1 = node:convertToNodeSpaceAR(location)
                p2 = node:convertToNodeSpace(location)

                cclog("AR: x=" .. p1.x .. ", y=" .. p1.y .. " -- Not AR: x=" .. p2.x .. ", y=" .. p2.y)
            end
        end
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesEnded,cc.Handler.EVENT_TOUCHES_ENDED )
    local eventDispatcher = ConvertToNode_layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, ConvertToNode_layer)

	Helper.titleLabel:setString("Convert To Node Space")
	Helper.subtitleLabel:setString("testing convertToNodeSpace / AR. Touch and see console")
	return ConvertToNode_layer
end

-----------------------------------
--  NodeOpaqueTest
-----------------------------------
local function NodeOpaqueTest()
	local layer = getBaseLayer()

    for i = 0, 49 do
        local background = cc.Sprite:create("Images/background1.png")
        background:setBlendFunc(cc.blendFunc(ccb.BlendFactor.ONE, ccb.BlendFactor.ONE_MINUS_SRC_ALPHA))
        background:setAnchorPoint(cc.p(0, 0))
        layer:addChild(background)
    end

	Helper.titleLabel:setString("Node Opaque Test")
	Helper.subtitleLabel:setString("Node rendered with GL_BLEND disabled")
	return layer
end

-----------------------------------
--  NodeNonOpaqueTest
-----------------------------------
local function NodeNonOpaqueTest()
	local layer = getBaseLayer()

    for i = 0, 49 do
        background = cc.Sprite:create("Images/background1.jpg")
        background:setBlendFunc(cc.blendFunc(ccb.BlendFactor.ONE, ccb.BlendFactor.ZERO))
        background:setAnchorPoint(cc.p(0, 0))
        layer:addChild(background)
    end
	Helper.titleLabel:setString("Node Non Opaque Test")
	Helper.subtitleLabel:setString("Node rendered with GL_BLEND enabled")
	return layer
end

-----------------------------------
--  NodeGlobalZValueTest
-----------------------------------
local function NodeGlobalZValueTest()
    local layer = getBaseLayer()
    Helper.titleLabel:setString("Global Z Value")
    Helper.subtitleLabel:setString("Center Sprite should change go from foreground to background")


    local s = cc.Director:getInstance():getWinSize()
    local zOrderSprite = nil
    for i = 1,9 do
        local parent = cc.Node:create()
        local sprite = nil
        if i == 5 then
            sprite = cc.Sprite:create("Images/grossinis_sister2.png")
            sprite:setGlobalZOrder(-1)
            zOrderSprite = sprite
        else
            sprite = cc.Sprite:create("Images/grossinis_sister1.png")
        end
        parent:addChild(sprite)
        layer:addChild(parent)

        local w = sprite:getContentSize().width
        sprite:setPosition(s.width/2 - w*0.7*(i - 6),s.height / 2)
    end

    local accum = 0

    local function update(dt)
        accum = accum + dt
        if accum > 1 then
            local z = zOrderSprite:getGlobalZOrder()
            zOrderSprite:setGlobalZOrder(-z)
            accum = 0
        end
    end

    local function onNodeEvent(tag)
        if tag == "exit" then
            layer:unscheduleUpdate()
        end
    end
    layer:scheduleUpdateWithPriorityLua(update,0)
    layer:registerScriptHandler(onNodeEvent)

    return layer
end



function CocosNodeTest()
	local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        CameraCenterTest,
        Test2,
        Test4,
        Test5,
        Test6,
        StressTest1,
        StressTest2,
        NodeToWorld,
        CameraOrbitTest,
        -- CameraZoomTest,
        ConvertToNode,
        NodeOpaqueTest,
        NodeNonOpaqueTest,
        NodeGlobalZValueTest,
    }
    Helper.index = 1

	scene:addChild(CameraCenterTest())
	scene:addChild(CreateBackMenuItem())

	return scene
end
