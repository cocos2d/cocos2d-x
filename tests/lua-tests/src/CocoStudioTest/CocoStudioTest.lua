require "src/CocoStudioTest/CocoStudioGUITest/CocoStudioGUITest"
require "src/CocoStudioTest/CocoStudioSceneTest/CocoStudioSceneTest"
require "src/CocoStudioTest/CocoStudioArmatureTest/CocoStudioArmatureTest"

local LINE_SPACE = 40
local ITEM_TAG_BASIC = 1000

local cocoStudioTestItemNames = 
{
    {
        itemTitle = "CocoStudioArmatureTest",
        testScene = function () 
            runArmatureTestScene()
        end
    },

    {
        itemTitle = "CocoStudioGUITest",
        testScene =  function () 
            runCocosGUITestScene()
        end
    },

    {
        itemTitle = "CocoStudioSceneTest",
        testScene = function () 
            runCocosSceneTestScene()
        end
    },
} 

local CocoStudioTestScene = class("CocoStudioTestScene")
CocoStudioTestScene.__index = CocoStudioTestScene

function CocoStudioTestScene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CocoStudioTestScene)
    return target
end

function CocoStudioTestScene:runThisTest()

    --armatureSceneIdx   = ArmatureTestIndex.TEST_COCOSTUDIO_WITH_SKELETON
    --self:addChild(restartArmatureTest())
end

function CocoStudioTestScene.create()
    local scene = CocoStudioTestScene.extend(cc.Scene:create())
    return scene   
end

local CocoStudioTestLayer = class("CocoStudioTestLayer")
CocoStudioTestLayer.__index = CocoStudioTestLayer

function CocoStudioTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, CocoStudioTestLayer)
    return target
end

function CocoStudioTestLayer.onMenuCallback(tag,sender)
    local index = sender:getLocalZOrder() - ITEM_TAG_BASIC
    cocoStudioTestItemNames[index].testScene()
end

function CocoStudioTestLayer:createMenu()

    local winSize = cc.Director:getInstance():getWinSize()

    local menu = cc.Menu:create()
    menu:setPosition(cc.p(0,0))
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)

    for i = 1, table.getn(cocoStudioTestItemNames) do
        local menuItem = cc.MenuItemFont:create(cocoStudioTestItemNames[i].itemTitle)
        menuItem:setPosition(cc.p(winSize.width / 2, winSize.height - (i + 1) * LINE_SPACE))
        menuItem:registerScriptTapHandler(CocoStudioTestLayer.onMenuCallback)
        menu:addChild(menuItem, ITEM_TAG_BASIC + i)
    end

    self:addChild(menu)
end

function CocoStudioTestLayer.create()
    local layer = CocoStudioTestLayer.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
    end 
    return layer
end

-------------------------------------
--CocoStudio Test
-------------------------------------
function CocoStudioTestMain()
    local newScene = CocoStudioTestScene.create()
	newScene:addChild(CreateBackMenuItem())
    newScene:addChild(CocoStudioTestLayer.create())
    newScene:runThisTest()
	return newScene
end
