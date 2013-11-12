local itemTagBasic = 1000
local winSize = cc.Director:getInstance():getWinSize()
local scheduler = cc.Director:getInstance():getScheduler()
local ArmatureTestIndex = 
{
    TEST_COCOSTUDIO_WITH_SKELETON = 1,
    TEST_DRAGON_BONES_2_0 = 2,
    TEST_PERFORMANCE = 3,
    TEST_CHANGE_ZORDER = 4,
    TEST_ANIMATION_EVENT = 5,
    TEST_PARTICLE_DISPLAY = 6,
    TEST_USE_DIFFERENT_PICTURE = 7,
    TEST_BOUDINGBOX = 8,
    TEST_ANCHORPOINT = 9,
    TEST_ARMATURE_NESTING = 10,
}
local armatureSceneIdx   = ArmatureTestIndex.TEST_COCOSTUDIO_WITH_SKELETON

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
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/TestBone0.png", "armature/TestBone0.plist", "armature/TestBone.json")
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/Cowboy0.png", "armature/Cowboy0.plist", "armature/Cowboy.ExportJson")
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/knight.png", "armature/knight.plist", "armature/knight.xml")
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/weapon.png", "armature/weapon.plist", "armature/weapon.xml")
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/robot.png", "armature/robot.plist", "armature/robot.xml")
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/cyborg.png", "armature/cyborg.plist", "armature/cyborg.xml")
    ccs.ArmatureDataManager:getInstance():addArmatureFileInfo("armature/Dragon.png", "armature/Dragon.plist", "armature/Dragon.xml")

    armatureSceneIdx   = ArmatureTestIndex.TEST_COCOSTUDIO_WITH_SKELETON
    self:addChild(restartArmatureTest())
end

function ArmatureTestScene.create()
    local scene = ArmatureTestScene.extend(cc.Scene:create())
    local bg    = cc.Sprite:create("armature/bg.jpg")
    bg:setPosition(VisibleRect:center())

    local scaleX = VisibleRect:getVisibleRect().width / bg:getContentSize().width
    local scaleY = VisibleRect:getVisibleRect().height / bg:getContentSize().height

    bg:setScaleX(scaleX)
    bg:setScaleY(scaleY)

    scene:addChild(bg)
    return scene   
end

function ArmatureTestScene.toMainMenuCallback()
    ccs.ArmatureDataManager:purgeArmatureSystem()
end

local ArmatureTestLayer = class("ArmatureTestLayer")
ArmatureTestLayer.__index = ArmatureTestLayer

function ArmatureTestLayer:onEnter()
    
end

function ArmatureTestLayer.title(idx)
    if ArmatureTestIndex.TEST_COCOSTUDIO_WITH_SKELETON == idx then
        return "Test Export From CocoStudio With Skeleton Effect"
    elseif ArmatureTestIndex.TEST_DRAGON_BONES_2_0 == idx then
        return "Test Export From DragonBones version 2.0"
    elseif ArmatureTestIndex.TEST_PERFORMANCE == idx then
        return "Test Performance"
    elseif ArmatureTestIndex.TEST_CHANGE_ZORDER == idx then
        return "Test Change ZOrder Of Different Armature"
    elseif ArmatureTestIndex.TEST_ANIMATION_EVENT == idx then
        return "Test Armature Animation Event"
    elseif ArmatureTestIndex.TEST_PARTICLE_DISPLAY == idx then
        return "Test Particle Display"
    elseif ArmatureTestIndex.TEST_USE_DIFFERENT_PICTURE == idx then
        return "Test One Armature Use Different Picture"
    elseif ArmatureTestIndex.TEST_BOUDINGBOX == idx then
        return "Test BoundingBox"
    elseif ArmatureTestIndex.TEST_ANCHORPOINT == idx then
        return "Test Set AnchorPoint"
    elseif ArmatureTestIndex.TEST_ARMATURE_NESTING == idx then
        return "Test Armature Nesting"
    end
end

function ArmatureTestLayer.subTitle(idx)
    if ArmatureTestIndex.TEST_PERFORMANCE == idx then
        return "Current Armature Count : "
    elseif ArmatureTestIndex.TEST_PARTICLE_DISPLAY == idx then
        return "Touch to change animation"
    elseif ArmatureTestIndex.TEST_USE_DIFFERENT_PICTURE == idx then
        return "weapon and armature are in different picture"
    else
        return ""
    end
end

function ArmatureTestLayer.create()
    local layer = ArmatureTestLayer.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
    end    

    return layer
end

function ArmatureTestLayer.backCallback()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(backArmatureTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function ArmatureTestLayer.restartCallback()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(restartArmatureTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function ArmatureTestLayer.nextCallback()
    local newScene = ArmatureTestScene.create()
    newScene:addChild(nextArmatureTest())
    cc.Director:getInstance():replaceScene(newScene)
end

function ArmatureTestLayer:createMenu()
    local menu = cc.Menu:create()
    
    local item1 = cc.MenuItemImage:create(s_pPathB1, s_pPathB2)
    item1:registerScriptTapHandler(self.backCallback)
    menu:addChild(item1,itemTagBasic)
    local item2 = cc.MenuItemImage:create(s_pPathR1, s_pPathR2)
    item2:registerScriptTapHandler(self.restartCallback)
    menu:addChild(item2,itemTagBasic)
    local item3 = cc.MenuItemImage:create(s_pPathF1, s_pPathF2)
    menu:addChild(item3,itemTagBasic) 
    item3:registerScriptTapHandler(self.nextCallback)
    
    local size = cc.Director:getInstance():getWinSize()        
    item1:setPosition(cc.p(size.width / 2 - item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    item2:setPosition(cc.p(size.width / 2, item2:getContentSize().height / 2))
    item3:setPosition(cc.p(size.width / 2 + item2:getContentSize().width * 2, item2:getContentSize().height / 2))
    
    menu:setPosition(cc.p(0, 0))

    self:addChild(menu)
end

function ArmatureTestLayer.toExtensionMenu()
    local scene = ExtensionsTestMain()
    if scene ~= nil then
        cc.Director:getInstance():replaceScene(scene)
    end
end

function ArmatureTestLayer:createToExtensionMenu()    
    cc.MenuItemFont:setFontName("Arial")
    cc.MenuItemFont:setFontSize(24)
    local menuItemFont = cc.MenuItemFont:create("Back")
    menuItemFont:setPosition(cc.p(VisibleRect:rightBottom().x - 50, VisibleRect:rightBottom().y + 25))
    menuItemFont:registerScriptTapHandler(ArmatureTestLayer.toExtensionMenu)

    local backMenu = cc.Menu:create()
    backMenu:addChild(menuItemFont)
    backMenu:setPosition(cc.p(0, 0))
    self:addChild(backMenu,10)
end

function ArmatureTestLayer:creatTitleAndSubTitle(idx)
    local title = cc.LabelTTF:create(ArmatureTestLayer.title(idx),"Arial",18)
    title:setColor(cc.c3b(0,0,0))
    self:addChild(title, 1, 10000)
    title:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 30))
    local subTitle = nil
    if "" ~= ArmatureTestLayer.subTitle(idx) then
        local subTitle = cc.LabelTTF:create(ArmatureTestLayer.subTitle(idx), "Arial", 18)
        subTitle:setColor(cc.c3b(0,0,0))
        self:addChild(subTitle, 1, 10001)
        subTitle:setPosition( cc.p(VisibleRect:center().x, VisibleRect:top().y - 60) )
    end
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
    local armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():playByIndex(0)
    armature:setScale(0.2)
    armature:setAnchorPoint(cc.p(0.5, 0.5))
    armature:setPosition(cc.p(winSize.width / 2, winSize.height / 2))
    self:addChild(armature)
end

function TestCSWithSkeleton.create()
    local layer = TestCSWithSkeleton.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
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
    local armature = ccs.Armature:create("Dragon")
    armature:getAnimation():playByIndex(1)
    armature:getAnimation():setAnimationScale(0.4)
    armature:setScale(0.6)
    armature:setAnchorPoint(cc.p(0.5, 0.5))
    armature:setPosition(cc.p(winSize.width / 2, winSize.height / 2))
    self:addChild(armature)
end

function TestDragonBones20.create()
    local layer = TestDragonBones20.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
    end 
    return layer   
end

local TestPerformance = class("TestPerformance",ArmatureTestLayer)
TestPerformance.__index = TestPerformance
TestPerformance.armatureCount = 0
TestPerformance.times         = 0
TestPerformance.testPerformanceEntry = 0
TestPerformance.selfLayer = nil

function TestPerformance.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestPerformance)
    return target
end

function TestPerformance.update(delta)
    TestPerformance.times = TestPerformance.times + delta
    if TestPerformance.times > 0.25 then
        TestPerformance.time = 0
        local armature = ccs.Armature:create("Knight_f/Knight")
        armature:getAnimation():playByIndex(0)
        armature:setPosition(cc.p(50 + TestPerformance.armatureCount * 5, winSize.height / 2))
        armature:setScale(0.6)
        TestPerformance.armatureCount = TestPerformance.armatureCount + 1
        TestPerformance.selfLayer:addChild(armature,TestPerformance.armatureCount)

        local subTitle = tolua.cast(TestPerformance.selfLayer:getChildByTag(10001),"LabelTTF")
        if nil ~= subTitle then
            local info = ArmatureTestLayer.subTitle(ArmatureTestIndex.TEST_PERFORMANCE) .. TestPerformance.armatureCount
            subTitle:setString(info)
        end        
    end
end

function TestPerformance.onEnterOrExit(tag)
    if tag == "enter" then
        TestPerformance.testPerformanceEntry = scheduler:scheduleScriptFunc(TestPerformance.update, 0.0, false)
    elseif tag == "exit" then
        scheduler:unscheduleScriptEntry(TestPerformance.testPerformanceEntry)
    end
end

function TestPerformance:onEnter()
    TestPerformance.armatureCount = 0
    TestPerformance.times         = 0
    TestPerformance.selfLayer = nil
    self:registerScriptHandler(self.onEnterOrExit)
end

function TestPerformance.create()
    local layer = TestPerformance.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
        TestPerformance.selfLayer = layer
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

    local armature = ccs.Armature:create("Knight_f/Knight")
    armature:getAnimation():playByIndex(0)
    armature:setPosition(cc.p(winSize.width / 2, winSize.height / 2 - 100 ))
    armature:setScale(0.6)
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():playByIndex(0)
    armature:setScale(0.24)
    armature:setPosition(cc.p(winSize.width / 2, winSize.height / 2 - 100))
    self.currentTag = self.currentTag + 1
    self:addChild(armature, self.currentTag, self.currentTag)

    armature = ccs.Armature:create("Dragon")
    armature:getAnimation():playByIndex(0)
    armature:setPosition(cc.p(winSize.width / 2, winSize.height / 2 - 100))
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
    local layer = TestChangeZorder.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
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
    local armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():play("Fire")
    armature:setScaleX(-0.24)
    armature:setScaleY(0.24)
    armature:setPosition(cc.p(VisibleRect:left().x + 50, VisibleRect:left().y))
    --armature:getAnimation()->MovementEventSignal.connect(this, &TestAnimationEvent::animationEvent)
    self:addChild(armature)
end

function TestAnimationEvent.create()
    local layer = TestAnimationEvent.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
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

    self.armature = ccs.Armature:create("robot")
    self.armature:getAnimation():playByIndex(0)
    self.armature:setPosition(VisibleRect:center())
    self.armature:setScale(0.48)
    self:addChild(self.armature)

    local p1 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")
    local p2 = cc.ParticleSystemQuad:create("Particles/SmallSun.plist")

    local bone  = ccs.Bone:create("p1")
    bone:addDisplay(p1, 0)
    bone:changeDisplayByIndex(0, true)
    bone:setIgnoreMovementBoneData(true)
    bone:setZOrder(100)
    bone:setScale(1.2)
    self.armature:addBone(bone, "bady-a3")
    
    bone  = ccs.Bone:create("p2")
    bone:addDisplay(p2, 0)
    bone:changeDisplayByIndex(0, true)
    bone:setIgnoreMovementBoneData(true)
    bone:setZOrder(100)
    bone:setScale(1.2)
    self.armature:addBone(bone, "bady-a30")

    local function onTouchBegan(x, y)
        self.animationID = (self.animationID + 1) % self.armature:getAnimation():getMovementCount()
        self.armature:getAnimation():playByIndex(self.animationID)
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
    local layer = TestParticleDisplay.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
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

    self.armature = ccs.Armature:create("Knight_f/Knight")
    self.armature:getAnimation():playByIndex(0)
    self.armature:setPosition(cc.p(VisibleRect:left().x + 70, VisibleRect:left().y))
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
    };

    local i = 1
    for i = 1,table.getn(weapon) do
        local skin = ccs.Skin:createWithSpriteFrameName(weapon[i])
        self.armature:getBone("weapon"):addDisplay(skin, i - 1)
    end

    local function onTouchBegan(x, y)
        self.displayIndex = (self.displayIndex + 1) % (table.getn(weapon) - 1)
        self.armature:getBone("weapon"):changeDisplayByIndex(self.displayIndex, true)
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
    local layer = TestUseMutiplePicture.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
    end 

    return layer   
end

local TestBoundingBox = class("TestBoundingBox",ArmatureTestLayer)
TestBoundingBox.__index = TestBoundingBox

function TestBoundingBox.extend(target)
    local t = tolua.getpeer(target)
    if not t then
        t = {}
        tolua.setpeer(target, t)
    end
    setmetatable(t, TestBoundingBox)
    return target
end

function TestBoundingBox:onEnter()
    local armature = ccs.Armature:create("Cowboy")
    armature:getAnimation():playByIndex(0)
    armature:setPosition(VisibleRect:center())
    armature:setScale(0.2)
    self:addChild(armature)
end

function TestBoundingBox.create()
    local layer = TestBoundingBox.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
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
        local armature = ccs.Armature:create("Cowboy")
        armature:getAnimation():playByIndex(0);
        armature:setPosition(VisibleRect:center())
        armature:setScale(0.2)
        self:addChild(armature, 0, i - 1)
    end

    self:getChildByTag(0):setAnchorPoint(cc.p(0,0))
    self:getChildByTag(1):setAnchorPoint(cc.p(0,1))
    self:getChildByTag(2):setAnchorPoint(cc.p(1,0))
    self:getChildByTag(3):setAnchorPoint(cc.p(1,1))
    self:getChildByTag(4):setAnchorPoint(cc.p(0.5,0.5))
end

function TestAnchorPoint.create()
    local layer = TestAnchorPoint.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
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

    self.armature = ccs.Armature:create("cyborg")
    self.armature:getAnimation():playByIndex(1)
    self.armature:setPosition(VisibleRect:center())
    self.armature:setScale(1.2)
    self.armature:getAnimation():setAnimationScale(0.4)
    self:addChild(self.armature)

    local function onTouchBegan(x, y)
        self.weaponIndex = (self.weaponIndex + 1) % 4
        self.armature:getBone("armInside"):getChildArmature():getAnimation():playByIndex(self.weaponIndex)
        self.armature:getBone("armOutside"):getChildArmature():getAnimation():playByIndex(self.weaponIndex)
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
    local layer = TestArmatureNesting.extend(cc.Layer:create())

    if nil ~= layer then
        layer:createMenu()
        layer:createToExtensionMenu()
        layer:onEnter()
        layer:creatTitleAndSubTitle(armatureSceneIdx)
    end 

    return layer 
end

local armatureSceneArr =
{
    TestCSWithSkeleton.create,
    TestDragonBones20.create,
    TestPerformance.create,
    TestChangeZorder.create,
    TestAnimationEvent.create,
    TestParticleDisplay.create,
    TestUseMutiplePicture.create,
    TestBoundingBox.create,
    TestAnchorPoint.create,
    TestArmatureNesting.create,
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

function runArmatureTest()
    local newScene = ArmatureTestScene.create()
    newScene:runThisTest()
    return newScene
end
