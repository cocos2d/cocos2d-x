local itemTagBasic = 1000
local winSize = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()
local TimelineTestIndex = 
{
    TEST_ACTION_TIMELINE        = 1,
    TEST_CHANGE_PLAY_SECTION    = 2,
    TEST_TIMELINE_FRAME_EVENT   = 3,
    TEST_TIMELINE_PERFORMACE    = 4, 
    TEST_TIMELINE_ANIMATION_LIST = 5,
    TEST_TIMELINE_PROJECT_NODE   = 6,
    TEST_PROJECT_NODE_FOR_SIMULATOR = 7,
    TEST_TIMELINE_NODE_LOADED_CALLBACK = 8,
    TEST_ACTION_TIMELINE_EASE    = 9,
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
    elseif TimelineTestIndex.TEST_ACTION_TIMELINE_EASE == idx then
        return "Test ActionTimelineEase"
    elseif TimelineTestIndex.TEST_TIMELINE_ANIMATION_LIST == idx then
        return "Test ActionTimeline AnimationList"
    elseif TimelineTestIndex.TEST_TIMELINE_PROJECT_NODE == idx then
        return "Test ActionTimeline ProjectNode"
    elseif TimelineTestIndex.TEST_PROJECT_NODE_FOR_SIMULATOR == idx then
        return "Test ProjectNode for Simalator"
    elseif TimelineTestIndex.TEST_TIMELINE_NODE_LOADED_CALLBACK == idx then
        return "Test node loaded call back"
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

    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(0)

    node:setScale(0.2)
    node:setPosition(VisibleRect:center())

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

    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(41)


    node:setScale(0.2)
    node:setPosition(VisibleRect:center())

    action:addAnimationInfo(ccs.AnimationInfo("stand", 0 , 40))
    action:addAnimationInfo(ccs.AnimationInfo("walk", 41 , 81))
    action:addAnimationInfo(ccs.AnimationInfo("killall", 174, 249))

    assert(action:IsAnimationInfoExists("stand") == true, "stand animation didn't exist")
    action:play("stand", true)
    assert(action:getAnimationInfo("stand").endIndex == 40, "endIndex of animationInfo is not 40")
    action:removeAnimationInfo("stand")
    assert(action:IsAnimationInfoExists("stand") == false, "stand animation has already existed")

    local function onTouchesEnded(touches, event)
        if action:getStartFrame() == 0 then
            action:gotoFrameAndPlay(41, 81, true)
        else
            action:gotoFrameAndPlay(0, 40, true)
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

    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(0)

    node:setScale(0.2)
    node:setPosition(VisibleRect:center())
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

    for i = 1,100 do
        local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer.csb")
        local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer.csb")
        node:runAction(action)
        action:gotoFrameAndPlay(41)

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

-------------------------------------------
---TestTimelineAnimationList
-------------------------------------------
local TestTimelineAnimationList = class("TestTimelineAnimationList",TimelineTestLayer)
TestTimelineAnimationList.__index = TestTimelineAnimationList

function TestTimelineAnimationList.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestTimelineAnimationList)
    return target
end

function TestTimelineAnimationList:onEnter()
    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer.csb")
    local standInfo = ccs.AnimationInfo("stand", 0, 40)
    local walkInfo = ccs.AnimationInfo("walk",  41,  81)
    action:addAnimationInfo(standInfo)
    action:addAnimationInfo(walkInfo)
    node:runAction(action)
    action:play("walk", true)

    node:setScale(0.2)
    node:setPosition(150,100)
    self:addChild(node)
end

function TestTimelineAnimationList.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestTimelineAnimationList.create()
    local layer = TestTimelineAnimationList.extend(cc.Layer:create())

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


-------------------------------------------
---TestTimelineProjectNode
-------------------------------------------
local TestTimelineProjectNode = class("TestTimelineProjectNode",TimelineTestLayer)
TestTimelineProjectNode.__index = TestTimelineProjectNode

function TestTimelineProjectNode.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestTimelineProjectNode)
    return target
end

function TestTimelineProjectNode:onEnter()
    local node = cc.CSLoader:createNode("ActionTimeline/TestAnimation.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/TestAnimation.csb")

    node:runAction(action)
    action:gotoFrameAndPlay(0, true)

    node:setPosition(-300, -300)
    self:addChild(node)
end

function TestTimelineProjectNode.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestTimelineProjectNode.create()
    local layer = TestTimelineProjectNode.extend(cc.Layer:create())

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


-------------------------------------------
---TestProjectNodeForSimulator
-------------------------------------------
local TestProjectNodeForSimulator = class("TestProjectNodeForSimulator",TimelineTestLayer)
TestProjectNodeForSimulator.__index = TestProjectNodeForSimulator

function TestProjectNodeForSimulator.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestProjectNodeForSimulator)
    return target
end

function TestProjectNodeForSimulator:onEnter()
    local node = cc.CSLoader:getInstance():createNodeWithFlatBuffersForSimulator("ActionTimeline/TestAnimation.csd")
    local action = ccs.ActionTimelineCache:getInstance():createActionWithFlatBuffersForSimulator("ActionTimeline/TestAnimation.csd")

    node:runAction(action)
    action:gotoFrameAndPlay(0, true)
    
    node:setPosition(-300, -300)
    self:addChild(node)

    --test for when ProjectNode file lost
    local lackProjectNodefileNode = cc.CSLoader:getInstance():createNodeWithFlatBuffersForSimulator("ActionTimeline/TestNullProjectNode.csd")
    local lackProjectNodefileAction = ccs.ActionTimelineCache:getInstance():createActionWithFlatBuffersForSimulator("ActionTimeline/TestNullProjectNode.csd")
    lackProjectNodefileNode:runAction(lackProjectNodefileAction)
    lackProjectNodefileAction:gotoFrameAndPlay(0)
    self:addChild(lackProjectNodefileNode)
end

function TestProjectNodeForSimulator.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestProjectNodeForSimulator.create()
    local layer = TestProjectNodeForSimulator.extend(cc.Layer:create())

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

-------------------------------------------
---TestTimelineNodeLoadedCallback
-------------------------------------------
local TestTimelineNodeLoadedCallback = class("TestTimelineNodeLoadedCallback",TimelineTestLayer)
TestTimelineNodeLoadedCallback.__index = TestTimelineNodeLoadedCallback

function TestTimelineNodeLoadedCallback.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestTimelineNodeLoadedCallback)
    return target
end

function TestTimelineNodeLoadedCallback:onEnter()
    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer.csb", function(object)
        if nil ~= object then
            print("object type is ", tolua.type(object))
            print("node name = ",object:getName())
            print("node parent name = ", object:getParent():getName())
        end
    end)
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(0)

    node:setScale(0.2)
    node:setPosition(VisibleRect:center())
    
    self:addChild(node)
end

function TestTimelineNodeLoadedCallback.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestTimelineNodeLoadedCallback.create()
    local layer = TestTimelineNodeLoadedCallback.extend(cc.Layer:create())

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

-------------------------------------------
---TestActionTimelineEase
-------------------------------------------
local TestActionTimelineEase = class("TestActionTimelineEase",TimelineTestLayer)
TestActionTimelineEase.__index = TestActionTimelineEase

function TestActionTimelineEase.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestActionTimelineEase)
    return target
end

function TestActionTimelineEase:onEnter()
    local node = cc.CSLoader:createNode("ActionTimeline/ActionTimelineEase.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/ActionTimelineEase.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(0)
    self:addChild(node)
end

function TestActionTimelineEase.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTestScene.create()
    newScene:addChild(restartTimelineTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function TestActionTimelineEase.create()
    local layer = TestActionTimelineEase.extend(cc.Layer:create())

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
    TestTimelineAnimationList.create,
    TestTimelineProjectNode.create,
    TestProjectNodeForSimulator.create,
    TestTimelineNodeLoadedCallback.create,
    TestActionTimelineEase.create,
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
