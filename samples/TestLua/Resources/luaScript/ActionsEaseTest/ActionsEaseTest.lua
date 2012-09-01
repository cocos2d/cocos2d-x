
local SceneIdx = -1
local MAX_LAYER = 13

local kTagAction1 = 1
local kTagAction2 = 2
local kTagSlider = 1

local titleLabel = nil
local s = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()

local function backAction()
	SceneIdx = SceneIdx - 1
    if SceneIdx < 0 then
        SceneIdx = SceneIdx + MAX_LAYER
    end

    return CreateActionsEaseLayer()
end

local function restartAction()
	return CreateActionsEaseLayer()
end

local function nextAction()
	SceneIdx = SceneIdx + 1
    SceneIdx = math.mod(SceneIdx, MAX_LAYER)

    return CreateActionsEaseLayer()
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

	titleLabel = CCLabelTTF:create("", "Arial", 32)
    layer:addChild(titleLabel)
    titleLabel:setPosition(s.width / 2, s.height - 50)

    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
	item1:registerScriptHandler(backCallback)
	item2:registerScriptHandler(restartCallback)
	item3:registerScriptHandler(nextCallback)

    local menu = CCMenu:create()
	menu:addChild(item1)
	menu:addChild(item2)
	menu:addChild(item3)

    menu:setPosition(CCPointMake(0, 0))
    item1:setPosition(CCPointMake(s.width/2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(s.width/2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(s.width/2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    layer:addChild(menu, 1)

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
	if tag == 0 then
		SpriteEase_entry = scheduler:scheduleScriptFunc(testStopAction, 6.25, false)
	elseif tag == 1 then
		scheduler:unscheduleScriptEntry(SpriteEase_entry)
	end
end

local function SpriteEase()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease_in = CCEaseIn:create(move:copy():autorelease(), 2.5)
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseOut:create(move:copy():autorelease(), 2.5)
    local move_ease_out_back = move_ease_out:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    local a2 = grossini:runAction(CCRepeatForever:create(seq1))
    a2:setTag(1)
    local a1 = tamara:runAction(CCRepeatForever:create(seq2))
    a1:setTag(1)
    local a = kathia:runAction(CCRepeatForever:create(seq3))
    a:setTag(1)

	layer:registerScriptHandler(SpriteEase_onEnterOrExit)

	titleLabel:setString("EaseIn - EaseOut - Stop")
	return layer
end

-----------------------------------
--	SpriteEaseInOut
-----------------------------------
local function SpriteEaseInOut()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))

    local move_ease_inout1 = CCEaseInOut:create(move:copy():autorelease(), 0.65)
    local move_ease_inout_back1 = move_ease_inout1:reverse()

    local move_ease_inout2 = CCEaseInOut:create(move:copy():autorelease(), 1.35)
    local move_ease_inout_back2 = move_ease_inout2:reverse()

    local move_ease_inout3 = CCEaseInOut:create(move:copy():autorelease(), 1.0)
    local move_ease_inout_back3 = move_ease_inout3:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move_ease_inout1)
	arr1:addObject(delay)
	arr1:addObject(move_ease_inout_back1)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_inout2)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_inout_back2)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_inout3)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_inout_back3)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    tamara:runAction(CCRepeatForever:create(seq1))
    kathia:runAction(CCRepeatForever:create(seq2))
    grossini:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("EaseInOut and rates")
	return layer
end

-----------------------------------
--	SpriteEaseExponential
-----------------------------------
local function SpriteEaseExponential()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease_in = CCEaseExponentialIn:create(move:copy():autorelease())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseExponentialOut:create(move:copy():autorelease())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("ExpIn - ExpOut actions")
	return layer
end

-----------------------------------
--	SpriteEaseExponentialInOut
-----------------------------------
local function SpriteEaseExponentialInOut()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease = CCEaseExponentialInOut:create(move:copy():autorelease())
    local move_ease_back = move_ease:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	titleLabel:setString("EaseExponentialInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseSine
-----------------------------------
local function SpriteEaseSine()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease_in = CCEaseSineIn:create(move:copy():autorelease())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseSineOut:create(move:copy():autorelease())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("EaseSineIn - EaseSineOut")
	return layer
end

-----------------------------------
--	SpriteEaseSineInOut
-----------------------------------
local function SpriteEaseSineInOut()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease = CCEaseSineInOut:create(move:copy():autorelease())
    local move_ease_back = move_ease:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	titleLabel:setString("EaseSineInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseElastic
-----------------------------------
local function SpriteEaseElastic()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease_in = CCEaseElasticIn:create(move:copy():autorelease())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseElasticOut:create(move:copy():autorelease())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("Elastic In - Out actions")
	return layer
end

-----------------------------------
--	SpriteEaseElasticInOut
-----------------------------------
local function SpriteEaseElasticInOut()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))

    local move_ease_inout1 = CCEaseElasticInOut:create(move:copy():autorelease(), 0.3)
    local move_ease_inout_back1 = move_ease_inout1:reverse()

    local move_ease_inout2 = CCEaseElasticInOut:create(move:copy():autorelease(), 0.45)
    local move_ease_inout_back2 = move_ease_inout2:reverse()

    local move_ease_inout3 = CCEaseElasticInOut:create(move:copy():autorelease(), 0.6)
    local move_ease_inout_back3 = move_ease_inout3:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move_ease_inout1)
	arr1:addObject(delay)
	arr1:addObject(move_ease_inout_back1)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_inout2)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_inout_back2)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_inout3)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_inout_back3)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    tamara:runAction(CCRepeatForever:create(seq1))
    kathia:runAction(CCRepeatForever:create(seq2))
    grossini:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("EaseElasticInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseBounce
-----------------------------------
local function SpriteEaseBounce()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease_in = CCEaseBounceIn:create(move:copy():autorelease())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseBounceOut:create(move:copy():autorelease())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("Bounce In - Out actions")
	return layer
end

-----------------------------------
--	SpriteEaseBounceInOut
-----------------------------------
local function SpriteEaseBounceInOut()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease = CCEaseBounceInOut:create(move:copy():autorelease())
    local move_ease_back = move_ease:reverse()

    local delay = CCDelayTime:create(0.25)

    local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	titleLabel:setString("EaseBounceInOut action")
	return layer
end

-----------------------------------
--	SpriteEaseBack
-----------------------------------
local function SpriteEaseBack()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease_in = CCEaseBackIn:create(move:copy():autorelease())
    local move_ease_in_back = move_ease_in:reverse()

    local move_ease_out = CCEaseBackOut:create(move:copy():autorelease())
    local move_ease_out_back = move_ease_out:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease_in)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_in_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

	local arr3 = CCArray:create()
	arr3:addObject(move_ease_out)
	arr3:addObject(delay:copy():autorelease())
	arr3:addObject(move_ease_out_back)
	arr3:addObject(delay:copy():autorelease())
    local seq3 = CCSequence:create(arr3)

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))
    kathia:runAction(CCRepeatForever:create(seq3))

	titleLabel:setString("Back In - Out actions")
	return layer
end

-----------------------------------
--	SpriteEaseBackInOut
-----------------------------------
local function SpriteEaseBackInOut()
	local layer = getBaseLayer()

	local move = CCMoveBy:create(3, CCPointMake(s.width - 130, 0))
    local move_back = move:reverse()

    local move_ease = CCEaseBackInOut:create(move:copy():autorelease())
    local move_ease_back = move_ease:reverse()

    local delay = CCDelayTime:create(0.25)

	local arr1 = CCArray:create()
	arr1:addObject(move)
	arr1:addObject(delay)
	arr1:addObject(move_back)
	arr1:addObject(delay:copy():autorelease())
    local seq1 = CCSequence:create(arr1)

	local arr2 = CCArray:create()
	arr2:addObject(move_ease)
	arr2:addObject(delay:copy():autorelease())
	arr2:addObject(move_ease_back)
	arr2:addObject(delay:copy():autorelease())
    local seq2 = CCSequence:create(arr2)

    positionForTwo()

    grossini:runAction(CCRepeatForever:create(seq1))
    tamara:runAction(CCRepeatForever:create(seq2))

	titleLabel:setString("EaseBackInOut action")
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
	if tag == 0 then
		SpeedTest_entry = scheduler:scheduleScriptFunc(altertime, 1.0, false)
	elseif tag == 1 then
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

	local spawn2 = spawn:copy():autorelease()
    SpeedTest_action2 = CCSpeed:create(CCRepeatForever:create(spawn2), 1.0)

	local spawn3 = spawn:copy():autorelease()
	SpeedTest_action3 = CCSpeed:create(CCRepeatForever:create(spawn3), 1.0)

    grossini:runAction(SpeedTest_action2)
    tamara:runAction(SpeedTest_action3)
    kathia:runAction(SpeedTest_action1)

	layer:registerScriptHandler(SpeedTest_onEnterOrExit)

	titleLabel:setString("Speed action")
	return layer
end

-----------------------------------
--  Actions Ease Test
-----------------------------------
function CreateActionsEaseLayer()
	if SceneIdx == 0 then
		return SpriteEase()
	elseif SceneIdx == 1  then
		return SpriteEaseInOut()
	elseif SceneIdx == 2  then
		return SpriteEaseExponential()
	elseif SceneIdx == 3  then
		return SpriteEaseExponentialInOut()
	elseif SceneIdx == 4  then
		return SpriteEaseSine()
	elseif SceneIdx == 5  then
		return SpriteEaseSineInOut()
	elseif SceneIdx == 6  then
		return SpriteEaseElastic()
	elseif SceneIdx == 7  then
		return SpriteEaseElasticInOut()
	elseif SceneIdx == 8  then
		return SpriteEaseBounce()
	elseif SceneIdx == 9  then
		return SpriteEaseBounceInOut()
	elseif SceneIdx == 10 then
		return SpriteEaseBack()
	elseif SceneIdx == 11 then
		return SpriteEaseBackInOut()
	elseif SceneIdx == 12 then
		return SpeedTest()
	end
end

function EaseActionsTest()
	local scene = CCScene:create()

	SceneIdx = -1
	scene:addChild(nextAction())
	scene:addChild(CreateBackMenuItem())

	return scene
end
