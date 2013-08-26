
local s = cc.Director:getInstance():getWinSize()

------------------------------------
--  SpriteProgressToRadial
------------------------------------
local function SpriteProgressToRadial()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local to1 = cc.ProgressTo:create(2, 100)
    local to2 = cc.ProgressTo:create(2, 100)

    local left = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister1))
    left:setType(cc.PROGRESS_TIMER_TYPE_RADIAL)
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(to1))
	layer:addChild(left)

    local right = cc.ProgressTimer:create(cc.Sprite:create(s_pPathBlock))
    right:setType(cc.PROGRESS_TIMER_TYPE_RADIAL)
    -- Makes the ridial CCW
    right:setReverseDirection(true)
    right:setPosition(cc.p(s.width - 100, s.height / 2))
    right:runAction(cc.RepeatForever:create(to2))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Radial")
	return layer
end

------------------------------------
--  SpriteProgressToHorizontal
------------------------------------
local function SpriteProgressToHorizontal()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local to1 = cc.ProgressTo:create(2, 100)
    local to2 = cc.ProgressTo:create(2, 100)

    local left = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister1))
    left:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the left since the midpoint is 0 for the x
    left:setMidpoint(cc.p(0, 0))
    -- Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    left:setBarChangeRate(cc.p(1, 0))
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(to1))
	layer:addChild(left)

    local right = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister2))
    right:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the left since the midpoint is 1 for the x
    right:setMidpoint(cc.p(1, 0))
    -- Setup for a horizontal bar since the bar change rate is 0 for y meaning no vertical change
    right:setBarChangeRate(cc.p(1, 0))
    right:setPosition(cc.p(s.width - 100, s.height / 2))
    right:runAction(cc.RepeatForever:create(to2))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Horizontal")
	return layer
end

------------------------------------
--  SpriteProgressToVertical
------------------------------------
local function SpriteProgressToVertical()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local to1 = cc.ProgressTo:create(2, 100)
    local to2 = cc.ProgressTo:create(2, 100)

    local left = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister1))
    left:setType(cc.PROGRESS_TIMER_TYPE_BAR)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(cc.p(0,0))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(cc.p(0, 1))
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(to1))
	layer:addChild(left)

    local right = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister2))
    right:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(cc.p(0, 1))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(cc.p(0, 1))
    right:setPosition(cc.p(s.width - 100, s.height / 2))
    right:runAction(cc.RepeatForever:create(to2))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Vertical")
	return layer
end

------------------------------------
--  SpriteProgressToRadialMidpointChanged
------------------------------------
local function SpriteProgressToRadialMidpointChanged()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local action = cc.ProgressTo:create(2, 100)

	-- Our image on the left should be a radial progress indicator, clockwise
    local left = cc.ProgressTimer:create(cc.Sprite:create(s_pPathBlock))
    left:setType(cc.PROGRESS_TIMER_TYPE_RADIAL)
    left:setMidpoint(cc.p(0.25, 0.75))
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(cc.ProgressTo:create(2, 100)))
	layer:addChild(left)

	-- Our image on the left should be a radial progress indicator, counter clockwise
    local right = cc.ProgressTimer:create(cc.Sprite:create(s_pPathBlock))
    right:setType(cc.PROGRESS_TIMER_TYPE_RADIAL)
    right:setMidpoint(cc.p(0.75, 0.25))

	--[[
	   Note the reverse property (default=NO) is only added to the right image. That's how
       we get a counter clockwise progress.
	]]
    right:setPosition(cc.p(s.width - 100, s.height / 2))
    right:runAction(cc.RepeatForever:create(cc.ProgressTo:create(2, 100)))
    layer:addChild(right)

	Helper.subtitleLabel:setString("Radial w/ Different Midpoints")
	return layer
end

------------------------------------
--  SpriteProgressBarVarious
------------------------------------
local function SpriteProgressBarVarious()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local to = cc.ProgressTo:create(2, 100)

    local left = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister1))
    left:setType(cc.PROGRESS_TIMER_TYPE_BAR)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(cc.p(1, 0))
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(cc.ProgressTo:create(2, 100)))
	layer:addChild(left)

    local middle = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister2))
    middle:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(cc.p(1, 1))
    middle:setPosition(cc.p(s.width/2, s.height/2))
    middle:runAction(cc.RepeatForever:create(cc.ProgressTo:create(2, 100)))
	layer:addChild(middle)

    local right = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister2))
    right:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(cc.p(0, 1))
    right:setPosition(cc.p(s.width-100, s.height/2))
    right:runAction(cc.RepeatForever:create(cc.ProgressTo:create(2, 100)))
	layer:addChild(right)

	Helper.subtitleLabel:setString("ProgressTo Bar Mid")
	return layer
end

------------------------------------
--  SpriteProgressBarTintAndFade
------------------------------------
local function SpriteProgressBarTintAndFade()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local to = cc.ProgressTo:create(6, 100)
    local tint = cc.Sequence:create(cc.TintTo:create(1, 255, 0, 0), cc.TintTo:create(1, 0, 255, 0), cc.TintTo:create(1, 0, 0, 255))
    local fade = cc.Sequence:create(cc.FadeTo:create(1.0, 0),cc.FadeTo:create(1.0, 255))
    local left = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister1))
    left:setType(cc.PROGRESS_TIMER_TYPE_BAR)

    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(cc.p(1, 0))
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(cc.ProgressTo:create(6, 100)))
    left:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.TintTo:create(1, 255, 0, 0), cc.TintTo:create(1, 0, 255, 0), cc.TintTo:create(1, 0, 0, 255))))
	layer:addChild(left)

    left:addChild(cc.LabelTTF:create("Tint", "Marker Felt", 20.0))

    local middle = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister2))
    middle:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(cc.p(1, 1))
    middle:setPosition(cc.p(s.width / 2, s.height / 2))
    middle:runAction(cc.RepeatForever:create(cc.ProgressTo:create(6, 100)))

    local fade2 = cc.Sequence:create(cc.FadeTo:create(1.0, 0), cc.FadeTo:create(1.0, 255))
    middle:runAction(cc.RepeatForever:create(fade2))
	layer:addChild(middle)

    middle:addChild(cc.LabelTTF:create("Fade", "Marker Felt", 20.0))

    local right = cc.ProgressTimer:create(cc.Sprite:create(s_pPathSister2))
    right:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(cc.p(0, 1))
    right:setPosition(cc.p(s.width - 100, s.height / 2))
    right:runAction(cc.RepeatForever:create(cc.ProgressTo:create(6, 100)))
    right:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.TintTo:create(1, 255, 0, 0), cc.TintTo:create(1, 0, 255, 0), cc.TintTo:create(1, 0, 0, 255))))
    right:runAction(cc.RepeatForever:create(cc.Sequence:create(cc.FadeTo:create(1.0, 0), cc.FadeTo:create(1.0, 255))))
	layer:addChild(right)

    right:addChild(cc.LabelTTF:create("Tint and Fade", "Marker Felt", 20.0))

	Helper.subtitleLabel:setString("ProgressTo Bar Mid")
	return layer
end

------------------------------------
--  SpriteProgressWithSpriteFrame
------------------------------------
local function SpriteProgressWithSpriteFrame()
	local layer = cc.Layer:create()
	Helper.initWithLayer(layer)

	local to = cc.ProgressTo:create(6, 100)

    cc.SpriteFrameCache:getInstance():addSpriteFrames("zwoptex/grossini.plist")

    local left = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("grossini_dance_01.png"))
    left:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    left:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    left:setBarChangeRate(cc.p(1, 0))
    left:setPosition(cc.p(100, s.height / 2))
    left:runAction(cc.RepeatForever:create(cc.ProgressTo:create(6, 100)))
	layer:addChild(left)

    local middle = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("grossini_dance_02.png"))
    middle:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    middle:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    middle:setBarChangeRate(cc.p(1, 1))
    middle:setPosition(cc.p(s.width / 2, s.height / 2))
    middle:runAction(cc.RepeatForever:create(cc.ProgressTo:create(6, 100)))
	layer:addChild(middle)

    local right = cc.ProgressTimer:create(cc.Sprite:createWithSpriteFrameName("grossini_dance_03.png"))
    right:setType(cc.PROGRESS_TIMER_TYPE_BAR)
    -- Setup for a bar starting from the bottom since the midpoint is 0 for the y
    right:setMidpoint(cc.p(0.5, 0.5))
    -- Setup for a vertical bar since the bar change rate is 0 for x meaning no horizontal change
    right:setBarChangeRate(cc.p(0, 1))
    right:setPosition(cc.p(s.width - 100, s.height / 2))
    right:runAction(cc.RepeatForever:create(cc.ProgressTo:create(6, 100)))
	layer:addChild(right)

	Helper.subtitleLabel:setString("Progress With Sprite Frame")
	return layer
end

function ProgressActionsTest()
	local scene = cc.Scene:create()

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

	cc.Director:getInstance():replaceScene(scene)
end
