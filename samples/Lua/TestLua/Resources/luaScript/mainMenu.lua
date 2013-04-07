require "luaScript/tests"
require "luaScript/helper"
require "luaScript/testResource"
------------------------


local LINE_SPACE = 40

local CurPos = {x = 0, y = 0}
local BeginPos = {x = 0, y = 0}


local _allTests = {
    { name = "ActionsTest"            , create_func   =               ActionsTest      },
    { name = "TransitionsTest"        , create_func   =           TransitionsTest      },
    { name = "ActionsProgressTest"    , create_func   =       ProgressActionsTest      },
    { name = "EffectsTest"            , create_func   =               EffectsTest      },
    { name = "ClickAndMoveTest"       , create_func   =          ClickAndMoveTest      },
    { name = "RotateWorldTest"        , create_func   =           RotateWorldTest      },
    { name = "ParticleTest"           , create_func   =              ParticleTest      },
    { name = "ActionsEaseTest"        , create_func   =           EaseActionsTest      },
    { name = "MotionStreakTest"       , create_func   =          MotionStreakTest      },
  --{ name = "DrawPrimitivesTest"     , create_func=        DrawPrimitivesTest      },
    { name = "NodeTest"               , create_func   =                  CocosNodeTest },
    { name = "TouchesTest"            , create_func   =               TouchesTest      },
    { name = "MenuTest"               , create_func   =                  MenuTestMain  },
    { name = "ActionManagerTest"      , create_func   =         ActionManagerTestMain  },
    { name = "LayerTest"              , create_func   =                 LayerTestMain  },
    { name = "SceneTest"              , create_func   =                 SceneTestMain  },
    { name = "ParallaxTest"           , create_func   =              ParallaxTestMain  },
    { name = "TileMapTest"            , create_func   =               TileMapTestMain  },
    { name = "IntervalTest"           , create_func   =              IntervalTestMain  },
  --{ name = "ChipmunkAccelTouchTest" , create_func=    ChipmunkAccelTouchTestMain  },
    { name = "LabelTest"              , create_func   =                 LabelTest      },
  --{ name = "TextInputTest"          , create_func=             TextInputTestMain  },
    { name = "SpriteTest"             , create_func   =                SpriteTest      },
  --{ name = "SchdulerTest"           , create_func=              SchdulerTestMain  },
    { name = "RenderTextureTest"      , create_func   =         RenderTextureTestMain  },
    { name = "Texture2DTest"          , create_func   =             Texture2dTestMain  },
  --{ name = "Box2dTest"              , create_func=                 Box2dTestMain  },
  --{ name = "Box2dTestBed"           , create_func=              Box2dTestBedMain  },
    { name = "EffectAdvancedTest"     , create_func   =        EffectAdvancedTestMain  },
  --{ name = "Accelerometer"          , create_func=             AccelerometerMain  },
  --{ name = "KeypadTest"             , create_func=                KeypadTestMain  },
    { name = "CocosDenshionTest"      , create_func   =         CocosDenshionTestMain  },
  --{ name = "PerformanceTest"        , create_func=           PerformanceTestMain  },
    { name = "ZwoptexTest"            , create_func   =               ZwoptexTestMain  },
  --{ name = "CurlTest"               , create_func=                  CurlTestMain  },
  --{ name = "UserDefaultTest"        , create_func=           UserDefaultTestMain  },
  --{ name = "BugsTest"               , create_func=              BugsTestMain      },
    { name = "FontTest"               , create_func   =              FontTestMain      },
  --{ name = "CurrentLanguageTest"    , create_func=   CurrentLanguageTestMain      },
  --{ name = "TextureCacheTest"       , create_func=      TextureCacheTestMain      },
  --{ name = "ExtensionsTest"         , create_func=        ExtensionsTestMain      },
  --{ name = "ShaderTest"             , create_func=            ShaderTestMain      },
  --{ name = "MutiTouchTest"          , create_func=          MutiTouchTestMain          }
}

-- create scene
local function CreateTestScene(nIdx)
    local scene = _allTests[nIdx].create_func()
    CCDirector:sharedDirector():purgeCachedData()
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
    local index = 0
    local obj = nil
    for index, obj in pairs(_allTests) do
        local testLabel = CCLabelTTF:create(obj.name, "Arial", 24)
        local testMenuItem = CCMenuItemLabel:create(testLabel)

        testMenuItem:registerScriptTapHandler(menuCallback)
        testMenuItem:setPosition(ccp(s.width / 2, (s.height - (index) * LINE_SPACE)))
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
