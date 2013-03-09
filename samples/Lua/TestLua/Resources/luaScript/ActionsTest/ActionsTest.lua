require "luaScript/ActionsTest/ActionsName"


local ActionIdx = -1
local size = CCDirector:sharedDirector():getWinSize()

local titleLabel    = nil
local subtitleLabel = nil

local function BackAction()
	ActionIdx = ActionIdx - 1
	if ActionIdx < 0 then
		ActionIdx = ActionIdx + Action_Table.ACTION_LAYER_COUNT
	end

	return CreateActionTestLayer()
end

local function RestartAction()
	return CreateActionTestLayer()
end

local function NextAction()
	ActionIdx = ActionIdx + 1
	ActionIdx = math.mod(ActionIdx, Action_Table.ACTION_LAYER_COUNT)

	return CreateActionTestLayer()
end

local function backCallback(sender)
	local scene = CCScene:create()

	scene:addChild(BackAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function restartCallback(sender)
	local scene = CCScene:create()

	scene:addChild(RestartAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function nextCallback(sender)
	local scene = CCScene:create()

	scene:addChild(NextAction())
	scene:addChild(CreateBackMenuItem())

	CCDirector:sharedDirector():replaceScene(scene)
end

local function initWithLayer(layer)
	grossini = CCSprite:create(s_pPathGrossini)
	tamara   = CCSprite:create(s_pPathSister1)
	kathia   = CCSprite:create(s_pPathSister2)

	layer:addChild(grossini, 1)
	layer:addChild(tamara, 2)
	layer:addChild(kathia, 3)

	grossini:setPosition(ccp(size.width / 2, size.height / 3))
	tamara:setPosition(ccp(size.width / 2, 2 * size.height / 3))
	kathia:setPosition(ccp(size.width / 2, size.height / 2))

	-- create title and subtitle
	titleLabel = CCLabelTTF:create("ActionsTest", "Arial", 18)
	titleLabel:setPosition(size.width/2, size.height - 30)
	subtitleLabel = CCLabelTTF:create("", "Thonburi", 22)
	subtitleLabel:setPosition(size.width / 2, size.height - 60)
	layer:addChild(titleLabel, 1)
	layer:addChild(subtitleLabel, 1)

	-- add menu
	local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
	local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
	local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
	item1:registerScriptTapHandler(backCallback)
	item2:registerScriptTapHandler(restartCallback)
	item3:registerScriptTapHandler(nextCallback)
	item1:setPosition(ccp(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
	item2:setPosition(ccp(size.width / 2, item2:getContentSize().height / 2))
	item3:setPosition(ccp(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))

	local menu = CCMenu:create()
	menu:addChild(item1)
	menu:addChild(item2)
	menu:addChild(item3)
	menu:setPosition(ccp(0, 0))
	layer:addChild(menu, 1)
end


local function centerSprites(numberOfSprites)
	if numberOfSprites == 0 then
		tamara:setVisible(false)
		kathia:setVisible(false)
		grossini:setVisible(false)
	elseif numberOfSprites == 1 then
		tamara:setVisible(false)
		kathia:setVisible(false)
		grossini:setPosition(ccp(size.width / 2, size.height / 2))
	elseif numberOfSprites == 2 then
		kathia:setPosition(ccp(size.width / 3, size.height / 2))
		tamara:setPosition(ccp(2 * size.width / 3, size.height / 2))
		grossini:setVisible(false)
	elseif numberOfSprites == 3 then
		grossini:setPosition(ccp(size.width / 2, size.height / 2))
		tamara:setPosition(ccp(size.width / 4, size.height / 2))
		kathia:setPosition(ccp(3 * size.width / 4, size.height / 2))
	end
end

local function alignSpritesLeft(numberOfSprites)
	if numberOfSprites == 1 then
		tamara:setVisible(false)
		kathia:setVisible(false)
		grossini:setPosition(ccp(60, size.height / 2))
	elseif numberOfSprites == 2 then
		kathia:setPosition(ccp(60, size.height / 3))
		tamara:setPosition(ccp(60, 2 * size.height / 3))
		grossini:setVisible(false)
	elseif numberOfSprites == 3 then
		grossini:setPosition(ccp(60, size.height / 2))
		tamara:setPosition(ccp(60, 2 * size.height / 3))
		kathia:setPosition(ccp(60, size.height / 3))
	end
end


--------------------------------------
-- ActionManual
--------------------------------------
local function ActionManual()
	local layer = CCLayer:create()
	initWithLayer(layer)

	tamara:setScaleX(2.5)
	tamara:setScaleY(-1.0)
	tamara:setPosition(ccp(100, 70))
	tamara:setOpacity(128)

	grossini:setRotation(120)
	grossini:setPosition(ccp(size.width / 2, size.height / 2))
	grossini:setColor(ccc3(255, 0, 0))

	kathia:setPosition(ccp(size.width - 100, size.height / 2))
	kathia:setColor(ccc3(0, 0, 255))

	subtitleLabel:setString("Manual Transformation")
	return layer
end

--------------------------------------
-- ActionMove
--------------------------------------
local function ActionMove()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)
	local actionBy = CCMoveBy:create(2, ccp(80, 80))
	local actionByBack = actionBy:reverse()

	tamara:runAction(CCMoveTo:create(2, ccp(size.width - 40, size.height - 40)))
	grossini:runAction(CCSequence:createWithTwoActions(actionBy, actionByBack))
	kathia:runAction(CCMoveTo:create(1, ccp(40, 40)))

	subtitleLabel:setString("MoveTo / MoveBy")
	return layer
end

--------------------------------------
-- ActionScale
--------------------------------------
local function ActionScale()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

	local actionTo = CCScaleTo:create(2.0, 0.5)
	local actionBy = CCScaleBy:create(2.0, 1.0, 10.0)
	local actionBy2 = CCScaleBy:create(2.0, 5.0, 1.0)

	grossini:runAction(actionTo)
	tamara:runAction(CCSequence:createWithTwoActions(actionBy, actionBy:reverse()))
	kathia:runAction(CCSequence:createWithTwoActions(actionBy2, actionBy2:reverse()))

	subtitleLabel:setString("ScaleTo / ScaleBy")
	return layer
end

--------------------------------------
-- ActionRotate
--------------------------------------
local function ActionRotate()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

    local actionTo = CCRotateTo:create( 2, 45)
    local actionTo2 = CCRotateTo:create( 2, -45)
    local actionTo0 = CCRotateTo:create(2 , 0)
    tamara:runAction(CCSequence:createWithTwoActions(actionTo, actionTo0))

    local actionBy = CCRotateBy:create(2 , 360)
    local actionByBack = actionBy:reverse()
    grossini:runAction(CCSequence:createWithTwoActions(actionBy, actionByBack))

    local action0Retain = CCRotateTo:create(2 , 0)

    kathia:runAction(CCSequence:createWithTwoActions(actionTo2, action0Retain))

	subtitleLabel:setString("RotateTo / RotateBy")
	return layer
end

--------------------------------------
-- ActionSkew
--------------------------------------
local function ActionSkew()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

    local actionTo = CCSkewTo:create(2, 37.2, -37.2)
    local actionToBack = CCSkewTo:create(2, 0, 0)
    local actionBy = CCSkewBy:create(2, 0.0, -90.0)
    local actionBy2 = CCSkewBy:create(2, 45.0, 45.0)
    local actionByBack = actionBy:reverse()

    tamara:runAction(CCSequence:createWithTwoActions(actionTo, actionToBack))
    grossini:runAction(CCSequence:createWithTwoActions(actionBy, actionByBack))
    kathia:runAction(CCSequence:createWithTwoActions(actionBy2, actionBy2:reverse()))

	subtitleLabel:setString("SkewTo / SkewBy")
	return layer
end

--ActionRotationalSkewVSStandardSkew
local function ActionRotationalSkewVSStandardSkew()

    local layer = CCLayer:create()
	initWithLayer(layer)

    tamara:removeFromParentAndCleanup(true);
    grossini:removeFromParentAndCleanup(true);
    kathia:removeFromParentAndCleanup(true);

    local s = CCDirector:sharedDirector():getWinSize();
    local boxSize = CCSizeMake(100.0, 100.0);
    local box = CCLayerColor:create(ccc4(255,255,0,255));
    box:setAnchorPoint(ccp(0.5,0.5));
    box:setContentSize( boxSize );
    box:ignoreAnchorPointForPosition(false);
    box:setPosition(ccp(s.width/2, s.height - 100 - box:getContentSize().height/2));
    layer:addChild(box);
    local label = CCLabelTTF:create("Standard cocos2d Skew", "Marker Felt", 16);
    label:setPosition(ccp(s.width/2, s.height - 100 + label:getContentSize().height));
    layer:addChild(label);
    local actionTo = CCSkewBy:create(2, 360, 0);
    local actionToBack = CCSkewBy:create(2, -360, 0);
    local seq = CCSequence:createWithTwoActions(actionTo, actionToBack)

    box:runAction(seq);

    box = CCLayerColor:create(ccc4(255,255,0,255));
    box:setAnchorPoint(ccp(0.5,0.5));
    box:setContentSize(boxSize);
    box:ignoreAnchorPointForPosition(false);
    box:setPosition(ccp(s.width/2, s.height - 250 - box:getContentSize().height/2));
    layer:addChild(box);
    label = CCLabelTTF:create("Rotational Skew", "Marker Felt", 16);
    label:setPosition(ccp(s.width/2, s.height - 250 + label:getContentSize().height/2));
    layer:addChild(label);
    local actionTo2 = CCRotateBy:create(2, 360);
    local actionToBack2 = CCRotateBy:create(2, -360);
    seq = CCSequence:createWithTwoActions(actionTo2, actionToBack2)
    box:runAction(seq);

    subtitleLabel:setString("Skew Comparison")
    return layer;
end

--------------------------------------
-- ActionSkewRotate
--------------------------------------
local function ActionSkewRotate()
	local layer = CCLayer:create()
	initWithLayer(layer)

	tamara:removeFromParentAndCleanup(true)
    grossini:removeFromParentAndCleanup(true)
    kathia:removeFromParentAndCleanup(true)

    local boxSize = CCSizeMake(100.0, 100.0)

    local box = CCLayerColor:create(ccc4(255, 255, 0, 255))
    box:setAnchorPoint(ccp(0, 0))
    box:setPosition(190, 110)
    box:setContentSize(boxSize)

	local markrside = 10.0
    local uL = CCLayerColor:create(ccc4(255, 0, 0, 255))
    box:addChild(uL)
    uL:setContentSize(CCSizeMake(markrside, markrside))
    uL:setPosition(0, boxSize.height - markrside)
    uL:setAnchorPoint(ccp(0, 0))

    local uR = CCLayerColor:create(ccc4(0, 0, 255, 255))
    box:addChild(uR)
    uR:setContentSize(CCSizeMake(markrside, markrside))
    uR:setPosition(boxSize.width - markrside, boxSize.height - markrside)
    uR:setAnchorPoint(ccp(0, 0))
    layer:addChild(box)

    local actionTo = CCSkewTo:create(2, 0, 2)
    local rotateTo = CCRotateTo:create(2, 61.0)
    local actionScaleTo = CCScaleTo:create(2, -0.44, 0.47)

    local actionScaleToBack = CCScaleTo:create(2, 1.0, 1.0)
    local rotateToBack = CCRotateTo:create(2, 0)
    local actionToBack = CCSkewTo:create(2, 0, 0)

    box:runAction(CCSequence:createWithTwoActions(actionTo, actionToBack))
    box:runAction(CCSequence:createWithTwoActions(rotateTo, rotateToBack))
    box:runAction(CCSequence:createWithTwoActions(actionScaleTo, actionScaleToBack))

	subtitleLabel:setString("Skew + Rotate + Scale")
	return layer
end

--------------------------------------
-- ActionJump
--------------------------------------
local function ActionJump()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

    local actionTo = CCJumpTo:create(2, ccp(300,300), 50, 4)
    local actionBy = CCJumpBy:create(2, ccp(300,0), 50, 4)
    local actionUp = CCJumpBy:create(2, ccp(0,0), 80, 4)
    local actionByBack = actionBy:reverse()

    tamara:runAction(actionTo)
    grossini:runAction(CCSequence:createWithTwoActions(actionBy, actionByBack))
    kathia:runAction(CCRepeatForever:create(actionUp))

	subtitleLabel:setString("JumpTo / JumpBy")
	return layer
end

--------------------------------------
-- ActionCardinalSpline
--------------------------------------
local function drawCardinalSpline(array)
	kmGLPushMatrix()
	kmGLTranslatef(50, 50, 0)
	ccDrawCardinalSpline(array, 0, 100)
	kmGLPopMatrix()

	kmGLPushMatrix()
	kmGLTranslatef(size.width / 2, 50, 0)
	ccDrawCardinalSpline(array, 1, 100)
	kmGLPopMatrix()
end

local function ActionCardinalSpline()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

	local array = CCPointArray:create(20)
	array:addControlPoint(ccp(0, 0))
	array:addControlPoint(ccp(size.width / 2 - 30, 0))
	array:addControlPoint(ccp(size.width / 2 - 30, size.height - 80))
	array:addControlPoint(ccp(0, size.height - 80))
	array:addControlPoint(ccp(0, 0))

	local action = CCCardinalSplineBy:create(3, array, 0)
	local reverse = action:reverse()
	local seq = CCSequence:createWithTwoActions(action, reverse)

	tamara:setPosition(ccp(50, 50))
	tamara:runAction(seq)

	local action2 = CCCardinalSplineBy:create(3, array, 1)
	local reverse2 = action2:reverse()
	local seq2 = CCSequence:createWithTwoActions(action2, reverse2)

	kathia:setPosition(ccp(size.width / 2, 50))
	kathia:runAction(seq2)

	drawCardinalSpline(array)

	titleLabel:setString("CardinalSplineBy / CardinalSplineAt")
	subtitleLabel:setString("Cardinal Spline paths.\nTesting different tensions for one array")
	return layer
end

--------------------------------------
-- ActionCatmullRom
--------------------------------------
local function drawCatmullRom(array1, array2)
	kmGLPushMatrix()
	kmGLTranslatef(50, 50, 0)
	ccDrawCatmullRom(array1, 50)
	kmGLPopMatrix()

	ccDrawCatmullRom(array2,50)
end

local function ActionCatmullRom()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

	tamara:setPosition(ccp(50, 50))

    local array = CCPointArray:create(20)
    array:addControlPoint(ccp(0, 0))
    array:addControlPoint(ccp(80, 80))
    array:addControlPoint(ccp(size.width - 80, 80))
    array:addControlPoint(ccp(size.width - 80, size.height - 80))
    array:addControlPoint(ccp(80, size.height - 80))
    array:addControlPoint(ccp(80, 80))
    array:addControlPoint(ccp(size.width / 2, size.height / 2))

    local action = CCCatmullRomBy:create(3, array)
    local reverse = action:reverse()
    local seq = CCSequence:createWithTwoActions(action, reverse)
	tamara:runAction(seq)

    local array2 = CCPointArray:create(20)
    array2:addControlPoint(ccp(size.width / 2, 30))
    array2:addControlPoint(ccp(size.width  -80, 30))
    array2:addControlPoint(ccp(size.width - 80, size.height - 80))
    array2:addControlPoint(ccp(size.width / 2, size.height - 80))
    array2:addControlPoint(ccp(size.width / 2, 30))

    local action2 = CCCatmullRomTo:create(3, array2)
    local reverse2 = action2:reverse()
    local seq2 = CCSequence:createWithTwoActions(action2, reverse2)
    kathia:runAction(seq2)

	drawCatmullRom(array, array2)

	titleLabel:setString("CatmullRomBy / CatmullRomTo")
	subtitleLabel:setString("Catmull Rom spline paths. Testing reverse too")
	return layer
end

--------------------------------------
-- ActionBezier
--------------------------------------
local function ActionBezier()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

	-- sprite 1
    local bezier = ccBezierConfig()
    bezier.controlPoint_1 = ccp(0, size.height / 2)
    bezier.controlPoint_2 = ccp(300, - size.height / 2)
    bezier.endPosition = ccp(300, 100)

    local bezierForward = CCBezierBy:create(3, bezier)
    local bezierBack = bezierForward:reverse()
    local rep = CCRepeatForever:create(CCSequence:createWithTwoActions(bezierForward, bezierBack))

    -- sprite 2
    tamara:setPosition(ccp(80,160))
    local bezier2 = ccBezierConfig()
    bezier2.controlPoint_1 = ccp(100, size.height / 2)
    bezier2.controlPoint_2 = ccp(200, - size.height / 2)
    bezier2.endPosition = ccp(240, 160)

    local bezierTo1 = CCBezierTo:create(2, bezier2)

    -- sprite 3
    kathia:setPosition(ccp(400,160))
    local bezierTo2 = CCBezierTo:create(2, bezier2)

    grossini:runAction(rep)
    tamara:runAction(bezierTo1)
    kathia:runAction(bezierTo2)

	subtitleLabel:setString("BezierTo / BezierBy")
	return layer
end

--------------------------------------
-- ActionBlink
--------------------------------------
local function ActionBlink()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

	local action1 = CCBlink:create(2, 10)
    local action2 = CCBlink:create(2, 5)

    tamara:runAction(action1)
    kathia:runAction(action2)

	subtitleLabel:setString("Blink")

	return layer
end

--------------------------------------
-- ActionFade
--------------------------------------
local function ActionFade()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

	tamara:setOpacity(0)
    local action1 = CCFadeIn:create(1)
    local action1Back = action1:reverse()

    local action2 = CCFadeOut:create(1)
    local action2Back = action2:reverse()

    tamara:runAction(CCSequence:createWithTwoActions( action1, action1Back))
    kathia:runAction(CCSequence:createWithTwoActions( action2, action2Back))

	subtitleLabel:setString("FadeIn / FadeOut")

	return layer
end

--------------------------------------
-- ActionTint
--------------------------------------
local function ActionTint()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

    local action1 = CCTintTo:create(2, 255, 0, 255)
    local action2 = CCTintBy:create(2, -127, -255, -127)
    local action2Back = action2:reverse()

    tamara:runAction(action1)
    kathia:runAction(CCSequence:createWithTwoActions(action2, action2Back))

	subtitleLabel:setString("TintTo / TintBy")

	return layer
end

--------------------------------------
-- ActionAnimate
--------------------------------------
local function ActionAnimate()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

    local animation = CCAnimation:create()
	local number, name
    for i = 1, 14 do
		if i < 10 then
			number = "0"..i
		else
			number = i
		end
        name = "Images/grossini_dance_"..number..".png"
        animation:addSpriteFrameWithFileName(name)
    end
    -- should last 2.8 seconds. And there are 14 frames.
    animation:setDelayPerUnit(2.8 / 14.0)
    animation:setRestoreOriginalFrame(true)

    local action = CCAnimate:create(animation)
    grossini:runAction(CCSequence:createWithTwoActions(action, action:reverse()))

    local cache = CCAnimationCache:sharedAnimationCache()
    cache:addAnimationsWithFile("animations/animations-2.plist")
    local animation2 = cache:animationByName("dance_1")

    local action2 = CCAnimate:create(animation2)
    tamara:runAction(CCSequence:createWithTwoActions(action2, action2:reverse()))

	local animation3 = animation2:copy():autorelease()
	-- problem
    tolua.cast(animation3,"CCAnimation"):setLoops(4)

    local action3 = CCAnimate:create(animation3)
    kathia:runAction(action3)

	titleLabel:setString("Animation")
	subtitleLabel:setString("Center: Manual animation. Border: using file format animation")

	return layer
end

--------------------------------------
-- ActionSequence
--------------------------------------
local function ActionSequence()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local action = CCSequence:createWithTwoActions(
        CCMoveBy:create(2, ccp(240,0)),
        CCRotateBy:create(2, 540))

    grossini:runAction(action)

	subtitleLabel:setString("Sequence: Move + Rotate")

	return layer
end

--------------------------------------
-- ActionSequence2
--------------------------------------
local actionSequenceLayer = nil

local function ActionSequenceCallback1()
	local label = CCLabelTTF:create("callback 1 called", "Marker Felt", 16)
    label:setPosition(size.width / 4, size.height / 2)

    actionSequenceLayer:addChild(label)
end

local function ActionSequenceCallback2(sender)
	local label = CCLabelTTF:create("callback 2 called", "Marker Felt", 16)
    label:setPosition(ccp(size.width / 4 * 2, size.height / 2))

    actionSequenceLayer:addChild(label)
end

local function ActionSequenceCallback3(sender)
	local label = CCLabelTTF:create("callback 3 called", "Marker Felt", 16)
    label:setPosition(ccp(size.width / 4 * 3, size.height / 2))

    actionSequenceLayer:addChild(label)
end

local function ActionSequence2()
	actionSequenceLayer = CCLayer:create()
	initWithLayer(actionSequenceLayer)

	alignSpritesLeft(1)

	grossini:setVisible(false)
	local array = CCArray:create()
	array:addObject(CCPlace:create(ccp(200,200)))
	array:addObject(CCShow:create())
	array:addObject(CCMoveBy:create(1, ccp(100,0)))
	array:addObject(CCCallFunc:create(ActionSequenceCallback1))
	array:addObject(CCCallFuncN:create(ActionSequenceCallback2))
	array:addObject(CCCallFuncN:create(ActionSequenceCallback3))
	local action = CCSequence:create(array)

    grossini:runAction(action)

	subtitleLabel:setString("Sequence of InstantActions")
	return actionSequenceLayer
end

--------------------------------------
-- ActionSpawn
--------------------------------------
local function ActionSpawn()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local action = CCSpawn:createWithTwoActions(
		CCJumpBy:create(2, ccp(300,0), 50, 4),
		CCRotateBy:create( 2,  720))

    grossini:runAction(action)

	subtitleLabel:setString("Spawn: Jump + Rotate")

	return layer
end

--------------------------------------
-- ActionReverse
--------------------------------------
local function ActionReverse()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local jump = CCJumpBy:create(2, ccp(300,0), 50, 4)
    local action = CCSequence:createWithTwoActions(jump, jump:reverse())

    grossini:runAction(action)

	subtitleLabel:setString("Reverse an action")

	return layer
end

--------------------------------------
-- ActionDelaytime
--------------------------------------
local function ActionDelaytime()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local move = CCMoveBy:create(1, ccp(150,0))
	local array = CCArray:create()
	array:addObject(move)
	array:addObject(CCDelayTime:create(2))
	array:addObject(move)
	local action = CCSequence:create(array)

    grossini:runAction(action)

	subtitleLabel:setString("DelayTime: m + delay + m")
	return layer
end

--------------------------------------
-- ActionRepeat
--------------------------------------
local function ActionRepeat()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(2)

    local a1 = CCMoveBy:create(1, ccp(150,0))
    local action1 = CCRepeat:create(CCSequence:createWithTwoActions(CCPlace:create(ccp(60,60)), a1), 3)

    local a2 = CCMoveBy:create(1, ccp(150,0))
    local action2 = CCRepeatForever:create(CCSequence:createWithTwoActions(a2, a1:reverse()))

    kathia:runAction(action1)
    tamara:runAction(action2)

	subtitleLabel:setString("Repeat / RepeatForever actions")
	return layer
end

--------------------------------------
-- ActionRepeatForever
--------------------------------------
local function repeatForever(sender)
	local repeatAction = CCRepeatForever:create(CCRotateBy:create(1.0, 360))

    sender:runAction(repeatAction)
end

local function ActionRepeatForever()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(1)

    local action = CCSequence:createWithTwoActions(
        CCDelayTime:create(1),
        CCCallFuncN:create(repeatForever))

    grossini:runAction(action)

	subtitleLabel:setString("CallFuncN + RepeatForever")
	return layer
end

--------------------------------------
-- ActionRotateToRepeat
--------------------------------------
local function ActionRotateToRepeat()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

    local act1 = CCRotateTo:create(1, 90)
    local act2 = CCRotateTo:create(1, 0)
    local seq  = CCSequence:createWithTwoActions(act1, act2)
    local rep1 = CCRepeatForever:create(seq)
    local rep2 = CCRepeat:create(tolua.cast(seq:copy():autorelease(), "CCSequence"), 10)

    tamara:runAction(rep1)
    kathia:runAction(rep2)

	subtitleLabel:setString("Repeat/RepeatForever + RotateTo")

	return layer
end

--------------------------------------
-- ActionRotateJerk
--------------------------------------
local function ActionRotateJerk()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

    local seq = CCSequence:createWithTwoActions(
        CCRotateTo:create(0.5, -20),
        CCRotateTo:create(0.5, 20))

    local rep1 = CCRepeat:create(seq, 10)

    local seq2 = CCSequence:createWithTwoActions(
        CCRotateTo:create(0.5, -20),
        CCRotateTo:create(0.5, 20))

    local rep2 = CCRepeatForever:create(seq2)

    tamara:runAction(rep1)
    kathia:runAction(rep2)

	subtitleLabel:setString("RepeatForever / Repeat + Rotate")
	return layer
end

--------------------------------------
-- ActionCallFunc
--------------------------------------
local callFuncLayer = nil

local function CallFucnCallback1()
	local label = CCLabelTTF:create("callback 1 called", "Marker Felt", 16)
    label:setPosition(size.width / 4, size.height / 2)

    callFuncLayer:addChild(label)
end

local function CallFucnCallback2(sender)
	local label = CCLabelTTF:create("callback 2 called", "Marker Felt", 16)
    label:setPosition(size.width / 4 * 2, size.height / 2)

    callFuncLayer:addChild(label)
end

local function CallFucnCallback3(sender)
	local label = CCLabelTTF:create("callback 3 called", "Marker Felt", 16)
    label:setPosition(size.width / 4 * 3, size.height / 2)

    callFuncLayer:addChild(label)
end

local function ActionCallFunc()
	callFuncLayer = CCLayer:create()
	initWithLayer(callFuncLayer)

	centerSprites(3)

	local action = CCSequence:createWithTwoActions(
        CCMoveBy:create(2, ccp(200,0)),
        CCCallFunc:create(CallFucnCallback1))

	local array = CCArray:create()
	array:addObject(CCScaleBy:create(2, 2))
	array:addObject(CCFadeOut:create(2))
	array:addObject(CCCallFuncN:create(CallFucnCallback2))
    local action2 = CCSequence:create(array)

    local array2 = CCArray:create()
    array2:addObject(CCRotateBy:create(3 , 360))
    array2:addObject(CCFadeOut:create(2))
    array2:addObject(CCCallFuncN:create(CallFucnCallback3))
    local action3 = CCSequence:create(array2)

    grossini:runAction(action)
	tamara:runAction(action2)
    kathia:runAction(action3)

	subtitleLabel:setString("Callbacks: CallFunc and friends")
	return callFuncLayer
end

--------------------------------------
-- ActionCallFuncND *
--   problem: the current luaEngine doesn't support
--   passing more than one param to lua script
--------------------------------------
local function ActionCallFuncND()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(1)


	titleLabel:setString("CallFuncND + auto remove")
	subtitleLabel:setString("CallFuncND + removeFromParentAndCleanup. Grossini dissapears in 2s")
	return layer
end

--------------------------------------
-- ActionReverseSequence
--------------------------------------
local function ActionReverseSequence()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(1)

	local move1  = CCMoveBy:create(1, ccp(250,0))
    local move2  = CCMoveBy:create(1, ccp(0,50))
	local array  = CCArray:create()
	array:addObject(move1)
	array:addObject(move2)
	array:addObject(move1:reverse())
    local seq    = CCSequence:create(array)
    local action = CCSequence:createWithTwoActions(seq, seq:reverse())

    grossini:runAction(action)

	subtitleLabel:setString("Reverse a sequence")
	return layer
end

--------------------------------------
-- ActionReverseSequence2
--------------------------------------
local function ActionReverseSequence2()
	local layer = CCLayer:create()
	initWithLayer(layer)

	alignSpritesLeft(2)

	-- Test:
    -- Sequence should work both with IntervalAction and InstantActions
	local move1  = CCMoveBy:create(1, ccp(250,0))
    local move2  = CCMoveBy:create(1, ccp(0,50))
	local tog1 = CCToggleVisibility:create()
    local tog2 = CCToggleVisibility:create()
	local array  = CCArray:createWithCapacity(10)
	array:addObject(move1)
	array:addObject(tog1)
	array:addObject(move2)
	array:addObject(tog2)
	array:addObject(move1:reverse())
    local seq = CCSequence:create(array)
    local action = CCRepeat:create(CCSequence:createWithTwoActions(seq, seq:reverse()), 3)

    -- Test:
    -- Also test that the reverse of Hide is Show, and vice-versa
    kathia:runAction(action)

    local move_tamara = CCMoveBy:create(1, ccp(100,0))
    local move_tamara2 = CCMoveBy:create(1, ccp(50,0))
    local hide = CCHide:create()
	local array2 = CCArray:createWithCapacity(10)
	array2:addObject(move_tamara)
	array2:addObject(hide)
	array2:addObject(move_tamara2)
    local seq_tamara = CCSequence:create(array2)
    local seq_back = seq_tamara:reverse()
    tamara:runAction(CCSequence:createWithTwoActions(seq_tamara, seq_back))

	subtitleLabel:setString("Reverse a sequence2")
	return layer
end

--------------------------------------
-- ActionOrbit
--------------------------------------
local function ActionOrbit()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(3)

	local orbit1 = CCOrbitCamera:create(2,1, 0, 0, 180, 0, 0)
    local action1 = CCSequence:createWithTwoActions(orbit1, orbit1:reverse())

    local orbit2 = CCOrbitCamera:create(2,1, 0, 0, 180, -45, 0)
    local action2 = CCSequence:createWithTwoActions(orbit2, orbit2:reverse())

    local orbit3 = CCOrbitCamera:create(2,1, 0, 0, 180, 90, 0)
    local action3 = CCSequence:createWithTwoActions(orbit3, orbit3:reverse())

    kathia:runAction(CCRepeatForever:create(action1))
    tamara:runAction(CCRepeatForever:create(action2))
    grossini:runAction(CCRepeatForever:create(action3))

    local move = CCMoveBy:create(3, ccp(100,-100))
    local move_back = move:reverse()
    local seq = CCSequence:createWithTwoActions(move, move_back)
    local rfe = CCRepeatForever:create(seq)
    kathia:runAction(rfe)
    tamara:runAction(tolua.cast(rfe:copy():autorelease(), "CCActionInterval"))
    grossini:runAction(tolua.cast(rfe:copy():autorelease(), "CCActionInterval"))


	subtitleLabel:setString("OrbitCamera action")
	return layer
end

--------------------------------------
-- ActionFollow
--------------------------------------
local function ActionFollow()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(1)

	grossini:setPosition(ccp(-200, size.height / 2))
    local move = CCMoveBy:create(2, ccp(size.width * 3, 0))
    local move_back = move:reverse()
    local seq = CCSequence:createWithTwoActions(move, move_back)
    local rep = CCRepeatForever:create(seq)

    grossini:runAction(rep)

    layer:runAction(CCFollow:create(grossini, CCRectMake(0, 0, size.width * 2 - 100, size.height)))

	subtitleLabel:setString("Follow action")
	return layer
end

--------------------------------------
-- ActionTargeted
--------------------------------------
local function ActionTargeted()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

	local jump1 = CCJumpBy:create(2, ccp(0, 0), 100, 3)
    local jump2 = CCJumpBy:create(2, ccp(0, 0), 100, 3)
    local rot1  = CCRotateBy:create(1, 360)
    local rot2  = CCRotateBy:create(1, 360)

    local t1 = CCTargetedAction:create(kathia, jump2)
    local t2 = CCTargetedAction:create(kathia, rot2)

	local array = CCArray:createWithCapacity(10)
	array:addObject(jump1)
	array:addObject(t1)
	array:addObject(rot1)
	array:addObject(t2)
    local seq = CCSequence:create(array)
    local always = CCRepeatForever:create(seq)

    tamara:runAction(always)

	titleLabel:setString("ActionTargeted")
	subtitleLabel:setString("Action that runs on another target. Useful for sequences")
	return layer
end

--------------------------------------
-- PauseResumeActions *
--   problem: schedule feature is constructing
--------------------------------------
local pausedTargets = nil
local PauseResumeActions_pauseEntry = nil
local PauseResumeActions_resumeEntry = nil

local function ActionPause(dt)
	cclog("Pausing")

	local scheduler = CCDirector:sharedDirector():getScheduler()
	scheduler:unscheduleScriptEntry(PauseResumeActions_pauseEntry)

	local director = CCDirector:sharedDirector()
    pausedTargets = director:getActionManager():pauseAllRunningActions()
    pausedTargets:retain()
end

local function ActionResume(dt)
	cclog("Resuming")

	local scheduler = CCDirector:sharedDirector():getScheduler()
	scheduler:unscheduleScriptEntry(PauseResumeActions_resumeEntry)

	local director = CCDirector:sharedDirector()
	if pausedTargets ~= nil then
		-- problem: will crash here. Try fixing me!
		director:getActionManager():resumeTargets(pausedTargets)
        pausedTargets:release()
	end
end

local function PauseResumeActions_onEnterOrExit(tag)
	local scheduler = CCDirector:sharedDirector():getScheduler()
	if tag == "enter" then
		PauseResumeActions_pauseEntry = scheduler:scheduleScriptFunc(ActionPause, 3, false)
		PauseResumeActions_resumeEntry = scheduler:scheduleScriptFunc(ActionResume, 5, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(PauseResumeActions_pauseEntry)
		scheduler:unscheduleScriptEntry(PauseResumeActions_resumeEntry)
	end
end

local function PauseResumeActions()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(2)

    tamara:runAction(CCRepeatForever:create(CCRotateBy:create(3, 360)))
    kathia:runAction(CCRepeatForever:create(CCRotateBy:create(3, 360)))

	layer:registerScriptHandler(PauseResumeActions_onEnterOrExit)

	titleLabel:setString("PauseResumeActions")
	subtitleLabel:setString("All actions pause at 3s and resume at 5s")
	return layer
end

--------------------------------------
-- ActionIssue1305
--------------------------------------
local spriteTmp = nil
local Issue1305_entry = nil
local Issue1305_layer = nil

local function Issue1305_log(sender)
	cclog("This message SHALL ONLY appear when the sprite is added to the scene, NOT BEFORE")
end

local function addSprite(dt)
	local scheduler = CCDirector:sharedDirector():getScheduler()
	scheduler:unscheduleScriptEntry(Issue1305_entry)

	spriteTmp:setPosition(ccp(250, 250))
    Issue1305_layer:addChild(spriteTmp)
end

local function Issue1305_onEnterOrExit(tag)
	local scheduler = CCDirector:sharedDirector():getScheduler()
	if tag == "enter" then
		Issue1305_entry = scheduler:scheduleScriptFunc(addSprite, 2, false)
	elseif tag == "exit" then
		scheduler:unscheduleScriptEntry(Issue1305_entry)
	end
end

local function ActionIssue1305()
	Issue1305_layer = CCLayer:create()
	initWithLayer(Issue1305_layer)

	centerSprites(0)

    spriteTmp = CCSprite:create("Images/grossini.png")
    spriteTmp:runAction(CCCallFuncN:create(Issue1305_log))

    Issue1305_layer:registerScriptHandler(Issue1305_onEnterOrExit)

	titleLabel:setString("Issue 1305")
	subtitleLabel:setString("In two seconds you should see a message on the console. NOT BEFORE.")
	return Issue1305_layer
end

--------------------------------------
-- ActionIssue1305_2
--------------------------------------
local function Issue1305_2_log1()
    cclog("1st block")
end

local function Issue1305_2_log2()
    cclog("2nd block")
end

local function Issue1305_2_log3()
    cclog("3rd block")
end

local function Issue1305_2_log4()
    cclog("4th block")
end

local function ActionIssue1305_2()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = CCSprite:create("Images/grossini.png")
    spr:setPosition(ccp(200,200))
    layer:addChild(spr)

    local act1 = CCMoveBy:create(2 ,ccp(0, 100))
    local act2 = CCCallFunc:create(Issue1305_2_log1)
    local act3 = CCMoveBy:create(2, ccp(0, -100))
    local act4 = CCCallFunc:create(Issue1305_2_log2)
    local act5 = CCMoveBy:create(2, ccp(100, -100))
    local act6 = CCCallFunc:create(Issue1305_2_log3)
    local act7 = CCMoveBy:create(2, ccp(-100, 0))
    local act8 = CCCallFunc:create(Issue1305_2_log4)

	local array = CCArray:create()
	array:addObject(act1)
	array:addObject(act2)
	array:addObject(act3)
	array:addObject(act4)
	array:addObject(act5)
	array:addObject(act6)
	array:addObject(act7)
	array:addObject(act8)
    local actF = CCSequence:create(array)

    CCDirector:sharedDirector():getActionManager():addAction(actF ,spr, false)

	titleLabel:setString("Issue 1305 #2")
	subtitleLabel:setString("See console. You should only see one message for each block")
	return layer
end

--------------------------------------
-- ActionIssue1288
--------------------------------------
local function ActionIssue1288()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = CCSprite:create("Images/grossini.png")
    spr:setPosition(ccp(100, 100))
    layer:addChild(spr)

    local act1 = CCMoveBy:create(0.5, ccp(100, 0))
    local act2 = act1:reverse()
    local act3 = CCSequence:createWithTwoActions(act1, act2)
    local act4 = CCRepeat:create(act3, 2)

    spr:runAction(act4)

	titleLabel:setString("Issue 1288")
	subtitleLabel:setString("Sprite should end at the position where it started.")
	return layer
end

--------------------------------------
-- ActionIssue1288_2
--------------------------------------
local function ActionIssue1288_2()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = CCSprite:create("Images/grossini.png")
    spr:setPosition(ccp(100, 100))
    layer:addChild(spr)

    local act1 = CCMoveBy:create(0.5, ccp(100, 0))
    spr:runAction(CCRepeat:create(act1, 1))

	titleLabel:setString("Issue 1288 #2")
	subtitleLabel:setString("Sprite should move 100 pixels, and stay there")
	return layer
end

--------------------------------------
-- ActionIssue1327
--------------------------------------
local function logSprRotation(sender)
	cclog(""..sender:getRotation())
end

local function ActionIssue1327()
	local layer = CCLayer:create()
	initWithLayer(layer)

	centerSprites(0)

    local spr = CCSprite:create("Images/grossini.png")
    spr:setPosition(ccp(100, 100))
    layer:addChild(spr)

    local act1 = CCCallFuncN:create(logSprRotation)
    local act2 = CCRotateBy:create(0.25, 45)
    local act3 = CCCallFuncN:create(logSprRotation)
    local act4 = CCRotateBy:create(0.25, 45)
    local act5 = CCCallFuncN:create(logSprRotation)
    local act6 = CCRotateBy:create(0.25, 45)
    local act7 = CCCallFuncN:create(logSprRotation)
    local act8 = CCRotateBy:create(0.25, 45)
    local act9 = CCCallFuncN:create(logSprRotation)

	local array = CCArray:create()
	array:addObject(act1)
	array:addObject(act2)
	array:addObject(act3)
	array:addObject(act4)
	array:addObject(act5)
	array:addObject(act6)
	array:addObject(act7)
	array:addObject(act8)
	array:addObject(act9)
    spr:runAction(CCSequence:create(array))

	titleLabel:setString("Issue 1327")
	subtitleLabel:setString("See console: You should see: 0, 45, 90, 135, 180")
	return layer
end

-------------------------------------
-- Create Action Test
-------------------------------------
function CreateActionTestLayer()
	local layer = nil
	if ActionIdx == Action_Table.ACTION_MANUAL_LAYER then
		layer = ActionManual()
	elseif ActionIdx == Action_Table.ACTION_MOVE_LAYER then
		layer = ActionMove()
	elseif ActionIdx == Action_Table.ACTION_SCALE_LAYER then
		layer = ActionScale()
	elseif ActionIdx == Action_Table.ACTION_ROTATE_LAYER then
		layer = ActionRotate()
	elseif ActionIdx == Action_Table.ACTION_SKEW_LAYER then
		layer = ActionSkew()
    elseif ActionIdx == Action_Table.ACTION_SKEW_STANDER then 
        layer = ActionRotationalSkewVSStandardSkew()
	elseif ActionIdx == Action_Table.ACTION_SKEWROTATE_LAYER then
		layer = ActionSkewRotate()
	elseif ActionIdx == Action_Table.ACTION_JUMP_LAYER then
		layer = ActionJump()
	elseif ActionIdx == Action_Table.ACTION_CARDINALSPLINE_LAYER then
		layer = ActionCardinalSpline()
    elseif ActionIdx == Action_Table.ACTION_CATMULLROM_LAYER then
		layer = ActionCatmullRom()
	elseif ActionIdx == Action_Table.ACTION_BEZIER_LAYER then
		layer = ActionBezier()
	elseif ActionIdx == Action_Table.ACTION_BLINK_LAYER then
		layer = ActionBlink()
	elseif ActionIdx == Action_Table.ACTION_FADE_LAYER then
		layer = ActionFade()
	elseif ActionIdx == Action_Table.ACTION_TINT_LAYER then
		layer = ActionTint()
	elseif ActionIdx == Action_Table.ACTION_ANIMATE_LAYER then
		layer = ActionAnimate()
	elseif ActionIdx == Action_Table.ACTION_SEQUENCE_LAYER then
		layer = ActionSequence()
	elseif ActionIdx == Action_Table.ACTION_SEQUENCE2_LAYER then
		layer = ActionSequence2()
	elseif ActionIdx == Action_Table.ACTION_SPAWN_LAYER then
		layer = ActionSpawn()
	elseif ActionIdx == Action_Table.ACTION_REVERSE then
		layer = ActionReverse()
	elseif ActionIdx == Action_Table.ACTION_DELAYTIME_LAYER then
		layer = ActionDelaytime()
	elseif ActionIdx == Action_Table.ACTION_REPEAT_LAYER then
		layer = ActionRepeat()
	elseif ActionIdx == Action_Table.ACTION_REPEATEFOREVER_LAYER then
		layer = ActionRepeatForever()
    elseif ActionIdx == Action_Table.ACTION_ROTATETOREPEATE_LAYER then
		layer = ActionRotateToRepeat()
    elseif ActionIdx == Action_Table.ACTION_ROTATEJERK_LAYER then
		layer = ActionRotateJerk()
    elseif ActionIdx == Action_Table.ACTION_CALLFUNC_LAYER then
		layer = ActionCallFunc()
    elseif ActionIdx == Action_Table.ACTION_CALLFUNCND_LAYER then
		layer = ActionCallFuncND()
    elseif ActionIdx == Action_Table.ACTION_REVERSESEQUENCE_LAYER then
		layer = ActionReverseSequence()
    elseif ActionIdx == Action_Table.ACTION_REVERSESEQUENCE2_LAYER then
		layer = ActionReverseSequence2()
    elseif ActionIdx == Action_Table.ACTION_ORBIT_LAYER then
		layer = ActionOrbit()
    elseif ActionIdx == Action_Table.ACTION_FOLLOW_LAYER then
		layer = ActionFollow()
    elseif ActionIdx == Action_Table.ACTION_TARGETED_LAYER then
		layer = ActionTargeted()
	elseif ActionIdx == Action_Table.PAUSERESUMEACTIONS_LAYER then
		layer = PauseResumeActions()
    elseif ActionIdx == Action_Table.ACTION_ISSUE1305_LAYER then
		layer = ActionIssue1305()
    elseif ActionIdx == Action_Table.ACTION_ISSUE1305_2_LAYER then
		layer = ActionIssue1305_2()
    elseif ActionIdx == Action_Table.ACTION_ISSUE1288_LAYER then
		layer = ActionIssue1288()
    elseif ActionIdx == Action_Table.ACTION_ISSUE1288_2_LAYER then
		layer = ActionIssue1288_2()
    elseif ActionIdx == Action_Table.ACTION_ISSUE1327_LAYER then
		layer = ActionIssue1327()
	end

	return layer
end

function ActionsTest()
	cclog("ActionsTest")
	local scene = CCScene:create()

	ActionIdx = -1
	scene:addChild(NextAction())
	scene:addChild(CreateBackMenuItem())

	return scene
end
