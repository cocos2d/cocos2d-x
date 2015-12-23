local kMaxNodes = 50000
local kBasicZOrder = 10
local kNodesIncrease = 250
local TEST_COUNT = 7

local s = cc.Director:getInstance():getWinSize()

-----------------------------------
--  For test functions
-----------------------------------
local function performanceActions(sprite)
	sprite:setPosition(cc.p(math.mod(math.random(1, 99999999), s.width), math.mod(math.random(1, 99999999), s.height)))

    local period = 0.5 + math.mod(math.random(1, 99999999), 1000) / 500.0
    local rot = cc.RotateBy:create(period, 360.0 * math.random())
	local rot = cc.RotateBy:create(period, 360.0 * math.random())
    local permanentRotation = cc.RepeatForever:create(cc.Sequence:createWithTwoActions(rot, rot:reverse()))
    sprite:runAction(permanentRotation)

     local growDuration = 0.5 + math.mod(math.random(1, 99999999), 1000) / 500.0
    local grow = cc.ScaleBy:create(growDuration, 0.5, 0.5)
    local permanentScaleLoop = cc.RepeatForever:create(cc.Sequence:createWithTwoActions(grow, grow:reverse()))
    sprite:runAction(permanentScaleLoop)
end

local function performanceActions20(sprite)
	if math.random() < 0.2 then
        sprite:setPosition(cc.p(math.mod(math.random(1, 99999999), s.width), math.mod(math.random(1, 99999999), s.height)))
    else
        sprite:setPosition(cc.p(-1000, -1000))
	end

    local period = 0.5 + math.mod(math.random(1, 99999999), 1000) / 500.0
    local rot = cc.RotateBy:create(period, 360.0 * math.random())
    local permanentRotation = cc.RepeatForever:create(cc.Sequence:createWithTwoActions(rot, rot:reverse()))
    sprite:runAction(permanentRotation)

    local growDuration = 0.5 + math.mod(math.random(1, 99999999), 1000) / 500.0
    local grow = cc.ScaleBy:create(growDuration, 0.5, 0.5)
    local permanentScaleLoop = cc.RepeatForever:create(cc.Sequence:createWithTwoActions(grow, grow:reverse()))
    sprite:runAction(permanentScaleLoop)
end

local function performanceRotationScale(sprite)
	sprite:setPosition(cc.p(math.mod(math.random(1, 99999999), s.width), math.mod(math.random(1, 99999999), s.height)))
    sprite:setRotation(math.random() * 360)
    sprite:setScale(math.random() * 2)
end

local function performancePosition(sprite)
	sprite:setPosition(cc.p(math.mod(math.random(1, 99999999), s.width), math.mod(math.random(1, 99999999), s.height)))
end

local function performanceout20(sprite)
	if math.random() < 0.2 then
        sprite:setPosition(cc.p(math.mod(math.random(1, 99999999), s.width), math.mod(math.random(1, 99999999), s.height)))
    else
        sprite:setPosition(cc.p(-1000, -1000))
	end
end

local function performanceOut100(sprite)
	sprite:setPosition(cc.p( -1000, -1000))
end

local function performanceScale(sprite)
	sprite:setPosition(cc.p(math.mod(math.random(1, 99999999), s.width), math.mod(math.random(1, 99999999), s.height)))
    sprite:setScale(math.random() * 100 / 50)
end

-----------------------------------
--  Subtest
-----------------------------------
local subtestNumber = 1
local batchNode  = nil  -- cc.SpriteBatchNode
local parent     = nil  -- cc.Node

local function initWithSubTest(nSubTest, p)
	subtestNumber = nSubTest
	parent = p
	batchNode = nil

	local mgr = cc.Director:getInstance():getTextureCache()
	-- remove all texture
	mgr:removeTexture(mgr:addImage("Images/grossinis_sister1.png"))
    mgr:removeTexture(mgr:addImage("Images/grossini_dance_atlas.png"))
    mgr:removeTexture(mgr:addImage("Images/spritesheet1.png"))

	if subtestNumber == 2 then
		cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
		batchNode = cc.SpriteBatchNode:create("Images/grossinis_sister1.png", 100)
		p:addChild(batchNode, 0)
	elseif subtestNumber == 3 then
		cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
		batchNode = cc.SpriteBatchNode:create("Images/grossinis_sister1.png", 100)
		p:addChild(batchNode, 0)
	elseif subtestNumber == 5 then
		cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
		batchNode = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 100)
		p:addChild(batchNode, 0)
	elseif subtestNumber == 6 then
		cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
		batchNode = cc.SpriteBatchNode:create("Images/grossini_dance_atlas.png", 100)
		p:addChild(batchNode, 0)
	elseif subtestNumber == 8 then
		cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)
		batchNode = cc.SpriteBatchNode:create("Images/spritesheet1.png", 100)
		p:addChild(batchNode, 0)
	elseif subtestNumber == 9 then
		cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A4444)
		batchNode = cc.SpriteBatchNode:create("Images/spritesheet1.png", 100)
		p:addChild(batchNode, 0)
	end

	-- todo
    if batchNode ~= nil then
        batchNode:retain()
    end

    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE_PIXELFORMAT_DEFAULT)
end

local function createSpriteWithTag(tag)
	cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE2_D_PIXEL_FORMAT_RGB_A8888)

    local sprite = nil
    if subtestNumber == 1 then
		sprite = cc.Sprite:create("Images/grossinis_sister1.png")
		parent:addChild(sprite, -1, tag + 100)
	elseif subtestNumber == 2 then
		sprite = cc.Sprite:createWithTexture(batchNode:getTexture(), cc.rect(0, 0, 52, 139))
		batchNode:addChild(sprite, 0, tag + 100)
	elseif subtestNumber == 3 then
		sprite = cc.Sprite:createWithTexture(batchNode:getTexture(), cc.rect(0, 0, 52, 139))
		batchNode:addChild(sprite, 0, tag + 100)
	elseif subtestNumber == 4 then
		local idx = math.floor((math.random() * 1400 / 100)) + 1
		local num
		if idx < 10 then
			num = "0" .. idx
		else
			num = idx
		end
		local str = "Images/grossini_dance_" .. num .. ".png"
		sprite = cc.Sprite:create(str)
		parent:addChild(sprite, -1, tag + 100)
	elseif subtestNumber == 5 then
		local y, x
		local r = math.floor(math.random() * 1400 / 100)
		y = math.floor(r / 5)
        x = math.mod(r, 5)
		x = x * 85
		y = y * 121
		sprite = cc.Sprite:createWithTexture(batchNode:getTexture(), cc.rect(x, y, 85, 121))
		batchNode:addChild(sprite, 0, tag + 100)
	elseif subtestNumber == 6 then
		local y, x
		local r = math.floor(math.random() * 1400 / 100)
		y = math.floor(r / 5)
		x = math.mod(r, 5)
		x = x * 85
		y = y * 121
		sprite = cc.Sprite:createWithTexture(batchNode:getTexture(), cc.rect(x, y, 85, 121))
		batchNode:addChild(sprite, 0, tag + 100)
	elseif subtestNumber == 7 then
		local y, x
		local r = math.floor(math.random() * 6400 / 100)
		y = math.floor(r / 8)
		x = math.mod(r, 8)
		local str = "Images/sprites_test/sprite-"..x.."-"..y..".png"
		sprite = cc.Sprite:create(str)
		parent:addChild(sprite, -1, tag + 100)
	elseif subtestNumber == 8 then
		local y, x
		local r = math.floor(math.random() * 6400 / 100)
		y = math.floor(r / 8)
		x = math.mod(r, 8)
		x = x * 32
		y = y * 32
		sprite = cc.Sprite:createWithTexture(batchNode:getTexture(), cc.rect(x, y, 32, 32))
		batchNode:addChild(sprite, 0, tag + 100)
	elseif subtestNumber == 9 then
		local y, x
		local r = math.floor(math.random() * 6400 / 100)
		y = math.floor(r / 8)
		x = math.mod(r, 8)
		x = x * 32
		y = y * 32
		sprite = cc.Sprite:createWithTexture(batchNode:getTexture(), cc.rect(x, y, 32, 32))
		batchNode:addChild(sprite, 0, tag + 100)
	end

    cc.Texture2D:setDefaultAlphaPixelFormat(cc.TEXTURE_PIXELFORMAT_DEFAULT)

    return sprite
end

local function removeByTag(tag)
	if subtestNumber == 1 then
		parent:removeChildByTag(tag + 100, true)
	elseif subtestNumber == 4 then
		parent:removeChildByTag(tag + 100, true)
	elseif subtestNumber == 7 then
		parent:removeChildByTag(tag + 100, true)
	else
		batchNode:removeChildAtIndex(tag, true)
	end
end

-----------------------------------
--  PerformBasicLayer
-----------------------------------
local curCase  = 0
local maxCases = 7

local function showThisTest()
	local scene = CreateSpriteTestScene()
	cc.Director:getInstance():replaceScene(scene)
end

local function backCallback(sender)
	subtestNumber = 1
	curCase = curCase - 1
	if curCase < 0 then
		curCase = curCase + maxCases
	end
	showThisTest()
end

local function restartCallback(sender)
	subtestNumber = 1
	showThisTest()
end

local function nextCallback(sender)
	subtestNumber = 1
	curCase = curCase + 1
	curCase = math.mod(curCase, maxCases)
	showThisTest()
end

local function toPerformanceMainLayer(sender)
	cc.Director:getInstance():replaceScene(PerformanceTest())
end

local function initWithLayer(layer, controlMenuVisible)
	cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local mainItem = cc.MenuItemFont:create("Back")
	mainItem:registerScriptTapHandler(toPerformanceMainLayer)
    mainItem:setPosition(s.width - 50, 25)
    local menu = cc.Menu:create()
	menu:addChild(mainItem)
    menu:setPosition(cc.p(0, 0))

    if controlMenuVisible == true then
        local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
        local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
        local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
		item1:registerScriptTapHandler(backCallback)
		item2:registerScriptTapHandler(restartCallback)
		item3:registerScriptTapHandler(nextCallback)
        item1:setPosition(s.width / 2 - 100, 30)
        item2:setPosition(s.width / 2, 30)
        item3:setPosition(s.width / 2 + 100, 30)

        menu:addChild(item1, kItemTagBasic)
        menu:addChild(item2, kItemTagBasic)
        menu:addChild(item3, kItemTagBasic)
	end
	layer:addChild(menu)
end

-----------------------------------
--  SpriteMainScene
-----------------------------------
local lastRenderedCount = nil
local quantityNodes     = nil

local infoLabel  = nil
local titleLabel = nil

local function testNCallback(tag)
	subtestNumber = tag - kBasicZOrder
	showThisTest()
end

local function updateNodes()
	if quantityNodes ~= lastRenderedCount then
		local str = quantityNodes .. " nodes"
        infoLabel:setString(str)
        lastRenderedCount = quantityNodes
    end
end

local function onDecrease(sender)
	if quantityNodes <= 0 then
        return
	end

    for i = 0, kNodesIncrease - 1 do
        quantityNodes = quantityNodes - 1
        removeByTag(quantityNodes)
	end
    updateNodes()
end

local function onIncrease(sender)
	if quantityNodes >= kMaxNodes then
        return
	end

    for i = 0, kNodesIncrease - 1 do
        local sprite = createSpriteWithTag(quantityNodes)

		if curCase == 0 then
			doPerformSpriteTest1(sprite)
		elseif curCase == 1 then
			doPerformSpriteTest2(sprite)
		elseif curCase == 2 then
			doPerformSpriteTest3(sprite)
		elseif curCase == 3 then
			doPerformSpriteTest4(sprite)
		elseif curCase == 4 then
			doPerformSpriteTest5(sprite)
		elseif curCase == 5 then
			doPerformSpriteTest6(sprite)
		elseif curCase == 6 then
			doPerformSpriteTest7(sprite)
		end

		quantityNodes = quantityNodes + 1
    end

    updateNodes()
end

local function initWithMainTest(scene, asubtest, nNodes)
	subtestNumber = asubtest
    initWithSubTest(asubtest, scene)

    lastRenderedCount = 0
    quantityNodes = 0

    cc.MenuItemFont:setFontSize(65)
    local decrease = cc.MenuItemFont:create(" - ")
	decrease:registerScriptTapHandler(onDecrease)
    decrease:setColor(cc.c3b(0, 200, 20))
    local increase = cc.MenuItemFont:create(" + ")
	increase:registerScriptTapHandler(onIncrease)
    increase:setColor(cc.c3b(0, 200, 20))

    local menu = cc.Menu:create()
	menu:addChild(decrease)
	menu:addChild(increase)
    menu:alignItemsHorizontally()
    menu:setPosition(s.width / 2, s.height - 65)
    scene:addChild(menu, 1)

    infoLabel = cc.Label:createWithTTF("0 nodes", s_markerFeltFontPath, 30)
    infoLabel:setColor(cc.c3b(0, 200, 20))
    infoLabel:setAnchorPoint(cc.p(0.5, 0.5))
    infoLabel:setPosition(s.width / 2, s.height - 90)
    scene:addChild(infoLabel, 1)

	maxCases = TEST_COUNT

    --  Sub Tests
    cc.MenuItemFont:setFontSize(32)
    subMenu = cc.Menu:create()
    for i = 1, 9 do
		local str = i .. " "
        local itemFont = cc.MenuItemFont:create(str)
		itemFont:registerScriptTapHandler(testNCallback)
        --itemFont:setTag(i)
        subMenu:addChild(itemFont, kBasicZOrder + i, kBasicZOrder + i)

        if i <= 3 then
            itemFont:setColor(cc.c3b(200, 20, 20))
        elseif i <= 6 then
            itemFont:setColor(cc.c3b(0, 200, 20))
        else
            itemFont:setColor(cc.c3b(0, 20, 200))
		end
	end

    subMenu:alignItemsHorizontally()
    subMenu:setPosition(cc.p(s.width / 2, 80))
    scene:addChild(subMenu, 1)

    --  add title label
    titleLabel = cc.Label:createWithTTF("No title", s_arialPath, 40)
    scene:addChild(titleLabel, 1)
    titleLabel:setAnchorPoint(cc.p(0.5, 0.5))
    titleLabel:setPosition(s.width / 2, s.height - 32)
    titleLabel:setColor(cc.c3b(255, 255, 40))

    while quantityNodes < nNodes do
        onIncrease()
	end
end

-----------------------------------
--  SpritePerformTest1
-----------------------------------
function doPerformSpriteTest1(sprite)
	performancePosition(sprite)
end

local function SpriteTestLayer1()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "A (" .. subtestNumber .. ") position"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  SpritePerformTest2
-----------------------------------
function doPerformSpriteTest2(sprite)
	performanceScale(sprite)
end

local function SpriteTestLayer2()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "B (" .. subtestNumber .. ") scale"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  SpritePerformTest3
-----------------------------------
function doPerformSpriteTest3(sprite)
	performanceRotationScale(sprite)
end

local function SpriteTestLayer3()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "C (" .. subtestNumber .. ") scale + rot"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  SpritePerformTest4
-----------------------------------
function doPerformSpriteTest4(sprite)
	performanceOut100(sprite)
end

local function SpriteTestLayer4()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "D (" .. subtestNumber .. ") 100% out"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  SpritePerformTest5
-----------------------------------
function doPerformSpriteTest5(sprite)
	performanceout20(sprite)
end

local function SpriteTestLayer5()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "E (" .. subtestNumber .. ") 80% out"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  SpritePerformTest6
-----------------------------------
function doPerformSpriteTest6(sprite)
	performanceActions(sprite)
end

local function SpriteTestLayer6()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "F (" .. subtestNumber .. ") actions"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  SpritePerformTest7
-----------------------------------
function doPerformSpriteTest7(sprite)
	performanceActions20(sprite)
end

local function SpriteTestLayer7()
	local layer = cc.Layer:create()
	initWithLayer(layer, true)

	local str = "G (" .. subtestNumber .. ") actions 80% out"
	titleLabel:setString(str)

	return layer
end

-----------------------------------
--  PerformanceSpriteTest
-----------------------------------
function CreateSpriteTestScene()
	local scene = cc.Scene:create()
	initWithMainTest(scene, subtestNumber, kNodesIncrease)

	if curCase == 0 then
		scene:addChild(SpriteTestLayer1())
	elseif curCase == 1 then
		scene:addChild(SpriteTestLayer2())
	elseif curCase == 2 then
		scene:addChild(SpriteTestLayer3())
	elseif curCase == 3 then
		scene:addChild(SpriteTestLayer4())
	elseif curCase == 4 then
		scene:addChild(SpriteTestLayer5())
	elseif curCase == 5 then
		scene:addChild(SpriteTestLayer6())
	elseif curCase == 6 then
		scene:addChild(SpriteTestLayer7())
	end

	return scene
end

function PerformanceSpriteTest()
	curCase = 0

	return CreateSpriteTestScene()
end
