local itemTagBasic = 1000
local armaturePerformanceTag = 20000
local frameEventActionTag = 10000
local winSize = CCDirector:sharedDirector():getWinSize()
local scheduler = CCDirector:sharedDirector():getScheduler()
local ArmatureTestIndex = 
{
    TEST_ASYNCHRONOUS_LOADING     = 1,
    TEST_DIRECT_LOADING           = 2,
    TEST_COCOSTUDIO_WITH_SKELETON = 3,
    TEST_DRAGON_BONES_2_0 = 4,
    TEST_PERFORMANCE = 5,
    TEST_PERFORMANCE_BATCHNODE = 6,
    TEST_CHANGE_ZORDER = 7,
    TEST_ANIMATION_EVENT = 8,
    TEST_FRAME_EVENT     = 9,
    TEST_PARTICLE_DISPLAY = 10,
    TEST_USE_DIFFERENT_PICTURE = 11,
    TEST_ANCHORPOINT = 12,
    TEST_ARMATURE_NESTING = 13,
    TEST_ARMATURE_NESTING_2 = 14,
}
local armatureSceneIdx   = ArmatureTestIndex.TEST_ASYNCHRONOUS_LOADING

local ccs = ccs or {}
ccs.MovementEventType = {
    START = 0,
    COMPLETE = 1,
    LOOP_COMPLETE = 2, 
}

local ArmatureTestScene = class("ArmatureTestScene")
ArmatureTestScene.__index = ArmatureTestScene

function ArmatureTestScene.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, ArmatureTestScene)
    return target
end

function ArmatureTestScene:runThisTest()
    armatureSceneIdx   = ArmatureTestIndex.TEST_ASYNCHRONOUS_LOADING
    self:addChild(restartArmatureTest())
end

function ArmatureTestScene.create()
    local scene = ArmatureTestScene.extend(CCScene:create())
    local bg    = CCSprite:create("armature/bg.jpg")
    bg:setPosition(VisibleRect:center())

    local scaleX = VisibleRect:getVisibleRect().size.width / bg:getContentSize().width
    local scaleY = VisibleRect:getVisibleRect().size.height / bg:getContentSize().height

    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)

    scene:addChild(bg)
    return scene   
end

function ArmatureTestScene.toMainMenuCallback()
    CCArmatureDataManager:purge()
end

local ArmatureTestLayer = class("ArmatureTestLayer")
ArmatureTestLayer.__index = ArmatureTestLayer
ArmatureTestLayer._backItem   = nil
ArmatureTestLayer._restarItem = nil
ArmatureTestLayer._nextItem   = nil

function ArmatureTestLayer:onEnter()
    
end

function ArmatureTestLayer.title(idx)
    if ArmatureTestIndex.TEST_ASYNCHRONOUS_LOADING == idx then
        return "Test Asynchronous Loading"
    elseif ArmatureTestIndex.TEST_DIRECT_LOADING   == idx then
        return "Test Direct Loading"
    elseif ArmatureTestIndex.TEST_COCOSTUDIO_WITH_SKELETON == idx then
        return "Test Export From CocoStudio With Skeleton Effect"
    elseif ArmatureTestIndex.TEST_DRAGON_BONES_2_0 == idx then
        return "Test Export From DragonBones version 2.0"
    elseif ArmatureTestIndex.TEST_PERFORMANCE == idx then
        return "Test Performance"
    elseif ArmatureTestIndex.TEST_PERFORMANCE_BATCHNODE == idx then
        return "Test Performance of using BatchNode"
    elseif ArmatureTestIndex.TEST_CHANGE_ZORDER == idx then
        return "Test Change ZOrder Of Different Armature"
    elseif ArmatureTestIndex.TEST_ANIMATION_EVENT == idx then
        return "Test Armature Animation Event"
    elseif ArmatureTestIndex.TEST_FRAME_EVENT == idx then
        return "Test Frame Event"
    elseif ArmatureTestIndex.TEST_PARTICLE_DISPLAY == idx then
        return "Test Particle Display"
    elseif ArmatureTestIndex.TEST_USE_DIFFERENT_PICTURE == idx then
        return "Test One Armature Use Different Picture"
    elseif ArmatureTestIndex.TEST_ANCHORPOINT == idx then
        return "Test Set AnchorPoint"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING == idx then
        return "Test Armature Nesting"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING_2 == idx then
        return "Test Armature Nesting 2" 
    end
end

function ArmatureTestLayer.subTitle(idx)
    if ArmatureTestIndex.TEST_ASYNCHRONOUS_LOADING == idx then
        return "current percent :"
    elseif ArmatureTestIndex.TEST_PERFORMANCE == idx then
        return "Current Armature Count : "
    elseif ArmatureTestIndex.TEST_PERFORMANCE_BATCHNODE == idx then
        return "Current Armature Count : "
    elseif ArmatureTestIndex.TEST_PARTICLE_DISPLAY == idx then
        return "Touch to change animation"
    elseif ArmatureTestIndex.TEST_USE_DIFFERENT_PICTURE == idx then
        return "weapon and armature are in different picture"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING_2 == idx then
        return "Move to a mount and press the ChangeMount Button."
    else
        return ""
    end
end

function ArmatureTestLayer.create()
    local layer = ArmatureTestLayer.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end    

    return layer
end

function ArmatureTestLayer.backCallback()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(backArmatureTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function ArmatureTestLayer.restartCallback()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(restartArmatureTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function ArmatureTestLayer.nextCallback()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(nextArmatureTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function ArmatureTestLayer:createMenu()
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

function ArmatureTestLayer.toExtensionMenu()
    CCArmatureDataManager:purge()
    local scene = CocoStudioTest()
    if scene ~= nil then
        CCDirector:sharedDirector():replaceScene(scene)
    end
end

function ArmatureTestLayer:createToExtensionMenu()    
    CCMenuItemFont:setFontName("Arial")
    CCMenuItemFont:setFontSize(24)
    local menuItemFont = CCMenuItemFont:create("Back")
    menuItemFont:setPosition(ccp(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    menuItemFont:registerScriptTapHandler(ArmatureTestLayer.toExtensionMenu)

    local backMenu = CCMenu:create()
    backMenu:addChild(menuItemFont)
    backMenu:setPosition(ccp(0, 0))
    self:addChild(backMenu,10)
end

function ArmatureTestLayer:creatTitleAndSubTitle(idx)
    local title = CCLabelTTF:create(ArmatureTestLayer.title(idx),"Arial",18)
    title:setColor(ccc3(0,0,0))
    self:addChild(title, 1, 10000)
    title:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= ArmatureTestLayer.subTitle(idx) then
        local subTitle = CCLabelTTF:create(ArmatureTestLayer.subTitle(idx), "Arial", 18)
        subTitle:setColor(ccc3(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 60) )
    end
end

local TestAsynchronousLoading = class("TestAsynchronousLoading",ArmatureTestLayer)
TestAsynchronousLoading.__index = TestAsynchronousLoading

function TestAsynchronousLoading.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestAsynchronousLoading)
    return target
end

function TestAsynchronousLoading:onEnter()
    self._backItem:setEnabled(false)
    self._restarItem:setEnabled(false)
    self._nextItem:setEnabled(false)

    local title = CCLabelTTF:create(ArmatureTestLayer.title(1),"Arial",18)
    title:setColor(ccc3(0,0,0))
    self:addChild(title, 1, 10000)
    title:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= ArmatureTestLayer.subTitle(1) then
        local subInfo  = ArmatureTestLayer.subTitle(1) .. 0.0
        local subTitle = CCLabelTTF:create(subInfo, "Arial", 18)
        subTitle:setColor(ccc3(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( ccp(VisibleRect:center().x, VisibleRect:top().y - 60) )
    end

    local function dataLoaded(percent)
        local label = self:getChildByTag(10001)
        if nil ~= label then
            local subInfo = ArmatureTestLayer.subTitle(1) .. (percent * 100)
            label:setString(subInfo)
        end
        if percent >= 1 and nil ~= self._backItem and nil ~= self._restarItem and nil ~= self._nextItem then
            self._backItem:setEnabled(true)
            self._restarItem:setEnabled(true)
            self._nextItem:setEnabled(true)
        end
    end

    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/knight.png", "armature/knight.plist", "armature/knight.xml", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/robot.png", "armature/robot.plist", "armature/robot.xml", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/Cowboy.ExportJson", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/hero.ExportJson", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/horse.ExportJson", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/bear.ExportJson", dataLoaded)
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfoAsync("armature/HeroAnimation.ExportJson", dataLoaded)

end

function TestAsynchronousLoading.restartCallback()
    CCArmatureDataManager:purge()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(restartArmatureTest())
    CCDirector:sharedDirector():replaceScene(newScene)
end

function TestAsynchronousLoading.create()
    local layer = TestAsynchronousLoading.extend(CCLayer:create())

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

local TestDirectLoading = class("TestDirectLoading",ArmatureTestLayer)
TestDirectLoading.__index = TestDirectLoading

function TestDirectLoading.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestDirectLoading)
    return target
end

function TestDirectLoading:onEnter()
    CCArmatureDataManager:sharedArmatureDataManager():removeArmatureFileInfo("armature/bear.ExportJson")
    CCArmatureDataManager:sharedArmatureDataManager():addArmatureFileInfo("armature/bear.ExportJson")
    local armature = CCArmature:create("bear")
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(ccp(VisibleRect:center().x,VisibleRect:center().y))
    self:addChild(armature)
end

function TestDirectLoading.create()
    local layer = TestDirectLoading.extend(CCLayer:create())
    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer
end


local TestCSWithSkeleton = class("TestCSWithSkeleton",ArmatureTestLayer)
TestCSWithSkeleton.__index = TestCSWithSkeleton

function TestCSWithSkeleton.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestCSWithSkeleton)
    return target
end

function TestCSWithSkeleton:onEnter()
    local armature = CCArmature:create("Cowboy")
    armature:getAnimation():playWithIndex(0)
    armature:setScale(0.2)
    armature:setAnchorPoint(ccp(0.5, 0.5))
    armature:setPosition(ccp(winSize.width / 2, winSize.height / 2))
    self:addChild(armature)
end

function TestCSWithSkeleton.create()
    local layer = TestCSWithSkeleton.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer
end

local TestDragonBones20 = class("TestDragonBones20",ArmatureTestLayer)
TestDragonBones20.__index = TestDragonBones20

function TestDragonBones20.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestDragonBones20)
    return target
end

function TestDragonBones20:onEnter()    
    local armature = CCArmature:create("Dragon")
    armature:getAnimation():playWithIndex(1)
    armature:getAnimation():setSpeedScale(0.4)
    armature:setPosition(ccp(VisibleRect:center().x, VisibleRect:center().y * 0.3))
    armature:setScale(0.6)
    self:addChild(armature)
end

function TestDragonBones20.create()
    local layer = TestDragonBones20.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer   
end

local TestPerformance = class("TestPerformance",ArmatureTestLayer)
TestPerformance.__index = TestPerformance
TestPerformance._armatureCount = 0
TestPerformance._frames        = 0
TestPerformance._times         = 0
TestPerformance._lastTimes     = 0
TestPerformance._generated     = false

function TestPerformance.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestPerformance)
    return target
end

function TestPerformance:refreshTitile()
    local subTitleInfo = ArmatureTestLayer.subTitle(5) .. self._armatureCount
    local label        = tolua.cast(self:getChildByTag(10001),"CCLabelTTF")
    label:setString(subTitleInfo)
end

function TestPerformance:addArmatureToParent(armature)
    self:addChild(armature, 0, armaturePerformanceTag + self._armatureCount)
end

function TestPerformance:removeArmatureFromParent(tag)
    self:removeChildByTag(armaturePerformanceTag + self._armatureCount, true)
end

function TestPerformance:addArmature(num)
    for i = 1, num do
        self._armatureCount = self._armatureCount + 1
        local armature = CCArmature:create("Knight_f/Knight")
        armature:getAnimation():playWithIndex(0)
        armature:setPosition(50 + self._armatureCount * 2, 150)
        armature:setScale(0.6)
        self:addArmatureToParent(armature)
    end

    self:refreshTitile()
end

function TestPerformance:onEnter()

    local function onIncrease(sender)
        self:addArmature(20)
    end

    local function onDecrease(sender)
        if self._armatureCount == 0 then
            return
        end

        for i = 1, 20 do
            self:removeArmatureFromParent(armaturePerformanceTag + self._armatureCount)
            self._armatureCount = self._armatureCount - 1
            self:refreshTitile()
        end
    end

    CCMenuItemFont:setFontSize(65)
    local decrease = CCMenuItemFont:create(" - ")
    decrease:setColor(ccc3(0,200,20))
    decrease:registerScriptTapHandler(onDecrease)

    local increase = CCMenuItemFont:create(" + ")
    increase:setColor(ccc3(0,200,20))
    increase:registerScriptTapHandler(onIncrease)
    
    local menu = CCMenu:create()
    menu:addChild(decrease)
    menu:addChild(increase)
    menu:alignItemsHorizontally()
    menu:setPosition(ccp(VisibleRect:getVisibleRect().size.width/2, VisibleRect:getVisibleRect().size.height-100))
    self:addChild(menu, 10000)

    self._armatureCount = 0
    self._frames        = 0
    self._times         = 0
    self._lastTimes     = 0
    self._generated     = false

    self:addArmature(100)
end

function TestPerformance.create()
    local layer = TestPerformance.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer   
end

local TestPerformanceBatchNode = class("TestPerformanceBatchNode",TestPerformance)
TestPerformanceBatchNode.__index = TestPerformanceBatchNode
TestPerformanceBatchNode._batchNode = nil

function TestPerformanceBatchNode.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestPerformanceBatchNode)
    return target
end

function TestPerformanceBatchNode:addArmatureToParent(armature)
    self._batchNode:addChild(armature, 0, armaturePerformanceTag + self._armatureCount)
end

function TestPerformanceBatchNode:removeArmatureFromParent(tag)
    self._batchNode:removeChildByTag(armaturePerformanceTag + self._armatureCount, true)
end

function TestPerformanceBatchNode:onEnter()    
    self._batchNode = CCBatchNode:create()
    self:addChild(self._batchNode)

    local function onIncrease(sender)
        self:addArmature(20)
    end

    local function onDecrease(sender)
        if self._armatureCount == 0 then
            return
        end

        for i = 1, 20 do
            self:removeArmatureFromParent(armaturePerformanceTag + self._armatureCount)
            self._armatureCount = self._armatureCount - 1
            self:refreshTitile()
        end
    end

    CCMenuItemFont:setFontSize(65)
    local decrease = CCMenuItemFont:create(" - ")
    decrease:setColor(ccc3(0,200,20))
    decrease:registerScriptTapHandler(onDecrease)

    local increase = CCMenuItemFont:create(" + ")
    increase:setColor(ccc3(0,200,20))
    increase:registerScriptTapHandler(onIncrease)
    
    local menu = CCMenu:create()
    menu:addChild(decrease)
    menu:addChild(increase)
    menu:alignItemsHorizontally()
    menu:setPosition(ccp(VisibleRect:getVisibleRect().size.width/2, VisibleRect:getVisibleRect().size.height-100))
    self:addChild(menu, 10000)

    self._armatureCount = 0
    self._frames        = 0
    self._times         = 0
    self._lastTimes     = 0
    self._generated     = false

    self:addArmature(100)
end

function TestPerformanceBatchNode.create()
    local layer = TestPerformanceBatchNode.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer   
end

local TestChangeZorder = class("TestChangeZorder",ArmatureTestLayer)
TestChangeZorder.__index = TestChangeZorder
TestChangeZorder.currentTag = -1

function TestChangeZorder.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestChangeZorder)
    return target
end

function TestChangeZorder:onEnter()  
    self.currentTag = -1

    local armature = CCArmature:create("Knight_f/Knight")
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(ccp(winSize.width / 2, winSize.height / 2 - 100 ))
    armature:setScale(0.6)
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    armature = CCArmature:create("Cowboy")
    armature:getAnimation():playWithIndex(0)
    armature:setScale(0.24)
    armature:setPosition(ccp(winSize.width / 2, winSize.height / 2 - 100))
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    armature = CCArmature:create("Dragon")
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(ccp(winSize.width / 2, winSize.height / 2 - 100))
    armature:setScale(0.6)
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    local function changeZorder(dt)
        local node = self:getChildByTag(self.currentTag)
        node:setZOrder(math.random(0,1) * 3)
        self.currentTag = (self.currentTag + 1) % 3
    end

    schedule(self,changeZorder, 1)
end

function TestChangeZorder.create()
    local layer = TestChangeZorder.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer   
end

--UNDO callback
local TestAnimationEvent = class("TestAnimationEvent",ArmatureTestLayer)
TestAnimationEvent.__index = TestAnimationEvent

function TestAnimationEvent.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestAnimationEvent)
    return target
end

function TestAnimationEvent:onEnter()    
    local armature = CCArmature:create("Cowboy")
    armature:getAnimation():play("Fire")
    armature:setScaleX(-0.24)
    armature:setScaleY(0.24)
    armature:setPosition(ccp(VisibleRect:left().x + 50, VisibleRect:left().y))

    local function callback1()
        armature:runAction(CCScaleTo:create(0.3, 0.24, 0.24))
        armature:getAnimation():play("FireMax", 10)
    end

    local function callback2()
        armature:runAction(CCScaleTo:create(0.3, -0.24, 0.24))
        armature:getAnimation():play("Fire", 10)
    end

    local function animationEvent(armatureBack,movementType,movementID)
        local id = movementID
        if movementType == ccs.MovementEventType.LOOP_COMPLETE then
            if id == "Fire" then
                armatureBack:stopAllActions()
                local actionToRight = CCMoveTo:create(2, ccp(VisibleRect:right().x - 50, VisibleRect:right().y))
                local arr = CCArray:create()
                arr:addObject(actionToRight)
                arr:addObject(CCCallFunc:create(callback1))
                armatureBack:runAction(CCSequence:create(arr))
                armatureBack:getAnimation():play("Walk")
            elseif id == "FireMax" then
                armatureBack:stopAllActions()
                local actionToLeft = CCMoveTo:create(2, ccp(VisibleRect:left().x + 50, VisibleRect:left().y))
                local arr = CCArray:create()
                arr:addObject(actionToLeft)
                arr:addObject(CCCallFunc:create(callback2))
                armatureBack:runAction(CCSequence:create(arr))
                armatureBack:getAnimation():play("Walk")
            end
        end
    end

    armature:getAnimation():setMovementEventCallFunc(animationEvent)

    self:addChild(armature)
end

function TestAnimationEvent.create()
    local layer = TestAnimationEvent.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer   
end

local TestFrameEvent = class("TestFrameEvent",ArmatureTestLayer)
TestFrameEvent.__index = TestFrameEvent

function TestFrameEvent.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestFrameEvent)
    return target
end

function TestFrameEvent:onEnter()    
    local armature = CCArmature:create("HeroAnimation")
    armature:getAnimation():play("attack")
    armature:getAnimation():setSpeedScale(0.5)
    armature:setPosition(ccp(VisibleRect:center().x - 50, VisibleRect:center().y -100))

    local function onFrameEvent( bone,evt,originFrameIndex,currentFrameIndex)
        local info = string.format("(%s) emit a frame event (%s) at frame index (%d).",bone:getName(),evt,currentFrameIndex)
        print(info)
        if (not self:getActionByTag(frameEventActionTag)) or (not self:getActionByTag(frameEventActionTag):isDone()) then
            self:stopAllActions()
            local action =  CCShatteredTiles3D:create(0.2, CCSizeMake(16,12), 5, false) 
            action:setTag(frameEventActionTag)
            self:runAction(action)
        end
    end

    armature:getAnimation():setFrameEventCallFunc(onFrameEvent)

    self:addChild(armature)

    local function checkAction(dt)
        if self:numberOfRunningActions() == 0 and self:getGrid() ~= nil then
            self:setGrid(nil)
        end
    end

    self:scheduleUpdateWithPriorityLua(checkAction,0)

    local function onNodeEvent(tag)
        if "exit" == tag then
            self:unscheduleUpdate()
        end
    end
end

function TestFrameEvent.create()
    local layer = TestFrameEvent.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 
    return layer   
end

local TestParticleDisplay = class("TestParticleDisplay",ArmatureTestLayer)
TestParticleDisplay.__index = TestParticleDisplay
TestParticleDisplay.animationID = 0
TestParticleDisplay.armature    = nil

function TestParticleDisplay.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestParticleDisplay)
    return target
end

function TestParticleDisplay:onEnter() 
    self:setTouchEnabled(true) 
    self.animationID = 0

    self.armature = CCArmature:create("robot")
    self.armature:getAnimation():playWithIndex(0)
    self.armature:setPosition(VisibleRect:center())
    self.armature:setScale(0.48)
    self:addChild(self.armature)

    local p1 = CCParticleSystemQuad:create("Particles/SmallSun.plist")
    local p2 = CCParticleSystemQuad:create("Particles/SmallSun.plist")

    local bone  = CCBone:create("p1")
    bone:addDisplay(p1, 0)
    bone:changeDisplayWithIndex(0, true)
    bone:setIgnoreMovementBoneData(true)
    bone:setZOrder(100)
    bone:setScale(1.2)
    self.armature:addBone(bone, "bady-a3")
    
    bone  = CCBone:create("p2")
    bone:addDisplay(p2, 0)
    bone:changeDisplayWithIndex(0, true)
    bone:setIgnoreMovementBoneData(true)
    bone:setZOrder(100)
    bone:setScale(1.2)
    self.armature:addBone(bone, "bady-a30")

    local function onTouchBegan(x, y)
        self.animationID = (self.animationID + 1) % self.armature:getAnimation():getMovementCount()
        self.armature:getAnimation():playWithIndex(self.animationID)
        return false
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return onTouchBegan(x,y)
        end
    end

    self:registerScriptTouchHandler(onTouch)
end

function TestParticleDisplay.create()
    local layer = TestParticleDisplay.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer   
end

local TestUseMutiplePicture = class("TestUseMutiplePicture",ArmatureTestLayer)
TestUseMutiplePicture.__index = TestUseMutiplePicture
TestUseMutiplePicture.displayIndex = 0
TestUseMutiplePicture.armature    = nil

function TestUseMutiplePicture.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestUseMutiplePicture)
    return target
end

function TestUseMutiplePicture:onEnter() 
    self:setTouchEnabled(true) 
    self.displayIndex = 1

    self.armature = CCArmature:create("Knight_f/Knight")
    self.armature:getAnimation():playWithIndex(0)
    self.armature:setPosition(ccp(VisibleRect:left().x + 70, VisibleRect:left().y))
    self.armature:setScale(1.2)
    self:addChild(self.armature)

    local weapon = 
    {
        "weapon_f-sword.png", 
        "weapon_f-sword2.png", 
        "weapon_f-sword3.png", 
        "weapon_f-sword4.png", 
        "weapon_f-sword5.png", 
        "weapon_f-knife.png", 
        "weapon_f-hammer.png",
    }

    local i = 1
    for i = 1,table.getn(weapon) do
        local skin = CCSkin:createWithSpriteFrameName(weapon[i])
        self.armature:getBone("weapon"):addDisplay(skin, i - 1)
    end

    local function onTouchBegan(x, y)
        self.displayIndex = (self.displayIndex + 1) % (table.getn(weapon) - 1)
        self.armature:getBone("weapon"):changeDisplayWithIndex(self.displayIndex, true)
        return false
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return onTouchBegan(x,y)
        end
    end

    self:registerScriptTouchHandler(onTouch)
end

function TestUseMutiplePicture.create()
    local layer = TestUseMutiplePicture.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer   
end

local TestAnchorPoint = class("TestAnchorPoint",ArmatureTestLayer)
TestAnchorPoint.__index = TestAnchorPoint

function TestAnchorPoint.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestAnchorPoint)
    return target
end

function TestAnchorPoint:onEnter()
    local i = 1
    for  i = 1 , 5 do
        local armature = CCArmature:create("Cowboy")
        armature:getAnimation():playWithIndex(0)
        armature:setPosition(VisibleRect:center())
        armature:setScale(0.2)
        self:addChild(armature, 0, i - 1)
    end

    self:getChildByTag(0):setAnchorPoint(ccp(0,0))
    self:getChildByTag(1):setAnchorPoint(ccp(0,1))
    self:getChildByTag(2):setAnchorPoint(ccp(1,0))
    self:getChildByTag(3):setAnchorPoint(ccp(1,1))
    self:getChildByTag(4):setAnchorPoint(ccp(0.5,0.5))
end

function TestAnchorPoint.create()
    local layer = TestAnchorPoint.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer
end

local TestArmatureNesting = class("TestArmatureNesting",ArmatureTestLayer)
TestArmatureNesting.__index = TestArmatureNesting
TestArmatureNesting.weaponIndex = 0
TestArmatureNesting.armature    = nil

function TestArmatureNesting.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestArmatureNesting)
    return target
end

function TestArmatureNesting:onEnter()
    self:setTouchEnabled(true) 
    self.weaponIndex = 0

    self.armature = CCArmature:create("cyborg")
    self.armature:getAnimation():playWithIndex(1)
    self.armature:setPosition(VisibleRect:center())
    self.armature:setScale(1.2)
    self.armature:getAnimation():setSpeedScale(0.4)
    self:addChild(self.armature)

    local function onTouchBegan(x, y)
        self.weaponIndex = (self.weaponIndex + 1) % 4
        self.armature:getBone("armInside"):getChildArmature():getAnimation():playWithIndex(self.weaponIndex)
        self.armature:getBone("armOutside"):getChildArmature():getAnimation():playWithIndex(self.weaponIndex)
        return false
    end

    local function onTouch(eventType, x, y)
        if eventType == "began" then
            return onTouchBegan(x,y)
        end
    end

    self:registerScriptTouchHandler(onTouch)
end

function TestArmatureNesting.create()
    local layer = TestArmatureNesting.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer 
end

local Hero = class("Hero")
Hero.__index = Hero
Hero._mount  = nil
Hero._layer  = nil

function Hero.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, Hero)
    return target
end

function Hero:changeMount(armature)
    if nil == armature then
        --note
        self:retain()

        self:playWithIndex(0)
        self._mount:getBone("hero"):removeDisplay(0)
        self._mount:stopAllActions()
        self:setPosition(self._mount:getPosition())
        self._layer:addChild(self)
        self:release()
        self._mount = armature
    else
        self._mount = armature
        self:retain()
        self:removeFromParentAndCleanup(false)
        local bone = armature:getBone("hero")
        bone:addDisplay(self, 0)
        bone:changeDisplayWithIndex(0, true)
        bone:setIgnoreMovementBoneData(true)
        self:setPosition(ccp(0,0))
        self:playWithIndex(1)
        self:setScale(1)
        self:release()
    end
end

function Hero:playWithIndex(index)
    self:getAnimation():playWithIndex(index)
    if nil ~= self._mount then
        self._mount:getAnimation():playWithIndex(index)
    end
end

function Hero.create(name)
    local hero = Hero.extend(CCArmature:create(name))
    return hero
end



local TestArmatureNesting2 = class("TestArmatureNesting",ArmatureTestLayer)
TestArmatureNesting2.__index = TestArmatureNesting2
TestArmatureNesting2._hero   = nil
TestArmatureNesting2._horse   = nil
TestArmatureNesting2._horse2  = nil
TestArmatureNesting2._bear    = nil
TestArmatureNesting2._touchedMenu = nil

function TestArmatureNesting2.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestArmatureNesting2)
    return target
end

function TestArmatureNesting2:onEnter()

    self:setTouchEnabled(true)

    local function onTouchesEnded(tableArray)
        local x,y = tableArray[1],tableArray[2]
        local armature = self._hero._mount and self._hero._mount  or self._hero
        if x < armature:getPositionX() then
            armature:setScaleX(-1)
        else
            armature:setScaleX(1)
        end

        armature:stopAllActions()
        local move = CCMoveTo:create(2, ccp(x,y))
        local arr  = CCArray:create()
        arr:addObject(move)
        armature:runAction(CCSequence:create(arr))
    end

    local function onTouch(eventType, tableArray)
        if eventType == "ended" then
            return onTouchesEnded(tableArray)
        end
    end

    self:registerScriptTouchHandler(onTouch,true)

    local function changeMountCallback(sender)
        self._hero:stopAllActions()

        if nil ~= self._hero._mount then
            self._hero:changeMount(nil)
        else
            if ccpDistance(ccp(self._hero:getPosition()),ccp(self._horse:getPosition())) < 20 then
                self._hero:changeMount(self._horse)
            elseif ccpDistance(ccp(self._hero:getPosition()),ccp(self._horse2:getPosition())) < 20 then
                self._hero:changeMount(self._horse2)
            elseif ccpDistance(ccp(self._hero:getPosition()),ccp(self._bear:getPosition())) < 30 then
                self._hero:changeMount(self._bear)
            end
        end
    end

    self._touchedMenu = false
    local label = CCLabelTTF:create("Change Mount", "Arial", 20)
    local menuItem = CCMenuItemLabel:create(label)
    menuItem:registerScriptTapHandler(changeMountCallback)
    local menu = CCMenu:create()
    menu:addChild(menuItem)
    menu:setPosition(ccp(0,0))
    menuItem:setPosition( ccp( VisibleRect:right().x - 67, VisibleRect:bottom().y + 50) )
    self:addChild(menu, 2)

    self._hero = Hero.create("hero")
    self._hero._layer = self
    self._hero:playWithIndex(0)
    self._hero:setPosition(ccp(VisibleRect:left().x + 20, VisibleRect:left().y))
    self:addChild(self._hero)

    self._horse = self:createMount("horse", VisibleRect:center())

    self._horse2 = self:createMount("horse", ccp(120, 200))
    self._horse2:setOpacity(200)

    self._bear = self:createMount("bear", ccp(300,70))
end

function TestArmatureNesting2:createMount(name,pt)
    local armature = CCArmature:create(name)
    armature:getAnimation():playWithIndex(0)
    armature:setPosition(pt)
    self:addChild(armature)
    return armature
end

function TestArmatureNesting2.create()
    local layer = TestArmatureNesting2.extend(CCLayer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        local function onNodeEvent(event)
            if "enter" == event then
                layer:onEnter()
            end
        end
        layer:registerScriptHandler(onNodeEvent)
    end 

    return layer 
end


local armatureSceneArr =
{
    TestAsynchronousLoading.create,
    TestDirectLoading.create,
    TestCSWithSkeleton.create,
    TestDragonBones20.create,
    TestPerformance.create,
    TestPerformanceBatchNode.create,
    TestChangeZorder.create,
    TestAnimationEvent.create,
    TestFrameEvent.create,
    TestParticleDisplay.create,
    TestUseMutiplePicture.create,
    TestAnchorPoint.create,
    TestArmatureNesting.create,
    TestArmatureNesting2.create,
}

function nextArmatureTest()
    armatureSceneIdx = armatureSceneIdx + 1
    armatureSceneIdx = armatureSceneIdx % table.getn(armatureSceneArr)
    if 0 == armatureSceneIdx then
        armatureSceneIdx = table.getn(armatureSceneArr)
    end
    return armatureSceneArr[armatureSceneIdx]()
end

function backArmatureTest() 
    armatureSceneIdx = armatureSceneIdx - 1
    if armatureSceneIdx <= 0 then
        armatureSceneIdx = armatureSceneIdx + table.getn(armatureSceneArr)
    end

    return armatureSceneArr[armatureSceneIdx]()
end

function restartArmatureTest()
    return armatureSceneArr[armatureSceneIdx]()
end

local function addFileInfo()
   
end

function runArmatureTestScene()
    local scene = ArmatureTestScene.create()
    scene:runThisTest()
    CCDirector:sharedDirector():replaceScene(scene)
end
