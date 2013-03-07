
local SceneIdx = 0
local MAX_LAYER = 3

local streak = nil
local titleLabel = nil
local subtitleLabel = nil

local s = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()

local firstTick = nil

local function backAction()
	SceneIdx = SceneIdx - 1
    if SceneIdx < 0 then
        SceneIdx = SceneIdx + MAX_LAYER
    end

    return CreateMotionLayer()
end

local function restartAction()
	return CreateParticleLayer()
end

local function nextAction()
	SceneIdx = SceneIdx + 1
    SceneIdx = math.mod(SceneIdx, MAX_LAYER)

    return CreateMotionLayer()
end

local function modeCallback(sender)
	fastMode = streak:isFastMode()
	if fastMode == true then
		streak:setFastMode(false)
	else
		streak:setFastMode(true)
	end
end

local function backCallback(sender)
	local scene = CCScene:create()

	scene:addChild(backAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function restartCallback(sender)
	local scene = CCScene:create()

	scene:addChild(restartAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function nextCallback(sender)
	local scene = CCScene:create()

	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function getBaseLayer()
	local layer = CCLayer:create()

	titleLabel = CCLabelTTF:create("", "Arial", 32)
    layer:addChild(titleLabel, 0)
    titleLabel:setPosition(s.width / 2, s.height - 50)

	subtitleLabel = CCLabelTTF:create("", "Thonburi", 16)
	layer:addChild(subtitleLabel, 1)
    subtitleLabel:setPosition(s.width / 2, s.height - 80)

    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
	item1:registerScriptTapHandler(backCallback)
	item2:registerScriptTapHandler(restartCallback)
	item3:registerScriptTapHandler(nextCallback)

    local menu = CCMenu:create()
	menu:addChild(item1)
	menu:addChild(item2)
	menu:addChild(item3)

    menu:setPosition(CCPointMake(0, 0))
    item1:setPosition(CCPointMake(s.width/2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(s.width/2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(s.width/2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    layer:addChild(menu, 1)

    local itemMode = CCMenuItemToggle:create(CCMenuItemFont:create("Use High Quality Mode"))
	itemMode:addSubItem(CCMenuItemFont:create("Use Fast Mode"))
	itemMode:registerScriptTapHandler(modeCallback)
    local menuMode = CCMenu:create()
	menuMode:addChild(itemMode)
    menuMode:setPosition(ccp(s.width / 2, s.height / 4))
    layer:addChild(menuMode)

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

	streak:setPosition(target:convertToWorldSpace(ccp(0, 0)))
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

	root = CCSprite:create(s_pPathR1)
    layer:addChild(root, 1)
    root:setPosition(ccp(s.width / 2, s.height / 2))

    target = CCSprite:create(s_pPathR1)
    root:addChild(target)
    target:setPosition(ccp(s.width / 4, 0))

    streak = CCMotionStreak:create(2, 3, 32, ccc3(0, 255, 0), s_streak)
    layer:addChild(streak)

    local a1 = CCRotateBy:create(2, 360)

    local action1 = CCRepeatForever:create(a1)
    local motion = CCMoveBy:create(2, CCPointMake(100,0))
    root:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(motion, motion:reverse())))
    root:runAction(action1)

	local array = CCArray:create()
	array:addObject(CCTintTo:create(0.2, 255, 0, 0))
	array:addObject(CCTintTo:create(0.2, 0, 255, 0))
	array:addObject(CCTintTo:create(0.2, 0, 0, 255))
	array:addObject(CCTintTo:create(0.2, 0, 255, 255))
	array:addObject(CCTintTo:create(0.2, 255, 255, 0))
	array:addObject(CCTintTo:create(0.2, 255, 255, 255))
    local colorAction = CCRepeatForever:create(CCSequence:create(array))

    streak:runAction(colorAction)

	firstTick = true
	layer:registerScriptHandler(MotionStreakTest1_onEnterOrExit)

	titleLabel:setString("MotionStreak test 1")
	return layer
end

-----------------------------------
--  MotionStreakTest2
-----------------------------------
local function MotionStreakTest2()
	local layer = getBaseLayer()

    streak = CCMotionStreak:create(3, 3, 64, ccc3(255, 255, 255), s_streak)
    layer:addChild(streak)

    streak:setPosition(CCPointMake(s.width / 2, s.height / 2))

	local function onTouchMoved(x, y)
		if firstTick == true then
			firstTick = false
			return
		end

		streak:setPosition(ccp(x, y))
    end

    local function onTouch(eventType, x, y)
		if eventType == "began" then
			return true
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        end
    end

	firstTick = true
	layer:setTouchEnabled(true)
    layer:registerScriptTouchHandler(onTouch)

	titleLabel:setString("MotionStreak test")
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
		ccp(center.x + math.cos(fAngle / 180 * math.pi) * fRadius, center.y + math.sin(fAngle/ 180 * math.pi) * fRadius))
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

	streak = CCMotionStreak:create(2.0, 1.0, 50.0, ccc3(255, 255, 0), "Images/Icon.png")
    layer:addChild(streak)

    center = ccp(s.width / 2, s.height / 2)
    fRadius = s.width / 3
    fAngle = 0

	firstTick = true
	layer:registerScriptHandler(Issue1358_onEnterOrExit)

	titleLabel:setString("Issue 1358")
	subtitleLabel:setString("The tail should use the texture")
	return layer
end

-----------------------------------
--  Motion Streak Test
-----------------------------------
function CreateMotionLayer()
	if SceneIdx == 0 then
		return MotionStreakTest1()
	elseif SceneIdx == 1  then
		return MotionStreakTest2()
	elseif SceneIdx == 2  then
		return Issue1358()
	end
end

function MotionStreakTest()
	local scene = CCScene:create()

	SceneIdx = -1
	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	return scene
end
