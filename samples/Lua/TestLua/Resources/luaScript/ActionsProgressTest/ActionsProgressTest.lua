
local s = CCDirector:getInstance():getWinSize()

------------------------------------
--  SpriteProgressToRadial
------------------------------------
local function SpriteProgressToRadial()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local to1 = CCProgressTo:create(2, 100)
    local to2 = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeRadial)
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(to1))
	layer:addChild(left)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathBlock))
    right:setType(kCCProgressTimerTypeRadial)
    -- Makes the ridial CCW
    right:setReverseProgress(true)
    right:setPosition(CCPoint(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(to2))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Radial")
	return layer
end

------------------------------------
--  SpriteProgressToHorizontal
------------------------------------
local function SpriteProgressToHorizontal()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local to1 = CCProgressTo:create(2, 100)
    local to2 = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the left since the midpoint is 0 for the x
    left:setMidpoint(CCPoint(0, 0))
    -- Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left:setBarChangeRate(CCPoint(1, 0))
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(to1))
	layer:addChild(left)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the left since the midpoint is 1 for the x
    right:setMidpoint(CCPoint(1, 0))
    -- Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right:setBarChangeRate(CCPoint(1, 0))
    right:setPosition(CCPoint(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(to2))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Horizontal")
	return layer
end

------------------------------------
--  SpriteProgressToVertical
------------------------------------
local function SpriteProgressToVertical()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local to1 = CCProgressTo:create(2, 100)
    local to2 = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPoint(0,0))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPoint(0, 1))
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(to1))
	layer:addChild(left)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPoint(0, 1))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPoint(0, 1))
    right:setPosition(CCPoint(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(to2))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Vertical")
	return layer
end

------------------------------------
--  SpriteProgressToRadialMidpointChanged
------------------------------------
local function SpriteProgressToRadialMidpointChanged()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local action = CCProgressTo:create(2, 100)

	-- Our image on the left should be a radial progress indicator, clockwise
    local left = CCProgressTimer:create(CCSprite:create(s_pPathBlock))
    left:setType(kCCProgressTimerTypeRadial)
    left:setMidpoint(CCPoint(0.25, 0.75))
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(left)

	-- Our image on the left should be a radial progress indicator, counter clockwise
    local right = CCProgressTimer:create(CCSprite:create(s_pPathBlock))
    right:setType(kCCProgressTimerTypeRadial)
    right:setMidpoint(CCPoint(0.75, 0.25))

	--[[
	   Note the reverse property (default=NO) is only added to the right image. That's how
       we get a counter clockwise progress.
	]]
    right:setPosition(CCPoint(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
    layer:addChild(right)

	Helper.subtitleLabel:setString("Radial w/ Different Midpoints")
	return layer
end

------------------------------------
--  SpriteProgressBarVarious
------------------------------------
local function SpriteProgressBarVarious()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local to = CCProgressTo:create(2, 100)

    local left = CCProgressTimer:create(CCSprite:create(s_pPathSister1))
    left:setType(kCCProgressTimerTypeBar)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPoint(1, 0))
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(left)

    local middle = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    middle:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(CCPoint(1, 1))
    middle:setPosition(CCPoint(s.width/2, s.height/2))
    middle:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(middle)

    local right = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    right:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPoint(0, 1))
    right:setPosition(CCPoint(s.width-100, s.height/2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(2, 100)))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Bar Mid")
	return layer
end

------------------------------------
--  SpriteProgressBarTintAndFade
------------------------------------
local function SpriteProgressBarTintAndFade()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

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
    left:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPoint(1, 0))
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
    left:runAction(CCRepeatForever:create(CCSequence:create(array)))
	layer:addChild(left)

    left:addChild(CCLabelTTF:create("Tint", "Marker Felt", 20.0))

    local middle = CCProgressTimer:create(CCSprite:create(s_pPathSister2))
    middle:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(CCPoint(1, 1))
    middle:setPosition(CCPoint(s.width / 2, s.height / 2))
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
    right:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPoint(0, 1))
    right:setPosition(CCPoint(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
    right:runAction(CCRepeatForever:create(CCSequence:create(array)))
    right:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(
		CCFadeTo:create(1.0, 0),
		CCFadeTo:create(1.0, 255))))
	layer:addChild(right)

    right:addChild(CCLabelTTF:create("Tint and Fade", "Marker Felt", 20.0))

	Helper.subtitleLabel:setString("ProgressTo Bar Mid")
	return layer
end

------------------------------------
--  SpriteProgressWithSpriteFrame
------------------------------------
local function SpriteProgressWithSpriteFrame()
	local layer = CCLayer:create()
	Helper.initWithLayer(layer)

	local to = CCProgressTo:create(6, 100)

    CCSpriteFrameCache:getInstance():addSpriteFramesWithFile("zwoptex/grossini.plist")

    local left = CCProgressTimer:create(CCSprite:createWithSpriteFrameName("grossini_dance_01.png"))
    left:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(CCPoint(1, 0))
    left:setPosition(CCPoint(100, s.height / 2))
    left:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
	layer:addChild(left)

    local middle = CCProgressTimer:create(CCSprite:createWithSpriteFrameName("grossini_dance_02.png"))
    middle:setType(kCCProgressTimerTypeBar)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(CCPoint(1, 1))
    middle:setPosition(CCPoint(s.width / 2, s.height / 2))
    middle:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
	layer:addChild(middle)

    local right = CCProgressTimer:create(CCSprite:createWithSpriteFrameName("grossini_dance_03.png"))
    right:setType(kCCProgressTimerTypeRadial)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(CCPoint(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(CCPoint(0, 1))
    right:setPosition(CCPoint(s.width - 100, s.height / 2))
    right:runAction(CCRepeatForever:create(CCProgressTo:create(6, 100)))
	layer:addChild(right)

	Helper.subtitleLabel:setString("Progress With Sprite Frame")
	return layer
end

function ProgressActionsTest()
	local scene = CCScene:create()

    Helper.createFunctionTable = {
        SpriteProgressToRadial,
        SpriteProgressToHorizontal,
        SpriteProgressToVertical,
        SpriteProgressToRadialMidpointChanged,
        SpriteProgressBarVarious,
        SpriteProgressBarTintAndFade,
        SpriteProgressWithSpriteFrame
    }

	scene:addChild(SpriteProgressToRadial())
	scene:addChild(CreateBackMenuItem())

	CCDirector:getInstance():replaceScene(scene)
end
