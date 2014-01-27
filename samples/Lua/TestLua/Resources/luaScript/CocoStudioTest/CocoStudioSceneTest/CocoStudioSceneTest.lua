require "luaScript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/acts"
require "luaScript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/cons"
require "luaScript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/eventDef"

local SceneEditorTestLayer = class("SceneEditorTestLayer")
SceneEditorTestLayer._curNode = nil

function SceneEditorTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SceneEditorTestLayer)
    return target
end

function SceneEditorTestLayer:createGameScene()
    local node = ccs.SceneReader:getInstance():createNodeWithSceneFile("scenetest/LoadSceneEdtiorFileTest/FishJoy2.json")
    if nil == node then
        return
    end
    self._curNode = node

    local function menuCloseCallback( sender )
        ccs.SceneReader:destroyInstance()
        ccs.ActionManagerEx:destroyInstance()
        ccs.TriggerMng.destroyInstance()
        local scene = CocoStudioTestMain()
        if scene ~= nil then
            cc.Director:getInstance():replaceScene(scene)
        end
    end

    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local itemBack = cc.MenuItemFont:create("Back")
    itemBack:setColor(cc.c3b(255, 255, 255))
    itemBack:setPosition( cc.p(430,30) )
    itemBack:registerScriptTapHandler(menuCloseCallback)
    local menuBack = cc.Menu:create()
    menuBack:setPosition(cc.p(0.0, 0.0))
    menuBack:setLocalZOrder(4)
    menuBack:addChild(itemBack)

    node:addChild(menuBack)

    ccs.ActionManagerEx:getInstance():playActionByName("startMenu_1.json","Animation1")

    local function onNodeEvent(event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end

    self:registerScriptHandler(onNodeEvent)

    local listener = cc.EventListenerTouchOneByOne:create()
    listener:setSwallowTouches(true)
    listener:registerScriptHandler(self.onTouchBegan,cc.Handler.EVENT_TOUCH_BEGAN )
    listener:registerScriptHandler(self.onTouchMoved,cc.Handler.EVENT_TOUCH_MOVED )
    listener:registerScriptHandler(self.onTouchEnded,cc.Handler.EVENT_TOUCH_ENDED )
    listener:registerScriptHandler(self.onTouchCancelled,cc.Handler.EVENT_TOUCH_CANCELLED )
    local eventDispatcher = self:getEventDispatcher()
    eventDispatcher:addEventListenerWithSceneGraphPriority(listener, self)

    return node
end

function SceneEditorTestLayer:onEnter()
    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_ENTERSCENE)
end

function SceneEditorTestLayer:onExit()
    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_LEAVESCENE)
end

function SceneEditorTestLayer:onTouchBegan(touch,event)
    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHBEGAN)
    return true
end

function SceneEditorTestLayer:onTouchMoved(touch,event)
    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHMOVED)
end

function SceneEditorTestLayer:onTouchEnded(touch,event)
    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHENDED)
end

function SceneEditorTestLayer:onTouchCancelled(touch,event)
    ccs.sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHCANCELLED)
end

function SceneEditorTestLayer.create()
    local scene = cc.Scene:create()
    local layer = SceneEditorTestLayer.extend(cc.LayerColor:create())
    layer:addChild(layer:createGameScene(), 0, 1)
    scene:addChild(layer)
    return scene   
end

function runCocosSceneTestScene()
   local scene = SceneEditorTestLayer.create()
   cc.Director:getInstance():replaceScene(scene)
end