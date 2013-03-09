require "luaScript/PerformanceTest/PerformanceSpriteTest"

local MAX_COUNT     = 1
local LINE_SPACE    = 40
local kItemTagBasic = 1000

local testsName =
{
	[0] = "PerformanceSpriteTest",
    "PerformanceParticleTest",
    "PerformanceNodeChildrenTest",
    "PerformanceTextureTest",
    "PerformanceTouchesTest"
}

local s = CCDirector:sharedDirector():getWinSize()

----------------------------------
--  PerformanceMainLayer
----------------------------------
local function menuCallback(tag)
	local scene = nil
--  tag = tag - kItemTagBasic

	if tag == "enter" then
		scene = PerformanceSpriteTest()
	elseif tag == 1 then

	elseif tag == 2 then

	elseif tag == 3 then

	elseif tag == 4 then

	end
	if scene ~= nil then
		CCDirector:sharedDirector():replaceScene(scene)
	end
end

local function PerformanceMainLayer()
	local layer = CCLayer:create()

	local menu = CCMenu:create()
    menu:setPosition(CCPointMake(0, 0))
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    for i = 0, MAX_COUNT - 1 do
		local item = CCMenuItemFont:create(testsName[i])
        item:registerScriptTapHandler(menuCallback)
        item:setPosition(s.width / 2, s.height - (i + 1) * LINE_SPACE)
        menu:addChild(item, kItemTagBasic + i, kItemTagBasic + i)
	end

    layer:addChild(menu)

	return layer
end

-------------------------------------
--  Performance Test
-------------------------------------
function PerformanceTest()
	local scene = CCScene:create()

	scene:addChild(PerformanceMainLayer())
	scene:addChild(CreateBackMenuItem())

	return scene
end
