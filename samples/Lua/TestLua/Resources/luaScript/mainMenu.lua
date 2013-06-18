require "luaScript/helper"
require "luaScript/testResource"

require "luaScript/ActionsTest/ActionsTest"
require "luaScript/TransitionsTest/TransitionsTest"
require "luaScript/ActionsProgressTest/ActionsProgressTest"
require "luaScript/EffectsTest/EffectsTest"
require "luaScript/ClickAndMoveTest/ClickAndMoveTest"
require "luaScript/RotateWorldTest/RotateWorldTest"
require "luaScript/ParticleTest/ParticleTest"
require "luaScript/ActionsEaseTest/ActionsEaseTest"
require "luaScript/MotionStreakTest/MotionStreakTest"
require "luaScript/DrawPrimitivesTest/DrawPrimitivesTest"
require "luaScript/NodeTest/NodeTest"
require "luaScript/TouchesTest/TouchesTest"
require "luaScript/SpriteTest/SpriteTest"
require "luaScript/LayerTest/LayerTest"
require "luaScript/PerformanceTest/PerformanceTest"
require "luaScript/LabelTest/LabelTest"
require "luaScript/ParallaxTest/ParallaxTest"
require "luaScript/TileMapTest/TileMapTest"
require "luaScript/ActionManagerTest/ActionManagerTest"
require "luaScript/MenuTest/MenuTest"
require "luaScript/IntervalTest/IntervalTest"
require "luaScript/SceneTest/SceneTest"
require "luaScript/Texture2dTest/Texture2dTest"
require "luaScript/RenderTextureTest/RenderTextureTest"
require "luaScript/ZwoptexTest/ZwoptexTest"
require "luaScript/FontTest/FontTest"
require "luaScript/CocosDenshionTest/CocosDenshionTest"
require "luaScript/EffectsAdvancedTest/EffectsAdvancedTest"
require "luaScript/UserDefaultTest/UserDefaultTest"
require "luaScript/CurrentLanguageTest/CurrentLanguageTest"
require "luaScript/BugsTest/BugsTest"
require "luaScript/ExtensionTest/ExtensionTest"
require "luaScript/AccelerometerTest/AccelerometerTest"
require "luaScript/KeypadTest/KeypadTest"


local LINE_SPACE = 40

local CurPos = {x = 0, y = 0}
local BeginPos = {x = 0, y = 0}


local _allTests = {
    { isSupported = true,  name = "ActionsTest"            , create_func   =               ActionsTest      },
    { isSupported = true,  name = "TransitionsTest"        , create_func   =           TransitionsTest      },
    { isSupported = true,  name = "ActionsProgressTest"    , create_func   =       ProgressActionsTest      },
    { isSupported = true,  name = "EffectsTest"            , create_func   =               EffectsTest      },
    { isSupported = true,  name = "ClickAndMoveTest"       , create_func   =          ClickAndMoveTest      },
    { isSupported = true,  name = "RotateWorldTest"        , create_func   =           RotateWorldTest      },
    { isSupported = true,  name = "ParticleTest"           , create_func   =              ParticleTest      },
    { isSupported = true,  name = "ActionsEaseTest"        , create_func   =           EaseActionsTest      },
    { isSupported = true,  name = "MotionStreakTest"       , create_func   =          MotionStreakTest      },
    { isSupported = false,  name = "DrawPrimitivesTest"     , create_func=        DrawPrimitivesTest      },
    { isSupported = true,  name = "NodeTest"               , create_func   =                  CocosNodeTest },
    { isSupported = true,  name = "TouchesTest"            , create_func   =               TouchesTest      },
    --Many tests in MenuTest will crash, so disable it. Should enable it after all crashes are resolved.
    { isSupported = true,  name = "MenuTest"               , create_func   =                  MenuTestMain  },
    { isSupported = true,  name = "ActionManagerTest"      , create_func   =         ActionManagerTestMain  },
    { isSupported = true,  name = "LayerTest"              , create_func   =                 LayerTestMain  },
    { isSupported = true,  name = "SceneTest"              , create_func   =                 SceneTestMain  },
    { isSupported = true,  name = "ParallaxTest"           , create_func   =              ParallaxTestMain  },
    { isSupported = true,  name = "TileMapTest"            , create_func   =               TileMapTestMain  },
    { isSupported = true,  name = "IntervalTest"           , create_func   =              IntervalTestMain  },
    { isSupported = false,  name = "ChipmunkAccelTouchTest" , create_func=    ChipmunkAccelTouchTestMain  },
    { isSupported = true,  name = "LabelTest"              , create_func   =                 LabelTest      },
    { isSupported = false,  name = "TextInputTest"          , create_func=             TextInputTestMain  },
    { isSupported = true,  name = "SpriteTest"             , create_func   =                SpriteTest      },
    { isSupported = false,  name = "SchdulerTest"           , create_func=              SchdulerTestMain  },
    { isSupported = true,  name = "RenderTextureTest"      , create_func   =         RenderTextureTestMain  },
    { isSupported = true,  name = "Texture2DTest"          , create_func   =             Texture2dTestMain  },
    { isSupported = false,  name = "Box2dTest"              , create_func=                 Box2dTestMain  },
    { isSupported = false,  name = "Box2dTestBed"           , create_func=              Box2dTestBedMain  },
    { isSupported = true,  name = "EffectAdvancedTest"     , create_func   =        EffectAdvancedTestMain  },
    { isSupported = true,  name = "Accelerometer"          , create_func=             AccelerometerMain  },
    { isSupported = true,  name = "KeypadTest"             , create_func=                KeypadTestMain  },
    { isSupported = true,  name = "CocosDenshionTest"      , create_func   =         CocosDenshionTestMain  },
    { isSupported = true,  name = "PerformanceTest"        , create_func=           PerformanceTestMain  },
    { isSupported = true,  name = "ZwoptexTest"            , create_func   =               ZwoptexTestMain  },
    { isSupported = false,  name = "CurlTest"               , create_func=                  CurlTestMain  },
    { isSupported = true,  name = "UserDefaultTest"        , create_func=           UserDefaultTestMain  },
    { isSupported = true,  name = "BugsTest"               , create_func=              BugsTestMain      },
    { isSupported = true,  name = "FontTest"               , create_func   =              FontTestMain      },
    { isSupported = true,  name = "CurrentLanguageTest"    , create_func=   CurrentLanguageTestMain      },
    { isSupported = false,  name = "TextureCacheTest"       , create_func=      TextureCacheTestMain      },
    { isSupported = true,  name = "ExtensionsTest"         , create_func=        ExtensionsTestMain      },
    { isSupported = false,  name = "ShaderTest"             , create_func=            ShaderTestMain      },
    { isSupported = false,  name = "MutiTouchTest"          , create_func=          MutiTouchTestMain     }
}

local TESTS_COUNT = table.getn(_allTests)

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
        if not obj.isSupported then
            testMenuItem:setEnabled(false)
        end
        testMenuItem:registerScriptTapHandler(menuCallback)
        testMenuItem:setPosition(ccp(s.width / 2, (s.height - (index) * LINE_SPACE)))
        MainMenu:addChild(testMenuItem, index + 10000, index + 10000)
    end

    MainMenu:setContentSize(CCSizeMake(s.width, (TESTS_COUNT + 1) * (LINE_SPACE)))
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

        if nextPosy > ((TESTS_COUNT + 1) * LINE_SPACE - winSize.height) then
            MainMenu:setPosition(0, ((TESTS_COUNT + 1) * LINE_SPACE - winSize.height))
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
