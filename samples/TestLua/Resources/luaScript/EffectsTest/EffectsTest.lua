require "luaScript/EffectsTest/EffectsName"


local ActionIdx = 0
local s = CCDirector:sharedDirector():getWinSize()
local kTagTextLayer  = 1
local kTagBackground = 1
local kTagLabel      = 2

local titleLabel = nil

local function checkAnim(dt)

end

local function getAction()
	return CreateEffect(ActionIdx, 3)
end

local function initWithLayer(layer)
	x, y = s.width, s.height

    local node = CCNode:create()
    local effect = getAction()
    node:runAction(effect)
    addChild(node, 0, kTagBackground)

    local bg = CCSprite:create(s_back3)
    node:addChild(bg, 0)
    bg:setPosition(CCPointMake(s.width / 2, s.height / 2))

    local grossini = CCSprite:create(s_pPathSister2)
    node:addChild(grossini, 1)
    grossini:setPosition( CCPointMake(x / 3, y / 2) )
    local sc = CCScaleBy:create(2, 5)
    local sc_back = sc:reverse()
    grossini:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(sc, sc_back)))

    local tamara = CCSprite:create(s_pPathSister1)
    node:addChild(tamara, 1)
    tamara:setPosition(CCPointMake(2 * x / 3, y / 2))
    local sc2 = CCScaleBy:create(2, 5)
    local sc2_back = sc2:reverse()
    tamara:runAction(CCRepeatForever:create(CCSequence:createWithTwoActions(sc2, sc2_back)))

	titleLabel = CCLabelTTF:create(EffectsList[ActionIdx], "Marker Felt", 32)
    titleLabel:setPosition(CCPointMake(x / 2, y - 80))
    addChild(titleLabel)
    titleLabel:setTag(kTagLabel)

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
    item1:setPosition(CCPointMake( s.width/2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(CCPointMake( s.width/2, item2:getContentSize().height / 2))
    item3:setPosition(CCPointMake( s.width/2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))

    layer:addChild(menu, 1)

    --schedule( schedule_selector(TextLayer:checkAnim) )
end


--------------------------------------
-- Entrance
--------------------------------------
function EffectsTest()
	cclog("EffectsTest")
	local scene = CCScene:create()
	local layer = CCLayerColor:create(ccc4(32,128,32,255))

	initWithLayer(layer)

	scene:addChild(layer)
	scene:addChild(CreateBackMenuItem())

	return scene
end
