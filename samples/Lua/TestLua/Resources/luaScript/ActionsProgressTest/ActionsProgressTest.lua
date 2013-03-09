
local SceneIdx = -1
local MAX_LAYER = 7
local s = CCDirector:sharedDirector():getWinSize()

local function nextAction()
	SceneIdx = SceneIdx + 1
    SceneIdx = math.mod(SceneIdx, MAX_LAYER)
    return CreateActionProgressLayer()
end

local function restartAction()
	return CreateActionProgressLayer()
end

local function backAction()
	SceneIdx = SceneIdx - 1
    if SceneIdx < 0 then
		SceneIdx = SceneIdx + MAX_LAYER
	end
    return CreateActionProgressLayer()
end

local function nextCallback(sender)
	local scene = CCScene:create()

	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function restartCallback(sender)
	local scene = CCScene:create()

	scene:addChild(restartAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function backCallback(sender)
	local scene = CCScene:create()

	scene:addChild(backAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function initWithLayer(layer)
	titleLabel = CCLabelTTF:create("ActionsProgressTest", "Arial", 18)
    layer:addChild(titleLabel, 1)
    titleLabel:setPosition(s.width / 2, s.height - 50)

    subtitleLabel = CCLabelTTF:create("", "Thonburi", 22)
	layer:addChild(subtitleLabel, 1)
	subtitleLabel:setPosition(s.width / 2, s.height - 80)

	-- menu
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
    item1:setPosition(CCPointMake(s.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(s.width / 2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(s.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    layer:addChild(menu, 1)

    local background = CCLayerColor:create(ccc4(255,0,0,255))
    layer:addChild(background, -10)
end

------------------------------------
--  SpriteProgressToRadial
------------------------------------
local function SpriteProgressToRadial()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local to1 = CCProgressTo:create(2, 100)
    local to2 = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeRadial)
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(to1))
	layer:addChild(left)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathBlock))
    right:setType(kCCProgressTimerTypeRadial)
    -- Makes the ridial CCW
    right:setReverseProgress(true)
    right:setPosition(CCPointMake(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(to2))
	layer:addChild(right)

	subtitleLabel:setString("ProgressTo Radial")
	return layer
end

------------------------------------
--  SpriteProgressToHorizontal
------------------------------------
local function SpriteProgressToHorizontal()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local to1 = CCProgressTo:create(2, 100)
    local to2 = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the left since the midpoint is 0 for the x
    left:setMidpoint(CCPointMake(0, 0))
    -- Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left:setBarChangeRate(CCPointMake(1, 0))
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(to1))
	layer:addChild(left)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the left since the midpoint is 1 for the x
    right:setMidpoint(CCPointMake(1, 0))
    -- Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right:setBarChangeRate(CCPointMake(1, 0))
    right:setPosition(CCPointMake(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(to2))
	layer:addChild(right)

	subtitleLabel:setString("ProgressTo Horizontal")
	return layer
end

------------------------------------
--  SpriteProgressToVertical
------------------------------------
local function SpriteProgressToVertical()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local to1 = CCProgressTo:create(2, 100)
    local to2 = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPointMake(0,0))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPointMake(0, 1))
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(to1))
	layer:addChild(left)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPointMake(0, 1))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPointMake(0, 1))
    right:setPosition(CCPointMake(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(to2))
	layer:addChild(right)

	subtitleLabel:setString("ProgressTo Vertical")
	return layer
end

------------------------------------
--  SpriteProgressToRadialMidpointChanged
------------------------------------
local function SpriteProgressToRadialMidpointChanged()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local action = CCProgressTo:create(2, 100)

	-- Our image on the left should be a radial progress indicator, clockwise
    local left = CCProgressTimer:create(CCSprite:create(s_pPathBlock))
    left:setType(kCCProgressTimerTypeRadial)
    left:setMidpoint(CCPointMake(0.25, 0.75))
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(left)

	-- Our image on the left should be a radial progress indicator, counter clockwise
    local right = CCProgressTimer:create(CCSprite:create(s_pPathBlock))
    right:setType(kCCProgressTimerTypeRadial)
    right:setMidpoint(CCPointMake(0.75, 0.25))

	--[[
	   Note the reverse property (default=NO) is only added to the right image. That's how
       we get a counter clockwise progress.
	]]
    right:setPosition(CCPointMake(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
    layer:addChild(right)

	subtitleLabel:setString("Radial w/ Different Midpoints")
	return layer
end

------------------------------------
--  SpriteProgressBarVarious
------------------------------------
local function SpriteProgressBarVarious()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local to = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPointMake(1, 0))
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(left)

    local middle = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    middle:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(CCPointMake(1, 1))
    middle:setPosition(CCPointMake(s.width/2, s.height/2))
    middle:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(middle)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPointMake(0, 1))
    right:setPosition(CCPointMake(s.width-100, s.height/2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(right)

	subtitleLabel:setString("ProgressTo Bar Mid")
	return layer
end

------------------------------------
--  SpriteProgressBarTintAndFade
------------------------------------
local function SpriteProgressBarTintAndFade()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local to = CCProgressTo:create(6, 100)
	local array = CCArray:create()
	array:addObject(CCTintTo:create(1, 255, 0, 0))
	array:addObject(CCTintTo:create(1, 0, 255, 0))
	array:addObject(CCTintTo:create(1, 0, 0, 255))
    local tint = CCSequence:create(array)
    local fade = CCSequence:createWithTwoActions(
		CCFadeTo:create(1.0, 0),
		CCFadeTo:create(1.0, 255))

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPointMake(1, 0))
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
    left:runAction(CCRepeatForever:create(CCSequence:create(array)))
	layer:addChild(left)

    left:addChild(CCLabelTTF:create("Tint", "Marker Felt", 20.0))

    local middle = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    middle:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(CCPointMake(1, 1))
    middle:setPosition(CCPointMake(s.width / 2, s.height / 2))
    middle:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))

    local fade2 = CCSequence:createWithTwoActions(
		CCFadeTo:create(1.0, 0),
		CCFadeTo:create(1.0, 255))
    middle:runAction(CCRepeatForever:create(fade2))
	layer:addChild(middle)

    middle:addChild(CCLabelTTF:create("Fade", "Marker Felt", 20.0))

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPointMake(0, 1))
    right:setPosition(CCPointMake(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
    right:runAction(CCRepeatForever:create(CCSequence:create(array)))
    right:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
		CCFadeTo:create(1.0, 0),
		CCFadeTo:create(1.0, 255))))
	layer:addChild(right)

    right:addChild(CCLabelTTF:create("Tint and Fade", "Marker Felt", 20.0))

	subtitleLabel:setString("ProgressTo Bar Mid")
	return layer
end

------------------------------------
--  SpriteProgressWithSpriteFrame
------------------------------------
local function SpriteProgressWithSpriteFrame()
	local layer = CCLayer:create()
	initWithLayer(layer)

	local to = CCProgressTo:create(6, 100)

    CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile("zwoptex/grossini.plist")

    local left = CCProgressTimer:create(CCSprite:createWithSpriteFrameName("grossini_dance_01.png"))
    left:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPointMake(1, 0))
    left:setPosition(CCPointMake(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
	layer:addChild(left)

    local middle = CCProgressTimer:create(CCSprite:createWithSpriteFrameName("grossini_dance_02.png"))
    middle:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(CCPointMake(1, 1))
    middle:setPosition(CCPointMake(s.width / 2, s.height / 2))
    middle:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
	layer:addChild(middle)

    local right = CCProgressTimer:create(CCSprite:createWithSpriteFrameName("grossini_dance_03.png"))
    right:setType(kCCProgressTimerTypeRadial)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPointMake(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPointMake(0, 1))
    right:setPosition(CCPointMake(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
	layer:addChild(right)

	subtitleLabel:setString("Progress With Sprite Frame")
	return layer
end

------------------------------------
-- Entrance
------------------------------------
function CreateActionProgressLayer()
	local layer = nil

	if SceneIdx == 0 then
		layer = SpriteProgressToRadial()
	elseif SceneIdx == 1 then
		layer = SpriteProgressToHorizontal()
	elseif SceneIdx == 2 then
		layer = SpriteProgressToVertical()
	elseif SceneIdx == 3 then
		layer = SpriteProgressToRadialMidpointChanged()
	elseif SceneIdx == 4 then
		layer = SpriteProgressBarVarious()
	elseif SceneIdx == 5 then
		layer = SpriteProgressBarTintAndFade()
	elseif SceneIdx == 6 then
		layer = SpriteProgressWithSpriteFrame()
	end

	return layer
end

function ProgressActionsTest()
	cclog("ProgressActionsTest")
	local scene = CCScene:create()

	SceneIdx = -1
	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end
