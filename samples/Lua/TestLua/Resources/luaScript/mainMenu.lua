require "luaScript/tests"
require "luaScript/helper"
require "luaScript/testResource"
------------------------


local LINE_SPACE = 40

local CurPos = {x = 0, y = 0}
local BeginPos = {x = 0, y = 0}

-- create scene
local function CreateTestScene(nIdx)
	CCDirector:sharedDirector():purgeCachedData()

	local scene = nil
	if nIdx == Test_Table.TEST_ACTIONS then
		scene = ActionsTest()
	elseif nIdx == Test_Table.TEST_TRANSITIONS then
		scene = TransitionsTest()
	elseif nIdx == Test_Table.TEST_PROGRESS_ACTIONS then
		scene = ProgressActionsTest()
    elseif nIdx == Test_Table.TEST_EFFECTS then
		scene = EffectsTest()
    elseif nIdx == Test_Table.TEST_CLICK_AND_MOVE then
		scene = ClickAndMoveTest()
    elseif nIdx == Test_Table.TEST_ROTATE_WORLD then
		scene = RotateWorldTest()
    elseif nIdx == Test_Table.TEST_PARTICLE then
		scene = ParticleTest()
    elseif nIdx == Test_Table.TEST_EASE_ACTIONS then
		scene = EaseActionsTest()
    elseif nIdx == Test_Table.TEST_MOTION_STREAK then
		scene = MotionStreakTest()
    elseif nIdx == Test_Table.TEST_DRAW_PRIMITIVES then
		scene = DrawPrimitivesTest()
    elseif nIdx == Test_Table.TEST_COCOSNODE then
		scene = CocosNodeTest()
    elseif nIdx == Test_Table.TEST_TOUCHES then
		scene = TouchesTest()
    elseif nIdx == Test_Table.TEST_MENU then
		scene = MenuTest()
    elseif nIdx == Test_Table.TEST_ACTION_MANAGER then
		scene = ActionManagerTest()
    elseif nIdx == Test_Table.TEST_LAYER then
		scene = LayerTest()
    elseif nIdx == Test_Table.TEST_SCENE then
		scene = SceneTest()
    elseif nIdx == Test_Table.TEST_PARALLAX then
		scene = ParallaxTest()
    elseif nIdx == Test_Table.TEST_TILE_MAP then
		scene = TileMapTest()
    elseif nIdx == Test_Table.TEST_INTERVAL then
		scene = IntervalTest()
    elseif nIdx == Test_Table.TEST_CHIPMUNKACCELTOUCH then
--#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
--        pScene = new ChipmunkAccelTouchTestScene()
--#else
--#ifdef MARMALADEUSECHIPMUNK
--#if    (MARMALADEUSECHIPMUNK == 1)
--        pScene = new ChipmunkAccelTouchTestScene();
--#endif
--        break;
--#endif
--#endif
    elseif nIdx == Test_Table.TEST_LABEL then
        scene = LabelTest()
    elseif nIdx == Test_Table.TEST_TEXT_INPUT then

    elseif nIdx == Test_Table.TEST_SPRITE then
        scene = SpriteTest()

    elseif nIdx == Test_Table.TEST_SCHEDULER then

    elseif nIdx == Test_Table.TEST_RENDERTEXTURE then

    elseif nIdx == Test_Table.TEST_TEXTURE2D then

    elseif nIdx == Test_Table.TEST_BOX2D then

    elseif nIdx == Test_Table.TEST_BOX2DBED then

    elseif nIdx == Test_Table.TEST_EFFECT_ADVANCE then

    elseif nIdx == Test_Table.TEST_ACCELEROMRTER then

--#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
--    elseif nIdx == Test_Table.TEST_KEYPAD then
--        pScene = new KeypadTestScene()
--#endif
    elseif nIdx == Test_Table.TEST_COCOSDENSHION then

    elseif nIdx == Test_Table.TEST_PERFORMANCE then
		scene = PerformanceTest()
    elseif nIdx == Test_Table.TEST_ZWOPTEX then

--#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
-- bada don't support libcurl
--#if (CC_TARGET_PLATFORM != CC_PLATFORM_BADA)
--   elseif nIdx == Test_Table.TEST_CURL then

--#endif
--#endif
    elseif nIdx == Test_Table.TEST_USERDEFAULT then

    elseif nIdx == Test_Table.TEST_BUGS then

    elseif nIdx == Test_Table.TEST_FONTS then

    elseif nIdx == Test_Table.TEST_CURRENT_LANGUAGE then

--#if (CC_TARGET_PLATFORM != CC_PLATFORM_MARMALADE)
--   elseif nIdx == Test_Table.TEST_TEXTURECACHE then pScene = new TextureCacheTestScene()
--#endif
    elseif nIdx == Test_Table.TEST_EXTENSIONS then

    elseif nIdx == Test_Table.TEST_SHADER then

    elseif nIdx == Test_Table.TEST_MUTITOUCH then

	end

	return scene
end

-- create menu
function CreateTestMenu()
	local menuLayer = CCLayer:create()

	local function closeCallback()
		CCDirector:sharedDirector():endToLua()
	end

	local function menuCallback(tag)
        print(tag)
		local Idx = tag - 10000
		local testScene = CreateTestScene(Idx)
		if testScene then
			CCDirector:sharedDirector():replaceScene(testScene)
		end
	end

	-- add close menu
	local s = CCDirector:sharedDirector():getWinSize()
	local CloseItem = CCMenuItemImage:create(s_pPathClose, s_pPathClose)
	CloseItem:registerScriptTapHandler(closeCallback)
	CloseItem:setPosition(ccp(s.width - 30, s.height - 30))

    local CloseMenu = CCMenu:create()
    CloseMenu:setPosition(0, 0)
	CloseMenu:addChild(CloseItem)
	menuLayer:addChild(CloseMenu)

	-- add menu items for tests
    local MainMenu = CCMenu:create()
    for index, labelName in pairs(Test_Name) do
		local testLabel = CCLabelTTF:create(labelName, "Arial", 24)
        local testMenuItem = CCMenuItemLabel:create(testLabel)

		testMenuItem:registerScriptTapHandler(menuCallback)
		testMenuItem:setPosition(ccp(s.width / 2, (s.height - (index + 1) * LINE_SPACE)))
        MainMenu:addChild(testMenuItem, index + 10000, index + 10000)
    end

    MainMenu:setContentSize(CCSizeMake(s.width, (Test_Table.TESTS_COUNT + 1) * (LINE_SPACE)))
	MainMenu:setPosition(CurPos.x, CurPos.y)
	menuLayer:addChild(MainMenu)

	-- handling touch events
    local function onTouchBegan(x, y)
		BeginPos = {x = x, y = y}
        -- CCTOUCHBEGAN event must return true
        return true
    end

    local function onTouchMoved(x, y)
        local nMoveY = y - BeginPos.y
		local curPosx, curPosy = MainMenu:getPosition()
		local nextPosy = curPosy + nMoveY
		local winSize = CCDirector:sharedDirector():getWinSize()
		if nextPosy < 0 then
			MainMenu:setPosition(0, 0)
			return
		end

		if nextPosy > ((Test_Table.TESTS_COUNT + 1) * LINE_SPACE - winSize.height) then
			MainMenu:setPosition(0, ((Test_Table.TESTS_COUNT + 1) * LINE_SPACE - winSize.height))
			return
		end

		MainMenu:setPosition(curPosx, nextPosy)
		BeginPos = {x = x, y = y}
		CurPos = {x = curPosx, y = nextPosy}
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return onTouchBegan(x, y)
        elseif eventType == "moved" then
            return onTouchMoved(x, y)
        end
    end

	menuLayer:setTouchEnabled(true)
    menuLayer:registerScriptTouchHandler(onTouch)

    return menuLayer
end
