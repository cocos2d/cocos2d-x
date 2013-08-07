local kTagAction1 = 1
local kTagAction2 = 2
local kTagSlider = 1

local s = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()

local function createSimpleMoveBy()
    return CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
end

local function createSimpleDelayTime()
    return CCDelayTime:create(0.25)
end

local function positionForTwo()
	grossini:setPosition(CCPointMake(60, s.height * 1 / 5))
    tamara:setPosition(CCPointMake(60, s.height * 4 / 5))
    kathia:setVisible(false)
end

local function getBaseLayer()
	local layer = CCLayer:create()

	grossini = CCSprite:create(s_pPathGrossini)
    tamara = CCSprite:create(s_pPathSister1)
    kathia = CCSprite:create(s_pPathSister2)

    layer:addChild(grossini, 3)
    layer:addChild(kathia, 2)
    layer:addChild(tamara, 1)

    grossini:setPosition(CCPointMake(60, s.height * 1 / 5))
    kathia:setPosition(CCPointMake(60, s.height * 2.5 / 5))
    tamara:setPosition(CCPointMake(60, s.height * 4 / 5))

	Helper.initWithLayer(layer)

	return layer
end

-----------------------------------
--  SpriteEase
-----------------------------------
local SpriteEase_entry = nil

local function testStopAction(dt)
	scheduler:unscheduleScriptEntry(SpriteEase_entry)
    tamara:stopActionByTag(1)
    kathia:stopActionByTag(1)
    grossini:stopActionByTag(1)
end

local function SpriteEase_onEnterOrExit(tag)
	if tag == "enter" then
		SpriteEase_entry = scheduler:scheduleScriptFunc(testStopAction, 6.25, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(SpriteEase_entry)
	end
end

local function SpriteEase()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease_in = CCEaseIn:create(createSimpleMoveBy(), 2.5)
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseOut:create(createSimpleMoveBy(), 2.5)
    local move_ease_out_back = move_ease_out:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    local a2 = grossini:runAction(CCRepeatForever:create(seq1))
    a2:setTag(1)
    local a1 = tamara:runAction(CCRepeatForever:create(seq2))
    a1:setTag(1)
    local a = kathia:runAction(CCRepeatForever:create(seq3))
    a:setTag(1)

	layer:registerScriptHandler(SpriteEase_onEnterOrExit)

	Helper.titleLabel:setString("EaseIn - EaseOut - Stop")
	return layer
end

-----------------------------------
--	SpriteEaseInOut
-----------------------------------
local function SpriteEaseInOut()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()

    local move_ease_inout1 = CCEaseInOut:create(createSimpleMoveBy(), 0.65)
    local move_ease_inout_back1 = move_ease_inout1:reverse()

    local move_ease_inout2 = CCEaseInOut:create(createSimpleMoveBy(), 1.35)
    local move_ease_inout_back2 = move_ease_inout2:reverse()

    local move_ease_inout3 = CCEaseInOut:create(createSimpleMoveBy(), 1.0)
    local move_ease_inout_back3 = move_ease_inout3:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move_ease_inout1)
	arr1:addObject(delay)
	arr1:addObject(move_ease_inout_back1)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_inout2)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_inout_back2)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_inout3)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_inout_back3)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    tamara:runAction(CCRepeatForever:create(seq1))
    kathia:runAction(CCRepeatForever:create(seq2))
    grossini:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("EaseInOut and rates")
	return layer
end

-----------------------------------
--	SpriteEaseExponential
-----------------------------------
local function SpriteEaseExponential()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease_in = CCEaseExponentialIn:create(createSimpleMoveBy())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseExponentialOut:create(createSimpleMoveBy())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)

	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)

	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_in_back)

	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)

	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_out_back)

	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("ExpIn - ExpOut actions")
	return layer
end

-----------------------------------
--	SpriteEaseExponentialInOut
-----------------------------------
local function SpriteEaseExponentialInOut()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease = CCEaseExponentialInOut:create(createSimpleMoveBy())
    local move_ease_back = move_ease:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)

	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)

	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_back)

	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	Helper.titleLabel:setString("EaseExponentialInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseSine
-----------------------------------
local function SpriteEaseSine()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease_in = CCEaseSineIn:create(createSimpleMoveBy())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseSineOut:create(createSimpleMoveBy())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("EaseSineIn - EaseSineOut")
	return layer
end

-----------------------------------
--	SpriteEaseSineInOut
-----------------------------------
local function SpriteEaseSineInOut()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease = CCEaseSineInOut:create(createSimpleMoveBy())
    local move_ease_back = move_ease:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	Helper.titleLabel:setString("EaseSineInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseElastic
-----------------------------------
local function SpriteEaseElastic()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease_in = CCEaseElasticIn:create(createSimpleMoveBy())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseElasticOut:create(createSimpleMoveBy())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("Elastic In - Out actions")
	return layer
end

-----------------------------------
--	SpriteEaseElasticInOut
-----------------------------------
local function SpriteEaseElasticInOut()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()

    local move_ease_inout1 = CCEaseElasticInOut:create(createSimpleMoveBy(), 0.3)
    local move_ease_inout_back1 = move_ease_inout1:reverse()

    local move_ease_inout2 = CCEaseElasticInOut:create(createSimpleMoveBy(), 0.45)
    local move_ease_inout_back2 = move_ease_inout2:reverse()

    local move_ease_inout3 = CCEaseElasticInOut:create(createSimpleMoveBy(), 0.6)
    local move_ease_inout_back3 = move_ease_inout3:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move_ease_inout1)
	arr1:addObject(delay)
	arr1:addObject(move_ease_inout_back1)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_inout2)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_inout_back2)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_inout3)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_inout_back3)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    tamara:runAction(CCRepeatForever:create(seq1))
    kathia:runAction(CCRepeatForever:create(seq2))
    grossini:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("EaseElasticInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseBounce
-----------------------------------
local function SpriteEaseBounce()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease_in = CCEaseBounceIn:create(createSimpleMoveBy())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseBounceOut:create(createSimpleMoveBy())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("Bounce In - Out actions")
	return layer
end

-----------------------------------
--	SpriteEaseBounceInOut
-----------------------------------
local function SpriteEaseBounceInOut()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease = CCEaseBounceInOut:create(createSimpleMoveBy())
    local move_ease_back = move_ease:reverse()

    local delay = createSimpleDelayTime()

    local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	Helper.titleLabel:setString("EaseBounceInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseBack
-----------------------------------
local function SpriteEaseBack()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease_in = CCEaseBackIn:create(createSimpleMoveBy())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseBackOut:create(createSimpleMoveBy())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(createSimpleDelayTime())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(createSimpleDelayTime())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	Helper.titleLabel:setString("Back In - Out actions")
	return layer
end

-----------------------------------
--	SpriteEaseBackInOut
-----------------------------------
local function SpriteEaseBackInOut()
	local layer = getBaseLayer()

	local move = createSimpleMoveBy()
    local move_back = move:reverse()

    local move_ease = CCEaseBackInOut:create(createSimpleMoveBy())
    local move_ease_back = move_ease:reverse()

    local delay = createSimpleDelayTime()

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(createSimpleDelayTime())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(createSimpleDelayTime())
	arr2:addObject(move_ease_back)
	arr2:addObject(createSimpleDelayTime())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	Helper.titleLabel:setString("EaseBackInOut action")
	return layer
end

-----------------------------------
--	SpeedTest
-----------------------------------
local SpeedTest_entry = nil
local SpeedTest_action1 = nil
local SpeedTest_action2 = nil
local SpeedTest_action3 = nil

local function altertime(dt)
    SpeedTest_action1:setSpeed(math.random() * 2)
    SpeedTest_action2:setSpeed(math.random() * 2)
    SpeedTest_action3:setSpeed(math.random() * 2)
end

local function SpeedTest_onEnterOrExit(tag)
	if tag == "enter" then
		SpeedTest_entry = scheduler:scheduleScriptFunc(altertime, 1.0, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(SpeedTest_entry)
	end
end

local function SpeedTest()
	local layer = getBaseLayer()

	local jump1 = CCJumpBy:create(4, CCPointMake(- s.width + 80, 0), 100, 4)
    local jump2 = jump1:reverse()
    local rot1 = CCRotateBy:create(4, 360 * 2)
    local rot2 = rot1:reverse()

    local seq3_1 = CCSequence:createWithTwoActions(jump2, jump1)
    local seq3_2 = CCSequence:createWithTwoActions(rot1, rot2)

    local spawn = CCSpawn:createWithTwoActions(seq3_1, seq3_2)
    SpeedTest_action1 = CCSpeed:create(CCRepeatForever:create(spawn), 1.0)

	local spawn2 = tolua.cast(spawn:copy():autorelease(), "CCSpawn")
    SpeedTest_action2 = CCSpeed:create(CCRepeatForever:create(spawn2), 1.0)

	local spawn3 = tolua.cast(spawn:copy():autorelease(), "CCSpawn")
	SpeedTest_action3 = CCSpeed:create(CCRepeatForever:create(spawn3), 1.0)

    grossini:runAction(SpeedTest_action2)
    tamara:runAction(SpeedTest_action3)
    kathia:runAction(SpeedTest_action1)

	layer:registerScriptHandler(SpeedTest_onEnterOrExit)

	Helper.titleLabel:setString("Speed action")
	return layer
end

function EaseActionsTest()
	local scene = CCScene:create()
	cclog("EaseActionsTest")

	Helper.createFunctionTable = {
		SpriteEase,
		SpriteEaseInOut,
		SpriteEaseExponential,
		SpriteEaseExponentialInOut,
		SpriteEaseSine,
		SpriteEaseSineInOut,
		SpriteEaseElastic,
		SpriteEaseElasticInOut,
		SpriteEaseBounce,	
		SpriteEaseBounceInOut,	
		SpriteEaseBack,	
		SpriteEaseBackInOut,
		SpeedTest
    }

	scene:addChild(SpriteEase())
	scene:addChild(CreateBackMenuItem())

	return scene
end
