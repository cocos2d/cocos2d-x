local itemTagBasic = 1000
local winSize = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()
local TimelineTestIndex = 
{
    TEST_ACTION_TIMELINE     = 1,
}
local timelineSceneIdx   = TimelineTestIndex.TEST_ACTION_TIMELINE

local TimelineTestScene = class("TimelineTestScene")
TimelineTestScene.__index = TimelineTestScene

function TimelineTestScene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TimelineTestScene)
    return target
end

function TimelineTestScene:runThisTest()
    timelineSceneIdx   = TimelineTestIndex.TEST_ACTION_TIMELINE
    self:addChild(restartTimelineTest())
end

function TimelineTestScene.create()
    local scene = TimelineTestScene.extend(CCScene:create())
    local bg    = CCSprite:create("armature/bg.jpg")
    bg:setPosition(VisibleRect:center())

    local scaleX = VisibleRect:getVisibleRect().size.width / bg:getContentSize().width
    local scaleY = VisibleRect:getVisibleRect().size.height / bg:getContentSize().height

    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)

    scene:addChild(bg)
    return scene   
end

function TimelineTestScene.toMainMenuCallback()

end

local TimelineTestLayer = class("TimelineTestLayer")
TimelineTestLayer.__index = TimelineTestLayer
TimelineTestLayer._backItem   = nil
TimelineTestLayer._restarItem = nil
TimelineTestLayer._nextItem   = nil

function TimelineTestLayer:onEnter()
    
end

function TimelineTestLayer.title(idx)
    if TimelineTestIndex.TEST_ACTION_TIMELINE == idx then
        return "CSArmature Test Bed"
    end
end

function TimelineTestLayer.subTitle(idx)
    if TimelineTestIndex.TEST_ACTION_TIMELINE == idx then
        return ""
    end
end

function TimelineTestLayer.create()
    local layer = TimelineTestLayer.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(timelineSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end    

    return layer
end

function TimelineTestLayer.backCallback()
    local newScene = TimelineTestScene.create()
    newScene:addChild(backimelineTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function TimelineTestLayer.restartCallback()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function TimelineTestLayer.nextCallback()
    local newScene = TimelineTestScene.create()
    newScene:addChild(nextTimelineTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function TimelineTestLayer:createMenu()
    local menu = CCMenu:create()
    
    self._backItem = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    self._backItem:registerScriptTapHandler(self.backCallback)
    menu:addChild(self._backItem,itemTagBasic)
    self._restarItem = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    self._restarItem:registerScriptTapHandler(self.restartCallback)
    menu:addChild(self._restarItem,itemTagBasic)
    self._nextItem = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    menu:addChild(self._nextItem,itemTagBasic) 
    self._nextItem:registerScriptTapHandler(self.nextCallback)
    
    local size = CCDirector:sharedDirector():getWinSize()        
    self._backItem:setPosition(ccp(size.width / 2 - self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))
    self._restarItem:setPosition(ccp(size.width / 2, self._restarItem:getContentSize().height / 2))
    self._nextItem:setPosition(ccp(size.width / 2 + self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))
    
    menu:setPosition(ccp(0, 0))

    self:addChild(menu)
end

function TimelineTestLayer.toExtensionMenu()
    CCArmatureDataManager:purge()
    local scene = CocoStudioTest()
    if scene ~= nil then
        CCDirector:sharedDirector():replaceScene(scene)
    end
end

function TimelineTestLayer:createToExtensionMenu()    
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    local menuItemFont = CCMenuItemFont:create("Back")
    menuItemFont:setPosition(ccp(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    menuItemFont:registerScriptTapHandler(TimelineTestLayer.toExtensionMenu)

    local backMenu = CCMenu:create()
    backMenu:addChild(menuItemFont)
    backMenu:setPosition(ccp(0, 0))
    self:addChild(backMenu,10)
end

function TimelineTestLayer:creatTitleAndSubTitle(idx)
    local title = CCLabelTTF:create(TimelineTestLayer.title(idx),"Arial",18)
    title:setColor(ccc3(0,0,0))
    self:addChild(title, 1, 10000)
    title:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= TimelineTestLayer.subTitle(idx) then
        local subTitle = CCLabelTTF:create(TimelineTestLayer.subTitle(idx), "Arial", 18)
        subTitle:setColor(ccc3(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 60) )
    end
end

local TestActionTimeline = class("TestActionTimeline",TimelineTestLayer)
TestActionTimeline.__index = TestActionTimeline

function TestActionTimeline.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestActionTimeline)
    return target
end

function TestActionTimeline:onEnter()
    CCSpriteFrameCache:sharedSpriteFrameCache():addSpriteFramesWithFile("armature/Cowboy0.plist", "armature/Cowboy0.png")

    local node = NodeReader:getInstance():createNode("ActionTimeline/boy_1.ExportJson")
    local action = ActionTimelineCache:getInstance():createAction("ActionTimeline/boy_1.ExportJson")

    node:runAction(action)
    action:gotoFrameAndPlay(0, 60, true)

    node:setScale(0.4)
    node:setPosition(0, 0)

    self:addChild(node)
end

function TestActionTimeline.restartCallback()
    CCArmatureDataManager:purge()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function TestActionTimeline.create()
    local layer = TestActionTimeline.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer
end

local actionlineSceneArr =
{
    TestActionTimeline.create,
}

function nextTimelineTest()
    timelineSceneIdx = timelineSceneIdx + 1
    timelineSceneIdx = timelineSceneIdx % table.getn(actionlineSceneArr)
    if 0 == timelineSceneIdx then
        timelineSceneIdx = table.getn(actionlineSceneArr)
    end
    return actionlineSceneArr[timelineSceneIdx]()
end

function backTimelineTest() 
    timelineSceneIdx = timelineSceneIdx - 1
    if timelineSceneIdx <= 0 then
        timelineSceneIdx = timelineSceneIdx + table.getn(actionlineSceneArr)
    end

    return actionlineSceneArr[timelineSceneIdx]()
end

function restartTimelineTest()
    return actionlineSceneArr[timelineSceneIdx]()
end

function runCocoStudioActionTimelineTestScene()
    local scene = TimelineTestScene.create()
    scene:runThisTest()
    CCDirector:sharedDirector():replaceScene(scene)
end
