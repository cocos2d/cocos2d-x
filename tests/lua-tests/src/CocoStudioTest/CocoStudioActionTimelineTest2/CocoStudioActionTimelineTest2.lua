
local itemTagBasic = 1000
local timelineSceneIdx = 1

local winSize = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()

local TimelineTest2Scene = class("TimelineTest2Scene")
TimelineTest2Scene.__index = TimelineTest2Scene

function TimelineTest2Scene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TimelineTest2Scene)
    return target
end

function TimelineTest2Scene:runThisTest()
    timelineSceneIdx = 1
    self:addChild(restartTimelineTest2())
end

function TimelineTest2Scene.create()
    local scene = TimelineTest2Scene.extend(cc.Scene:create())
    local bg    = cc.Sprite:create("armature/bg.jpg")
    bg:setPosition(VisibleRect:center())

    local scaleX = VisibleRect:getVisibleRect().width / bg:getContentSize().width
    local scaleY = VisibleRect:getVisibleRect().height / bg:getContentSize().height

    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)

    scene:addChild(bg)
    return scene
end

function TimelineTest2Scene.toMainMenuCallback()

end

local TimelineTest2Layer = class("TimelineTest2Layer")
TimelineTest2Layer.__index = TimelineTest2Layer
TimelineTest2Layer._backItem   = nil
TimelineTest2Layer._restarItem = nil
TimelineTest2Layer._nextItem   = nil

function TimelineTest2Layer:onEnter()

end

local _titles = {
    "debug",
    "change animation",
    "AnimationList: walk",
    "AnimationList: stand",
}

function TimelineTest2Layer.title(idx)
    return _titles[idx] or "";
end

function TimelineTest2Layer.subTitle(idx)
    return ""
end

function TimelineTest2Layer.create()
    local layer = TimelineTest2Layer.extend(cc.Layer:create())

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

function TimelineTest2Layer.backCallback()
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(backTimelineTest2())
    cc.Director:getInstance():replaceScene(newScene)
end

function TimelineTest2Layer.restartCallback()
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
    cc.Director:getInstance():replaceScene(newScene)
end

function TimelineTest2Layer.nextCallback()
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(nextTimelineTest2())
    cc.Director:getInstance():replaceScene(newScene)
end

function TimelineTest2Layer:createMenu()
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

function TimelineTest2Layer.toExtensionMenu()
    ccs.ArmatureDataManager:destroyInstance()
    local scene = CocoStudioTestMain()
    if scene ~= nil then
        cc.Director:getInstance():replaceScene(scene)
    end
end

function TimelineTest2Layer:createToExtensionMenu()
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local menuItemFont = cc.MenuItemFont:create("Back")
    menuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    menuItemFont:registerScriptTapHandler(TimelineTest2Layer.toExtensionMenu)

    local backMenu = cc.Menu:create()
    backMenu:addChild(menuItemFont)
    backMenu:setPosition(cc.p(0, 0))
    self:addChild(backMenu,10)
end

function TimelineTest2Layer:creatTitleAndSubTitle(idx)
    print("set title")
    local title = cc.Label:createWithTTF(TimelineTest2Layer.title(idx), "fonts/Thonburi.ttf", 18)
    title:setColor(cc.c3b(255,0,0))
    self:addChild(title, 1, 10000)
    title:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= TimelineTest2Layer.subTitle(idx) then
        local subTitle = cc.Label:createWithTTF(TimelineTest2Layer.subTitle(idx), "fonts/Thonburi.ttf", 18)
        subTitle:setColor(cc.c3b(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 60) )
    end
end

local TestActionTimeline = class("TestActionTimeline",TimelineTest2Layer)
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

    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer_skeleton.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer_skeleton.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(0)

    node:setScale(0.2)
    node:setPosition(VisibleRect:center())

    self:addChild(node)
end

function TestActionTimeline.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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

local TestChangePlaySection = class("TestChangePlaySection",TimelineTest2Layer)
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

    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer_skeleton.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer_skeleton.csb")
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
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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

local TestTimelineFrameEvent = class("TestTimelineFrameEvent",TimelineTest2Layer)
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

    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer_skeleton.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer_skeleton.csb")
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
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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

local TestTimelinePerformance = class("TestTimelinePerformance",TimelineTest2Layer)
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
        local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer_skeleton.csb")
        local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer_skeleton.csb")
        node:runAction(action)
        action:gotoFrameAndPlay(41)

        node:setScale(0.1)
        node:setPosition((i - 1) * 2, 100)
        self:addChild(node)
    end
end

function TestTimelinePerformance.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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
local TestTimelineAnimationList = class("TestTimelineAnimationList",TimelineTest2Layer)
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
    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer_skeleton.csb")
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer_skeleton.csb")
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
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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
local TestTimelineProjectNode = class("TestTimelineProjectNode",TimelineTest2Layer)
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
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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
local TestProjectNodeForSimulator = class("TestProjectNodeForSimulator",TimelineTest2Layer)
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
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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
local TestTimelineNodeLoadedCallback = class("TestTimelineNodeLoadedCallback",TimelineTest2Layer)
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
    local node = cc.CSLoader:createNode("ActionTimeline/DemoPlayer_skeleton.csb", function(object)
        if nil ~= object then
            print("object type is ", tolua.type(object))
            print("node name = ",object:getName())
            print("node parent name = ", object:getParent():getName())
        end
    end)
    local action = cc.CSLoader:createTimeline("ActionTimeline/DemoPlayer_skeleton.csb")
    node:runAction(action)
    action:gotoFrameAndPlay(0)

    node:setScale(0.2)
    node:setPosition(VisibleRect:center())

    self:addChild(node)
end

function TestTimelineNodeLoadedCallback.restartCallback()
    ccs.ArmatureDataManager:destroyInstance()
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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
local TestActionTimelineEase = class("TestActionTimelineEase",TimelineTest2Layer)
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
    local newScene = TimelineTest2Scene.create()
    newScene:addChild(restartTimelineTest2())
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

function nextTimelineTest2()
    timelineSceneIdx = timelineSceneIdx + 1
    timelineSceneIdx = timelineSceneIdx % table.getn(actionlineSceneArr)
    if 0 == timelineSceneIdx then
        timelineSceneIdx = table.getn(actionlineSceneArr)
    end
    return actionlineSceneArr[timelineSceneIdx]()
end

function backTimelineTest2()
    timelineSceneIdx = timelineSceneIdx - 1
    if timelineSceneIdx <= 0 then
        timelineSceneIdx = timelineSceneIdx + table.getn(actionlineSceneArr)
    end

    return actionlineSceneArr[timelineSceneIdx]()
end

function restartTimelineTest2()
    return actionlineSceneArr[timelineSceneIdx]()
end

function runCocoStudioActionTimelineTest2Scene()
    local scene = TimelineTest2Scene.create()
    scene:runThisTest()
    cc.Director:getInstance():replaceScene(scene)
end
