
local streak = nil
local titleLabel = nil
local subtitleLabel = nil

local s = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

local firstTick = nil

local function modeCallback(sender)
	fastMode = streak:isFastMode()
	if fastMode == true then
		streak:setFastMode(false)
	else
		streak:setFastMode(true)
	end
end

local function getBaseLayer()
	local layer = cc.Layer:create()

    local itemMode = cc.MenuItemToggle:create(cc.MenuItemFont:create("Use High Quality Mode"))
	itemMode:addSubItem(cc.MenuItemFont:create("Use Fast Mode"))
	itemMode:registerScriptTapHandler(modeCallback)
    local menuMode = cc.Menu:create()
	menuMode:addChild(itemMode)
    menuMode:setPosition(cc.p(s.width / 2, s.height / 4))
    layer:addChild(menuMode)

    Helper.initWithLayer(layer)

	return layer
end

-----------------------------------
--  MotionStreakTest1
-----------------------------------
local root = nil
local target = nil

local MotionStreakTest1_entry = nil

local function MotionStreakTest1_update(dt)
	if firstTick == true then
		firstTick = false
		return
	end

	streak:setPosition(target:convertToWorldSpace(cc.p(0, 0)))
end

local function MotionStreakTest1_onEnterOrExit(tag)
	if tag == "enter" then
		MotionStreakTest1_entry = scheduler:scheduleScriptFunc(MotionStreakTest1_update, 0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(MotionStreakTest1_entry)
	end
end

local function MotionStreakTest1()
	local layer = getBaseLayer()

	root = cc.Sprite:create(s_pPathR1)
    layer:addChild(root, 1)
    root:setPosition(cc.p(s.width / 2, s.height / 2))

    target = cc.Sprite:create(s_pPathR1)
    root:addChild(target)
    target:setPosition(cc.p(s.width / 4, 0))

    streak = cc.MotionStreak:create(2, 3, 32, cc.c3b(0, 255, 0), s_streak)
    layer:addChild(streak)

    local a1 = cc.RotateBy:create(2, 360)

    local action1 = cc.RepeatForever:create(a1)
    local motion = cc.MoveBy:create(2, cc.p(100,0))
    root:runAction(cc.RepeatForever:create(cc.Sequence:create(motion, motion:reverse())))
    root:runAction(action1)

    local colorAction = cc.RepeatForever:create(cc.Sequence:create(cc.TintTo:create(0.2, 255, 0, 0),
                                                cc.TintTo:create(0.2, 0, 255, 0),
                                                cc.TintTo:create(0.2, 0, 0, 255),
                                                cc.TintTo:create(0.2, 0, 255, 255),
                                                cc.TintTo:create(0.2, 255, 255, 0),
                                                cc.TintTo:create(0.2, 255, 255, 255)))

    streak:runAction(colorAction)

	firstTick = true
	layer:registerScriptHandler(MotionStreakTest1_onEnterOrExit)

	Helper.titleLabel:setString("MotionStreak test 1")
	return layer
end

-----------------------------------
--  MotionStreakTest2
-----------------------------------
local function MotionStreakTest2()
	local layer = getBaseLayer()

    streak = cc.MotionStreak:create(3, 3, 64, cc.c3b(255, 255, 255), s_streak)
    layer:addChild(streak)

    streak:setPosition(cc.p(s.width / 2, s.height / 2))

    local function onTouchesMoved(touches, event)
        streak:setPosition( touches[1]:getLocation() )
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()
    listener:registerScriptHandler(onTouchesMoved,cc.Handler.EVENT_TOUCHES_MOVED )
    local eventDispatcher = layer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, layer)

	Helper.titleLabel:setString("MotionStreak test")

	return layer
end

-----------------------------------
--  Issue1358
-----------------------------------
local Issue1358_entry = nil

local center = nil
local fAngle = nil
local fRadius = nil

local function Issue1358_update(dt)
	if firstTick == true then
		firstTick = false
		return
	end
	fAngle = fAngle + 1.0
    streak:setPosition(
		cc.p(center.x + math.cos(fAngle / 180 * math.pi) * fRadius, center.y + math.sin(fAngle/ 180 * math.pi) * fRadius))
end

local function Issue1358_onEnterOrExit(tag)
	if tag == "enter" then
		Issue1358_entry = scheduler:scheduleScriptFunc(Issue1358_update, 0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Issue1358_entry)
	end
end

local function Issue1358()
	local layer = getBaseLayer()

	streak = cc.MotionStreak:create(2.0, 1.0, 50.0, cc.c3b(255, 255, 0), "Images/Icon.png")
    layer:addChild(streak)

    center = cc.p(s.width / 2, s.height / 2)
    fRadius = s.width / 3
    fAngle = 0

	firstTick = true
	layer:registerScriptHandler(Issue1358_onEnterOrExit)

	Helper.titleLabel:setString("Issue 1358")
	Helper.subtitleLabel:setString("The tail should use the texture")
	return layer
end

function MotionStreakTest()
	local scene = cc.Scene:create()

    Helper.createFunctionTable = {
        MotionStreakTest1,
        MotionStreakTest2,
        Issue1358
    }

	scene:addChild(MotionStreakTest1())
	scene:addChild(CreateBackMenuItem())

	return scene
end
