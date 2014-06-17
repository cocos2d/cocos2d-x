require "luaScript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/acts"
require "luaScript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/cons"
require "luaScript/CocoStudioTest/CocoStudioSceneTest/TriggerCode/eventDef"

local itemTagBasic = 1000

local sceneEditorTestIdx = 1
local TouchEventType = 
{
    began = 0,
    moved = 1,
    ended = 2,
    canceled = 3,
}

local MovementEventType = {
    start = 0,
    complete = 1,
    loopComplete = 2, 
}

local SceneEditorTestLayer = class("SceneEditorTestLayer")
SceneEditorTestLayer.__index = SceneEditorTestLayer
SceneEditorTestLayer._backItem = nil
SceneEditorTestLayer._restarItem = nil
SceneEditorTestLayer._nextItem   = nil
SceneEditorTestLayer.title       = 
{
    "loadSceneEdtiorFile Test",
    "Sprite Component Test",
    "Armature Component Test",
    "UI Component Test",
    "TmxMap Component Test",
    "Particle Component Test",
    "Effect Component Test",
    "Background Component Test",
    "Attribute Component Test",
    "Trigger Test",
}
SceneEditorTestLayer.loadtypeStr=
{
    "change to load \nwith binary file",
    "change to load \nwith json file"
}

SceneEditorTestLayer.fileName = ""
SceneEditorTestLayer.rootNode  = nil

function SceneEditorTestLayer.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SceneEditorTestLayer)
    return target
end


function SceneEditorTestLayer:onEnter() 
    
end

function SceneEditorTestLayer:onExit()
    TriggerMng.destroyInstance()
    CCArmatureDataManager:purge()
    SceneReader:sharedSceneReader():purge()
    ActionManager:purge()
    GUIReader:purge()
end

function SceneEditorTestLayer.create()
    local layer = SceneEditorTestLayer.extend(CCLayer:create())
    if nil ~= layer then
        layer:createTitle()
        layer:createMenu()
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end
end

function SceneEditorTestLayer:createTitle()
    local title = CCLabelTTF:create(self.title[sceneEditorTestIdx],"Arial",18)
    title:setColor(ccc3(255, 255, 255))
    self:addChild(title, 1, 10000)
    title:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 30))
end

function SceneEditorTestLayer:loadFileChangeHelper(filePathName)
    local indexTable = {}
    local index = 0

    while true do
        index = string.find(filePathName, "%.", index + 1)
        if nil == index then
            break
        end

        indexTable[#indexTable + 1] = index
    end

    if #indexTable == 0 then
        return filePathName
    end
    
    local lastIndex = indexTable[#indexTable]
    if lastIndex == 1 then
        return filePathName
    end
    local renamePathName= string.sub(filePathName, 1, lastIndex - 1)
    print("renamePath is", renamePathName)
    if self.isCsbLoad then
        renamePathName = renamePathName .. ".csb"
    else
        renamePathName = renamePathName .. ".json"
    end

    return renamePathName
end

function SceneEditorTestLayer:defaultPlay() 
    
end

function SceneEditorTestLayer:createMenu()
    local menu = CCMenu:create()

    local function pre()
        local scene = CCScene:create()
        scene:addChild(backSceneEditorTest())
        CCDirector:sharedDirector():replaceScene(scene)
    end

    local function restart()
        local scene = CCScene:create()
        scene:addChild(restartSceneEditorTest())
        CCDirector:sharedDirector():replaceScene(scene)
    end

    local function next()
        local scene = CCScene:create()
        scene:addChild(nextSceneEditorTest())
        CCDirector:sharedDirector():replaceScene(scene)
    end

    self._backItem = CCMenuItemImage:create(s_pPathB1, s_pPathB2)
    self._backItem:registerScriptTapHandler(pre)
    self._restarItem = CCMenuItemImage:create(s_pPathR1, s_pPathR2)
    self._restarItem:registerScriptTapHandler(restart)
    self._nextItem = CCMenuItemImage:create(s_pPathF1, s_pPathF2)
    self._nextItem:registerScriptTapHandler(next)



    local size = CCDirector:sharedDirector():getWinSize()
    self._backItem:setPosition(ccp(size.width / 2 - self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))
    self._restarItem:setPosition(ccp(size.width / 2, self._restarItem:getContentSize().height / 2))
    self._nextItem:setPosition(ccp(size.width / 2 + self._restarItem:getContentSize().width * 2, self._restarItem:getContentSize().height / 2))

    menu:addChild(self._backItem,itemTagBasic)
    menu:addChild(self._restarItem,itemTagBasic)
    menu:addChild(self._nextItem,itemTagBasic)
    menu:setPosition(ccp(0,0))
    self:addChild(menu, 100)

    local function back()
        local scene = CocoStudioTest()
        if nil ~= scene then
            CCDirector:sharedDirector():replaceScene(scene)
        end
    end




    self.isCsbLoad = false
    self.loadtypeLabel = CCLabelTTF:create(self.loadtypeStr[1], "Arial", 12)

    local function changeLoadTypeCallback(sender)
        self.isCsbLoad = not self.isCsbLoad
        if self.isCsbLoad then
            self.loadtypeLabel:setString(self.loadtypeStr[2])
        else
            self.loadtypeLabel:setString(self.loadtypeStr[1])
        end

        SceneEditorTestLayer.fileName = self:loadFileChangeHelper(SceneEditorTestLayer.fileName)
    
        if SceneEditorTestLayer.rootNode ~= nil then
            self:removeChild(SceneEditorTestLayer.rootNode, true)
            SceneEditorTestLayer.rootNode = SceneReader:sharedSceneReader():createNodeWithSceneFile(SceneEditorTestLayer.fileName)
            if SceneEditorTestLayer.rootNode == nil then
                return
            end
            self:defaultPlay()
            self:addChild(SceneEditorTestLayer.rootNode)
        end
    end
    local loadTypeItem = CCMenuItemLabel:create(self.loadtypeLabel)
    loadTypeItem:registerScriptTapHandler(changeLoadTypeCallback)
    local loadtypeMenu = CCMenu:create()
    loadTypeItem:setPosition(ccp(VisibleRect:rightTop().x -50,VisibleRect:rightTop().y -20))
    loadtypeMenu:addChild(loadTypeItem)
    loadtypeMenu:setPosition(0, 0)
    self:addChild(loadtypeMenu, 100)

    local backMenu = CCMenu:create()
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    local menuItemFont = CCMenuItemFont:create("Back")
    menuItemFont:setPosition(ccp(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    menuItemFont:registerScriptTapHandler(back)

    backMenu:addChild(menuItemFont)
    backMenu:setPosition(ccp(0, 0))
    self:addChild(backMenu,10)
end

local LoadSceneEdtiorFileTest = class("LoadSceneEdtiorFileTest",SceneEditorTestLayer)
LoadSceneEdtiorFileTest.__index = LoadSceneEdtiorFileTest

function LoadSceneEdtiorFileTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, LoadSceneEdtiorFileTest)
    return target
end

function LoadSceneEdtiorFileTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/LoadSceneEdtiorFileTest/FishJoy2.json")
    SceneEditorTestLayer.fileName = "scenetest/LoadSceneEdtiorFileTest/FishJoy2.json"
    SceneEditorTestLayer.rootNode = node
    self:defaultPlay()
    return node
end

function LoadSceneEdtiorFileTest:defaultPlay()
    ActionManager:shareManager():playActionByName("startMenu_1.json","Animation1")
end

function LoadSceneEdtiorFileTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function LoadSceneEdtiorFileTest.create()
    local layer = LoadSceneEdtiorFileTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local SpriteComponentTest = class("SpriteComponentTest",SceneEditorTestLayer)
SpriteComponentTest.__index = SpriteComponentTest

function SpriteComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, SpriteComponentTest)
    return target
end

function SpriteComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/SpriteComponentTest/SpriteComponentTest.json")
    if nil ~= node then

        SceneEditorTestLayer.fileName = "scenetest/SpriteComponentTest/SpriteComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function SpriteComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function SpriteComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
        local action1 = CCBlink:create(2, 10)
        local action2 = CCBlink:create(2, 5)

        local sister1 = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10003):getComponent("CCSprite"),"CCComRender")
        sister1:getNode():runAction(action1)
        local sister2 = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10004):getComponent("CCSprite"),"CCComRender")
        sister2:getNode():runAction(action2)
    end
end

function SpriteComponentTest.create()
    local layer = SpriteComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local ArmatureComponentTest = class("ArmatureComponentTest",SceneEditorTestLayer)
ArmatureComponentTest.__index = ArmatureComponentTest

function ArmatureComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, ArmatureComponentTest)
    return target
end

function ArmatureComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/ArmatureComponentTest/ArmatureComponentTest.json")
    if nil ~= node then
        SceneEditorTestLayer.fileName = "scenetest/ArmatureComponentTest/ArmatureComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function ArmatureComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootName ~= nil then
        local blowFish = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10007):getComponent("CCArmature"),"CCComRender")
        blowFish:getNode():runAction(CCMoveBy:create(10.0, ccp(-1000.0, 0)))

        local butterflyfish = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10008):getComponent("CCArmature"),"CCComRender")
        butterflyfish:getNode():runAction(CCMoveBy:create(10.0, ccp(-1000.0, 0)))
    end
end

function ArmatureComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function ArmatureComponentTest.create()
    local layer = ArmatureComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local UIComponentTest = class("UIComponentTest",SceneEditorTestLayer)
UIComponentTest.__index = UIComponentTest

function UIComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, UIComponentTest)
    return target
end

function UIComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/UIComponentTest/UIComponentTest.json")
    if nil ~= node then
        SceneEditorTestLayer.fileName = "scenetest/UIComponentTest/UIComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function UIComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
        local render = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10025):getComponent("GUIComponent"),"CCComRender")
        local touchGroup = tolua.cast(render:getNode(), "TouchGroup")
        local widget = tolua.cast(touchGroup:getWidgetByName("Panel_154"), "Widget")
        local button = tolua.cast(widget:getChildByName("Button_156"),"Button")
        local function onTouch(sender, eventType)
            if eventType == TouchEventType.began then
                local blowFish = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10010):getComponent("CCArmature"), "CCComRender")
                blowFish:getNode():runAction(CCMoveBy:create(10.0, ccp(-1000.0, 0)))

                local butterflyfish = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10011):getComponent("CCArmature"), "CCComRender")
                butterflyfish:getNode():runAction(CCMoveBy:create(10.0, ccp(-1000.0, 0)))
            end
        end

        button:addTouchEventListener(onTouch)
    end
end

function UIComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function UIComponentTest.create()
    local layer = UIComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local TmxMapComponentTest = class("TmxMapComponentTest",SceneEditorTestLayer)
TmxMapComponentTest.__index = TmxMapComponentTest

function TmxMapComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TmxMapComponentTest)
    return target
end

function TmxMapComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/TmxMapComponentTest/TmxMapComponentTest.json")
    if nil ~= node then

        SceneEditorTestLayer.fileName = "scenetest/TmxMapComponentTest/TmxMapComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function TmxMapComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
        local tmxMap = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10015):getComponent("CCTMXTiledMap"),"CCComRender")
        local actionTo = CCSkewTo:create(2, 0.0, 2.0)
        local rotateTo = CCRotateTo:create(2, 61.0)
        local actionScaleTo = CCScaleTo:create(2, -0.44, 0.47)

        local actionScaleToBack = CCScaleTo:create(2, 1.0, 1.0)
        local rotateToBack = CCRotateTo:create(2, 0)
        local actionToBack = CCSkewTo:create(2, 0, 0)

        local arr = CCArray:create()
        arr:addObject(actionTo)
        arr:addObject(actionToBack)
        tmxMap:getNode():runAction(CCSequence:create(arr))

        arr = CCArray:create()
        arr:addObject(rotateTo)
        arr:addObject(rotateToBack)
        tmxMap:getNode():runAction(CCSequence:create(arr))

        arr = CCArray:create()
        arr:addObject(actionScaleTo)
        arr:addObject(actionScaleToBack)
        tmxMap:getNode():runAction(CCSequence:create(arr))
    end
end

function TmxMapComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function TmxMapComponentTest.create()
    local layer = TmxMapComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local ParticleComponentTest = class("ParticleComponentTest",SceneEditorTestLayer)
ParticleComponentTest.__index = ParticleComponentTest

function ParticleComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, ParticleComponentTest)
    return target
end

function ParticleComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/ParticleComponentTest/ParticleComponentTest.json")
    if nil ~= node then

        SceneEditorTestLayer.fileName = "scenetest/ParticleComponentTest/ParticleComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function ParticleComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
        local particle = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10020):getComponent("CCParticleSystemQuad"),"CCComRender")
        local jump = CCJumpBy:create(5, ccp(-500,0), 50, 4)
        local arr  = CCArray:create()
        arr:addObject(jump)
        arr:addObject(jump:reverse())
        local action = CCSequence:create(arr)
        particle:getNode():runAction(action)
    end
end

function ParticleComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function ParticleComponentTest.create()
    local layer = ParticleComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local EffectComponentTest = class("EffectComponentTest",SceneEditorTestLayer)
EffectComponentTest.__index = EffectComponentTest

function EffectComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, EffectComponentTest)
    return target
end

function EffectComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/EffectComponentTest/EffectComponentTest.json")
    if nil ~= node then

        SceneEditorTestLayer.fileName = "scenetest/EffectComponentTest/EffectComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function EffectComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
        local render = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10015):getComponent("CCArmature"),"CCComRender")
        local armature = tolua.cast(render:getNode(),"CCArmature")
        local function animationEvent(armatureBack,movementType,movementID)
            local id = movementID
            if movementType == MovementEventType.loopComplete then
                if id == "Fire" then
                    local audio = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10015):getComponent("CCComAudio"), "CCComAudio")
                    audio:playEffect()
                end
            end
        end

        armature:getAnimation():setMovementEventCallFunc(animationEvent)
    end
end

function EffectComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function EffectComponentTest.create()
    local layer = EffectComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local BackgroundComponentTest = class("BackgroundComponentTest",SceneEditorTestLayer)
BackgroundComponentTest.__index = BackgroundComponentTest

function BackgroundComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, BackgroundComponentTest)
    return target
end

function BackgroundComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/BackgroundComponentTest/BackgroundComponentTest.json")
    if nil ~= node then

        SceneEditorTestLayer.fileName = "scenetest/BackgroundComponentTest/BackgroundComponentTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end

    return node
end

function BackgroundComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
       local audio = tolua.cast(SceneEditorTestLayer.rootNode:getComponent("CCBackgroundAudio"),"CCComAudio")
        audio:playBackgroundMusic()
    end
end

function BackgroundComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function BackgroundComponentTest.create()
    local layer = BackgroundComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local AttributeComponentTest = class("AttributeComponentTest",SceneEditorTestLayer)
AttributeComponentTest.__index = AttributeComponentTest

function AttributeComponentTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, AttributeComponentTest)
    return target
end

function AttributeComponentTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/AttributeComponentTest/AttributeComponentTest.json")
    if nil ~= node then
        SceneEditorTestLayer.fileName = "scenetest/AttributeComponentTest/AttributeComponentTest.json"
        SceneEditorTestLayer.rootNode = node
        self:defaultPlay()
    return node
    end
end

function AttributeComponentTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then
        local attribute = tolua.cast(SceneEditorTestLayer.rootNode:getChildByTag(10015):getComponent("CCComAttribute"), "CCComAttribute")
        print(string.format("Name: %s, HP: %f, MP: %f", attribute:getCString("name"), attribute:getFloat("maxHP"), attribute:getFloat("maxMP")))
    end
end

function AttributeComponentTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end
    
end

function AttributeComponentTest.create()
    local layer = AttributeComponentTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local TriggerTest = class("TriggerTest",SceneEditorTestLayer)
TriggerTest.__index = TriggerTest

function TriggerTest.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TriggerTest)
    return target
end

function TriggerTest:createGameScene()
    local node = SceneReader:sharedSceneReader():createNodeWithSceneFile("scenetest/TriggerTest/TriggerTest.json")
    if nil ~= node then
        SceneEditorTestLayer.fileName = "scenetest/TriggerTest/TriggerTest.json"
        SceneEditorTestLayer.rootNode = node

        self:defaultPlay()
    end
    return node
end

function TriggerTest:onTouchBegan(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHBEGAN)
    return true
end

function TriggerTest:onTouchMoved(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHMOVED)
end

function TriggerTest:onTouchEnded(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHENDED)
end

function TriggerTest:onTouchCancelled(x,y)
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_TOUCHCANCELLED)
end

function TriggerTest:onEnter()
    self:createMenu()
    self:createTitle()
    local root = self:createGameScene()
    if nil ~= root then
        self:addChild(root, 0, 1)
    end    
end

function TriggerTest:defaultPlay()
    if SceneEditorTestLayer.rootNode ~= nil then

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
        self:setTouchMode(kCCTouchesOneByOne)
        self:registerScriptTouchHandler(onTouchEvent)

        local function update(dt)
            sendTriggerEvent(triggerEventDef.TRIGGEREVENT_UPDATESCENE)
        end
        self:scheduleUpdateWithPriorityLua(update,0)
        sendTriggerEvent(triggerEventDef.TRIGGEREVENT_ENTERSCENE)
    end
end

function TriggerTest:onExit()
    sendTriggerEvent(triggerEventDef.TRIGGEREVENT_LEAVESCENE)
    self:unscheduleUpdate()
    self:setTouchEnabled(false)
    TriggerMng.destroyInstance()
    CCArmatureDataManager:purge()
    SceneReader:sharedSceneReader():purge()
    ActionManager:purge()
    GUIReader:purge()
end

function TriggerTest.create()
    local layer = TriggerTest.extend(CCLayer:create())

    if nil ~= layer then
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            elseif "exit" == event then
                layer:onExit()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end

    return layer
end

local createSceneEditorTest = 
{
    LoadSceneEdtiorFileTest.create,
    SpriteComponentTest.create,
    ArmatureComponentTest.create,
    UIComponentTest.create,
    TmxMapComponentTest.create,
    ParticleComponentTest.create,
    EffectComponentTest.create,
    BackgroundComponentTest.create,
    AttributeComponentTest.create,
    TriggerTest.create,
}

function nextSceneEditorTest( )
    sceneEditorTestIdx = sceneEditorTestIdx + 1
    sceneEditorTestIdx = sceneEditorTestIdx % table.getn(createSceneEditorTest)

    if 0 == sceneEditorTestIdx  then
        sceneEditorTestIdx = table.getn(createSceneEditorTest)
    end

    return createSceneEditorTest[sceneEditorTestIdx]()
end

function backSceneEditorTest()
    sceneEditorTestIdx = sceneEditorTestIdx - 1
    if sceneEditorTestIdx <= 0 then
        sceneEditorTestIdx = sceneEditorTestIdx + table.getn(createSceneEditorTest)
    end

    return createSceneEditorTest[sceneEditorTestIdx]()
end

function restartSceneEditorTest()
    return createSceneEditorTest[sceneEditorTestIdx]()
end

function runCocosSceneTestScene()
   local scene = CCScene:create()
   sceneEditorTestIdx = 1
   scene:addChild(restartSceneEditorTest())
   CCDirector:sharedDirector():replaceScene(scene)
end
