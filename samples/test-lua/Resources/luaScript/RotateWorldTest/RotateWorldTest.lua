
local size = cc.Director:getInstance():getWinSize()

local function CreateSpriteLayer()
	local layer = cc.Layer:create()

	local x, y
    x = size.width
    y = size.height

    local sprite = cc.Sprite:create(s_pPathGrossini)
    local spriteSister1 = cc.Sprite:create(s_pPathSister1)
    local spriteSister2 = cc.Sprite:create(s_pPathSister2)

    sprite:setScale(1.5)
    spriteSister1:setScale(1.5)
    spriteSister2:setScale(1.5)

    sprite:setPosition(cc.p(x / 2, y / 2))
    spriteSister1:setPosition(cc.p(40, y / 2))
    spriteSister2:setPosition(cc.p(x - 40, y / 2))

    layer:addChild(sprite)
    layer:addChild(spriteSister1)
    layer:addChild(spriteSister2)

	local rot = cc.RotateBy:create(16, -3600)
    sprite:runAction(rot)

    local jump1 = cc.JumpBy:create(4, cc.p(-400, 0), 100, 4)
    local jump2 = jump1:reverse()

    local rot1 = cc.RotateBy:create(4, 360 * 2)
    local rot2 = rot1:reverse()

    local jump3 = cc.JumpBy:create(4, cc.p(-400, 0), 100, 4)
    local jump4 = jump3:reverse()
    local rot3 = cc.RotateBy:create(4, 360 * 2)
    local rot4 = rot3:reverse()

    spriteSister1:runAction(cc.Repeat:create(cc.Sequence:create(jump2, jump1), 5))
    spriteSister2:runAction(cc.Repeat:create(cc.Sequence:create(jump3, jump4), 5))

    spriteSister1:runAction(cc.Repeat:create(cc.Sequence:create(rot1, rot2), 5))
    spriteSister2:runAction(cc.Repeat:create(cc.Sequence:create(rot4, rot3), 5))

	return layer
end

local function CreateTestLayer()
	local layer = cc.Layer:create()

	local x, y
    x = size.width
    y = size.height

    local label = cc.LabelTTF:create("cocos2d", "Tahoma", 64)
    label:setPosition(x / 2, y / 2)
    layer:addChild(label)

	return layer
end

local function CreateRotateWorldLayer()
	local layer = cc.Layer:create()

	local x, y
    x = size.width
    y = size.height

    local blue =  cc.LayerColor:create(cc.c4b(0,0,255,255))
    local red =   cc.LayerColor:create(cc.c4b(255,0,0,255))
    local green = cc.LayerColor:create(cc.c4b(0,255,0,255))
    local white = cc.LayerColor:create(cc.c4b(255,255,255,255))

    blue:setScale(0.5)
    blue:setPosition(cc.p(- x / 4, - y / 4))
    blue:addChild(CreateSpriteLayer())

    red:setScale(0.5)
    red:setPosition(cc.p(x / 4, - y / 4))

    green:setScale(0.5)
    green:setPosition(cc.p(- x / 4, y / 4))
    green:addChild(CreateTestLayer())

    white:setScale(0.5)
    white:setPosition(cc.p(x / 4, y / 4))
    white:ignoreAnchorPointForPosition(false)
    white:setPosition(cc.p(x / 4 * 3, y / 4 * 3))

    layer:addChild(blue, -1)
    layer:addChild(white)
    layer:addChild(green)
    layer:addChild(red)

    local rot = cc.RotateBy:create(8, 720)
    local rot1 = cc.RotateBy:create(8, 720)
    local rot2 = cc.RotateBy:create(8, 720)
    local rot3 = cc.RotateBy:create(8, 720)

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
	local scene = cc.Scene:create()
	local layer = CreateRotateWorldLayer()

	scene:addChild(layer)
	scene:addChild(CreateBackMenuItem())
	scene:runAction(cc.RotateBy:create(4, -360))

	return scene
end
