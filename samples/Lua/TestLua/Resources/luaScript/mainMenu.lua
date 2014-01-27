require "Cocos2d"
require "Cocos2dConstants"
require "Opengl"
require "OpenglConstants"
require "StudioConstants"
require "GuiConstants"
require "luaScript/helper"
require "luaScript/testResource"
require "luaScript/VisibleRect"

require "luaScript/AccelerometerTest/AccelerometerTest"
require "luaScript/ActionManagerTest/ActionManagerTest"
require "luaScript/ActionsEaseTest/ActionsEaseTest"
require "luaScript/ActionsProgressTest/ActionsProgressTest"
require "luaScript/ActionsTest/ActionsTest"
require "luaScript/AssetsManagerTest/AssetsManagerTest"
require "luaScript/BugsTest/BugsTest"
require "luaScript/ClickAndMoveTest/ClickAndMoveTest"
require "luaScript/CocosDenshionTest/CocosDenshionTest"
require "luaScript/CocoStudioTest/CocoStudioTest"
require "luaScript/CurrentLanguageTest/CurrentLanguageTest"
require "luaScript/DrawPrimitivesTest/DrawPrimitivesTest"
require "luaScript/EffectsTest/EffectsTest"
require "luaScript/EffectsAdvancedTest/EffectsAdvancedTest"
require "luaScript/ExtensionTest/ExtensionTest"
require "luaScript/FontTest/FontTest"
require "luaScript/IntervalTest/IntervalTest"
require "luaScript/KeypadTest/KeypadTest"
require "luaScript/LabelTest/LabelTest"
require "luaScript/LabelTestNew/LabelTestNew"
require "luaScript/LayerTest/LayerTest"
require "luaScript/MenuTest/MenuTest"
require "luaScript/MotionStreakTest/MotionStreakTest"
require "luaScript/NewEventDispatcherTest/NewEventDispatcherTest"
require "luaScript/NodeTest/NodeTest"
require "luaScript/OpenGLTest/OpenGLTest"
require "luaScript/ParallaxTest/ParallaxTest"
require "luaScript/ParticleTest/ParticleTest"
require "luaScript/PerformanceTest/PerformanceTest"
require "luaScript/RenderTextureTest/RenderTextureTest"
require "luaScript/RotateWorldTest/RotateWorldTest"
require "luaScript/SpriteTest/SpriteTest"
require "luaScript/SceneTest/SceneTest"
require "luaScript/SpineTest/SpineTest"
require "luaScript/Texture2dTest/Texture2dTest"
require "luaScript/TileMapTest/TileMapTest"
require "luaScript/TouchesTest/TouchesTest"
require "luaScript/TransitionsTest/TransitionsTest"
require "luaScript/UserDefaultTest/UserDefaultTest"
require "luaScript/ZwoptexTest/ZwoptexTest"
require "luaScript/LuaBridgeTest/LuaBridgeTest"
require "luaScript/XMLHttpRequestTest/XMLHttpRequestTest"
require "luaScript/PhysicsTest/PhysicsTest"


local LINE_SPACE = 40

local CurPos = {x = 0, y = 0}
local BeginPos = {x = 0, y = 0}


local _allTests = {
    { isSupported = true,  name = "Accelerometer"          , create_func=             AccelerometerMain  },
    { isSupported = true,  name = "ActionManagerTest"      , create_func   =         ActionManagerTestMain  },
    { isSupported = true,  name = "ActionsEaseTest"        , create_func   =           EaseActionsTest      },
    { isSupported = true,  name = "ActionsProgressTest"    , create_func   =       ProgressActionsTest      },
    { isSupported = true,  name = "ActionsTest"            , create_func   =               ActionsTest      },
    { isSupported = true,  name = "AssetsManagerTest"      , create_func   =         AssetsManagerTestMain      },
    { isSupported = false,  name = "Box2dTest"              , create_func=                 Box2dTestMain  },
    { isSupported = false,  name = "Box2dTestBed"           , create_func=              Box2dTestBedMain  },
    { isSupported = true,  name = "BugsTest"               , create_func=              BugsTestMain      },
    { isSupported = false,  name = "ChipmunkAccelTouchTest" , create_func=    ChipmunkAccelTouchTestMain  },
    { isSupported = true,  name = "ClickAndMoveTest"       , create_func   =          ClickAndMoveTest      },
    { isSupported = true,  name = "CocosDenshionTest"      , create_func   =         CocosDenshionTestMain  },
    { isSupported = true,  name = "CocoStudioTest"         , create_func   =         CocoStudioTestMain  },  
    { isSupported = false,  name = "CurlTest"               , create_func=                  CurlTestMain  },
    { isSupported = true,  name = "CurrentLanguageTest"    , create_func=   CurrentLanguageTestMain      },
    { isSupported = true,  name = "DrawPrimitivesTest"     , create_func=        DrawPrimitivesTest      },
    { isSupported = true,  name = "EffectsTest"            , create_func   =               EffectsTest      },
    { isSupported = true,  name = "EffectAdvancedTest"     , create_func   =        EffectAdvancedTestMain  },
    { isSupported = true,  name = "ExtensionsTest"         , create_func=        ExtensionsTestMain      },
    { isSupported = true,  name = "FontTest"               , create_func   =              FontTestMain      },
    { isSupported = true,  name = "IntervalTest"           , create_func   =              IntervalTestMain  },
    { isSupported = true,  name = "KeypadTest"             , create_func=                KeypadTestMain  }, 
    { isSupported = true,  name = "LabelTest"              , create_func   =                 LabelTest      },
    { isSupported = true,  name = "LabelTestNew"           , create_func   =                 LabelTestNew      },
    { isSupported = true,  name = "LayerTest"              , create_func   =                 LayerTestMain  },
    { isSupported = true,  name = "LuaBridgeTest"          , create_func   =        LuaBridgeMainTest },
    { isSupported = true,  name = "MenuTest"               , create_func   =                  MenuTestMain  }, 
    { isSupported = true,  name = "MotionStreakTest"       , create_func   =          MotionStreakTest      },
    { isSupported = false,  name = "MutiTouchTest"          , create_func=          MutiTouchTestMain     },
    { isSupported = true,  name = "NewEventDispatcherTest"  , create_func   =       NewEventDispatcherTest },
    { isSupported = true,  name = "NodeTest"               , create_func   =                  CocosNodeTest },
    { isSupported = true,   name = "OpenGLTest"             , create_func=          OpenGLTestMain     },
    { isSupported = true,  name = "ParallaxTest"           , create_func   =              ParallaxTestMain  },
    { isSupported = true,  name = "ParticleTest"           , create_func   =              ParticleTest      }, 
    { isSupported = true,  name = "PerformanceTest"        , create_func=           PerformanceTestMain  },
	{ isSupported = true,  name = "PhysicsTest"            , create_func =          PhysicsTest  },
    { isSupported = true,  name = "RenderTextureTest"      , create_func   =         RenderTextureTestMain  },
    { isSupported = true,  name = "RotateWorldTest"        , create_func   =           RotateWorldTest      },
    { isSupported = true,  name = "SceneTest"              , create_func   =                 SceneTestMain  },
    { isSupported = true,  name = "SpineTest"              , create_func   =                 SpineTestMain  },
    { isSupported = false,  name = "SchdulerTest"           , create_func=              SchdulerTestMain  },
    { isSupported = false,  name = "ShaderTest"             , create_func=            ShaderTestMain      },
    { isSupported = true,  name = "SpriteTest"             , create_func   =                SpriteTest      },
    { isSupported = false,  name = "TextInputTest"          , create_func=             TextInputTestMain  },
    { isSupported = true,  name = "Texture2DTest"          , create_func   =             Texture2dTestMain  },
    { isSupported = false,  name = "TextureCacheTest"       , create_func=      TextureCacheTestMain      },
    { isSupported = true,  name = "TileMapTest"            , create_func   =               TileMapTestMain  }, 
    { isSupported = true,  name = "TouchesTest"            , create_func   =               TouchesTest      },
    { isSupported = true,  name = "TransitionsTest"        , create_func   =           TransitionsTest      },   
    { isSupported = true,  name = "UserDefaultTest"        , create_func=           UserDefaultTestMain  },
    { isSupported = true,  name = "XMLHttpRequestTest"     , create_func   =        XMLHttpRequestTestMain  },
    { isSupported = true,  name = "ZwoptexTest"            , create_func   =               ZwoptexTestMain  }
}

local TESTS_COUNT = table.getn(_allTests)

-- create scene
local function CreateTestScene(nIdx)
    cc.Director:getInstance():purgeCachedData()
    local scene = _allTests[nIdx].create_func()
    return scene
end
-- create menu
function CreateTestMenu()
    local menuLayer = cc.Layer:create()

    local function closeCallback()
        cc.Director:getInstance():endToLua()
    end

    local function menuCallback(tag)
        print(tag)
        local Idx = tag - 10000
        local testScene = CreateTestScene(Idx)
        if testScene then
            cc.Director:getInstance():replaceScene(testScene)
        end
    end

    -- add close menu
    local s = cc.Director:getInstance():getWinSize()
    local CloseItem = cc.MenuItemImage:create(s_pPathClose, s_pPathClose)
    CloseItem:registerScriptTapHandler(closeCallback)
    CloseItem:setPosition(cc.p(s.width - 30, s.height - 30))

    local CloseMenu = cc.Menu:create()
    CloseMenu:setPosition(0, 0)
    CloseMenu:addChild(CloseItem)
    menuLayer:addChild(CloseMenu)

    -- add menu items for tests
    local MainMenu = cc.Menu:create()
    local index = 0
    local obj = nil
    for index, obj in pairs(_allTests) do
        local testLabel = cc.LabelTTF:create(obj.name, "Arial", 24)
        local testMenuItem = cc.MenuItemLabel:create(testLabel)
        if not obj.isSupported then
            testMenuItem:setEnabled(false)
        end
        testMenuItem:registerScriptTapHandler(menuCallback)
        testMenuItem:setPosition(cc.p(s.width / 2, (s.height - (index) * LINE_SPACE)))
        MainMenu:addChild(testMenuItem, index + 10000, index + 10000)
    end

    MainMenu:setContentSize(cc.size(s.width, (TESTS_COUNT + 1) * (LINE_SPACE)))
    MainMenu:setPosition(CurPos.x, CurPos.y)
    menuLayer:addChild(MainMenu)

    -- handling touch events
    local function onTouchBegan(touch, event)
        BeginPos = touch:getLocation()
        -- CCTOUCHBEGAN event must return true
        return true
    end

    local function onTouchMoved(touch, event)
        local location = touch:getLocation()
        local nMoveY = location.y - BeginPos.y
        local curPosx, curPosy = MainMenu:getPosition()
        local nextPosy = curPosy + nMoveY
        local winSize = cc.Director:getInstance():getWinSize()
        if nextPosy < 0 then
            MainMenu:setPosition(0, 0)
            return
        end

        if nextPosy > ((TESTS_COUNT + 1) * LINE_SPACE - winSize.height) then
            MainMenu:setPosition(0, ((TESTS_COUNT + 1) * LINE_SPACE - winSize.height))
            return
        end

        MainMenu:setPosition(curPosx, nextPosy)
        BeginPos = {x = location.x, y = location.y}
        CurPos = {x = curPosx, y = nextPosy}
    end

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:registerScriptHandler(onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    local eventDispatcher = menuLayer:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, menuLayer)

    return menuLayer
end
