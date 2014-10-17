local itemTagBasic = 1000
local winSize = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()
local TimelineTestIndex = 
{
    TEST_ACTION_TIMELINE        = 1,
    TEST_CHANGE_PLAY_SECTION    = 2,
    TEST_TIMELINE_FRAME_EVENT   = 3,
    TEST_TIMELINE_PERFORMACE    = 4,
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
    local scene = TimelineTestScene.extend(cc.Scene:create())
    local bg    = cc.Sprite:create("armature/bg.jpg")
    bg:setPosition(VisibleRect:center())

    local scaleX = VisibleRect:getVisibleRect().width / bg:getContentSize().width
    local scaleY = VisibleRect:getVisibleRect().height / bg:getContentSize().height

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
        return "Test ActionTimeline"
    elseif TimelineTestIndex.TEST_CHANGE_PLAY_SECTION == idx then
        return "Test Change Play Section"
    elseif TimelineTestIndex.TEST_TIMELINE_FRAME_EVENT == idx then
        return "Test Frame Event"
    elseif TimelineTestIndex.TEST_TIMELINE_PERFORMACE == idx then
        return "Test ActionTimeline performance"
    end
end

function TimelineTestLayer.subTitle(idx)
    if TimelineTestIndex.TEST_ACTION_TIMELINE == idx then
        return ""
    else
        return ""
    end
end

function TimelineTestLayer.create()
    local layer = TimelineTestLayer.extend(cc.Layer:create())

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
    newScene:addChild(backTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TimelineTestLayer.restartCallback()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TimelineTestLayer.nextCallback()
    local newScene = TimelineTestScene.create()
    newScene:addChild(nextTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TimelineTestLayer:createMenu()
    local menu = cc.Menu:create()
    
    self._backItem = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
    self._backItem:registerScriptTapHandler(self.backCallback)
    menu:addChild(self._backItem,itemTagBasic)
    self._restarItem = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
    self._restarItem:registerScriptTapHandler(self.restartCallback)
    menu:addChild(self._restarItem,itemTagBasic)
    self._nextItem = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
    menu:addChild(self._nextItem,itemTagBasic) 
    self._nextItem:registerScriptTapHandler(self.nextCallback)
    
    local size = cc.Director:getInstance():getWinSize()        
    self._backItem:setPosition(cc.p(size.width / 2 - self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))
    self._restarItem:setPosition(cc.p(size.width / 2, self._restarItem:getContentSize().height / 2))
    self._nextItem:setPosition(cc.p(size.width / 2 + self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))
    
    menu:setPosition(cc.p(0, 0))

    self:addChild(menu)
end

function TimelineTestLayer.toExtensionMenu()
    ccs.ArmatureDataManager:destroyInstance()
    local scene = CocoStudioTestMain()
    if scene ~= nil then
        cc.Director:getInstance():replaceScene(scene)
    end
end

function TimelineTestLayer:createToExtensionMenu()    
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local menuItemFont = cc.MenuItemFont:create("Back")
    menuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    menuItemFont:registerScriptTapHandler(TimelineTestLayer.toExtensionMenu)

    local backMenu = cc.Menu:create()
    backMenu:addChild(menuItemFont)
    backMenu:setPosition(cc.p(0, 0))
    self:addChild(backMenu,10)
end

function TimelineTestLayer:creatTitleAndSubTitle(idx)
    print("set title")
    local title = cc.Label:createWithTTF(TimelineTestLayer.title(idx), "fonts/Thonburi.ttf", 18)
    title:setColor(cc.c3b(255,0,0))
    self:addChild(title, 1, 10000)
    title:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= TimelineTestLayer.subTitle(idx) then
        local subTitle = cc.Label:createWithTTF(TimelineTestLayer.subTitle(idx), "fonts/Thonburi.ttf", 18)
        subTitle:setColor(cc.c3b(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 60) )
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
    cc.SpriteFrameCache:getInstance():addSpriteFrames("armature/Cowboy0.plist", "armature/Cowboy0.png")

    local node = cc.CSLoader:createNode("ActionTimeline/boy_1.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/boy_1.csb")

    node:runAction(action)
    action:gotoFrameAndPlay(0, 60, true)

    node:setScale(0.2)
    node:setPosition(150, 100)

    self:addChild(node)
end

function TestActionTimeline.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestActionTimeline.create()
    local layer = TestActionTimeline.extend(cc.Layer:create())

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

local TestChangePlaySection = class("TestChangePlaySection",TimelineTestLayer)
TestChangePlaySection.__index = TestChangePlaySection

function TestChangePlaySection.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestChangePlaySection)
    return target
end

function TestChangePlaySection:onEnter()
    cc.SpriteFrameCache:getInstance():addSpriteFrames("armature/Cowboy0.plist", "armature/Cowboy0.png")

    local node = cc.CSLoader:createNode("ActionTimeline/boy_1.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/boy_1.csb")

    node:runAction(action)
    action:gotoFrameAndPlay(70, action:getDuration(), true)

    node:setScale(0.2)
    node:setPosition(150, 100)

    local function onTouchesEnded(touches, event)
        if action:getStartFrame() == 0 then
            action:gotoFrameAndPlay(70, action:getDuration(), true)
        else
            action:gotoFrameAndPlay(0, 60, true)
        end
    end

    local listener = cc.EventListenerTouchAllAtOnce:create()    
    listener:registerScriptHandler(onTouchesEnded,cc.Handler.EVENT_TOUCHES_ENDED )

    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    self:addChild(node)
end

function TestChangePlaySection.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestChangePlaySection.create()
    local layer = TestChangePlaySection.extend(cc.Layer:create())

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

local TestTimelineFrameEvent = class("TestTimelineFrameEvent",TimelineTestLayer)
TestTimelineFrameEvent.__index = TestTimelineFrameEvent

function TestTimelineFrameEvent.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestTimelineFrameEvent)
    return target
end

function TestTimelineFrameEvent:onEnter()
    cc.SpriteFrameCache:getInstance():addSpriteFrames("armature/Cowboy0.plist", "armature/Cowboy0.png")

    local node = cc.CSLoader:createNode("ActionTimeline/boy_1.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/boy_1.csb")

    node:runAction(action)
    action:gotoFrameAndPlay(0, 60, true)

    node:setScale(0.2)
    node:setPosition(150, 100)
    self:addChild(node)

    local function onFrameEvent(frame)
        if nil == frame then
            return
        end

        local str = frame:getEvent()

        if str == "changeColor" then
            frame:getNode():setColor(cc.c3b(0, 0, 0))
        elseif(str == "endChangeColor") then
            frame:getNode():setColor(cc.c3b(255,255,255))
        end
    end

    action:setFrameEventCallFunc(onFrameEvent)
end

function TestTimelineFrameEvent.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestTimelineFrameEvent.create()
    local layer = TestTimelineFrameEvent.extend(cc.Layer:create())

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

local TestTimelinePerformance = class("TestTimelinePerformance",TimelineTestLayer)
TestTimelinePerformance.__index = TestTimelinePerformance

function TestTimelinePerformance.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestTimelinePerformance)
    return target
end

function TestTimelinePerformance:onEnter()
    cc.SpriteFrameCache:getInstance():addSpriteFrames("armature/Cowboy0.plist", "armature/Cowboy0.png")

    for i = 1,100 do
        local node = cc.CSLoader:createNode("ActionTimeline/boy_1.csb")
        local action = cc.CSLoader:createTimeline("ActionTimeline/boy_1.csb")

        node:runAction(action)
        action:gotoFrameAndPlay(70, action:getDuration(), true)

        node:setScale(0.1)
        node:setPosition((i - 1) * 2, 100)
        self:addChild(node)
    end
end

function TestTimelinePerformance.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestTimelinePerformance.create()
    local layer = TestTimelinePerformance.extend(cc.Layer:create())

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

local actionlineSceneArr =
{
    TestActionTimeline.create,
    TestChangePlaySection.create,
    TestTimelineFrameEvent.create,
    TestTimelinePerformance.create,
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
    cc.Director:getInstance():replaceScene(scene)
end
