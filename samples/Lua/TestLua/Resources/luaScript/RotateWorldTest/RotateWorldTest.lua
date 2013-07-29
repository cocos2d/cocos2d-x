
local size = CCDirector:getInstance():getWinSize()

local function CreateSpriteLayer()
	local layer = CCLayer:create()

	local x, y
    x = size.width
    y = size.height

    local sprite = CCSprite:create(s_pPathGrossini)
    local spriteSister1 = CCSprite:create(s_pPathSister1)
    local spriteSister2 = CCSprite:create(s_pPathSister2)

    sprite:setScale(1.5)
    spriteSister1:setScale(1.5)
    spriteSister2:setScale(1.5)

    sprite:setPosition(CCPoint(x / 2, y / 2))
    spriteSister1:setPosition(CCPoint(40, y / 2))
    spriteSister2:setPosition(CCPoint(x - 40, y / 2))

    layer:addChild(sprite)
    layer:addChild(spriteSister1)
    layer:addChild(spriteSister2)

	local rot = CCRotateBy:create(16, -3600)
    sprite:runAction(rot)

    local jump1 = CCJumpBy:create(4, CCPoint(-400, 0), 100, 4)
    local jump2 = jump1:reverse()

    local rot1 = CCRotateBy:create(4, 360 * 2)
    local rot2 = rot1:reverse()

    local jump3 = CCJumpBy:create(4, CCPoint(-400, 0), 100, 4)
    local jump4 = jump3:reverse()
    local rot3 = CCRotateBy:create(4, 360 * 2)
    local rot4 = rot3:reverse()

    spriteSister1:runAction(CCRepeat:create(CCSequence:createWithTwoActions(jump2, jump1), 5))
    spriteSister2:runAction(CCRepeat:create(CCSequence:createWithTwoActions(jump3, jump4), 5))

    spriteSister1:runAction(CCRepeat:create(CCSequence:createWithTwoActions(rot1, rot2), 5))
    spriteSister2:runAction(CCRepeat:create(CCSequence:createWithTwoActions(rot4, rot3), 5))

	return layer
end

local function CreateTestLayer()
	local layer = CCLayer:create()

	local x, y
    x = size.width
    y = size.height

    local label = CCLabelTTF:create("cocos2d", "Tahoma", 64)
    label:setPosition(x / 2, y / 2)
    layer:addChild(label)

	return layer
end

local function CreateRotateWorldLayer()
	local layer = CCLayer:create()

	local x, y
    x = size.width
    y = size.height

    local blue =  CCLayerColor:create(Color4B(0,0,255,255))
    local red =   CCLayerColor:create(Color4B(255,0,0,255))
    local green = CCLayerColor:create(Color4B(0,255,0,255))
    local white = CCLayerColor:create(Color4B(255,255,255,255))

    blue:setScale(0.5)
    blue:setPosition(CCPoint(- x / 4, - y / 4))
    blue:addChild(CreateSpriteLayer())

    red:setScale(0.5)
    red:setPosition(CCPoint(x / 4, - y / 4))

    green:setScale(0.5)
    green:setPosition(CCPoint(- x / 4, y / 4))
    green:addChild(CreateTestLayer())

    white:setScale(0.5)
    white:setPosition(CCPoint(x / 4, y / 4))
    white:ignoreAnchorPointForPosition(false)
    white:setPosition(CCPoint(x / 4 * 3, y / 4 * 3))

    layer:addChild(blue, -1)
    layer:addChild(white)
    layer:addChild(green)
    layer:addChild(red)

    local rot = CCRotateBy:create(8, 720)
    local rot1 = CCRotateBy:create(8, 720)
    local rot2 = CCRotateBy:create(8, 720)
    local rot3 = CCRotateBy:create(8, 720)

    blue:runAction(rot)
    red:runAction(rot1)
    green:runAction(rot2)
    white:runAction(rot3)

	return layer
end

--------------------------------
-- Rotate World Test
--------------------------------
function RotateWorldTest()
	cclog("RotateWorldTest")
	local scene = CCScene:create()
	local layer = CreateRotateWorldLayer()

	scene:addChild(layer)
	scene:addChild(CreateBackMenuItem())
	scene:runAction(CCRotateBy:create(4, -360))

	return scene
end
