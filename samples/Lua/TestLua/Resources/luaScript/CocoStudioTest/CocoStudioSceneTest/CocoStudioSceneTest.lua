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
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/LoadSceneEdtiorFileTest/FishJoy2.json")
    if nil == node then
        return
    end
    self._curNode = node

    local winSize = CCDirector:sharedDirector():getWinSize()
    local scale = winSize.height / 320
    self._curNode:setScale(scale)
    self._curNode:setPosition(ccp((winSize.width - 480 * scale) / 2, (winSize.height - 320 * scale) / 2))

    local function menuCloseCallback( sender )
        SceneReader:sharedSceneReader():purge()
        ActionManager:purge()
        TriggerMng.destroyInstance()
        local scene = CocoStudioTest()
        if scene ~= nil then
            CCDirector:sharedDirector():replaceScene(scene)
        end
    end

    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    local itemBack = CCMenuItemFont:create("Back")
    itemBack:setColor(ccc3(255, 255, 255))
    itemBack:setPosition( ccp(430,30) )
    itemBack:registerScriptTapHandler(menuCloseCallback)
    local menuBack = CCMenu:create()
    menuBack:setPosition(ccp(0.0, 0.0))
    menuBack:setZOrder(4)
    menuBack:addChild(itemBack)

    node:addChild(menuBack)

    ActionManager:shareManager():playActionByName("startMenu_1.json","Animation1")

    local function onNodeEvent(event)
        if event == "enter" then
            self:onEnter()
        elseif event == "exit" then
            self:onExit()
        end
    end

    self:registerScriptHandler(onNodeEvent)

    local function onTouchEvent(eventType, x, y)
        if eventType == "began" then
            return self:onTouchBegan(x, y)
        elseif eventType == "moved" then
            self:onTouchMoved(x, y)
        elseif eventType == "ended" then
            self:onTouchEnded(x,y)
        elseif eventType == "cancelled" then
            self:onTouchCancelled(x, y)
        end
    end
    self:setTouchEnabled(true)
    self:registerScriptTouchHandler(onTouchEvent)

    return node
end

function SceneEditorTestLayer:onEnter()
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_ENTERSCENE)
end

function SceneEditorTestLayer:onExit()
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_LEAVESCENE)
end

function SceneEditorTestLayer:onTouchBegan(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHBEGAN)
    return true
end

function SceneEditorTestLayer:onTouchMoved(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHMOVED)
end

function SceneEditorTestLayer:onTouchEnded(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHENDED)
end

function SceneEditorTestLayer:onTouchCancelled(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHCANCELLED)
end

function SceneEditorTestLayer.create()
    local scene = CCScene:create()
    local layer = SceneEditorTestLayer.extend(CCLayerColor:create())
    layer:addChild(layer:createGameScene(), 0, 1)
    scene:addChild(layer)
    return scene   
end

function runCocosSceneTestScene()
   local scene = SceneEditorTestLayer.create()
   CCDirector:sharedDirector():replaceScene(scene)
end
