require "luaScript/TransitionsTest/TransitionsName"


local SceneIdx = 0
local TRANSITION_DURATION = 1.2
local s = CCDirector:sharedDirector():getWinSize()

-----------------------------
-- TestLayer1
-----------------------------
local function layer1BackCallback()
	SceneIdx = SceneIdx - 1
    if SceneIdx < 0 then
        SceneIdx = SceneIdx + Transition_Table.MAX_LAYER
	end

	generateTranScene(2)
end

local function layer1RestartCallback()
	generateTranScene(2);
end

local function layer1NextCallback()
	SceneIdx = SceneIdx + 1
    SceneIdx = math.mod(SceneIdx, Transition_Table.MAX_LAYER)

    generateTranScene(2)
end

local function createLayer1()
	local layer = CCLayer:create()
	local x, y = s.width, s.height

	local bg1 = CCSprite:create(s_back1)
	bg1:setPosition(CCPointMake(s.width / 2, s.height / 2))
	layer:addChild(bg1, -1)

	local titleLabel = CCLabelTTF:create(Transition_Name[SceneIdx], "Thonburi", 32)
	layer:addChild(titleLabel)
    titleLabel:setColor(ccc3(255,32,32))
    titleLabel:setPosition(x / 2, y - 100)

    local label = CCLabelTTF:create("SCENE 1", "Marker Felt", 38)
    label:setColor(ccc3(16,16,255))
    label:setPosition(x / 2, y / 2)
    layer:addChild(label)

    -- menu
    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
	item1:registerScriptHandler(layer1BackCallback)
	item2:registerScriptHandler(layer1RestartCallback)
	item3:registerScriptHandler(layer1NextCallback)

    local menu = CCMenu:create()
	menu:addChild(item1)
	menu:addChild(item2)
	menu:addChild(item3)
	menu:setPosition(CCPointMake(0, 0))
    item1:setPosition(CCPointMake(s.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(s.width / 2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(s.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))

    layer:addChild(menu, 1)

	return layer
end

-----------------------------
-- TestLayer2
-----------------------------
local function layer2BackCallback()
	SceneIdx = SceneIdx - 1
    if SceneIdx < 0 then
        SceneIdx = SceneIdx + Transition_Table.MAX_LAYER
	end

	generateTranScene(1)
end

local function layer2RestartCallback()
	generateTranScene(1);
end

local function layer2NextCallback()
	SceneIdx = SceneIdx + 1
    SceneIdx = math.mod(SceneIdx, Transition_Table.MAX_LAYER)

    generateTranScene(1)
end

local function createLayer2()
	local layer = CCLayer:create()
	local x, y = s.width, s.height

	local bg1 = CCSprite:create(s_back2)
	bg1:setPosition(CCPointMake(s.width / 2, s.height / 2))
	layer:addChild(bg1, -1)

	local titleLabel = CCLabelTTF:create(Transition_Name[SceneIdx], "Thonburi", 32 )
    layer:addChild(titleLabel)
    titleLabel:setColor(ccc3(255,32,32))
    titleLabel:setPosition(x / 2, y - 100)

    local label = CCLabelTTF:create("SCENE 2", "Marker Felt", 38)
    label:setColor(ccc3(16,16,255))
    label:setPosition(x / 2, y / 2)
    layer:addChild(label)

    -- menu
    local item1 = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    local item2 = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    local item3 = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
	item1:registerScriptHandler(layer2BackCallback)
	item2:registerScriptHandler(layer2RestartCallback)
	item3:registerScriptHandler(layer2NextCallback)

    local menu = CCMenu:create()
	menu:addChild(item1)
	menu:addChild(item2)
	menu:addChild(item3)
	menu:setPosition(CCPointMake(0, 0))
    item1:setPosition(CCPointMake(s.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake(s.width / 2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake(s.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))

    layer:addChild(menu, 1)

	return layer
end

-----------------------------
-- Create Transition Test
-----------------------------
local function createTransition(index, t, scene)
	CCDirector:sharedDirector():setDepthTest(false)

	if index == Transition_Table.CCTransitionJumpZoom then
		scene = CCTransitionJumpZoom:create(t, scene)
	elseif index == Transition_Table.CCTransitionProgressRadialCCW then
		scene = CCTransitionProgressRadialCCW:create(t, scene)
	elseif index == Transition_Table.CCTransitionProgressRadialCW then
		scene = CCTransitionProgressRadialCW:create(t, scene)
	elseif index == Transition_Table.CCTransitionProgressHorizontal then
		scene = CCTransitionProgressHorizontal:create(t, scene)
	elseif index == Transition_Table.CCTransitionProgressVertical then
		scene = CCTransitionProgressVertical:create(t, scene)
	elseif index == Transition_Table.CCTransitionProgressInOut then
		scene = CCTransitionProgressInOut:create(t, scene)
	elseif index == Transition_Table.CCTransitionProgressOutIn then
		scene = CCTransitionProgressOutIn:create(t, scene)
	elseif index == Transition_Table.CCTransitionCrossFade then
		scene = CCTransitionCrossFade:create(t, scene)
    elseif index == Transition_Table.TransitionPageForward then
		CCDirector:sharedDirector():setDepthTest(true)
		scene = CCTransitionPageTurn:create(t, scene, false)
	elseif index == Transition_Table.TransitionPageBackward then
		CCDirector:sharedDirector():setDepthTest(true)
		scene = CCTransitionPageTurn:create(t, scene, true)
	elseif index == Transition_Table.CCTransitionFadeTR then
		scene = CCTransitionFadeTR:create(t, scene)
	elseif index == Transition_Table.CCTransitionFadeBL then
		scene = CCTransitionFadeBL:create(t, scene)
	elseif index == Transition_Table.CCTransitionFadeUp then
		scene = CCTransitionFadeUp:create(t, scene)
	elseif index == Transition_Table.CCTransitionFadeDown then
		scene = CCTransitionFadeDown:create(t, scene)
	elseif index == Transition_Table.CCTransitionTurnOffTiles then
		scene = CCTransitionTurnOffTiles:create(t, scene)
	elseif index == Transition_Table.CCTransitionSplitRows then
		scene = CCTransitionSplitRows:create(t, scene)
	elseif index == Transition_Table.CCTransitionSplitCols then
		scene = CCTransitionSplitCols:create(t, scene)
	elseif index == Transition_Table.CCTransitionFade then
		scene = CCTransitionFade:create(t, scene)
	elseif index == Transition_Table.FadeWhiteTransition then
		scene = CCTransitionFade:create(t, scene, ccc3(255, 255, 255))
	elseif index == Transition_Table.FlipXLeftOver then
		scene = CCTransitionFlipX:create(t, scene, kOrientationLeftOver)
	elseif index == Transition_Table.FlipXRightOver then
		scene = CCTransitionFlipX:create(t, scene, kOrientationRightOver)
    elseif index == Transition_Table.FlipYUpOver then
		scene = CCTransitionFlipY:create(t, scene, kOrientationUpOver)
    elseif index == Transition_Table.FlipYDownOver then
		scene = CCTransitionFlipY:create(t, scene, kOrientationDownOver)
    elseif index == Transition_Table.FlipAngularLeftOver then
		scene = CCTransitionFlipAngular:create(t, scene, kOrientationLeftOver)
    elseif index == Transition_Table.FlipAngularRightOver then
		scene = CCTransitionFlipAngular:create(t, scene, kOrientationRightOver)
    elseif index == Transition_Table.ZoomFlipXLeftOver then
		scene = CCTransitionZoomFlipX:create(t, scene, kOrientationLeftOver)
    elseif index == Transition_Table.ZoomFlipXRightOver then
		scene = CCTransitionZoomFlipX:create(t, scene, kOrientationRightOver)
    elseif index == Transition_Table.ZoomFlipYUpOver then
		scene = CCTransitionZoomFlipY:create(t, scene, kOrientationUpOver)
    elseif index == Transition_Table.ZoomFlipYDownOver then
		scene = CCTransitionZoomFlipY:create(t, scene, kOrientationDownOver)
    elseif index == Transition_Table.ZoomFlipAngularLeftOver then
		scene = CCTransitionZoomFlipAngular:create(t, scene, kOrientationLeftOver)
	elseif index == Transition_Table.ZoomFlipAngularRightOver then
		scene = CCTransitionZoomFlipAngular:create(t, scene, kOrientationRightOver)
    elseif index == Transition_Table.CCTransitionShrinkGrow then
		scene = CCTransitionShrinkGrow:create(t, scene)
    elseif index == Transition_Table.CCTransitionRotoZoom then
		scene = CCTransitionRotoZoom:create(t, scene)
    elseif index == Transition_Table.CCTransitionMoveInL then
		scene = CCTransitionMoveInL:create(t, scene)
    elseif index == Transition_Table.CCTransitionMoveInR then
		scene = CCTransitionMoveInR:create(t, scene)
    elseif index == Transition_Table.CCTransitionMoveInT then
		scene = CCTransitionMoveInT:create(t, scene)
   elseif index == Transition_Table.CCTransitionMoveInB then
		scene = CCTransitionMoveInB:create(t, scene)
    elseif index == Transition_Table.CCTransitionSlideInL then
		scene = CCTransitionSlideInL:create(t, scene)
    elseif index == Transition_Table.CCTransitionSlideInR then
		scene = CCTransitionSlideInR:create(t, scene)
    elseif index == Transition_Table.CCTransitionSlideInT then
		scene = CCTransitionSlideInT:create(t, scene)
    elseif index == Transition_Table.CCTransitionSlideInB then
		scene = CCTransitionSlideInB:create(t, scene)
	end

	return scene
end

function generateTranScene(sceneType)
	local scene = CCScene:create()
    local layer = nil

	if sceneType == 1 then
		layer = createLayer1()
	elseif sceneType == 2 then
		layer = createLayer2()
	end

	scene:addChild(CreateBackMenuItem())
    scene:addChild(layer)

    local tranScene = createTransition(SceneIdx, TRANSITION_DURATION, scene)
    if tranScene ~= nil then
        CCDirector:sharedDirector():replaceScene(tranScene)
	end
end

function TransitionsTest()
	cclog("TransitionsTest")
	local scene = CCScene:create()

	scene:addChild(CreateBackMenuItem())
	scene:addChild(createLayer1())

	return scene
end
